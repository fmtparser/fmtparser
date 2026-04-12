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
#include "fmt_infer.h"
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

/* FIXME: add more inference tests */
TEST(infer, lf)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_f;
    spec.len = FMT_SPEC_LEN_l;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "double"), 0);

    spec.type = FMT_SPEC_TYPE_f;
    spec.len = FMT_SPEC_LEN_L;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "long double"), 0);

    spec.type = FMT_SPEC_TYPE_f;
    spec.len = FMT_SPEC_LEN_ll;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "bad_type"), 0);
}

TEST(infer, x)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_x;
    spec.len = FMT_SPEC_LEN_l;

    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "unsigned long int"), 0);

    spec.type = FMT_SPEC_TYPE_x;
    spec.len = FMT_SPEC_LEN_ll;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "unsigned long long int"),
              0);

    spec.type = FMT_SPEC_TYPE_x;
    spec.len = FMT_SPEC_LEN_hh;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "unsigned char"),
              0);

    spec.type = FMT_SPEC_TYPE_x;
    spec.len = FMT_SPEC_LEN_h;
    ASSERT_EQ(strcmp(fmt_infer_pattern_type_c(&spec), "unsigned short int"),
              0);
}

TEST(infer, s)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_s;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "char *");
}

TEST(infer, c)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_c;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "char");
}

TEST(infer, c_full)
{
    fmt_status  rc;
    fmt_spec    spec;
    const char *s = "%c";

    fmt_spec_init(&spec);
    rc = fmt_read_one(&s, &spec);
    ASSERT_EQ(rc, FMT_EOK);
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec),
                 "char");
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

/* Additional comprehensive tests */

TEST(Masks, all_integer_types)
{
    // Test %d
    const char *str_d = "%d";
    fmt_spec spec;
    const char *tmp = str_d;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(d);

    // Test %i
    str_d = "%i";
    tmp = str_d;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(i);

    // Test %u
    str_d = "%u";
    tmp = str_d;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(u);

    // Test %o
    str_d = "%o";
    tmp = str_d;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(o);

    // Test %X (uppercase hex)
    str_d = "%X";
    tmp = str_d;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(X);
}

TEST(Masks, all_float_types)
{
    fmt_spec spec;
    const char *tmp;

    // Test %f
    tmp = "%f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(f);

    // Test %F
    tmp = "%F";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(F);

    // Test %e
    tmp = "%e";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(e);

    // Test %E
    tmp = "%E";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(E);

    // Test %g
    tmp = "%g";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(g);

    // Test %a (hex float)
    tmp = "%a";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(a);
}

TEST(Masks, pointer_and_special)
{
    fmt_spec spec;
    const char *tmp;

    // Test %p (pointer)
    tmp = "%p";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(p);

    // Test %n (written count)
    tmp = "%n";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_TYPE(n);
}

TEST(Masks, all_length_modifiers)
{
    fmt_spec spec;
    const char *tmp;

    // Test %hd (short)
    tmp = "%hd";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(h);
    EXPECT_TYPE(d);

    // Test %hhd (char)
    tmp = "%hhd";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(hh);
    EXPECT_TYPE(d);

    // Test %zd (size_t)
    tmp = "%zd";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(z);
    EXPECT_TYPE(d);

    // Test %jd (intmax_t)
    tmp = "%jd";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(j);
    EXPECT_TYPE(d);

    // Test %td (ptrdiff_t)
    tmp = "%td";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(t);
    EXPECT_TYPE(d);

    // Test %Lf (long double)
    tmp = "%Lf";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_LEN(L);
    EXPECT_TYPE(f);
}

TEST(Masks, combined_flags)
{
    fmt_spec spec;
    const char *tmp;

    // Test %-+d (left align + prepend plus)
    tmp = "%-+d";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS((left_align | prepend_plus));

    // Test %0#x (zero pad + alternate)
    tmp = "%0#x";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS((prepend_zero | alternate));

    // Test %#010x (alternate + zero pad with width)
    tmp = "%#010x";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS((alternate | prepend_zero));
    EXPECT_WIDTH(10);
}

TEST(Masks, width_and_precision)
{
    fmt_spec spec;
    const char *tmp;

    // Test %.5f (precision only)
    tmp = "%.5f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PRECISION(5);
    EXPECT_TYPE(f);

    // Test %10.5f (width and precision)
    tmp = "%10.5f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_WIDTH(10);
    EXPECT_PRECISION(5);
    EXPECT_TYPE(f);

    // Test %*.* (both out of line)
    tmp = "%*.*s";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_WIDTH_OOL();
    EXPECT_PRECISION_OOL();
    EXPECT_TYPE(s);

    // Test %10.*f (width fixed, precision OOL)
    tmp = "%10.*f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_WIDTH(10);
    EXPECT_PRECISION_OOL();
    EXPECT_TYPE(f);
}

TEST(Masks, positional_parameters)
{
    fmt_spec spec;
    const char *tmp;

    // Test %1$d
    tmp = "%1$d";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PARAM(1);
    EXPECT_TYPE(d);

    // Test %42$s
    tmp = "%42$s";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PARAM(42);
    EXPECT_TYPE(s);

    // Test %3$10.5f (with width and precision)
    tmp = "%3$10.5f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PARAM(3);
    EXPECT_WIDTH(10);
    EXPECT_PRECISION(5);
    EXPECT_TYPE(f);
}

TEST(Masks, complex_patterns)
{
    const char *str = "Price: %+10.2f€, Count: %'lld, Name: %-20s";
    fmt_spec spec;
    const char *tmp = str;

    // String before first pattern
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR("Price: ");

    // %+10.2f
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(f);
    EXPECT_FLAGS(prepend_plus);
    EXPECT_WIDTH(10);
    EXPECT_PRECISION(2);

    // String between patterns
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    // %'lld
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(d);
    EXPECT_LEN(ll);
    EXPECT_FLAGS(thousands_grouping);

    // String between patterns
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    // %-20s
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(s);
    EXPECT_FLAGS(left_align);
    EXPECT_WIDTH(20);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, empty_string)
{
    const char *str = "";
    fmt_spec spec;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, only_text)
{
    const char *str = "No format specifiers here!";
    fmt_spec spec;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR("No format specifiers here!");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, consecutive_percents)
{
    const char *str = "%%%%";
    fmt_spec spec;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(PERCENT);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(PERCENT);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, alternate_flag)
{
    fmt_spec spec;
    const char *tmp;

    // Test %#x
    tmp = "%#x";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS(alternate);
    EXPECT_TYPE(x);

    // Test %#o
    tmp = "%#o";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS(alternate);
    EXPECT_TYPE(o);

    // Test %#f
    tmp = "%#f";
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_FLAGS(alternate);
    EXPECT_TYPE(f);
}

TEST(infer, all_integer_types)
{
    fmt_spec spec;
    
    // Test %d
    spec.type = FMT_SPEC_TYPE_d;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "int");

    // Test %hd
    spec.len = FMT_SPEC_LEN_h;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "short int");

    // Test %hhd
    spec.len = FMT_SPEC_LEN_hh;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "char");

    // Test %ld
    spec.len = FMT_SPEC_LEN_l;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "long int");

    // Test %lld
    spec.len = FMT_SPEC_LEN_ll;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "long long int");
}

TEST(infer, unsigned_types)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_u;
    
    // Test %u
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "unsigned int");

    // Test %hu
    spec.len = FMT_SPEC_LEN_h;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "unsigned short int");

    // Test %hhu
    spec.len = FMT_SPEC_LEN_hh;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "unsigned char");

    // Test %lu
    spec.len = FMT_SPEC_LEN_l;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "unsigned long int");

    // Test %llu
    spec.len = FMT_SPEC_LEN_ll;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "unsigned long long int");
}

TEST(infer, float_types)
{
    fmt_spec spec;
    
    // Test %f
    spec.type = FMT_SPEC_TYPE_f;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "double");

    // Test %e
    spec.type = FMT_SPEC_TYPE_e;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "double");

    // Test %g
    spec.type = FMT_SPEC_TYPE_g;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "double");

    // Test %a
    spec.type = FMT_SPEC_TYPE_a;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "double");
}

TEST(infer, size_modifiers)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_d;
    
    // Test %zd
    spec.len = FMT_SPEC_LEN_z;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "size_t");

    // Test %jd
    spec.len = FMT_SPEC_LEN_j;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "intmax_t");

    // Test %td
    spec.len = FMT_SPEC_LEN_t;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "ptrdiff_t");
}

TEST(infer, pointer_type)
{
    fmt_spec spec;
    spec.type = FMT_SPEC_TYPE_p;
    spec.len = FMT_SPEC_LEN_UNKNOWN;
    ASSERT_STREQ(fmt_infer_pattern_type_c(&spec), "void *");
}

TEST(util, spec_len2str)
{
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_UNKNOWN), "UNKNOWN");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_h), "h");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_hh), "hh");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_l), "l");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_ll), "ll");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_L), "L");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_z), "z");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_j), "j");
    ASSERT_STREQ(fmt_spec_len2str(FMT_SPEC_LEN_t), "t");
}

TEST(util, spec_type2str)
{
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_UNKNOWN), "UNKNOWN");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_PERCENT), "PERCENT");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_d), "d");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_i), "i");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_u), "u");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_f), "f");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_F), "F");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_e), "e");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_E), "E");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_g), "g");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_G), "G");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_x), "x");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_X), "X");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_o), "o");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_s), "s");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_c), "c");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_p), "p");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_a), "a");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_A), "A");
    ASSERT_STREQ(fmt_spec_type2str(FMT_SPEC_TYPE_n), "n");
}

TEST(util, read_is_ok)
{
    ASSERT_EQ(fmt_read_is_ok(FMT_EOK), FMT_TRUE);
    ASSERT_EQ(fmt_read_is_ok(FMT_EEOL), FMT_FALSE);
}

TEST(Masks, real_world_examples)
{
    // Example from printf man page
    const char *str = "%.2f";
    fmt_spec spec;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(f);
    EXPECT_PRECISION(2);
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);

    // Common debug format
    str = "%s:%d: %s\n";
    tmp = str;
    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(s);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR(":");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(d);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR(": ");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(s);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();
    EXPECT_STR("\n");

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

TEST(Masks, hex_pointer_format)
{
    const char *str = "Pointer: %p, Hex: 0x%08X";
    fmt_spec spec;
    const char *tmp = str;

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(p);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_STRING();

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EOK);
    EXPECT_PATTERN();
    EXPECT_TYPE(X);
    EXPECT_FLAGS(prepend_zero);
    EXPECT_WIDTH(8);

    ASSERT_EQ(fmt_init_read(&tmp, &spec), FMT_EEOL);
}

#endif

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
