#include "img.h"
#include "conversions.h"


Image * convert_YUV444_to_YUV444p (Image * img_yuv444)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value
    // Base image: YUV YUV YUV YUV
    // New image: YYYY UUUU VVVV
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444p->data[i] = img_yuv444->data[i * 3];
        // Copy U component
        img_yuv444p->data[i + width * height] = img_yuv444->data[i * 3 + 1];
        // Copy V component
        img_yuv444p->data[i + width * height * 2] = img_yuv444->data[i * 3 + 2];
    }

    return img_yuv444p;
}


Image * convert_YUV444_to_YUV420p (Image * img_yuv444)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint32_t offset = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, 4 Y values share a single U and V value
    // Base image: YUV YUV YUV YUV
    // New image: YYYY U V
    
    // Copy Y component
    for (i = 0; i < width * height; i++) {
        img_yuv420p->data[i] = img_yuv444->data[i * 3];
    }

    // Y component done, increment offset
    offset += width * height;

    // Copy U component
    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        img_yuv420p->data[i] = img_yuv444->data[(i - offset) * 2 * 3 + 1];
    }

    // U component done, increment offset
    offset += UROUND_UP(width * height / 4);

    // Copy U component
    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        img_yuv420p->data[i] = img_yuv444->data[(i - offset) * 2 * 3 + 2];
    }

    return img_yuv420p;
}


Image * convert_YUV444_to_RGB24 (Image * img_yuv444)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_rgb24 = create_image(width, height, RGB24);
    if (!img_rgb24) return NULL;

    // In RGB24, each pixel has one R, one G and one B value
    // Base image: YUV YUV YUV YUV
    // New image: RGB RGB RGB RGB
    for (i = 0; i < width * height; i++) {
        // Copy Y -> R component
        img_rgb24->data[i * 3] = yuv_to_rgb_r(img_yuv444->data[i * 3],
                                              img_yuv444->data[i * 3 + 1],
                                              img_yuv444->data[i * 3 + 2]);
        // Copy U -> G component
        img_rgb24->data[i * 3 + 1] = yuv_to_rgb_g(img_yuv444->data[i * 3],
                                              img_yuv444->data[i * 3 + 1],
                                              img_yuv444->data[i * 3 + 2]);
        // Copy V -> B component
        img_rgb24->data[i * 3 + 2] = yuv_to_rgb_b(img_yuv444->data[i * 3],
                                              img_yuv444->data[i * 3 + 1],
                                              img_yuv444->data[i * 3 + 2]);
    }

    return img_rgb24;
}


Image * convert_YUV444_to_RGB565 (Image * img_yuv444)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        g = yuv_to_rgb_g(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        b = yuv_to_rgb_b(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        // Put values together in new image
        // All 5 bits of R + first 3 bits of G
        img_rgb565->data[i * 2] = (r & 0x1f) | ((g & 0x07) << 5);
        // Last 3 bits of G + all 5 bits of b
        img_rgb565->data[i * 2 + 1] = ((g & 0x38) >> 3) | ((b & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_YUV444_to_RGB8 (Image * img_yuv444)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        g = yuv_to_rgb_g(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        b = yuv_to_rgb_b(img_yuv444->data[i * 3],
                         img_yuv444->data[i * 3 + 1],
                         img_yuv444->data[i * 3 + 2]);

        // Put values together in new image
        // 3 bits of R, 3 bits of G and 2 bits of B
        img_rgb8->data[i] = (r & 0x07) | ((g & 0x07) << 3) | ((b & 0x03) << 6);
    }

    return img_rgb8;
}


Image * convert_YUV444_to_GRAYSCALE (Image * img_yuv444)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444) return NULL;
    if (img_yuv444->format != YUV444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel has one Y value
    // Base image: YUV YUV YUV YUV
    // New image: Y Y Y Y
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_grayscale->data[i] = img_yuv444->data[i * 3];
    }

    return img_grayscale;
}


Image * convert_YUV444p_to_YUV444 (Image * img_yuv444p)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value
    // Base image: YYYY UUUU VVVV
    // New image: YUV YUV YUV YUV
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444->data[i * 3] = img_yuv444p->data[i];
        // Copy U component
        img_yuv444->data[i * 3 + 1] = img_yuv444p->data[i + width * height];
        // Copy V component
        img_yuv444->data[i * 3 + 2] = img_yuv444p->data[i + width * height * 2];
    }

    return img_yuv444;
}


Image * convert_YUV444p_to_YUV420p (Image * img_yuv444p)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t offset = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, four Y values share one U and one V value
    // Base image: YYYY UUUU VVVV
    // New image: YYYY U V
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv420p->data[i] = img_yuv444p->data[i];
    }

    // Y is done, increment offset
    offset += width * height;

    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        // Copy U component
        img_yuv420p->data[i] = img_yuv444p->data[(i - offset) * 4 + width * height];
    }

    // U is done, increment offset
    offset += UROUND_UP(width * height / 4);

    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        // Copy V component
        img_yuv420p->data[i] = img_yuv444p->data[(i - offset) * 4 + width * height * 2];
    }

    return img_yuv420p;
}


Image * convert_YUV444p_to_RGB24 (Image * img_yuv444p)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_rgb24 = create_image(width, height, RGB24);
    if (!img_rgb24) return NULL;

    // In RGB24, each pixel has one R, one G and one B value
    // Base image: YYYY UUUU VVVV
    // New image: RGB RGB RGB RGB
    for (i = 0; i < width * height; i++) {
        // Copy Y -> R component
        img_rgb24->data[i * 3] = yuv_to_rgb_r(img_yuv444p->data[i],
                                              img_yuv444p->data[i + width * height],
                                              img_yuv444p->data[i + width * height * 2]);
        // Copy U -> G component
        img_rgb24->data[i * 3 + 1] = yuv_to_rgb_g(img_yuv444p->data[i],
                                              img_yuv444p->data[i + width * height],
                                              img_yuv444p->data[i + width * height * 2]);
        // Copy V -> B component
        img_rgb24->data[i * 3 + 2] = yuv_to_rgb_b(img_yuv444p->data[i],
                                              img_yuv444p->data[i + width * height],
                                              img_yuv444p->data[i + width * height * 2]);
    }

    return img_rgb24;
}


Image * convert_YUV444p_to_RGB565 (Image * img_yuv444p)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        g = yuv_to_rgb_g(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        b = yuv_to_rgb_b(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        // Put values together in new image
        // All 5 bits of R + first 3 bits of G
        img_rgb565->data[i * 2] = (r & 0x1f) | ((g & 0x07) << 5);
        // Last 3 bits of G + all 5 bits of b
        img_rgb565->data[i * 2 + 1] = ((g & 0x38) >> 3) | ((b & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_YUV444p_to_RGB8 (Image * img_yuv444p)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        g = yuv_to_rgb_g(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        b = yuv_to_rgb_b(img_yuv444p->data[i],
                         img_yuv444p->data[i + width * height],
                         img_yuv444p->data[i + width * height * 2]);

        // Put values together in new image
        // 3 bits of R, 3 bits of G and 2 bits of B
        img_rgb8->data[i] = (r & 0x07) | ((g & 0x07) << 3) | ((b & 0x03) << 6);
    }

    return img_rgb8;
}


Image * convert_YUV444p_to_GRAYSCALE (Image * img_yuv444p)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444p) return NULL;
    if (img_yuv444p->format != YUV444p) return NULL;

    width = img_yuv444p->width;
    height = img_yuv444p->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel has one Y value
    // Base image: YYYYY UUUU VVVV
    // New image: Y Y Y Y
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_grayscale->data[i] = img_yuv444p->data[i];
    }

    return img_grayscale;
}


Image * convert_YUV420p_to_YUV444 (Image * img_yuv420p)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value
    // This necessitates upscaling, so U and V values will be quadrupled
    // Base image: YYYY U V
    // New image: YUV YUV YUV YUV
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444->data[i * 3] = img_yuv420p->data[i];
        // Copy U component
        img_yuv444->data[i * 3 + 1] = img_yuv420p->data[i / 4 + width * height];
        // Copy V component
        img_yuv444->data[i * 3 + 2] = img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)];
    }

    return img_yuv444;
}


Image * convert_YUV420p_to_YUV444p (Image * img_yuv420p)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value
    // This necessitates upscaling, so U and V values will be quadrupled
    // Base image: YYYY U V
    // New image: YYYY UUUU VVVV
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444p->data[i] = img_yuv420p->data[i];
        // Copy U component
        img_yuv444p->data[i + width * height] = img_yuv420p->data[i / 4 + width * height];
        // Copy V component
        img_yuv444p->data[i + width * height * 2] = img_yuv420p->data[i / 4 + width * height +
                                                                      UROUND_UP(width * height / 4)];
    }

    return img_yuv444p;
}


Image * convert_YUV420p_to_RGB24 (Image * img_yuv420p)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_rgb24 = create_image(width, height, RGB24);
    if (!img_rgb24) return NULL;

    // In RGB24, each pixel has one R, one G and one B value
    // This necessitates upscaling, so U and V values will be quadrupled
    // Base image: YYYY U V
    // New image: RGB RGB RGB RGB
    for (i = 0; i < width * height; i++) {
        // Copy Y -> R component
        img_rgb24->data[i * 3] = yuv_to_rgb_r(img_yuv420p->data[i],
                                              img_yuv420p->data[i / 4 + width * height],
                                              img_yuv420p->data[i / 4 + width * height +
                                                                UROUND_UP(width * height / 4)]);
        // Copy U -> G component
        img_rgb24->data[i * 3 + 1] = yuv_to_rgb_g(img_yuv420p->data[i],
                                              img_yuv420p->data[i / 4 + width * height],
                                              img_yuv420p->data[i / 4 + width * height +
                                                                UROUND_UP(width * height / 4)]);
        // Copy V -> B component
        img_rgb24->data[i * 3 + 2] = yuv_to_rgb_b(img_yuv420p->data[i],
                                              img_yuv420p->data[i / 4 + width * height],
                                              img_yuv420p->data[i / 4 + width * height +
                                                                UROUND_UP(width * height / 4)]);
    }

    return img_rgb24;
}


Image * convert_YUV420p_to_RGB565 (Image * img_yuv420p)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    // This necessitates upscaling, so U and V values will be quadrupled
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        g = yuv_to_rgb_g(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        b = yuv_to_rgb_b(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        // Put values together in new image
        // All 5 bits of R + first 3 bits of G
        img_rgb565->data[i * 2] = (r & 0x1f) | ((g & 0x07) << 5);
        // Last 3 bits of G + all 5 bits of b
        img_rgb565->data[i * 2 + 1] = ((g & 0x38) >> 3) | ((b & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_YUV420p_to_RGB8 (Image * img_yuv420p)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    // This necessitates upscaling, so U and V values will be quadrupled
    for (i = 0; i < width * height; i++) {
        // Convert values
        r = yuv_to_rgb_r(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        g = yuv_to_rgb_g(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        b = yuv_to_rgb_b(img_yuv420p->data[i],
                         img_yuv420p->data[i / 4 + width * height],
                         img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)]);

        // Put values together in new image
        // 3 bits of R, 3 bits of G and 2 bits of B
        img_rgb8->data[i] = (r & 0x07) | ((g & 0x07) << 3) | ((b & 0x03) << 6);
    }

    return img_rgb8;
}


Image * convert_YUV420p_to_GRAYSCALE (Image * img_yuv420p)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel has one Y value
    // Base image: YYYYY U V
    // New image: Y Y Y Y
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_grayscale->data[i] = img_yuv420p->data[i];
    }

    return img_grayscale;
}


Image * convert_RGB24_to_YUV444 (Image * img_rgb24)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value
    // Base image: RGB RGB RGB RGB
    // New image: YUV YUV YUV YUV
    for (i = 0; i < width * height * 3; i += 3) {
        // Transform RGB -> YUV
        y = rgb_to_yuv_y(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);
        u = rgb_to_yuv_u(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);
        v = rgb_to_yuv_v(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);

        // Copy Y component
        img_yuv444->data[i] = y;
        // Copy U component
        img_yuv444->data[i + 1] = u;
        // Copy V component
        img_yuv444->data[i + 2] = v;
    }

    return img_yuv444;
}


Image * convert_RGB24_to_YUV444p (Image * img_rgb24)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value
    // Base image: RGB RGB RGB RGB
    // New image: YYYY UUUU VVVV
    for (i = 0; i < width * height; i++) {
        // Transform RGB -> YUV
        y = rgb_to_yuv_y(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        u = rgb_to_yuv_u(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        v = rgb_to_yuv_v(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);

        // Copy Y component
        img_yuv444p->data[i] = y;
        // Copy U component
        img_yuv444p->data[i + width * height] = u;
        // Copy V component
        img_yuv444p->data[i + width * height * 2] = v;
    }

    return img_yuv444p;
}


Image * convert_RGB24_to_YUV420p (Image * img_rgb24)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, for Y values share one U and one V value
    // Base image: RGB RGB RGB RGB
    // New image: YYYY U V
    for (i = 0; i < width * height; i++) {
        // Transform RGB -> YUV
        y = rgb_to_yuv_y(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        u = rgb_to_yuv_u(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        v = rgb_to_yuv_v(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);

        // Copy Y component
        img_yuv420p->data[i] = y;
        // Copy U component
        img_yuv420p->data[i / 4 + width * height] = u;
        // Copy V component
        img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)] = v;
    }

    return img_yuv420p;
}


Image * convert_RGB24_to_RGB565 (Image * img_rgb24)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Transform RGB -> YUV
        r = img_rgb24->data[i * 3];
        g = img_rgb24->data[i * 3 + 1];
        b = img_rgb24->data[i * 3 + 2];

        // Put values together in new image
        // All 5 bits of R + first 3 bits of G
        img_rgb565->data[i * 2] = (r & 0x1f) | ((g & 0x07) << 5);
        // Last 3 bits of G + all 5 bits of b
        img_rgb565->data[i * 2 + 1] = ((g & 0x38) >> 3) | ((b & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_RGB24_to_RGB8 (Image * img_rgb24)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Transform RGB -> YUV
        r = img_rgb24->data[i * 3];
        g = img_rgb24->data[i * 3 + 1];
        b = img_rgb24->data[i * 3 + 2];

        // Put values together in new image
        // 3 bits of R, 3 bits of G and 2 bits of B
        img_rgb8->data[i] = (r & 0x07) | ((g & 0x07) << 3) | ((b & 0x03) << 6);
    }

    return img_rgb8;
}














uint8_t yuv_to_rgb_r (uint8_t y, uint8_t u, uint8_t v)
{
    int16_t r = 0;

    r = 1 * y + 0 * u + 1.28033 * v;

    if (r < 0) return 0;
    if (r > 255) return 255;
    return (uint8_t) r;
}


uint8_t yuv_to_rgb_g (uint8_t y, uint8_t u, uint8_t v)
{
    int16_t g = 0;

    g = 1 * y - 0.21482 * u - 0.38059 * v;

    if (g < 0) return 0;
    if (g > 255) return 255;
    return (uint8_t) g;
}


uint8_t yuv_to_rgb_b (uint8_t y, uint8_t u, uint8_t v)
{
    int16_t b = 0;

    b = 1 * y + 2.12798 * u + 0 * v;

    if (b < 0) return 0;
    if (b > 255) return 255;
    return (uint8_t) b;
}


uint8_t rgb_to_yuv_y (uint8_t r, uint8_t g, uint8_t b)
{
    int16_t y = 0;

    y = 0.2126 * r + 0.7152 * g + 0.0722 * b;

    if (y < 0) return 0;
    if (y > 255) return 255;
    return (uint8_t) y;
}


uint8_t rgb_to_yuv_u (uint8_t r, uint8_t g, uint8_t b)
{
    int16_t u = 0;

    u = -0.09991 * r - 0.33609 * g + 0.436 * b;

    if (u < 0) return 0;
    if (u > 255) return 255;
    return (uint8_t) u;
}


uint8_t rgb_to_yuv_v (uint8_t r, uint8_t g, uint8_t b)
{
    int16_t v = 0;

    v = 0.615 * r - 0.55861 * g - 0.05639 * b;

    if (v < 0) return 0;
    if (v > 255) return 255;
    return (uint8_t) v;
}
