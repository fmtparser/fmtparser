/**
 * @file
 * @brief fmtparser specifier API
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_READER_H
#define FMT_READER_H

#include "fmt_bool.h"
#include "fmt_spec.h"
#include "fmt_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup fmt_spec_api Parser API
 * @ingroup fmt_spec
 * Main functions to parse specifiers from the string.
 * @{
 */

    /**
     * Allocate specifier and initialize it
     *
     * @return Newly allocated format specifier
     */
    extern fmt_spec *fmt_spec_alloc(void);

    /**
     * Get kind of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Value belonging to @p fmt_spec_kind enumeration
     */
    extern uint32_t fmt_spec_get_kind(fmt_spec *spec);

    /**
     * Get parameter of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Parameter value
     * @retval     @c FMT_VALUE_NOT_DEFINED if unspecified
     * @retval     Any other value - actual index of a parameter in printf()
     *             variadic arguments
     */
    extern uint32_t fmt_spec_get_parameter(fmt_spec *spec);

    /**
     * Get width of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Width value
     * @retval     @c FMT_VALUE_NOT_DEFINED if unspecified
     * @retval     @c FMT_VALUE_OUT_OF_LINE if defined in an external parameter
     * @retval     Any other value - the actual width
     */
    extern uint32_t fmt_spec_get_width(fmt_spec *spec);

    /**
     * Get precision of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Precision value
     * @retval     @c FMT_VALUE_NOT_DEFINED if unspecified
     * @retval     @c FMT_VALUE_OUT_OF_LINE if defined in an external parameter
     * @retval     Any other value - the actual precision
     */
    extern uint32_t fmt_spec_get_precision(fmt_spec *spec);

    /**
     * Get length modifier of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Length modifier
     * @retval     @c FMT_VALUE_OUT_OF_LINE if defined in an external parameter
     * @retval     Any other value - the actual length defined in
     *             @p fmt_spec_len enumeration
     */
    extern uint32_t fmt_spec_get_length(fmt_spec *spec);

    /**
     * Get type of a specifier
     *
     * @param      spec  The specifier
     *
     * @return     Actual type in terms of @p fmt_spec_type enumeration
     */
    extern uint32_t fmt_spec_get_type(fmt_spec *spec);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
