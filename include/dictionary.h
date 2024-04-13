#ifndef __DICTIONARY__
#define __DICTIONARY__

#include "bmp.h"
#include "exceptions.h"

typedef struct {
    RGB color;
    uint32_t count;
} Pair;

typedef struct {
    uint32_t len;
    Pair *pairs;
} Dict;

int32_t dict_add(Dict **dict, RGB color);

#endif
