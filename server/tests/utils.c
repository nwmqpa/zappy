/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils test
*/

#include <criterion/criterion.h>
#include "utils.h"

Test(utils, basic) {
    const char *to_join[] = {
        "Salut",
        "je",
        "m'apel",
        "Alexandre",
        "."
    };
    char *joinned = malloc(sizeof(char) * 27);

    join_str(joinned, to_join, ' ', 5);
    cr_assert_str_eq(joinned, "Salut je m'apel Alexandre .");
}

Test(join_str, with_null) {
    const char *to_join[] = {
        "123",
        "12.4",
        "42.1",
        NULL,
        "123.0",
        "1235.21",
        NULL,
        NULL,
        "555.5"
    };
    char *new = NULL;
    char *joinned = malloc(sizeof(char) * 28 + 6);

    join_str(joinned, to_join, ',', 6);
    asprintf(&new, "[%s]", joinned);
    cr_assert_str_eq(new, "[123,12.4,42.1,123.0,1235.21,555.5]");
}

Test(join_str, with_null_and_empty_string) {
    const char *to_join[] = {
        "123",
        "12.4",
        "",
        "123.0",
        "",
        NULL,
        NULL,
        "555.5"
    };
    char *joinned = malloc(sizeof(char) * 23);

    join_str(joinned, to_join, ',', 6);
    cr_assert_str_eq(joinned, "123,12.4,,123.0,,555.5");
}

Test(join_str, with_all_empty_expect_one) {
    const char *to_join[] = {
        "123",
        "",
        "",
        ""
    };
    char *joinned = malloc(sizeof(char) * 7);

    join_str(joinned, to_join, ',', 4);
    cr_assert_str_eq(joinned, "123,,,");
}
