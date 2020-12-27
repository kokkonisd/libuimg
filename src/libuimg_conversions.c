#include "libuimg_img.h"
#include "libuimg_conversions.h"


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
    uint32_t j = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
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
    
    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Copy Y data
            img_yuv420p->data[i * width + j] = img_yuv444->data[i * 3 * width + j * 3];
            // Copy U data
            img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = img_yuv444->data[i * 3 * width +
                                                                                                      j * 3 + 1];
            // Copy V data
            img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = img_yuv444->data[i * 3 * width +
                                                                                                      j * 3 + 2];
        }
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
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

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
        r_value = yuv_to_rgb_r(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        g_value = yuv_to_rgb_g(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        b_value = yuv_to_rgb_b(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        // Rescale values
        r_value = rescale_color(r_value, 0, 255, 0, 32);
        g_value = rescale_color(g_value, 0, 255, 0, 64);
        b_value = rescale_color(b_value, 0, 255, 0, 32);

        // Put values together in new image
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[i * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[i * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_YUV444_to_RGB8 (Image * img_yuv444)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

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
        r_value = yuv_to_rgb_r(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        g_value = yuv_to_rgb_g(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        b_value = yuv_to_rgb_b(img_yuv444->data[i * 3],
                               img_yuv444->data[i * 3 + 1],
                               img_yuv444->data[i * 3 + 2]);

        // Rescale values
        r_value = rescale_color(r_value, 0, 255, 0, 8);
        g_value = rescale_color(g_value, 0, 255, 0, 8);
        b_value = rescale_color(b_value, 0, 255, 0, 4);

        // Put values together in new image
        // MSB | 3 bits of R, 3 bits of G 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x07) | ((g_value & 0x07) << 2) | ((g_value & 0x03) << 5);
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
    uint32_t j = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t width = 0;
    uint16_t height = 0;

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
    
    // Copy Y data
    memcpy(img_yuv420p->data, img_yuv444p->data, width * height);

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Copy U data
            img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = img_yuv444p->data[u_offset + 
                                                                                                       i * width +
                                                                                                       j];
            // Copy V data
            img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = img_yuv444p->data[u_offset * 2 +
                                                                                                       i * width +
                                                                                                       j];
        }
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
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

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
        r_value = yuv_to_rgb_r(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        g_value = yuv_to_rgb_g(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        b_value = yuv_to_rgb_b(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        // Rescale values
        r_value = rescale_color(r_value, 0, 255, 0, 32);
        g_value = rescale_color(g_value, 0, 255, 0, 64);
        b_value = rescale_color(b_value, 0, 255, 0, 32);

        // Put values together in new image
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[i * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[i * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_YUV444p_to_RGB8 (Image * img_yuv444p)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

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
        r_value = yuv_to_rgb_r(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        g_value = yuv_to_rgb_g(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        b_value = yuv_to_rgb_b(img_yuv444p->data[i],
                               img_yuv444p->data[i + width * height],
                               img_yuv444p->data[i + width * height * 2]);

        // Rescale values
        r_value = rescale_color(r_value, 0, 255, 0, 8);
        g_value = rescale_color(g_value, 0, 255, 0, 8);
        b_value = rescale_color(b_value, 0, 255, 0, 4);

        // Put values together in new image
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
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
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t base_row_offset = 0;
    uint32_t conv_row_offset = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value
    // This necessitates upscaling, so U and V values will be quadrupled by doubling them horizontally and vertically
    // Base image: YYYY U V
    // New image: YUV YUV YUV YUV
    // 
    // More explicitly, for a 3x3 image (to show how to handle odd dimensions):
    // 
    // Base 3x3 YUV420p image:
    //
    //     Y0 Y1 Y2
    //     Y3 Y4 Y5
    //     Y6 Y7 Y8
    //     --------
    //     U0    U1
    //     
    //     U2    U3
    //     --------
    //     V0    V1
    //     
    //     V2    V3
    //
    //
    // Converted 3x3 YUV444 image:
    //
    //     Y0U0V0 Y1U0V0 Y2U1V1
    //     Y3U0V0 Y4U0V0 Y5U1V1
    //     Y6U2V2 Y7U2V2 Y8U3V3
    //
    //
    // In conclusion, because the dimensions are odd, U1 is shared among 2 pixels only (Y2 and Y5), U2 is shared among
    // 2 pixels only (Y6 and Y7) and U3 is used by one pixel only (Y8).
    
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444->data[i * 3] = img_yuv420p->data[i];
    }

    for (i = 0; i < height; i++) {
        // On the base image, we need to skip the Y values (W x H bytes)
        base_row_offset = width * height + (i / 2) * UROUND_UP(width / 2);
        // On the converted image, we only want 
        conv_row_offset = i * 3 * width;

        for (j = 0; j < width; j++) {
            // U values are duplicated horizontally & vertically
            img_yuv444->data[conv_row_offset + j * 3 + 1] = img_yuv420p->data[base_row_offset + (j / 2)];

            // Increment base offset to handle V values of the current iteration
            base_row_offset += UROUND_UP(width / 2) * UROUND_UP(height / 2);
            // V values are duplicated horizontally & vertically
            img_yuv444->data[i * 3 * width + j * 3 + 2] = img_yuv420p->data[base_row_offset + (j / 2)];
            // Reset base row offset for the U values of the next iteration
            base_row_offset -= UROUND_UP(width / 2) * UROUND_UP(height / 2);
        }
    }

    return img_yuv444;
}


Image * convert_YUV420p_to_YUV444p (Image * img_yuv420p)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t base_offset = 0;
    uint32_t converted_offset = 0;

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
    // More explicitly, for a 3x3 image (to show how to handle odd dimensions):
    // 
    // Base 3x3 YUV420p image:
    //
    //     Y0 Y1 Y2
    //     Y3 Y4 Y5
    //     Y6 Y7 Y8
    //     --------
    //     U0    U1
    //     
    //     U2    U3
    //     --------
    //     V0    V1
    //     
    //     V2    V3
    //
    //
    // Converted 3x3 YUV444p image:
    //
    //     Y0 Y1 Y2
    //     Y3 Y4 Y5
    //     Y6 Y7 Y8
    //     --------
    //     U0 U0 U1
    //     U0 U0 U1
    //     U2 U2 U3
    //     --------
    //     V0 V0 V1
    //     V0 V0 V1
    //     V2 V2 V3
    //
    //
    // In conclusion, because the dimensions are odd, U1 is shared among 2 pixels only (Y2 and Y5), U2 is shared among
    // 2 pixels only (Y6 and Y7) and U3 is used by one pixel only (Y8).
    
    // Copy Y component
    memcpy(img_yuv444p->data, img_yuv420p->data, width * height);

    base_offset = width * height;
    converted_offset = width * height;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // U values are duplicated horizontally & vertically
            img_yuv444p->data[converted_offset + i * width + j] = img_yuv420p->data[base_offset +
                                                                                    (i / 2) * UROUND_UP(width / 2) +
                                                                                    (j / 2)];
        }
    }

    base_offset += UROUND_UP(width / 2) * UROUND_UP(height / 2);
    converted_offset += width * height;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // V values are duplicated horizontally & vertically
            img_yuv444p->data[converted_offset + i * width + j] = img_yuv420p->data[base_offset +
                                                                                    (i / 2) * UROUND_UP(width / 2) +
                                                                                    (j / 2)];
        }
    }

    return img_yuv444p;
}


Image * convert_YUV420p_to_RGB24 (Image * img_yuv420p)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;

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
    // See `convert_YUV420p_to_YUV444()` or `convert_YUV420p_to_YUV444p()` for more info

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Get values for the YUV pixel corresponding to the current RGB pixel
            y_value = img_yuv420p->data[i * width + j];
            u_value = img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];
            v_value = img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];

            // Copy R data
            img_rgb24->data[i * 3 * width + j * 3] = yuv_to_rgb_r(y_value, u_value, v_value);
            // Copy G data
            img_rgb24->data[i * 3 * width + j * 3 + 1] = yuv_to_rgb_g(y_value, u_value, v_value);
            // Copy B data
            img_rgb24->data[i * 3 * width + j * 3 + 2] = yuv_to_rgb_b(y_value, u_value, v_value);
        }
    }

    return img_rgb24;
}


Image * convert_YUV420p_to_RGB565 (Image * img_yuv420p)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    // This necessitates upscaling, so U and V values will be quadrupled
    // See `convert_YUV420p_to_YUV444()` or `convert_YUV420p_to_YUV444p()` for more info

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Get values for the YUV pixel corresponding to the current RGB pixel
            y_value = img_yuv420p->data[i * width + j];
            u_value = img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];
            v_value = img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];

            // Calculate R data
            r_value = yuv_to_rgb_r(y_value, u_value, v_value);
            // Calculate G data
            g_value = yuv_to_rgb_g(y_value, u_value, v_value);
            // Calculate B data
            b_value = yuv_to_rgb_b(y_value, u_value, v_value);

            // Rescale values to new range
            r_value = rescale_color(r_value, 0, 255, 0, 32);
            g_value = rescale_color(g_value, 0, 255, 0, 64);
            b_value = rescale_color(b_value, 0, 255, 0, 32);

            // Put values together in new image
            // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
            img_rgb565->data[i * 2 * width + j * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
            img_rgb565->data[i * 2 * width + j * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
        }
    }

    return img_rgb565;
}


Image * convert_YUV420p_to_RGB8 (Image * img_yuv420p)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_yuv420p) return NULL;
    if (img_yuv420p->format != YUV420p) return NULL;

    width = img_yuv420p->width;
    height = img_yuv420p->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    // This necessitates upscaling, so U and V values will be quadrupled
    // See `convert_YUV420p_to_YUV444()` or `convert_YUV420p_to_YUV444p()` for more info

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Get values for the YUV pixel corresponding to the current RGB pixel
            y_value = img_yuv420p->data[i * width + j];
            u_value = img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];
            v_value = img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)];

            // Calculate R data
            r_value = yuv_to_rgb_r(y_value, u_value, v_value);
            // Calculate G data
            g_value = yuv_to_rgb_g(y_value, u_value, v_value);
            // Calculate B data
            b_value = yuv_to_rgb_b(y_value, u_value, v_value);

            r_value = rescale_color(r_value, 0, 255, 0, 8);
            g_value = rescale_color(g_value, 0, 255, 0, 8);
            b_value = rescale_color(b_value, 0, 255, 0, 4);

            // Put values together in new image
            // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
            img_rgb8->data[i * width + j] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
        }
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
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;

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
        y_value = rgb_to_yuv_y(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);
        u_value = rgb_to_yuv_u(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);
        v_value = rgb_to_yuv_v(img_rgb24->data[i], img_rgb24->data[i + 1], img_rgb24->data[i + 2]);

        // Copy Y component
        img_yuv444->data[i] = y_value;
        // Copy U component
        img_yuv444->data[i + 1] = u_value;
        // Copy V component
        img_yuv444->data[i + 2] = v_value;
    }

    return img_yuv444;
}


Image * convert_RGB24_to_YUV444p (Image * img_rgb24)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;

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
        y_value = rgb_to_yuv_y(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        u_value = rgb_to_yuv_u(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);
        v_value = rgb_to_yuv_v(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);

        // Copy Y component
        img_yuv444p->data[i] = y_value;
        // Copy U component
        img_yuv444p->data[i + width * height] = u_value;
        // Copy V component
        img_yuv444p->data[i + width * height * 2] = v_value;
    }

    return img_yuv444p;
}


Image * convert_RGB24_to_YUV420p (Image * img_rgb24)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, four Y values share one U and one V value
    // Base image: RGB RGB RGB RGB
    // New image: YYYY U V
    
    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Get values for the RGB pixel corresponding to the current YUV pixel
            r_value = img_rgb24->data[i * 3 * width + j * 3];
            g_value = img_rgb24->data[i * 3 * width + j * 3 + 1];
            b_value = img_rgb24->data[i * 3 * width + j * 3 + 2];

            // Transform values to YUV
            y_value = rgb_to_yuv_y(r_value, g_value, b_value);
            u_value = rgb_to_yuv_u(r_value, g_value, b_value);
            v_value = rgb_to_yuv_v(r_value, g_value, b_value);

            // Copy Y, U and V data
            img_yuv420p->data[i * width + j] = y_value;
            img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = u_value;
            img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = v_value;
        }
    }

    return img_yuv420p;
}


Image * convert_RGB24_to_RGB565 (Image * img_rgb24)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Rescale values
        r_value = rescale_color(img_rgb24->data[i * 3], 0, 255, 0, 32);
        g_value = rescale_color(img_rgb24->data[i * 3 + 1], 0, 255, 0, 64);
        b_value = rescale_color(img_rgb24->data[i * 3 + 2], 0, 255, 0, 32);

        // Put values together in new image
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[i * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[i * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_RGB24_to_RGB8 (Image * img_rgb24)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Rescale values
        r_value = rescale_color(img_rgb24->data[i * 3], 0, 255, 0, 8);
        g_value = rescale_color(img_rgb24->data[i * 3 + 1], 0, 255, 0, 8);
        b_value = rescale_color(img_rgb24->data[i * 3 + 2], 0, 255, 0, 4);

        // Put values together in new image
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    return img_rgb8;
}


Image * convert_RGB24_to_GRAYSCALE (Image * img_rgb24)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t y_value = 0;

    if (!img_rgb24) return NULL;
    if (img_rgb24->format != RGB24) return NULL;

    width = img_rgb24->width;
    height = img_rgb24->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel has one Y value
    // Base image: RGB RGB RGB RGB
    // New image: YYYY
    for (i = 0; i < width * height; i++) {
        // Transform RGB -> Y
        y_value = rgb_to_yuv_y(img_rgb24->data[i * 3], img_rgb24->data[i * 3 + 1], img_rgb24->data[i * 3 + 2]);

        // Copy Y component
        img_grayscale->data[i] = y_value;
    }

    return img_grayscale;
}


Image * convert_RGB565_to_YUV444 (Image * img_rgb565)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value: YUV YUV YUV YUV

    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb565->data[2 * i] & 0x1f;
        g_value = ((img_rgb565->data[2 * i] & 0xe0) >> 5) | ((img_rgb565->data[2 * i + 1] & 0x07) << 3);
        r_value = (img_rgb565->data[2 * i + 1] & 0xf8) >> 3;

        // Rescale values
        r_value = rescale_color(r_value, 0, 32, 0, 255);
        g_value = rescale_color(g_value, 0, 64, 0, 255);
        b_value = rescale_color(b_value, 0, 32, 0, 255);

        // Transform RGB -> YUV and apply YUV values to new image
        img_yuv444->data[3 * i] = rgb_to_yuv_y(r_value, g_value, b_value);
        img_yuv444->data[3 * i + 1] = rgb_to_yuv_u(r_value, g_value, b_value);
        img_yuv444->data[3 * i + 2] = rgb_to_yuv_v(r_value, g_value, b_value);
    }

    return img_yuv444;
}


Image * convert_RGB565_to_YUV444p (Image * img_rgb565)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value: YYYY UUUU VVVV

    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb565->data[2 * i] & 0x1f;
        g_value = ((img_rgb565->data[2 * i] & 0xe0) >> 5) | ((img_rgb565->data[2 * i + 1] & 0x07) << 3);
        r_value = (img_rgb565->data[2 * i + 1] & 0xf8) >> 3;

        // Rescale values
        r_value = rescale_color(r_value, 0, 32, 0, 255);
        g_value = rescale_color(g_value, 0, 64, 0, 255);
        b_value = rescale_color(b_value, 0, 32, 0, 255);

        // Transform RGB -> YUV and apply YUV values to new image
        img_yuv444p->data[i] = rgb_to_yuv_y(r_value, g_value, b_value);
        img_yuv444p->data[i + width * height] = rgb_to_yuv_u(r_value, g_value, b_value);
        img_yuv444p->data[i + width * height * 2] = rgb_to_yuv_v(r_value, g_value, b_value);
    }

    return img_yuv444p;
}


Image * convert_RGB565_to_YUV420p (Image * img_rgb565)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, each pixel has one Y, one U and one V value: YYYY U V

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Extract R, G and B values
            b_value = img_rgb565->data[i * 2 * width + j * 2] & 0x1f;
            g_value = ((img_rgb565->data[i * 2 * width + j * 2] & 0xe0) >> 5) |
                      ((img_rgb565->data[i * 2 * width + j * 2 + 1] & 0x07) << 3);
            r_value = (img_rgb565->data[i * 2 * width + j * 2 + 1] & 0xf8) >> 3;

            // Rescale values
            r_value = rescale_color(r_value, 0, 32, 0, 255);
            g_value = rescale_color(g_value, 0, 64, 0, 255);
            b_value = rescale_color(b_value, 0, 32, 0, 255);

            // Transform RGB -> YUV and apply YUV values to new image
            img_yuv420p->data[i * width + j] = rgb_to_yuv_y(r_value, g_value, b_value);
            img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = rgb_to_yuv_u(r_value,
                                                                                                  g_value,
                                                                                                  b_value);
            img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = rgb_to_yuv_v(r_value,
                                                                                                  g_value,
                                                                                                  b_value);
        }
    }

    return img_yuv420p;
}


Image * convert_RGB565_to_RGB24 (Image * img_rgb565)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_rgb24 = create_image(width, height, RGB24);
    if (!img_rgb24) return NULL;

    // In RGB24, each pixel has one R, one G and one B value: RGB RGB RGB RGB

    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values for base image
        b_value = img_rgb565->data[2 * i] & 0x1f;
        g_value = ((img_rgb565->data[2 * i] & 0xe0) >> 5) | ((img_rgb565->data[2 * i + 1] & 0x07) << 3);
        r_value = (img_rgb565->data[2 * i + 1] & 0xf8) >> 3;

        // Rescale values
        r_value = rescale_color(r_value, 0, 32, 0, 255);
        g_value = rescale_color(g_value, 0, 64, 0, 255);
        b_value = rescale_color(b_value, 0, 32, 0, 255);

        // Apply scaled values to new image
        img_rgb24->data[3 * i] = r_value;
        img_rgb24->data[3 * i + 1] = g_value;
        img_rgb24->data[3 * i + 2] = b_value;
    }

    return img_rgb24;
}


Image * convert_RGB565_to_RGB8 (Image * img_rgb565)
{
    Image * img_rgb8 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_rgb8 = create_image(width, height, RGB8);
    if (!img_rgb8) return NULL;

    // In RGB8, R is encoded on 3 bits, G on 3 and B on 2, so we have 8 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values for base image
        b_value = img_rgb565->data[2 * i] & 0x1f;
        g_value = ((img_rgb565->data[2 * i] & 0xe0) >> 5) | ((img_rgb565->data[2 * i + 1] & 0x07) << 3);
        r_value = (img_rgb565->data[2 * i + 1] & 0xf8) >> 3;

        // Rescale values
        r_value = rescale_color(r_value, 0, 32, 0, 8);
        g_value = rescale_color(g_value, 0, 64, 0, 8);
        b_value = rescale_color(b_value, 0, 32, 0, 4);

        // Put values together in new image
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    return img_rgb8;
}


Image * convert_RGB565_to_GRAYSCALE (Image * img_rgb565)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb565) return NULL;
    if (img_rgb565->format != RGB565) return NULL;

    width = img_rgb565->width;
    height = img_rgb565->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel only has a single Y value: Y Y Y Y
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values for base image
        b_value = img_rgb565->data[2 * i] & 0x1f;
        g_value = ((img_rgb565->data[2 * i] & 0xe0) >> 5) | ((img_rgb565->data[2 * i + 1] & 0x07) << 3);
        r_value = (img_rgb565->data[2 * i + 1] & 0xf8) >> 3;

        // Rescale values
        r_value = rescale_color(r_value, 0, 32, 0, 255);
        g_value = rescale_color(g_value, 0, 64, 0, 255);
        b_value = rescale_color(b_value, 0, 32, 0, 255);

        // Convert values to Y-channel only
        img_grayscale->data[i] = rgb_to_yuv_y(r_value, g_value, b_value);
    }

    return img_grayscale;
}


Image * convert_RGB8_to_YUV444 (Image * img_rgb8)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value: YUV YUV YUV YUV
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb8->data[i] & 0x03;
        g_value = (img_rgb8->data[i] >> 2) & 0x07;
        r_value = (img_rgb8->data[i] >> 5) & 0x07;

        // Rescale values
        r_value = rescale_color(r_value, 0, 8, 0, 255);
        g_value = rescale_color(g_value, 0, 8, 0, 255);
        b_value = rescale_color(b_value, 0, 4, 0, 255);

        // Transform RGB -> YUV and apply YUV values to new image
        img_yuv444->data[3 * i] = rgb_to_yuv_y(r_value, g_value, b_value);
        img_yuv444->data[3 * i + 1] = rgb_to_yuv_u(r_value, g_value, b_value);
        img_yuv444->data[3 * i + 2] = rgb_to_yuv_v(r_value, g_value, b_value);
    }

    return img_yuv444;
}


Image * convert_RGB8_to_YUV444p (Image * img_rgb8)
{
    Image * img_yuv444p = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value: YYYY UUUU VVVV
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb8->data[i] & 0x03;
        g_value = (img_rgb8->data[i] >> 2) & 0x07;
        r_value = (img_rgb8->data[i] >> 5) & 0x07;

        // Rescale values
        r_value = rescale_color(r_value, 0, 8, 0, 255);
        g_value = rescale_color(g_value, 0, 8, 0, 255);
        b_value = rescale_color(b_value, 0, 4, 0, 255);

        // Transform RGB -> YUV and apply YUV values to new image
        img_yuv444p->data[i] = rgb_to_yuv_y(r_value, g_value, b_value);
        img_yuv444p->data[i + width * height] = rgb_to_yuv_u(r_value, g_value, b_value);
        img_yuv444p->data[i + width * height * 2] = rgb_to_yuv_v(r_value, g_value, b_value);
    }

    return img_yuv444p;
}


Image * convert_RGB8_to_YUV420p (Image * img_rgb8)
{
    Image * img_yuv420p = NULL;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t u_offset = 0;
    uint32_t v_offset = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420p, each pixel has one Y, one U and one V value: YYYY U V

    u_offset = width * height;
    v_offset = u_offset + UROUND_UP(width / 2) * UROUND_UP(height / 2);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Extract R, G and B values
            b_value = img_rgb8->data[i * width + j] & 0x03;
            g_value = (img_rgb8->data[i * width + j] >> 2) & 0x07;
            r_value = (img_rgb8->data[i * width + j] >> 5) & 0x07;

            // Rescale values
            r_value = rescale_color(r_value, 0, 8, 0, 255);
            g_value = rescale_color(g_value, 0, 8, 0, 255);
            b_value = rescale_color(b_value, 0, 4, 0, 255);

            // Transform RGB -> YUV and apply YUV values to new image
            img_yuv420p->data[i * width + j] = rgb_to_yuv_y(r_value, g_value, b_value);
            img_yuv420p->data[u_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = rgb_to_yuv_u(r_value,
                                                                                                  g_value,
                                                                                                  b_value);
            img_yuv420p->data[v_offset + (i / 2) * UROUND_UP(width / 2) + (j / 2)] = rgb_to_yuv_v(r_value,
                                                                                                  g_value,
                                                                                                  b_value);
        }
    }

    return img_yuv420p;
}


Image * convert_RGB8_to_RGB24 (Image * img_rgb8)
{
    Image * img_rgb24 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_rgb24 = create_image(width, height, RGB24);
    if (!img_rgb24) return NULL;

    // In RGB24, each pixel has one R, one G and one B value: RGB RGB RGB RGB

    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb8->data[i] & 0x03;
        g_value = (img_rgb8->data[i] >> 2) & 0x07;
        r_value = (img_rgb8->data[i] >> 5) & 0x07;

        // Rescale values
        r_value = rescale_color(r_value, 0, 8, 0, 255);
        g_value = rescale_color(g_value, 0, 8, 0, 255);
        b_value = rescale_color(b_value, 0, 4, 0, 255);

        // Apply scaled values to new image
        img_rgb24->data[3 * i] = r_value;
        img_rgb24->data[3 * i + 1] = g_value;
        img_rgb24->data[3 * i + 2] = b_value;
    }

    return img_rgb24;
}


Image * convert_RGB8_to_RGB565 (Image * img_rgb8)
{
    Image * img_rgb565 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_rgb565 = create_image(width, height, RGB565);
    if (!img_rgb565) return NULL;

    // In RGB565, R is encoded on 5 bits, G on 6 and B on 5, so we have 16 bits per pixel
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb8->data[i] & 0x03;
        g_value = (img_rgb8->data[i] >> 2) & 0x07;
        r_value = (img_rgb8->data[i] >> 5) & 0x07;

        // Rescale values
        r_value = rescale_color(r_value, 0, 8, 0, 32);
        g_value = rescale_color(g_value, 0, 8, 0, 64);
        b_value = rescale_color(b_value, 0, 4, 0, 32);

        // Put values together in new image
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[i * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[i * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    return img_rgb565;
}


Image * convert_RGB8_to_GRAYSCALE (Image * img_rgb8)
{
    Image * img_grayscale = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    if (!img_rgb8) return NULL;
    if (img_rgb8->format != RGB8) return NULL;

    width = img_rgb8->width;
    height = img_rgb8->height;

    // Allocate memory for new image
    img_grayscale = create_image(width, height, GRAYSCALE);
    if (!img_grayscale) return NULL;

    // In GRAYSCALE, each pixel only has one Y value: Y Y Y Y
    for (i = 0; i < width * height; i++) {
        // Extract R, G and B values
        b_value = img_rgb8->data[i] & 0x03;
        g_value = (img_rgb8->data[i] >> 2) & 0x07;
        r_value = (img_rgb8->data[i] >> 5) & 0x07;

        // Rescale values
        r_value = rescale_color(r_value, 0, 8, 0, 255);
        g_value = rescale_color(g_value, 0, 8, 0, 255);
        b_value = rescale_color(b_value, 0, 4, 0, 255);

        // Set Y-channel only
        img_grayscale->data[i] = rgb_to_yuv_y(r_value, g_value, b_value);
    }

    return img_grayscale;
}


Image * convert_GRAYSCALE_to_YUV444 (Image * img_grayscale)
{
    Image * img_yuv444 = NULL;
    uint32_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_grayscale) return NULL;
    if (img_grayscale->format != GRAYSCALE) return NULL;

    width = img_grayscale->width;
    height = img_grayscale->height;

    // Allocate memory for new image
    img_yuv444 = create_image(width, height, YUV444);
    if (!img_yuv444) return NULL;

    // In YUV444, each pixel has one Y, one U and one V value
    // Base image: YYYY
    // New image: YUV YUV YUV YUV
    // Since there is no U, V information in the base image, they will be set to 0
    for (i = 0; i < width * height; i++) {
        // Copy Y component
        img_yuv444->data[i * 3] = img_grayscale->data[i];
        // Set U component to be all zeroes, since there is no U data in the base image
        img_yuv444->data[i * 3 + 1] = 0;
        // Set V component to be all zeroes, since there is no U data in the base image
        img_yuv444->data[i * 3 + 2] = 0;
    }

    return img_yuv444;
}


Image * convert_GRAYSCALE_to_YUV444p (Image * img_grayscale)
{
    Image * img_yuv444p = NULL;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_grayscale) return NULL;
    if (img_grayscale->format != GRAYSCALE) return NULL;

    width = img_grayscale->width;
    height = img_grayscale->height;

    // Allocate memory for new image
    img_yuv444p = create_image(width, height, YUV444p);
    if (!img_yuv444p) return NULL;

    // In YUV444p, each pixel has one Y, one U and one V value
    // Base image: YYYY
    // New image: YYYY UUUU VVVV
    // Since there is no U, V information in the base image, they will be set to 0
    
    // Copy Y component
    memcpy(img_yuv444p->data, img_grayscale->data, width * height);
    // Set U component to be all zeroes, since there is no U data in the base image
    memset(&img_yuv444p->data[width * height], 0, width * height);
    // Set V component to be all zeroes, since there is no U data in the base image
    memset(&img_yuv444p->data[width * height * 2], 0, width * height);

    return img_yuv444p;
}


uint8_t rescale_color (uint8_t value, uint8_t old_min, uint8_t old_max, uint8_t new_min, uint8_t new_max)
{
    return (((float) value - old_min) / ((float) old_max - old_min)) * (new_max - new_min) + new_min;
}


uint8_t yuv_to_rgb_r (uint8_t y, uint8_t u, uint8_t v)
{
    (void) u; // U is unused
    int32_t r = 0;

    // Perform integer calculation of R value
    r = 298 * (y - 16) + 409 * (v - 128) + 128;

    // Offset to obtain "real" value
    r >>= 8;

    if (r < 0) return 0;
    if (r > 255) return 255;
    return (uint8_t) r;
}


uint8_t yuv_to_rgb_g (uint8_t y, uint8_t u, uint8_t v)
{
    int32_t g = 0;

    // Perform integer calculation of G value
    g = 298 * (y - 16) - 100 * (u - 128) - 208 * (v - 128) + 128;

    // Offset to obtain "real" value
    g >>= 8;

    if (g < 0) return 0;
    if (g > 255) return 255;
    return (uint8_t) g;
}


uint8_t yuv_to_rgb_b (uint8_t y, uint8_t u, uint8_t v)
{
    (void) v; // V is unused
    int32_t b = 0;

    // Perform integer calculation of R value
    b = 298 * (y - 16) + 516 * (u - 128) + 128;

    // Offset to obtain "real" value
    b >>= 8;

    if (b < 0) return 0;
    if (b > 255) return 255;
    return (uint8_t) b;
}


uint8_t rgb_to_yuv_y (uint8_t r, uint8_t g, uint8_t b)
{
    int32_t y = 0;

    // Perform integer calculation of Y value
    y = 66 * r + 129 * g + 25 * b + 128;

    // Offset to obtain "real" value
    y = (y >> 8) + 16;

    if (y < 0) return 0;
    if (y > 255) return 255;
    return (uint8_t) y;
}


uint8_t rgb_to_yuv_u (uint8_t r, uint8_t g, uint8_t b)
{
    int32_t u = 0;

    // Perform integer calculation of U value
    u = -38 * r - 74 * g + 112 * b + 128;

    // Offset to obtain "real" value
    u = (u >> 8) + 128;

    if (u < 0) return 0;
    if (u > 255) return 255;
    return (uint8_t) u;
}


uint8_t rgb_to_yuv_v (uint8_t r, uint8_t g, uint8_t b)
{
    int32_t v = 0;

    // Perform integer calculation of V value
    v = 112 * r - 94 * g - 18 * b + 128;

    // Offset to obtain "real" value
    v = (v >> 8) + 128;

    if (v < 0) return 0;
    if (v > 255) return 255;
    return (uint8_t) v;
}
