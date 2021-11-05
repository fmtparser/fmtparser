#ifndef FMT_SPEC_TYPE_H
#define FMT_SPEC_TYPE_H

/** Specifier types */
typedef enum fmt_spec_type
{
    /* See possible values in fmt_vals.def */
#define FMT_SPEC_TYPE_VALUE(__name) FMT_SPEC_TYPE_ ## __name,
#include "fmt_vals.def"
} fmt_spec_type;

#endif
