/*
** EPITECH PROJECT, 2024
** execute combi
** File description:
** when is  good
*/

#include "../include/my.h"
static int cont;

static void child_work(sh_t *sh, char *command, char *args[], char **env)
{
    char *str = NULL;
    char **path_ar = NULL;

    str = search_key(env, "PATH=");
    if (str == NULL) {
        my_putstrerr(sh->reader_notmod);
        my_putstrerr(": Command not found.\n");
        exit(1);
    }
    shell.reader_notmod = my_strdup(command);
    path_ar = my_str_to_word_array(str + 5, ':');
    execute_the_child(path_ar, args, env, command);
    free(shell.reader_notmod);
}

static void more_cond(r_dir_t **combi, int i)
{
    int fd = 0;

    if (combi[i]->parenthese_sortie == REDIR) {
        fd = special_dup(combi[i]->parenthese_file, combi[i]->redir_type);
        close(fd);
    }
}

void configure_thechild(r_dir_t **combi, int i)
{
    if (shell.pid1 != 0)
        return;
    if (combi[i]->sortie == PIPE)
        dup2(combi[i]->fd[1], STDOUT_FILENO);
    if (combi[i]->entre == PIPE && i != 0)
        dup2(combi[i - 1]->fd[0], STDIN_FILENO);
    if (combi[i]->parenthese_sortie == PIPE)
        dup2(combi[i]->fd[1], STDOUT_FILENO);
    more_cond(combi, i);
    if (combi[i]->sortie == REDIR)
        redirect(combi[i]->args, combi[i]->file, combi[i]->redir_type);
        shell.reader_splited = combi[i]->args;
        shell.reader_notmod = my_strdup(shell.reader_splited[0]);
    for (int i = 0; combi[i] != NULL; i++) {
        if (combi[i]->sortie == PIPE && combi[i]->fd[1] != 0) {
            close(combi[i]->fd[1]);
            close(combi[i]->fd[0]);
        }
    }
}

static void all_after_oper_inparent(r_dir_t **combi, int i)
{
    if ((combi[i]->sortie == PIPE || combi[i]->parenthese_sortie == PIPE)
        && combi[i]->fd[1] != 0)
        close(combi[i]->fd[1]);
    if (combi[i]->sortie == ET) {
        waitpid(combi[i]->pid, &shell.status1, 0);
        shell.status = WEXITSTATUS(shell.status1);
    }
    if (cont == 2) {
        add_job(combi[i]->pid, str_cmd);
        waitpid(combi[i]->pid, &shell.status1, WNOHANG);
    }
}

void operation_in_parent_for_exec(r_dir_t **combi, int i)
{
    if (combi[i]->pid == 0) {
        if (i != 0)
            waitpid(combi[i - 1]->pid, &shell.status1, 0);
        if (i != 0 && combi[i]->entre == ET)
            waitpid(combi[i - 1]->pid, &shell.status1, 0);
        configure_thechild(combi, i);
        if (possible_cmd() == 1)
            exit(0);
        if (combi[i]->sortie == PARENTESE2) {
            parenthese_execution(combi[i]->cmd);
            exit(0);
        }
        child_work(&shell, combi[i]->args[0], combi[i]->args, shell.env);
    } else
        all_after_oper_inparent(combi, i);
}

static int exec_built_inparent(r_dir_t **combi, int i)
{
    if (strstr(combi[i]->cmd, "`") != NULL) {
        shell.status = 0;
        exit(0);
        return 1;
    }
    combi[i]->args = G_GLOB(split_str2(my_strdup(combi[i]->cmd)));
    shell.reader_splited = combi[i]->args;
    shell.reader_notmod = my_strdup(shell.reader_splited[0]);
    if (combi[i]->sortie != REDIR && combi[i]->sortie != PIPE
    && combi[i]->entre != PIPE && possible_cmd() == 1)
        return 1;
    if (my_strcmp(combi[i]->args[0], "cd") == 0 && possible_cmd() == 1)
        return 1;
    if (my_strcmp(combi[i]->args[0], "setenv") == 0 &&
    count_arr_size(combi[i]->args) > 1 && possible_cmd() == 1)
        return 1;
    if (my_strcmp(combi[i]->args[0], "unsetenv") == 0 &&
    count_arr_size(combi[i]->args) > 1 && possible_cmd() == 1)
        return 1;
    return 0;
}

static void all_wait_execve(r_dir_t **combi)
{
    for (int i = 0; combi[i] != NULL; i++) {
        if (combi[i]->pid != 0 && is_background == 0
        && cont == 0) {
            waitpid(combi[i]->pid, &shell.status1, WUNTRACED | WCONTINUED);
            shell.status = WEXITSTATUS(shell.status1);
            child_stat(shell.status1);
        }
    }
    cont = 0;
}

int exec_combitable(r_dir_t **combi)
{
    for (int i = 0; combi[i] != NULL; i++)
        if (combi[i]->sortie == PIPE || combi[i]->parenthese_sortie == PIPE)
            pipe(combi[i]->fd);
    for (int i = 0; combi[i] != NULL; i++) {
        if (i != 0 && combi[i]->entre == ET && WIFEXITED(shell.status) != true)
            break;
        if (i != 0 && combi[i]->entre == OU && shell.status == 0)
            break;
            str_cmd = my_strdup(combi[i]->cmd);
        if (exec_built_inparent(combi, i) == 1)
            continue;
        if (combi[i]->sortie == J_CONTROL)
            cont = 2;
        combi[i]->pid = fork();
        fg_pid = combi[i]->pid;
        operation_in_parent_for_exec(combi, i);
    }
    all_wait_execve(combi);
}
