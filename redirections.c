#include "minishell.h"

void	ft_odd_right_redirection(char *str, int i, t_data *data)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(str, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		decisionmechanism(&(data->parts[i].str[i]), data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void ft_odd_left_redirection(char *str, int i, t_data *data)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);//// move it to an other place
	fd = open(str, O_RDWR, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 0);
		decisionmechanism(&(data->parts[i].str[i]), data);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_right_redirection(char *str, int i, t_data *data)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		decisionmechanism(&(data->parts[i].str[i]), data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}