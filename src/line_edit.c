/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-2-42sh-bill.adjagboni
** File description:
** line_edit.c
*/

#include "../include/my.h"
#include <sys/ioctl.h>

int k;

integer_t init_integers(void)
{
    integer_t val;

    val = (integer_t){0, 0, 0, 0, NULL, NULL, NULL};
    val.buffer = malloc(sizeof(char) * 2048);
    return val;
}

int get_width(void)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

static void suppr_char(void)
{
    if (val.c == 8 || (val.c == 127 && val.cursor_pos > 0)) {
        for (int i = val.cursor_pos - 1; i < val.len - 1; i++)
            val.buffer[i] = val.buffer[i + 1];
        val.len--;
        val.cursor_pos--;
        val.buffer[val.len] = '\0';
        printf("\b \b");
        printf("\033[s");
        printf("\033[K");
        printf("%s", &val.buffer[val.cursor_pos]);
        printf("\033[u");
        fflush(stdout);
    }
}

void delete_char(void)
{
    if (val.cursor_pos == val.len)
        return;
    for (int i = val.cursor_pos; i < val.len - 1; i++)
        val.buffer[i] = val.buffer[i + 1];
    val.len--;
    val.buffer[val.len] = '\0';
    printf("\033[s");
    printf("\033[K");
    printf("%s", &val.buffer[val.cursor_pos]);
    printf("\033[u");
    fflush(stdout);
}

char *give_command(void)
{
    history_t *temp = h;

    if (dup_history_size < 1)
        dup_history_size = 1;
    if (dup_history_size >= history_size) {
        dup_history_size = history_size;
        return "";
    }
    return (return_n_cmd(temp, dup_history_size));
}

static void cursor_move3(void)
{
    char *str = NULL;

    if (val.l == 'D' && val.cursor_pos > 0) {
        printf("\033[D");
        val.cursor_pos--;
    } else if (val.l == 'A')
        dup_history_size--;
    if (val.l == 'B')
        dup_history_size++;
    if (val.l == 'A' || val.l == 'B') {
        str = give_command();
        if (str != NULL)
            val.buffer = my_strdup(str);
        for (; val.cursor_pos > 0; val.cursor_pos--)
            printf("\033[D");
        printf("\033[K");
        val.len = strlen(val.buffer);
        printf("%s", val.buffer);
    }
}

static void cursor_move4(void)
{
    if (val.c == 11) {
        val.pasta = strdup(&val.buffer[val.cursor_pos]);
        printf("\033[K");
        val.buffer[val.cursor_pos] = '\0';
        val.len = val.cursor_pos;
    } else if (val.c == 14) {
        val.l = 'B';
        cursor_move3();
        val.cursor_pos = val.len;
    }
    if (val.c == 25 && val.pasta != NULL) {
        for (int i = 0; i < strlen(val.pasta); i++) {
            val.c = val.pasta[i];
            another_char();
        }
    val.c = 20;
    } else if (val.c == 16) {
        val.l = 'A';
        cursor_move3();
        val.cursor_pos = val.len;
    }
}

static void cursor_move2(void)
{
    if (val.c == 1)
        for (; val.cursor_pos > 0; val.cursor_pos--)
            printf("\033[D");
    if (val.c == 2)
        if (val.cursor_pos > 0) {
            printf("\033[D");
            val.cursor_pos--;
        }
    if (val.c == 3)
        val.buffer[0] = '\0';
    if (val.c == 5)
        for (; val.cursor_pos < val.len; val.cursor_pos++)
            printf("\033[C");
    if (val.c == 6)
        if (val.cursor_pos < val.len) {
            printf("\033[C");
            (val.cursor_pos)++;
        }
    cursor_move4();
}

static void cursor_move(void)
{
    if (val.c != 27)
        return cursor_move2();
    getchar();
    val.l = getchar();
    if (val.l == 'H')
        for (; val.cursor_pos > 0; val.cursor_pos--)
            printf("\033[D");
    if (val.l == 'F')
        for (; val.cursor_pos < val.len; val.cursor_pos++)
            printf("\033[C");
    if (val.l == 'C')
        if (val.cursor_pos < val.len) {
            printf("\033[C");
            (val.cursor_pos)++;
        }
    if (val.l == '3' && getchar() == '~')
        delete_char();
    cursor_move3();
    if (val.l == 'A' || val.l == 'B')
        val.cursor_pos = val.len;
}

void another_char(void)
{
    int width;
    int line_len;
    int curs;

    if (val.cursor_pos < val.len)
        for (int i = val.len; i > val.cursor_pos; i--)
            val.buffer[i] = val.buffer[i - 1];
    val.buffer[val.cursor_pos] = val.c;
    val.cursor_pos++;
    val.len++;
    val.buffer[val.len] = '\0';
    width = get_width();
    curs = val.cursor_pos + 27;
    line_len = curs % width;
    if (line_len == 0)
        printf("\n");
    printf("\033[s");
    printf("%s", &val.buffer[val.cursor_pos - 1]);
    printf("\033[u");
    printf("\033[C");
}

char *my_getline(void)
{
    struct termios old;
    struct termios new;

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
    val.c = getchar();
    for (; val.c != '\n'; val.c = getchar()) {
        suppr_char();
        cursor_move();
        if (val.c == 4)
            return ending(&old);
        if (val.c != 127 && val.c > 31)
            another_char();
        fflush(stdout);
    }
    val.buffer[val.len] = '\0';
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
    return val.buffer;
}
