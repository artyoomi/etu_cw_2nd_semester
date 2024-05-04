#include "../include/bmp.h"

int32_t read_bmp(const char* file_name, RGB*** arr,
                 BitmapFileHeader* bmfh, BitmapInfoHeader* bmif)
{
    // to do special logic
    FILE* fd = fopen(file_name, "rb");
    if (fd == NULL) {
        error_return_warg("The %s file was not open\n", IO_ERROR, file_name);
    }

    // simplified verification form
    if (!fread(bmfh, sizeof(BitmapFileHeader), 1, fd)) {
        error_return_wfd("BitmapFileHeader was no read\n",
                         BMP_FORMAT_ERROR, fd);
    }
    if (bmfh->signature != 0x4D42) {
         // exit from program with error
         error_return_wfd("BMP file signature doesn't match BM\n",
                          BMP_FORMAT_ERROR, fd);
    }  

    // simplified verification form
    if (!fread(bmif, sizeof(BitmapInfoHeader), 1, fd))  {
        error_return_wfd("BitmapInfoHeader was no read\n",
                         IO_ERROR, fd);
    }

    // turn on after find image without compression and with 24-bit color
    if (bmif->bits_per_pixel != 24 || bmif->compression != 0) {
        error_return_wfd("This program can't process BMP image like this\n",
                         BMP_FORMAT_ERROR, fd);
    }
    fseek(fd, bmfh->pixel_arr_offset, SEEK_SET);

    uint32_t H = bmif->height;
    uint32_t W = bmif->width;
    
    uint64_t padded_width = W * sizeof(RGB) + (4 - W * sizeof(RGB) % 4) % 4;
    
    (*arr) = (RGB**)calloc(H, sizeof(RGB*));
    if ((*arr) == NULL) {
        error_return_wfd("Allocating memory to pixels array lines return NULL",
                         ALLOC_ERROR, fd);
    }
    for (int64_t i = 0; i < H; i++) {
        (*arr)[i] = (RGB*)calloc(padded_width, 1);
        if ((*arr)[i] == NULL)
            error_return_wfd("Allocating memory to pixels array line return NULL\n",
                             ALLOC_ERROR, fd);

        fread((*arr)[i], padded_width, 1, fd);
    }
    
    fclose(fd);
    printf("File was succesfully read!\n");
    
    return NO_ERROR;
}

int32_t write_bmp(const char* file_name, RGB*** arr, 
                  const BitmapFileHeader* bmfh,
                  const BitmapInfoHeader* bmih)
{
    int32_t H = bmih->height;
    int32_t W = bmih->width;
    uint64_t padded_width = W * sizeof(RGB) + (4 - W * sizeof(RGB) % 4) % 4;
    
    FILE* fd = fopen(file_name, "wb");
    if (fd == NULL) {
        error_return_warg("This %s file was not open\n",
                          IO_ERROR, file_name);
    }
    
    if (fwrite(bmfh, sizeof(BitmapFileHeader), 1, fd) != 1) {
        error_return_wfd("BitmapFileHeader was not written\n", IO_ERROR, fd);
    }
    
    if (fwrite(bmih, sizeof(BitmapInfoHeader), 1, fd) != 1) {
        error_return_wfd("BitmapInfoHeader was not written\n", IO_ERROR, fd);
    }

    fseek(fd, bmfh->pixel_arr_offset, SEEK_SET);

    for (int64_t i = 0; i < H; i++)
        fwrite((*arr)[i], padded_width, 1, fd);
    
    fclose(fd);
    printf("File was succesfully written!\n");
    
    return NO_ERROR;
}

void print_file_header(BitmapFileHeader bmfh)
{
    printf("signature:\t%x (%hu)\n", bmfh.signature, bmfh.signature);
    printf("filesize:\t%x (%u)\n", bmfh.filesize, bmfh.filesize);
    printf("reserved1:\t%x (%hu)\n", bmfh.reserved1, bmfh.reserved1);
    printf("reserved2:\t%x (%hu)\n", bmfh.reserved2, bmfh.reserved2);
    printf("pixel_arr_offset:\t%x (%u)\n",
           bmfh.pixel_arr_offset, bmfh.pixel_arr_offset);
}

void print_info_header(BitmapInfoHeader bmih) 
{
    printf("header_size:\t%x (%u)\n", bmih.header_size, bmih.header_size);
    printf("width:\t%x (%u)\n", bmih.width, bmih.width);
    printf("height:\t%x (%u)\n", bmih.height, bmih.height);
    printf("planes:\t%x (%hu)\n", bmih.planes, bmih.planes);
    printf("bits_per_pixel:\t%x (%hu)\n",
           bmih.bits_per_pixel, bmih.bits_per_pixel);
    printf("compression:\t%x (%u)\n", bmih.compression, bmih.compression);
    printf("image_size:\t%x (%u)\n", bmih.image_size, bmih.image_size);
    printf("x_pixels_per_meter:\t%x (%u)\n",
           bmih.x_pixels_per_meter, bmih.x_pixels_per_meter);
    printf("y_pixels_per_meter:\t%x (%u)\n",
           bmih.y_pixels_per_meter, bmih.y_pixels_per_meter);
    printf("colors_in_color_table:\t%x (%u)\n",
           bmih.colors_in_color_table, bmih.colors_in_color_table);
    printf("important_color_count:\t%x (%u)\n",
           bmih.important_color_count, bmih.important_color_count);
}
