/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** alias function
*/

#include "../include/my.h"

char *read_file(char *filepath)
{
    char *tab = NULL;
    struct stat t;
    int fd = open(filepath, O_RDONLY);

    stat(filepath, &t);
    if (fd == -1)
        return NULL;
    tab = malloc(sizeof(char) * (t.st_size + 2));
    read(fd, tab, t.st_size);
    tab[t.st_size] = '\0';
    close(fd);
    return tab;
}

static char *little_replace(char *s)
{
    if (s == NULL)
        return NULL;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '=') {
            s[i] = ' ';
            return s;
        }
    }
    return s;
}

void alias_cmd(char *str)
{
    char *str1 = little_replace(str);
    char **args = split_str2(str1);

    if (count_arr_size(args) == 0)
        my_set(shell.alias);
    if (count_arr_size(args) == 1)
        shell.alias = my_s(args[0], NULL, shell.alias);
    if (count_arr_size(args) >= 2)
        shell.alias = my_s(args[0], array_to_str(args, 1), shell.alias);
    if (str1 != NULL)
        free(str1);
    if (args != NULL)
        free_2d_tab(args);
}
