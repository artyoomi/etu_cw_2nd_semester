#include "../include/draw.h"

// coords in format: x0 y0 x1 y1 ... xn yn
int32_t polygon_fill(RGB*** arr,
                     int64_t* coords, int32_t coords_len, RGB fill_color)
{
    if (!coords)
        error_return("Coords array is NULL\n", POINTER_ERROR);
    else if (coords_len % 2 != 0)
        error_return("Must be 2 components for each coord\n", ARG_ERROR);

    typedef struct {
        
    } edges_table;
    
    return NO_ERROR;
}

void draw_triangle(RGB*** arr, int64_t x0, int64_t y0,
                   int64_t x1, int64_t y1, int64_t x2, int64_t y2,
                   int32_t thickness, RGB color,
                   uint8_t is_fill, RGB fill_color,
                   uint32_t H, uint32_t W)
{
    if (is_fill) {
        int64_t coords[] = {x0, y0, x1, y1, x2, y2};
        int32_t coords_len = 6;
        polygon_fill(arr, coords, coords_len, fill_color);
    }
    
    draw_line(arr, x0, y0, x1, y1, thickness, color, H, W);
    draw_line(arr, x1, y1, x2, y2, thickness, color, H, W);
    draw_line(arr, x2, y2, x0, y0, thickness, color, H, W);  
}

void draw_8pixels(RGB*** arr, int64_t x0, int64_t y0,
                  int64_t x, int64_t y, int32_t thickness, RGB color,
                  uint32_t H, uint32_t W)
{
    fill_circle(arr, x + x0, y + y0, thickness, color, H, W);
    fill_circle(arr, x + x0, -y + y0, thickness, color, H, W);
    fill_circle(arr, -x + x0, -y + y0, thickness, color, H, W);
    fill_circle(arr, -x + x0, y + y0, thickness, color, H, W);
    fill_circle(arr, y + x0, x + y0, thickness, color, H, W);
    fill_circle(arr, y + x0, -x + y0, thickness, color, H, W);
    fill_circle(arr, -y + x0, -x + y0, thickness, color, H, W);
    fill_circle(arr, -y + x0, x + y0, thickness, color, H, W);
}

void draw_circle(RGB*** arr, int64_t x0, int64_t y0, int32_t radius,
                 int32_t thickness, RGB color,
                 uint8_t is_fill, RGB fill_color,
                 uint32_t H, uint32_t W)
{
    int64_t hor_dist;
    int64_t diag_dist;
    int64_t dist;

    int64_t x = 0;
    int64_t y = radius;

    if (is_fill) {
        fill_circle(arr, x0, y0, radius, fill_color, H, W);
    }
   
    dist = 3 - 2 * y;
    while (x <= y) {
        draw_8pixels(arr, x0, y0, x, y, thickness, color, H, W);
        if (dist < 0)
            dist = dist + 4 * x + 6;
        else {
            dist = dist + 4 * (x - y) + 10;
            y--;
        }
        x++; 
    }
}

void fill_circle(RGB*** arr, int64_t x0, int64_t y0, int32_t radius,
                 RGB fill_color, uint32_t H, uint32_t W)
{
    for (int32_t i = -radius; i <= radius; i++) {
        for (int32_t j = -radius; j <= radius; j++) {
            // real coord values
            int64_t x_r = x0 + j;
            int64_t y_r = y0 - i;
            if (i * i + j * j <= radius * radius &&
                x_r >= 0 && x_r < W && y_r >= 0 && y_r < H)
                (*arr)[y_r][x_r] = fill_color;
        }
    }
}

// brezenham line drawing algorithm
int32_t draw_line(RGB*** arr, 
                  int64_t x0, int64_t y0, int64_t x1, int64_t y1,
                  int32_t thickness, RGB color,
                  uint32_t H, uint32_t W)
{
    if (x0 != x1) {
        if (x0 > x1) {
            swap_int64(&x0, &x1);
            swap_int64(&y0, &y1);
        }
             
        double k = (double)(y1 - y0) / (x1 - x0);
        double b = (double)y0 - (double)k * x0;
        for (int32_t x = x0; x < x1 + 1; x++) {
            int32_t y = k * x + b;
            fill_circle(arr, x, y, thickness / 2, color, H, W);
        }
    } else {
        if (y0 > y1)
            swap_int64(&y0, &y1);
        
        for (int32_t y = y0; y < y1; y++) {
            fill_circle(arr, x0, y, thickness / 2, color, H, W);
        }
    }
    
    return NO_ERROR;
}

int32_t draw_square(RGB*** arr, int64_t* left_up, uint32_t side_size,
                    uint32_t thickness, RGB color,
                    uint8_t is_fill, RGB fill_color,
                    uint32_t H, uint32_t W)
{
    // x and y swaped to be nice for test system -
    // need to fix later
    int64_t x0 = left_up[0];
    int64_t y0 = H - left_up[1] - 1;

    int64_t delta_left = thickness / 2;
    int64_t delta_right = (thickness % 2) ? (thickness / 2)
                                          : (thickness / 2 - 1);

    if (is_fill && side_size > 2) {
        for (int64_t y = y0; y > y0 - side_size; y--) {
            for (int64_t x = x0; x < x0 + side_size - 1; x++) {
                if (x >= 0 && x < W && y >= 0 && y < H)
                (*arr)[y][x] = fill_color;
            }
        }
    }

    // left up corner
    int64_t x_lu = x0;
    int64_t y_lu = y0;

    // right up corner
    int64_t x_ru = x_lu + side_size - 1;
    int64_t y_ru = y_lu;

    // right down corner
    int64_t x_rd = x_ru;
    int64_t y_rd = y_ru - (side_size - 1);

    // left down corner
    int64_t x_ld = x_lu;
    int64_t y_ld = y_rd;
    
    draw_line(arr, x_lu, y_lu, x_ru, y_ru, thickness, color, H, W);
    draw_line(arr, x_ru, y_ru, x_rd, y_rd, thickness, color, H, W);
    draw_line(arr, x_rd, y_rd, x_ld, y_ld, thickness, color, H, W);
    draw_line(arr, x_ld, y_ld, x_lu, y_lu, thickness, color, H, W);    

    return NO_ERROR;
}
