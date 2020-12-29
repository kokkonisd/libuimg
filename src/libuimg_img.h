#ifndef __LIB_UIMG_IMG_H__
#define __LIB_UIMG_IMG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * @brief      Round up an unsigned number.
 * 
 * This macro should function like `ceil()` for unsigned numbers.
 *
 * @param      x     An unsigned (floating point or integer) number to round up.
 *
 * @return     The rounded unsigned integer.
 */
#define UROUND_UP(x) (((uint32_t) (x)) < ((float) x) ? ((uint32_t) (x)) + 1 : ((uint32_t) (x)))


/**
 * @brief Enumeration of the currently supported pixel formats.
 * 
 * The pixel formats currently supported by libuimg have as follows:
 * 
 * YUV444, packed, 24bpp
 * YUV444p, planar, 24bpp
 * YUV420p, planar, 12bpp
 * RGB24, packed, 24bpp
 * RGB565, packed, 16bpp
 * RGB8, packed, 8bpp
 * GRAYSCALE, packed/planar, 8bpp
 */
typedef enum {
    YUV444,
    YUV444p,
    YUV420p,
    RGB24,
    RGB565,
    RGB8,
    GRAYSCALE
} PixelFormat_t;


/**
 * @brief The Image structure.
 * 
 * This structure holds all of the relevant info corresponding to an image.
 */
typedef struct {
    /** The width of the image (in pixels). */
    uint16_t width;
    /** The height of the image (in pixels). */
    uint16_t height;
    /** The pixel format of the image. */
    PixelFormat_t format;
    /** The pixel data of the image. */
    uint8_t * data;
} Image_t;


/**
 * @brief      Create an image.
 * 
 * Dynamically allocates memory for the image struct itself as well as the image data (based on the pixel format).
 *
 * @param[in]  width   The width of the image (in pixels).
 * @param[in]  height  The height of the image (in pixels).
 * @param[in]  format  The pixel format of the image.
 *
 * @return     The created image.
 */
Image_t * create_image (uint16_t width, uint16_t height, PixelFormat_t format);

/**
 * @brief      Destroy an image.
 * 
 * Frees the memory of the image data and of the image struct itself.
 *
 * @param      img   The image to destroy.
 */
void destroy_image (Image_t * img);


#endif
