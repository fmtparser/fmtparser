#ifndef FMT_STATUS_H
#define FMT_STATUS_H

typedef enum fmt_status
{
    FMT_EOK,
    FMT_EEOL,
    FMT_EFAIL,
    FMT_ESTATE,
    FMT_EINVAL,
    FMT_ENOMEM,
} fmt_status;

#endif