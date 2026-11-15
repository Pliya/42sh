/*
** EPITECH PROJECT, 2024
** set.c
** File description:
** set.c
*/

#include "../include/my.h"

int my_set(lol_t *p)
{
    while (p != NULL) {
        printf("%s    %s\n", p->name, p->value);
        p = p->next;
    }
    return 0;
}

static void little_place(lol_t *p, lol_t **head, char *m, char *n)
{
    lol_t *l;

    l = *head;
    if (my_strcmp(l->name, m) == 0) {
        l->value = my_strdup(n);
        return;
    }
    while (l->next != NULL) {
        if (my_strcmp(l->name, m) == 0) {
            l->value = my_strdup(n);
            return;
        }
        l = l->next;
    }
    l->next = p;
}

void add_at_end(char *m, char *n, lol_t **head)
{
    lol_t *p = malloc(sizeof(lol_t));
    lol_t *l;

    p->name = strdup(m);
    p->value = my_strdup(n);
    p->next = NULL;
    if (*head == NULL) {
        *head = p;
        return;
    } else {
        little_place(p, head, m, n);
    }
}

lol_t *my_s(char *a, char *b, lol_t *p)
{
    int i = 0;

    if (error_for_set(a) != 84)
        add_at_end(a, b, &p);
    return p;
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

void local_set_var(char *str)
{
    char *str1 = little_replace(str);
    char **args = split_str2(str1);

    if (count_arr_size(args) == 0)
        my_set(shell.local);
    if (count_arr_size(args) == 1)
        shell.local = my_s(args[0], " ", shell.local);
    if (count_arr_size(args) == 2)
        shell.local = my_s(args[0], args[1], shell.local);
    if (count_arr_size(args) > 2) {
        for (int i = 0; args[i] != NULL; i++)
            shell.local = my_s(args[i], " ", shell.local);
    }
    if (str1 != NULL)
        free(str1);
    if (args != NULL)
        free_2d_tab(args);
}

void local_unset_var(char *str)
{
    char **args = split_str2(str);

    if (args[0] == NULL)
        my_unset(NULL, &shell.local);
    for (int i = 0; i < count_arr_size(args); i++)
        my_unset(args[i], &shell.local);
    if (args != NULL)
        free_2d_tab(args);
}
