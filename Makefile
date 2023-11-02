NAME = minishell

src = minishellmain.c helperfunctions.c helperfunctions2.c controls.c signals.c parse.c parse2.c parsecomplete.c path.c

objs = minishellmain.o

all: $(NAME)

$(NAME): $(src)
	@make -C ./libft/
	@gcc -Wall -Werror -Wextra -lreadline $(src) libft/libft.a -o $(NAME)

clean:
	@make clean -C ./libft/

fclean: clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

re: fclean all