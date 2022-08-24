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
 * @brief      Determine if a given pixel format is valid.
 *
 * @param      format  The pixel format to check.
 *
 * @return     1 if the format is valid, 0 otherwise.
 */
#define IS_VALID_PIXEL_FORMAT(format) ((format) >= YUV444 && (format) <= ASCII)


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
    GRAYSCALE,
    ASCII
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

/**
 * @brief      Save an image to a (binary) file.
 *
 * The following elements are saved in the binary file, in order: width, height, pixel
 * format, raw image data.
 *
 * @param[in]  img       The image to save.
 * @param[in]  filepath  The path to the file where the image should be saved.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t save_image (Image_t * img, const char * filepath);

/**
 * @brief      Load an image from a (binary) file.
 *
 * An image will be created by this function, and it has to be freed later; if you wish
 * to not use any dynamic allocations, use `load_static_image` instead.
 *
 * @param[in]  filepath  The path to the file where the image should be loaded from.
 *
 * @return     The loaded image structure if successful, NULL otherwise.
 */
Image_t * load_image (const char * filepath);

/**
 * @brief      Load an image from a (binary) file statically (without any allocations).
 *
 * The img parameter passed to this function should already be initialized correctly
 * as no allocations will be performed; we expect the data buffer to be large enough to
 * contain what is going to be loaded from the image file.
 *
 * @param[in]  img       The image structure to load to.
 * @param[in]  filepath  The path to the file where the image should be loaded from.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t load_static_image (Image_t * img, const char * filepath);

/**
 * @brief      Get the size (in bytes) of the raw pixel data required for an image.
 *
 * @param[in]  width   The width of the image.
 * @param[in]  height  The height of the image.
 * @param[in]  format  The pixel format of the image.
 *
 * @return     The size (in bytes) of the raw pixel data.
 */
uint32_t get_image_data_size (uint16_t width, uint16_t height, PixelFormat_t format);


#endif
