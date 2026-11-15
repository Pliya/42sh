/*
** EPITECH PROJECT, 2024
** my str to word array
** File description:
** my file
*/

#include "../include/my.h"

int number_line_s(char *s, char c)
{
    int i = 0;
    int j = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == c || s[i] == '\t')
            j++;
    }
    return j + 1;
}

int number_colomn_s(char *s, int k, char c)
{
    if (*s == c || *s == '\t') {
        s++;
        return 0;
    }
    while (*s != c && *s != '\0' && *s != '\t') {
            s++;
            k++;
    }
    return k;
}

char **my_str_to_word_array(char *s, char c)
{
    int j = number_line_s(s, c);
    int k = 0;
    char **t = malloc(sizeof(char *) * (j + 1));
    int i = 0;
    int l = 0;

    for (i = 0; i < j; i++) {
        k = number_colomn_s(s, k, c);
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
