/*
** EPITECH PROJECT, 2024
** history.c
** File description:
** implementation of history command
*/

#include "../include/my.h"
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char times[20 * 100];
void history_strdup(history_t **begin, char *command)
{
    history_t *new = malloc(sizeof(history_t));
    history_t *last = *begin;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (command[0] != '!' && command[0] != '\0') {
        strftime(times, sizeof(times), "%H:%M", tm_info);
        my_strcat(times, "  ");
        new->str = my_strdup(my_strcat(times, command));
        new->i = fd;
        fd++;
        new->next = NULL;
    }
    if (*begin == NULL) {
        *begin = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}

void history(history_t *h)
{
    history_t *temp = h;

    while (temp != NULL) {
        if (temp->str != NULL)
            printf("%d  %s\n", temp->i, temp->str);
        temp = temp->next;
    }
}

char *return_last_cmd(history_t *h)
{
    history_t *temp = h;

    if (temp == NULL)
        return NULL;
    while (temp != NULL) {
        temp = temp->next;
    }
    return &temp->str[7];
}

char *return_n_cmd(history_t *h, int n)
{
    history_t *temp = h;

    if (temp == NULL)
        return NULL;
    while (temp != NULL) {
        if (temp->i == n) {
            return &temp->str[7];
        }
        temp = temp->next;
    }
    fprintf(stderr, "Elément introuvable\n");
    return NULL;
}

char *return_str_cmd(history_t *h, char *str, int *fd)
{
    int n = my_strlen(str);
    char *last = NULL;
    int l = nbrlen(*fd);
    history_t *temp = h;

    if (temp == NULL)
        return NULL;
    while (temp != NULL) {
        if (temp->str != NULL && my_strncmp(&temp->str[l + 6], str, n) == 0) {
            last = &temp->str[l + 6];
        }
        temp = temp->next;
    }
    if (last != NULL)
        return last;
    if (str != NULL && str[0] != '!')
        fprintf(stderr, "Elément introuvable\n");
    else
        fprintf(stderr, "!: Command not found.\n");
    return NULL;
}
