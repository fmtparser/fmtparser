#ifndef FMT_READER_H
#define FMT_READER_H

#define FMT_START_SYMBOL ('%')

/* Internal boolean type */
typedef enum fmt_bool
{
    FMT_FALSE = 0,
    FMT_TRUE,
} fmt_bool;

typedef enum fmt_status
{
    FMT_EOK,
    FMT_EEOL,
    FMT_EFAIL,
    FMT_ESTATE,
    FMT_EINVAL,
    FMT_ENOMEM,
} fmt_status;

typedef enum fmt_specifier_kind
{
    FMT_SPEC_KIND_UNKNOWN,
    FMT_SPEC_KIND_STRING,
    FMT_SPEC_KIND_PATTERN,
} fmt_specifier_kind;

typedef enum fmt_specifier_len
{
    /* See possible values in fmt_vals.def */
#define FMT_SPEC_LEN_VALUE(__name) FMT_SPEC_LEN_ ## __name,
#include "fmt_vals.def"
} fmt_specifier_len;

typedef enum fmt_specifier_type
{
    /* See possible values in fmt_vals.def */
#define FMT_SPEC_TYPE_VALUE(__name) FMT_SPEC_TYPE_ ## __name,
#include "fmt_vals.def"
} fmt_specifier_type;

typedef struct fmt_specifier
{
    fmt_specifier_kind kind;
    fmt_specifier_type type;
    const char *str_start;
    const char *str_end;

    int parameter;

    struct
    {
        fmt_bool minus:1;
        fmt_bool plus:1;
        fmt_bool space:1;
        fmt_bool zero:1;
        fmt_bool apostrophe:1;
        fmt_bool hash:1;
    } flags;

    fmt_bool width:1;
    fmt_bool precision:1;

    fmt_specifier_len len;

} fmt_specifier;

extern void fmt_spec_init(fmt_specifier *spec);
extern fmt_status fmt_read_one(const char **fmt, fmt_specifier *spec);

extern fmt_bool fmt_read_is_ok(fmt_status status);

#endif