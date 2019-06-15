/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** Generic utils function.
*/

#include "generic_list.h"

void print_list(list_t *list, print_func function)
{
    entry_t *entry;

    LIST_FOREACH(entry, &list->head, next)
    {
        function(entry->data);
    }
}

int is_empty_list(list_t *list)
{
    return LIST_EMPTY(&list->head);
}

void empty_list(list_t *list, dtor_func dtor)
{
    entry_t *entry;

    while (!LIST_EMPTY(&list->head)) {
        entry = LIST_FIRST(&list->head);
        LIST_REMOVE(entry, next);
        dtor(entry->data);
    }
    list->size = 0;
    LIST_INIT(&list->head);
}

size_t len_list(list_t *list)
{
    return list->size;
}