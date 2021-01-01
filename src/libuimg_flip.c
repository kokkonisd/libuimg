#include "libuimg_flip.h"


uint8_t (* flipY_function_LUT[ASCII + 1]) (Image_t * img) = {
    flipY_YUV444,
    flipY_YUV444p,
    flipY_YUV420p,
    flipY_RGB24,
    flipY_RGB565,
    flipY_RGB8,
    flipY_GRAYSCALE,
    flipY_ASCII,
};


uint8_t flipY_image (Image_t * img)
{
    if (!img) return 0;

    return flipY_function_LUT[img->format](img);
}


/* --------------------------------------------------------------------------------------------------------------------
 * MID-LEVEL FLIP FUNCTIONS
 * --------------------------------------------------------------------------------------------------------------------
 */


uint8_t flipY_YUV444 (Image_t * img_yuv444)
{
    if (!img_yuv444) return 0;
    if (img_yuv444->format != YUV444) return 0;

    return flipY_24bpp(img_yuv444);
}


uint8_t flipY_YUV444p (Image_t * img_yuv444p)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t temp_data = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t loop_width = 0;
    uint32_t row_offset_left = 0;
    uint32_t row_offset_right = 0;

    if (!img_yuv444p) return 0;
    if (img_yuv444p->format != YUV444p) return 0;

    width = img_yuv444p->width;
    height = img_yuv444p->height;
    loop_width = width / 2;

    u_offset = width * height;
    v_offset = u_offset * 2;

    for (i = 0; i < height; i++) {
        row_offset_left = i * width;
        row_offset_right = (i + 1) * width;

        for (j = 0; j < loop_width; j++) {
            // Flip Y component
            temp_data = img_yuv444p->data[row_offset_left + j];
            img_yuv444p->data[row_offset_left + j] = img_yuv444p->data[row_offset_right - 1 - j];
            img_yuv444p->data[row_offset_right - 1 - j] = temp_data;

            // Flip U component
            temp_data = img_yuv444p->data[u_offset + row_offset_left + j];
            img_yuv444p->data[u_offset + row_offset_left + j] = img_yuv444p->data[u_offset + row_offset_right - 1 - j];
            img_yuv444p->data[u_offset + row_offset_right - 1 - j] = temp_data;

            // Flip V component
            temp_data = img_yuv444p->data[v_offset + row_offset_left + j];
            img_yuv444p->data[v_offset + row_offset_left + j] = img_yuv444p->data[v_offset + row_offset_right - 1 - j];
            img_yuv444p->data[v_offset + row_offset_right - 1 - j] = temp_data;
        }
    }

    return 1;
}


uint8_t flipY_YUV420p (Image_t * img_yuv420p)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t temp_data = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t uv_width = 0;
    uint32_t row_offset_left_y = 0;
    uint32_t row_offset_right_y = 0;
    uint32_t row_offset_left_uv = 0;
    uint32_t row_offset_right_uv = 0;
    uint16_t loop_width = 0;

    if (!img_yuv420p) return 0;
    if (img_yuv420p->format != YUV420p) return 0;

    width = img_yuv420p->width;
    height = img_yuv420p->height;
    loop_width = UROUND_UP(width / 2);

    u_offset = width * height;
    uv_width = UROUND_UP(width / 2);
    v_offset = u_offset + uv_width * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        row_offset_left_y = i * width;
        row_offset_right_y = (i + 1) * width - 1;
        row_offset_left_uv = i / 2 * uv_width;
        row_offset_right_uv = (i / 2 + 1) * uv_width - 1;
 
        for (j = 0; j < loop_width; j++) {
            // Flip Y component
            temp_data = img_yuv420p->data[row_offset_left_y + j];
            img_yuv420p->data[row_offset_left_y + j] = img_yuv420p->data[row_offset_right_y - j];
            img_yuv420p->data[row_offset_right_y - j] = temp_data;

            // Only flip when i and j are even, otherwise the U, V elements will be flipped twice
            if (i % 2 == 0 && j % 2 == 0) {
                // Flip U component
                temp_data = img_yuv420p->data[u_offset + row_offset_left_uv + j / 2];
                img_yuv420p->data[u_offset + row_offset_left_uv + j / 2] = img_yuv420p->data[u_offset +
                                                                                             row_offset_right_uv -
                                                                                             j / 2];
                img_yuv420p->data[u_offset + row_offset_right_uv - j / 2] = temp_data;

                // Flip V component
                temp_data = img_yuv420p->data[v_offset + row_offset_left_uv + j / 2];
                img_yuv420p->data[v_offset + row_offset_left_uv + j / 2] = img_yuv420p->data[v_offset +
                                                                                             row_offset_right_uv -
                                                                                             j / 2];
                img_yuv420p->data[v_offset + row_offset_right_uv - j / 2] = temp_data;
            }
        }
    }

    return 1;
}


uint8_t flipY_RGB24 (Image_t * img_rgb24)
{
    if (!img_rgb24) return 0;
    if (img_rgb24->format != RGB24) return 0;

    return flipY_24bpp(img_rgb24);
}


uint8_t flipY_RGB565 (Image_t * img_rgb565)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t loop_width = 0;
    uint16_t loop_height = 0;
    uint8_t temp_data = 0;
    uint32_t row_offset_left = 0;
    uint32_t row_offset_right = 0;

    if (!img_rgb565) return 0;
    if (img_rgb565->format != RGB565) return 0;

    width = img_rgb565->width;
    height = img_rgb565->height;
    loop_height = height * 2;
    loop_width = width;

    for (i = 0; i < loop_height; i += 2) {
        row_offset_left = i * width;
        row_offset_right = (i + 2) * width;

        for (j = 0; j < loop_width; j += 2) {
            // Flip 2 bytes at a time
            temp_data = img_rgb565->data[row_offset_left + j];
            img_rgb565->data[row_offset_left + j] = img_rgb565->data[row_offset_right - 2 - j];
            img_rgb565->data[row_offset_right - 2 - j] = temp_data;

            temp_data = img_rgb565->data[row_offset_left + j + 1];
            img_rgb565->data[row_offset_left + j + 1] = img_rgb565->data[row_offset_right - 1 - j];
            img_rgb565->data[row_offset_right - 1 - j] = temp_data;
        }
    }

    return 1;
}


uint8_t flipY_RGB8 (Image_t * img_rgb8)
{
    if (!img_rgb8) return 0;
    if (img_rgb8->format != RGB8) return 0;

    return flipY_8bpp(img_rgb8);
}


uint8_t flipY_GRAYSCALE (Image_t * img_grayscale)
{
    if (!img_grayscale) return 0;
    if (img_grayscale->format != GRAYSCALE) return 0;

    return flipY_8bpp(img_grayscale);
}


uint8_t flipY_ASCII (Image_t * img_ascii)
{
    if (!img_ascii) return 0;
    if (img_ascii->format != ASCII) return 0;

    return flipY_8bpp(img_ascii);
}



/* --------------------------------------------------------------------------------------------------------------------
 * LOW-LEVEL TRANSFORMATION FUNCTIONS
 * --------------------------------------------------------------------------------------------------------------------
 */


uint8_t flipY_24bpp (Image_t * img)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t loop_width = 0;
    uint32_t loop_height = 0;
    uint8_t temp_data = 0;
    uint32_t row_offset_left = 0;
    uint32_t row_offset_right = 0;

    if (!img) return 0;

    width = img->width;
    height = img->height;
    loop_width = (width / 2) * 3;
    loop_height = height * 3;

    for (i = 0; i < loop_height; i += 3) {
        row_offset_left = i * width;
        row_offset_right = (i + 3) * width;

        for (j = 0; j < loop_width; j += 3) {
            // Flip 1st channel
            temp_data = img->data[row_offset_left + j];
            img->data[row_offset_left + j] = img->data[row_offset_right - 3 - j];
            img->data[row_offset_right - 3 - j] = temp_data;

            // Flip 2nd channel
            temp_data = img->data[row_offset_left + j + 1];
            img->data[row_offset_left + j + 1] = img->data[row_offset_right - 2 - j];
            img->data[row_offset_right - 2 - j] = temp_data;

            // Flip 3rd channel
            temp_data = img->data[row_offset_left + j + 2];
            img->data[row_offset_left + j + 2] = img->data[row_offset_right - 1 - j];
            img->data[row_offset_right - 1 - j] = temp_data;
        }
    }

    return 1;
}


uint8_t flipY_8bpp (Image_t * img)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t loop_width = 0;
    uint8_t temp_data = 0;
    uint32_t row_offset_left = 0;
    uint32_t row_offset_right = 0;

    if (!img) return 0;

    width = img->width;
    height = img->height;
    loop_width = width / 2;

    for (i = 0; i < height; i++) {
        row_offset_left = i * width;
        row_offset_right = (i + 1) * width;

        for (j = 0; j < loop_width; j++) {
            // Flip elements of row
            temp_data = img->data[row_offset_left + j];
            img->data[row_offset_left + j] = img->data[row_offset_right - 1 - j];
            img->data[row_offset_right - 1 - j] = temp_data;
        }
    }

    return 1;
}
