/*
** EPITECH PROJECT, 2024
** parenthese
** File description:
** parenthese
*/

#include "../include/my.h"

static int nb_quote;
static char *real_cmd;
static void et_executions(b_tree_t *t)
{
    if (is_operator_type(t->value) == ET){
        execve_binary_tree(t->left);
        if (WIFEXITED(shell.status) != true) {
            return;
        }
        execve_binary_tree(t->right);
    }
}

static void ou_executions(b_tree_t *t)
{
    if (is_operator_type(t->value) == OU){
        execve_binary_tree(t->left);
        if (shell.status == 0) {
            return;
        }
        execve_binary_tree(t->right);
    }
}

static void point_executions(b_tree_t *t)
{
    if (strcmp(t->value, ";") == 0){
        execve_binary_tree(t->left);
        execve_binary_tree(t->right);
    }
}

static void more_if(b_tree_t *t, int fd, int type)
{
    pid_t p;
    char **c = NULL;
    char *file = b_search_noncommand(t->right);

    if (file != NULL) {
        c = split_str2(file);
        file = c[0];
    }
    if (file != NULL)
        p = fork();
    if (p == 0) {
        fd = special_dup(file, type);
        close(fd);
        execve_binary_tree(t->left);
        exit(0);
    } else {
        waitpid(p, &shell.status1, 0);
        shell.status = WEXITSTATUS(shell.status1);
    }
}

static void redirections_executions(b_tree_t *t)
{
    int fd = 0;
    int type;
    pid_t p;

    if (t == NULL)
        return;
    if (is_operator_type(t->value) == REDIR){
        type = identity_oper(t->value);
        more_if(t, fd, type);
    }
}

static void pipe_executions1(int *p_fd, b_tree_t *t)
{
    pid_t p;

    p = fork();
    if (p == 0) {
        dup2(p_fd[1], STDOUT_FILENO);
        close(p_fd[0]);
        close(p_fd[1]);
        execve_binary_tree(t->left);
        exit(0);
    } else {
        waitpid(p, &shell.status1, 0);
        shell.status = WEXITSTATUS(shell.status1);
    }
}

static void pipe_executions2(int *p_fd, b_tree_t *t)
{
    pid_t p;

    p = fork();
    if (p == 0) {
        dup2(p_fd[0], STDIN_FILENO);
        close(p_fd[0]);
        close(p_fd[1]);
        execve_binary_tree(t->right);
        exit(0);
    } else {
        close(p_fd[0]);
        close(p_fd[1]);
        waitpid(p, &shell.status1, 0);
        shell.status = WEXITSTATUS(shell.status1);
    }
}

static void pipe_executions(b_tree_t *t)
{
    int p_fd[2] = {0};
    char *file = NULL;
    int fd = 0;
    int type;

    if (t == NULL)
        return;
    if (is_operator_type(t->value) == PIPE){
        pipe(p_fd);
        pipe_executions1(p_fd, t);
        pipe_executions2(p_fd, t);
    }
}

static void execv_parenthese_branch(b_tree_t *t)
{
    if (is_operator_type(t->value) == PARENTESE1){
        execve_binary_tree(t->right);
    }
    if (is_operator_type(t->value) == PARENTESE2){
        execve_binary_tree(t->left);
    }
}

void execve_binary_tree(b_tree_t *t)
{
    if (t == NULL)
        return;
    if (is_operator_tab(t->value) == 1){
        point_executions(t);
        et_executions(t);
        ou_executions(t);
        redirections_executions(t);
        pipe_executions(t);
        execv_parenthese_branch(t);
    }
    if (strlen(t->value) != 0 && is_operator_tab(t->value) == 0) {
        main_part2(t->value);
    }
}
