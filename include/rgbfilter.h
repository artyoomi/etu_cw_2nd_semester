#ifndef __RGBFILTER__
#define __RGBFILTER__

#include <stdint.h>
#include <string.h>
#include <regex.h>

#include "bmp.h"
#include "exceptions.h"
#include "parse_funcs.h"

uint8_t identify(const char*);
int32_t rgbfilter(RGB*** arr,
                  const char* compt_name, const uint8_t compt_val,
                  uint32_t H, uint32_t W);

#endif
