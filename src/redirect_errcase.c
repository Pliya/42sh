/*
** EPITECH PROJECT, 2024
** error cases
** File description:
** of the combination
*/

#include "../include/my.h"

static int check_pipe_err(r_dir_t **c, int i)
{
    if (c[i]->sortie == PIPE && c[i + 1] == NULL) {
        my_putstrerr("Invalid null command.\n");
        return 1;
    }
    if (c[i]->sortie == PIPE && c[i + 1] != NULL) {
        if (VER_STRSNULL(c[i]->cmd,
        strtok(my_strdup(c[i + 1]->cmd), " \t<>&|"))){
            my_putstrerr("Invalid null command.\n");
            return 1;
        }
    }
    return 0;
}

static int check_redir_err(r_dir_t **c, int i)
{
    if (c[i]->sortie == REDIR){
        if (c[i]->file == NULL) {
            my_putstrerr("Missing name for redirect.\n");
            return 1;
    }
        if (c[i]->cmd == NULL ||
        strtok(my_strdup(c[i]->cmd), " \t<>&|") == NULL) {
            my_putstrerr("Invalid null command.\n");
            return 1;
        }
    }
    if (c[i]->entre == REDIR){
        my_putstrerr("Invalid null command.\n");
        return 1;
    }
    return 0;
}

int err_opperation(r_dir_t **c)
{
    for (int i = 0; c[i] != NULL; i++) {
        if (check_pipe_err(c, i) == 1)
            return 1;
        if (check_redir_err(c, i) == 1)
            return 1;
        if (AMBIG_ERR(c[i]->entre, c[i]->sortie, c[i]->redir_type)){
            my_putstrerr("Ambiguous input redirect.\n");
            return 1;
        }
    }
}

int check_args(char **ar)
{
    for (int i = 0; ar[i] != NULL; i++) {
        if (i == 0 &&
        ((my_strstr(ar[i], "|") != NULL) || (my_strstr(ar[i], ">") != NULL)
        || (my_strstr(ar[i], "<") != NULL))) {
            my_putstrerr("Invalid null command.\n");
            return 1;
        }
    }
    return 0;
}

static void bef_1(char *cmd, char *str, int *i, int *j)
{
    int k = 0;

    while (str[*i] != 0 &&
    (str[*i] == '|' || str[*i] == '>' || str[*i] == '`'
    || str[*i] == '<' || str[*i] == '(' || str[*i] == ')')){
        cmd[*j] = str[*i];
        k = 1;
        (*i)++;
        (*j)++;
    }
    if (k == 1) {
        cmd[*j] = ' ';
        (*j)++;
        k = 0;
    }
}

static void complete(char *cmd, int *j, char *str, int *i)
{
    cmd[*j] = ' ';
    (*j)++;
    while (str[*i] != 0 &&
    (str[*i] == '|' || str[*i] == '>' || str[*i] == '`'
    || str[*i] == '<' || str[*i] == '(' || str[*i] == ')')){
        cmd[*j] = str[*i];
        (*i)++;
        (*j)++;
    }
    cmd[*j] = ' ';
    (*j)++;
    (*i)--;
}

char *str_oper_clean(char *str)
{
    int j = 0;
    char cmd[1000] = {0};

    for (int i = 0; str[i] != 0; i++) {
        while (str[i] != 0 &&
        !(str[i] == '|' || str[i] == '>' || str[i] == '`'
        || str[i] == '<' || str[i] == '(' || str[i] == ')')){
            bef_1(cmd, str, &i, &j);
            cmd[j] = str[i];
            i++;
            j++;
        }
        complete(cmd, &j, str, &i);
    }
    return strdup(cmd);
}

static int parenthese_funct(char *str)
{
    int in_par = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ')')
            in_par--;
        if (str[i] == '(')
            in_par++;
    }
    if (in_par > 0)
        fprintf(stderr, "Too many ('s.\n");
    if (in_par < 0)
        fprintf(stderr, "Too many )'s.\n");
    return in_par;
}

static int parenthese_funct1(char *str)
{
    int in_par = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '`')
            in_par++;
    }
    if ((in_par % 2) != 0)
        return 1;
    else
        return 0;
}

int exec_combi(char *str)
{
    char **arg = split_string(str);
    r_dir_t **combi = NULL;
    r_dir_t **other = NULL;
    char *str1 = str_oper_clean(str);

    combi = create_rstruct_from_args(str1);
    shell.status = 0;
    if (combi != NULL && err_opperation(combi) != 1 && check_args(arg) != 1
    && parenthese_funct(str) == 0 && parenthese_funct1(str) == 0)
        exec_combitable(combi);
    free_2d_tab(arg);
    free_rstruct(combi);
}
