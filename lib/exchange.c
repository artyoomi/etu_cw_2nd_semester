#include "../include/exchange.h"

int32_t exchange(RGB ***arr, const BitmapInfoHeader *bmih,
                 int64_t *left_up, int64_t *right_down,
                 char *exchange_type)
{
    uint32_t W = bmih->width;
    uint32_t H = bmih->height;    
    
    int64_t x0 = left_up[0];
    int64_t y0 = left_up[1];
    int64_t x1 = right_down[0];
    int64_t y1 = right_down[1];

    // add check to linelike area

    // standarize points
    if (x0 > x1)
        swap_int64(&x0, &x1);
    if (y0 > y1)
        swap_int64(&y0, &y1);     

    // add all sorts of checks
    /*// if this if is true, then area outside of picture
    if ((x1 < 0 || x0 > W) || 
        (y1 > H || y0 < 0))
        return NO_ERROR;

    if (x0 < 0 && x1 > 0)
        x0 = 0;
    if (x1 > W && x0 < H - 1)*/

    RGB **tmp_arr;

    if (!strcmp(exchange_type, "clockwise")) {
        
    }

    free(tmp_arr);

    return NO_ERROR;
}
