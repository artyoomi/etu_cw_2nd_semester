#include "../include/etc.h"

void swap_int64(int64_t* a, int64_t* b)
{
    int64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

