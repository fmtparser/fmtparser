#include "fmt_parser.h"
#include "fmt_util.h"
#include <stdio.h>
#include "gtest/gtest.h"

int test()
{
    char       input[1024];
    const char *tmp = input;
    fmt_spec    spec;
    fmt_status  status;

    fgets(input, sizeof(input), stdin);

    printf("INPUT: %s\n", input);

    fmt_spec_init(&spec);

    while (fmt_read_is_ok(status = fmt_read_one(&tmp, &spec)))
    {
        printf("Segment: ");
        fmt_spec_print(&spec, stdout);
        printf("\n");
        fmt_spec_init(&spec);
    }

    return (status == FMT_EEOL || status == FMT_EOK) ? 0 : 1;
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
