#ifndef FMT_SPEC_H
#define FMT_SPEC_H

#include "fmt_bool.h"
#include "fmt_spec_kind.h"
#include "fmt_spec_len.h"
#include "fmt_spec_type.h"

typedef struct fmt_spec
{
    fmt_spec_kind kind;
    fmt_spec_type type;
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

    fmt_spec_len len;

} fmt_spec;

#endif
