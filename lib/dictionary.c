#include "../include/dictionary.h"

int32_t dict_add(Dict **dict, RGB color)
{
    if (dict == NULL)
        error_return("Pointer to dict is NULL", POINTER_ERROR);
    
    // if pointer to dict is NULL -> create dict
    if ((*dict) == NULL) {
        (*dict) = (Dict*)malloc(sizeof(Dict));
        (*dict)->pairs = (Pair*)malloc(ALLOC_BLOCK * sizeof(Pair));
        (*dict)->len = 0;
        (*dict)->alloc_size = ALLOC_BLOCK;
        (*dict)->pairs[0].color = color;
        (*dict)->pairs[0].count = 1;

        return NO_ERROR;
    }

    int32_t target_ind = -1;
    uint8_t color_in_dict = 0;
    for (uint32_t i = 0; i < (*dict)->len; i++) {
        if ((*dict)->pairs[i].color.r == color.r && 
            (*dict)->pairs[i].color.g == color.g &&
            (*dict)->pairs[i].color.b == color.b) {
            color_in_dict = 1;
            target_ind = i;
            break;
        }
    }

    if (color_in_dict) {
        (*dict)->pairs[target_ind].count++;
        return NO_ERROR;
    }
    if ((*dict)->alloc_size <= (*dict)->len) {
        (*dict)->pairs = (Pair*)realloc((*dict)->pairs, 
                                    ((*dict)->len + ALLOC_BLOCK) * sizeof(Pair));
        (*dict)->alloc_size += ALLOC_BLOCK;
    }
    if (!(*dict)->pairs)
        error_return("Reallocate for Pair array failed!\n", ALLOC_ERROR);
    
    (*dict)->pairs[(*dict)->len].color = color;
    (*dict)->pairs[(*dict)->len].count = 1;
    (*dict)->len++;

    return NO_ERROR;
}
