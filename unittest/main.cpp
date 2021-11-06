/**
 * @file
 * fmtparser unit test program
 *
 * It is only effective when char type is not redefined
 *
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#include "gtest/gtest.h"
#include "fmt_parser.h"
#include "fmt_util.h"
#include "wrap.hpp"
#ifdef ENABLE_SPEC_API
#include "fmt_spec_api.h"
#endif

#ifdef FMT_CHAR_TYPE_DEFAULT

TEST(Masks, str_ld_s)
{
    const char *str = "Hello, %157$02ld test %*s world!";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    fmt_spec_init(&spec);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR("Hello, ");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%157$02ld");
    EXPECT_PARAM(157);
    EXPECT_FLAGS(prepend_zero);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR(" test ");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%*s");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR(" world!");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, percent)
{
    const char *str = "Hello, %% world";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR("Hello, ");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%%");
    EXPECT_TYPE(PERCENT);
    EXPECT_FLAGS(0);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR(" world");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, val02x)
{
    const char *str = "%02x";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%02x");
    EXPECT_TYPE(x);
    EXPECT_FLAGS(prepend_zero);
    /* FIXME: width */

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}


TEST(Masks, valld)
{
    const char *str = "%ld";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%ld");
    EXPECT_LEN(l);
    EXPECT_TYPE(d);
    EXPECT_FLAGS(0);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, vallld)
{
    const char *str = "%lld";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%lld");
    EXPECT_LEN(ll);
    EXPECT_TYPE(d);
    EXPECT_FLAGS(0);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}


TEST(Masks, vallli)
{
    const char *str = "%lli";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%lli");
    EXPECT_LEN(ll);
    EXPECT_TYPE(i);
    EXPECT_FLAGS(0);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, valspacex)
{
    const char *str = "% x";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("% x");
    EXPECT_TYPE(x);
    EXPECT_FLAGS(prepend_space);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}


TEST(Masks, valthousandsd)
{
    const char *str = "%'d";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%'d");
    EXPECT_TYPE(d);
    EXPECT_FLAGS(thousands_grouping);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, valleftG)
{
    const char *str = "%-G";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%-G");
    EXPECT_TYPE(G);
    EXPECT_FLAGS(left_align);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, valplusA)
{
    const char *str = "%+A";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%+A");
    EXPECT_TYPE(A);
    EXPECT_FLAGS(prepend_plus);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, valprecisions)
{
    const char *str = "%.*s";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%.*s");
    EXPECT_TYPE(s);
    EXPECT_PRECISION_OOL();

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, valwidths)
{
    const char *str = "%3s";
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%3s");
    EXPECT_TYPE(s);
    EXPECT_WIDTH(3);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(encoding, utf8)
{
    uint8_t     str_u[] = { 0xd0, 0x9f, 0xd1, 0x80, 0xd0, 0xb8, 0xd0, 0xb2,
                        0xd0, 0xb5, 0xd1, 0x82, 0x20, 0x25, 0x73, 0x20,
                        0xd0, 0xbc, 0xd0, 0xb8, 0xd1, 0x80, '\0' };
    fmt_spec    spec;
    fmt_status  status;
    const char *tmp = (const char *)str_u;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_STR("%s");
    EXPECT_TYPE(s);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

#ifdef ENABLE_SPEC_API

static void
fmt_spec_set_flag(fmt_spec *spec, fmt_flag flag, fmt_bool val)
{
    switch (flag)
    {
        case FMT_FLAG_LEFT_ALIGN:
            spec->flags.left_align = val;
            break;
        case FMT_FLAG_PREPEND_PLUS:
            spec->flags.prepend_plus = val;
            break;
        case FMT_FLAG_PREPEND_SPACE:
            spec->flags.prepend_space = val;
            break;
        case FMT_FLAG_PREPEND_ZERO:
            spec->flags.prepend_zero = val;
            break;
        case FMT_FLAG_THOUSANDS_GROUPING:
            spec->flags.thousands_grouping = val;
            break;
        case FMT_FLAG_ALTERNATE:
            spec->flags.alternate = val;
            break;
        default:
            FAIL();
            break;
    }
}

TEST(spec_api, spec)
{
    char *    str = (char *)"hello world!";
    fmt_spec *spec = fmt_spec_alloc();

    spec->str_start = str + 5;
    spec->str_end = str + 6;

    ASSERT_EQ(fmt_spec_get_start_position(spec, &str), 5);
    ASSERT_EQ(fmt_spec_get_end_position(spec, &str), 6);

    spec->kind = FMT_SPEC_KIND_PATTERN;
    ASSERT_EQ(fmt_spec_get_kind(spec), FMT_SPEC_KIND_PATTERN);

    spec->parameter = 157;
    ASSERT_EQ(fmt_spec_get_parameter(spec), 157);

    spec->width = 356;
    ASSERT_EQ(fmt_spec_get_width(spec), 356);

    spec->precision = 467;
    ASSERT_EQ(fmt_spec_get_precision(spec), 467);

    spec->type = FMT_SPEC_TYPE_s;
    ASSERT_EQ(fmt_spec_get_type(spec), FMT_SPEC_TYPE_s);

    spec->flags.left_align = 0;
    spec->flags.prepend_plus = 0;
    spec->flags.prepend_space = 0;
    spec->flags.prepend_zero = 0;
    spec->flags.thousands_grouping = 0;
    spec->flags.alternate = 0;
    for (int i = FMT_FLAG_FIRST; i <= FMT_FLAG_LAST; ++i)
    {
        ASSERT_EQ(fmt_spec_get_flag(spec, (fmt_flag)i), FMT_FALSE);
        fmt_spec_set_flag(spec, (fmt_flag)i, FMT_TRUE);
        ASSERT_EQ(fmt_spec_get_flag(spec, (fmt_flag)i), FMT_TRUE);
        fmt_spec_set_flag(spec, (fmt_flag)i, FMT_FALSE);
    }


    fmt_spec_free(spec);
}

TEST(spec_api, str)
{
    fmt_char **s = fmt_str_alloc((char *)"test");

    ASSERT_EQ(strcmp(*s, "test"), 0);
    fmt_str_free(s);
}
#endif

#endif

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
