#include "libuimg.h"

/**
 * This file is an entry point to libuimg, used for fuzzing. Essentially, it uses all of
 * the available features of the library, in the hopes of finding some bug in one of
 * them.
 */

static void stress_test_image (Image_t * img, const char * img_file)
{
    PixelFormat_t formats[] = { YUV444, YUV444p, YUV420p, RGB24, RGB565, RGB8, GRAYSCALE, ASCII };
    uint8_t res = 0;
    Image_t * img2 = NULL;

    res = flipX_image(img);
    if (res != 1) {
        fprintf(stderr, "Unsuccessful first X-flip for image %s.\n", img_file);
    }
    res = flipY_image(img);
    if (res != 1) {
        fprintf(stderr, "Unsuccessful first Y-flip for image %s.\n", img_file);
    }

    if (!img) {
        fprintf(stderr, "Invalid image %s, cannot proceed to conversions.\n", img_file);
        return;
    }

    // Perform operations on the image for every available format.
    for (int i = 0; i < sizeof(formats) / sizeof(PixelFormat_t); i++) {
        img2 = create_image(img->width, img->height, formats[i]);
        res = convert_image(img, img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful conversion while converting %s to format %d.\n", img_file, formats[i]);
        }
        res = flipX_image(img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful X-flip for %s in format %d.\n", img_file, formats[i]);
        }
        flipY_image(img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful Y-flip for %s in format %d.\n", img_file, formats[i]);
        }
        destroy_image(img2);
    }
}

int main (int argc, char * argv[])
{
    Image_t * img = NULL;
    uint16_t width = 0;
    uint16_t height = 0;
    PixelFormat_t format = 0;
    uint8_t res = 0;

    // An image file is used as an input.
    if (argc != 2) {
        printf("Usage: %s <image file>\n", argv[0]);
    }

    // Load the image dynamically first.
    img = load_image(argv[1]);

    stress_test_image(img, argv[1]);

    // The image needs to be non-null for us to load it statically.
    if (img) {
        // Save the properties of the image to load it again.
        width = img->width;
        height = img->height;
        format = img->format;
        destroy_image(img);

        // Load the image statically this time.
        img = create_image(width, height, format);
        res = load_static_image(img, argv[1]);
        if (res != 1) {
            fprintf(stderr, "Could not load image %s.\n", argv[1]);
        }

        stress_test_image(img, argv[1]);
    }

    destroy_image(img);

    return 0;
}
