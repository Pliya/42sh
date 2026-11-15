/*
** EPITECH PROJECT, 2024
** This is a file
** File description:
** File to constr char
*/
#include <stdio.h>
#include <unistd.h>
#include "../include/my.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int k = 0;

    for (i = 0; dest[i] != '\0'; i++);
    for (k = 0; k < my_strlen(src) != '\0'; k++) {
        dest[i] = src[k];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *my_superstrcat(char *dest, char const *src)
{
    char *str = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 1));

    my_strcpy(str, dest);
    return my_strcat(str, src);
}

void my_putstrerr(char *str)
{
    write(2, str, my_strlen(str));
}

int my_putstr(char const *str)
{
    if (str == NULL)
        return 1;
    while (*str != '\0'){
        my_putchar(*str);
        str++;
    }
    return 0;
}
