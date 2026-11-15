/*
** EPITECH PROJECT, 2024
** split_sep
** File description:
** split
*/

#include "../include/my.h"

int token_operator_num(char *str)
{
    int i = 0;

    for (char *s = strtok(str, "|&><\n"); s != NULL;
    s = strtok(NULL, "|&><\n")) {
        i++;
    }
    return i;
}

char **split_sep(char *str)
{
    int i = 0;
    int j = token_operator_num(my_strdup(str)) + 1;
    char **args = malloc(sizeof(char *) * (j));

    for (char *s = strtok(my_strdup(str), "|&><\n"); s != NULL;
    s = strtok(NULL, "|&><\n")) {
        args[i] = my_strdup(s);
        i++;
    }
    args[i] = NULL;
    return args;
}

int identity_oper(char *str)
{
    if (my_strstr(str, ">>") != NULL)
        return 2;
    if (my_strstr(str, "<<") != NULL)
        return 4;
    if (my_strstr(str, ">") != NULL)
        return 1;
    if (my_strstr(str, "<") != NULL)
        return 3;
    return -1;
}
