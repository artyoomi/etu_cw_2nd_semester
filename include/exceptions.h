#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <stdio.h>

// extern enum {      
//     FOPN_ERROR = 1,             // fopen error
//     FRD_ERROR = 2,              // fread error
//     FWRT_ERROR = 3,             // fwrite error
//     MALLOC_ERROR = 4,           // memory allocate error
//     WRONG_SIGNATURE = 5,        // not bmp file
//     WRONG_BMP_FORMAT = 6,       // doesnt match 24-bit format and zero compression
//     WRONG_ARG = -1,              // wrong flag argument
//     EMPTY_ARG = 8
// } internal_exception_t;

extern enum {
    NO_ERROR = 0,
    IO_ERROR = 40,
    ALLOC_ERROR = 41,
    BMP_FORMAT_ERROR = 42,
    ARG_ERROR = 43,
    PARSE_ERROR = 44,
    POINTER_ERROR = 45,
    DICT_ERROR = 46
} external_exception_t;

#define error_return(msg, error_code) \
        ({ fprintf(stderr, "Error: "); \
           fprintf(stderr, msg); \
           return error_code; })

// error_return with file descriptor
#define error_return_wfd(msg, error_code, fd) \
        ({ fprintf(stderr, "Error: "); \
           fprintf(stderr, msg); \
           fclose(fd); \
           return error_code; })

// error_return with argument
#define error_return_warg(msg, error_code, arg) \
        ({ fprintf(stderr, "Error: "); \
           fprintf(stderr, msg, arg); \
           return error_code; })

#endif
