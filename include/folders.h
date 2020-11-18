/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of functions that operates folders
*/

#pragma once

#include <stdbool.h>

bool folder_exists(const char *folder_name);
bool folder_exists_and_not_empty(const char *folder_name);
bool make_folder(const char *folder_name);