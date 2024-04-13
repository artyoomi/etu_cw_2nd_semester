#include "../include/square.h"

void swap_int(int32_t *a, int32_t *b)
{
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

int32_t interpolate(RGB*** arr, double k, double b,
                    int64_t x_start, int64_t x_end, RGB color)
{
    int64_t y1, y2;
    for (size_t x = x_start; x < x_end; x++) {
        y1 = (int)(k * x + b);
        y2 = y2 + 1;
        (*arr)[x][y1].r = 0;
        (*arr)[x][y1].g = 0;
        (*arr)[x][y1].b = 0;

        (*arr)[x][y2].r = 0;
        (*arr)[x][y2].g = 0;
        (*arr)[x][y2].b = 0;
    }
    return NO_ERROR;
}

int32_t draw_line(RGB*** arr, const BitmapInfoHeader* bmih,
                  int64_t x0, int64_t y0, int64_t x1, int64_t y1,
                  const uint32_t thickness, RGB color)
{
    uint32_t W = bmih->width;
    uint32_t H = bmih->height;

    // 1. find line equation in format y = k*x + b
    double k = (double)(y0 - y1) / (x0 - x1);
    double b = (double)y0 - k * x0;

    // angle k of perpendicular to main line
    double k_p = -1 / k;
    // find b components of perpendiculars
    double b_p0 = (double)y0 - k_p * (double)x0;
    double b_p1 = (double)y1 - k_p * (double)x1;

    printf("Main line: {%ld <= x <= %ld} y = %lfx + %lf\n",
           x0, x1, k, b);
    printf("P1 line; y = %lfx + %lf\n", k_p, b_p0);
    printf("P2 line; y = %lfx + %lf\n", k_p, b_p1);

    // sqrt(dx^2 + dy^2) = 1 => dx = 1 / sqrt(1 + k_p^2)
    double target_move_x = 1 / sqrt(k_p * k_p);

    // now we need to move main line up and down to reach target thickness
    double max_move = target_move_x * ((double)thickness - 1) / 2;
    printf("Max move: %lf\n", max_move);

    for (double x0_cur = x0 - max_move; x0_cur < x0 + max_move; x0_cur += target_move_x) {
        double y0_cur = k_p * x0_cur + b_p0;
        printf("Point: (%lf, %lf)\n", x0_cur, y0_cur);

        double x_bias = x0_cur - x0;
        
        double x1_cur = x1 + x_bias;
        double b_cur = y0_cur - k * x0_cur;
        printf("Sub line: {%lf <= x <= %lf} y = %lfx + %lf\n",
               x0_cur, x1_cur, k, b_cur);
    }
    
    // 2.
    interpolate(arr, k, b, x0, x1, color);
    
    // x0 = clip(0, W, x0);
    // x1 = clip(0, W, x1);
    // y0 = clip(0, H, y0);
    // y1 = clip(0, H, y1);
    // vertical line
    // if (x0 == x1) {
    //     if (y0 > y1)
    //         swap_int(&y0, &y1);
    //     for (int32_t y = y0; y < y1; y++) {
    //         for (int32_t j = 0; j < thickness; j++) {
    //             if (H - y >= 0 && x0 - j >= 0 && x0 - j < W && H - y < H) {
    //                 fprintf(stdout, "DEBUG |%d|%d|\n", y, x0 -j);
    //                 (*arr)[y][x0 - j].r = 255; //*(color);
    //                 (*arr)[y][x0 - j].g = 0; //*(color + 1);
    //                 (*arr)[y][x0 - j].b = 255; //*(color + 2);
    //             }
    //         }
    //     }
    //     return NO_ERROR;
    // // horizontal line
    // } else if (y0 == y1) {
    //     if (x0 > x1)
    //         swap_int(&x0, &x1);
    //     for (int32_t x = x0; x < x1; x++) {
    //         for (int32_t j = 0; j < thickness; j++) {
    //             if (H - y0 + j >= 0 && x >= 0 && x < W && H - y0 + j < H) {
    //                 (*arr)[H - y0 + j][x].r = *(color);
    //                 (*arr)[H - y0 + j][x].g = *(color + 1);
    //                 (*arr)[H - y0 + j][x].b = *(color + 2);
    //             }
    //         }
    //     }
    //     return NO_ERROR;
    // } else {
    //     // sloping line
    //     return ARG_ERROR;
    // }
    return NO_ERROR;
}

int32_t square(RGB*** arr, const BitmapInfoHeader* bmih,
               int32_t* left_up, uint32_t side_size, uint32_t thickness,
               RGB color, RGB fill_color)
{
    
}

