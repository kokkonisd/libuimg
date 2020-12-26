#include "cuts.h"

#include "libuimg.h"

#define TEST_WIDTH 256
#define TEST_HEIGHT 123


char * test_image_conversion_YUV444_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    Image * img_yuv444 = NULL;
    Image * img_yuv444p = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_yuv444p = convert_YUV444_to_YUV444p(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");

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
    uint32_t offset = 0;
    Image * img_yuv444 = NULL;
    Image * img_yuv420p = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_yuv420p = convert_YUV444_to_YUV420p(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");

    // Check the Y pixels of the converted image
    for (i = 0; i < width * height; i++) {
        CUTS_ASSERT(img_yuv420p->data[i] == 'Y', "Wrong Y value for converted YUV420p image on pixel %d", i);
    }

    // Done with Y pixels, increment offset
    offset += width * height;

    // Check the U pixels of the converted image
    for (i = offset; i < offset + (uint32_t) (width * height * 0.25); i++) {
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for converted YUV420p image on pixel %d", i - offset);
    }

    // Done with U pixels, increment offset
    offset += (uint32_t) (width * height * 0.25);

    // Check the V pixels of the converted image
    for (i = offset; i < offset + (uint32_t) (width * height * 0.25); i++) {
        CUTS_ASSERT(img_yuv420p->data[i] == 'V', "Wrong V value for converted YUV420p image on pixel %d", i - offset);
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
    Image * img_yuv444 = NULL;
    Image * img_rgb24 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_rgb24 = convert_YUV444_to_RGB24(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");

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
    uint8_t full_r = 0;
    uint8_t full_g = 0;
    uint8_t full_b = 0;
    uint8_t partial_r = 0;
    uint8_t partial_g = 0;
    uint8_t partial_b = 0;
    Image * img_yuv444 = NULL;
    Image * img_rgb565 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_rgb565 = convert_YUV444_to_RGB565(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    // Calculate expected values
    full_r = yuv_to_rgb_r('Y', 'U', 'V');
    full_g = yuv_to_rgb_g('Y', 'U', 'V');
    full_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        partial_r = img_rgb565->data[i * 2] & 0x1f;
        partial_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        partial_b = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

        CUTS_ASSERT(partial_r == (full_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(partial_g == (full_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(partial_b == (full_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
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
    uint8_t full_r = 0;
    uint8_t full_g = 0;
    uint8_t full_b = 0;
    uint8_t partial_r = 0;
    uint8_t partial_g = 0;
    uint8_t partial_b = 0;
    Image * img_yuv444 = NULL;
    Image * img_rgb8 = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_rgb8 = convert_YUV444_to_RGB8(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    // Calculate expected values
    full_r = yuv_to_rgb_r('Y', 'U', 'V');
    full_g = yuv_to_rgb_g('Y', 'U', 'V');
    full_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        partial_r = img_rgb8->data[i] & 0x07;
        partial_g = (img_rgb8->data[i] >> 3) & 0x7;
        partial_b = (img_rgb8->data[i] >> 6) & 0x3;

        CUTS_ASSERT(partial_r == (full_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(partial_g == (full_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(partial_b == (full_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
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
    Image * img_yuv444 = NULL;
    Image * img_grayscale = NULL;

    // Create YUV444 image
    img_yuv444 = create_image(width, height, YUV444);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y values
        img_yuv444->data[i    ] = 'Y';
        img_yuv444->data[i + 1] = 'U';
        img_yuv444->data[i + 2] = 'V';
    }

    // Convert image
    img_grayscale = convert_YUV444_to_GRAYSCALE(img_yuv444);

    // Test that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv444);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_YUV444p_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    Image * img_yuv444p = NULL;
    Image * img_yuv444 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_yuv444 = convert_YUV444p_to_YUV444(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");

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
    uint32_t offset = 0;
    Image * img_yuv444p = NULL;
    Image * img_yuv420p = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_yuv420p = convert_YUV444p_to_YUV420p(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'Y', "Wrong Y value for YUV420p image on pixel %d", i);
    }

    // Y is done, increment offset
    offset += width * height;

    for (i = offset; i < offset + (uint32_t) (width * height * 0.25); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for YUV420p image on pixel %d", i - offset);
    }

    // U is done, increment offset
    offset += (uint32_t) (width * height * 0.25);

    for (i = offset; i < offset + (uint32_t) (width * height * 0.25); i++) {
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'V', "Wrong V value for YUV420p image on pixel %d", i - offset);
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
    Image * img_yuv444p = NULL;
    Image * img_rgb24 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_rgb24 = convert_YUV444p_to_RGB24(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb24, "Converted RGB24 image couldn't be created");
    CUTS_ASSERT(img_rgb24->width == width, "Converted RGB24 image has wrong width");
    CUTS_ASSERT(img_rgb24->height == height, "Converted RGB24 image has wrong height");
    CUTS_ASSERT(img_rgb24->format == RGB24, "Converted RGB24 image has wrong format");

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
    uint8_t full_r = 0;
    uint8_t full_g = 0;
    uint8_t full_b = 0;
    uint8_t partial_r = 0;
    uint8_t partial_g = 0;
    uint8_t partial_b = 0;
    Image * img_yuv444p = NULL;
    Image * img_rgb565 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_rgb565 = convert_YUV444p_to_RGB565(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    // Calculate expected values
    full_r = yuv_to_rgb_r('Y', 'U', 'V');
    full_g = yuv_to_rgb_g('Y', 'U', 'V');
    full_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        partial_r = img_rgb565->data[i * 2] & 0x1f;
        partial_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        partial_b = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

        CUTS_ASSERT(partial_r == (full_r & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(partial_g == (full_g & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(partial_b == (full_b & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
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
    uint8_t full_r = 0;
    uint8_t full_g = 0;
    uint8_t full_b = 0;
    uint8_t partial_r = 0;
    uint8_t partial_g = 0;
    uint8_t partial_b = 0;
    Image * img_yuv444p = NULL;
    Image * img_rgb8 = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_rgb8 = convert_YUV444p_to_RGB8(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    // Calculate expected values
    full_r = yuv_to_rgb_r('Y', 'U', 'V');
    full_g = yuv_to_rgb_g('Y', 'U', 'V');
    full_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        partial_r = img_rgb8->data[i] & 0x07;
        partial_g = (img_rgb8->data[i] >> 3) & 0x7;
        partial_b = (img_rgb8->data[i] >> 6) & 0x3;

        CUTS_ASSERT(partial_r == (full_r & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(partial_g == (full_g & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(partial_b == (full_b & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
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
    Image * img_yuv444p = NULL;
    Image * img_grayscale = NULL;

    // Create YUV444p image
    img_yuv444p = create_image(width, height, YUV444p);
    // Set image pixels to the appropriate values
    for (i = 0; i < width * height; i++) {
        // Set Y values
        img_yuv444p->data[i] = 'Y';
        img_yuv444p->data[i + width * height] = 'U';
        img_yuv444p->data[i + width * height * 2] = 'V';
    }

    // Convert image
    img_grayscale = convert_YUV444p_to_GRAYSCALE(img_yuv444p);

    // Test that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv444p);
    destroy_image(img_grayscale);

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

    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_YUV444p_to_GRAYSCALE);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
