#ifndef __EXCHANGE__
#define __EXCHANGE__

#include <stdint.h>
#include <string.h>

#include "bmp.h"
#include "exceptions.h"
#include "etc.h"

int32_t exchange(RGB ***arr, const BitmapInfoHeader *bmih, 
                 int64_t *left_up, int64_t *right_down,
                 char *exchange_type);

#endif
