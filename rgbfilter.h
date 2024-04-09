#ifndef __RGBFILTER__
#define __RGBFILTER__

#include <stdint.h>
#include <string.h>

#include "bmp.h"
#include "exception.h"

uint8_t identify(const char*);
size_t rgbfilter(RGB***, const BitmapInfoHeader*, const char*, uint8_t);

#endif
