NAME = minishell

src = minishellmain.c helperfunctions.c controls.c signals.c parse.c

objs = minishellmain.o

all: $(NAME)

$(NAME):
	make -C ./libft/
	gcc -Wall -Werror -Wextra -lreadline $(src) libft/libft.a -o $(NAME)
clean:
	rm -rf $(objs)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all