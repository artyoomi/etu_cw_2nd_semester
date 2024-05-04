#include "../include/exchange.h"

// delta x and delta y
int64_t dx;
int64_t dy;

// coords after mid of area
int64_t aft_mid_x;
int64_t aft_mid_y;

void swap_rgb(RGB* a, RGB* b)
{
    RGB tmp = *a;
    *a = *b;
    *b = tmp;  
}

void rotate_clockwise(RGB*** arr, int64_t x0,  int64_t y0,
                      int64_t x1, int64_t y1, uint32_t W, uint32_t H)
{

    for (int64_t x_lu = x0; x_lu < aft_mid_x; x_lu++) {
        for (int64_t y_lu = y0; y_lu > aft_mid_y; y_lu--) {
            
            // x and y for right down area 
            int64_t x_rd = aft_mid_x + labs(x_lu - x0);
            int64_t y_rd = aft_mid_y - labs(y_lu - y0);

            // x and y for left down area
            int64_t x_ld = x_lu;
            int64_t y_ld = y_rd;

            // x and y for right up area
            int64_t x_ru = x_rd;
            int64_t y_ru = y_lu;
            
            // left up with left down 
            swap_rgb(&(*arr)[y_lu][x_lu], &(*arr)[y_ld][x_ld]);
            // right up with right_down
            swap_rgb(&(*arr)[y_ru][x_ru], &(*arr)[y_rd][x_rd]);
            // curr right up (prev right down) with curr left down (prev left_up)
            swap_rgb(&(*arr)[y_ru][x_ru], &(*arr)[y_ld][x_ld]);
        }
    }
}

void rotate_cclockwise(RGB*** arr, int64_t x0,  int64_t y0,
                       int64_t x1, int64_t y1, uint32_t W, uint32_t H)
{
    
    for (int64_t x_lu = x0; x_lu < aft_mid_x; x_lu++) {
        for (int64_t y_lu = y0; y_lu > aft_mid_y; y_lu--) {
            
            // x and y for right down area 
            int64_t x_rd = aft_mid_x + labs(x_lu - x0);
            int64_t y_rd = aft_mid_y - labs(y_lu - y0);

            // x and y for left down area
            int64_t x_ld = x_lu;
            int64_t y_ld = y_rd;

            // x and y for right up area
            int64_t x_ru = x_rd;
            int64_t y_ru = y_lu;
            
            // right down with right up             
            swap_rgb(&(*arr)[y_rd][x_rd], &(*arr)[y_ru][x_ru]);
            // left up with left down
            swap_rgb(&(*arr)[y_lu][x_lu], &(*arr)[y_ld][x_ld]);
            // curr left up (prev left down) with right down (prev right up)
            swap_rgb(&(*arr)[y_lu][x_lu], &(*arr)[y_rd][x_rd]);
        }
    }
}

void rotate_diagonal(RGB*** arr, int64_t x0,  int64_t y0,
                     int64_t x1, int64_t y1, uint32_t W, uint32_t H)
{
    // iterating throw left up area
    for (int64_t x_lu = x0; x_lu < aft_mid_x; x_lu++) {
        for (int64_t y_lu = y0; y_lu > aft_mid_y; y_lu--) {
            
            // x and y for right down area 
            int64_t x_rd = aft_mid_x + labs(x_lu - x0);
            int64_t y_rd = aft_mid_y - labs(y_lu - y0);

            // x and y for left down area
            int64_t x_ld = x_lu;
            int64_t y_ld = y_rd;

            // x and y for right up area
            int64_t x_ru = x_rd;
            int64_t y_ru = y_lu;
            
            // left up and right down             
            swap_rgb(&(*arr)[y_lu][x_lu], &(*arr)[y_rd][x_rd]);
            // left_down and right up
            swap_rgb(&(*arr)[y_ld][x_ld], &(*arr)[y_ru][x_ru]);
        }
    }
}

// processing only good sized image
int32_t exchange(RGB*** arr,
                 int64_t* left_up, int64_t* right_down,
                 char* exchange_type, uint32_t H, uint32_t W)
{
    int64_t x0 = left_up[0];
    int64_t y0 = H - left_up[1] - 1;
    int64_t x1 = right_down[0];
    int64_t y1 = H - right_down[1] - 1;

    // standartize x coords
    if (x0 < 0)
        x0 = 0;
    if (x0 >= W)
        x0 = W - 1;
    if (x1 < 0)
        x1 = 0;
    if (x1 >= W)
        x1 = W - 1;

    // standartize y coords
    if (y0 < 0)
        y0 = 0;
    if (y0 >= H)
        y0 = H - 1;
    if (y1 < 0)
        y1 = 0;
    if (y1 >= H)
        y1 = H - 1;

    // standarize points
    if (x0 > x1)
        swap_int64(&x0, &x1);
    if (y0 < y1)
        swap_int64(&y0, &y1);

    dx = labs(x1 - x0);
    dy = labs(y1 - y0);

    aft_mid_x = x0 + dx / 2;
    aft_mid_y = y0 - dy / 2;    
    
    if (!strcmp(exchange_type, "clockwise")) {
        rotate_clockwise(arr, x0, y0, x1, y1, W, H);
    } else if (!strcmp(exchange_type, "counterclockwise")) {
        rotate_cclockwise(arr, x0, y0, x1, y1, W, H);
    } else if (!strcmp(exchange_type, "diagonals")) {
        rotate_diagonal(arr, x0, y0, x1, y1, W, H);
    } else
        error_return("Unknown argument for --exchange_type flag\n", ARG_ERROR);
        
    return NO_ERROR;
}
