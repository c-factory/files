/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of functions that operates files
*/

#pragma once

#include <stdbool.h>
#include "strings.h"

typedef struct
{
    string_t *name;
    string_t *extension;
} file_name_t;

typedef struct
{
    strings_list_t base;
} file_name_template_t;

bool file_exists(const char *file_name);
void destroy_file_name(file_name_t *file_name);
file_name_t * split_file_name(string_t name_with_extension);

file_name_template_t * create_file_name_template(string_t name);
bool file_name_matches_template(string_t name, file_name_template_t *tmpl);
void destroy_file_name_template(file_name_template_t *tmpl);