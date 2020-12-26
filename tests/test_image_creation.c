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


char * create_YUV444p_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, YUV444p);
    CUTS_ASSERT(img, "YUV444p image creation failed");

    CUTS_ASSERT(img->width == width, "YUV444p image has wrong width");
    CUTS_ASSERT(img->height == height, "YUV444p image has wrong height");
    CUTS_ASSERT(img->format == YUV444p, "YUV444p image has wrong format");
    CUTS_ASSERT(img->data, "YUV444p image has invalid data");

    destroy_image(img);

    return NULL;
}


char * create_YUV420p_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, YUV420p);
    CUTS_ASSERT(img, "YUV420p image creation failed");

    CUTS_ASSERT(img->width == width, "YUV420p image has wrong width");
    CUTS_ASSERT(img->height == height, "YUV420p image has wrong height");
    CUTS_ASSERT(img->format == YUV420p, "YUV420p image has wrong format");
    CUTS_ASSERT(img->data, "YUV420p image has invalid data");

    destroy_image(img);

    return NULL;
}


char * create_RGB24_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, RGB24);
    CUTS_ASSERT(img, "RGB24 image creation failed");

    CUTS_ASSERT(img->width == width, "RGB24 image has wrong width");
    CUTS_ASSERT(img->height == height, "RGB24 image has wrong height");
    CUTS_ASSERT(img->format == RGB24, "RGB24 image has wrong format");
    CUTS_ASSERT(img->data, "RGB24 image has invalid data");

    destroy_image(img);

    return NULL;
}


char * create_RGB565_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, RGB565);
    CUTS_ASSERT(img, "RGB565 image creation failed");

    CUTS_ASSERT(img->width == width, "RGB565 image has wrong width");
    CUTS_ASSERT(img->height == height, "RGB565 image has wrong height");
    CUTS_ASSERT(img->format == RGB565, "RGB565 image has wrong format");
    CUTS_ASSERT(img->data, "RGB565 image has invalid data");

    destroy_image(img);

    return NULL;
}


char * create_RGB8_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, RGB8);
    CUTS_ASSERT(img, "RGB8 image creation failed");

    CUTS_ASSERT(img->width == width, "RGB8 image has wrong width");
    CUTS_ASSERT(img->height == height, "RGB8 image has wrong height");
    CUTS_ASSERT(img->format == RGB8, "RGB8 image has wrong format");
    CUTS_ASSERT(img->data, "RGB8 image has invalid data");

    destroy_image(img);

    return NULL;
}


char * create_GRAYSCALE_image ()
{
    uint16_t width = 250;
    uint16_t height = 250;

    Image * img = create_image(width, height, GRAYSCALE);
    CUTS_ASSERT(img, "GRAYSCALE image creation failed");

    CUTS_ASSERT(img->width == width, "GRAYSCALE image has wrong width");
    CUTS_ASSERT(img->height == height, "GRAYSCALE image has wrong height");
    CUTS_ASSERT(img->format == GRAYSCALE, "GRAYSCALE image has wrong format");
    CUTS_ASSERT(img->data, "GRAYSCALE image has invalid data");

    destroy_image(img);

    return NULL;
}


char * all_tests ()
{
    CUTS_START();

    CUTS_RUN_TEST(create_YUV444_image);
    CUTS_RUN_TEST(create_YUV444p_image);
    CUTS_RUN_TEST(create_YUV420p_image);
    CUTS_RUN_TEST(create_RGB24_image);
    CUTS_RUN_TEST(create_RGB565_image);
    CUTS_RUN_TEST(create_RGB8_image);
    CUTS_RUN_TEST(create_GRAYSCALE_image);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
