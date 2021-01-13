#ifndef IMAGE_ROTATION_FILE_H
#define IMAGE_ROTATION_FILE_H

#include <stdio.h>

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum open_status open_file(FILE** file, const char* path, const char* mode);

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum close_status close_file(FILE** file);

#endif //IMAGE_ROTATION_FILE_H
