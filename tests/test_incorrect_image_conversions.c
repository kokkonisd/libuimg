#include "cuts.h"

#include "libuimg.h"


char * test_failed_conversion_by_dimension_mismatch ()
{
    uint8_t res = 0;;
    Image_t * base_img = NULL;
    Image_t * conv_img = NULL;

    base_img = create_image(1, 2, YUV444);
    // Both dimensions are different
    conv_img = create_image(3, 4, RGB24);

    CUTS_ASSERT(base_img, "Failed to create base image");
    CUTS_ASSERT(conv_img, "Failed to create converted image");

    res = convert_image(base_img, conv_img);
    CUTS_ASSERT(res == 0, "Conversion should fail by dimension mismatch");

    destroy_image(conv_img);

    // Only height is different
    conv_img = create_image(1, 3, RGB24);
    CUTS_ASSERT(conv_img, "Failed to create second converted image");

    res = convert_image(base_img, conv_img);
    CUTS_ASSERT(res == 0, "Conversion should fail by dimension mismatch");

    destroy_image(conv_img);
    destroy_image(base_img);

    return NULL;
}


char * test_failed_conversion_by_uninitialized_images ()
{
    uint8_t res = 0;;
    Image_t * base_img = NULL;
    Image_t * conv_img = NULL;

    // Attempt to convert with both images being uninitialized
    res = convert_image(base_img, conv_img);
    CUTS_ASSERT(res == 0, "Conversion should fail when both images are uninitialized");

    base_img = create_image(1, 1, GRAYSCALE);

    // Attempt to convert with the second image being uninitialized
    res = convert_image(base_img, conv_img);
    CUTS_ASSERT(res == 0, "Conversion should fail when the second image is uninitialized");

    destroy_image(base_img);
    base_img = NULL;

    conv_img = create_image(1, 1, RGB565);

    // Attempt to convert with the first image being uninitialized    
    res = convert_image(base_img, conv_img);
    CUTS_ASSERT(res == 0, "Conversion should fail when the first image is uninitialized");

    destroy_image(conv_img);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(test_failed_conversion_by_dimension_mismatch);
    CUTS_RUN_TEST(test_failed_conversion_by_uninitialized_images);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
