#include "libuimg_img.h"


Image * create_image (uint16_t width, uint16_t height, PixelFormat_t format)
{
    uint32_t data_size = 0;

    // Create new image
    Image * new_image = calloc(1, sizeof(Image));
    if (!new_image) return NULL;

    // Fill in width, height and pixel format
    new_image->width = width;
    new_image->height = height;
    new_image->format = format;
    new_image->data = NULL;

    // Get data size based on format
    switch (format) {
        default:
        case YUV444:
        case YUV444p:
        case RGB24:
            data_size = width * height * 3;
            break;

        case RGB565:
            data_size = width * height * 2;
            break;

        case YUV420p:
            data_size = width * height + 2 * (UROUND_UP(width / 2) * UROUND_UP(height / 2));
            break;

        case RGB8:
        case GRAYSCALE:
            data_size = width * height;
            break;
    }

    // Allocate the calculated size
    new_image->data = calloc(1, sizeof(uint8_t) * data_size);
    if (!new_image->data) return NULL;

    return new_image;
}


void destroy_image (Image * img)
{
    if (img->data) free(img->data);
    if (img) free(img);
}
