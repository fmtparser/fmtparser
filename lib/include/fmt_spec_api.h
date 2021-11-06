/**
 * @file
 * @brief fmtparser specifier API
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_API_H
#define FMT_SPEC_API_H

#include "fmt_bool.h"
#include "fmt_spec.h"
#include "fmt_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @addtogroup fmt_spec_api Specifier API
     * @ingroup fmt_spec
     * Helper functions for accessing specifiers from other languages
     * @{
     */

    /**
     * Format specifier flag
     */
    typedef enum fmt_flag
    {
        FMT_FLAG_FIRST = 0, /**< The first flag in enumeration */
        FMT_FLAG_LEFT_ALIGN = 0, /**< Left align flag */
        FMT_FLAG_PREPEND_PLUS, /**< Prepend plus flag */
        FMT_FLAG_PREPEND_SPACE, /**< Prepend space flag */
        FMT_FLAG_PREPEND_ZERO, /**< Prepend zero flag */
        FMT_FLAG_THOUSANDS_GROUPING, /**< Enable thousands grouping */
        FMT_FLAG_ALTERNATE, /**< Enable alternate form */
        FMT_FLAG_LAST = FMT_FLAG_ALTERNATE, /**< Last flag */
    } fmt_flag;

    /**
     * Allocate specifier and initialize it
     *
     * @return Newly allocated format specifier
     */
    extern fmt_spec *fmt_spec_alloc(void);

    /**
     * Free allocated specifier
     *
     * @param      spec  Pointer to the specifier
     */
    extern void fmt_spec_free(fmt_spec *spec);

    /**
     * Allocate string buffer for use in @p fmt_parser API
     *
     * @param      str   The string
     *
     * @return     Newly allocated pointer to string
     */
    extern char **fmt_str_alloc(fmt_char *str);

    /**
     * Free string pointer allocated by @p fmt_str_alloc()
     *
     * @param      str_ptr  The string pointer
     */
    extern void fmt_str_free(fmt_char **str_ptr);

    /**
     * Get specifier's start position
     *
     * @param      spec  The specifier
     * @param      str   Original string that was originally passed to the first
     *                   @p fmt_read_one().
     *
     * @return     Position within @p str string
     */
    extern int32_t fmt_spec_get_start_position(fmt_spec *spec, fmt_char **str);

    /**
     * Get specifier's end position
     *
     * @param      spec  The specifier
     * @param      str   Original string that was originally passed to the first
     *                   @p fmt_read_one().
     *
     * @return     End position within @p str string
     */
    extern int32_t fmt_spec_get_end_position(fmt_spec *spec, fmt_char **str);

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

    /**
     * Get flag of a specifier
     *
     * @param      spec  The specifier
     * @param      flag  The flag of @p fmt_flag enumeration
     *
     * @return     @c FMT_TRUE if flag is set, @c FMT_FALSE otherwise
     */
    extern fmt_bool fmt_spec_get_flag(fmt_spec *spec, fmt_flag flag);

    /** @} */

#ifdef __cplusplus
}
#endif

#endif
