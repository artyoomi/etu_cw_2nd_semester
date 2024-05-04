#ifndef __DRAW__
#define __DRAW__

#include <stdint.h>
#include <math.h>

#include "bmp.h"
#include "exceptions.h"
#include "etc.h"

typedef struct {
    uint8_t up_hor;
    uint8_t down_hor;
    uint8_t left_vert;
    uint8_t right_vert;
} DrawConf;

void draw_triangle(RGB*** arr, int64_t x0, int64_t y0,
                   int64_t x1, int64_t y1, int64_t x2, int64_t y2,
                   int32_t thickness, RGB color,
                   uint8_t is_fill, RGB fill_color,
                   uint32_t H, uint32_t W);


// draw 8 symetric pixels
void draw_8pixels(RGB*** arr, int64_t x0, int64_t y0,
                  int64_t x, int64_t y, int32_t thickness, RGB color,
                  uint32_t H, uint32_t W);


void draw_circle(RGB*** arr, int64_t x0, int64_t y0, int32_t radius,
                 int32_t thickness, RGB color,
                 uint8_t is_fill, RGB fill_color,
                 uint32_t H, uint32_t W);

void fill_circle(RGB*** arr, int64_t x0, int64_t y0,
                 int32_t radius, RGB fill_color,
                 uint32_t H, uint32_t W);

int32_t draw_line(RGB*** arr,
                  int64_t x0, int64_t y0, int64_t x1, int64_t y1,
                  int32_t thickness, RGB color,
                  uint32_t H, uint32_t W);

int32_t draw_square(RGB*** arr, int64_t* left_up, uint32_t side_size,
                    uint32_t thickness, RGB color,
                    uint8_t is_fill, RGB fill_color,
                    uint32_t H, uint32_t W);

#endif
