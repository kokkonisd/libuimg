#include "libuimg.h"

int main (int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: %s <image file>\n", argv[0]);
    }

    Image_t * img1 = load_image(argv[1]);
    if (!img1) {
        fprintf(stderr, "Could not load image %s.\n", argv[1]);
        return 1;
    }


    Image_t * img2 = NULL;
    PixelFormat_t formats[] = { YUV444, YUV444p, YUV420p, RGB24, RGB565, RGB8, GRAYSCALE, ASCII };
    uint8_t res = 0;

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
