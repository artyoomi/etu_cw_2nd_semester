#include "exception.h"

size_t check_error(size_t ret_code) {
    switch (ret_code) {
        case FOPN_ERROR:
            fprintf(stderr, "Error while opening file\n");
            break;
        case FRD_ERROR:
            fprintf(stderr, "Error while read in file\n");
            break;
        case FWRT_ERROR:
            fprintf(stderr, "Error while write in file\n");  
            break;
        case MALLOC_ERROR:
            fprintf(stderr, "Error while allocating memory");
            break;
        case WRONG_SIGNATURE:
            fprintf(stderr, "Error: this is not BMP file");
            break;
        case WRONG_BMP_FORMAT:
            fprintf(stderr, "Only the BMP format is supported without compression and with 24-bit color\n");
            break;
        case EMPTY_ARG:
            fprintf(stderr, "Flag required an argument\n");
            break;
        // case EQUAL_ERROR:
        // case :
        // case ERROR
    }
    return ret_code;
}
