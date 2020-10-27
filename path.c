/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates file paths
*/

#include "path.h"
#include "allocator.h"
#include <assert.h>

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

file_name_template_t * create_file_name_template(string_t name)
{
    size_t i, count = 0;
    for (i = 0; i < name.length; i++)
    {
        if(name.data[i] == '*')
            count++;
    }
    file_name_template_t *tmpl = nnalloc(sizeof(file_name_template_t));
    tmpl->parts = nnalloc(sizeof(string_t*) * (count + 1));
    tmpl->count = 0;
    size_t idx = 0,
        length = 0;
    for (i = 0; i < name.length; i++)
    {
        if(name.data[i] == '*')
        {
            tmpl->parts[tmpl->count++] = sub_string(name, idx, length);
            idx = i + 1;
            length = 0;
        }
        else
        {
            length++;
        }
    }
    tmpl->parts[tmpl->count++] = sub_string(name, idx, length);
    return tmpl;
}

static size_t index_of_part(string_t *file_name, string_t *part, size_t start_index, bool *found)
{
    size_t idx = start_index;
    size_t end_index = file_name->length - part->length;
    *found = false;
    while (idx <= end_index)
    {
        bool flag = true;
        for (size_t k = 0; k < part->length; k++)
        {
            if (part->data[k] != '?' && part->data[k] != file_name->data[idx + k])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            *found = true;
            return idx;
        }
        idx++;
    }
    return 0;
}

bool file_name_matches_template(string_t name, file_name_template_t *tmpl)
{
    bool found;
    assert(tmpl->count > 0);

    if (tmpl->count == 1)
        return are_strings_equal(name, *tmpl->parts[0]);
    
    string_t *first_part = tmpl->parts[0]; 
    if (first_part->length > 0)
    {
        if (name.length < first_part->length)
            return false;
        size_t start_index = index_of_part(&name, first_part, 0, &found);
        if (!found || start_index > 0)
            return false;
    }
    
    string_t *last_part = tmpl->parts[tmpl->count - 1]; 
    if (last_part->length > 0)
    {
        if (name.length < last_part->length)
            return false;
        size_t expected_end_index = name.length - last_part->length;
        size_t end_index = index_of_part(&name, last_part, expected_end_index, &found);
        if (!found || end_index != expected_end_index)
            return false;
    }

    if (tmpl->count > 2)
    {
        size_t expected_next_index = first_part->length;
        for (size_t j = 1; j < tmpl->count - 1; j++)
        {
            string_t *next_part = tmpl->parts[j];
            if (name.length < next_part->length)
                return false;
            size_t next_index = index_of_part(&name, next_part, expected_next_index, &found);
            if (!found)
                return false;
            expected_next_index = next_index + next_part->length;
        }
    }
    return true;
}

void destroy_file_name_template(file_name_template_t *tmpl)
{
    for (size_t i = 0; i < tmpl->count; i++)
        free(tmpl->parts[i]);
    free(tmpl->parts);
    free(tmpl);
}
