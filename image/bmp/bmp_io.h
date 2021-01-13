#ifndef IMAGE_ROTATION_BMP_IO_H
#define IMAGE_ROTATION_BMP_IO_H

#include "bmp_header.h"

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum read_status {
    READ_OK = 0,
    READ_ERROR,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_DEPTH
};

enum write_status to_bmp(FILE* out, struct image const* img);
enum read_status from_bmp(FILE* in, struct image* img, struct bmp_header* header);

size_t get_padding(const size_t width);

#endif //IMAGE_ROTATION_BMP_IO_H
