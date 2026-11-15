/*
** EPITECH PROJECT, 2024
** redirections
** File description:
** combinaisons
*/

#include "../include/my.h"


static int ind;
static int fin;
static char *pos;
static int redir_type;
static char *cd;

static void create_2(char **args, r_dir_t **combi, int *i, int k)
{
    if (args[*i] != NULL && is_operator(args[*i]) == 1)
        combi[k]->sortie = is_operator_type(args[*i]);
    else
        combi[k]->sortie = NONE;
    if (k != 0)
        combi[k]->entre = combi[k - 1]->sortie;
    else
        combi[k]->entre = NONE;
    if (k > 0 && combi[k - 1]->sortie != PARENTESE2)
        combi[k]->entre = combi[k - 1]->sortie;
    if (k > 0 && combi[k - 1]->sortie == PARENTESE2)
        combi[k]->entre = combi[k - 1]->parenthese_sortie;
    if (combi[k]->sortie == REDIR) {
        combi[k]->redir_type = identity_oper(args[*i]);
        (*i)++;
        if (args[*i] != NULL)
            combi[k]->file = strdup(args[*i]);
        else
            combi[k]->file = NULL;
    }
}

static void more_if(int *k, int *i, char **args, r_dir_t **combi)
{
    if (*k == 0)
        combi[*k]->entre = NONE;
    if (*k > 0 && combi[*k - 1]->sortie != PARENTESE2)
        combi[*k]->entre = combi[*k - 1]->sortie;
    if (*k > 0 && combi[*k - 1]->sortie == PARENTESE2)
        combi[*k]->entre = combi[*k - 1]->parenthese_sortie;
    combi[*k]->sortie = PARENTESE2;
    if (args[*i] != NULL && is_operator_type(args[*i]) == PIPE){
        combi[*k]->parenthese_sortie = PIPE;
    }
    if (args[*i] != NULL && args[*i + 1] != NULL &&
    is_operator_type(args[*i]) == REDIR){
        combi[*k]->parenthese_sortie = REDIR;
        combi[*k]->redir_type = identity_oper(args[*i]);
        combi[*k]->parenthese_file = strdup(args[*i + 1]);
        (*i) += 2;
    }
}

static void parenthese_copy(int *k, int *i, char **args, r_dir_t **combi)
{
    char cmd[500] = {0};
    int in_parenthese = 0;

    do {
        if (is_operator_type(args[*i]) == PARENTESE1)
            in_parenthese++;
        if (is_operator_type(args[*i]) == PARENTESE2)
            in_parenthese--;
        strcat(cmd, args[*i]);
        strcat(cmd, " ");
        (*i)++;
    } while (args[*i] != NULL && in_parenthese != 0);
    combi[*k]->cmd = strdup(cmd);
    more_if(k, i, args, combi);
}

static void m_quote_fct(int *k, int *i, char **args, r_dir_t **combi)
{
    char cmd[500] = {0};

    if (is_operator_type(args[*i]) == M_QUOTE){
        strcat(cmd, "`");
        (*i)++;
        while (args[*i] != NULL && is_operator_type(args[*i]) != M_QUOTE){
            strcat(cmd, args[*i]);
            strcat(cmd, " ");
            (*i)++;
        }
        strcat(cmd, "`");
        (*i)++;
        combi[*k]->cmd = my_strdup(cmd);
        combi[*k]->sortie = M_QUOTE;
        if (*k > 0 && combi[*k - 1]->sortie != PARENTESE2)
            combi[*k]->entre = combi[*k - 1]->sortie;
        if (*k > 0 && combi[*k - 1]->sortie == PARENTESE2)
            combi[*k]->entre = combi[*k - 1]->parenthese_sortie;
    }
}

static int to_continue(int *k, int *i, char **args, r_dir_t **combi)
{
    if (is_operator(args[*i]) == 0)
        combi[*k]->cmd = strdup(args[*i]);
    else
        combi[*k]->cmd = "";
    if (is_operator_type(args[*i]) == PARENTESE1){
        ind = *k;
        parenthese_copy(k, i, args, combi);
        (*k)++;
        cd[0] = 0;
        return 1;
    }
    m_quote_fct(k, i, args, combi);
    return 0;
}

static r_dir_t *combi_first_create(void)
{
    int fd[2] = {0};
    r_dir_t *combi = malloc(sizeof(r_dir_t));

    combi->args = NULL;
    combi->cmd = NULL;
    combi->entre = NONE;
    combi->fd[0] = 0;
    combi->fd[1] = 0;
    combi->file = NULL;
    combi->p_tree = NULL;
    combi->parenthese_file = NULL;
    combi->parenthese_sortie = NONE;
    combi->pid = 0;
    combi->redir_type = 0;
    combi->sortie = NONE;
    return combi;
}

r_dir_t **create_rstruct_from_args(char *str)
{
    char cmd[500] = {0};
    char **args = give_cmd_arr(split_3(str));
    r_dir_t **combi = malloc(sizeof(r_dir_t *) * (ARR_SIZEI(args) + 1));
    int k = 0;

    for (int i = 0; i < count_arr_size(args); i++){
        if (args[i] == NULL)
            break;
        combi[k] = combi_first_create();
        cd = cmd;
        if (to_continue(&k, &i, args, combi) == 1)
            continue;
        i++;
        create_2(args, combi, &i, k);
        k++;
    }
    combi[k] = NULL;
    free_2d_tab(args);
    return combi;
}
