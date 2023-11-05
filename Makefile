NAME = minishell

src = minishellmain.c helperfunctions/helperfunctions.c helperfunctions/helperfunctions2.c controls.c signals.c parse/parse.c parse/parse2.c parse/parsecomplete.c path.c builtinfuncs/cd.c builtinfuncs/pwd.c builtinfuncs/env.c builtinfuncs/export.c helperfunctions/doublepointer.c

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