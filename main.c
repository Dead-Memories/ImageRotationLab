#include "image/bmp/bmp_header.h"
#include "file_operations/file.h"
#include "image/image_operations/rotate.h"
#include "image/bmp/bmp_io.h"

#include <stdio.h>
#include <stdlib.h>


void usage() {
    fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME\n");
}

void err(char* message)
{
    fprintf(stderr,"%s", message);
    exit(1);
}

int main( int argc, char** argv ) {
    if (argc != 2) usage();
    if (argc < 2) err("Not enough arguments \n" );
    if (argc > 2) err("Too many arguments \n" );

    struct bmp_header h = { 0 };
    if (read_header_from_file( argv[1], &h )) {
        bmp_header_print( &h, stdout );
    }
    else {
        err( "Failed to open BMP file or reading header.\n" );
    }

    struct image img = {h.biWidth, h.biHeight, NULL};
    FILE* in_file = NULL;
    FILE* out_file = NULL;

    // Try to open
    enum open_status os = open_file(&in_file, argv[1], "rb");
    if (os != OPEN_OK){
        err("Can't open the file\n");
    }

    os = open_file(&out_file, "123.bmp", "wb");
    if (os != OPEN_OK){
        err("Can't open the file\n");
    }

    // Try to read
    enum read_status rs = from_bmp(in_file, &img, &h);
    if (rs != READ_OK){
        err("Can't read bmp\n");
    }

    struct image rotated = rotate_counterclockwise(img);

    // Try to write bmp file
    enum write_status ws = to_bmp(out_file, &rotated);
    if (ws != WRITE_OK){
        err("Can't write bmp\n");
    }

    // Try to close file
    enum close_status cs = close_file(&out_file);
    if (cs != CLOSE_OK){
        err("Can't close the file\n");
    }
    return 0;
}

