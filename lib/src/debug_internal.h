/**
 * @file
 * @brief Internal debug definitions
 * @author Maxim Menshikov (maxim@menshikov.org)
 */
#ifndef FMT_DEBUG_INTERNAL_H
#define FMT_DEBUG_INTERNAL_H

#ifdef FMT_DEBUG
/** Perform debug print */
#define DBG(__fmt, __x...) \
    do {                                                                    \
        fprintf(stderr, "%s: " __fmt "\n", __FUNCTION__, __x);              \
    } while (0)
#else
#define DBG(...) do { } while (0)
#endif

#endif
