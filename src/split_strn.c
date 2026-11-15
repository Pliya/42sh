/*
** EPITECH PROJECT, 2024
** oytr
** File description:
** ytr
*/

#include "../include/my.h"
#include <stdio.h>
#include <stdlib.h>

static int verify_n(char c)
{
    if (c != '\n')
        return 1;
    else
    return 0;
}

static int number_line_n(char *s)
{
    int i = 0;
    int j = 0;
    char d = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (verify_n(s[i]) == 0)
            j++;
        if (i > 0)
            d = s[i - 1];
    }
    return j + 1;
}

static int number_colomn_n(char *s, int k, char d)
{
    if (verify_n(*s) == 0) {
        d = *s;
        s++;
        return 0;
    }
    while (verify_n(*s) == 1 && *s != '\0') {
            d = *s;
            s++;
            k++;
    }
    return k;
}

char **split_str_n(char *s)
{
    int j = number_line_n(s);
    int k = 0;
    char **t = malloc(sizeof(char *) * (j + 1));
    int i = 0;
    int l = 0;
    char d = 0;

    for (i = 0; i < j; i++) {
        k = number_colomn_n(s, k, d);
        if (k != 0) {
        t[l] = malloc((k + 1) * sizeof(char));
        my_strncpy(s, t[l], k);
        l++;
        }
        s = (k + 1) + s;
        k = 0;
    }
    t[l] = NULL;
    return t;
}
