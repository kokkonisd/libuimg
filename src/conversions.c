#include "img.h"


Image * convert_YUV444_to_YUV420p (Image * img_yuv444)
{
    Image * img_yuv420p = NULL;
    uint16_t i = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if (!img_yuv444) return NULL;

    width = img_yuv444->width;
    height = img_yuv444->height;

    // Allocate memory for new image
    img_yuv420p = create_image(width, height, YUV420p);
    if (!img_yuv420p) return NULL;

    // In YUV420, 4 Y values share a single U and V value
    // Base image: YUV YUV YUV YUV
    // New image: YYYYUV
    for (i = 0; i < width * height / (3 * 4); i += 4) {
        // Copy Y component
        img_yuv420p->data[i    ] = img_yuv444->data[i * 3    ];
        img_yuv420p->data[i + 1] = img_yuv444->data[i * 3 * 2];
        img_yuv420p->data[i + 2] = img_yuv444->data[i * 3 * 3];
        img_yuv420p->data[i + 3] = img_yuv444->data[i * 3 * 4];
        // Copy U component
        img_yuv420p->data[i + 4] = img_yuv444->data[i * 3 + 1];
        // Copy V component
        img_yuv420p->data[i + 5] = img_yuv444->data[i * 3 + 2];
    }

    return img_yuv420p;
}
