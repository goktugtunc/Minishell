NAME = minishell

src = minishellmain.c helperfunctions/helperfunctions.c helperfunctions/helperfunctions2.c controls.c signals.c parse/parse.c parse/parse2.c parse/parsecomplete.c path.c builtinfuncs/cd.c builtinfuncs/pwd.c builtinfuncs/env.c builtinfuncs/export.c

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

all: $(READLINE) $(NAME)

$(NAME): $(src)
	@make -C ./libft/
	@gcc -Wall -Werror -Wextra -lreadline $(src) libft/libft.a -L${PWD}/readline/lib  -I${PWD}/readline/include/ -o $(NAME)

clean:
	@make clean -C ./libft/

fclean: clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

re: fclean all


# CC = @gcc
# NAME = minishell
# CFLAGS = -g -Wall -Wextra -Werror
# RM = @rm -rf

# OBJS = minishellmain.o helperfunctions/helperfunctions.o helperfunctions/helperfunctions2.o controls.o signals.o parse/parse.o parse/parse2.o parse/parsecomplete.o path.o builtinfuncs/cd.o builtinfuncs/pwd.o builtinfuncs/env.o builtinfuncs/export.o


# READLINE = readline

# all: $(READLINE) $(NAME)

# $(READLINE):
# 	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
# 	tar -xvf readline-8.2.tar.gz
# 	cd readline-8.2 && ./configure --prefix=${PWD}/readline
# 	cd readline-8.2 && make install


# $(NAME): $(OBJS)
# 	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline libft/libft.a

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

# fclean: clean
# 	$(RM) $(NAME)
# 	@make fclean -C ./libft/
# 	rm -rf readline-8.2 readline-8.2.tar.gz

# clean:
# 	@make clean -C ./libft/
# 	$(RM) $(OBJS)

# re: fclean all

# .PHONY: all fclean clean re
