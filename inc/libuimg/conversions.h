#ifndef __LIB_UIMG_CONVERSIONS_H__
#define __LIB_UIMG_CONVERSIONS_H__


#include <string.h>


#include "img.h"


/**
 * @brief      Convert a base image to a different format.
 * 
 * The conversions is static, meaning that the user has to have provided memory for the converted image.
 *
 * @param      base_img       The base image to be converted.
 * @param      converted_img  The converted image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_image (Image_t * base_img, Image_t * converted_img);


/**
 * @brief      Convert a base image to a different format.
 *
 * The conversion is dynamic, meaning that memory will be dynamically allocated for the converted image.
 *
 * @param      base_img  The base image to be converted.
 * @param[in]  format    The format to convert to.
 *
 * @return     The converted image if successful, NULL otherwise.
 */
Image_t * convert_dynamic_image (Image_t * base_img, PixelFormat_t format);


/**
 * @brief      Rescale a color value.
 * 
 * Maps a value from a range [old_min, old_max] to a range [new_min, new_max].
 *
 * @param[in]  value    The value to rescale.
 * @param[in]  old_min  The old minimum.
 * @param[in]  old_max  The old maximum.
 * @param[in]  new_min  The new minimum.
 * @param[in]  new_max  The new maximum.
 *
 * @return     The rescaled value.
 */
uint8_t rescale_color (uint8_t value, uint8_t old_min, uint8_t old_max, uint8_t new_min, uint8_t new_max);

/**
 * @brief      Convert YUV color to R (in RGB).
 *
 * @param[in]  y     The color's Y value.
 * @param[in]  u     The color's U value.
 * @param[in]  v     The color's V value.
 *
 * @return     The R component of the converted color.
 */
uint8_t yuv_to_rgb_r (uint8_t y, uint8_t u, uint8_t v);

/**
 * @brief      Convert YUV color to G (in RGB).
 *
 * @param[in]  y     The color's Y value.
 * @param[in]  u     The color's U value.
 * @param[in]  v     The color's V value.
 *
 * @return     The R component of the converted color.
 */
uint8_t yuv_to_rgb_g (uint8_t y, uint8_t u, uint8_t v);

/**
 * @brief      Convert YUV color to B (in RGB).
 *
 * @param[in]  y     The color's Y value.
 * @param[in]  u     The color's U value.
 * @param[in]  v     The color's V value.
 *
 * @return     The B component of the converted color.
 */
uint8_t yuv_to_rgb_b (uint8_t y, uint8_t u, uint8_t v);

/**
 * @brief      Convert RGB color to Y (in YUV).
 *
 * @param[in]  r     The color's R value.
 * @param[in]  g     The color's G value.
 * @param[in]  b     The color's B value.
 *
 * @return     The Y component of the converted color.
 */
uint8_t rgb_to_yuv_y (uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief      Convert RGB color to U (in YUV).
 *
 * @param[in]  r     The color's R value.
 * @param[in]  g     The color's G value.
 * @param[in]  b     The color's B value.
 *
 * @return     The U component of the converted color.
 */
uint8_t rgb_to_yuv_u (uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief      Convert RGB color to V (in YUV).
 *
 * @param[in]  r     The color's R value.
 * @param[in]  g     The color's G value.
 * @param[in]  b     The color's B value.
 *
 * @return     The V component of the converted color.
 */
uint8_t rgb_to_yuv_v (uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief      Convert Y (grayscale) color to ASCII characters.
 *
 * @param[in]  y     The Y color to convert.
 *
 * @return     An ASCII character corresponding to the Y color.
 */
uint8_t y_to_ascii (uint8_t y);


/**
 * @brief      Convert a YUV444 image to a YUV444p image.
 * 
 * This conversion is lossless; both formats use the same number of bits-per-pixel.
 *
 * @param      img_yuv444   The YUV444 image to convert.
 * @param      img_yuv444p  The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_YUV444p (Image_t * img_yuv444, Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444 image to a YUV420p image.
 * 
 * This conversion is lossy, as YUV420p uses less bits-per-pixel than YUV444; however, by the nature of the Y-U-V color
 * format, the loss is barely noticeable to the human eye.
 *
 * @param      img_yuv444   The YUV444 image to convert.
 * @param      img_yuv420p  The converted YUV420p image.
 * 
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_YUV420p (Image_t * img_yuv444, Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV444 image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 * @param      img_rgb24   The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_RGB24 (Image_t * img_yuv444, Image_t * img_rgb24);

/**
 * @brief      Convert a YUV444 image to an RGB565 image.
 * 
 * This conversion is lossy; RGB565 uses less bits-per-pixel than YUV444, and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 * @param      img_rgb565  The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_RGB565 (Image_t * img_yuv444, Image_t * img_rgb565);

/**
 * @brief      Convert a YUV444 image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel than YUV444, and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 * @param      img_rgb8    The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_RGB8 (Image_t * img_yuv444, Image_t * img_rgb8);

/**
 * @brief      Convert a YUV444 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv444     The YUV444 image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_GRAYSCALE (Image_t * img_yuv444, Image_t * img_grayscale);

/**
 * @brief      Convert a YUV444 image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444_to_ASCII (Image_t * img_yuv444, Image_t * img_ascii);


/**
 * @brief      Convert a YUV444p image to a YUV444 image.
 * 
 * This conversion is lossless; both formats use the same number of bits-per-pixel.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 * @param      img_yuv444   The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_YUV444 (Image_t * img_yuv444p, Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444p image to a YUV420p image.
 * 
 * This conversion is lossy, as YUV420p uses less bits-per-pixel than YUV444p; however, due to the nature of the Y-U-V
 * format, the loss is barely noticeable to the human eye.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 * @param      img_yuv420p  The converted YUV420p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_YUV420p (Image_t * img_yuv444p, Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV444p image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 * @param      img_rgb24    The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_RGB24 (Image_t * img_yuv444p, Image_t * img_rgb24);

/**
 * @brief      Convert a YUV444p image to an RGB565 image.
 * 
 * This conversion is lossy; RGB565 uses less bits-per-pixel than YUV444p and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 * @param      img_rgb565   The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_RGB565 (Image_t * img_yuv444p, Image_t * img_rgb565);

/**
 * @brief      Convert a YUV444p image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel than YUV444p and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 * @param      img_rgb8     The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_RGB8 (Image_t * img_yuv444p, Image_t * img_rgb8);

/**
 * @brief      Convert a YUV444p image to a GRAYSCALE image.
 * 
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv444p    The YUV444p image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_GRAYSCALE (Image_t * img_yuv444p, Image_t * img_grayscale);

/**
 * @brief      Convert a YUV444p image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The YUV444p image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV444p_to_ASCII (Image_t * img_yuv444p, Image_t * img_ascii);


/**
 * @brief      Convert a YUV420p image to a YUV444 image.
 * 
 * This conversion is lossless; however, there is some upsampling since the YUV444 format uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 * @param      img_yuv444   The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_YUV444 (Image_t * img_yuv420p, Image_t * img_yuv444);

/**
 * @brief      Convert a YUV420p image to a YUV444p image.
 * 
 * This conversion is lossless; however, there is some upsampling since the YUV444p format uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 * @param      img_yuv444p  The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_YUV444p (Image_t * img_yuv420p, Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV420p image to an RGB24 image.
 * 
 * This conversion is lossy, since the YUV->RGB conversion is nonlinear. It also uses upsampling since the RGB24 image
 * uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 * @param      img_rgb24    The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_RGB24 (Image_t * img_yuv420p, Image_t * img_rgb24);

/**
 * @brief      Convert a YUV420p image to an RGB565 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 * @param      img_rgb565   The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_RGB565 (Image_t * img_yuv420p, Image_t * img_rgb565);

/**
 * @brief      Convert a YUV420p image to an RGB8 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear and RGB8 uses less bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 * @param      img_rgb8     The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_RGB8 (Image_t * img_yuv420p, Image_t * img_rgb8);

/**
 * @brief      Convert a YUV420p image to a GRAYSCALE image.
 * 
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv420p    The YUV420p image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_GRAYSCALE (Image_t * img_yuv420p, Image_t * img_grayscale);

/**
 * @brief      Convert a YUV420p image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The YUV420p image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_YUV420p_to_ASCII (Image_t * img_yuv420p, Image_t * img_ascii);


/**
 * @brief      Convert an RGB24 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb24   The RGB24 image to convert.
 * @param      img_yuv444  The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_YUV444 (Image_t * img_rgb24, Image_t * img_yuv444);

/**
 * @brief      Convert an RGB24 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb24    The RGB24 image to convert.
 * @param      img_yuv444p  The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_YUV444p (Image_t * img_rgb24, Image_t * img_yuv444p);

/**
 * @brief      Convert an RGB24 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and the YUV420p format uses less bits-per-pixel.
 *
 * @param      img_rgb24    The RGB24 image to convert.
 * @param      img_yuv420p  The converted YUV420p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_YUV420p (Image_t * img_rgb24, Image_t * img_yuv420p);

/**
 * @brief      Convert an RGB24 image to an RGB565 image.
 * 
 * This conversion is lossy; the RGB565 format uses less bits-per-pixel.
 *
 * @param      img_rgb24   The RGB24 image to convert.
 * @param      img_rgb565  The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_RGB565 (Image_t * img_rgb24, Image_t * img_rgb565);

/**
 * @brief      Convert an RGB24 image to an RGB8 image.
 * 
 * This conversion is lossy; the RGB8 format uses less bits-per-pixel.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 * @param      img_rgb8   The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_RGB8 (Image_t * img_rgb24, Image_t * img_rgb8);

/**
 * @brief      Convert an RGB24 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and the GRAYSCALE format uses less bits-per-pixel.
 *
 * @param      img_rgb24      The RGB24 image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_GRAYSCALE (Image_t * img_rgb24, Image_t * img_grayscale);

/**
 * @brief      Convert a RGB24 image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The RGB24 image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB24_to_ASCII (Image_t * img_rgb24, Image_t * img_ascii);


/**
 * @brief      Convert an RGB565 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 * @param      img_yuv444  The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_YUV444 (Image_t * img_rgb565, Image_t * img_yuv444);

/**
 * @brief      Convert an RGB565 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565   The RGB565 image to convert.
 * @param      img_yuv444p  The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_YUV444p (Image_t * img_rgb565, Image_t * img_yuv444p);

/**
 * @brief      Convert an RGB565 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565   The RGB565 image to convert.
 * @param      img_yuv420p  The converted YUV420p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_YUV420p (Image_t * img_rgb565, Image_t * img_yuv420p);

/**
 * @brief      Convert an RGB565 image to an RGB24 image.
 * 
 * This conversion is lossless; RGB565 uses less bits-per-pixel than RGB24.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 * @param      img_rgb24   The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_RGB24 (Image_t * img_rgb565, Image_t * img_rgb24);

/**
 * @brief      Convert an RGB565 image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 * @param      img_rgb8    The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_RGB8 (Image_t * img_rgb565, Image_t * img_rgb8);

/**
 * @brief      Convert an RGB565 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and GRAYSCALE uses less bits-per-pixel.
 *
 * @param      img_rgb565     The RGB565 image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_GRAYSCALE (Image_t * img_rgb565, Image_t * img_grayscale);

/**
 * @brief      Convert a RGB565 image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The RGB565 image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB565_to_ASCII (Image_t * img_rgb565, Image_t * img_ascii);


/**
 * @brief      Convert an RGB8 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8    The RGB8 image to convert.
 * @param      img_yuv444  The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_YUV444 (Image_t * img_rgb8, Image_t * img_yuv444);

/**
 * @brief      Convert an RGB8 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8     The RGB8 image to convert.
 * @param      img_yuv444p  The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_YUV444p (Image_t * img_rgb8, Image_t * img_yuv444p);

/**
 * @brief      Convert an RGB8 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8     The RGB8 image to convert.
 * @param      img_yuv420p  The converted YUV420p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_YUV420p (Image_t * img_rgb8, Image_t * img_yuv420p);

/**
 * @brief      Convert an RGB8 image to an RGB24 image.
 * 
 * This conversion is lossless; RGB8 uses less bits-per-pixel than RGB24.
 *
 * @param      img_rgb8   The RGB8 image to convert.
 * @param      img_rgb24  The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_RGB24 (Image_t * img_rgb8, Image_t * img_rgb24);

/**
 * @brief      Convert an RGB8 image to an RGB565 image.
 * 
 * This conversion is lossless; RGB8 uses less bits-per-pixel than RGB565.
 *
 * @param      img_rgb8    The RGB8 image to convert.
 * @param      img_rgb565  The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_RGB565 (Image_t * img_rgb8, Image_t * img_rgb565);

/**
 * @brief      Convert an RGB8 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8       The RGB8 image to convert.
 * @param      img_grayscale  The converted GRAYSCALE image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_GRAYSCALE (Image_t * img_rgb8, Image_t * img_grayscale);

/**
 * @brief      Convert a RGB8 image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The RGB8 image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_RGB8_to_ASCII (Image_t * img_rgb8, Image_t * img_ascii);


/**
 * @brief      Convert a GRAYSCALE image to a YUV444 image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV444.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_yuv444     The converted YUV444 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_YUV444 (Image_t * img_grayscale, Image_t * img_yuv444);

/**
 * @brief      Convert a GRAYSCALE image to a YUV444p image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV444p.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_yuv444p    The converted YUV444p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_YUV444p (Image_t * img_grayscale, Image_t * img_yuv444p);

/**
 * @brief      Convert a GRAYSCALE image to a YUV420p image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV420p.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_yuv420p    The converted YUV420p image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_YUV420p (Image_t * img_grayscale, Image_t * img_yuv420p);

/**
 * @brief      Convert a GRAYSCALE image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_rgb24      The converted RGB24 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_RGB24 (Image_t * img_grayscale, Image_t * img_rgb24);

/**
 * @brief      Convert a GRAYSCALE image to an RGB565 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_rgb565     The converted RGB565 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_RGB565 (Image_t * img_grayscale, Image_t * img_rgb565);

/**
 * @brief      Convert a GRAYSCALE image to an RGB8 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 * @param      img_rgb8       The converted RGB8 image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_RGB8 (Image_t * img_grayscale, Image_t * img_rgb8);

/**
 * @brief      Convert a GRAYSCALE image to an ASCII image.
 * 
 * The ASCII format can be used to debug images in embedded applications where a screen isn't available. The user can
 * convert the image to ASCII characters and dump the resulting image via UART.
 *
 * @param      img_yuv444  The GRAYSCALE image to convert.
 * @param      img_ascii   The converted ASCII image.
 *
 * @return     1 if successful, 0 otherwise.
 */
uint8_t convert_GRAYSCALE_to_ASCII (Image_t * img_grayscale, Image_t * img_ascii);


#endif
