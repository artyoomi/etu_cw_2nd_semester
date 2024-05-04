#ifndef __BMP__
#define __BMP__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "exceptions.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;           // BMP file identifier
    uint32_t filesize;            // BMP filesize in bytes
    uint16_t reserved1;           // reserved space
    uint16_t reserved2;           //
    uint32_t pixel_arr_offset;    // offset (pixels array bytes offset)
} BitmapFileHeader;

typedef struct {
    uint32_t header_size;            // header size in bytes
    uint32_t width;                  // image width
    uint32_t height;                 // image height
    uint16_t planes;                 // count of color planes (m/b 1)
    uint16_t bits_per_pixel;         // color depth (1, 4, 8, 16, 24, 32)
    uint32_t compression;            // compression method 
    uint32_t image_size;             // image size
    uint32_t x_pixels_per_meter;     // horizontal resolution of image
    uint32_t y_pixels_per_meter;     // vertical resolution of image
    uint32_t colors_in_color_table;  // number of colors in the color palette
    uint32_t important_color_count;  // number of important colors, 0 if all colors is important
} BitmapInfoHeader;

// the color components are in reverse order since it is little-endian
typedef struct {
    uint8_t b;    // blue
    uint8_t g;    // green
    uint8_t r;    // red
} RGB;
#pragma pack(pop)

int32_t read_bmp(const char* file_name, RGB*** arr, 
                 BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);

int32_t write_bmp(const char* file_name, RGB*** arr, 
                  const BitmapFileHeader* bmfh, const BitmapInfoHeader* bmif);

void print_file_header(BitmapFileHeader bmfh);

void print_info_header(BitmapInfoHeader bmih);

#endif
