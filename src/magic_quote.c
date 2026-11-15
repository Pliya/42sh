/*
** EPITECH PROJECT, 2024
** ls
** File description:
** ls
*/

#include "../include/my.h"

static char *cd;

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

char *return_the_filecontent(char *command, char *ptr)
{
    FILE *fp = popen(command, "r");
    char buffer[128 * 10];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcpy(ptr, buffer);
        ptr += strlen(buffer);
    }
    pclose(fp);
    return ptr;
}

char *stock_thick_cmd(char *start)
{
    char command[500];
    int i = 0;

    while (*start && *start != '`' && i < sizeof(command) - 1) {
        command[i] = *start;
        i++;
        start++;
    }
    cd = start;
    command[i] = '\0';
    return strdup(command);
}

char *replace_backticks(char *input)
{
    char *output = malloc(1024);
    char *ptr = output;
    char *start = input;

    while (*start) {
        if (*start == '`') {
            start++;
            ptr = return_the_filecontent(stock_thick_cmd(start), ptr);
            start = cd;
        } else {
            *ptr = *start;
            ptr++;
            start++;
        }
    }
    *ptr = '\0';
    return output;
}
