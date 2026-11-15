/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** my_putchar file
*/
#include <unistd.h>
#include "../include/my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (s2 == NULL || s1 == NULL)
        return 1;
    while (s2[i] != '\0' && s1[i] != '\0' && i < n) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return 0;
}

static int l_chaine(char const *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++);
    return i;
}

static int the_function(int i, char *str, char const *to_find)
{
    int k = 0;

    for (int j = 0; to_find[j] != '\0'; j++) {
        if (str[i + j] == to_find[j]) {
            k++;
        }
    }
    return k;
}

char *my_strstr(char *str, char const *to_find)
{
    int l = l_chaine(to_find);
    int k = 0;
    int j = 0;
    int i = 0;

    if (to_find[0] == '\0')
        return NULL;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[0]) {
            k = the_function(i, str, to_find);
        }
        if (l == k) {
            return (str + i);
        }
        j = 0;
        k = 0;
    }
    return NULL;
}

char *my_strstr1(char *str, char const *to_find)
{
    int parenthese = 0;
    int l = l_chaine(to_find);
    int k = 0;
    int j = 0;

    if (to_find[0] == '\0')
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(')
            parenthese++;
        if (str[i] == ')')
            parenthese--;
        if (str[i] == to_find[0])
            k = the_function(i, str, to_find);
        if (l == k && parenthese == 0)
            return (str + i);
        j = 0;
        k = 0;
    }
    return NULL;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}
