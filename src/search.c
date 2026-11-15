/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-2-42sh-bill.adjagboni
** File description:
** search.c
*/

#include "../include/my.h"

int get_nbpath(char *var)
{
    int count = 0;

    for (int i = 0; var[i] != '\0'; i++) {
        if (var[i] == ':')
            count++;
    }
    return count;
}

char **tokenize_args(char *input, int func(char *), char const *sep)
{
    int count = func(input) + 1;
    char **args = malloc(sizeof(char *) * (count + 1));
    char *cpy = my_strdup(input);
    char *token = strtok(cpy, sep);
    int i = 0;

    while (token) {
        args[i] = token;
        token = strtok(NULL, sep);
        i++;
    }
    args[i] = NULL;
    return args;
}

int check_binary(char *path, char *str)
{
    my_strcat(path, "/");
    my_strcat(path, str);
    if (access(path, X_OK) == 0) {
        return 0;
    }
    return 1;
}

void search_path(char *command)
{
    char **tab = tokenize_args(getenv("PATH"), get_nbpath, ":");
    char *full_path;

    for (int i = 0; tab[i] != NULL; i++) {
            full_path = malloc(my_strlen(tab[i]) + my_strlen(command) + 2);
            full_path = my_strcpy(full_path, tab[i]);
            if (check_binary(full_path, command) == 0) {
                printf("%s\n", full_path);
            }
            free(full_path);
        }
}

void search_first_path(char *command)
{
    char **tab = tokenize_args(getenv("PATH"), get_nbpath, ":");
    char *full_path;

    for (int i = 0; tab[i] != NULL; i++) {
            full_path = malloc(my_strlen(tab[i]) + my_strlen(command) + 2);
            full_path = my_strcpy(full_path, tab[i]);
            if (check_binary(full_path, command) == 0) {
                printf("%s\n", full_path);
                return;
            }
            free(full_path);
        }
    fprintf(stderr, "%s: Command not found.\n", command);
}
