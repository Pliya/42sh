/*
** EPITECH PROJECT, 2024
** str to word array of bootcamp
** File description:
** the bootcamp
*/


#include "../include/my.h"
#include <stdio.h>
#include <stdlib.h>

static int single_quote;
static int double_quote;

void my_strncpy(char *s, char *t, int n)
{
    int i = 0;

    for (i = 0; i < n; i++) {
        if (*s == '\\') {
            n--;
            s++;
        }
        t[i] = *s;
        s++;
    }
    t[i] = '\0';
}

void my_strncpy3(char *s, char *t, int n)
{
    int i = 0;

    for (i = 0; i < n; i++) {
        t[i] = *s;
        s++;
    }
    t[i] = '\0';
}

static void change_state(char *str, char *result, int *i, int *j)
{
    if ((str[*i] == ' ' || str[*i] == '\t')
        && (single_quote == 1 || double_quote == 1)) {
        result[*j] = '\\';
        (*j)++;
        result[*j] = ' ';
        (*j)++;
    } else {
        result[*j] = str[*i];
        (*j)++;
    }
}

char *change_str(char *str)
{
    char *result = malloc(strlen(str) * 2 + 1);
    int j = 0;

    single_quote = 0;
    double_quote = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'') {
            single_quote = !single_quote;
            result[j] = str[i];
        }
        if (str[i] == '\"') {
            double_quote = !double_quote;
            result[j] = str[i];
        }
        if (str[i] != '\'' && str[i] != '\"')
            change_state(str, result, &i, &j);
    }
    result[j] = '\0';
    return result;
}

static char *return_str(char *result, int j)
{
    result[j] = '\0';
    return result;
}

char *change_str1(char *str)
{
    char *result = malloc(strlen(str) * 2 + 1);
    int j = 0;

    single_quote = 0;
    double_quote = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'') {
            single_quote = !single_quote;
            result[j] = str[i];
            j++;
        }
        if (str[i] == '\"') {
            double_quote = !double_quote;
            result[j] = str[i];
            j++;
        }
        if (str[i] != '\'' && str[i] != '\"')
            change_state(str, result, &i, &j);
    }
    return return_str(result, j);
}
