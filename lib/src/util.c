/**
 * @file
 * @brief fmtparser utility API implementation
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#include "fmt_parser.h"
#include "fmt_util.h"
#include <inttypes.h>

/* See the description in fmt_util.h */
const char *
fmt_spec_len2str(fmt_spec_len len)
{
	switch (len)
	{
#define FMT_SPEC_LEN_VALUE(__name) 											\
		case (FMT_SPEC_LEN_ ## __name):										\
		{																	\
			return #__name;													\
		}

#include "fmt_vals.def"

		default:
		{
			return "Unknown";
		}
	}
}

/* See the description in fmt_util.h */
const char *
fmt_spec_type2str(fmt_spec_type type)
{
	switch (type)
	{
#define FMT_SPEC_TYPE_VALUE(__name) 										\
		case (FMT_SPEC_TYPE_ ## __name):									\
		{																	\
			return #__name;													\
		}

#include "fmt_vals.def"

		default:
		{
			return "Unknown";
		}
	}
}

static void
print_str_from_to(const char *start, const char *end, FILE *f)
{
	const char *ptr;

	fputc('\'', f);
	for (ptr = start; ptr != end; ++ptr)
	{
		fputc(*ptr, f);
	}
	fputc('\'', f);
}

/* See the description in fmt_util.h */
fmt_status
fmt_spec_print(fmt_spec *spec, FILE *f)
{
	int 		retval;
	fmt_bool 	write_one = FMT_FALSE;

#define TRY_PRINTF(...)														\
	{																		\
		if (write_one)														\
			fprintf(f, ", ");												\
		retval = fprintf(f, __VA_ARGS__);									\
		if (retval < 0)														\
		{																	\
			break;															\
		}																	\
		else																\
		{																	\
			write_one = FMT_TRUE;											\
		}																	\
	}

	if (spec == NULL || f == NULL)
	{
		return FMT_EINVAL;
	}

	switch (spec->kind)
	{
		case FMT_SPEC_KIND_STRING:
		{
			TRY_PRINTF("string of len %" PRIuPTR ": ",
					   spec->str_end - spec->str_start);
			break;
		}
		case FMT_SPEC_KIND_PATTERN:
		{
			if (spec->parameter != -1)
			{
				TRY_PRINTF("parameter %d", spec->parameter);
			}
			if (spec->flags.left_align)
			{
				TRY_PRINTF("left align");
			}
			if (spec->flags.prepend_plus)
			{
				TRY_PRINTF("prepend plus");
			}
			if (spec->flags.prepend_space)
			{
				TRY_PRINTF("prepend space");
			}
			if (spec->flags.prepend_zero)
			{
				TRY_PRINTF("prepend zeros");
			}
			if (spec->flags.thousands_grouping)
			{
				TRY_PRINTF("thousands grouping");
			}
			if (spec->flags.alternate)
			{
				TRY_PRINTF("alternate form");
			}
			if (spec->width > 0)
			{
				TRY_PRINTF("width %d", spec->width);
			}
			else if (spec->width == FMT_VALUE_OUT_OF_LINE)
			{
				TRY_PRINTF("width out-of-line");
			}
			if (spec->precision > 0)
			{
				TRY_PRINTF("precision %d", spec->precision);
			}
			else if (spec->precision == FMT_VALUE_OUT_OF_LINE)
			{
				TRY_PRINTF("precision out-of-line");
			}
			if (spec->len != FMT_SPEC_LEN_UNKNOWN)
			{
				TRY_PRINTF("len %s", fmt_spec_len2str(spec->len));
			}
			if (spec->type != FMT_SPEC_TYPE_UNKNOWN)
			{
				TRY_PRINTF("type %s", fmt_spec_type2str(spec->type));
			}
			if (sizeof(fmt_char) == sizeof(char))
			{
				TRY_PRINTF("text: ");
			}
			break;
		}
	}

	print_str_from_to(spec->str_start, spec->str_end, f);

#undef TRY_PRINTF

	return FMT_EOK;
}
