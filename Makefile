##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## my_makefile
##


SRC	=	src/mini_printf.c	\
		src/putnbr.c	\
		src/my_putstr.c	\
		src/nbrlen.c	\
		src/my_strcmp.c	\
		src/my_strcpy.c \
		src/my_strdup.c	\
		src/my_strlen.c	\
		src/my_putchar.c 	\
		src/print_the_prompt.c \
		src/split_string.c \
		src/change_dir.c \
		src/env_functions.c \
		src/str_to_word_array.c \
		src/setenv.c \
		src/unsetenv.c \
		src/execute_the_child.c \
		src/redirections.c \
		src/redirections2.c \
		src/redirect_errcase.c \
		src/split_sep.c \
		src/redirections_execute_combi.c \
		src/split_str1.c \
		src/possible_commands.c \
		src/history.c\
		src/alias.c \
		src/split_strn.c \
		src/place_alias.c \
		src/glob.c \
		src/give_cmd_arr.c \
		src/split_string2.c \
		src/split_str2.c \
		src/set.c \
		src/unset.c \
		src/error_file_for_global.c \
		src/repeat.c \
		src/parenthese.c \
		src/parenthese2.c \
		src/parenthese3.c \
		src/tree.c \
		src/search.c	\
		src/split3.c \
		src/jobs_ctrl.c \
		src/magic_quote.c \
		src/line_edit.c \
		src/place_allias2.c \
		src/wh.c \
		main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

UNIT_TEST = unit_test

all:	$(NAME)

$(NAME):
	gcc  -g3 -lm $(SRC) -o $(NAME)

clean :
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *~
	rm -f *.vgcore
	rm -f $(UNIT_TEST)
	rm -f *vgcore.*
	find "." -type f -name '*~' -exec rm -f {} \;

fclean: clean
	rm -f coding-style-reports.log
	rm -f $(NAME)

re:	fclean all

code: fclean
	clear
	coding-style . .
	cat coding-style-reports.log
	rm -rf coding-style-reports.log

unit_tests:	fclean
	gcc -o $(UNIT_TEST) \
	src/my_strdup.c src/my_strlen.c \
	src/my_putchar.c \
	src/my_putstr.c tests/unitest.c \
	--coverage -lcriterion -lgcov -lm

tests_run:	unit_tests
		./$(UNIT_TEST)
		gcovr  --exclude tests/ --branches
