#ifndef FMT_SPEC_H
#define FMT_SPEC_H

#include "fmt_bool.h"
#include "fmt_spec_kind.h"
#include "fmt_spec_len.h"
#include "fmt_spec_type.h"

typedef struct fmt_spec
{
    fmt_spec_kind kind;                 /**< Specifier kind */
    const char   *str_start;            /**< Pointer to start position in
                                             format string */
    const char   *str_end;              /**< Pointer to end position in
                                             format string */

    int           parameter;            /**< Parameter number */

    struct
    {
        fmt_bool left_align:1;          /**< Left alignment, set by minus */
        fmt_bool prepend_plus:1;        /**< Prepend plus, set by plus */
        fmt_bool prepend_space:1;       /**< Prepend spaces, set by space */
        fmt_bool prepend_zero:1;        /**< Prepend zeros, set by zero */
        fmt_bool thousands_grouping:1;  /**< Thousands grouping, set by
                                             apostrophe */
        fmt_bool alternate:1;           /**< Alternate form, set by hash */
    } flags;

    fmt_bool width:1;                   /**< Width is provided as a separate
                                             parameter */
    fmt_bool precision:1;               /**< Precision is provided as a separate
                                             parameter */

    fmt_spec_len len;                   /**< Length specifier */
    fmt_spec_type type;                 /**< Type specifier */

} fmt_spec;

#endif
