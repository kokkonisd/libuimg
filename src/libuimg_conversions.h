#ifndef __LIB_UIMG_CONVERSIONS_H__
#define __LIB_UIMG_CONVERSIONS_H__

#include "libuimg_img.h"

#include <string.h>


uint8_t rescale_color (uint8_t value, uint8_t old_min, uint8_t old_max, uint8_t new_min, uint8_t new_max);

uint8_t yuv_to_rgb_r (uint8_t y, uint8_t u, uint8_t v);
uint8_t yuv_to_rgb_g (uint8_t y, uint8_t u, uint8_t v);
uint8_t yuv_to_rgb_b (uint8_t y, uint8_t u, uint8_t v);

uint8_t rgb_to_yuv_y (uint8_t r, uint8_t g, uint8_t b);
uint8_t rgb_to_yuv_u (uint8_t r, uint8_t g, uint8_t b);
uint8_t rgb_to_yuv_v (uint8_t r, uint8_t g, uint8_t b);


Image * convert_YUV444_to_YUV444p (Image * img_yuv444);
Image * convert_YUV444_to_YUV420p (Image * img_yuv444);
Image * convert_YUV444_to_RGB24 (Image * img_yuv444);
Image * convert_YUV444_to_RGB565 (Image * img_yuv444);
Image * convert_YUV444_to_RGB8 (Image * img_yuv444);
Image * convert_YUV444_to_GRAYSCALE (Image * img_yuv444);

Image * convert_YUV444p_to_YUV444 (Image * img_yuv444p);
Image * convert_YUV444p_to_YUV420p (Image * img_yuv444p);
Image * convert_YUV444p_to_RGB24 (Image * img_yuv444p);
Image * convert_YUV444p_to_RGB565 (Image * img_yuv444p);
Image * convert_YUV444p_to_RGB8 (Image * img_yuv444p);
Image * convert_YUV444p_to_GRAYSCALE (Image * img_yuv444p);

Image * convert_YUV420p_to_YUV444 (Image * img_yuv420p);
Image * convert_YUV420p_to_YUV444p (Image * img_yuv420p);
Image * convert_YUV420p_to_RGB24 (Image * img_yuv420p);
Image * convert_YUV420p_to_RGB565 (Image * img_yuv420p);
Image * convert_YUV420p_to_RGB8 (Image * img_yuv420p);
Image * convert_YUV420p_to_GRAYSCALE (Image * img_yuv420p);

Image * convert_RGB24_to_YUV444 (Image * img_rgb24);
Image * convert_RGB24_to_YUV444p (Image * img_rgb24);
Image * convert_RGB24_to_YUV420p (Image * img_rgb24);
Image * convert_RGB24_to_RGB565 (Image * img_rgb24);
Image * convert_RGB24_to_RGB8 (Image * img_rgb24);
Image * convert_RGB24_to_GRAYSCALE (Image * img_rgb24);

Image * convert_RGB565_to_YUV444 (Image * img_rgb565);
Image * convert_RGB565_to_YUV444p (Image * img_rgb565); // TODO
Image * convert_RGB565_to_YUV420p (Image * img_rgb565); // TODO
Image * convert_RGB565_to_RGB24 (Image * img_rgb565); // TODO
Image * convert_RGB565_to_RGB8 (Image * img_rgb565); // TODO
Image * convert_RGB565_to_GRAYSCALE (Image * img_rgb565); // TODO

Image * convert_RGB8_to_YUV444 (Image * img_rgb8); // TODO
Image * convert_RGB8_to_YUV444p (Image * img_rgb8); // TODO
Image * convert_RGB8_to_YUV420p (Image * img_rgb8); // TODO
Image * convert_RGB8_to_RGB24 (Image * img_rgb8); // TODO
Image * convert_RGB8_to_RGB565 (Image * img_rgb8); // TODO
Image * convert_RGB8_to_GRAYSCALE (Image * img_rgb8); // TODO

Image * convert_GRAYSCALE_to_YUV444 (Image * img_grayscale); // TODO
Image * convert_GRAYSCALE_to_YUV444p (Image * img_grayscale); // TODO
Image * convert_GRAYSCALE_to_YUV420p (Image * img_grayscale); // TODO
Image * convert_GRAYSCALE_to_RGB24 (Image * img_grayscale); // TODO
Image * convert_GRAYSCALE_to_RGB565 (Image * img_grayscale); // TODO
Image * convert_GRAYSCALE_to_RGB8 (Image * img_grayscale); // TODO


#endif
