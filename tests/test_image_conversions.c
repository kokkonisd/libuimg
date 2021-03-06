#include "cuts.h"

#include "libuimg.h"

#define TEST_WIDTH 257
#define TEST_HEIGHT 125


char * test_image_conversion_YUV444_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_yuv444p = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_yuv444, img_yuv444p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == 'Y', "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == 'U', "Wrong U value for YUV444p image on pixel %d", i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == 'V', "Wrong V value for YUV444p image on pixel %d",
                    i);
    }

    destroy_image(img_yuv444);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_YUV444_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_yuv420p = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_yuv444, img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'Y', "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for YUV420p image on pixel %d", i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == 'V',
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_yuv444);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_YUV444_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_rgb24 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_yuv444, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check R channel
        CUTS_ASSERT(img_rgb24->data[i * 3] == yuv_to_rgb_r('Y', 'U', 'V'),
                    "Wrong R value for RGB24 image on pixel %d", i / 3);
        // Check G channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 1] == yuv_to_rgb_g('Y', 'U', 'V'),
                    "Wrong G value for RGB24 image on pixel %d", i / 3);
        // Check B channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 2] == yuv_to_rgb_b('Y', 'U', 'V'),
                    "Wrong B value for RGB24 image on pixel %d", i / 3);
    }

    destroy_image(img_yuv444);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_YUV444_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_rgb565 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_yuv444, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 32);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 64);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (expected_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_yuv444);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_YUV444_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_rgb8 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_yuv444, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb8->data[i] & 0x03;
        actual_g = (img_rgb8->data[i] >> 2) & 0x7;
        actual_r = (img_rgb8->data[i] >> 5) & 0x7;

        CUTS_ASSERT(actual_r == (expected_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_yuv444);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_YUV444_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_grayscale = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_yuv444, img_grayscale);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv444);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_YUV444_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444 = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Set Y values
            img_yuv444->data[i * 3 * width + j * 3] = curr_value;
            img_yuv444->data[i * 3 * width + j * 3 + 1] = 'U';
            img_yuv444->data[i * 3 * width + j * 3 + 2] = 'V';
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_yuv444, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(curr_value),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_yuv444);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_YUV444p_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_yuv444 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_yuv444p, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == 'Y', "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == 'U', "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == 'V', "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_YUV444p_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_yuv420p = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_yuv444p, img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'Y', "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for YUV420p image on pixel %d", i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == 'V',
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_YUV444p_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_rgb24 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_yuv444p, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check R channel
        CUTS_ASSERT(img_rgb24->data[i * 3] == yuv_to_rgb_r('Y', 'U', 'V'),
                    "Wrong R value for RGB24 image on pixel %d", i / 3);
        // Check G channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 1] == yuv_to_rgb_g('Y', 'U', 'V'),
                    "Wrong G value for RGB24 image on pixel %d", i / 3);
        // Check B channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 2] == yuv_to_rgb_b('Y', 'U', 'V'),
                    "Wrong B value for RGB24 image on pixel %d", i / 3);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_YUV444p_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_rgb565 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_yuv444p, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 32);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 64);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (expected_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_YUV444p_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_rgb8 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_yuv444p, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb8->data[i] & 0x03;
        actual_g = (img_rgb8->data[i] >> 2) & 0x07;
        actual_r = (img_rgb8->data[i] >> 5) & 0x07;

        CUTS_ASSERT(actual_r == (expected_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_YUV444p_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_grayscale = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_yuv444p, img_grayscale);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_YUV444p_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv444p = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Set Y values
            img_yuv444p->data[i * width + j] = curr_value;
            img_yuv444p->data[width * height + i * width + j] = 'U';
            img_yuv444p->data[width * height * 2 + i * width + j] = 'V';
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_yuv444p, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(curr_value),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_yuv444p);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_YUV420p_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_yuv444 = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_yuv420p, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == 'Y', "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == 'U', "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == 'V', "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_YUV420p_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_yuv444p = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_yuv420p, img_yuv444p);


    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == 'Y', "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == 'U', "Wrong U value for YUV444p image on pixel %d", i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == 'V', "Wrong V value for YUV444p image on pixel %d: %c",
                    i, img_yuv444p->data[i + width * height * 2]);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_YUV420p_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_rgb24 = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_yuv420p, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check R channel
        CUTS_ASSERT(img_rgb24->data[i * 3] == yuv_to_rgb_r('Y', 'U', 'V'),
                    "Wrong R value for RGB24 image on pixel %d", i / 3);
        // Check G channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 1] == yuv_to_rgb_g('Y', 'U', 'V'),
                    "Wrong G value for RGB24 image on pixel %d", i / 3);
        // Check B channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 2] == yuv_to_rgb_b('Y', 'U', 'V'),
                    "Wrong B value for RGB24 image on pixel %d", i / 3);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_YUV420p_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_rgb565 = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_yuv420p, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 32);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 64);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (expected_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_YUV420p_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_rgb8 = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_yuv420p, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb8->data[i] & 0x03;
        actual_g = (img_rgb8->data[i] >> 2) & 0x07;
        actual_r = (img_rgb8->data[i] >> 5) & 0x07;

        CUTS_ASSERT(actual_r == (expected_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_YUV420p_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_grayscale = NULL;

    // Create YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);

    // Set image pixels to the appropriate values
    // Set Y values
    memset(img_yuv420p->data, 'Y', width * height);

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Set U values
        img_yuv420p->data[i] = 'U';
        // Set Y values
        img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] = 'V';
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_yuv420p, img_grayscale);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_YUV420p_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_yuv420p = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;

    // Create YUV444 image
    img_yuv420p = create_image(width, height, YUV420p);
    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Set Y values
            img_yuv420p->data[i * width + j] = curr_value;
            img_yuv420p->data[width * height + (i / 2)  * UROUND_UP(width / 2) + (j / 2)] = 'U';
            img_yuv420p->data[width * height +
                              UROUND_UP(width / 2) * UROUND_UP(height / 2) +
                              (i / 2) * UROUND_UP(width / 2) + 
                              (j / 2)] = 'V';
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_yuv420p, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(curr_value),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_yuv420p);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_RGB24_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_yuv444 = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_rgb24, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y('R', 'G', 'B');
    u_value = rgb_to_yuv_u('R', 'G', 'B');
    v_value = rgb_to_yuv_v('R', 'G', 'B');

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == y_value, "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == u_value, "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == v_value, "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_rgb24);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_RGB24_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_yuv444p = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_rgb24, img_yuv444p);

    // Calculate expected values
    y_value = rgb_to_yuv_y('R', 'G', 'B');
    u_value = rgb_to_yuv_u('R', 'G', 'B');
    v_value = rgb_to_yuv_v('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == y_value, "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == u_value, "Wrong U value for YUV444p image on pixel %d",
                    i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == v_value,
                    "Wrong V value for YUV444p image on pixel %d", i);
    }

    destroy_image(img_rgb24);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_RGB24_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_yuv420p = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_rgb24, img_yuv420p);

    // Calculate expected values
    y_value = rgb_to_yuv_y('R', 'G', 'B');
    u_value = rgb_to_yuv_u('R', 'G', 'B');
    v_value = rgb_to_yuv_v('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == y_value, "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == u_value, "Wrong U value for YUV420p image on pixel %d",
                    i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == v_value,
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_rgb24);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_RGB24_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_rgb565 = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_rgb24, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    expected_r = rescale_color('R', 0, 255, 0, 32);
    expected_g = rescale_color('G', 0, 255, 0, 64);
    expected_b = rescale_color('B', 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (expected_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_rgb24);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_RGB24_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_rgb8 = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_rgb24, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    expected_r = rescale_color('R', 0, 255, 0, 8);
    expected_g = rescale_color('G', 0, 255, 0, 8);
    expected_b = rescale_color('B', 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb8->data[i] & 0x03;
        actual_g = (img_rgb8->data[i] >> 2) & 0x7;
        actual_r = (img_rgb8->data[i] >> 5) & 0x7;

        CUTS_ASSERT(actual_r == (expected_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_rgb24);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_RGB24_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t y_value = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_grayscale = NULL;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set R values
        img_rgb24->data[i] = 'R';
        // Set G values
        img_rgb24->data[i + 1] = 'G';
        // Set B values
        img_rgb24->data[i + 2] = 'B';
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_rgb24, img_grayscale);

    // Calculate expected value
    y_value = rgb_to_yuv_y('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == y_value, "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_rgb24);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_RGB24_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_rgb24 = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;

    // Create RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Set RGB values
            img_rgb24->data[i * 3 * width + j * 3] = curr_value;
            img_rgb24->data[i * 3 * width + j * 3 + 1] = curr_value;
            img_rgb24->data[i * 3 * width + j * 3 + 2] = curr_value;
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_rgb24, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(rgb_to_yuv_y(curr_value, curr_value, curr_value)),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_rgb24);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_RGB565_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_yuv444 = NULL;

    // Create RGB565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_rgb565, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == y_value, "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == u_value, "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == v_value, "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_rgb565);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_RGB565_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_yuv444p = NULL;

    // Create RGB565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_rgb565, img_yuv444p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == y_value, "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == u_value, "Wrong U value for YUV444p image on pixel %d",
                    i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == v_value,
                    "Wrong V value for YUV444p image on pixel %d", i);
    }

    destroy_image(img_rgb565);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_RGB565_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_yuv420p = NULL;

    // Create RGB565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_rgb565, img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == y_value, "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == u_value, "Wrong U value for YUV420p image on pixel %d",
                    i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == v_value,
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_rgb565);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_RGB565_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_rgb24 = NULL;

    // Create RGB565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_rgb565, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");


    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_rgb24->data[i] == r_value, "Wrong R value for RGB24 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_rgb24->data[i + 1] == g_value, "Wrong G value for RGB24 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_rgb24->data[i + 2] == b_value, "Wrong B value for RGB24 image on pixel %d", i / 3);
    }

    destroy_image(img_rgb565);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_RGB565_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_rgb8 = NULL;

    // Create RGΒ565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_rgb565, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Downscale values further to 8-bit space
    r_value = rescale_color(r_value, 0, 32, 0, 8);
    g_value = rescale_color(g_value, 0, 64, 0, 8);
    b_value = rescale_color(b_value, 0, 32, 0, 4);

    for (i = 0; i < width * height; i++) {
        CUTS_ASSERT((img_rgb8->data[i] & 0x03) == (b_value & 0x07), "Wrong B value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(((img_rgb8->data[i] >> 2) & 0x7) == (g_value & 0x07),
                    "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(((img_rgb8->data[i] >> 5) & 0x7) == (r_value & 0x03),
                    "Wrong R value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_rgb565);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_RGB565_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_grayscale = NULL;

    // Create RGΒ565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 32);
    g_value = rescale_color('G', 0, 255, 0, 64);
    b_value = rescale_color('B', 0, 255, 0, 32);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
        img_rgb565->data[2 * i] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
        img_rgb565->data[2 * i + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_rgb565, img_grayscale);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    y_value = rgb_to_yuv_y(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == y_value, "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_rgb565);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_RGB565_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_rgb565 = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    // Create RGΒ565 image
    img_rgb565 = create_image(width, height, RGB565);

    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        // Downscale original values
        r_value = rescale_color(curr_value, 0, 255, 0, 32);
        g_value = rescale_color(curr_value, 0, 255, 0, 64);
        b_value = rescale_color(curr_value, 0, 255, 0, 32);

        for (j = 0; j < width; j++) {
            // MSB | 5 bits of R, 6 bits of G, 5 bits of B | LSB
            img_rgb565->data[i * 2 * width + j * 2] = (b_value & 0x1f) | ((g_value & 0x07) << 5);
            img_rgb565->data[i * 2 * width + j * 2 + 1] = ((g_value & 0x38) >> 3) | ((r_value & 0x1f) << 3);
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_rgb565, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        // Downscale original values
        r_value = rescale_color(curr_value, 0, 255, 0, 32);
        g_value = rescale_color(curr_value, 0, 255, 0, 64);
        b_value = rescale_color(curr_value, 0, 255, 0, 32);

        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(rgb_to_yuv_y(r_value, g_value, b_value)),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_rgb565);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_RGB8_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_yuv444 = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_rgb8, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == y_value, "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == u_value, "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == v_value, "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_rgb8);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_RGB8_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_yuv444p = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_rgb8, img_yuv444p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == y_value, "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == u_value, "Wrong U value for YUV444p image on pixel %d",
                    i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == v_value,
                    "Wrong V value for YUV444p image on pixel %d", i);
    }

    destroy_image(img_rgb8);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_RGB8_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    uint8_t u_value = 0;
    uint8_t v_value = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_yuv420p = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_rgb8, img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    y_value = rgb_to_yuv_y(r_value, g_value, b_value);
    u_value = rgb_to_yuv_u(r_value, g_value, b_value);
    v_value = rgb_to_yuv_v(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == y_value, "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == u_value, "Wrong U value for YUV420p image on pixel %d",
                    i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == v_value,
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_rgb8);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_RGB8_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_rgb24 = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_rgb8, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");


    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_rgb24->data[i] == r_value, "Wrong R value for RGB24 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_rgb24->data[i + 1] == g_value, "Wrong G value for RGB24 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_rgb24->data[i + 2] == b_value, "Wrong B value for RGB24 image on pixel %d", i / 3);
    }

    destroy_image(img_rgb8);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_RGB8_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_rgb565 = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_rgb8, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (r_value & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (g_value & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (b_value & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_rgb8);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_RGB8_to_GRAYSCALE ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;
    uint8_t y_value = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_grayscale = NULL;

    // Create RGB8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Downscale original values
    r_value = rescale_color('R', 0, 255, 0, 8);
    g_value = rescale_color('G', 0, 255, 0, 8);
    b_value = rescale_color('B', 0, 255, 0, 4);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
        img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
    }

    // Create converted GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Convert image
    res = convert_image(img_rgb8, img_grayscale);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    y_value = rgb_to_yuv_y(r_value, g_value, b_value);

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == y_value, "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_rgb8);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_RGB8_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_rgb8 = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;
    uint8_t r_value = 0;
    uint8_t g_value = 0;
    uint8_t b_value = 0;

    // Create RGΒ8 image
    img_rgb8 = create_image(width, height, RGB8);

    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        // Downscale original values
        r_value = rescale_color(curr_value, 0, 255, 0, 32);
        g_value = rescale_color(curr_value, 0, 255, 0, 64);
        b_value = rescale_color(curr_value, 0, 255, 0, 32);

        for (j = 0; j < width; j++) {
            // MSB | 3 bits of R, 3 bits of G, 2 bits of B | LSB
            img_rgb8->data[i] = (b_value & 0x03) | ((g_value & 0x07) << 2) | ((r_value & 0x07) << 5);
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_rgb8, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        // Downscale original values
        r_value = rescale_color(curr_value, 0, 255, 0, 8);
        g_value = rescale_color(curr_value, 0, 255, 0, 8);
        b_value = rescale_color(curr_value, 0, 255, 0, 4);

        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(rgb_to_yuv_y(r_value, g_value, b_value)),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_rgb8);
    destroy_image(img_ascii);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_yuv444 = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Convert image
    res = convert_image(img_grayscale, img_yuv444);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == 'Y', "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == 0, "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == 0, "Wrong V value for YUV444 image on pixel %d", i / 3);
    }

    destroy_image(img_grayscale);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_yuv444p = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Convert image
    res = convert_image(img_grayscale, img_yuv444p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == 'Y', "Wrong Y value for YUV444p image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == 0, "Wrong U value for YUV444p image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == 0,
                    "Wrong V value for YUV444p image on pixel %d", i / 3);
    }

    destroy_image(img_grayscale);
    destroy_image(img_yuv444p);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_YUV420p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_yuv420p = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted YUV420p image
    img_yuv420p = create_image(width, height, YUV420p);
    // Convert image
    res = convert_image(img_grayscale, img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'Y', "Wrong Y value for YUV420p image on pixel %d", i);
    }

    for (i = width * height; i < width * height + UROUND_UP(width / 2) * UROUND_UP(height / 2); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == 0, "Wrong U value for YUV420p image on pixel %d", i - width * height);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i + UROUND_UP(width / 2) * UROUND_UP(height / 2)] == 0,
                    "Wrong V value for YUV420p image on pixel %d", i - width * height);
    }

    destroy_image(img_grayscale);
    destroy_image(img_yuv420p);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_RGB24 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_rgb24 = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted RGB24 image
    img_rgb24 = create_image(width, height, RGB24);
    // Convert image
    res = convert_image(img_grayscale, img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    for (i = 0; i < width * height; i++) {
        // Check R channel
        CUTS_ASSERT(img_rgb24->data[i * 3] == yuv_to_rgb_r('Y', 0, 0), "Wrong R value for RGB24 image on pixel %d",
                    i / 3);
        // Check G channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 1] == yuv_to_rgb_g('Y', 0, 0), "Wrong G value for RGB24 image on pixel %d",
                    i / 3);
        // Check B channel
        CUTS_ASSERT(img_rgb24->data[i * 3 + 2] == yuv_to_rgb_b('Y', 0, 0), "Wrong B value for RGB24 image on pixel %d",
                    i / 3);
    }

    destroy_image(img_grayscale);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_rgb565 = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted RGB565 image
    img_rgb565 = create_image(width, height, RGB565);
    // Convert image
    res = convert_image(img_grayscale, img_rgb565);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 0, 0), 0, 255, 0, 32);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 0, 0), 0, 255, 0, 64);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 0, 0), 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] >> 5) & 0x07) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] >> 3) & 0x1f;

        CUTS_ASSERT(actual_r == (expected_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
    }

    destroy_image(img_grayscale);
    destroy_image(img_rgb565);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_RGB8 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_rgb8 = NULL;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_grayscale->data[i] = 'Y';
    }

    // Create converted RGB8 image
    img_rgb8 = create_image(width, height, RGB8);
    // Convert image
    res = convert_image(img_grayscale, img_rgb8);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 0, 0), 0, 255, 0, 8);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 0, 0), 0, 255, 0, 8);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 0, 0), 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get actual R, G, B
        actual_b = img_rgb8->data[i] & 0x03;
        actual_g = (img_rgb8->data[i] >> 2) & 0x07;
        actual_r = (img_rgb8->data[i] >> 5) & 0x07;

        CUTS_ASSERT(actual_r == (expected_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == (expected_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == (expected_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
    }

    destroy_image(img_grayscale);
    destroy_image(img_rgb8);

    return NULL;
}


char * test_image_conversion_GRAYSCALE_to_ASCII ()
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img_grayscale = NULL;
    Image_t * img_ascii = NULL;
    uint8_t curr_value = 0;

    // Create GRAYSCALE image
    img_grayscale = create_image(width, height, GRAYSCALE);
    // Set image pixels to the appropriate values
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Set Y values
            img_grayscale->data[i * width + j] = curr_value;
        }

        curr_value += 22;
    }

    // Create converted ASCII image
    img_ascii = create_image(width, height, ASCII);
    // Convert image
    res = convert_image(img_grayscale, img_ascii);

    // Check that the converted image is okay
    CUTS_ASSERT(img_ascii, "Converted ASCII image couldn't be created");
    CUTS_ASSERT(img_ascii->width == width, "Converted ASCII image has wrong width");
    CUTS_ASSERT(img_ascii->height == height, "Converted ASCII image has wrong height");
    CUTS_ASSERT(img_ascii->format == ASCII, "Converted ASCII image has wrong format");
    CUTS_ASSERT(res == 1, "Conversion failed");

    curr_value = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Check Y channel
            CUTS_ASSERT(img_ascii->data[i * width + j] == y_to_ascii(curr_value),
                        "Wrong Y value for ASCII image on pixel %d", i * width + j);
        }

        curr_value += 22;
    }

    destroy_image(img_grayscale);
    destroy_image(img_ascii);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(test_image_conversion_YUV444_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_YUV444_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_RGB565_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_RGB565_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_RGB8_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_GRAYSCALE);
    CUTS_RUN_TEST(test_image_conversion_RGB8_to_ASCII);

    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_GRAYSCALE_to_ASCII);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
