/**
 * @file
 * @brief fmtparser utility API
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_UTIL_H
#define FMT_UTIL_H

#include "fmt_status.h"
#include "fmt_spec.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print format specifier
 *
 * @param      spec  The specifier
 * @param      file  File pointer
 *
 * @return Status code
 */
extern fmt_status fmt_spec_print(fmt_spec *spec, FILE *file);

/**
 * Convert length to string
 *
 * @param      len   The length specifier
 *
 * @return     String representation of length
 */
extern const char *fmt_spec_len2str(fmt_spec_len len);

/**
 * Convert type to string
 *
 * @param      type  The type specifier
 *
 * @return     String representation of length
 */
extern const char *fmt_spec_type2str(fmt_spec_type type);


#ifdef __cplusplus
}
#endif

#endif
