/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates files
*/

#include "files.h"
#include <stdio.h>

bool file_exists(const char *file_name)
{
    bool exists = false;
    FILE* stream = fopen(file_name, "r");
    if (stream)
    {
        exists = true;
        fclose(stream);
    }
    return exists;
}
