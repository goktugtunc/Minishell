#include "minishell.h"

void	ft_odd_right_redirection(char *str)
{
	int	fd;
	int	chiled;

	fd = open(str, O_CREAT | O_WRONLY, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		commandfinder();
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void	ft_odd_left_redirection(void)
{
	int	fd;
	int	chiled;

	fd = open(g_data->parts[1].str[0], O_CREAT | O_RDONLY, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(1, fd);
	}
	wait(NULL);
}