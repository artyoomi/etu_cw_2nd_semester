#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "bmp.h"
#include "exception.h"
#include "print_funcs.h"

typedef struct {
    int32_t help;
    int32_t info;
    int32_t input;
    int32_t output;
} Config;

int main(int argc, char** argv)
{
    printf("Course work for option 5.3, created by Artem Ivanov\n");

    if (argc == 1) {
        print_warn_msg(argv[0]);
        return 1;
    }

    // to change flags input later
    Config config = {0, 0, 0, 0};

    char* optstring = "h?io:";
    struct option long_options[] =  {
        {"help", no_argument, NULL, 1},
        {"info", no_argument, NULL, 2},
        {"input", required_argument, NULL, 3}, 
        {"output", required_argument, NULL, 4},
        {NULL, no_argument, NULL, 0}
    };

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;

    RGB** arr;
    // to think about logic when --help and file typed together
    size_t ret = read_bmp(&arr, argv[argc - 1], &bmfh, &bmih);
    if (check_error(ret))
        return ret;

    int32_t optchar;
    while ((optchar = getopt_long(argc, argv, optstring, long_options, 
                                  &optind)) != -1) {
        switch (optchar) {
            case 1:
                print_help(argv[0]);
                return 0;
            case 2:
                printf("BMP HEADER:\n");
                print_file_header(bmfh);
                printf("\nBMP HEADER INFO:\n");
                print_info_header(bmih);
                return 0;
            case 3:
                // to add change file name logic with "optarg"
                printf("In input: %s\n", optarg);
                break;
            case 4:
                printf("In output: %s\n", optarg);
                break;
            default:
                // to add some logic
                break;
        }
    }

    return 0;
}
