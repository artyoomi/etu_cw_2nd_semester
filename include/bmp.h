#ifndef __BMP__
#define __BMP__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "exceptions.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;           // идетификация файла BMP и DIB
    uint32_t filesize;            // размер BMP файла в байтах
    uint16_t reserved1;           // зарезервированное пространство
    uint16_t reserved2;           //
    uint32_t pixelArrOffset;        // смещение (нач. адрес байта где находится массив пикселей)
} BitmapFileHeader;

typedef struct {
    uint32_t headerSize;          // размер заголовка в байтах
    uint32_t width;               // ширина изображения в пикселях
    uint32_t height;              // длина изображения в пикселях
    uint16_t planes;              // количество цветовых пл-тей (д/б 1)
    uint16_t bitsPerPixel;        // глубина цвета изобр. (1, 4, 8, 16, 24, 32)
    uint32_t compression;         // метод сжатия 
    uint32_t imageSize;           // размер изображения
    uint32_t xPixelsPerMeter;     // гориз. разрешение изображения
    uint32_t yPixelsPerMeter;     // вертик. разреш. изображения
    uint32_t colorsInColorTable;  // кол-во цветов в цвет. палитре
    uint32_t importantColorCount; // кол-во важных цветов
} BitmapInfoHeader;

// thats little-endian.
typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} RGB;
#pragma pack(pop)

int32_t read_bmp(const char* file_name, RGB*** arr, 
                BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);
int32_t write_bmp(const char* file_name, RGB*** arr, 
                 const BitmapFileHeader* bmfh, const BitmapInfoHeader* bmif);

void print_file_header(BitmapFileHeader header);
void print_info_header(BitmapInfoHeader header);

#endif
