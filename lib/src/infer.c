/**
 * @file
 * @brief fmtparser inference API implementation
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#include <stddef.h>
#include <stddef.h>
#include "fmt_infer.h"

#define FMT_INFER_USE_DEFAULT   "use_default"

/* Convenience wrappers */
#define LEN(__a) \
    FMT_SPEC_LEN_ ## __a
#define TYPE_TABLE_MAP(__a, __name) \
    FMT_SPEC_TYPE_ ## __a, __name
#define LEN2NAME_MAP(__len, __name) \
    {                               \
        LEN(__len),                 \
        __name,                     \
    }

/** Internal structure for length -> name mapping */
typedef struct subtype_elem
{
    fmt_spec_len len;
    const char  *str;
} subtype_elem;

/** Internal structure for type -> len and type -> name mapping */
typedef struct type_elem
{
    fmt_spec_type type;
    const char   *str;
    subtype_elem *table;
} type_elem;

static subtype_elem table_d[] = {
    LEN2NAME_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
    LEN2NAME_MAP(h, "short int"),
    LEN2NAME_MAP(hh, "char"),
    LEN2NAME_MAP(l, "long int"),
    LEN2NAME_MAP(ll, "long long int"),
    LEN2NAME_MAP(L, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(z, "size_t"),
    LEN2NAME_MAP(j, "intmax_t"),
    LEN2NAME_MAP(t, "ptrdiff_t"),
};

static subtype_elem table_u[] = {
    LEN2NAME_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
    LEN2NAME_MAP(h, "unsigned short int"),
    LEN2NAME_MAP(hh, "unsigned char"),
    LEN2NAME_MAP(l, "unsigned long int"),
    LEN2NAME_MAP(ll, "unsigned long long int"),
    LEN2NAME_MAP(L, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(z, "size_t"),
    LEN2NAME_MAP(j, "uintmax_t"),
    LEN2NAME_MAP(t, "ptrdiff_t"),
};

static subtype_elem table_f[] = {
    LEN2NAME_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
    LEN2NAME_MAP(h, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(hh, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(l, "double"),
    LEN2NAME_MAP(ll, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(L, "long double"),
    LEN2NAME_MAP(z, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(j, "uintmax_t"),
    LEN2NAME_MAP(t, "ptrdiff_t"),
};

static subtype_elem table_s[] = {
    LEN2NAME_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
    LEN2NAME_MAP(h, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(hh, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(l, "wchar_t *"),
    LEN2NAME_MAP(ll, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(L, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(z, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(j, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(t, FMT_INFER_BAD_TYPE),
};

static subtype_elem table_c_p[] = {
    LEN2NAME_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
    LEN2NAME_MAP(h, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(hh, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(l, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(ll, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(L, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(z, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(j, FMT_INFER_BAD_TYPE),
    LEN2NAME_MAP(t, FMT_INFER_BAD_TYPE),
};

static type_elem type_table[] = {
    {
        TYPE_TABLE_MAP(UNKNOWN, FMT_INFER_USE_DEFAULT),
        NULL,
    },
    {
        TYPE_TABLE_MAP(d, "int"),
        table_d,
    },
    {
        TYPE_TABLE_MAP(i, "int"),
        table_d,
    },
    {
        TYPE_TABLE_MAP(u, "unsigned int"),
        table_u,
    },
    {
        TYPE_TABLE_MAP(f, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(F, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(e, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(E, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(g, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(G, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(x, "unsigned int"),
        table_u,
    },
    {
        TYPE_TABLE_MAP(X, "unsigned int"),
        table_u,
    },
    {
        TYPE_TABLE_MAP(o, "unsigned int"),
        table_u,
    },
    {
        TYPE_TABLE_MAP(s, "char *"),
        table_s,
    },
    {
        TYPE_TABLE_MAP(c, "char"),
        table_c_p,
    },
    {
        TYPE_TABLE_MAP(p, "void *"),
        table_c_p,
    },
    {
        TYPE_TABLE_MAP(a, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(p, "double"),
        table_f,
    },
    {
        TYPE_TABLE_MAP(n, FMT_INFER_USE_DEFAULT),
        NULL,
    },
};

/* See the description in fmt_infer.h */
const char *
fmt_infer_pattern_type_c(fmt_spec *spec)
{
    type_elem    *el;
    subtype_elem *sub;
    const char   *str;

    if ((size_t)spec->type >= sizeof(type_table) / sizeof(*type_table))
        return NULL;

    el = &type_table[(size_t)spec->type];
    if (el == NULL || el->str == NULL || el->str == FMT_INFER_USE_DEFAULT ||
        el->table == NULL)
    {
        return NULL;
    }

    sub = &el->table[(size_t)spec->len];
    if (sub == NULL)
        return NULL;

    str = sub->str;
    if (str == FMT_INFER_USE_DEFAULT)
        str = el->str;
    if (str == FMT_INFER_USE_DEFAULT)
        str = NULL;

    return str;
}
