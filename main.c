/*
** EPITECH PROJECT, 2024
** The main function
** File description:
** of the program of minishell
*/

#include "include/my.h"
sh_t shell;
pid_t fg_pid;
history_t *h;
int fd;
job_t *jobs;
char *str_cmd;
int is_background;
int dup_history_size;
int history_size;
integer_t val;

char *ending(struct termios *old)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, old);
    return NULL;
}

static void print_backslash_n(int i)
{
    mini_printf("\033[1;32m");
    mini_printf("[SINGINT]");
    mini_printf("\033[0m");
    mini_printf("\n");
    shell.status = 1;
    print_the_prompt(shell.env);
    shell.status = 0;
}

static void sigtstp_handler(int sig)
{
    if (fg_pid > 0) {
        add_job(fg_pid, str_cmd);
        kill(fg_pid, SIGTSTP);
        is_background = 1;
        printf("Suspended (signal)\n");
        fg_pid = -1;
    }
}

static void init(int ac, char **av, char **env)
{
    jobs = NULL;
    shell.status = 0;
    shell.change_loc = 0;
    shell.local = NULL;
    shell.alias = NULL;
    env_strdup(&shell.head, env);
    getcwd(shell.old, 512);
    getcwd(shell.pwd, 512);
    signal(2, &print_backslash_n);
    signal(SIGTSTP, &sigtstp_handler);
    signal(SIGSEGV, &viral);
}

int main_part2(char *str)
{
    char *s = str;
    char **args = NULL;

    if (s == NULL)
        return 0;
    args = split_string1(my_strdup(str));
    for (int i = 0; args[i] != NULL; i++){
        list_to_array(shell.head);
        exec_combi(args[i]);
    }
    free_2d_tab(args);
}

int main_part2bt(char *str)
{
    char *s = str;
    char **args = NULL;

    if (s == NULL)
        return 0;
    args = split_string1(my_strdup(str));
    for (int i = 0; args[i] != NULL && shell.status == 0; i++){
        list_to_array(shell.head);
        exec_combi(args[i]);
    }
    free_2d_tab(args);
}

void boucle_infini(void)
{
    while (1) {
        is_background = 0;
        fg_pid = -1;
        list_to_array(shell.head);
        print_the_prompt(shell.env);
        shell.reader = reader();
        shell.reader = place_alias(shell.reader);
        shell.reader = remplacer_point_virgule(shell.reader);
        shell.reader = remplacer(shell.reader, "&&", " && ");
        if (shell.reader != NULL && shell.reader[0] != '!')
            history_strdup(&h, shell.reader);
        main_part2(shell.reader);
    }
}

int main(int ac, char **av, char **env)
{
    fd = 1;
    str_cmd = NULL;
    init(ac, av, env);
    boucle_infini();
    return 0;
}
