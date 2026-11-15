/*
** EPITECH PROJECT, 2024
** execute the file as a function
** File description:
** the file
*/

#include "../include/my.h"

static void exec_normalbin(char **args)
{
    char *str_tofind = my_strstr(args[0], "./");

    if (str_tofind != NULL) {
        if (opendir(str_tofind + 2) != NULL) {
            my_putstrerr(args[0]);
            my_putstrerr(": Permission denied.\n");
            exit(1);
        }
        if (access(args[0], X_OK) == -1) {
            my_putstrerr(args[0]);
            my_putstrerr(": Command not found.\n");
            exit(1);
        }
        execve(args[0], args, shell.env);
    }
}

static void check_all_paths(char **args, char **paths)
{
    int i = 0;
    char *str_concat = malloc(sizeof(char) * 1024);

    while (paths[i] != NULL) {
        my_strcpy(str_concat, paths[i]);
        my_strcat(str_concat, "/");
        args[0] = path_cleaner(shell.reader_notmod);
        my_strcat(str_concat, args[0]);
        if (access(str_concat, X_OK) == 0) {
            execve(str_concat, args, shell.env);
        }
        i++;
        free(str_concat);
        str_concat = malloc(sizeof(char) * 1024);
    }
    free(str_concat);
}

void execute_the_child(char **paths, char **args, char **env, char *n_modified)
{
    exec_normalbin(args);
    if (opendir(n_modified) != NULL) {
        my_putstrerr(args[0]);
        my_putstrerr(": Permission denied.\n");
        exit(1);
    }
    check_all_paths(args, paths);
    if (access(n_modified, X_OK) == 0)
        execve(n_modified, args, env);
    if (execve(n_modified, args, env) == -1) {
        if (errno == ENOEXEC) {
            my_putstrerr(n_modified);
            my_putstrerr(": ");
            my_putstrerr("Exec format error. Wrong Architecture.\n");
            exit(1);
        }
    }
    my_putstrerr(n_modified);
    my_putstrerr(": Command not found.\n");
    exit(1);
}
