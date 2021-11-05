#ifndef FMT_DEBUG_H

#ifdef FMT_DEBUG
#define DBG(__fmt, __x...) \
    do {                                                                    \
        fprintf(stderr, "%s: " __fmt "\n", __FUNCTION__, __x);              \
    } while (0)
#else
#define DBG(...)
#endif

#endif