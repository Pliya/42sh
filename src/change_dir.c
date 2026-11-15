/*
** EPITECH PROJECT, 2024
** change dir
** File description:
** the function that changes the directory
*/

#include "../include/my.h"

static void little_clean(void)
{
    int i = 0;

    while (i != 512) {
        shell.old[i] = ' ';
        shell.pwd[i] = ' ';
        i++;
    }
    shell.old[i] = '\0';
    shell.pwd[i] = '\0';
}

static void change_dir_env2(void)
{
    char *str2 = NULL;
    my_env_t *node2 = search_node(shell.head, "OLDPWD");

    if (node2 != NULL) {
        str2 = malloc(sizeof(char) * (my_strlen(shell.old) + 10));
        my_strcpy(str2, "OLDPWD=");
        my_strcat(str2, shell.old);
        node2->str = my_strdup(str2);
        free(str2);
    }
}

void change_dir_env(void)
{
    char *str1 = NULL;
    my_env_t *node1 = search_node(shell.head, "PWD");

    change_dir_env2();
    if (node1 != NULL) {
        str1 = malloc(sizeof(char) * (my_strlen(shell.pwd) + 6));
        my_strcpy(str1, "PWD=");
        my_strcat(str1, shell.pwd);
        node1->str = my_strdup(str1);
        free(str1);
    }
    list_to_array(shell.head);
}

void change_directory(char *path)
{
    char *str = malloc(sizeof(char) * 512);

    my_strcpy(str, path);
    little_clean();
    getcwd(shell.old, 512);
    if (chdir(str) == -1) {
        my_strcat(str, ": ");
        my_putstrerr(str);
        my_putstrerr(strerror(errno));
        my_putstrerr(".\n");
        free(str);
        return;
    }
    getcwd(shell.pwd, 512);
    free(str);
    if (my_strcmp(shell.old, shell.pwd) != 0)
        shell.change_loc += 1;
}

int count_arr_size(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return 0;
    while (tab[i] != NULL) {
        i++;
    }
    return i;
}

char *search_key(char **env, char *to_find)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strstr(env[i], to_find) != NULL &&
        my_strncmp(env[i], to_find, my_strlen(to_find)) == 0)
            return env[i];
    }
    return NULL;
}

static char *dir_path(char **env, char *string)
{
    char *str = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        str = my_strstr(env[i], string);
        if (str != NULL && my_strcmp(string, "HOME=") == 0)
            return str + 5;
    }
    return shell.old;
}

static int back_dir(int count, char **tab)
{
    if (count == 2 && my_strcmp(tab[1], "-") == 0) {
        if (shell.change_loc == 0 && my_strcmp(shell.old, shell.pwd) == 0) {
            my_putstrerr(": No such file or directory.\n");
            shell.status = 1;
            return 1;
        }
        change_directory(shell.old);
        return 1;
    }
    return 0;
}

void change_dir(char **tab, char **env)
{
    int count = count_arr_size(tab);

    if (count > 2) {
        shell.status = 1;
        my_putstrerr("cd: Too many arguments.\n");
        return;
    }
    if (count == 2 && my_strcmp(tab[1], "~") == 0) {
        change_directory(dir_path(env, "HOME="));
        return;
    }
    if (back_dir(count, tab) == 1)
        return;
    if (count == 1) {
        change_directory(dir_path(env, "HOME="));
        return;
    }
    change_directory(tab[1]);
}
