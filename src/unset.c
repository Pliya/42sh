/*
** EPITECH PROJECT, 2024
** unset
** File description:
** unset
*/

#include "../include/my.h"
int delete(lol_t **data, char *id)
{
    lol_t *end = *data;
    lol_t *prev = NULL;

    if (end != NULL && (strncmp(end->name, id, strlen(id)) == 0)) {
        *data = (*data)->next;
        free(end);
        return 0;
    }
    while (end != NULL && (strncmp(end->name, id, strlen(id)) != 0)) {
        prev = end;
        end = end->next;
    }
    if (end == NULL)
        return 84;
    if (prev != NULL)
        prev->next = end->next;
    return 0;
}

int my_unset(char *p, lol_t **ab)
{
    if (p == NULL || p[0] == '\0') {
        printf("unset:");
        printf(" Too few arguments.\n");
        return 1;
    } else {
        delete(ab, p);
    }
}
