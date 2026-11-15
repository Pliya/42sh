/*
** EPITECH PROJECT, 2024
** print the prompt
** File description:
** of minishell
*/

#include "../include/my.h"

char *reader(void)
{
    char *buf = NULL;
    size_t len = 0;
    int the_return;

    history_size = fd;
    dup_history_size = history_size;
    val = init_integers();
    buf = my_getline();
    printf("\n");
    if (buf == "exit")
        exit(shell.status);
    return buf;
}

static char *user_name(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        str = my_strstr(env[i], "USER");
        if (str != NULL)
            return str + 9;
    }
    return "root";
}

static char *host_name(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        str = my_strstr(env[i], "HOSTNAME=");
        if (str != NULL)
            return str + 9;
    }
    return "host_name";
}

void print_the_prompt(char **env)
{
    mini_printf("\033[1;34m");
    mini_printf("[%s@%s]", user_name(env), host_name(env));
    mini_printf("\033[0m");
    if (shell.status != 0 && shell.status != 20) {
        mini_printf("\033[1;31m");
        mini_printf("{%d}", shell.status);
        mini_printf("\033[0m");
    } else {
        mini_printf("\033[1;32m");
        mini_printf("{%d}", shell.status);
        mini_printf("\033[0m");
    }
    mini_printf("$>");
}

char *path_cleaner(char *str)
{
    int i = 0;

    if (my_strstr(str, "/") == NULL)
        return my_strdup(str);
    for (i = my_strlen(str); str[i] != '/' && i != 0; i--);
    return my_strdup(str + i + 1);
}

static void child_work(sh_t *sh)
{
    char *str = NULL;
    char **path_ar = NULL;

    str = search_key(sh->env, "PATH=");
    if (str == NULL) {
        my_putstrerr(sh->reader_notmod);
        my_putstrerr(": Command not found.\n");
        exit(1);
    }
    path_ar = my_str_to_word_array(str + 5, ':');
    execute_the_child(path_ar,
    sh->reader_splited, sh->env, sh->reader_notmod);
}

void child_stat(int status)
{
    if (WIFEXITED(status) != true && shell.status != 20
    && shell.status1 != 136) {
        my_putstrerr(strsignal(WTERMSIG(status)));
        my_putstrerr("\n");
    }
    if (shell.status1 == 136)
        my_putstrerr("Floating exception\n");
}

int execute(sh_t *sh)
{
    int pid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0)
        child_work(sh);
    else {
        waitpid(pid, &status, 0);
        shell.status = WEXITSTATUS(status);
        child_stat(status);
    }
}
