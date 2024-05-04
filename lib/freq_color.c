#include "../include/freq_color.h"

void freq_color(RGB*** arr, RGB color, uint32_t H, uint32_t W)
{
    // this realization is fast but use a lot of memory
    RGB max_color = {0, 0, 0};
    uint32_t max_count = 0;

    // def and init colors array
    const uint64_t colors_len = 256*256*256 + 256*256 + 256;
    uint32_t* colors = (uint32_t*)calloc(colors_len, sizeof(uint32_t));

    // find most freq color
    for (uint32_t i = 0; i < H; i++) {
        for (uint32_t j = 0; j < W; j++) {
            RGB curr_color = (*arr)[i][j];
            uint8_t r = curr_color.r;
            uint8_t g = curr_color.g;
            uint8_t b = curr_color.b;
            uint64_t ind = 256*256*r + 256*g + b;
            
            colors[ind]++;
            if (colors[ind] > max_count) {
                max_count = colors[ind];
                max_color = curr_color;
            }            
        }
    }

    // replace most frequent color to new color
    for (uint32_t i = 0; i < H; i++) {
        for (uint32_t j = 0; j < W; j++) {
            RGB curr_color = (*arr)[i][j];
            if (curr_color.r == max_color.r &&
                curr_color.g == max_color.g &&
                curr_color.b == max_color.b) {
                (*arr)[i][j] = color;
            }
        }
    }

    printf("The most frequent color was succesfully replaced!\n");
    printf("Max freq color is (%u,%u,%u)\n", 
           max_color.r, max_color.g, max_color.b);
    printf("Max color count is [%u]\n", max_count);
    
    free(colors);
}
