/*
** EPITECH PROJECT, 2024
** pe
** File description:
** pe
*/

#include "../include/my.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *operators_table[] = {
    ";",
    "||",
    "&&",
    ">",
    ">>",
    "<",
    "<<",
    "|",
    ")",
    "(",
    NULL
};

void print_tree(b_tree_t *t)
{
    if (t == NULL) {
        return;
    }
    if (t->value != NULL) {
        printf("ma valeur est \"%s\"\n", t->value);
        if (t->right)
            printf("mon right est \"%s\"\n", t->right->value);
        else
            printf("NULL right\n");
        if (t->left)
            printf("mon left est \"%s\"\n", t->left->value);
        else
            printf("NULL left\n");
    }
    printf("\n");
    print_tree(t->right);
    print_tree(t->left);
}

char *last_founded(char *string, char *to_found)
{
    int i = 0;
    char *str = NULL;

    if (string == NULL || to_found == NULL)
        return NULL;
    do {
        if (str != NULL) {
            str += strlen(to_found);
            string = str;
        }
        if (strcmp(to_found, ";") == 0)
            str = my_strstr1(string, to_found);
        if (strcmp(to_found, ";") != 0)
            str = my_strstr(string, to_found);
        if (i == 0 && str == NULL)
            return NULL;
        i++;
    } while (str != NULL);
    return string - strlen(to_found);
}

sp_string_t string_cast(char *str)
{
    int i = 0;
    char *src = NULL;
    sp_string_t sps = {NULL, NULL, NULL};

    for (i = 0; operators_table[i] != NULL; i++) {
        src = last_founded(str, (char *)operators_table[i]);
        if (src != NULL)
            break;
    }
    if (src != NULL) {
        sps.oper = strdup(operators_table[i]);
        sps.right = my_strdup(src + my_strlen(sps.oper));
        *src = '\0';
        sps.left = strdup(str);
    } else {
        sps.right = my_strdup(str);
    }
    return sps;
}

int is_operator_tab(char *str)
{
    if (str == NULL)
        return 0;
    for (int i = 0; operators_table[i] != NULL; i++)
        if (!strcmp(str, operators_table[i]))
            return 1;
    return 0;
}

void parenthese_execution(char *str)
{
    b_tree_t *tree = NULL;

    if (str == NULL)
        return;
    str = remplacer(str, "\\;", ";");
    tree = create_tree(str);
    execve_binary_tree(tree);
    free_tree(tree);
}
