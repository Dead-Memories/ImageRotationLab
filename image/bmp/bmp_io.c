#include <stdio.h>
#include <malloc.h>

#include "../image.h"
#include "bmp_io.h"


size_t get_padding(const size_t width) {
    size_t byte_width = width*sizeof(struct pixel);
    if (byte_width%4) {return 4-byte_width%4;}
    return 0;
}

struct bmp_header create_bmp_header(const size_t width, const size_t height) {
    struct bmp_header header;
    header.bfType = 0x4d42;
    header.bfileSize = sizeof(struct bmp_header) + (sizeof(struct pixel)*width+get_padding(width))*height;
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = width*height*sizeof(struct pixel);
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    return header;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
    struct bmp_header header = create_bmp_header(img->width, img->height);
    fwrite(&header, sizeof(struct bmp_header), 1, out);

    const size_t padding = get_padding(img->width);

    size_t error_check = 0;

    for (size_t height = 0; height < img->height; height++) {
        error_check+= fwrite(img->data + (img->width * height), sizeof(struct pixel), img->width, out);
        error_check+= fwrite("0", sizeof(char), padding, out);
    }

    if (error_check == (img->width + padding) * img->height) { return WRITE_OK;}

    return WRITE_ERROR;
}

enum read_status from_bmp(FILE* in, struct image* img, struct bmp_header *header) {
    if(header->bOffBits!=sizeof(struct bmp_header)) {
        return READ_INVALID_HEADER;
    }

    if(header->biBitCount!=24) {
        return READ_INVALID_BITS;
    }

    if (header->bfType!=0x4d42) {
        return READ_INVALID_SIGNATURE;
    }

    if (header->biSize!=40) {
        return READ_INVALID_DEPTH;
    }
    const size_t width = header->biWidth;
    const size_t height = header->biHeight;
    const size_t padding = get_padding(width);

    struct pixel* pixels = malloc(sizeof (struct pixel)*height*width);

    size_t error_check = 0;

    fseek(in, header->bOffBits, SEEK_CUR);
    for (size_t i = 0; i < height; i++) {
        error_check+= fread(pixels + (width * i), sizeof(struct pixel), width, in);
        fseek(in, padding, SEEK_CUR);
    }

    if (error_check!=width*height){
        return READ_ERROR;
    }

    img->data = pixels;
    return READ_OK;
}
