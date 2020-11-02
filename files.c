/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates files
*/

#include "files.h"
#include "allocator.h"
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

void destroy_file_name(file_name_t *fn)
{
    free(fn->name);
    free(fn->extension);
    free(fn);
}

file_name_t * split_file_name(string_t str)
{
    file_name_t *fn = nnalloc(sizeof(file_name_t));
    char *p = str.data + str.length - 1;
    while(p >= str.data && *p != '.')
        p--;
    fn->extension = sub_string(str, p - str.data + 1, str.data + str.length - p - 1);    
    fn->name = sub_string(str, 0, p - str.data);
    return fn;
}
