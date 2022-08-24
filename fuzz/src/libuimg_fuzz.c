#include "libuimg.h"

/**
 * This file is an entry point to libuimg, used for fuzzing. Essentially, it uses all of
 * the available features of the library, in the hopes of finding some bug in one of
 * them.
 */

int main (int argc, char * argv[])
{
    Image_t * img1 = NULL;
    Image_t * img2 = NULL;
    uint16_t width = 0;
    uint16_t height = 0;
    PixelFormat_t formats[] = { YUV444, YUV444p, YUV420p, RGB24, RGB565, RGB8, GRAYSCALE, ASCII };
    PixelFormat_t format = formats[0];
    uint8_t res = 0;

    // An image file is used as an input.
    if (argc != 2) {
        printf("Usage: %s <image file>\n", argv[0]);
    }

    // Load the image dynamically first.
    img1 = load_image(argv[1]);
    if (!img1) {
        fprintf(stderr, "Could not load image %s.\n", argv[1]);
        return 1;
    }

    // Save the properties of the image to load it again.
    width = img1->width;
    height = img1->height;
    format = img1->format;
    destroy_image(img1);

    // Load the image statically this time.
    img1 = create_image(width, height, format);
    res = load_static_image(img1, argv[1]);
    if (res != 1) {
        fprintf(stderr, "Could not load image %s.\n", argv[1]);
        return 1;
    }

    // Perform operations on the image for every available format.
    for (int i = 0; i < sizeof(formats) / sizeof(PixelFormat_t); i++) {
        img2 = create_image(img1->width, img1->height, formats[i]);
        res = convert_image(img1, img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful conversion while converting %s to format %d.\n", argv[1], formats[i]);
        }
        res = flipX_image(img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful X-flip for %s in format %d.\n", argv[1], formats[i]);
        }
        flipY_image(img2);
        if (res != 1) {
            fprintf(stderr, "Unsuccessful Y-flip for %s in format %d.\n", argv[1], formats[i]);
        }
        destroy_image(img2);
    }

    destroy_image(img1);

    return 0;
}
