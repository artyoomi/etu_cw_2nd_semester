#ifndef __IMAGE__
#define __IMAGE__

#include <stdint.h>
//#include <math.h>

#include "bmp.h"
#include "etc.h"


RGB** image_copy_area(RGB*** arr,
                      int64_t x_lu, int64_t y_lu,
                      int64_t x_rd, int64_t y_rd,
                      uint32_t H, uint32_t W);

void image_replace_to_area(RGB*** arr, RGB*** area,
                           int64_t x_dest, int64_t y_dest,
                           int32_t area_height, int32_t area_width,
                           uint32_t H, uint32_t W);

void image_most(RGB*** arr,
                int64_t x_lu, int64_t y_lu,
                int64_t x_rd, int64_t y_rd,
                uint32_t H, uint32_t W);

int32_t image_outside_rect(RGB*** arr,
                           int64_t x_lu, int64_t y_lu,
                           int64_t x_rd, int64_t y_rd, RGB color,
                           uint32_t H, uint32_t W);

#endif
