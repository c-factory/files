/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates file paths
*/

#include "path.h"
#include "allocator.h"

void fix_path_separators(char *path)
{
    char *p = path;
    while(*p)
    {
        if (*p == wrong_path_separator)
            *p = path_separator;
        p++;
    }
}

void destroy_full_path(full_path_t *fp)
{
    free(fp->path);
    free(fp->file_name);
    free(fp);
}

full_path_t * split_path(string_t path)
{
    full_path_t *fp = nnalloc(sizeof(full_path_t));
    char *p = path.data + path.length - 1;
    while(p >= path.data && *p != path_separator && *p != wrong_path_separator)
        p--;
    fp->file_name = sub_string(path, p - path.data + 1, path.data + path.length - p - 1);    
    fp->path = sub_string(path, 0, p - path.data);
    fix_path_separators(fp->path->data);
    return fp;
}

