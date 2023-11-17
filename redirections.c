#include "minishell.h"

void	ft_odd_right_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(str, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		ft_input_all(part, data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void ft_odd_left_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);//// move it to an other place
	fd = open(str, O_RDWR, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 0);
		commandfinderother(part, data);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_right_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 1);
		ft_input_all(part, data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_left_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	data->fderr = dup(1);
	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	chiled = fork();
	if (chiled == 0)
	{
		dup2(fd, 0);
		commandfinderother(part, data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}