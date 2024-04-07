#include <stdio.h>
#include "print_funcs.h"

void print_warn_msg(char* exe_name)
{
    printf("%s: missing arguments\n", exe_name);
    printf("Try \'%s --help\' for more information\n", exe_name);
}

void print_help(char* exe_name)
{
    printf("Usage: %s [OPTIONS] FILE\n", exe_name);
    printf("%4s, %-20s  %-30s\n", "-h", "--help", "print this help and exit");
    printf("%4s, %-20s  %-30s\n", "-i", "--info", "print info about bmp file");
    printf("%4s  %-20s  %-30s\n", " ", "--input", "set up file to processing");
    printf("%4s, %-20s  %-30s\n", "-o", "--output", "change standard output file name");
}
