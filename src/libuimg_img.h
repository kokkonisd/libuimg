#ifndef __LIB_UIMG_IMG_H__
#define __LIB_UIMG_IMG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define UROUND_UP(x) (((uint32_t) (x)) < ((float) x) ? ((uint32_t) (x)) + 1 : ((uint32_t) (x)))


typedef enum {
    YUV444,
    YUV444p,
    YUV420p,
    RGB24,
    RGB565,
    RGB8,
    GRAYSCALE
} PixelFormat_t;


typedef struct {
    uint16_t width;
    uint16_t height;
    PixelFormat_t format;
    uint8_t * data;
} Image_t;


Image_t * create_image (uint16_t width, uint16_t height, PixelFormat_t format);
void destroy_image (Image_t * img);


#endif
