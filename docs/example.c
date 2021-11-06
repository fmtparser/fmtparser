#include "fmt_parser.h"
#include "fmt_util.h"
#include <stdio.h>

int main()
{
    fmt_status  rc;
    fmt_spec    spec;
    const char *str = "Hello, %157$02ld test %*s world!";
    const char *tmp = str;

    do
    {
        fmt_spec_init(&spec);
        rc = fmt_read_one(&tmp, &spec);
        if (rc == FMT_EOK)
        {
            fmt_spec_print(&spec, stdout);
            printf("\n");
        }
    } while (fmt_read_is_ok(rc));

    return 0;
}
