/*
** EPITECH PROJECT, 2019
** logger.c
** File description:
** logger code file.
*/

#include "logger.h"

/// The log const is defining how the log is shown.
///                        [Date - hour | level] message
static const char *LOG = "%s[%s | %s] %s\e[0m";

static const char *LEVEL_NAME[] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG"};

char *get_log(int log_level, const char *color, const char *str)
{
    char *ret = NULL;
    time_t epoch = time(NULL);
    char *time_str = ctime(&epoch);

    time_str[24] = 0;
    asprintf(&ret, LOG, color, time_str, LEVEL_NAME[log_level], str);
    return ret;
}

int get_log_level(void)
{
    char *env_level = getenv("LOG_LEVEL");

    if (env_level)
        return atoi(env_level);
    return LOG_LEVEL;
}
