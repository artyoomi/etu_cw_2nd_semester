#ifndef __EXCEPTION__
#define __EXCEPTION__

#include <stdio.h>

extern enum {
    NO_ERROR = 0,
    FOPN_ERROR = 40,
    FRD_ERROR = 41,
    FWRT_ERROR = 42,
    MALLOC_ERROR = 43,
    WRONG_SIGNATURE = 44,
    WRONG_BMP_FORMAT = 45
} exception_t;

size_t check_error(const size_t ret);

#endif
