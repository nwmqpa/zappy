/*
** EPITECH PROJECT, 2019
** generic_linked_list.c
** File description:
** generic linked list source code.
*/

#include "generic_list.h"

list_t *create_list()
{
    list_t *list = malloc(sizeof(list_t));

    list->size = 0;
    if (!list)
        return NULL;
    LIST_INIT(&list->head);
    return list;
}

void *pop_list(list_t *list, size_t idx)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (idx == i) {
            LIST_REMOVE(entry, next);
            list->size--;
            return entry->data;
        }
        i++;
    }
    return NULL;
}

void *get_list(list_t *list, size_t idx)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (idx == i)
            return entry->data;
        i++;
    }
    return NULL;
}

void map(list_t *list, map_func func, void *params)
{
    entry_t *entry;

    LIST_FOREACH(entry, &list->head, next)
    {
        func(entry->data, params);
    }
}
