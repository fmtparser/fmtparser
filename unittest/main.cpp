#include "fmt_parser.h"
#include "fmt_util.h"
#include "gtest/gtest.h"
#include "wrap.hpp"

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

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
