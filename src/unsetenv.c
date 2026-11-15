/*
** EPITECH PROJECT, 2024
** unsetenv
** File description:
** variable in the env
*/

#include "../include/my.h"

void unset_env(char *str, my_env_t *hd)
{
    my_env_t *sv = hd;
    my_env_t *save = NULL;

    if (my_strncmp(hd->str, str, my_strlen(str)) == 0) {
        save = shell.head;
        shell.head = shell.head->next;
        free(save);
        return;
    }
    while (hd != NULL) {
        if (my_strncmp(hd->str, str, my_strlen(str)) == 0) {
            save = hd;
            sv->next = hd->next;
            free(save);
            return;
        }
        sv = hd;
        hd = hd->next;
    }
}
