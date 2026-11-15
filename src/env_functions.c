/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** a file for the env functions
*/

#include "../include/my.h"

my_env_t *create_env_node(char *str)
{
    my_env_t *new_node = malloc(sizeof(my_env_t));

    new_node->str = my_strdup(str);
    new_node->next = NULL;
    return new_node;
}

void add_env_node(my_env_t **head, my_env_t *node)
{
    my_env_t *nt = *head;

    if (*head == NULL) {
        *head = node;
        return;
    }
    if ((*head)->next == NULL) {
        (*head)->next = node;
        return;
    }
    while (nt->next != NULL)
        nt = nt->next;
    nt->next = node;
}

void env_strdup(my_env_t **head, char **env)
{
    int i = 0;

    *head = NULL;
    while (environ[i] != NULL) {
        add_env_node(head, create_env_node(environ[i]));
        i++;
    }
}

static int elements_in_list(my_env_t *hd)
{
    int i = 0;

    while (hd != NULL) {
        i++;
        hd = hd->next;
    }
    return i;
}

void list_to_array(my_env_t *hd)
{
    int i = 0;
    int j = elements_in_list(hd);

    shell.env = malloc(sizeof(char *) * (j + 8));
    for (i = 0; i < j; i++) {
        shell.env[i] = my_strdup(hd->str);
        hd = hd->next;
    }
    shell.env[i] = NULL;
}

void print_env(my_env_t *hd)
{
    while (hd != NULL) {
        mini_printf("%s\n", hd->str);
        hd = hd->next;
    }
}
