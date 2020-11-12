/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of functions that operates files
*/

#include "files.h"
#include "allocator.h"
#include <stdio.h>
#include <assert.h>

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

file_name_template_t * create_file_name_template(string_t name)
{
    return (file_name_template_t*)split_string(name, '*');
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
    assert(tmpl->base.size > 0);

    if (tmpl->base.size == 1)
        return are_strings_equal(name, *tmpl->base.items[0]);
    
    string_t *first_part = tmpl->base.items[0]; 
    if (first_part->length > 0)
    {
        if (name.length < first_part->length)
            return false;
        size_t start_index = index_of_part(&name, first_part, 0, &found);
        if (!found || start_index > 0)
            return false;
    }
    
    string_t *last_part = tmpl->base.items[tmpl->base.size - 1]; 
    if (last_part->length > 0)
    {
        if (name.length < last_part->length)
            return false;
        size_t expected_end_index = name.length - last_part->length;
        size_t end_index = index_of_part(&name, last_part, expected_end_index, &found);
        if (!found || end_index != expected_end_index)
            return false;
    }

    if (tmpl->base.size > 2)
    {
        size_t expected_next_index = first_part->length;
        for (size_t j = 1; j < tmpl->base.size - 1; j++)
        {
            string_t *next_part = tmpl->base.items[j];
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
    destroy_strings_list(&tmpl->base);
}
