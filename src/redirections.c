/*
** EPITECH PROJECT, 2024
** redirections
** File description:
** for the minishell2
*/

#include "../include/my.h"

static void child_work(sh_t *sh, char *command, char *args[], char **env)
{
    char *str = NULL;
    char **path_ar = NULL;

    str = search_key(sh->env, "PATH=");
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

int redirect1(char **cmd, char *file)
{
    int status = 0;
    int fd = 0;

    fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    dup2(fd, STDOUT_FILENO);
    shell.reader_splited = cmd;
    if (possible_cmd() == 1) {
        close(fd);
        exit(0);
    }
    close(fd);
    child_work(&shell, cmd[0], cmd, shell.env);
}

int redirect2(char **cmd, char *file)
{
    int status = 0;
    int fd = 0;

    fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
    dup2(fd, STDOUT_FILENO);
    shell.reader_splited = cmd;
    if (possible_cmd() == 1) {
        close(fd);
        exit(0);
    }
    close(fd);
    child_work(&shell, cmd[0], cmd, shell.env);
}

int redirect3(char **cmd, char *file)
{
    int status = 0;
    int fd = 0;

    fd = open(file, O_RDONLY, 0644);
    dup2(fd, STDIN_FILENO);
    shell.reader_splited = cmd;
    if (possible_cmd() == 1) {
        close(fd);
        exit(0);
    }
    close(fd);
    child_work(&shell, cmd[0], cmd, shell.env);
}

static int *writeredirection_file(char *end)
{
    int *pipe_fd = malloc(sizeof(int) * 3);

    pipe(pipe_fd);
    shell.utl_str = NULL;
    do {
        if (shell.utl_str != NULL)
            free(shell.utl_str);
        shell.utl_str = NULL;
        mini_printf("? ");
        getline(&shell.utl_str, &shell.utl_si, stdin);
        if (shell.utl_si != my_strlen(end)
        && my_strncmp(end, shell.utl_str, shell.utl_si) != 0)
            write(pipe_fd[1], shell.utl_str, my_strlen(shell.utl_str));
        shell.utl_str[my_strlen(shell.utl_str) - 1] = '\0';
    } while (my_strcmp(end, shell.utl_str) != 0);
    return pipe_fd;
}

int redirect4(char **cmd, char *end)
{
    int pid = 0;
    int status = 0;
    int *pipe_fd = writeredirection_file(end);

    dup2(pipe_fd[0], STDIN_FILENO);
    shell.reader_splited = cmd;
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    if (possible_cmd() == 1)
        exit(0);
    child_work(&shell, cmd[0], cmd, shell.env);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid, &status, 0);
    free(pipe_fd);
}

int redirect(char **command, char *file, int flag)
{
    if (flag == 1)
        redirect1(command, file);
    if (flag == 2)
        redirect2(command, file);
    if (flag == 3)
        redirect3(command, file);
    if (flag == 4)
        redirect4(command, file);
}
