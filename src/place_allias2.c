/*
** EPITECH PROJECT, 2024
** place alias
** File description:
** alias
*/

#include "../include/my.h"

int in_mq;

static void virgule_condition(char *str, char *result, int *j, int i)
{
    if (str[i] == '`') {
        in_mq = 0;
        result[*j] = str[i];
        (*j)++;
    } else if (str[i] == ';' && (in_mq == 1)) {
        result[*j] = '\\';
        (*j)++;
        result[*j] = ';';
        (*j)++;
    } else {
        result[*j] = str[i];
        (*j)++;
    }
}

char *remplacer_point_virgule2(char *str)
{
    int i = 0;
    int j = 0;
    int len = strlen(str);
    char *result = malloc(len * 2 + 1);

    in_mq = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '`') {
            in_mq = 1;
            result[j] = str[i];
            j++;
        }
        if (str[i] != '`') {
            virgule_condition(str, result, &j, i);
        }
    }
    result[j] = '\0';
    return result;
}

static sp_string_t avant_egale(char *str)
{
    sp_string_t s = {0};
    char *str1 = my_strdup(str);
    char *str2 = NULL;

    if (str1 == NULL)
        return s;
    str2 = str1;
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] == '=') {
            str1[i] = '\0';
            s.right = my_strdup(str1);
            str2++;
            s.left = my_strdup(str2);
            break;
        }
        str2++;
    }
    return s;
}

static char *place_set_env(char *s)
{
    sp_string_t sp = {0};
    char cmd[500] = {0};

    for (my_env_t *al = shell.head; al != NULL; al = al->next) {
        sp = avant_egale(al->str);
        strcat(cmd, "$");
        strcat(cmd, sp.right);
        s = remplacer(s, cmd, sp.left);
        cmd[0] = '\0';
    }
    return strdup(s);
}

char **ret_set_env(void)
{
    if (!shell.reader_splited)
        return NULL;
    for (int i = 0; shell.reader_splited[i] != NULL; i++)
        shell.reader_splited[i] = place_set_env(shell.reader_splited[i]);
    return shell.reader_splited;
}
