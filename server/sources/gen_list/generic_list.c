/*
** EPITECH PROJECT, 2019
** generic_linked_list.c
** File description:
** generic linked list source code.
*/

#include "generic_list.h"
#include <criterion/logging.h>

list_t *create_list()
{
    list_t *list = malloc(sizeof(list_t));

    list->size = 0;
    if (!list)
        return NULL;
    LIST_INIT(&list->head);
    return list;
}

void insert_list(list_t *list, void *elem, size_t idx)
{
    entry_t *new = malloc(sizeof(entry_t));
    entry_t *entry;
    size_t i = 0;

    list->size++;
    new->data = elem;
    LIST_FOREACH(entry, &list->head, next)
    {
        if (i == idx){
            LIST_INSERT_AFTER(entry, new, next);
            return;
        }
    }
}

void insert_head_list(list_t *list, void *elem)
{
   entry_t *new = malloc(sizeof(entry_t));

    list->size++;
    new->data = elem;
    LIST_INSERT_HEAD(&list->head, new, next);
}

void append_list(list_t *list, void *elem)
{
    if (list->size == 0)
        return insert_head_list(list, elem);
    entry_t *new = malloc(sizeof(entry_t));
    entry_t *entry;
    size_t i = 0;

    new->data = elem;
    LIST_FOREACH(entry, &list->head, next)
    {
        if ((list->size - 1) == i) {
            LIST_INSERT_AFTER(entry, new, next);
            list->size++;
            return;
        }
        i++;
    }
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

void *pop_filter_list(list_t *list, filter_func function)
{
    return NULL;
}

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
            list->size--;
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
