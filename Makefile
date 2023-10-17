NAME = minishell

src = minishellmain.c helperfunctions.c controls.c signals.c

objs = minishellmain.o

all: $(NAME)

$(NAME):
	make -C ./libft/
	gcc -Wall -Werror -Wextra -lreadline $(src) libft/libft.a -o $(NAME)
clean:
	rm -rf $(objs)

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all