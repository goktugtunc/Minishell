/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:05:43 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 01:02:22 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_odd_right_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	fd = open(str, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	chiled = fork();
	if (chiled == -1)
		exit(1);
	if (chiled == 0)
	{
		dup2(fd, 1);
		ft_input_all(part, data);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void	ft_odd_left_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	fd = open(str, O_RDWR, 0777);
	chiled = fork();
	if (chiled == -1)
		exit(1);
	if (chiled == 0)
	{
		dup2(fd, 0);
		decisionmechanism(part[0].str, data);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_right_redirection(char *str, t_data *data, t_parse *part)
{
	int	fd;
	int	chiled;

	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	chiled = fork();
	if (chiled == -1)
		exit(1);
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
	int	fds[2];
	int	chiled;

	pipe(fds);
	write(fds[1], str, ft_strlen(str));
	chiled = fork();
	if (chiled == -1)
		exit(1);
	if (chiled == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		decisionmechanism(part[0].str, data);
		close(fds[0]);
		exit(0);
	}
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
}
