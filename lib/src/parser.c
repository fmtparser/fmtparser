/**
 * @file
 * @brief fmtparser main API implementation
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#include "fmt_parser.h"
#include <string.h>
#include <stdio.h>
#include "parser_internal.h"
#include "util_internal.h"
#include "debug_internal.h"

/* Read parameter value */
static fmt_status
fmt_read_parameter(const char **fmt, fmt_spec *spec)
{
    int num = 0;
    const char *old_fmt = *fmt;

    while (**fmt)
    {
        const char c = **fmt;

        if (c >= '0' && c <= '9')
        {
            num = num * 10 + (c - '0');
        }
        else if (c == '$')
        {
            /* The last symbol in series - ending it gracefully */
            spec->parameter = num;
            INC_FMT();
            return FMT_EOK;
        }
        else
        {
            break;
        }
        INC_FMT();
    }

    *fmt = old_fmt;

    return FMT_ESTATE;
}

/* Read flags */
static fmt_status
fmt_read_flags(const char **fmt, fmt_spec *spec)
{
    int      num = 0;
    fmt_bool found = FMT_FALSE;

    while (**fmt)
    {
        const char c = **fmt;
        fmt_bool   stop = FMT_FALSE;

        switch (c)
        {
            case '-':
                spec->flags.left_align = FMT_TRUE;
                found = FMT_TRUE;
                break;
            case '+':
                spec->flags.prepend_plus = 1;
                found = FMT_TRUE;
                break;
            case ' ':
                spec->flags.prepend_space = 1;
                found = FMT_TRUE;
                break;
            case '0':
                spec->flags.prepend_zero = 1;
                found = FMT_TRUE;
                break;
            case '\'':
                spec->flags.thousands_grouping = 1;
                found = FMT_TRUE;
                break;
            case '#':
                spec->flags.alternate = 1;
                found = FMT_TRUE;
                break;
            default:
                stop = FMT_TRUE;
                break;
        }

        if (stop)
            break;

        INC_FMT();
    }

    if (!found)
        return FMT_ESTATE;

    return FMT_EOK;
}

/* Read width */
static fmt_status
fmt_read_width(const char **fmt, fmt_spec *spec)
{
    int      width = 0;
    fmt_bool found = FMT_FALSE;

    while (**fmt)
    {
        const char c = **fmt;

        if (c >= '0' && c <= '9')
        {
            width = width * 10 + (c - '0');
            found = FMT_TRUE;
        }
        else if (c == '*')
        {
            width = FMT_VALUE_OUT_OF_LINE;
            found = FMT_TRUE;
            INC_FMT();
            break;
        }
        else
        {
            break;
        }
        INC_FMT();
    }

    if (!found)
        return FMT_ESTATE;

    spec->width = width;

    return FMT_EOK;
}

/* Read precision */
static fmt_status
fmt_read_precision(const char **fmt, fmt_spec *spec)
{
    int precision = 0;

    if (**fmt != '.')
        return FMT_ESTATE;

    while (**fmt)
    {
        const char c = **fmt;

        if (c >= '0' && c <= '9')
        {
            precision = precision * 10 + (c - '0');
        }
        else if (c == '*')
        {
            precision = FMT_VALUE_OUT_OF_LINE;
            INC_FMT();
            break;
        }
        else
        {
            break;
        }
        INC_FMT();
    }

    spec->precision = precision;

    return FMT_EOK;
}

/* Read length */
static fmt_status
fmt_read_length(const char **fmt, fmt_spec *spec)
{
    int width = 0;

    while (**fmt)
    {
        char     c = **fmt;
        fmt_bool stop = FMT_FALSE;

        switch (c)
        {
#define CASE_DOUBLE(_char, _projected_type1, _projected_type2)              \
            case (_char):                                                   \
            {                                                               \
                if (spec->len == (_projected_type1))                        \
                {                                                           \
                    spec->len = (_projected_type2);                         \
                }                                                           \
                else if (spec->len == FMT_SPEC_LEN_UNKNOWN)                 \
                {                                                           \
                    spec->len = (_projected_type1);                         \
                }                                                           \
                else                                                        \
                {                                                           \
                    stop = FMT_TRUE;                                        \
                }                                                           \
                break;                                                      \
            }
#define CASE_SINGLE(_char, _projected_type1)                                \
            case (_char):                                                   \
            {                                                               \
                if (spec->len == FMT_SPEC_LEN_UNKNOWN)                      \
                {                                                           \
                    spec->len = (_projected_type1);                         \
                }                                                           \
                else                                                        \
                {                                                           \
                    stop = FMT_TRUE;                                        \
                }                                                           \
                break;                                                      \
            }

            CASE_DOUBLE('h', FMT_SPEC_LEN_h, FMT_SPEC_LEN_hh);
            CASE_DOUBLE('l', FMT_SPEC_LEN_l, FMT_SPEC_LEN_ll);
            CASE_SINGLE('L', FMT_SPEC_LEN_L);
            CASE_SINGLE('z', FMT_SPEC_LEN_z);
            CASE_SINGLE('j', FMT_SPEC_LEN_j);
            CASE_SINGLE('t', FMT_SPEC_LEN_t);
            default:
                stop = FMT_TRUE;
                break;

#undef CASE_SINGLE
#undef CASE_DOUBLE
        }
        if (stop)
            break;
        INC_FMT();
    }

    if (spec->len == FMT_SPEC_LEN_UNKNOWN)
        return FMT_ESTATE;

    return FMT_EOK;
}

/* Read type */
static fmt_status
fmt_read_type(const char **fmt, fmt_spec *spec)
{
    while (**fmt)
    {
        const char  c = **fmt;
        fmt_bool    stop = FMT_FALSE;

        switch (c)
        {
#define CASE_SINGULAR(_char, _projected_type) \
            case (_char):                                                   \
            {                                                               \
                if (spec->type == FMT_SPEC_TYPE_UNKNOWN)                    \
                {                                                           \
                    spec->type = (_projected_type);                         \
                }                                                           \
                else                                                        \
                {                                                           \
                    stop = FMT_TRUE;                                        \
                }                                                           \
                break;                                                      \
            }
            CASE_SINGULAR('%', FMT_SPEC_TYPE_PERCENT);
            CASE_SINGULAR('d', FMT_SPEC_TYPE_d);
            CASE_SINGULAR('i', FMT_SPEC_TYPE_i);
            CASE_SINGULAR('u', FMT_SPEC_TYPE_u);
            CASE_SINGULAR('f', FMT_SPEC_TYPE_f);
            CASE_SINGULAR('F', FMT_SPEC_TYPE_F);
            CASE_SINGULAR('e', FMT_SPEC_TYPE_e);
            CASE_SINGULAR('E', FMT_SPEC_TYPE_E);
            CASE_SINGULAR('g', FMT_SPEC_TYPE_g);
            CASE_SINGULAR('G', FMT_SPEC_TYPE_G);
            CASE_SINGULAR('x', FMT_SPEC_TYPE_x);
            CASE_SINGULAR('X', FMT_SPEC_TYPE_X);
            CASE_SINGULAR('o', FMT_SPEC_TYPE_o);
            CASE_SINGULAR('s', FMT_SPEC_TYPE_s);
            CASE_SINGULAR('c', FMT_SPEC_TYPE_c);
            CASE_SINGULAR('p', FMT_SPEC_TYPE_p);
            CASE_SINGULAR('a', FMT_SPEC_TYPE_a);
            CASE_SINGULAR('A', FMT_SPEC_TYPE_A);
            CASE_SINGULAR('n', FMT_SPEC_TYPE_n);

#undef CASE_SINGULAR
            default:
                stop = FMT_TRUE;
                break;
        }

        if (stop)
            break;
        INC_FMT();
    }

    if (spec->type == FMT_SPEC_TYPE_UNKNOWN)
        return FMT_EFAIL;

    return FMT_EOK;
}

/* See the description in fmt_parser.h */
fmt_status
fmt_read_one(const char **fmt, fmt_spec *spec)
{
    if (fmt == NULL || spec == NULL)
        return FMT_EINVAL;

#ifdef FMT_DEBUG
    DBG("Start with %s", *fmt);
#endif

    if (**fmt == '\0')
        return FMT_EEOL;

    if (**fmt == FMT_START_SYMBOL)
    {
        spec->kind = FMT_SPEC_KIND_PATTERN;
    }
    else
    {
        spec->kind = FMT_SPEC_KIND_STRING;
    }

    spec->str_start = *fmt;

    INC_FMT();

    switch (spec->kind)
    {
        case FMT_SPEC_KIND_PATTERN:
        {
#define FMT_READ(_func_call)                                                \
            do {                                                            \
                fmt_status status;                                          \
                const char **old_fmt = fmt;                                 \
                                                                            \
                DBG("before %s: %s", #_func_call, *fmt);                    \
                status = _func_call(fmt, spec);                             \
                DBG("after %s: %s", #_func_call, *fmt);                     \
                if (status == FMT_ESTATE)                                   \
                {                                                           \
                    DBG("%s is missing", #_func_call);                      \
                    fmt = old_fmt;                                          \
                }                                                           \
                else if (status != FMT_EOK)                                 \
                {                                                           \
                    DBG("%s: Error at %s", #_func_call, *fmt);              \
                    return status;                                          \
                }                                                           \
                else                                                        \
                {                                                           \
                    DBG("%s: OK", #_func_call);                             \
                }                                                           \
            } while (0)

            FMT_READ(fmt_read_parameter);
            FMT_READ(fmt_read_flags);
            FMT_READ(fmt_read_width);
            FMT_READ(fmt_read_precision);
            FMT_READ(fmt_read_length);
            FMT_READ(fmt_read_type);
#undef FMT_READ

            break;
        }
        case FMT_SPEC_KIND_STRING:
        {
            while (**fmt)
            {
                if (**fmt == FMT_START_SYMBOL)
                    break;
                INC_FMT();
            }
            break;
        }
    }

    spec->str_end = *fmt;

    return FMT_EOK;
}

/* See the description in fmt_parser.h */
void
fmt_spec_init(fmt_spec *spec)
{
    memset(spec, 0, sizeof(fmt_spec));
    spec->parameter = -1;
}

/* See the description in fmt_parser.h */
fmt_bool
fmt_read_is_ok(fmt_status status)
{
    return status == FMT_EOK || status == FMT_ESTATE;
}