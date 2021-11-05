/**
 * @file
 * @brief Format specifier kind definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_SPEC_KIND_H
#define FMT_SPEC_KIND_H

/** Specifier kind */
typedef enum fmt_spec_kind
{
    FMT_SPEC_KIND_UNKNOWN = 0,      /**< Unknown specifier kind */
    FMT_SPEC_KIND_STRING,           /**< A string in between masks */
    FMT_SPEC_KIND_PATTERN,          /**< printf-mask */
} fmt_spec_kind;

#endif