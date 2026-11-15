/*
** EPITECH PROJECT, 2024
** combi table
** File description:
** table
*/
#include "../include/my.h"

static int is_type(char *str)
{
    if (str == NULL)
        return NONE;
    if (!strcmp(str, "||"))
        return OU;
    if (!strcmp(str, "&"))
        return J_CONTROL;
    if (!strcmp(str, "&&"))
        return ET;
    if (!strcmp(str, ">"))
        return REDIR;
    if (!strcmp(str, ">>"))
        return REDIR;
    return 0;
}

info_t is_operator_type(char *str)
{
    if (is_type(str) != 0)
        return is_type(str);
    if (!strcmp(str, "<"))
        return REDIR;
    if (!strcmp(str, "<<"))
        return REDIR;
    if (!strcmp(str, "|"))
        return PIPE;
    if (!strcmp(str, "("))
        return PARENTESE1;
    if (!strcmp(str, ")"))
        return PARENTESE2;
    if (!strcmp(str, "`"))
        return M_QUOTE;
    return NONE;
}

int is_operator(char *str)
{
    if (!strcmp(str, "|") || !strcmp(str, "&") ||
    !strcmp(str, "&&") || !strcmp(str, ">") ||
    !strcmp(str, ">>") || !strcmp(str, "<") ||
    !strcmp(str, "<<") || !strcmp(str, "||") ||
    !strcmp(str, "(") || !strcmp(str, ")")
    || !strcmp(str, "`"))
        return 1;
    return 0;
}

static char *bef_operator(char **arg, int *i)
{
    char cmd[1000] = {0};
    char str[500] = {0};
    int k = 0;

    while (arg[*i] != NULL && is_operator(arg[*i]) == 0) {
        if (k != 0)
            strcat(str, " ");
        strcat(str, arg[*i]);
        strcat(cmd, str);
        str[0] = '\0';
        (*i)++;
        k++;
    }
    return strdup(cmd);
}

char **give_cmd_arr(char **arg)
{
    int j = 0;
    char *cmd = NULL;
    char **t = malloc(sizeof(char *) * (ARR_SIZEI(arg) + 1));

    for (int i = 0; arg[i] != NULL; i++) {
        cmd = bef_operator(arg, &i);
        if (strlen(cmd) == 0) {
            t[j] = strdup(arg[i]);
            j++;
            continue;
        }
        t[j] = cmd;
        j++;
        if (arg[i] == NULL)
            break;
        t[j] = strdup(arg[i]);
        j++;
    }
    t[j] = NULL;
    return t;
}
