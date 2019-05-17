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

    if (!list)
        return NULL;
    LIST_INIT(&list->head);
    return list;
}

void append_list(list_t *list, void *elem)
{
    entry_t *new = malloc(sizeof(entry_t));

    new->data = elem;
    LIST_INSERT_HEAD(&list->head, new, next);
}

void *pop_list(list_t *list, size_t idx)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (idx == i) {
            LIST_REMOVE(entry, next);
            return entry;
        }
        i++;
    }
    return NULL;
}

void *pop_filter_list(list_t *list, filter_func function)
{
    return NULL;
}

void *get_list(list_t *list, size_t idx)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (idx == i)
            return entry;
        i++;
    }
    return NULL;

}

void *get_filter_list(list_t *list, filter_func function)
{
    return NULL;
}

void *filter_list(list_t *list, filter_func function)
{
    entry_t *entry;
    size_t i = 0;

    LIST_FOREACH(entry, &list->head, next)
    {
        if (function(entry)) {
            LIST_REMOVE(entry, next);
        }
        i++;
    }
    return NULL;
}

void print_list(list_t *list, print_func function)
{
    entry_t *entry;

    LIST_FOREACH(entry, &list->head, next)
    {
        function(entry);
    }
}

int is_empty_list(list_t *list)
{
    return LIST_EMPTY(&list->head);
}

void empty_list(list_t *list, print_func dtor)
{
    entry_t *entry;

    while (!LIST_EMPTY(&list->head)) {
        entry = LIST_FIRST(&list->head);
        LIST_REMOVE(entry, next);
        dtor(entry);
    }
    LIST_INIT(&list->head);
}
