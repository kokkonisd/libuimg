#include "libuimg/img.h"


static uint32_t get_image_data_size (uint16_t width, uint16_t height, PixelFormat_t format)
{
    uint32_t data_size = 0;

    switch (format) {
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
        case ASCII:
            data_size = width * height;
            break;

        default:
            data_size = 0;
            break;
    }

    return data_size;
}


Image_t * create_image (uint16_t width, uint16_t height, PixelFormat_t format)
{
    uint32_t data_size = 0;

    // Create new image
    Image_t * new_image = calloc(1, sizeof(Image_t));
    if (!new_image) return NULL;

    // Fill in width, height and pixel format
    new_image->width = width;
    new_image->height = height;
    new_image->format = format;
    new_image->data = NULL;

    // Get data size based on format
    data_size = get_image_data_size(width, height, format);

    // Allocate the calculated size
    new_image->data = calloc(1, sizeof(uint8_t) * data_size);
    if (!new_image->data) {
        free(new_image);
        return NULL;
    }

    return new_image;
}


void destroy_image (Image_t * img)
{
    if (img->data) free(img->data);
    if (img) free(img);
}


uint8_t save_image (Image_t * img, const char * filepath)
{
    FILE * image_file = NULL;
    size_t res = 0;
    uint32_t data_size = 0;

    if (!img) return 0;

    image_file = fopen(filepath, "wb");
    if (!image_file) return 0;

    // Write the width, height and pixel format first.
    res = fwrite(&img->width, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    res = fwrite(&img->height, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    res = fwrite(&img->format, sizeof(PixelFormat_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    // Write the raw image data.
    data_size = get_image_data_size(img->width, img->height, img->format);
    res = fwrite(img->data, sizeof(uint8_t), data_size, image_file);
    if (res != data_size) {
        fclose(image_file);
        return 0;
    }

    fclose(image_file);

    return 1;
}


Image_t * load_image (const char * filepath)
{
    FILE * image_file = NULL;
    Image_t * img = NULL;
    uint16_t width = 0;
    uint16_t height = 0;
    PixelFormat_t format = 0;
    size_t res = 0;
    uint32_t data_size = 0;

    image_file = fopen(filepath, "rb");
    if (!image_file) return NULL;

    // Load the width, height and pixel format first.
    res = fread(&width, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return NULL;
    }

    res = fread(&height, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return NULL;
    }

    res = fread(&format, sizeof(PixelFormat_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return NULL;
    }

    // Create the image structure.
    img = create_image(width, height, format);

    // Load the raw image data.
    data_size = get_image_data_size(img->width, img->height, img->format);
    res = fread(img->data, sizeof(uint8_t), data_size, image_file);
    if (res != data_size) {
        destroy_image(img);
        fclose(image_file);
        return NULL;
    }

    fclose(image_file);

    return img;
}


uint8_t load_static_image (Image_t * img, const char * filepath)
{
    FILE * image_file = NULL;
    uint16_t width = 0;
    uint16_t height = 0;
    PixelFormat_t format = 0;
    size_t res = 0;
    uint32_t data_size = 0;

    if (!img) return 0;

    image_file = fopen(filepath, "rb");
    if (!image_file) return 0;

    // Load the width, height and pixel format first.
    res = fread(&width, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    res = fread(&height, sizeof(uint16_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    res = fread(&format, sizeof(PixelFormat_t), 1, image_file);
    if (res != 1) {
        fclose(image_file);
        return 0;
    }

    // Check that the data we just read matches the expected image data.
    if (width != img->width) {
        fclose(image_file);
        return 0;
    }
    if (height != img->height) {
        fclose(image_file);
        return 0;
    }
    if (format != img->format) {
        fclose(image_file);
        return 0;
    }

    // Load the raw image data.
    data_size = get_image_data_size(img->width, img->height, img->format);
    res = fread(img->data, sizeof(uint8_t), data_size, image_file);
    if (res != data_size) {
        fclose(image_file);
        return 0;
    }

    fclose(image_file);

    return 1;
}
