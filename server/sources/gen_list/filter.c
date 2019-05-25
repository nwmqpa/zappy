/*
** EPITECH PROJECT, 2019
** filter.c
** File description:
** Generic filtering function.
*/

#include "generic_list.h"

void *pop_filter_list(list_t *list, filter_func function)
{
    return NULL;
}

void *get_filter_list(list_t *list, filter_func function)
{
    return NULL;
}

void *filter_list(list_t *list, filter_func function, dtor_func dtor)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (function(entry)) {
            LIST_REMOVE(entry, next);
            dtor(entry);
            list->size--;
        }
        i++;
    }
    return NULL;
}