#include "../include/square.h"

int32_t draw_line(RGB*** arr, const BitmapInfoHeader* bmih,
                  int64_t x0, int64_t y0, int64_t x1, int64_t y1,
                  const uint32_t thickness, RGB color)
{
    int32_t ret_val;
    
    uint32_t W = bmih->width;
    uint32_t H = bmih->height;

    // draw vertical line
    if (x0 == x1) {
        if (y0 > y1)
            swap_int64(&y0, &y1);

        for (int64_t y = y0; y < y1; y++) {
            for (int32_t l_pos = x0; l_pos < x0 + thickness; l_pos++) {
                ;    
            }
        }
    }

    return NO_ERROR;
}

int32_t square(RGB*** arr, const BitmapInfoHeader* bmih,
               int32_t* left_up, uint32_t side_size, uint32_t thickness,
               RGB color, RGB fill_color)
{
    
}
