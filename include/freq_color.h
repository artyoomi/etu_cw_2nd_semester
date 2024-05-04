#ifndef __FREQ_COLOR__
#define __FREQ_COLOR__

#include <stdint.h>

#include "bmp.h"
#include "exceptions.h"

void freq_color(RGB*** arr, RGB color, uint32_t H, uint32_t W);

#endif
