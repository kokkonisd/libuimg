#ifndef __LIB_UIMG_IMG_H__
#define __LIB_UIMG_IMG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define VERSION 0.0.1


typedef enum {
    YUV444,
    YUV444p,
    YUV420p,
    RGB24,
    RGB565,
    RGB8,
    GRAYSCALE
} PixelFormat;


typedef struct {
    uint16_t width;
    uint16_t height;
    PixelFormat format;
    uint8_t * data;
} Image;


Image * create_image (uint16_t width, uint16_t height, PixelFormat format);
void destroy_image (Image * img);


#endif
