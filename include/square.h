#ifndef __SQUARE__
#define __SQUARE__

#include <stdint.h>

#include "bmp.h"
#include "exceptions.h"

int32_t draw_line(RGB***, const BitmapInfoHeader*,
                  int32_t, int32_t, int32_t, int32_t, 
                  uint32_t, uint8_t*);

int32_t square(RGB***, const BitmapInfoHeader*, 
               int32_t*, uint32_t, uint32_t, uint8_t*, uint8_t*);

#endif
