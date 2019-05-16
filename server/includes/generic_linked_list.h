/*
** EPITECH PROJECT, 2019
** generic_linked_list.h
** File description:
** generic linked list.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

typedef int (*cmp_func) (const void *, const void *);
typedef int (*filter_func) (const void *);

typedef struct entry_s {
    void *data;
    LIST_ENTRY(entry_s) next;
} entry_t;

typedef struct list_s {
    LIST_HEAD(list, entry_s) head;
} list_t;

list_t *create_list();

void append_list(list_t *list, void *elem);

void *pop_list(list_t *list, size_t idx);
void *pop_filter_list(list_t *list, filter_func function);

void *get_list(list_t *list, size_t idx);
void *get_filter_list(list_t *list, filter_func function);

void *filter_list(list_t *list, filter_func function);
