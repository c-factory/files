/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates folders
*/

#include "files.h"
#include <dirent.h>
#include <string.h>
#ifdef linux
#include <sys/stat.h>
#endif

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

bool folder_exists_and_not_empty(const char *folder_name)
{
    bool result = false;
    DIR* dir = opendir(folder_name);
    if (dir)
    {
        struct dirent *dent;
        while((dent = readdir(dir)) != NULL)
        {
            char *name = dent->d_name;
            if (!((name[0] == '.' && name[1] == '\0') || (name[0] == '.' && name[1] == '.' && name[2] == '\0')))
            {
                result = true;
                break;
            }
        }
        closedir(dir);
    }
    return result;
}

bool make_folder(const char *folder_name)
{
    bool result = false;
#ifdef _WIN32
    if (0 == mkdir(folder_name))
        result = true;
#endif
#ifdef linux
    if (0 == mkdir(folder_name, 0770))
        result = true;
#endif
    return result;
}
