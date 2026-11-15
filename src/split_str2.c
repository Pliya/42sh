/*
** EPITECH PROJECT, 2024
** project
** File description:
** project
*/

#include "../include/my.h"

static int verify(char c, char d)
{
    if (c != ' ' && c != '\t' && c != '\n' ||
    ((c == ' ' && d == '\\') && (c != '\t' && d == '\\')
    && (c != '\"' && d == '\\')))
        return 1;
    else
    return 0;
}

static int number_line(char *s)
{
    int i = 0;
    int j = 0;
    char d = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (verify(s[i], d) == 0)
            j++;
        d = s[(i >= 1 ? i : 1) - 1];
    }
    return j + 1;
}

static int number_colomn(char *s, int k, char d)
{
    if (verify(*s, d) == 0) {
        d = *s;
        s++;
        return 0;
    }
    while (verify(*s, d) == 1 && *s != '\0') {
            d = *s;
            if (*s == '\\') {
                d = *s;
                s++;
                k++;
                continue;
            }
            s++;
            k++;
    }
    return k;
}

char **split_str2(char *s)
{
    char *str = change_str(s);
    int j = number_line(str);
    int k = 0;
    char **t = malloc(sizeof(char *) * (j + 1));
    int i = 0;
    int l = 0;
    char d = 0;

    for (i = 0; i < j; i++) {
        k = number_colomn(str, k, d);
        if (k != 0) {
            t[l] = malloc((k + 1) * sizeof(char));
            my_strncpy(str, t[l], k);
            l++;
        }
        str = (k + 1) + str;
        k = 0;
    }
    t[l] = NULL;
    return t;
}
