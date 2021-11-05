#include "fmt_parser.h"
#include "fmt_util.h"
#include <stdio.h>

int main()
{
	char 		input[1024];
	const char *tmp = input;
	fmt_spec 	spec;

	fgets(input, sizeof(input), stdin);

	printf("INPUT: %s\n", input);

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