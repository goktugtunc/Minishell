/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:07:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/10 01:27:11 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipecommand(char **s1, char **s2, int i)
{
	int	fds[2];
	int	chiled;

	pipe(fds);
	chiled = fork();
	if (chiled == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		decisionmechanism(s1);
		close(fds[1]);
		exit(0);
	}
	close(fds[1]);
	wait(NULL);
	dup2(fds[0], 0);
	if (i > 1)
	{
		g_data->j += 2;
		pipecommand(g_data->parts[g_data->j].str,
			g_data->parts[g_data->j + 2].str, i - 2);
	}
	else
		decisionmechanism(s2);
	close(fds[0]);
	return (g_data->j);
}

int	ft_chiledforpipe(char **str1, char **str2)
{
	int		chiled;
	char	*temp;
	int		fds[2];

	g_data->j = 0;
	pipe(fds);
	chiled = fork();
	if (chiled == 0)
	{
		close(fds[0]);
		g_data->j = pipecommand(str1, str2, g_data->commandcount - 2);
		temp = ft_itoa(g_data->j);
		write(fds[1], temp, ft_strlen(temp));
		close(fds[1]);
		free(temp);
		exit(0);
	}
	wait(NULL);
	temp = malloc(10);
	read(fds[0], temp, 999);
	g_data->j = ft_atoi(temp);
	close(fds[0]);
	close(fds[1]);
	free(temp);
	return (g_data->j);
}
