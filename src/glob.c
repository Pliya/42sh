/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-2-42sh-bill.adjagboni
** File description:
** glob.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "../include/my.h"

int counter(char **args, glob_t buffer, int count)
{
    count = 0;
    for (int i = 0; args[i] != NULL; i++) {
        if (strchr(args[i], '*') || strchr(args[i], '?') ||
        (strchr(args[i], '[') && strchr(args[i], ']'))) {
            glob(args[i], GLOB_NOCHECK, NULL, &buffer);
            count += buffer.gl_pathc;
            globfree(&buffer);
        } else
            count++;
    }
    return count;
}

char **looping(glob_t buffer, char **tab, int *idx)
{
    for (int j = 0; j < buffer.gl_pathc; j++) {
        tab[(*idx)] = strdup(buffer.gl_pathv[j]);
        (*idx)++;
    }
    return tab;
}

char **handle_glob(char **args)
{
    int idx = 0;
    glob_t buffer = {0};
    int count = counter(args, buffer, count);
    char **tab = malloc(sizeof(char *) * (count + 1));

    for (int i = 0; args[i] != NULL; i++) {
        if (strchr(args[i], '*') || strchr(args[i], '?') ||
        (strchr(args[i], '[') && strchr(args[i], ']'))) {
            glob(args[i], GLOB_NOCHECK, NULL, &buffer);
            tab = looping(buffer, tab, &idx);
            globfree(&buffer);
        }
        if (!(strchr(args[i], '*') || strchr(args[i], '?') ||
        (strchr(args[i], '[') && strchr(args[i], ']')))) {
            tab[idx] = strdup(args[i]);
            idx++;
        }
    }
    tab[idx] = NULL;
    return tab;
}
