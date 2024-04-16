#include "../include/print_funcs.h"

void print_warn_msg(char* exe_name)
{
    printf("%s: missing arguments\n", exe_name);
    printf("Try \'%s --help\' for more information\n", exe_name);
}

void print_help(char* exe_name)
{
    printf("Usage: %s [OPTIONS] FILE\n", exe_name);
    printf("%4s  %-40s  %-30s\n", "-h,", "--help", "print this help and exit");
    printf("%4s  %-40s  %-30s\n", "-I,", "--info", "print info about bmp file");
    printf("%4s  %-40s  %-30s\n", "-i,", "--input [INP_NAME]", "set up file to processing");
    printf("%4s  %-40s  %-30s\n", "-o,", "--output [OUT_NAME]", "change standard output file name");
    
    printf("%4s  %-40s  %-30s\n", "-r,", "--rgbfilter", "changes chosen RGB component of image, need flags --component_name and --component_value to work");
    printf("%4s  %-40s  %-30s\n", "-n,", "--component_name [red|green|blue]", "flag to choose component to be replaced");
    printf("%4s  %-40s  %-30s\n", "-v,", "--component_value [0..255]", "flag to enter new value of component");
    
    printf("%4s  %-40s  %-30s\n", "-s,", "--square", "draws square, for work need flag --left_up, --side_size, --thickness, --color and optionally argument --fill and --fill_color");
    printf("%4s  %-40s  %-30s\n", " ", "--left_up [LEFT.UP]", "entering coordinates of the upper-left corner of the square");
    printf("%4s  %-40s  %-30s\n", "-S,", "--side_size [POSITIVE_NUMBER]", "entering side size of square");
    printf("%4s  %-40s  %-30s\n", "-T,", "--thickness [POSITIVE_NUMBER]", "entering thickness of square side");
    printf("%4s  %-40s  %-30s\n", "-c,", "--color [R.G.B]", "entering color components");
    printf("%4s  %-40s  %-30s\n", "-l,", "--fill", "it works as a flag and indicates whether a square should be filled in");
    printf("%4s  %-40s  %-30s\n", "-C,", "--fill_color [R.G.B]", "selecting the color to fill the square with if the --fill flag was entered");

    printf("%4s  %-40s  %-30s\n", "-e,", "--exchange", "flag to change image parts, need flags --left_up, --right_down and --exchange_type");
    printf("%4s  %-40s  %-30s\n", "-R,", "--right_down [RIGHT.DOWN]", "flag to choose right down corner of segment to be changed");   
    printf("%4s  %-40s  %-30s\n", "-E,", "--exchange_type [clockwise|counterclockwise|diagonals]", "flag to choose mode to change image parts");
    printf("%4s  %-40s  %-30s\n", "-f,", "--freq_color", "finds and replaces with the most frequent color to argument of flag --color");
}
