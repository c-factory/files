/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates folders
*/

#include "files.h"
#include <dirent.h>

bool folder_exists(const char *folder_name)
{
    bool exists = false;
    DIR* dir = opendir(folder_name);
    if (dir)
    {
        exists = true;
        closedir(dir);
    }
    return exists;
}
