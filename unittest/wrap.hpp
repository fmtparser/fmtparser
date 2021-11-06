#pragma once
#include "fmt_parser.h"
#include "fmt_util.h"

typedef enum
{
    left_align = 1,
    prepend_plus = 2,
    prepend_space = 4,
    prepend_zero = 8,
    thousands_grouping = 16,
    alternate = 32,
} flags;

static inline fmt_status
fmt_init_read(const fmt_char **fmt, fmt_spec *spec)
{
    fmt_spec_init(spec);

    return fmt_read_one(fmt, spec);
}

#define EXPECT_STRING() ASSERT_EQ(spec.kind, FMT_SPEC_KIND_STRING)
#define EXPECT_PATTERN() ASSERT_EQ(spec.kind, FMT_SPEC_KIND_PATTERN)

#define EXPECT_STR(__str) \
    ASSERT_EQ(memcmp(spec.str_start, __str, spec.str_end - spec.str_start), 0)
#define EXPECT_STR_LEN(__len) ASSERT_EQ(spec.str_end - spec.str_start, __len)

#define EXPECT_PARAM(__num) ASSERT_EQ(spec.parameter, __num)

#define EXPECT_FLAGS(__flags)                                             \
    do                                                                    \
    {                                                                     \
        ASSERT_EQ(spec.flags.left_align,                                  \
                  (__flags & left_align) ? FMT_TRUE : FMT_FALSE);         \
        ASSERT_EQ(spec.flags.prepend_plus,                                \
                  (__flags & prepend_plus) ? FMT_TRUE : FMT_FALSE);       \
        ASSERT_EQ(spec.flags.prepend_space,                               \
                  (__flags & prepend_space) ? FMT_TRUE : FMT_FALSE);      \
        ASSERT_EQ(spec.flags.prepend_zero,                                \
                  (__flags & prepend_zero) ? FMT_TRUE : FMT_FALSE);       \
        ASSERT_EQ(spec.flags.thousands_grouping,                          \
                  (__flags & thousands_grouping) ? FMT_TRUE : FMT_FALSE); \
        ASSERT_EQ(spec.flags.alternate,                                   \
                  (__flags & alternate) ? FMT_TRUE : FMT_FALSE);          \
    } while (0)

#define EXPECT_WIDTH(__val) ASSERT_EQ(spec.width, (__val))
#define EXPECT_WIDTH_OOL() ASSERT_EQ(spec.width, FMT_VALUE_OUT_OF_LINE)
#define EXPECT_PRECISION(__val) ASSERT_EQ(spec.precision, (__val))
#define EXPECT_PRECISION_OOL() ASSERT_EQ(spec.precision, FMT_VALUE_OUT_OF_LINE)
#define EXPECT_LEN(__name) ASSERT_EQ(spec.len, FMT_SPEC_LEN_##__name)
#define EXPECT_TYPE(__name) ASSERT_EQ(spec.type, FMT_SPEC_TYPE_##__name)
