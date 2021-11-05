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

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
