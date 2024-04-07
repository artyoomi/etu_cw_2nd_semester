#include "bmp.h"
#include "exception.h"

/*void chk_frd_fwrt_err(size_t ret, const char* msg, 
                      uint32_t line, const char* func_name, 
                      FILE* fd, const size_t size)
{
    if (ret < size) {
        fprintf(stderr, "%d: %s: %s\n", line, func_name, msg);
        fclose(fd);
        exit(EXIT_FAILURE);
    }
}*/

size_t read_bmp(RGB*** arr, const char* file_name, 
                BitmapFileHeader* bmfh, BitmapInfoHeader* bmif)
{
    // to do special logic
    FILE* fd = fopen(file_name, "rb");
    if (fd == NULL)
        return FOPN_ERROR;

    if (fread(bmfh, 1, sizeof(BitmapFileHeader), fd) 
        < sizeof(BitmapFileHeader)) {
        fclose(fd);
        return FRD_ERROR;
    }
    //chk_frd_fwrt_err(ret, "Error while read BMP header\n", 
    //                 __LINE__, __FUNCTION__, fd, sizeof(BitmapFileHeader));
    if (bmfh->signature != 0x4D42) {
         // exit from program with error
         fclose(fd);
         return WRONG_SIGNATURE;
    }   
    
    /*if (ret < sizeof(BitmapFileHeader)) {
        fprintf(stderr, "%d: %s: Error while read BMP header\n", 
                __LINE__, __FUNCTION__);
        fclose(fd);
        exit(EXIT_FAILURE);
    }*/
    if (fread(bmif, 1, sizeof(BitmapInfoHeader), fd) 
        < sizeof(BitmapInfoHeader)) {
        fclose(fd);
        return FRD_ERROR;
    }

    if (bmif->bitsPerPixel != 24 || bmif->compression != 0) {
        fclose(fd);
        return WRONG_BMP_FORMAT;
    }
    //chk_frd_fwrt_err(ret, "Error while read BMP header info\n",
    //              __LINE__, __FUNCTION__, fd, sizeof(BitmapInfoHeader));
    /*if (ret < sizeof(BitmapInfoHeader)) {
        fprintf(stderr, "%d: %s: Error while read BMP header info\n", 
                __LINE__, __FUNCTION__);
        fclose(fd);
        exit(EXIT_FAILURE);
    }*/
    
    uint16_t H = bmif->height;
    uint16_t W = bmif->width;
    
    *arr = (RGB**)malloc(H * sizeof(RGB*));
    if (*arr == NULL) {
        fclose(fd);
        return MALLOC_ERROR;
    }

    for (size_t i = 0; i < H; i++) {
        (*arr)[i] = (RGB*)malloc(W * sizeof(RGB) + (W * 3) % 4);
        if ((*arr)[i] == NULL) {
            fclose(fd);
            return MALLOC_ERROR;
        }
        if (fread((*arr)[i], 1, W * sizeof(RGB) + (W * 3) % 4, fd)
            < W * sizeof(RGB) + (W * 3) % 4) {
            fclose(fd);
            return FRD_ERROR;
        }        
        //chk_frd_fwrt_err(ret, "Error while read pixels line",
        //                 __LINE__, __FUNCTION__, 
        //                 fd, W * sizeof(RGB) + (W * 3) % 4);
        /*if (ret < W * sizeof(RGB) + (W * 3) % 4) {
            
        }*/
    }
    
    fclose(fd);
    return NO_ERROR;
}

size_t write_bmp(const char* file_name, RGB** arr, 
               int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif)
{
    FILE* fd = fopen(file_name, "wb");
    if (fd == NULL)
        return FOPN_ERROR;
    if (fwrite(&bmfh, 1, sizeof(BitmapFileHeader), fd)
        < sizeof(BitmapFileHeader)) {
        fclose(fd);
        return FWRT_ERROR;
    }
    //chk_frd_fwrt_err(ret, "Error while write BMP header in file\n",
    //                 __LINE__, __FUNCTION__, fd, 
    //                 sizeof(BitmapFileHeader));
    if (fwrite(&bmif, 1, sizeof(BitmapInfoHeader), fd)
        < sizeof(BitmapInfoHeader)) {
        fclose(fd);
        return FWRT_ERROR;
    }
    //chk_frd_fwrt_err(ret, "Error while write BMP header info in file\n",
    //                 __LINE__, __FUNCTION__, fd, 
    //                 sizeof(BitmapFileHeader));
    for (size_t i = 0; i < H; i++) {
        if (fwrite(arr[i], 1, W * sizeof(RGB) + (W * 3) % 4, fd)
            < W * sizeof(RGB) + (W * 3) % 4) {
            fclose(fd);
            return FWRT_ERROR;
        }
        //chk_frd_fwrt_err(ret, "Error while write pixels array in file\n",
        //                 __LINE__, __FUNCTION__, fd,
        //                 W * sizeof(RGB) + (W * 3) % 4);
    }
    fclose(fd);
    return NO_ERROR;
}

void print_file_header(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header) 
{
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:\t%x (%u)\n", header.width, header.width);
    printf("height:\t%x (%u)\n", header.height, header.height);
    printf("planes:\t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}
