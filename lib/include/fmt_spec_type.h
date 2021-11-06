/**
 * @file
 * @brief Format type specifier definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_TYPE_H
#define FMT_SPEC_TYPE_H

/**
 * @addtogroup fmt_spec_type Specifier type
 * @ingroup fmt_spec_fields
 * The specifier type explicitly assigns a type to a printf() parameter.
 * It can be one of a limited set of options including integer, hex
 * representation, floating point numbers, etc.
 * @{
 */
/** Specifier types */
typedef enum fmt_spec_type
{
/* See possible values in fmt_vals.def */
#define FMT_SPEC_TYPE_VALUE(__name) FMT_SPEC_TYPE_##__name,
#include "fmt_vals.def"
} fmt_spec_type;

/**
 * @}
 */
#endif
