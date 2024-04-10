#ifndef __RGBFILTER__
#define __RGBFILTER__

#include <stdint.h>
#include <string.h>
#include <regex.h>

#include "bmp.h"
#include "exceptions.h"
#include "parse_funcs.h"

uint8_t identify(const char*);
int32_t rgbfilter(RGB***, const BitmapInfoHeader*, const char*, const uint8_t);

#endif
