#ifndef __FREQ_COLOR__
#define __FREQ_COLOR__

#include <stdint.h>

#include "bmp.h"
#include "dictionary.h"
#include "exceptions.h"

int32_t freq_color(RGB*** arr, const BitmapInfoHeader *bmih, RGB color);

#endif
