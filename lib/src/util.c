#include "fmt_parser.h"
#include "fmt_util.h"
#include <inttypes.h>

const char *
fmt_spec_len2str(fmt_specifier_len len)
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

const char *
fmt_spec_type2str(fmt_specifier_type type)
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

fmt_status
fmt_spec_print(fmt_specifier *spec, FILE *f)
{
	int 		retval;
	fmt_bool 	write_one = FMT_FALSE;

#define TRY_PRINTF(_params...)												\
	{																		\
		if (write_one)														\
			fprintf(f, ", ");												\
		retval = fprintf(f, _params);										\
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
			TRY_PRINTF("string of len %" PRIuPTR,
					   spec->str_end - spec->str_start);
			break;
		}
		case FMT_SPEC_KIND_PATTERN:
		{
			if (spec->parameter != -1)
			{
				TRY_PRINTF("parameter %d", spec->parameter);
			}
			if (spec->flags.minus)
			{
				TRY_PRINTF("left align");
			}
			if (spec->flags.plus)
			{
				TRY_PRINTF("prepend plus");
			}
			if (spec->flags.space)
			{
				TRY_PRINTF("prepend space");
			}
			if (spec->flags.zero)
			{
				TRY_PRINTF("prepend zeros");
			}
			if (spec->flags.apostrophe)
			{
				TRY_PRINTF("thousands grouping");
			}
			if (spec->flags.hash)
			{
				TRY_PRINTF("alternate form");
			}
			if (spec->width)
			{
				TRY_PRINTF("width provided");
			}
			if (spec->precision)
			{
				TRY_PRINTF("precision provided");
			}
			if (spec->len != FMT_SPEC_LEN_UNKNOWN)
			{
				TRY_PRINTF("len %s", fmt_spec_len2str(spec->len));
			}
			if (spec->type != FMT_SPEC_TYPE_UNKNOWN)
			{
				TRY_PRINTF("type %s", fmt_spec_type2str(spec->type));
			}
			break;
		}
	}

	return FMT_EOK;
}