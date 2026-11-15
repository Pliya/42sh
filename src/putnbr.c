/*
** EPITECH PROJECT, 2024
** rush2
** File description:
** putnbr
*/
#include <stdio.h>
#include "../include/my.h"

void free_2d_tab(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return;
    while (tab[i] != NULL) {
        free(tab[i]);
        tab[i] = NULL;
        i++;
    }
    free(tab);
}

void free_rstruct(r_dir_t **tab)
{
    int i = 0;

    if (tab == NULL)
        return;
    while (tab[i] != NULL) {
        free(tab[i]);
        tab[i] = NULL;
        i++;
    }
    free(tab);
}

void free_the_shell(sh_t *sh)
{
    free_2d_tab(sh->env);
    free_2d_tab(sh->reader_splited);
    free(sh->reader);
    free(sh->reader_notmod);
    sh->reader = NULL;
    sh->reader_splited = NULL;
    sh->reader_notmod = NULL;
}

void exit_shell(char *str, int status)
{
    if (my_strcmp(str, "exit") == 0) {
        mini_printf("exit\n");
        exit(0);
    }
}

int putnbr(int nbr)
{
    int n = 0;

    if (nbr < 0) {
        my_putchar('-');
        putnbr(- nbr);
    } else if (nbr > 9) {
        putnbr(nbr / 10);
        putnbr(nbr % 10);
    } else {
        my_putchar(nbr + '0');
    }
    n = nbrlen(nbr);
    return n;
}
