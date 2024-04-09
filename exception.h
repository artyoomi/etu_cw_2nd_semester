#ifndef __EXCEPTION__
#define __EXCEPTION__

#include <stdio.h>

extern enum {
    NO_ERROR = 0,      
    FOPN_ERROR = 40,             // fopen error
    FRD_ERROR = 41,              // fread error
    FWRT_ERROR = 42,             // fwrite error
    MALLOC_ERROR = 43,           // memory allocate error
    WRONG_SIGNATURE = 44,        // not bmp file
    WRONG_BMP_FORMAT = 45,       // doesnt match 24-bit format and zero compression
    WRONG_ARG = 46,              // wrong flag argument
    EMPTY_ARG = 47,
    ERROR = 49
} exception_t;

size_t check_error(const size_t ret);

#endif
