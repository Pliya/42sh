/*
** EPITECH PROJECT, 2024
** tree .c
** File description:
** tree function
*/

#include "../include/my.h"

static b_tree_t *left_operator(sp_string_t sps, b_tree_t *t, char *str)
{
    if (sps.left != NULL) {
        t->value = strdup(sps.left);
        if (my_strcmp(sps.left, str) == 0)
            return t;
        t->right = create_tree(sps.right);
        t->left = create_tree(sps.left);
        return t;
    }
    return t;
}

static b_tree_t *right_operator(sp_string_t sps, b_tree_t *t, char *str)
{
    if (sps.right != NULL) {
        t->value = strdup(sps.right);
        if (my_strcmp(sps.right, str) == 0)
            return t;
        t->right = create_tree(sps.right);
        t->left = create_tree(sps.left);
        return t;
    }
    return left_operator(sps, t, str);
}

static b_tree_t *tree_operator(sp_string_t sps, b_tree_t *t, char *str)
{
    if (sps.oper != NULL) {
        t->value = strdup(sps.oper);
        if (my_strcmp(sps.oper, str) == 0 &&
        my_strcmp(sps.oper, "`") == 0) {
            t->right = create_tree(sps.right);
            t->left = create_tree(sps.left);
            return t;
        }
        if (my_strcmp(sps.oper, str) == 0)
            return t;
        t->right = create_tree(sps.right);
        t->left = create_tree(sps.left);
        return t;
    }
    return right_operator(sps, t, str);
}

sp_string_t *fill_spstruct(char *oper, char *r, char *l)
{
    sp_string_t *sp = malloc(sizeof(sp_string_t));

    if (l != NULL)
        sp->left = strdup(l);
    else
        sp->left = NULL;
    if (r != NULL)
        sp->right = strdup(r);
    else
        sp->right = NULL;
    if (oper != NULL)
        sp->oper = strdup(oper);
    else
        sp->oper = NULL;
    return sp;
}

void free_spstruct(sp_string_t *sp)
{
    if (sp == NULL)
        return;
    if (sp->left != NULL)
        free(sp->left);
    sp->left = NULL;
    if (sp->right != NULL)
        free(sp->right);
    sp->right = NULL;
    if (sp->oper != NULL)
        free(sp->oper);
    sp->oper = NULL;
}

b_tree_t *create_branch(char *value)
{
    b_tree_t *t = malloc(sizeof(b_tree_t));

    t->value = my_strdup(value);
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;
    return t;
}

void free_tree(b_tree_t *t)
{
    if (t == NULL)
        return;
    if (t->value != NULL)
        free(t->value);
    free_tree(t->left);
    free_tree(t->right);
    if (t->left != NULL)
        free(t->left);
    if (t->right != NULL)
        free(t->right);
}

b_tree_t *create_tree(char *str)
{
    b_tree_t *t = NULL;
    sp_string_t sps = {NULL, NULL, NULL};

    if (str == NULL) {
        return NULL;
    }
    sps = string_cast(str);
    if (sps.oper == NULL && sps.right == NULL && sps.left == NULL)
        return NULL;
    t = create_branch("");
    return tree_operator(sps, t, str);
}
