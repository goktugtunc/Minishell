SRCS = minishellmain.c helperfunctions/helperfunctions.c helperfunctions/helperfunctions2.c controls.c signals.c parse/parse.c parse/parse2.c parse/parsecomplete.c path.c builtinfuncs/cd.c\
		builtinfuncs/pwd.c builtinfuncs/env.c builtinfuncs/export.c helperfunctions/doublepointer.c pipp.c execv.c builtinfuncs/unset.c builtinfuncs/exit.c inputandoutput/inputandoutput.c\
		dollar/dollar.c redirections.c helperfunctions/helperfunctions3.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME):
	$(CC) -o $(NAME) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline libft/libft.a $(SRCS)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) readline-8.2 readline-8.2.tar.gz

re: fclean all
