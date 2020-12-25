#include "cuts.h"

#include "libuimg.h"


char * create_YUV444_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, YUV444);
    CUTS_ASSERT(img, "YUV444 image creation failed");

    CUTS_ASSERT(img->width == width, "YUV444 image has wrong width");
    CUTS_ASSERT(img->height == height, "YUV444 image has wrong height");
    CUTS_ASSERT(img->format == YUV444, "YUV444 image has wrong format");
    CUTS_ASSERT(img->data, "YUV444 image has invalid data");

    destroy_image(img);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(create_YUV444_image);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
