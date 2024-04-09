#include "bmp.h"
#include "exception.h"

size_t read_bmp(const char* file_name, RGB*** arr, 
                BitmapFileHeader* bmfh, BitmapInfoHeader* bmif)
{
    // to do special logic
    FILE* fd = fopen(file_name, "rb");
    if (fd == NULL)
        return FOPN_ERROR;

    if (fread(bmfh, sizeof(BitmapFileHeader), 1, fd) != 1) {
        fclose(fd);
        return FRD_ERROR;
    }
    if (bmfh->signature != 0x4D42) {
         // exit from program with error
         fclose(fd);
         return WRONG_SIGNATURE;
    }   
  
    if (fread(bmif, sizeof(BitmapInfoHeader), 1, fd) != 1)  {
        fclose(fd);
        return FRD_ERROR;
    }

    // turn on after find image without compression and with 24-bit color
    if (bmif->bitsPerPixel != 24 
        || bmif->compression != 0 || bmif->colorsInColorTable != 0) {
        fclose(fd);
        return WRONG_BMP_FORMAT;
    }
    fseek(fd, bmfh->pixelArrOffset, SEEK_SET);

    uint32_t H = bmif->height;
    uint32_t W = bmif->width;
    uint64_t padded_width = W * sizeof(RGB) + W * sizeof(RGB) % 4;
    
    (*arr) = (RGB**)calloc(H, sizeof(RGB*));
    if (*arr == NULL) {
        fclose(fd);
        return MALLOC_ERROR;
    }
    for (size_t i = 0; i < H; i++) {
        (*arr)[i] = (RGB*)calloc(padded_width, 1);
        if ((*arr)[i] == NULL) {
            fclose(fd);
            return MALLOC_ERROR;
        }
        
        if (fread((*arr)[i], 1, padded_width, fd) < padded_width) {
            fclose(fd);
            return FRD_ERROR;
        }        
    }
    
    fclose(fd);
    printf("File was succesfully read!\n");
    
    return NO_ERROR;
}

size_t write_bmp(const char* file_name, RGB*** arr, 
                 const BitmapFileHeader* bmfh, const BitmapInfoHeader* bmih)
{
    int32_t H = bmih->height;
    int32_t W = bmih->width;
    uint64_t padded_width = W * sizeof(RGB) + W * sizeof(RGB) % 4;
    
    FILE* fd = fopen(file_name, "wb");
    if (fd == NULL)
        return FOPN_ERROR;
    
    if (fwrite(bmfh, sizeof(BitmapFileHeader), 1, fd) != 1) {
        fclose(fd);
        return FWRT_ERROR;
    }
    
    if (fwrite(bmih, sizeof(BitmapInfoHeader), 1, fd) != 1) {
        fclose(fd);
        return FWRT_ERROR;
    }

    fseek(fd, bmfh->pixelArrOffset, SEEK_SET);

    for (size_t i = 0; i < H; i++) {
        if (fwrite((*arr)[i], 1, padded_width, fd) < padded_width) {
            fclose(fd);
            return FWRT_ERROR;
        }
    }
    
    fclose(fd);
    printf("File was succesfully written!\n");
    
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
