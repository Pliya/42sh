/*
** EPITECH PROJECT, 2024
** display_map.c
** File description:
** Display my map
*/
#include "../include/my.h"

char *int_to_str(int nb)
{
    char *str = malloc(sizeof(char) * (nbrlen(nb) + 1));
    int i = nbrlen(nb);
    int nbr = nbrlen(nb);
    int ver = 0;

    do {
        i--;
        if (i < 0)
            break;
        str[i] = (nb % 10) + 48;
        if (nb < 10){
            ver++;
        }
        if (ver > 1)
            break;
        nb = nb / 10;
    } while (ver < 2);
    str[nbr] = '\0';
    return str;
}
