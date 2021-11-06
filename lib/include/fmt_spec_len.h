/**
 * @file
 * @brief Format length specifier definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_LEN_H
#define FMT_SPEC_LEN_H

/** Specifier lengths */
typedef enum fmt_spec_len
{
/* See possible values in fmt_vals.def */
#define FMT_SPEC_LEN_VALUE(__name) FMT_SPEC_LEN_##__name,
#include "fmt_vals.def"
} fmt_spec_len;

#endif
