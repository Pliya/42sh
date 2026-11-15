/*
** EPITECH PROJECT, 2024
** oytr
** File description:
** ytr
*/

#include "../include/my.h"

int verify1(char c, char d)
{
    if (c != ';' && c != '\n' || (c == ';' && d == '\\'))
        return 1;
    else
    return 0;
}

int number_line1(char *s)
{
    int i = 0;
    int j = 0;
    char d = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (verify1(s[i], d) == 0)
            j++;
            d = s[(i >= 1 ? i : 1) - 1];
    }
    return j + 1;
}

int number_colomn1(char *s, int k, char d)
{
    if (verify1(*s, d) == 0) {
        d = *s;
        s++;
        return 0;
    }
    while (verify1(*s, d) == 1 && *s != '\0') {
            d = *s;
            s++;
            k++;
    }
    return k;
}

void my_strncpy1(char *s, char *t, int n)
{
    int i = 0;

    for (i = 0; i < n; i++) {
        t[i] = *s;
        s++;
    }
    t[i] = '\0';
}

char **split_string1(char *s)
{
    int j = number_line1(s);
    int k = 0;
    char **t = malloc(sizeof(char *) * (j + 1));
    int i = 0;
    int l = 0;
    char d = 0;

    for (i = 0; i < j; i++) {
        k = number_colomn1(s, k, d);
        if (k != 0) {
        t[l] = malloc((k + 1) * sizeof(char));
        my_strncpy1(s, t[l], k);
        l++;
        }
            s = (k + 1) + s;
            k = 0;
    }
    t[l] = NULL;
    return t;
}
