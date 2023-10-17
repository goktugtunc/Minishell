/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 09:27:01 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getusernameandpcname(t_lists *data)
{
	int		fd[2];
	pid_t	id;
	int		bytesread;

	data->pcname = malloc(256 * sizeof(char));
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil",
			ft_split("scutil --get ComputerName", ' '), NULL);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		bytesread = read(fd[0], data->pcname, sizeof(data->pcname));
		close(fd[0]);
		if (bytesread == -1)
			ft_error("File read error!");
		data->pcname[bytesread] = '\0';
	}
}

void	findstarttext(t_lists *data)
{
	data->starttext = ft_strjoin2("\033[32m", getenv("LOGNAME"));
	data->starttext = ft_strjoin(data->starttext, "@");
	data->starttext = ft_strjoin(data->starttext, data->pcname);
	data->starttext = ft_strjoin(data->starttext, " : ");
	data->starttext = ft_strjoin(data->starttext, "\033[0m");
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}

int	lettercount(char *text, char letter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (text[i])
	{
		if (text[i] == letter)
			count++;
		i++;
	}
	return (count);
}
