/*
** EPITECH PROJECT, 2019
** compare.c
** File description:
** Generic comparing function.
*/

#include "generic_list.h"

void *pop_cmp_list(list_t *list, cmp_func function, void *to_cmp)
{
    entry_t *entry;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (function(entry->data, to_cmp)) {
            LIST_REMOVE(entry, next);
            list->size--;
            return entry->data;
        }
    }
    return NULL;
}