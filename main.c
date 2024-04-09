#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "bmp.h"
#include "exception.h"
#include "print_funcs.h"
#include "rgbfilter.h"

typedef struct {
    int8_t info;
    int8_t input;
    int8_t output;
    int8_t rgbfilt;
} Config;

typedef struct {
    char* input;
    char* output;
    char* rgb_comp;
} Optarg;

int main(int argc, char** argv)
{   
    printf("Course work for option 5.3, created by Artem Ivanov\n");

    if (argc == 1) {
        print_warn_msg(argv[0]);
        return NO_ERROR;
    }

    Config config = {0, 0, 0, 0};
    Optarg optargs = {argv[argc - 1], "out.bmp"};

    int32_t optchar;
    
    // to use custom error messages
    //opterr = 0;
        
    char* short_options = "hI::i:o:r";
    struct option long_options[] =  {
        {"help", no_argument, NULL, 'h'}, 
        {"info", optional_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'}, 
        {"output", required_argument, NULL, 'o'},
        {"rgbfilter", required_argument, NULL, 'r'},
        {"component_name", required_argument, NULL, 'n'},
        {"component_value", required_argument, NULL, 'v'},
        {"square", required_argument, NULL, 's'},
        {"left_up", required_argument, NULL, 't'},
        {"side_size", required_argument, NULL, 'S'},
        {"thickness", required_argument, NULL, 'T'},
        {"color", required_argument, NULL, 'c'},
        {"fill", required_argument, NULL, 'l'},
        {"fill_color", required_argument, NULL, 'L'},
        {"exchange", required_argument, NULL, 'e'},
        {"right_down", required_argument, NULL, 'R'},
        {"exchange_type", required_argument, NULL, 'E'},
        {"freq_color", required_argument, NULL, 'f'},
        {NULL, no_argument, NULL, 0}
    };

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB** arr;
    
    while ((optchar = getopt_long(argc, argv, short_options, long_options, 
                                  &optind)) != -1) {
        switch (optchar) {
            case 'h':
                print_help(argv[0]);
                return NO_ERROR;
            case 'I':
                config.info = 1;
                break;
            case 'i':
                if (optarg != NULL) {
                    config.input = 1;
                    optargs.input = strdup(optarg);
                    break;
                } else {
                    check_error(EMPTY_ARG);
                    return EMPTY_ARG;    
                }
            case 'o':
                if (optarg != NULL) {
                    config.output = 1;
                    optargs.output = strdup(optarg);
                    break;
                } else {
                    check_error(EMPTY_ARG);
                    return EMPTY_ARG;
                }
            case 'r':
            case 'n':
            case 'v':
            case 's':
            case 't':
            case 'S':
            case 'T':
            case 'c':
            case 'l':
            case 'L':
            case 'e':
            case 'R':
            case 'E':
            case 'f':
                break;
            case '?':
                return ERROR;
        }
    }

    // check if input and output filename is match
    if (!strcmp(optargs.input, optargs.output)) {
        fprintf(stderr, "The input and output file name must not match!\n");
        return ERROR;
    }

    // input bmp file information
    size_t ret = read_bmp(optargs.input, &arr, &bmfh, &bmih);
    if (check_error(ret)) return ret;

    // print file inforamtion
    if (config.info) {
        printf("BitmapFileHeader:\n");
        print_file_header(bmfh);
        printf("\nBitmapInfoHeader:\n");
        print_info_header(bmih);
        return NO_ERROR;
    }
    
    ret = write_bmp(optargs.output, &arr, &bmfh, &bmih);
    
    for (; optind < argc; optind++) {
        printf("extra arg is %s\n", argv[optind]);
    }

    // !!! add free expresions
    return NO_ERROR;
}
