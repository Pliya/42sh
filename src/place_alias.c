/*
** EPITECH PROJECT, 2024
** place the alias
** File description:
** place the  alias
*/

#include "../include/my.h"
int inParentheses;

char *array_to_str(char **t, int j)
{
    char cmd[5000] = {0};

    if (t == NULL)
        NULL;
    for (int i = j; t[i] != NULL; i++) {
        strcat(cmd, t[i]);
        if (t[i + 1] != NULL)
            strcat(cmd, " ");
    }
    return strdup(cmd);
}

static int valid_alias(char *cmmd, char *d)
{
    char md[500] = {0};
    char ms[500] = {0};
    char *str = NULL;

    strcat(md, " ");
    strcat(ms, d);
    strcat(md, d);
    strcat(ms, " ");
    strcat(md, " ");
    str = strstr(cmmd, ms);
    if (str != NULL && str[0] == ms[0])
        return 1;
    str = strstr(cmmd, md);
    if (str != NULL)
        return 1;
    return 0;
}

char *remplacer(char *str, char *key, char *value)
{
    char *result = malloc(strlen(str) * 50);
    char *current = NULL;
    char *end = NULL;

    strcpy(result, str);
    current = result;
    current = strstr(current, key);
    while ((current) != NULL) {
        end = current + strlen(key);
        memmove(current + strlen(value),
        end,
        strlen(end));
        strncpy(current, value, strlen(value));
        current += strlen(value);
        current = strstr(current, key);
    }
    return result;
}

static void virgule_condition(char *str, char *result, int *j, int i)
{
    if (str[i] == ')') {
        inParentheses = 0;
        result[*j] = str[i];
        (*j)++;
    } else if (str[i] == ';' && (inParentheses == 1)) {
        result[*j] = '\\';
        (*j)++;
        result[*j] = ';';
        (*j)++;
    } else {
        result[*j] = str[i];
        (*j)++;
    }
}

char *remplacer_point_virgule(char *str)
{
    int i = 0;
    int j = 0;
    int len = strlen(str);
    char *result = malloc(len * 2 + 1);

    inParentheses = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            inParentheses = 1;
            result[j] = str[i];
            j++;
        }
        if (str[i] != '(') {
            virgule_condition(str, result, &j, i);
        }
    }
    result[j] = '\0';
    return remplacer_point_virgule2(result);
}

static char *place_set_var(char *s)
{
    char cmd[500] = {0};

    for (lol_t *al = shell.local; al != NULL; al = al->next) {
        if (al->name != NULL && al->value != NULL) {
            strcat(cmd, "$");
            strcat(cmd, al->name);
            s = remplacer(s, cmd, al->value);
            cmd[0] = '\0';
        }
    }
    return strdup(s);
}

char **ret_set_var(void)
{
    if (!shell.reader_splited)
        return NULL;
    for (int i = 0; shell.reader_splited[i] != NULL; i++)
        shell.reader_splited[i] = place_set_var(shell.reader_splited[i]);
    return shell.reader_splited;
}

char *place_alias(char *s)
{
    for (lol_t *al = shell.alias; al != NULL; al = al->next) {
        if (al->name != NULL && al->value != NULL
        && valid_alias(s, al->name) == 1){
            s = remplacer(s, al->name, al->value);
        }
    }
    return strdup(s);
}
