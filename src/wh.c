/*
** EPITECH PROJECT, 2024
** where and which
** File description:
** where and which
*/

#include "../include/my.h"

int in_built_tab(char *str)
{
    for (int i = 0; built_in[i] != NULL; i++) {
        if (my_strcmp(built_in[i], str) == 0)
            return 1;
    }
    return 0;
}

void where_fct(void)
{
    for (int i = 1; shell.reader_splited[i] != NULL; i++) {
        if (in_built_tab(shell.reader_splited[i]) == 1) {
            printf("%s is a shell built-in\n", shell.reader_splited[i]);
        }
        search_path(shell.reader_splited[i]);
    }
}

void viral(int sig)
{
    int i = 0;

    exit(0);
}

void which_fct(void)
{
    for (int i = 1; shell.reader_splited[i] != NULL; i++) {
        if (in_built_tab(shell.reader_splited[i]) == 1) {
            printf("%s: shell built-in command.\n", shell.reader_splited[i]);
            continue;
        }
        search_first_path(shell.reader_splited[i]);
    }
}
