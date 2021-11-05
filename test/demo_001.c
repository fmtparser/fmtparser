#include "fmt_parser.h"
#include "fmt_util.h"
#include <stdio.h>

int main()
{
	char 	   *fmt = "Hello, %157$02ld test %*s world!";
	const char *tmp = fmt;

	fmt_specifier spec;

	printf("%s\n", fmt);

	fmt_spec_init(&spec);

	while (fmt_read_is_ok(fmt_read_one(&tmp, &spec)))
	{
		printf("Segment: ");
		fmt_spec_print(&spec, stdout);
		printf("\n");
		fmt_spec_init(&spec);
	}
	return 0;
}