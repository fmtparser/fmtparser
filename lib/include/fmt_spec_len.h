/**
 * @file
 * @brief Format length specifier definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_LEN_H
#define FMT_SPEC_LEN_H

/**
 * @addtogroup fmt_spec_len Length specifier
 * @ingroup fmt_spec_fields
 * Length of a typed parameter
 * @{
 */
/** Specifier lengths */
typedef enum fmt_spec_len
{
/* See possible values in fmt_vals.def */
#define FMT_SPEC_LEN_VALUE(__name) FMT_SPEC_LEN_##__name,
#include "fmt_vals.def"
} fmt_spec_len;

/**
 * @}
 */

#endif
