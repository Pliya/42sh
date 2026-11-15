/*
** EPITECH PROJECT, 2024
** Day08
** File description:
** This is a file
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"

char *my_strdup(char *src)
{
    char *message = NULL;
    int i = 0;
    int j = my_strlen(src);

    if (src == NULL)
        return NULL;
    message = malloc(sizeof(char) * (j + 1));
    my_strcpy(message, src);
    return message;
}

void print_arg(char **arg)
{
    for (int i = 0; arg[i] != NULL; i++) {
        my_putstr(arg[i]);
        my_putchar('\n');
    }
}
