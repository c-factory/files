/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of functions that operates file paths
*/

#pragma once

#include "strings/strings.h"

typedef struct
{
    string_t *path;
    string_t *file_name;
} full_path_t;

#ifdef _WIN32
    static const char path_separator = '\\';
    static const char wrong_path_separator = '/';
#else
    static const char path_separator = '/';
    static const char wrong_path_separator = '\\';
#endif

void fix_path_separators(char *path);
void destroy_full_path(full_path_t *full_path);
full_path_t * split_path(string_t path);
