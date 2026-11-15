/*
** EPITECH PROJECT, 2024
** error
** File description:
** file
*/
#include "../include/my.h"

int error_for_set(char *ac)
{
    int i = 0;

    if (ac == NULL)
        return 0;
    if (!(ac[0] >= 'a' && ac[0] <= 'z') &&
        !(ac[0] >= 'A' && ac[0] <= 'Z') && (ac[0] != '_')) {
        printf("set: Variable name must begin with a letter.\n");
        return 84;
    }
    for (i = 1; ac[i] != '\0'; i++) {
        if (!(ac[i] >= 'a' && ac[i] <= 'z') &&
            !(ac[i] >= 'A' && ac[i] <= 'Z') && (ac[i] != '_') &&
            !(ac[i] >= '0' && ac[i] <= '9')) {
            printf("%s", "set: ");
            printf("Variable name must contain alphanumeric");
            printf(" characters.\n");
            return 84;
        }
    }
    return 0;
}
