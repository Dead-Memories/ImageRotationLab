#ifndef IMAGE_ROTATION_IMAGE_H
#define IMAGE_ROTATION_IMAGE_H

#include <inttypes.h>

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif //IMAGE_ROTATION_IMAGE_H
