#ifndef __LIB_UIMG_CONVERSIONS_H__
#define __LIB_UIMG_CONVERSIONS_H__


#include <string.h>


#include "libuimg_img.h"


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
 * @brief      Convert a YUV444 image to a YUV444p image.
 * 
 * This conversion is lossless; both formats use the same number of bits-per-pixel.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_YUV444_to_YUV444p (Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444 image to a YUV420p image.
 * 
 * This conversion is lossy, as YUV420p uses less bits-per-pixel than YUV444; however, by the nature of the Y-U-V color
 * format, the loss is barely noticeable to the human eye.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_YUV444_to_YUV420p (Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444 image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_YUV444_to_RGB24 (Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444 image to an RGB565 image.
 * 
 * This conversion is lossy; RGB565 uses less bits-per-pixel than YUV444, and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_YUV444_to_RGB565 (Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444 image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel than YUV444, and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_YUV444_to_RGB8 (Image_t * img_yuv444);

/**
 * @brief      Convert a YUV444 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv444  The YUV444 image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_YUV444_to_GRAYSCALE (Image_t * img_yuv444);


/**
 * @brief      Convert a YUV444p image to a YUV444 image.
 * 
 * This conversion is lossless; both formats use the same number of bits-per-pixel.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_YUV444p_to_YUV444 (Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444p image to a YUV420p image.
 * 
 * This conversion is lossy, as YUV420p uses less bits-per-pixel than YUV444p; however, due to the nature of the Y-U-V
 * format, the loss is barely noticeable to the human eye.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_YUV444p_to_YUV420p (Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444p image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_YUV444p_to_RGB24 (Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444p image to an RGB565 image.
 * 
 * This conversion is lossy; RGB565 uses less bits-per-pixel than YUV444p and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_YUV444p_to_RGB565 (Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444p image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel than YUV444p and the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_YUV444p_to_RGB8 (Image_t * img_yuv444p);

/**
 * @brief      Convert a YUV444p image to a GRAYSCALE image.
 * 
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv444p  The YUV444p image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_YUV444p_to_GRAYSCALE (Image_t * img_yuv444p);


/**
 * @brief      Convert a YUV420p image to a YUV444 image.
 * 
 * This conversion is lossless; however, there is some upsampling since the YUV444 format uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_YUV420p_to_YUV444 (Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV420p image to a YUV444p image.
 * 
 * This conversion is lossless; however, there is some upsampling since the YUV444p format uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_YUV420p_to_YUV444p (Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV420p image to an RGB24 image.
 * 
 * This conversion is lossy, since the YUV->RGB conversion is nonlinear. It also uses upsampling since the RGB24 image
 * uses more bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_YUV420p_to_RGB24 (Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV420p image to an RGB565 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_YUV420p_to_RGB565 (Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV420p image to an RGB8 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear and RGB8 uses less bits-per-pixel.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_YUV420p_to_RGB8 (Image_t * img_yuv420p);

/**
 * @brief      Convert a YUV420p image to a GRAYSCALE image.
 *
 * This conversion is lossy; only the Y channel is kept in the GRAYSCALE image.
 *
 * @param      img_yuv420p  The YUV420p image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_YUV420p_to_GRAYSCALE (Image_t * img_yuv420p);


/**
 * @brief      Convert an RGB24 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_RGB24_to_YUV444 (Image_t * img_rgb24);

/**
 * @brief      Convert an RGB24 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_RGB24_to_YUV444p (Image_t * img_rgb24);

/**
 * @brief      Convert an RGB24 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and the YUV420p format uses less bits-per-pixel.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_RGB24_to_YUV420p (Image_t * img_rgb24);

/**
 * @brief      Convert an RGB24 image to an RGB565 image.
 * 
 * This conversion is lossy; the RGB565 format uses less bits-per-pixel.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_RGB24_to_RGB565 (Image_t * img_rgb24);

/**
 * @brief      Convert an RGB24 image to an RGB8 image.
 * 
 * This conversion is lossy; the RGB8 format uses less bits-per-pixel.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_RGB24_to_RGB8 (Image_t * img_rgb24);

/**
 * @brief      Convert an RGB24 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and the GRAYSCALE format uses less bits-per-pixel.
 *
 * @param      img_rgb24  The RGB24 image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_RGB24_to_GRAYSCALE (Image_t * img_rgb24);


/**
 * @brief      Convert an RGB565 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_RGB565_to_YUV444 (Image_t * img_rgb565);

/**
 * @brief      Convert an RGB565 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_RGB565_to_YUV444p (Image_t * img_rgb565);

/**
 * @brief      Convert an RGB565 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_RGB565_to_YUV420p (Image_t * img_rgb565);

/**
 * @brief      Convert an RGB565 image to an RGB24 image.
 * 
 * This conversion is lossless; RGB565 uses less bits-per-pixel than RGB24.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_RGB565_to_RGB24 (Image_t * img_rgb565);

/**
 * @brief      Convert an RGB565 image to an RGB8 image.
 * 
 * This conversion is lossy; RGB8 uses less bits-per-pixel.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_RGB565_to_RGB8 (Image_t * img_rgb565);

/**
 * @brief      Convert an RGB565 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear and GRAYSCALE uses less bits-per-pixel.
 *
 * @param      img_rgb565  The RGB565 image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_RGB565_to_GRAYSCALE (Image_t * img_rgb565);


/**
 * @brief      Convert an RGB8 image to a YUV444 image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_RGB8_to_YUV444 (Image_t * img_rgb8);

/**
 * @brief      Convert an RGB8 image to a YUV444p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_RGB8_to_YUV444p (Image_t * img_rgb8);

/**
 * @brief      Convert an RGB8 image to a YUV420p image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_RGB8_to_YUV420p (Image_t * img_rgb8);

/**
 * @brief      Convert an RGB8 image to an RGB24 image.
 * 
 * This conversion is lossless; RGB8 uses less bits-per-pixel than RGB24.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_RGB8_to_RGB24 (Image_t * img_rgb8);

/**
 * @brief      Convert an RGB8 image to an RGB565 image.
 * 
 * This conversion is lossless; RGB8 uses less bits-per-pixel than RGB565.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_RGB8_to_RGB565 (Image_t * img_rgb8);

/**
 * @brief      Convert an RGB8 image to a GRAYSCALE image.
 * 
 * This conversion is lossy; the RGB->YUV conversion is nonlinear.
 *
 * @param      img_rgb8  The RGB8 image to convert.
 *
 * @return     The converted GRAYSCALE image.
 */
Image_t * convert_RGB8_to_GRAYSCALE (Image_t * img_rgb8);


/**
 * @brief      Convert a GRAYSCALE image to a YUV444 image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV444.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted YUV444 image.
 */
Image_t * convert_GRAYSCALE_to_YUV444 (Image_t * img_grayscale);

/**
 * @brief      Convert a GRAYSCALE image to a YUV444p image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV444p.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted YUV444p image.
 */
Image_t * convert_GRAYSCALE_to_YUV444p (Image_t * img_grayscale);

/**
 * @brief      Convert a GRAYSCALE image to a YUV420p image.
 * 
 * This conversion is lossless; GRAYSCALE uses less bits-per-pixel than YUV420p.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted YUV420p image.
 */
Image_t * convert_GRAYSCALE_to_YUV420p (Image_t * img_grayscale);

/**
 * @brief      Convert a GRAYSCALE image to an RGB24 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted RGB24 image.
 */
Image_t * convert_GRAYSCALE_to_RGB24 (Image_t * img_grayscale);

/**
 * @brief      Convert a GRAYSCALE image to an RGB565 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted RGB565 image.
 */
Image_t * convert_GRAYSCALE_to_RGB565 (Image_t * img_grayscale);

/**
 * @brief      Convert a GRAYSCALE image to an RGB8 image.
 * 
 * This conversion is lossy; the YUV->RGB conversion is nonlinear.
 *
 * @param      img_grayscale  The GRAYSCALE image to convert.
 *
 * @return     The converted RGB8 image.
 */
Image_t * convert_GRAYSCALE_to_RGB8 (Image_t * img_grayscale);


#endif
