#ifndef __LIB_UIMG_TRANSFORMATIONS_H__
#define __LIB_UIMG_TRANSFORMATIONS_H__


#include "libuimg_img.h"


/**
 * @brief      Flip an image along the Y axis.
 *
 * @param      img   The image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_image (Image_t * img);


/**
 * @brief      Flip a YUV444 image along the Y axis.
 *
 * @param      img_yuv444  The YUV444 image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_YUV444 (Image_t * img_yuv444);

/**
 * @brief      Flip a YUV444p image along the Y axis.
 *
 * @param      img_yuv444p  The YUV444p image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_YUV444p (Image_t * img_yuv444p);

/**
 * @brief      Flip a YUV420p image along the Y axis.
 *
 * @param      img_yuv420p  The YUV420p image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_YUV420p (Image_t * img_yuv420p);

/**
 * @brief      Flip a RGB24 image along the Y axis.
 *
 * @param      img_rgb24  The RGB24 image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_RGB24 (Image_t * img_rgb24);

/**
 * @brief      Flip a RGB565 image along the Y axis.
 *
 * @param      img_rgb565  The RGB565 image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_RGB565 (Image_t * img_rgb565);

/**
 * @brief      Flip a RGB8 image along the Y axis.
 *
 * @param      img_rgb8  The RGB8 image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_RGB8 (Image_t * img_rgb8);

/**
 * @brief      Flip a GRAYSCALE image along the Y axis.
 *
 * @param      img_grayscale  The GRAYSCALE image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_GRAYSCALE (Image_t * img_grayscale);

/**
 * @brief      Flip a ASCII image along the Y axis.
 *
 * @param      img_ascii  The ASCII image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_ASCII (Image_t * img_ascii);


/**
 * @brief      Flip a 24-bits-per-pixel packed image along the Y axis.
 *
 * @param      img   The packed 24-bpp image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_24bpp (Image_t * img);

/**
 * @brief      Flip an 8-bits-per-pixel image along the Y axis.
 *
 * @param      img   The 8-bpp image to flip.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t flipY_8bpp (Image_t * img);


#endif
