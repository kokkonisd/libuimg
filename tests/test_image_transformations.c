#include "cuts.h"

#include "libuimg.h"


// Both dimensions shouldn't be greater than 2^8 - 1, because then the verification method using ASCII characters and a
// counter will not work.
#define IMG_WIDTH 255
#define IMG_HEIGHT 127


char * test_flipY_for_YUV444 ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_yuv444 = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_yuv444 = create_image(width, height, YUV444);
    // Fill image
    for (i = 0; i < height * 3; i += 3) {
        counter = 0;

        for (j = 0; j < width * 3; j += 3) {
            // Fill in Y component
            img_yuv444->data[i * width + j] = 'Y' | counter;
            // Fill in U component
            img_yuv444->data[i * width + j + 1] = 'U' | counter;
            // Fill in V component
            img_yuv444->data[i * width + j + 2] = 'V' | counter;

            counter++;
        }
    }


    // Flip image along the Y axis
    res = flipY_image(img_yuv444);
    CUTS_ASSERT(res == 1, "Could not flip YUV444 image along the Y axis");

    // Evaluate result
    for (i = 0; i < height * 3; i += 3) {
        counter = width - 1;
        
        for (j = 0; j < width * 3; j += 3) {
            // Evaluate Y component
            CUTS_ASSERT(img_yuv444->data[i * width + j] == ('Y' | counter), "Wrong Y value for pixel %d",
                        i / 3 * width + j / 3);
            // Evaluate U component
            CUTS_ASSERT(img_yuv444->data[i * width + j + 1] == ('U' | counter), "Wrong U value for pixel %d",
                        i / 3 * width + j / 3);
            // Evaluate V component
            CUTS_ASSERT(img_yuv444->data[i * width + j + 2] == ('V' | counter), "Wrong V value for pixel %d",
                        i / 3 * width + j / 3);

            counter--;
        }
    }

    destroy_image(img_yuv444);

    return NULL;
}


char * test_flipY_for_YUV444p ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_yuv444p = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_yuv444p = create_image(width, height, YUV444p);
    // Fill image
    for (i = 0; i < height; i++) {
        counter = 0;

        for (j = 0; j < width; j++) {
            // Fill in Y component
            img_yuv444p->data[i * width + j] = 'Y' | counter;
            // Fill in U component
            img_yuv444p->data[width * height + i * width + j] = 'U' | counter;
            // Fill in V component
            img_yuv444p->data[width * height * 2 + i * width + j] = 'V' | counter;

            counter++;
        }
    }


    // Flip image along the Y axis
    res = flipY_image(img_yuv444p);
    CUTS_ASSERT(res == 1, "Could not flip YUV444p image along the Y axis");

    // Evaluate result
    for (i = 0; i < height; i++) {
        counter = width - 1;
        
        for (j = 0; j < width; j++) {
            // Evaluate Y component
            CUTS_ASSERT(img_yuv444p->data[i * width + j] == ('Y' | counter), "Wrong Y value for pixel %d",
                        i * width + j);
            // Evaluate U component
            CUTS_ASSERT(img_yuv444p->data[width * height + i * width + j] == ('U' | counter),
                        "Wrong U value for pixel %d", i * width + j);
            // Evaluate V component
            CUTS_ASSERT(img_yuv444p->data[width * height * 2 + i * width + j] == ('V' | counter),
                        "Wrong V value for pixel %d", i * width + j);

            counter--;
        }
    }

    destroy_image(img_yuv444p);

    return NULL;
}


char * test_flipY_for_YUV420p ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_yuv420p = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_yuv420p = create_image(width, height, YUV420p);
    // Fill image
    for (i = 0; i < height; i++) {
        counter = 0;

        for (j = 0; j < width; j++) {
            // Fill in Y component
            img_yuv420p->data[i * width + j] = 'Y' | counter;

            counter++;
        }
    }

    for (i = 0; i < UROUND_UP(height / 2); i++) {
        counter = 0;

        for (j = 0; j < UROUND_UP(width / 2); j++) {
            // Fill in U component
            img_yuv420p->data[width * height + i * UROUND_UP(width / 2) + j] = 'U' | counter;
            // Fill in V component
            img_yuv420p->data[width * height +
                              UROUND_UP(width / 2) * UROUND_UP(height / 2) +
                              i * UROUND_UP(width / 2) + j] = 'V' | counter;

            counter++;
        }
    }


    // Flip image along the Y axis
    res = flipY_image(img_yuv420p);
    CUTS_ASSERT(res == 1, "Could not flip YUV420p image along the Y axis");

    // Evaluate result
    for (i = 0; i < height; i++) {
        counter = width - 1;
        
        for (j = 0; j < width; j++) {
            // Evaluate Y component
            CUTS_ASSERT(img_yuv420p->data[i * width + j] == ('Y' | counter), "Wrong Y value for pixel %d",
                        i * width + j);

            counter--;
        }
    }

    for (i = 0; i < UROUND_UP(height / 2); i++) {
        counter = UROUND_UP(width / 2) - 1;

        for (j = 0; j < UROUND_UP(width / 2); j++) {
            // Evaluate U component
            CUTS_ASSERT(img_yuv420p->data[width * height + i * UROUND_UP(width / 2) + j] == ('U' | counter),
                        "Wrong U value for pixel %d", i * UROUND_UP(width / 2) + j);
            // Evaluate V component
            CUTS_ASSERT(img_yuv420p->data[width * height +
                                          UROUND_UP(width / 2) * UROUND_UP(height / 2) +
                                          i * UROUND_UP(width / 2) + j] == ('V' | counter),
                        "Wrong V value for pixel %d", i * UROUND_UP(width / 2) + j);

            counter--;
        }
    }

    destroy_image(img_yuv420p);

    return NULL;
}


char * test_flipY_for_RGB24 ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_rgb24 = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_rgb24 = create_image(width, height, RGB24);
    // Fill image
    for (i = 0; i < height * 3; i += 3) {
        counter = 0;

        for (j = 0; j < width * 3; j += 3) {
            // Fill in R component
            img_rgb24->data[i * width + j] = 'R' | counter;
            // Fill in G component
            img_rgb24->data[i * width + j + 1] = 'G' | counter;
            // Fill in B component
            img_rgb24->data[i * width + j + 2] = 'B' | counter;

            counter++;
        }
    }


    // Flip image along the Y axis
    res = flipY_image(img_rgb24);
    CUTS_ASSERT(res == 1, "Could not flip RGB24 image along the Y axis");

    // Evaluate result
    for (i = 0; i < height * 3; i += 3) {
        counter = width - 1;
        
        for (j = 0; j < width * 3; j += 3) {
            // Evaluate R component
            CUTS_ASSERT(img_rgb24->data[i * width + j] == ('R' | counter), "Wrong R value for pixel %d",
                        i / 3 * width + j / 3);
            // Evaluate G component
            CUTS_ASSERT(img_rgb24->data[i * width + j + 1] == ('G' | counter), "Wrong G value for pixel %d",
                        i / 3 * width + j / 3);
            // Evaluate B component
            CUTS_ASSERT(img_rgb24->data[i * width + j + 2] == ('B' | counter), "Wrong B value for pixel %d",
                        i / 3 * width + j / 3);

            counter--;
        }
    }

    destroy_image(img_rgb24);

    return NULL;
}


char * test_flipY_for_RGB565 ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_rgb565 = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;

    // Create image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    expected_r = rescale_color('R', 0, 255, 0, 32);
    expected_g = rescale_color('G', 0, 255, 0, 64);
    expected_b = rescale_color('B', 0, 255, 0, 32);

    // Fill image
    for (i = 0; i < height * 2; i += 2) {
        counter = 0;

        for (j = 0; j < width * 2; j += 2) {
            // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
            img_rgb565->data[i * width + j] = (expected_b & 0x1f) | ((expected_g & 0x07) << 5) | counter;
            img_rgb565->data[i * width + j + 1] = ((expected_g & 0x38) >> 3) | ((expected_r & 0x1f) << 3) | counter;

            counter++;
        }
    }

    // Flip image along the Y axis
    res = flipY_image(img_rgb565);
    CUTS_ASSERT(res == 1, "Could not flip RGB565 image along the Y axis");

    // Evaluate result
    for (i = 0; i < height * 2; i += 2) {
        counter = width - 1;
        
        for (j = 0; j < width * 2; j += 2) {
            // Get actual R, G, B
            actual_b = img_rgb565->data[i * width + j] & 0x1f;
            actual_g = ((img_rgb565->data[i * width + j] >> 5) & 0x07) |
                       ((img_rgb565->data[i * width + j + 1] & 0x07) << 3);
            actual_r = (img_rgb565->data[i * width + j + 1] >> 3) & 0x1f;

            CUTS_ASSERT(img_rgb565->data[i * width + j] == ((expected_b & 0x1f) |
                                                            ((expected_g & 0x07) << 5) |
                                                            counter),
                        "Wrong first byte value for RGB565 image on pixel %d", i);
            CUTS_ASSERT(img_rgb565->data[i * width + j + 1] == (((expected_g & 0x38) >> 3) |
                                                                ((expected_r & 0x1f) << 3) |
                                                                counter),
                        "Wrong second byte value for RGB565 image on pixel %d", i);

            counter--;
        }
    }

    destroy_image(img_rgb565);

    return NULL;
}


char * test_flipY_for_RGB8 ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_rgb8 = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_rgb8 = create_image(width, height, RGB8);
    // Fill image
    for (i = 0; i < height; i++) {
        counter = 0;

        for (j = 0; j < width; j++) {
            // Fill in image
            img_rgb8->data[i * width + j] = counter;

            counter++;
        }
    }

    // Flip image along the Y axis
    res = flipY_image(img_rgb8);
    CUTS_ASSERT(res == 1, "Could not flip RGB8 image along the Y axis");

    // Evaluate result
    for (i = 0; i < height; i++) {
        counter = width - 1;
        
        for (j = 0; j < width; j++) {
            // Evaluate image bytes
            CUTS_ASSERT(img_rgb8->data[i * width + j] == counter, "Wrong value for byte %d", i * width + j);

            counter--;
        }
    }

    destroy_image(img_rgb8);

    return NULL;
}


char * test_flipY_for_GRAYSCALE ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_grayscale = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Fill image
    for (i = 0; i < height; i++) {
        counter = 0;

        for (j = 0; j < width; j++) {
            // Fill in image
            img_grayscale->data[i * width + j] = counter;

            counter++;
        }
    }

    // Flip image along the Y axis
    res = flipY_image(img_grayscale);
    CUTS_ASSERT(res == 1, "Could not flip GRAYSCALE image along the Y axis");

    // Evaluate result
    for (i = 0; i < height; i++) {
        counter = width - 1;
        
        for (j = 0; j < width; j++) {
            // Evaluate image bytes
            CUTS_ASSERT(img_grayscale->data[i * width + j] == counter, "Wrong value for byte %d", i * width + j);

            counter--;
        }
    }

    destroy_image(img_grayscale);

    return NULL;
}


char * test_flipY_for_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    Image_t * img_ascii = NULL;
    uint16_t width = IMG_WIDTH;
    uint16_t height = IMG_HEIGHT;
    uint16_t counter = 0;
    uint8_t res = 0;

    // Create image
    img_ascii = create_image(width, height, ASCII);
    // Fill image
    for (i = 0; i < height; i++) {
        counter = 0;

        for (j = 0; j < width; j++) {
            // Fill in image
            img_ascii->data[i * width + j] = counter;

            counter++;
        }
    }

    // Flip image along the Y axis
    res = flipY_image(img_ascii);
    CUTS_ASSERT(res == 1, "Could not flip ASCII image along the Y axis");

    // Evaluate result
    for (i = 0; i < height; i++) {
        counter = width - 1;
        
        for (j = 0; j < width; j++) {
            // Evaluate image bytes
            CUTS_ASSERT(img_ascii->data[i * width + j] == counter, "Wrong value for byte %d", i * width + j);

            counter--;
        }
    }

    destroy_image(img_ascii);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(test_flipY_for_YUV444);
    CUTS_RUN_TEST(test_flipY_for_YUV444p);
    CUTS_RUN_TEST(test_flipY_for_YUV420p);
    CUTS_RUN_TEST(test_flipY_for_RGB24);
    CUTS_RUN_TEST(test_flipY_for_RGB565);
    CUTS_RUN_TEST(test_flipY_for_RGB8);
    CUTS_RUN_TEST(test_flipY_for_GRAYSCALE);
    CUTS_RUN_TEST(test_flipY_for_ASCII);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
