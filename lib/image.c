#include "../include/image.h"

// MOST IMAGE ===============================================
RGB** image_copy_area(RGB*** arr,
                      int64_t x_lu, int64_t y_lu,
                      int64_t x_rd, int64_t y_rd,
                      uint32_t H, uint32_t W)
{
    if (x_lu > x_rd)
        swap_int64(&x_lu, &x_rd);
    if (y_lu < y_rd)
        swap_int64(&y_lu, &y_rd);

    int32_t area_height = y_lu - y_rd + 1;
    int32_t area_width = x_rd - x_lu + 1;

    RGB **area = (RGB**)malloc(area_height * sizeof(RGB*));
    for (int32_t i = 0; i < area_height; i++) {
        area[i] = (RGB*)malloc(area_width * sizeof(RGB));
    }

    // fill area array
    for (int64_t y = y_lu; y > y_lu - area_height; y--) {
        for (int64_t x = x_lu; x < x_lu + area_width; x++) {
            // x and y coords in area array
            int64_t y_area = y_lu - y;
            int64_t x_area = x - x_lu;
            if (x_area >= 0 && x_area < W &&
                y_area >= 0 && y_area < H &&
                x >= 0 && x < W &&
                y >= 0 && y < H)
                area[y_area][x_area] = (*arr)[y][x];
        }
    }

    return area;
}

void image_replace_to_area(RGB ***arr, RGB ***area,
                           int64_t x_dest, int64_t y_dest,
                           int32_t area_height, int32_t area_width,
                           uint32_t H, uint32_t W)
{
    // replace dest pixels
    for (int64_t y = y_dest; y > y_dest - area_height; y--) {
        for (int64_t x = x_dest; x < x_dest + area_width; x++) {
            // x and y coords in area array
            int64_t y_area = y_dest - y;
            int64_t x_area = x - x_dest;
            if (x_area >= 0 && x_area < W &&
                y_area >= 0 && y_area < H &&
                x >= 0 && x < W &&
                y >= 0 && y < H)
                (*arr)[y][x] = (*area)[y_area][x_area];
        }
    }
}

void image_most(RGB*** arr,
                int64_t x_lu, int64_t y_lu,
                int64_t x_rd, int64_t y_rd,
                uint32_t H, uint32_t W)
{
    // check what coords are in image borders
    if (x_lu < 0)
        x_lu = 0;
    if (x_lu >= W)
        x_lu = W - 1;
    
    if (x_rd < 0)
        x_rd = 0;
    if (x_rd >= W)
        x_rd = W - 1;

    if (y_lu < 0)
        y_lu = 0;
    if (y_lu >= H)
        y_lu = H - 1;

    if (y_rd < 0)
        y_rd = 0;
    if (y_rd >= H)
        y_rd = H - 1;


    // change coords to left up orientation
    y_lu = H - y_lu - 1;
    y_rd = H - y_rd - 1;
    
    int32_t area_height = labs(y_lu - y_rd) + 1;
    int32_t area_width = labs(x_rd - x_lu) + 1;

    int64_t delta_y = labs(y_lu - y_rd);
    int64_t delta_x = labs(x_lu - x_rd);

    RGB** area = image_copy_area(arr, x_lu, y_lu, x_rd, y_rd, H, W);

    for (int64_t y = H - 1; y >= 0; y -= delta_y) {
        for (int64_t x = 0; x < W; x += delta_x) {
            image_replace_to_area(arr, &area, x, y,
                                  area_height, area_width, H, W);
        }
    }


    for (int32_t i = 0; i < area_height; i++) {
        free(area[i]);
    }
    free(area);
}
// ========================================================

int32_t image_outside_rect(RGB*** arr, int64_t x_lu, int64_t y_lu,
                           int64_t x_rd, int64_t y_rd, RGB color,
                           uint32_t H, uint32_t W)
{
    // check what coords are in image borders
    if (x_lu < 0)
        x_lu = 0;
    if (x_lu >= W)
        x_lu = W - 1;
    
    if (x_rd < 0)
        x_rd = 0;
    if (x_rd >= W)
        x_rd = W - 1;

    if (y_lu < 0)
        y_lu = 0;
    if (y_lu >= H)
        y_lu = H - 1;

    if (y_rd < 0)
        y_rd = 0;
    if (y_rd >= H)
        y_rd = H - 1;   

    // standartize y comps
    y_lu = H - y_lu - 1;
    y_rd = H - y_rd - 1;
    
    if (x_lu > x_rd)
        swap_int64(&x_lu, &x_rd);
    if (y_lu < y_rd)
        swap_int64(&y_lu, &y_rd);
    
    for (int64_t y = 0; y < H; y++) {
        for (int64_t x = 0; x < W; x++) {
            if (!(x >= x_lu && x <= x_rd && y <= y_lu && y >= y_rd)) {
                (*arr)[y][x] = color;
            }
        }
    }
    
    return NO_ERROR;
}
