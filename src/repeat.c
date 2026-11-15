/*
** EPITECH PROJECT, 2024
** repeat
** File description:
** repeat
*/

#include "../include/my.h"

int is_digit(char *ac)
{
    for (int i = 0; ac[i] != '\0'; i++) {
        if (!((ac[i] >= '0' && ac[i] <= '9') || ac[i] == '+' || ac[i] == '-')){
            fprintf(stderr, "repeat: Badly formed number.\n");
            return 84;
        }
    }
    return 0;
}

int c_digit(char *ac)
{
    for (int i = 1; ac[i] != '\0'; i++) {
        if (!((ac[i] >= '0' && ac[i] <= '9'))) {
            return 1;
        }
    }
    return 0;
}

void repeat_cmd(char **c)
{
    if (count_arr_size(c) < 3)
        fprintf(stderr, "repeat: Too few arguments.\n");
    if (count_arr_size(c) >= 3 && is_digit(c[1]) == 0) {
        for (int i = 0; i < atoi(c[1]); i++)
            main_part2(array_to_str(c, 2));
    }
}
