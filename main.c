#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

#include "include/bmp.h"
#include "include/exceptions.h"
#include "include/print_funcs.h"
#include "include/rgbfilter.h"
#include "include/square.h"
#include "include/exchange.h"
#include "include/freq_color.h"
#include "include/parse_funcs.h"

typedef struct {
    int8_t info;
    int8_t input;
    int8_t output;
    int8_t rgbfilter;
    int8_t component_name;
    int8_t component_value;
    int8_t square;
    int8_t left_up;
    int8_t side_size;
    int8_t thickness;
    int8_t color;
    int8_t fill;
    int8_t fill_color;
    int8_t freq_color;
    int8_t exchange;
    int8_t right_down;
    int8_t exchange_type;
} Config;

typedef struct {
    char* input;
    char* output;
    char* component_name;           // checks in rgbfilter
    uint8_t component_value;        // in string form, checks in rgbfilter
    int64_t* left_up;
    uint32_t side_size;
    uint32_t thickness;
    RGB color;
    RGB fill_color;
    int64_t* right_down;
    char *exchange_type;
} Optarg;

int main(int argc, char** argv)
{   
    printf("Course work for option 5.3, created by Artem Ivanov\n");

    if (argc == 1) {
        print_warn_msg(argv[0]);
        return NO_ERROR;
    }

    Config config = {0, 0, 0, 0, 0, 0};
    Optarg optargs = {NULL, NULL, NULL, 0, NULL};

    int32_t optchar;
    int32_t ret_val = 0;  
    // to use custom error messages
    //opterr = 0;
        
    char* short_options = "hIi:o:rn:v:sS:T:c:lC:eR:E:f";
    struct option long_options[] =  {
        {"help", no_argument, NULL, 'h'}, 
        {"info", no_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'}, 
        {"output", required_argument, NULL, 'o'},
        
        {"rgbfilter", no_argument, NULL, 'r'},
        {"component_name", required_argument, NULL, 'n'},
        {"component_value", required_argument, NULL, 'v'},
        
        {"square", no_argument, NULL, 's'},
        {"left_up", required_argument, NULL, 't'},
        {"side_size", required_argument, NULL, 'S'},
        {"thickness", required_argument, NULL, 'T'},
        {"color", required_argument, NULL, 'c'},
        {"fill", no_argument, NULL, 'l'},
        {"fill_color", required_argument, NULL, 'C'},
        
        {"exchange", required_argument, NULL, 'e'},
        {"right_down", required_argument, NULL, 'R'},
        {"exchange_type", required_argument, NULL, 'E'},
        {"freq_color", no_argument, NULL, 'f'},
        {NULL, no_argument, NULL, 0}
    };

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB** arr;

    // all configuration logic and parse optargs arguments 
    // must be in this while loop    
    while ((optchar = getopt_long(argc, argv, short_options, long_options, 
                                  &optind)) != -1) {
        switch (optchar) {
            case 'h': // -h --help
                print_help(argv[0]);
                return NO_ERROR;
            case 'I': // -I --info
                config.info = 1;
                break;
            case 'i': // -i --input
                // if (optarg != NULL)
                // this check useless if opterr != 0
                // otherwise, a check is needed along with the error output
                // else { error throw logic }
                                
                config.input = 1;
                optargs.input = strdup(optarg);
                break;
            case 'o': // -o --output
                config.output = 1;
                optargs.output = strdup(optarg);
                break;
            case 'r': // --rgbfilter
                config.rgbfilter = 1;
                break;
            case 'n': // --component_name
                config.component_name = 1;
                optargs.component_name = strdup(optarg);
                break;
            case 'v': // --component_value
                config.component_value = 1;
                ret_val = parse_unsigned_char(optarg, &(optargs.component_value));
                    
                // check if parse was succesful
                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;
            case 's': // --square
                config.square = 1;
                break;
            case 't': // --left_up
                config.left_up = 1;
                ret_val = parse_coords(optarg, &(optargs.left_up));

                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;
            case 'S': // --size_size
                config.side_size = 1;
                ret_val = parse_posit_number(optarg, &(optargs.side_size));

                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;
            case 'T': // --thickness
                config.thickness = 1;
                // parse_side_size contains the necessary logic
                ret_val = parse_posit_number(optarg, &(optargs.thickness));

                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;
            case 'c': // --color
                config.color = 1;
                ret_val = parse_comps(optarg, &(optargs.color));

                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;
            case 'l': // --fill
                config.fill = 1;
                break;
            case 'C': // --fill_color
                if (config.fill) {
                    config.fill_color = 1;
                    ret_val = parse_comps(optarg, &(optargs.fill_color));
                    if (ret_val != PARSE_ERROR)
                        break;
                }
                return ARG_ERROR;
            case 'e': // --exchange
                config.exchange = 1;
                break;
            case 'R': // --right_down
                config.right_down = 1;
                ret_val = parse_coords(optarg, &(optargs.right_down));

                if (ret_val != PARSE_ERROR)
                    break;
                return ARG_ERROR;    
            case 'E': // --exchange_type
                config.exchange_type = 1;
                optargs.exchange_type = strdup(optarg);
                break;                
            case 'f': // --freq_color
                config.freq_color = 1;
                break;
            case '?': // unknown flag
                return ARG_ERROR;
        }
    }

    if (!config.input)
        optargs.input = strdup(argv[argc - 1]);

    if (!config.output)
        optargs.output = strdup("out.bmp");

    // check if input and output filename is match
    if (!strcmp(optargs.input, optargs.output) && !config.info) {
        error_return("Input and output file names musn't be the same!\n", ARG_ERROR);
        // fprintf(stderr, "Input and output file names musn't be the same!\n");
        // return ARG_ERROR;
    }

    // input bmp file information
    ret_val = read_bmp(optargs.input, &arr, &bmfh, &bmih);
    if (ret_val) return ret_val;

    // print file inforamtion
    if (config.info) {
        printf("BitmapFileHeader:\n");
        print_file_header(bmfh);
        printf("\nBitmapInfoHeader:\n");
        print_info_header(bmih);
        return NO_ERROR;
    }

    // 1. rgbfilter subtask
    if (config.rgbfilter) {
        if (!config.component_name || !config.component_value) {
            error_return("Missing flags to --rgbfilter, type --help to more information\n",
                         ARG_ERROR);
        } else {
            ret_val = rgbfilter(&arr, &bmih, 
                                optargs.component_name, 
                                optargs.component_value);
            if (ret_val)
                return ret_val;
        }
    }

    // 2. square subtask
    if (config.square) {
        if (!config.left_up || !config.side_size ||
            !config.thickness || !config.color)
            error_return("Missing flags to --square, type --help for more information\n",
                         ARG_ERROR);
        else if (!config.fill && config.fill_color || 
                 config.fill && !config.fill_color)
            error_return("Flag --fill and --fill_color nedd to be used together\n", ARG_ERROR);
        else {
            //ret_val = square();
            //if (ret_val) return ret_val;
            //printf("(%d;%d)\n", optargs.left_up[0], optargs.left_up[1]);
            draw_line(&arr, &bmih, optargs.left_up[0], optargs.left_up[1], 10, 2, 
                      optargs.thickness, optargs.color);
        }
    }

    // 3. exchange subtask
    if (config.exchange) {
        if (!config.left_up || !config.right_down || !config.exchange_type)
            error_return("--exchange need flags!\n", ARG_ERROR);    
        else {
            ret_val = exchange(&arr, &bmih, optargs.left_up,
                               optargs.right_down, optargs.exchange_type);
            if (ret_val)
                return ret_val; 
        }
    }
    
    // 4. freq_color subtask
    if (config.freq_color) {
        if (!config.color)
            error_return("--freq_color need --color flag!\n", ARG_ERROR); 
        
        ret_val = freq_color(&arr, &bmih, optargs.color);
        if (ret_val)
            return ret_val;    
    }
    
    // write changes in file
    ret_val = write_bmp(optargs.output, &arr, &bmfh, &bmih);
    if (ret_val) return ret_val;
    
    for (; optind < argc; optind++) {
        printf("extra arg is %s\n", argv[optind]);
    }

    // free optargs
    free(optargs.input);
    free(optargs.output);
    if (config.component_name)
        free(optargs.component_name);
    if (config.left_up)
        free(optargs.left_up);
    if (config.exchange_type)
        free(optargs.exchange_type);

    // free pixels array
    for (size_t i = 0; i < bmih.height; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return NO_ERROR;
}
