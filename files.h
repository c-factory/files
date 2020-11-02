/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of functions that operates files
*/

#pragma once

#include <stdbool.h>
#include "strings/strings.h"

typedef struct
{
    string_t *name;
    string_t *extension;
} file_name_t;

bool file_exists(const char *file_name);
void destroy_file_name(file_name_t *file_name);
file_name_t * split_file_name(string_t name_with_extension);