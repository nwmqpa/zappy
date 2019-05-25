/*
** EPITECH PROJECT, 2019
** insert.c
** File description:
** Generic inserting function.
*/

#include "generic_list.h"

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