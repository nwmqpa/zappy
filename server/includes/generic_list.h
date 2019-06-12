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
typedef void (*print_func) (const void *);
typedef void (*dtor_func) (void *);
typedef void (*map_func) (void *, const void *);

typedef struct entry_s {
    void *data;
    LIST_ENTRY(entry_s) next;
} entry_t;

typedef struct list_s {
    LIST_HEAD(list, entry_s) head;
    size_t size;
} list_t;

list_t *create_list();

void append_list(list_t *list, void *elem);
void insert_head_list(list_t *list, void *elem);
void insert_list(list_t *list, void *elem, size_t idx);

void *pop_list(list_t *list, size_t idx);
void *pop_filter_list(list_t *list, filter_func function);
void *pop_cmp_list(list_t *list, cmp_func function, void *to_cmp);

void *get_list(list_t *list, size_t idx);
void *get_filter_list(list_t *list, filter_func function);
void *get_cmp_list(list_t *list, cmp_func function, void *to_cmp);

void *filter_list(list_t *list, filter_func function, dtor_func dtor);

void print_list(list_t *list, print_func function);

int is_empty_list(list_t *list);

size_t len_list(list_t *list);

void empty_list(list_t *list, dtor_func dtor);

void map(list_t *list, map_func mapped, void *data);
