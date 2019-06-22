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

/// Function to compare two entries of a list.
typedef int (*cmp_func) (const void *, const void *);

/// Function to filter entries of a list.
typedef int (*filter_func) (const void *);

/// Function to print content of a list.
typedef void (*print_func) (const void *);

/// Function to free content of a list.
typedef void (*dtor_func) (void *);

/// Function to map on a list.
typedef void (*map_func) (void *, const void *);

typedef struct entry_s {
    void *data;
    LIST_ENTRY(entry_s) next;
} entry_t;

/// Runtime generic list.
typedef struct list_s {
    LIST_HEAD(list, entry_s) head;
    size_t size;
} list_t;

/// Create a new runtime generic list.
list_t *create_list();

/// Add an entry to the end of the list.
void append_list(list_t *list, void *elem);

/// Add an entry at the beginning of the list.
void insert_head_list(list_t *list, void *elem);

/// Add an entry at `idx`.
void insert_list(list_t *list, void *elem, size_t idx);

/// Pop an entry at `idx`.
void *pop_list(list_t *list, size_t idx);

/// Pop an entry when function return 1.
void *pop_filter_list(list_t *list, filter_func function);

/// Pop an entry when to_cmp return 1 then return.
void *pop_cmp_list(list_t *list, cmp_func function, void *to_cmp);

/// Get entry `idx`.
void *get_list(list_t *list, size_t idx);

/// Get entry with function.
void *get_filter_list(list_t *list, filter_func function);

/// Get entry when to_cmp return 1 and then return it.
void *get_cmp_list(list_t *list, cmp_func function, void *to_cmp);

/// Filter the list.
void *filter_list(list_t *list, filter_func function, dtor_func dtor);

/// Print the content of the list.
void print_list(list_t *list, print_func function);

/// Check if the list is empty.
int is_empty_list(list_t *list);

/// Get the length of a list.
size_t len_list(list_t *list);

/// Empty a list.
void empty_list(list_t *list, dtor_func dtor);

/// Map a function on the list.
void map(list_t *list, map_func mapped, void *data);
