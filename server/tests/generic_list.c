/*
** EPITECH PROJECT, 2019
** generic_list.c
** File description:
** generic_list.c
*/

#include <criterion/criterion.h>
#include "genericl_list.h"

Test(generic_list, creation) {
    list_t *list = create_list();

    cr_assert(client != NULL);
    cr_assert(len_list(client) == 0);
}

Test(generic_list, append) {
    list_t *list = create_list();

    append_list(list, 123);
    append_list(list, 532);
    append_list(list, 233);

    cr_assert(len_list(list), 3);
    int *value = get_list(list, 0);
    cr_assert(*value == 233);
    value = get_list(list, 2);
    cr_assert(*value = 123);
}

Test(generic_list, remove) {
    list_t *list = create_list();

    append_list(list, 123);
    append_list(list, 532);
    append_list(list, 233);

    int *one = pop_list(list, 0);
    int *two = pop_list(list, 0);
    int *three = pop_list(list, 0);

    cr_assert(*one == 123);
    cr_assert(*two == 532);
    cr_assert(*three == 233);
}

Test(generic_list, remove) {
    list_t *list = create_list();

    append_list(list, 1);
    append_list(list, 2);
    append_list(list, 3);

    int *one = pop_list(list, 2);
    int *two = pop_list(list, 1);
    int *three = pop_list(list, 0);

    cr_assert(*one == 3);
    cr_assert(*two == 2);
    cr_assert(*three == 1);
}

Test(generic_list, remove_empty) {

}

Test(generic_list, clear) {

}

Test(generic_list, clear_empty) {

}

Test(generic_list, print) {

}

Test(generic_list, pop) {

}
