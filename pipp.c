/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:07:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/12 21:16:34 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_pipe(t_parse *part)
{
	int	i;

	i = 0;
	while (ft_strcmp(part[i].type , "pipe") && part[i].type)
	{
		i++;
	}
	i++;
	return (i);
}

void	pipecommand(t_parse *part1, t_parse *part2, int i)
{
	int	fds[2];
	int	chiled;

	pipe(fds);
	chiled = fork();
	if (chiled == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		commandfinderother(part1);
		close(fds[1]);
		exit(0);
	}
	close(fds[1]);
	wait(NULL);
	dup2(fds[0], 0);
	if (i > 1)
		pipecommand(part1 + pass_pipe(part1), part2 + pass_pipe(part2), i - 2);
	else
		commandfinderother(part2);
	close(fds[0]);
}

void	ft_chiledforpipe(t_parse *part1, t_parse *part2)
{
	int		chiled;

	chiled = fork();
	if (chiled == 0)
	{
		pipecommand(part1, part2, g_data->commandcount - 2);
		exit(0);
	}
	wait(NULL);
}
