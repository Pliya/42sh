/*
** EPITECH PROJECT, 2024
** possible commands
** File description:
** of the sh
*/

#include "../include/my.h"

const char *built_in[] = {
    "where",
    "which",
    "cd",
    "env",
    "setenv",
    "unsetenv",
    "set",
    "unset",
    "alias",
    "history",
    "repeat",
    "fg",
    "bg",
    "jobs",
    "echo",
    NULL
};

static int possible_cmd2(void)
{
    if (my_strcmp(shell.reader_splited[0], "unsetenv") == 0) {
        if (shell.reader_splited[1] == NULL) {
            my_putstrerr("unsetenv: Too few arguments.\n");
            shell.status = 1;
            return 1;
        }
        for (int i = 1; shell.reader_splited[i] != NULL; i++) {
            shell.utl_str = malloc(sizeof(char) *
            (my_strlen(shell.reader_splited[i]) + 4));
            my_strcpy(shell.utl_str, shell.reader_splited[i]);
            my_strcat(shell.utl_str, "=");
            unset_env(shell.utl_str, shell.head);
            free(shell.utl_str);
        }
        return 1;
    }
    return 0;
}

static int possible_commands(void)
{
    if (my_strcmp(shell.reader_splited[0], "cd") == 0) {
        change_dir(shell.reader_splited, shell.env);
        change_dir_env();
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "env") == 0) {
        print_env(shell.head);
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "setenv") == 0) {
        set_env(shell.reader_splited);
        return 1;
    }
    if (possible_cmd2() == 1)
        return 1;
    exit_shell(shell.reader_splited[0], shell.status);
    return 0;
}

static int possible_cmd3(void)
{
    if (my_strcmp(shell.reader_splited[0], "alias") == 0) {
        alias_cmd(array_to_str(shell.reader_splited, 1));
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "history") == 0) {
        history(h);
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "set") == 0){
        local_set_var(array_to_str(shell.reader_splited, 1));
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "unset") == 0){
        local_unset_var(array_to_str(shell.reader_splited, 1));
        return 1;
    }
    return 0;
}

static int jobs_buit_in_poscmd(void)
{
    int a = 0;

    if (my_strcmp(shell.reader_splited[0], "fg") == 0){
        fg_cmd(shell.reader_splited);
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "bg") == 0){
        bg_cmd(shell.reader_splited);
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "jobs") == 0){
        jobs_fct(jobs, &a);
        return 1;
    }
    return 0;
}

static int possible_cmd4(void)
{
    char *cmd = NULL;

    if (jobs_buit_in_poscmd() == 1)
        return 1;
    if (my_strcmp(shell.reader_splited[0], "repeat") == 0){
        repeat_cmd(shell.reader_splited);
        return 1;
    }
    if (shell.reader_splited[0][0] == '!' && shell.reader_splited[0][1] == '!'
        && shell.reader_splited[0][2] == '\0') {
        cmd = return_last_cmd(h);
        main_part2(cmd);
        return 1;
    }
}

static int possible_cmd5(void)
{
    char *cmd = NULL;
    int n = 1;
    char *str = NULL;

    if (shell.reader_splited[0][0] == '!'
        && c_digit(shell.reader_splited[0]) == 0) {
        n = atoi(strdup(&shell.reader_splited[0][1]));
        if (return_n_cmd(h, n) != NULL)
            printf("%s\n", return_n_cmd(h, n));
        main_part2(return_n_cmd(h, n));
        return 1;
    }
    if (shell.reader_splited[0][0] == '!'
        && c_digit(shell.reader_splited[0]) == 1) {
        str = strdup(&shell.reader_splited[0][1]);
        if (return_str_cmd(h, str, &fd) != NULL)
            printf("%s\n", return_str_cmd(h, str, &fd));
        main_part2(return_str_cmd(h, str, &fd));
        return 1;
    }
}

static int possible_cmd6(void)
{
    if (my_strcmp(shell.reader_splited[0], "where") == 0) {
        where_fct();
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "which") == 0) {
        which_fct();
        return 1;
    }
    if (my_strcmp(shell.reader_splited[0], "my_google") == 0) {
        system("python3 my_google.py");
        return 1;
    }
    shell.reader_splited = ret_set_var();
    shell.reader_splited = ret_set_env();
    if (my_strcmp(shell.reader_splited[0], "my_google") == 0) {
        system("python3 my_google.py");
        return 1;
    }
    return 0;
}

static int part1_possible_cmd(void)
{
    if (shell.reader_splited[0] == NULL) {
        list_to_array(shell.head);
        return 1;
    }
    if (possible_commands() == 1) {
        list_to_array(shell.head);
        return 1;
    }
    if (possible_cmd3() == 1) {
        list_to_array(shell.head);
        return 1;
    }
    if (possible_cmd4() == 1) {
        list_to_array(shell.head);
        return 1;
    }
    return 0;
}

int possible_cmd(void)
{
    if (possible_cmd6() == 1) {
        list_to_array(shell.head);
        return 1;
    }
    if (part1_possible_cmd() == 1)
        return 1;
    if (possible_cmd5() == 1) {
        list_to_array(shell.head);
        return 1;
    }
}
