#include "cuts.h"

#include "libuimg.h"

#define TEST_WIDTH 200
#define TEST_HEIGHT 300


char * test_image_save_and_static_load ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img1 = NULL;
    Image_t * img2 = NULL;

    // Create YUV444 image
    img1 = create_image(width, height, YUV444);
    img2 = create_image(width, height, YUV444);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y, U, V values
        img1->data[i    ] = 'Y';
        img1->data[i + 1] = 'U';
        img1->data[i + 2] = 'V';
    }

    // Save image
    res = save_image(img1, "/tmp/yuv444.img");
    CUTS_ASSERT(res == 1, "Could not save YUV444 image.");
    destroy_image(img1);

    // Load image
    res = load_static_image(img2, "/tmp/yuv444.img");
    CUTS_ASSERT(res == 1, "Could not load YUV444 image.");
    CUTS_ASSERT(img2->width == width, "Width is wrong on loaded YUV444 image.");
    CUTS_ASSERT(img2->height == height, "Height is wrong on loaded YUV444 image.");
    CUTS_ASSERT(img2->format == YUV444, "Pixel format is wrong on loaded YUV444 image.");

    for (i = 0; i < width * height * 3; i += 3) {
        CUTS_ASSERT(img2->data[i    ] == 'Y', "'Y' element wrong for loaded YUV444 image.");
        CUTS_ASSERT(img2->data[i + 1] == 'U', "'U' element wrong for loaded YUV444 image.");
        CUTS_ASSERT(img2->data[i + 2] == 'V', "'V' element wrong for loaded YUV444 image.");
    }

    destroy_image(img2);

    return NULL;
}


char * test_image_save_and_load ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t res = 0;
    Image_t * img1 = NULL;
    Image_t * img2 = NULL;

    // Create YUV444 image
    img1 = create_image(width, height, YUV444);

    // Set image pixels to the appropriate values
    for (i = 0; i < width * height * 3; i += 3) {
        // Set Y, U, V values
        img1->data[i    ] = 'Y';
        img1->data[i + 1] = 'U';
        img1->data[i + 2] = 'V';
    }

    // Save image
    res = save_image(img1, "/tmp/yuv444.img");
    CUTS_ASSERT(res == 1, "Could not save YUV444 image.");
    destroy_image(img1);

    // Load image
    img2 = load_image("/tmp/yuv444.img");
    CUTS_ASSERT(img2, "Could not load YUV444 image.");
    CUTS_ASSERT(img2->width == width, "Width is wrong on loaded YUV444 image.");
    CUTS_ASSERT(img2->height == height, "Height is wrong on loaded YUV444 image.");
    CUTS_ASSERT(img2->format == YUV444, "Pixel format is wrong on loaded YUV444 image.");

    for (i = 0; i < width * height * 3; i += 3) {
        CUTS_ASSERT(img2->data[i    ] == 'Y', "'Y' element wrong for loaded YUV444 image.");
        CUTS_ASSERT(img2->data[i + 1] == 'U', "'U' element wrong for loaded YUV444 image.");
        CUTS_ASSERT(img2->data[i + 2] == 'V', "'V' element wrong for loaded YUV444 image.");
    }

    destroy_image(img2);

    return NULL;
}


char * test_invalid_file_on_save ()
{
    size_t res = 0;
    Image_t * img = NULL;

    img = create_image(TEST_WIDTH, TEST_HEIGHT, RGB565);
    res = save_image(img, "");
    CUTS_ASSERT(res == 0, "Empty image file name should fail on save.");

    destroy_image(img);

    return NULL;
}


char * test_invalid_file_on_load ()
{
    size_t res = 0;
    Image_t * img = NULL;

    img = load_image("");
    CUTS_ASSERT(img == NULL, "Empty image file name should fail on load.");

    img = create_image(TEST_WIDTH, TEST_HEIGHT, GRAYSCALE);
    res = load_static_image(img, "");
    CUTS_ASSERT(res == 0, "Empty image file name should fail on static load.");

    destroy_image(img);

    return NULL;
}


char * test_unexpected_data_on_static_load ()
{
    size_t res = 0;
    Image_t * img1 = NULL;
    Image_t * img2 = NULL;

    img1 = create_image(TEST_WIDTH, TEST_HEIGHT, YUV420p);
    img2 = create_image(1, TEST_HEIGHT, YUV420p);

    save_image(img1, "/tmp/yuv420p.img");
    destroy_image(img1);

    res = load_static_image(img2, "/tmp/yuv420p.img");
    CUTS_ASSERT(res == 0, "Width should be wrong when loading image.");

    destroy_image(img2);
    img2 = create_image(TEST_WIDTH, 1, YUV420p);
    res = load_static_image(img2, "/tmp/yuv420p.img");
    CUTS_ASSERT(res == 0, "Height should be wrong when loading image.");

    destroy_image(img2);
    img2 = create_image(TEST_WIDTH, TEST_HEIGHT, GRAYSCALE);
    res = load_static_image(img2, "/tmp/yuv420p.img");
    CUTS_ASSERT(res == 0, "Format should be wrong when loading image.");

    destroy_image(img2);

    return NULL;
}


char * test_load_from_empty_file ()
{
    size_t res = 0;
    Image_t * img = NULL;
    FILE * image_file = NULL;

    // Create an empty binary file.
    image_file = fopen("/tmp/empty.img", "wb");
    fclose(image_file);

    // Attempt to load an image from the empty file.
    img = load_image("/tmp/empty.img");
    CUTS_ASSERT(img == NULL, "Should not be able to load an image from an empty file.");
    // Attempt to statically load an image from the empty file.
    img = create_image(TEST_WIDTH, TEST_HEIGHT, YUV444);
    res = load_static_image(img, "/tmp/empty.img");
    CUTS_ASSERT(res == 0, "Should not be able to statically load an image from an empty file.");

    destroy_image(img);

    return NULL;
}


char * test_load_from_file_missing_height ()
{
    size_t res = 0;
    Image_t * img = NULL;
    uint16_t width = 1;
    FILE * image_file = NULL;

    // Create a binary file containing only the width of the image.
    image_file = fopen("/tmp/missing_height.img", "wb");
    fwrite(&width, sizeof(uint16_t), 1, image_file); 
    fclose(image_file);

    // Attempt to load an image from the incomplete file.
    img = load_image("/tmp/missing_height.img");
    CUTS_ASSERT(img == NULL, "Should not be able to load an image from a file that's missing its height.");
    // Attempt to statically load an image from the incomplete file.
    img = create_image(1, 2, YUV444);
    res = load_static_image(img, "/tmp/missing_height.img");
    CUTS_ASSERT(res == 0, "Should not be able to statically load an image from a file that's missing its height.");

    destroy_image(img);

    return NULL;
}


char * test_load_from_file_missing_format ()
{
    size_t res = 0;
    Image_t * img = NULL;
    uint16_t width = 1;
    uint16_t height = 2;
    FILE * image_file = NULL;

    // Create a binary file containing only the width and the height of the image.
    image_file = fopen("/tmp/missing_format.img", "wb");
    fwrite(&width, sizeof(uint16_t), 1, image_file); 
    fwrite(&height, sizeof(uint16_t), 1, image_file); 
    fclose(image_file);

    // Attempt to load an image from the incomplete file.
    img = load_image("/tmp/missing_format.img");
    CUTS_ASSERT(img == NULL, "Should not be able to load an image from a file that's missing its format.");
    // Attempt to statically load an image from the incomplete file.
    img = create_image(1, 2, YUV444);
    res = load_static_image(img, "/tmp/missing_format.img");
    CUTS_ASSERT(res == 0, "Should not be able to statically load an image from a file that's missing its format.");

    destroy_image(img);

    return NULL;
}


char * test_load_from_file_missing_data ()
{
    size_t res = 0;
    Image_t * img = NULL;
    uint16_t width = 1;
    uint16_t height = 2;
    PixelFormat_t format = YUV444;
    FILE * image_file = NULL;

    // Create a binary file containing only the width, height and the format of the image.
    image_file = fopen("/tmp/missing_data.img", "wb");
    fwrite(&width, sizeof(uint16_t), 1, image_file); 
    fwrite(&height, sizeof(uint16_t), 1, image_file); 
    fwrite(&format, sizeof(PixelFormat_t), 1, image_file); 
    fclose(image_file);

    // Attempt to load an image from the incomplete file.
    img = load_image("/tmp/missing_data.img");
    CUTS_ASSERT(img == NULL, "Should not be able to load an image from a file that's missing its data.");
    // Attempt to statically load an image from the incomplete file.
    img = create_image(1, 2, YUV444);
    res = load_static_image(img, "/tmp/missing_data.img");
    CUTS_ASSERT(res == 0, "Should not be able to statically load an image from a file that's missing its data.");

    destroy_image(img);

    return NULL;
}


char * test_load_from_file_incomplete_data ()
{
    size_t res = 0;
    Image_t * img = NULL;
    uint16_t width = 1;
    uint16_t height = 2;
    PixelFormat_t format = YUV444;
    uint8_t data[] = { 'Y', 'U', 'V' };
    FILE * image_file = NULL;

    // Create a binary file containing everything, but only write half of the pixel data it's supposed to have.
    image_file = fopen("/tmp/missing_data.img", "wb");
    fwrite(&width, sizeof(uint16_t), 1, image_file); 
    fwrite(&height, sizeof(uint16_t), 1, image_file); 
    fwrite(&format, sizeof(PixelFormat_t), 1, image_file); 
    fwrite(data, sizeof(uint8_t), 3, image_file); 
    fclose(image_file);

    // Attempt to load an image from the incomplete file.
    img = load_image("/tmp/incomplete_data.img");
    CUTS_ASSERT(img == NULL, "Should not be able to load an image from a file that has incomplete pixel data.");
    // Attempt to statically load an image from the incomplete file.
    img = create_image(1, 2, YUV444);
    res = load_static_image(img, "/tmp/incomplete_data.img");
    CUTS_ASSERT(res == 0, "Should not be able to load an image from a file that has incomplete pixel data.");

    destroy_image(img);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(test_image_save_and_static_load);
    CUTS_RUN_TEST(test_image_save_and_load);
    CUTS_RUN_TEST(test_invalid_file_on_save);
    CUTS_RUN_TEST(test_invalid_file_on_load);
    CUTS_RUN_TEST(test_unexpected_data_on_static_load);
    CUTS_RUN_TEST(test_load_from_empty_file);
    CUTS_RUN_TEST(test_load_from_file_missing_height);
    CUTS_RUN_TEST(test_load_from_file_missing_format);
    CUTS_RUN_TEST(test_load_from_file_missing_data);
    CUTS_RUN_TEST(test_load_from_file_incomplete_data);

    return NULL;
}

CUTS_RUN_SUITE(all_tests);
