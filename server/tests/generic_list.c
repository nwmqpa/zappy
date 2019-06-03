/*
** EPITECH PROJECT, 2019
** generic_list.c
** File description:
** generic_list.c
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "generic_list.h"

list_t *append_x(int how)
{
    list_t *list = create_list();

    for (int i = 0; i < how; i++) {
        int *x = malloc(sizeof(int));
        *x = i;
        append_list(list, x);
    }
    return list;
}

void print_int(const void *data)
{
    const int *value = data;

    cr_log_info("%d\n", *value);
}

void times_10(void *data, void *nothing)
{
    int *value = ((int *) data);

    *value *= 10;
}

void times_x(void *data, void *x)
{
    int *times = ((int *) x);
    int *value = ((int *) data);

    *value *= *times;
}

Test(generic_list, creation) {
    list_t *list = create_list();

    cr_assert(list != NULL);
    cr_assert(len_list(list) == 0);
}

Test(generic_list, append) {
    list_t *list = append_x(3);

    cr_assert(len_list(list) == 3, "len: %d != 3\n", len_list(list));
    int *value = get_list(list, 0);
    cr_assert(*value == 0);
    value = get_list(list, 2);
    cr_assert(*value == 2);
}

Test(generic_list, remove) {
    list_t *list = append_x(3);

    int *one = pop_list(list, 0);
    int *two = pop_list(list, 0);
    int *three = pop_list(list, 0);

    cr_assert(*one == 0);
    cr_assert(*two == 1);
    cr_assert(*three == 2);
}

Test(generic_list, remove_2) {
    list_t *list = append_x(10);

    int *one = pop_list(list, 2);
    int *two = pop_list(list, 1);
    int *three = pop_list(list, 0);

    cr_assert(*one == 2);
    cr_assert(*two == 1);
    cr_assert(*three == 0);
}

Test(generic_list, remove_empty) {
    list_t *list = create_list();

    cr_assert(pop_list(list, 2) == NULL);
    cr_assert(pop_list(list, 0) == NULL);
    cr_assert(pop_list(list, -1) == NULL);
}

Test(generic_list, clear) {
    list_t *client = append_x(100);

    empty_list(client, free);
    cr_assert(len_list(client) == 0);
}

Test(generic_list, clear_empty) {
    list_t *client = create_list();

    empty_list(client, free);
}

Test(generic_list, print_empty) {
    list_t *client = create_list();

    print_list(client, print_int);
}

Test(generic_list, print) {
    cr_log_info("Printing 20 elements of a int linked list.");
    list_t *client = append_x(20);

    print_list(client, print_int);
}

Test(generic_list, map) {
    list_t *list = append_x(20);

    map(list, times_10, NULL);

    int *one = pop_list(list, 0);
    int *two = pop_list(list, 0);
    int *three = pop_list(list, 0);

    cr_assert(*one == 0);
    cr_assert(*two == 10);
    cr_assert(*three == 20);
}

Test(generic_list, map_2) {
    list_t *list = append_x(20);
    int ten = 10;

    map(list, times_x, &ten);

    int *one = pop_list(list, 0);
    int *two = pop_list(list, 0);
    int *three = pop_list(list, 0);

    cr_assert(*one == 0);
    cr_assert(*two == 10);
    cr_assert(*three == 20);
}
