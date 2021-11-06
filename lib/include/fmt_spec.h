/**
 * @file
 * @brief Specifier definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_H
#define FMT_SPEC_H

#include <inttypes.h>

#include "fmt_bool.h"
#include "fmt_spec_kind.h"
#include "fmt_spec_len.h"
#include "fmt_spec_type.h"

#ifndef FMT_CHAR_TYPE
/** Externally-defined char type */
#define FMT_CHAR_TYPE char
#define FMT_CHAR_TYPE_DEFAULT
#endif

#ifndef FMT_CHAR_CONV
/** Converter from regular char to used-defined type */
#define FMT_CHAR_CONV(__chr) ((fmt_char)(__chr))
#endif

#define FMT_VALUE_OUT_OF_LINE (-1)

/**
 * The default char type used in the parser
 */
typedef FMT_CHAR_TYPE fmt_char;

/** Format specifier segment. It may mean a string or a %-something mask */
typedef struct fmt_spec
{
    uint32_t kind; /**< Specifier kind belonging to
                        @p fmt_spec_kind type */
    const fmt_char *str_start; /**< Pointer to start position in
                                    format string */
    const fmt_char *str_end; /**< Pointer to end position in
                                  format string */
    uint32_t parameter; /**< Parameter number */
    struct
    {
        fmt_bool left_align : 1; /**< Left alignment, set by minus */
        fmt_bool prepend_plus : 1; /**< Prepend plus, set by plus */
        fmt_bool prepend_space : 1; /**< Prepend spaces, set by space */
        fmt_bool prepend_zero : 1; /**< Prepend zeros, set by zero */
        fmt_bool thousands_grouping : 1; /**< Thousands grouping, set by
                                              apostrophe */
        fmt_bool alternate : 1; /**< Alternate form, set by hash */
    } flags;
    uint32_t width; /**< A numeric width, or a
                         @c FMT_VALUE_OUT_OF_LINE if it is
                         provided as a separate parameter */
    uint32_t precision; /**< A numeric precision, or a
                             @c FMT_VALUE_OUT_OF_LINE if it is
                             provided as a separate parameter */
    uint32_t len; /**< Length specifier belonging to
                       @p fmt_spec_len type */
    uint32_t type; /**< Type specifier belonging to
                        @p fmt_spec_type type */
} fmt_spec;

#endif
