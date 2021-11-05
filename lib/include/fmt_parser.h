/**
 * @file
 * @brief fmtparser API
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_READER_H
#define FMT_READER_H

#include "fmt_status.h"
#include "fmt_bool.h"
#include "fmt_spec.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize format specifier
 *
 * @param[out] spec  Pointer to specifier
 */
extern void fmt_spec_init(fmt_spec *spec);

/**
 * Read one specifier from the format string
 *
 * @param      fmt   The format string
 * @param[out] spec  Pointer to specifier
 *
 * @return     Status code
 */
extern fmt_status fmt_read_one(const char **fmt, fmt_spec *spec);

/**
 * Check that read is OK and specifier parsing can be continued
 *
 * @param      status  Status code (from @p fmt_read_one())
 *
 * @return     @c FMT_TRUE if read can be continued, @c FMT_FALSE otherwise
 */
extern fmt_bool fmt_read_is_ok(fmt_status status);


#ifdef __cplusplus
}
#endif

#endif