/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:07:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 21:23:21 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_pipe(t_parse *part)
{
	int	i;

	i = 0;
	while (ft_strcmp(part[i].type, "pipe") && part[i].type)
	{
		i++;
	}
	i++;
	return (i);
}

int	pass_pipe_red(t_red *part)
{
	int	i;

	i = 0;
	while (ft_strcmp(part[i].type, "pipe") && part[i].type)
	{
		i++;
	}
	i++;
	return (i);
}

void	pipecommand(t_parse *part1, t_parse *part2, int i, t_data *data)
{
	int	fds[2];
	int	chiled;

	pipe(fds);
	data->fderr = dup(1);
	chiled = fork();
	if (chiled == -1)
		exit (1);
	if (chiled == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		ft_output_all(part1, data);
		close(fds[1]);
		exit(0);
	}
	close(fds[1]);
	wait(NULL);
	dup2(fds[0], 0);
	if (i > 1)
		pipecommand(part1 + pass_pipe(part1),
			part2 + pass_pipe(part2), i - 2, data);
	else
		ft_output_all(part2, data);
	close(fds[0]);
}

void	ft_chiledforpipe(t_parse *part1, t_parse *part2, t_data *data)
{
	int		chiled;

	chiled = fork();
	if (chiled == -1)
		exit(1);
	if (chiled == 0)
	{
		pipecommand(part1, part2, data->commandcount - 2, data);
		exit(0);
	}
	wait(NULL);
}
