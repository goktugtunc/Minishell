#include "minishell.h"

void	ft_odd_right_redirection(t_parse *part, int i, t_data *data)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(part->str[1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		if (i == 0)
			decisionmechanism(&((part - 1)->str[0]), data);
		else
			decisionmechanism(&((part + i)->str[0]), data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void ft_odd_left_redirection(t_parse *part, int i, t_data *data)
{
	int	fd;
	int chiled;

	data->fderr = dup(1);//// move it to an other place
	fd = open(part->str[1], O_RDWR, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 0);
		if (i == 0)
			decisionmechanism(&((part - 1)->str[0]), data);
		else
			decisionmechanism(&((part + 1)->str[0]), data);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_right_redirection(t_parse *part, int i, t_data *data)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(part->str[1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		if (i == 0)
		{
			decisionmechanism(&((part - 1)->str[0]), data);
		}
		else
			decisionmechanism(&((part + 1)->str[0]), data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}