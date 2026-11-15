/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** header
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <termios.h>
    #include <unistd.h>
    #include <signal.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <stdbool.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <ctype.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <math.h>
    #define MAX_ELEMENTS 100
    #define VER_STRSNULL(s1, s2) ((s1 == NULL || s2 == NULL) ? 1 : 0)
    #define AMBIG_ERR(x, y, z) (x == PIPE && y == REDIR && z >= 3)
    #define G_GLOB(x) (handle_glob(x))
    #define ARR_SIZEI(x) (count_arr_size(x))
    #define CMD_ARRAY(x) (give_cmd_arr(split_string(x)))
    #define IS_OPERT(x, type) (is_operator_type(x) == type)

typedef struct linked_list {
    char *str;
    struct linked_list *next;
} my_env_t;

typedef struct ino {
    char *value;
    char *name;
    struct ino *next;
} lol_t;

typedef struct sh_s {
    char utl_c;
    char *utl_str;
    char old[512];
    char pwd[512];
    char *reader;
    char *reader_notmod;
    char **reader_splited;
    my_env_t *head;
    int status;
    int status1;
    int change_loc;
    int ult_i;
    pid_t pid1;
    size_t utl_si;
    char **env;
    lol_t *alias;
    lol_t *local;
}sh_t;

typedef struct pipe_s {
    char *cmd1[150];
    int **pipe_fd;
    int status1;
    pid_t pid1;
    pid_t pid2;
} pipe_t;

typedef enum {
    NONE,
    PIPE,
    REDIR,
    REDIR1,
    REDIR2,
    REDIR3,
    REDIR4,
    ET,
    OU,
    J_CONTROL,
    PARENTESE1,
    PARENTESE2,
    M_QUOTE
}info_t;

typedef struct b_tree {
    char *value;
    struct b_tree *left;
    struct b_tree *right;
    struct b_tree *parent;
}b_tree_t;

typedef struct history_s {
    char *str;
    int i;
    struct history_s *next;
} history_t;

typedef struct {
    char *right;
    char *left;
    char *oper;
}sp_string_t;

typedef struct r_dir_s {
    info_t entre;
    char *cmd;
    char **args;
    info_t sortie;
    int fd[2];
    int redir_type;
    char *file;
    pid_t pid;
    info_t parenthese_sortie;
    char *parenthese_file;
    b_tree_t *p_tree;
} r_dir_t;

typedef struct job {
    pid_t pid;
    char *command;
    int status;
    struct job *next;
} job_t;

typedef struct integer_s {
    int c;
    int l;
    int len;
    int cursor_pos;
    char *buffer;
    char *pasta;
    char *cas;
} integer_t;

extern job_t *jobs;
extern sh_t shell;
extern char **environ;
extern int fd;
extern history_t *h;
extern char *str_cmd;
extern pid_t fg_pid;
extern int is_background;
extern int dup_history_size;
extern int history_size;
extern integer_t val;
extern const char *built_in[];

void viral(int sig);
void which_fct(void);
void where_fct(void);
void another_char(void);
char **ret_set_env(void);
char **ret_set_var(void);
integer_t init_integers(void);
int main_part2bt(char *str);
char *replace_backticks(char *input);
void fore_g(pid_t pid);
void jobs_fct(job_t *current, int *i);
void fg_cmd(char **c);
void bg_cmd(char **c);
void add_job(pid_t pid, char *s);
void boucle_infini(void);
void parenthese_execution(char *str);
int is_operator_tab(char *str);
char *ending(struct termios *old);
char *b_search_noncommand(b_tree_t *t);
void parenthese_execution(char *str);
void execve_binary_tree(b_tree_t *t);
int special_dup(char *file, int type);
void parenthese_execution(char *str);
void free_tree(b_tree_t *t);
b_tree_t *create_tree(char *str);
sp_string_t string_cast(char *str);
char *my_strstr1(char *str, char const *to_find);
void repeat_cmd(char **c);
int main_part2(char *str);
char *read_file(char *filepath);
int my_set(lol_t *p);
int my_unset(char *p, lol_t **ab);
void local_unset_var(char *str);
int delete(lol_t **data, char *id);
char *array_to_str(char **t, int j);
void local_set_var(char *str);
lol_t *my_s(char *a, char *b, lol_t *p);
int error_for_set(char *ac);
int is_digit(char *ac);
int c_digit(char *ac);
char **split_str2(char *s);
char *str_oper_clean(char *str);
char **split_string2(char *s);
char *change_str1(char *str);
char *remplacer_point_virgule(char *str);
char *remplacer(char *str, char *key, char *value);
char *change_str(char *str);
r_dir_t **create_rstruct_from_args(char *str);
info_t is_operator_type(char *str);
int is_operator(char *str);
char **give_cmd_arr(char **arg);
char *verify_alias_exist(char *cmd);
char **split_str_n(char *s);
char *my_getline(void);
void alias_cmd(char *c);
int exec_combitable(r_dir_t **combi);
char **split_string1(char *s);
int identity_oper(char *str);
r_dir_t **create_r_from_args(char **args, char *str);
void print_arg(char **arg);
void child_stat(int status);
char **split_sep(char *str);
int exec_combi(char *str);
void execve_mquote(char *cmd);
void free_rstruct(r_dir_t **tab);
void free_rstruct(r_dir_t **tab);
int redirect(char **command, char *file, int flag);
my_env_t *search_node(my_env_t *head, char *to_find);
my_env_t *create_env_node(char *str);
int count_char_str(char *str, char c);
void add_env_node(my_env_t **head, my_env_t *node);
void set_env(char **args);
int count_arr_size(char **tab);
int my_strncmp(char const *s1, char const *s2, int n);
char *search_key(char **env, char *to_find);
void list_to_array(my_env_t *hd);
char **my_str_to_word_array(char *s, char c);
void my_strncpy(char *s, char *t, int n);
void print_env(my_env_t *hd);
void free_2d_tab(char **tab);
void env_strdup(my_env_t **head, char **env);
char *my_strdup(char *src);
void free_the_shell(sh_t *sh);
void change_directory(char *path);
void print_the_prompt(char **env);
char *int_to_str(int nb);
void exit_shell(char *str, int status);
int execute(sh_t *sh);
char *my_strcat(char *dest, char const *src);
int mini_printf(const char *format, ...);
char *my_strcpy(char *dest, const char *src);
int my_str_isnum(char const *str);
int str_to_int(char *str);
char *path_cleaner(char *str);
int nbrlen(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
void my_putchar(char c);
int my_strcmp(char const *s1, char const *s2);
int putnbr(int nbr);
int str_to_int(char *str);
char **split_string(char *s);
void my_putstrerr(char *str);
void change_dir(char **tab, char **env);
void unset_env(char *str, my_env_t *hd);
void execute_the_child(char **paths, char **args, char **env, char *nmodified);
char *my_strstr(char *str, char const *to_find);
void change_dir_env(void);
int execute_pipe(char *commands[], char **env);
int possible_cmd(void);
char *reader(void);
char *place_alias(char *s);
char *return_last_cmd(history_t *h);
char **handle_glob(char **args);
char **file_line_number(char *pathname);
char *return_n_cmd(history_t *h, int n);
char *return_str_cmd(history_t *h, char *str, int *fd);
void history(history_t *h);
void history_strdup(history_t **begin, char *command);
int get_nbpath(char *var);
char **tokenize_args(char *input, int func(char *), char const *sep);
int check_binary(char *path, char *str);
void search_path(char *command);
void search_first_path(char *command);
char **split_3(char *s);
void my_strncpy3(char *s, char *t, int n);
char *remplacer_point_virgule2(char *str);
#endif
