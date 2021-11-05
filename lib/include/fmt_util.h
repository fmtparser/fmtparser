#ifndef FMT_UTIL_H
#define FMT_UTIL_H

#include "fmt_parser.h"
#include <stdio.h>

extern fmt_status fmt_spec_print(fmt_specifier *spec, FILE *f);

extern const char *fmt_spec_len2str(fmt_specifier_len len);

#endif