#include "rotate.h"
#include "../image.h"
#include <malloc.h>

struct image rotate_counterclockwise(struct image const img) {

    struct image rotated = {.height=img.width, .width=img.height};
    struct pixel *pixels = malloc(sizeof(struct pixel)*img.height*img.width);

    for (size_t i = 0; i < img.height; i++){
        for (size_t j = 0;j < img.width; j++){
            pixels[img.height * j + (img.height - 1 - i)] = img.data[img.width * i + j];
        }
    }
    rotated.data = pixels;
    return rotated;
}
