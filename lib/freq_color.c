#include "../include/freq_color.h"

int32_t freq_color(RGB*** arr, const BitmapInfoHeader *bmih, RGB color)
{
    int32_t ret_val;
    
    uint32_t W = bmih->width;
    uint32_t H = bmih->height;

    Dict *dict = NULL;

    // add colors in dictonary
    for (uint32_t i = 0; i < H; i++) {
        for (uint32_t j = 0; j < W - 1; j++) {
            ret_val = dict_add(&dict, (*arr)[i][j]);
            if (ret_val)
                return DICT_ERROR;
        }
    }

    uint32_t max_count = 0;
    RGB max_color;

    // find the most frequent color
    for (uint32_t i = 0; i < dict->len; i++) {
        if (dict->pairs[i].count > max_count) {
            max_count = dict->pairs[i].count;
            max_color.r = dict->pairs[i].color.r;
            max_color.g = dict->pairs[i].color.g;
            max_color.b = dict->pairs[i].color.b;
        }
    }

    RGB curr;
    // replace max freq color
    for (uint32_t i = 0; i < H; i++) {
        for (uint32_t j = 0; j < W; j++) {
            curr = (*arr)[i][j];
            if (curr.r == max_color.r && 
                curr.g == max_color.g && 
                curr.b == max_color.b) {
                // fprintf(stderr, "Coords is [%u][%u]\n", i, j);
                (*arr)[i][j] = color;
            }
        }
    }

    // free dict memory
    free(dict->pairs);
    free(dict);

    printf("The most frequent color was succesfully replaced!\n");
    printf("Max freq color is (%u,%u,%u)\n", 
           max_color.r, max_color.g, max_color.b);
    printf("Max color count is [%u]\n", max_count);
    return NO_ERROR;
}
