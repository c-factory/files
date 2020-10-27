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

typedef struct
{
    size_t count;
    string_t **parts;
} file_name_template_t;

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
file_name_template_t * create_file_name_template(string_t name);
bool file_name_matches_template(string_t name, file_name_template_t *tmpl);
void destroy_file_name_template(file_name_template_t *tmpl);
