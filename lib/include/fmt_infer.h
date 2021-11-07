/**
 * @file
 * @brief fmtparser inference API
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_INFER_H
#define FMT_INFER_H

#include "fmt_bool.h"
#include "fmt_spec.h"
#include "fmt_status.h"

#define FMT_INFER_BAD_TYPE "bad_type"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     *  @addtogroup fmt_infer Inference API
     *  Functions to guess a real C type
     *  @{
     */

    /**
     * Guess C type from specifier
     *
     * @param      spec  The specifier
     *
     * @return     Target type string, e.g. "unsigned int".
     */
    extern const char *fmt_infer_pattern_type_c(fmt_spec *spec);

    /** @} */

#ifdef __cplusplus
}
#endif

#endif
