#include "libuimg.h"

#include <time.h>
#include <stdlib.h>

#define MIN_WIDTH  1
#define MAX_WIDTH  10
#define MIN_HEIGHT 1
#define MAX_HEIGHT 10

#define RAND_RANGE(min, max) ((uint16_t)((rand() % (((max) + 1) - (min))) + (min)))


Image_t * generate_image (uint16_t width, uint16_t height, PixelFormat_t format)
{
    Image_t * img = create_image(width, height, format);
    uint8_t max_pixel_value = UINT8_MAX;
    uint32_t data_size = get_image_data_size(img->width, img->height, img->format);

    if (format == ASCII) {
        // See img.c; the ASCII format has a different range.
        max_pixel_value = 11;
    }

    for (uint32_t i = 0; i < data_size; i++) {
        img->data[i] = RAND_RANGE(0, max_pixel_value);
    }

    return img;
}


int main (void)
{
    srand(time(NULL));

    Image_t * yuv420p = generate_image(RAND_RANGE(MIN_WIDTH, MAX_WIDTH), RAND_RANGE(MIN_HEIGHT, MAX_HEIGHT), YUV420p);
    Image_t * ascii = generate_image(RAND_RANGE(MIN_WIDTH, MAX_WIDTH), RAND_RANGE(MIN_HEIGHT, MAX_HEIGHT), ASCII);

    save_image(yuv420p, "in/yuv420p.img");
    save_image(ascii, "in/ascii.img");

    destroy_image(yuv420p);
    destroy_image(ascii);

    return 0;
}
