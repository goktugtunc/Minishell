SRCS = minishellmain.c helperfunctions/helperfunctions.c helperfunctions/helperfunctions2.c controls.c signals.c parse/parse.c parse/parse2.c parse/parsecomplete.c path.c builtinfuncs/cd.c builtinfuncs/pwd.c builtinfuncs/env.c builtinfuncs/export.c helperfunctions/doublepointer.c pipp.c execv.c

CC = @gcc
NAME = minishell
CFLAGS = -g -Wall -Wextra -Werror
RM = @rm -rf

OBJS = $(SRCS:.c=.o)

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install


$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

fclean: clean
	$(RM) $(NAME)
	rm -rf readline-8.2 readline-8.2.tar.gz

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all fclean clean re
