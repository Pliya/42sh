/*
** EPITECH PROJECT, 2024
** poi
** File description:
** poids gloire
*/

#include "../include/my.h"

char *b_search_noncommand(b_tree_t *t)
{
    char *str = NULL;

    if (t == NULL)
        return NULL;
    if (is_operator_type(t->value) == NONE
    && strlen(t->value) != 0 && strcmp(t->value, " ") != 0)
        return t->value;
    str = b_search_noncommand(t->right);
    if (str != NULL)
        return str;
    str = b_search_noncommand(t->left);
    if (str != NULL)
        return str;
}

int special_dup(char *file, int type)
{
    int fd = 0;

    if (file != NULL && type == 1)
        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (file != NULL && type == 2)
        fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (file != NULL && type == 3)
        fd = open(file, O_RDONLY, 0644);
    if (file != NULL && type <= 2)
        dup2(fd, STDOUT_FILENO);
    if (file != NULL && type > 2)
        dup2(fd, STDIN_FILENO);
        return fd;
}
