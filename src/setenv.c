/*
** EPITECH PROJECT, 2024
** setenv function
** File description:
** minishell
*/

#include "../include/my.h"

static int verify_char(char c)
{
    if (!((c >= 'a' && c <= 'z') || (c <= 'Z' && c >= 'A')
        || (c >= '0' && c <= '9') || c == '_'))
            return 1;
    else
        return 0;
}

static int verify_char_setenv(char *str)
{
    char c;

    for (int i = 1; str[i] != '\0'; i++) {
        c = str[i];
        if (verify_char(c) == 1)
            return 1;
    }
    return 0;
}

my_env_t *search_node(my_env_t *head, char *to_find)
{
    char *str = NULL;

    while (head != NULL) {
        str = malloc(sizeof(char) * (my_strlen(to_find) + 3));
        my_strcpy(str, to_find);
        my_strcat(str, "=");
        if (my_strstr(head->str, to_find) != NULL &&
        my_strncmp(head->str, str, my_strlen(str)) == 0)
            return head;
        free(str);
        head = head->next;
    }
    return NULL;
}

static void set_env_arrsize2(char **args)
{
    my_env_t *node = search_node(shell.head, args[1]);
    char *str = malloc(sizeof(char) * (my_strlen(args[1]) + 2));

    my_strcpy(str, args[1]);
    my_strcat(str, "=");
    if (!((args[1][0] >= 'a' && args[1][0] <= 'z') ||
    (args[1][0] <= 'Z' && args[1][0] >= 'A') || args[1][0] == '_')) {
        my_putstrerr("setenv: Variable name must begin with a letter.\n");
        shell.status = 1;
        return;
    }
    if (node != NULL) {
        node->str = my_strdup(str);
    } else {
        node = create_env_node(str);
        add_env_node(&shell.head, node);
    }
    free(str);
}

static void set_env_arrsize3(char **args)
{
    my_env_t *node = search_node(shell.head, args[1]);
    char *str = malloc(sizeof(char) *
    (my_strlen(args[1]) + my_strlen(args[2]) + 5));

    my_strcpy(str, args[1]);
    my_strcat(str, "=");
    my_strcat(str, args[2]);
    if (!((args[1][0] >= 'a' && args[1][0] <= 'z') ||
    (args[1][0] <= 'Z' && args[1][0] >= 'A') || args[1][0] == '_')) {
        my_putstrerr("setenv: Variable name must begin with a letter.\n");
        shell.status = 1;
        return;
    }
    if (node != NULL) {
        free(node->str);
        node->str = str;
    } else {
        node = create_env_node(str);
        add_env_node(&shell.head, node);
    }
}

static void set_env_2args(int j, char **args)
{
    if (j == 2) {
        if (verify_char_setenv(args[1]) == 1) {
            my_putstrerr
            ("setenv: Variable name must contain alphanumeric characters.\n");
            shell.status = 1;
            return;
        }
        set_env_arrsize2(args);
    }
}

void set_env(char **args)
{
    my_env_t *node = NULL;
    char *str = NULL;
    int j = count_arr_size(args);

    if (j == 1)
        print_env(shell.head);
    set_env_2args(j, args);
    if (j == 3) {
        if (verify_char_setenv(args[1]) == 1) {
            my_putstrerr
            ("setenv: Variable name must contain alphanumeric characters.\n");
            shell.status = 1;
            return;
        }
        set_env_arrsize3(args);
    }
    if (j > 3) {
        my_putstrerr("setenv: Too many arguments.\n");
        shell.status = 1;
    }
}
