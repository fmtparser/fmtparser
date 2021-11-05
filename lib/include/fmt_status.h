/**
 * @file
 * @brief Status code definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_STATUS_H
#define FMT_STATUS_H

/** Status codes */
typedef enum fmt_status
{
    FMT_EOK,    /**< No error */
    FMT_EEOL,   /**< End-of-line error */
    FMT_EFAIL,  /**< Other error */
    FMT_ESTATE, /**< Invalid state. Mostly it means there is no part that is
                     about to be read*/
    FMT_EINVAL, /**< Invalid parameter */
} fmt_status;

#endif