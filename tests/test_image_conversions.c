#include "cuts.h"

#include "libuimg.h"

#define TEST_WIDTH 257
#define TEST_HEIGHT 125


// char * test_incorrect_conversions ()
// {
//     // Conversion functions should explicitly check that the image passed to them is of the appropriate format
//     Image * dummy_yuv444 = create_image(TEST_WIDTH, TEST_HEIGHT, YUV444);
//     Image * dummy_yuv444p = create_image(TEST_WIDTH, TEST_HEIGHT, YUV444p);
//     Image * dummy_yuv420p = create_image(TEST_WIDTH, TEST_HEIGHT, YUV420p);
//     Image * dummy_rgb24 = create_image(TEST_WIDTH, TEST_HEIGHT, RGB24);
//     Image * dummy_rgb565 = create_image(TEST_WIDTH, TEST_HEIGHT, RGB565);
//     Image * dummy_rgb8 = create_image(TEST_WIDTH, TEST_HEIGHT, RGB8);
//     Image * dummy_grayscale = create_image(TEST_WIDTH, TEST_HEIGHT, GRAYSCALE);


//     // Check that wrong conversions fail

//     // Base: YUV 444
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_yuv444p), "YUV444 to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_yuv420p), "YUV444 to YUV444p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_rgb24), "YUV444 to YUV444p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_rgb565), "YUV444 to YUV444p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_rgb8), "YUV444 to YUV444p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_YUV444p(dummy_grayscale), "YUV444 to YUV444p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_yuv444p), "YUV444 to YUV420p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_yuv420p), "YUV444 to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_rgb24), "YUV444 to YUV420p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_rgb565), "YUV444 to YUV420p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_rgb8), "YUV444 to YUV420p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_YUV420p(dummy_grayscale), "YUV444 to YUV420p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_yuv444p), "YUV444 to RGB24 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_yuv420p), "YUV444 to RGB24 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_rgb24), "YUV444 to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_rgb565), "YUV444 to RGB24 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_rgb8), "YUV444 to RGB24 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_RGB24(dummy_grayscale), "YUV444 to RGB24 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_yuv444p), "YUV444 to RGB565 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_yuv420p), "YUV444 to RGB565 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_rgb24), "YUV444 to RGB565 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_rgb565), "YUV444 to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_rgb8), "YUV444 to RGB565 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_RGB565(dummy_grayscale), "YUV444 to RGB565 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_yuv444p), "YUV444 to RGB8 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_yuv420p), "YUV444 to RGB8 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_rgb24), "YUV444 to RGB8 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_rgb565), "YUV444 to RGB8 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_rgb8), "YUV444 to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_RGB8(dummy_grayscale), "YUV444 to RGB8 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_yuv444p), "YUV444 to GRAYSCALE should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_yuv420p), "YUV444 to GRAYSCALE should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_rgb24), "YUV444 to GRAYSCALE should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_rgb565), "YUV444 to GRAYSCALE should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_rgb8), "YUV444 to GRAYSCALE should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444_to_GRAYSCALE(dummy_grayscale),
//                 "YUV444 to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: YUV444p
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_yuv444), "YUV444p to YUV444 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_yuv420p), "YUV444p to YUV444 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_rgb24), "YUV444p to YUV444 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_rgb565), "YUV444p to YUV444 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_rgb8), "YUV444p to YUV444 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV444(dummy_grayscale), "YUV444p to YUV444 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_yuv444), "YUV444p to YUV420p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_yuv420p), "YUV444p to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_rgb24), "YUV444p to YUV420p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_rgb565), "YUV444p to YUV420p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_rgb8), "YUV444p to YUV420p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_YUV420p(dummy_grayscale),
//                 "YUV444p to YUV420p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_yuv444), "YUV444p to RGB24 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_yuv420p), "YUV444p to RGB24 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_rgb24), "YUV444p to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_rgb565), "YUV444p to RGB24 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_rgb8), "YUV444p to RGB24 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB24(dummy_grayscale), "YUV444p to RGB24 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_yuv444), "YUV444p to RGB565 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_yuv420p), "YUV444p to RGB565 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_rgb24), "YUV444p to RGB565 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_rgb565), "YUV444p to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_rgb8), "YUV444p to RGB565 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB565(dummy_grayscale), "YUV444p to RGB565 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_yuv444), "YUV444p to RGB8 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_yuv420p), "YUV444p to RGB8 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_rgb24), "YUV444p to RGB8 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_rgb565), "YUV444p to RGB8 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_rgb8), "YUV444p to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_RGB8(dummy_grayscale), "YUV444p to RGB8 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_yuv444), "YUV444p to GRAYSCALE should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_yuv420p),
//                 "YUV444p to GRAYSCALE should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_rgb24), "YUV444p to GRAYSCALE should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_rgb565), "YUV444p to GRAYSCALE should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_rgb8), "YUV444p to GRAYSCALE should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV444p_to_GRAYSCALE(dummy_grayscale),
//                 "YUV444p to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: YUV420p
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_yuv444p), "YUV420p to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_yuv444), "YUV420p to YUV444p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_rgb24), "YUV420p to YUV444p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_rgb565), "YUV420p to YUV444p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_rgb8), "YUV420p to YUV444p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444p(dummy_grayscale),
//                 "YUV420p to YUV444p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_yuv444p), "YUV420p to YUV444 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_yuv444), "YUV420p to YUV444 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_rgb24), "YUV420p to YUV444 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_rgb565), "YUV420p to YUV444 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_rgb8), "YUV420p to YUV444 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_YUV444(dummy_grayscale), "YUV420p to YUV444 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_yuv444p), "YUV420p to RGB24 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_yuv444), "YUV420p to RGB24 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_rgb24), "YUV420p to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_rgb565), "YUV420p to RGB24 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_rgb8), "YUV420p to RGB24 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB24(dummy_grayscale), "YUV420p to RGB24 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_yuv444p), "YUV420p to RGB565 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_yuv444), "YUV420p to RGB565 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_rgb24), "YUV420p to RGB565 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_rgb565), "YUV420p to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_rgb8), "YUV420p to RGB565 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB565(dummy_grayscale), "YUV420p to RGB565 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_yuv444p), "YUV420p to RGB8 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_yuv444), "YUV420p to RGB8 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_rgb24), "YUV420p to RGB8 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_rgb565), "YUV420p to RGB8 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_rgb8), "YUV420p to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_RGB8(dummy_grayscale), "YUV420p to RGB8 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_yuv444p),
//                 "YUV420p to GRAYSCALE should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_yuv444), "YUV420p to GRAYSCALE should fail for base image YUV444");
//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_rgb24), "YUV420p to GRAYSCALE should fail for base image RGB24");
//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_rgb565), "YUV420p to GRAYSCALE should fail for base image RGB565");
//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_rgb8), "YUV420p to GRAYSCALE should fail for base image RGB8");
//     CUTS_ASSERT(!convert_YUV420p_to_GRAYSCALE(dummy_grayscale),
//                 "YUV420p to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: RGB24
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_yuv444p), "RGB24 to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_yuv420p), "RGB24 to YUV444p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_yuv444), "RGB24 to YUV444p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_rgb565), "RGB24 to YUV444p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_rgb8), "RGB24 to YUV444p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444p(dummy_grayscale), "RGB24 to YUV444p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_yuv444p), "RGB24 to YUV420p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_yuv420p), "RGB24 to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_yuv444), "RGB24 to YUV420p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_rgb565), "RGB24 to YUV420p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_rgb8), "RGB24 to YUV420p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_YUV420p(dummy_grayscale), "RGB24 to YUV420p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_yuv444p), "RGB24 to YUV444 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_yuv420p), "RGB24 to YUV444 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_yuv444), "RGB24 to YUV444 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_rgb565), "RGB24 to YUV444 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_rgb8), "RGB24 to YUV444 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_YUV444(dummy_grayscale), "RGB24 to YUV444 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_yuv444p), "RGB24 to RGB565 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_yuv420p), "RGB24 to RGB565 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_yuv444), "RGB24 to RGB565 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_rgb565), "RGB24 to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_rgb8), "RGB24 to RGB565 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_RGB565(dummy_grayscale), "RGB24 to RGB565 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_yuv444p), "RGB24 to RGB8 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_yuv420p), "RGB24 to RGB8 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_yuv444), "RGB24 to RGB8 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_rgb565), "RGB24 to RGB8 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_rgb8), "RGB24 to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_RGB8(dummy_grayscale), "RGB24 to RGB8 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_yuv444p), "RGB24 to GRAYSCALE should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_yuv420p), "RGB24 to GRAYSCALE should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_yuv444), "RGB24 to GRAYSCALE should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_rgb565), "RGB24 to GRAYSCALE should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_rgb8), "RGB24 to GRAYSCALE should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB24_to_GRAYSCALE(dummy_grayscale),
//                 "RGB24 to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: RGB565
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_yuv444p), "RGB565 to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_yuv420p), "RGB565 to YUV444p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_rgb24), "RGB565 to YUV444p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_yuv444), "RGB565 to YUV444p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_rgb8), "RGB565 to YUV444p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444p(dummy_grayscale), "RGB565 to YUV444p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_yuv444p), "RGB565 to YUV420p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_yuv420p), "RGB565 to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_rgb24), "RGB565 to YUV420p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_yuv444), "RGB565 to YUV420p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_rgb8), "RGB565 to YUV420p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_YUV420p(dummy_grayscale), "RGB565 to YUV420p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_yuv444p), "RGB565 to RGB24 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_yuv420p), "RGB565 to RGB24 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_rgb24), "RGB565 to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_yuv444), "RGB565 to RGB24 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_rgb8), "RGB565 to RGB24 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_RGB24(dummy_grayscale), "RGB565 to RGB24 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_yuv444p), "RGB565 to YUV444 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_yuv420p), "RGB565 to YUV444 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_rgb24), "RGB565 to YUV444 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_yuv444), "RGB565 to YUV444 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_rgb8), "RGB565 to YUV444 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_YUV444(dummy_grayscale), "RGB565 to YUV444 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_yuv444p), "RGB565 to RGB8 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_yuv420p), "RGB565 to RGB8 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_rgb24), "RGB565 to RGB8 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_yuv444), "RGB565 to RGB8 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_rgb8), "RGB565 to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_RGB8(dummy_grayscale), "RGB565 to RGB8 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_yuv444p), "RGB565 to GRAYSCALE should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_yuv420p), "RGB565 to GRAYSCALE should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_rgb24), "RGB565 to GRAYSCALE should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_yuv444), "RGB565 to GRAYSCALE should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_rgb8), "RGB565 to GRAYSCALE should fail for base image RGB8");
//     CUTS_ASSERT(!convert_RGB565_to_GRAYSCALE(dummy_grayscale),
//                 "RGB565 to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: RGB8
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_yuv444p), "RGB8 to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_yuv420p), "RGB8 to YUV444p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_rgb24), "RGB8 to YUV444p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_rgb565), "RGB8 to YUV444p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_yuv444), "RGB8 to YUV444p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444p(dummy_grayscale), "RGB8 to YUV444p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_yuv444p), "RGB8 to YUV420p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_yuv420p), "RGB8 to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_rgb24), "RGB8 to YUV420p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_rgb565), "RGB8 to YUV420p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_yuv444), "RGB8 to YUV420p should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_YUV420p(dummy_grayscale), "RGB8 to YUV420p should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_yuv444p), "RGB8 to RGB24 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_yuv420p), "RGB8 to RGB24 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_rgb24), "RGB8 to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_rgb565), "RGB8 to RGB24 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_yuv444), "RGB8 to RGB24 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_RGB24(dummy_grayscale), "RGB8 to RGB24 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_yuv444p), "RGB8 to RGB565 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_yuv420p), "RGB8 to RGB565 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_rgb24), "RGB8 to RGB565 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_rgb565), "RGB8 to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_yuv444), "RGB8 to RGB565 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_RGB565(dummy_grayscale), "RGB8 to RGB565 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_yuv444p), "RGB8 to YUV444 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_yuv420p), "RGB8 to YUV444 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_rgb24), "RGB8 to YUV444 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_rgb565), "RGB8 to YUV444 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_yuv444), "RGB8 to YUV444 should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_YUV444(dummy_grayscale), "RGB8 to YUV444 should fail for base image GRAYSCALE");

//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_yuv444p), "RGB8 to GRAYSCALE should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_yuv420p), "RGB8 to GRAYSCALE should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_rgb24), "RGB8 to GRAYSCALE should fail for base image RGB24");
//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_rgb565), "RGB8 to GRAYSCALE should fail for base image RGB565");
//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_yuv444), "RGB8 to GRAYSCALE should fail for base image YUV444");
//     CUTS_ASSERT(!convert_RGB8_to_GRAYSCALE(dummy_grayscale),
//                 "RGB8 to GRAYSCALE should fail for base image GRAYSCALE");


//     // Base: GRAYSCALE
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_yuv444p),
//                 "GRAYSCALE to YUV444p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_yuv420p),
//                 "GRAYSCALE to YUV444p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_rgb24), "GRAYSCALE to YUV444p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_rgb565), "GRAYSCALE to YUV444p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_rgb8), "GRAYSCALE to YUV444p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444p(dummy_yuv444), "GRAYSCALE to YUV444p should fail for base image YUV444");

//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_yuv444p),
//                 "GRAYSCALE to YUV420p should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_yuv420p),
//                 "GRAYSCALE to YUV420p should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_rgb24), "GRAYSCALE to YUV420p should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_rgb565), "GRAYSCALE to YUV420p should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_rgb8), "GRAYSCALE to YUV420p should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV420p(dummy_yuv444), "GRAYSCALE to YUV420p should fail for base image YUV444");

//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_yuv444p), "GRAYSCALE to RGB24 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_yuv420p), "GRAYSCALE to RGB24 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_rgb24), "GRAYSCALE to RGB24 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_rgb565), "GRAYSCALE to RGB24 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_rgb8), "GRAYSCALE to RGB24 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB24(dummy_yuv444), "GRAYSCALE to RGB24 should fail for base image YUV444");

//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_yuv444p), "GRAYSCALE to RGB565 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_yuv420p), "GRAYSCALE to RGB565 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_rgb24), "GRAYSCALE to RGB565 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_rgb565), "GRAYSCALE to RGB565 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_rgb8), "GRAYSCALE to RGB565 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB565(dummy_yuv444), "GRAYSCALE to RGB565 should fail for base image YUV444");

//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_yuv444p), "GRAYSCALE to RGB8 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_yuv420p), "GRAYSCALE to RGB8 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_rgb24), "GRAYSCALE to RGB8 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_rgb565), "GRAYSCALE to RGB8 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_rgb8), "GRAYSCALE to RGB8 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_RGB8(dummy_yuv444), "GRAYSCALE to RGB8 should fail for base image YUV444");

//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_yuv444p), "GRAYSCALE to YUV444 should fail for base image YUV444p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_yuv420p), "GRAYSCALE to YUV444 should fail for base image YUV420p");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_rgb24), "GRAYSCALE to YUV444 should fail for base image RGB24");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_rgb565), "GRAYSCALE to YUV444 should fail for base image RGB565");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_rgb8), "GRAYSCALE to YUV444 should fail for base image RGB8");
//     CUTS_ASSERT(!convert_GRAYSCALE_to_YUV444(dummy_yuv444), "GRAYSCALE to YUV444 should fail for base image YUV444");


//     // Clean up
//     destroy_image(dummy_yuv444);
//     destroy_image(dummy_yuv444p);
//     destroy_image(dummy_yuv420p);
//     destroy_image(dummy_rgb24);
//     destroy_image(dummy_rgb565);
//     destroy_image(dummy_rgb8);
//     destroy_image(dummy_grayscale);

//     return NULL;
// }


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

    // Check that the converted image is okay
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

    // Check that the converted image is okay
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
    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for converted YUV420p image on pixel %d", i - offset);
    }

    // Done with U pixels, increment offset
    offset += UROUND_UP(width * height / 4);

    // Check the V pixels of the converted image
    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
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

    // Check that the converted image is okay
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
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
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

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    // Calculate expected values
    expected_r = yuv_to_rgb_r('Y', 'U', 'V');
    expected_g = yuv_to_rgb_g('Y', 'U', 'V');
    expected_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_b = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

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
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
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

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    // Calculate expected values
    expected_r = yuv_to_rgb_r('Y', 'U', 'V');
    expected_g = yuv_to_rgb_g('Y', 'U', 'V');
    expected_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb8->data[i] & 0x07;
        actual_g = (img_rgb8->data[i] >> 3) & 0x7;
        actual_b = (img_rgb8->data[i] >> 6) & 0x3;

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

    // Check that the converted image is okay
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

    // Check that the converted image is okay
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

    // Check that the converted image is okay
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

    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i] == 'U', "Wrong U value for YUV420p image on pixel %d", i - offset);
    }

    // U is done, increment offset
    offset += UROUND_UP(width * height / 4);

    for (i = offset; i < offset + UROUND_UP(width * height / 4); i++) {
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

    // Check that the converted image is okay
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
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
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

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    // Calculate expected values
    expected_r = yuv_to_rgb_r('Y', 'U', 'V');
    expected_g = yuv_to_rgb_g('Y', 'U', 'V');
    expected_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_b = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

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
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
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

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    // Calculate expected values
    expected_r = yuv_to_rgb_r('Y', 'U', 'V');
    expected_g = yuv_to_rgb_g('Y', 'U', 'V');
    expected_b = yuv_to_rgb_b('Y', 'U', 'V');

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb8->data[i] & 0x07;
        actual_g = (img_rgb8->data[i] >> 3) & 0x7;
        actual_b = (img_rgb8->data[i] >> 6) & 0x3;

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

    // Check that the converted image is okay
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


char * test_image_conversion_YUV420p_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    Image * img_yuv420p = NULL;
    Image * img_yuv444 = NULL;

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

    // Convert image
    img_yuv444 = convert_YUV420p_to_YUV444(img_yuv420p);

    // Check that the converted image is okay
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

    destroy_image(img_yuv420p);
    destroy_image(img_yuv444);

    return NULL;
}


char * test_image_conversion_YUV420p_to_YUV444p ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    Image * img_yuv420p = NULL;
    Image * img_yuv444p = NULL;

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

    // Convert image
    img_yuv444p = convert_YUV420p_to_YUV444p(img_yuv420p);


    // Check that the converted image is okay
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
    Image * img_yuv420p = NULL;
    Image * img_rgb24 = NULL;

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

    // Convert image
    img_rgb24 = convert_YUV420p_to_RGB24(img_yuv420p);

    // Check that the converted image is okay
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

    destroy_image(img_yuv420p);
    destroy_image(img_rgb24);

    return NULL;
}


char * test_image_conversion_YUV420p_to_RGB565 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image * img_yuv420p = NULL;
    Image * img_rgb565 = NULL;

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

    // Convert image
    img_rgb565 = convert_YUV420p_to_RGB565(img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 32);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 64);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 32);

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_b = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_r = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

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
    uint8_t expected_r = 0;
    uint8_t expected_g = 0;
    uint8_t expected_b = 0;
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image * img_yuv420p = NULL;
    Image * img_rgb8 = NULL;

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

    // Convert image
    img_rgb8 = convert_YUV420p_to_RGB8(img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    // Calculate expected values
    expected_r = rescale_color(yuv_to_rgb_r('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_g = rescale_color(yuv_to_rgb_g('Y', 'U', 'V'), 0, 255, 0, 8);
    expected_b = rescale_color(yuv_to_rgb_b('Y', 'U', 'V'), 0, 255, 0, 4);

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
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
    Image * img_yuv420p = NULL;
    Image * img_grayscale = NULL;

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

    // Convert image
    img_grayscale = convert_YUV420p_to_GRAYSCALE(img_yuv420p);

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == 'Y', "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_yuv420p);
    destroy_image(img_grayscale);

    return NULL;
}


char * test_image_conversion_RGB24_to_YUV444 ()
{
    uint32_t i = 0;
    uint16_t width = TEST_WIDTH;
    uint16_t height = TEST_HEIGHT;
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;
    Image * img_rgb24 = NULL;
    Image * img_yuv444 = NULL;

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

    // Convert image
    img_yuv444 = convert_RGB24_to_YUV444(img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444, "Converted YUV444 image couldn't be created");
    CUTS_ASSERT(img_yuv444->width == width, "Converted YUV444 image has wrong width");
    CUTS_ASSERT(img_yuv444->height == height, "Converted YUV444 image has wrong height");
    CUTS_ASSERT(img_yuv444->format == YUV444, "Converted YUV444 image has wrong format");

    // Calculate expected values
    y = rgb_to_yuv_y('R', 'G', 'B');
    u = rgb_to_yuv_u('R', 'G', 'B');
    v = rgb_to_yuv_v('R', 'G', 'B');

    for (i = 0; i < width * height * 3; i += 3) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444->data[i] == y, "Wrong Y value for YUV444 image on pixel %d", i / 3);
        // Check U channel
        CUTS_ASSERT(img_yuv444->data[i + 1] == u, "Wrong U value for YUV444 image on pixel %d", i / 3);
        // Check V channel
        CUTS_ASSERT(img_yuv444->data[i + 2] == v, "Wrong V value for YUV444 image on pixel %d", i / 3);
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
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;
    Image * img_rgb24 = NULL;
    Image * img_yuv444p = NULL;

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

    // Convert image
    img_yuv444p = convert_RGB24_to_YUV444p(img_rgb24);

    // Calculate expected values
    y = rgb_to_yuv_y('R', 'G', 'B');
    u = rgb_to_yuv_u('R', 'G', 'B');
    v = rgb_to_yuv_v('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv444p, "Converted YUV444p image couldn't be created");
    CUTS_ASSERT(img_yuv444p->width == width, "Converted YUV444p image has wrong width");
    CUTS_ASSERT(img_yuv444p->height == height, "Converted YUV444p image has wrong height");
    CUTS_ASSERT(img_yuv444p->format == YUV444p, "Converted YUV444p image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv444p->data[i] == y, "Wrong Y value for YUV444p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height] == u, "Wrong U value for YUV444p image on pixel %d", i);
        // Check V channel
        CUTS_ASSERT(img_yuv444p->data[i + width * height * 2] == v, "Wrong V value for YUV444p image on pixel %d",
                    i);
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
    uint8_t y = 0;
    uint8_t u = 0;
    uint8_t v = 0;
    Image * img_rgb24 = NULL;
    Image * img_yuv420p = NULL;

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

    // Convert image
    img_yuv420p = convert_RGB24_to_YUV420p(img_rgb24);

    // Calculate expected values
    y = rgb_to_yuv_y('R', 'G', 'B');
    u = rgb_to_yuv_u('R', 'G', 'B');
    v = rgb_to_yuv_v('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_yuv420p, "Converted YUV420p image couldn't be created");
    CUTS_ASSERT(img_yuv420p->width == width, "Converted YUV420p image has wrong width");
    CUTS_ASSERT(img_yuv420p->height == height, "Converted YUV420p image has wrong height");
    CUTS_ASSERT(img_yuv420p->format == YUV420p, "Converted YUV420p image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_yuv420p->data[i] == y, "Wrong Y value for YUV420p image on pixel %d", i);
        // Check U channel
        CUTS_ASSERT(img_yuv420p->data[i / 4 + width * height] == u, "Wrong U value for YUV420p image on pixel %d",
                    i / 4);
        // Check V channel
        CUTS_ASSERT(img_yuv420p->data[i / 4 + width * height + UROUND_UP(width * height / 4)] == v,
                    "Wrong V value for YUV420p image on pixel %d", i / 4);
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
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image * img_rgb24 = NULL;
    Image * img_rgb565 = NULL;

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

    // Convert image
    img_rgb565 = convert_RGB24_to_RGB565(img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb565, "Converted RGB565 image couldn't be created");
    CUTS_ASSERT(img_rgb565->width == width, "Converted RGB565 image has wrong width");
    CUTS_ASSERT(img_rgb565->height == height, "Converted RGB565 image has wrong height");
    CUTS_ASSERT(img_rgb565->format == RGB565, "Converted RGB565 image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb565->data[i * 2] & 0x1f;
        actual_g = ((img_rgb565->data[i * 2] & 0xe0) >> 5) | ((img_rgb565->data[i * 2 + 1] & 0x07) << 3);
        actual_b = (img_rgb565->data[i * 2 + 1] & 0xf8) >> 3;

        CUTS_ASSERT(actual_r == ('R' & 0x1f), "Wrong R value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_g == ('G' & 0x3f), "Wrong G value for RGB565 image on pixel %d", i);
        CUTS_ASSERT(actual_b == ('B' & 0x1f), "Wrong B value for RGB565 image on pixel %d", i);
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
    uint8_t actual_r = 0;
    uint8_t actual_g = 0;
    uint8_t actual_b = 0;
    Image * img_rgb24 = NULL;
    Image * img_rgb8 = NULL;

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

    // Convert image
    img_rgb8 = convert_RGB24_to_RGB8(img_rgb24);

    // Check that the converted image is okay
    CUTS_ASSERT(img_rgb8, "Converted RGB8 image couldn't be created");
    CUTS_ASSERT(img_rgb8->width == width, "Converted RGB8 image has wrong width");
    CUTS_ASSERT(img_rgb8->height == height, "Converted RGB8 image has wrong height");
    CUTS_ASSERT(img_rgb8->format == RGB8, "Converted RGB8 image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Get partial R, G, B
        actual_r = img_rgb8->data[i] & 0x07;
        actual_g = (img_rgb8->data[i] >> 3) & 0x7;
        actual_b = (img_rgb8->data[i] >> 6) & 0x3;

        CUTS_ASSERT(actual_r == ('R' & 0x07), "Wrong R value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_g == ('G' & 0x07), "Wrong G value for RGB8 image on pixel %d", i);
        CUTS_ASSERT(actual_b == ('B' & 0x03), "Wrong B value for RGB8 image on pixel %d", i);
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
    uint8_t y = 0;
    Image * img_rgb24 = NULL;
    Image * img_grayscale = NULL;

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

    // Convert image
    img_grayscale = convert_RGB24_to_GRAYSCALE(img_rgb24);

    // Calculate expected value
    y = rgb_to_yuv_y('R', 'G', 'B');

    // Check that the converted image is okay
    CUTS_ASSERT(img_grayscale, "Converted GRAYSCALE image couldn't be created");
    CUTS_ASSERT(img_grayscale->width == width, "Converted GRAYSCALE image has wrong width");
    CUTS_ASSERT(img_grayscale->height == height, "Converted GRAYSCALE image has wrong height");
    CUTS_ASSERT(img_grayscale->format == GRAYSCALE, "Converted GRAYSCALE image has wrong format");

    for (i = 0; i < width * height; i++) {
        // Check Y channel
        CUTS_ASSERT(img_grayscale->data[i] == y, "Wrong Y value for GRAYSCALE image on pixel %d", i);
    }

    destroy_image(img_rgb24);
    destroy_image(img_grayscale);

    return NULL;
}






char * all_tests ()
{
    CUTS_START();

    // CUTS_RUN_TEST(test_incorrect_conversions);

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

    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB24);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_YUV420p_to_GRAYSCALE);

    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV444);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV444p);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_YUV420p);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_RGB565);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_RGB8);
    CUTS_RUN_TEST(test_image_conversion_RGB24_to_GRAYSCALE);

    return NULL;
}


CUTS_RUN_SUITE(all_tests);
