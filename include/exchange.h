#ifndef __EXCHANGE__
#define __EXCHANGE__

#include <stdint.h>
#include <string.h>

#include "bmp.h"
#include "exceptions.h"
#include "etc.h"

void swap_rgb(RGB* a, RGB* b);

void rotate_clockwise(RGB*** arr, int64_t x0, int64_t y0,
                      int64_t x1, int64_t y1, uint32_t W, uint32_t H);

// counterclockwise
void rotate_cclockwise(RGB*** arr, int64_t x0, int64_t y0,
                      int64_t x1, int64_t y1, uint32_t W, uint32_t H);

void rotate_diagonals(RGB*** arr, int64_t x0, int64_t y0,
                      int64_t x1, int64_t y1, uint32_t W, uint32_t H);

int32_t exchange(RGB*** arr, 
                 int64_t* left_up, int64_t* right_down,
                 char* exchange_type, uint32_t H, uint32_t W);

#endif
