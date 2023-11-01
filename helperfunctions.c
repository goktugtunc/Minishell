/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 11:40:12 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getpcname(void)
{
	char	*pcname;
	int		fd[2];
	pid_t	id;
	int		bytesread;

	pcname = malloc(256 * sizeof(char));////////
	pipe(fd);
	id = fork();
	if (id == 0)
	{/////// closing fd;
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil",
			ft_split("scutil --get ComputerName", ' '), NULL);
	}
	else
	{////////closing fd;
		wait(NULL);
		bytesread = read(fd[0], pcname, sizeof(pcname));
		if (bytesread == -1)
			ft_error("File read error!");
		pcname[bytesread] = '\0';
	}
	return (pcname);
}

void	findstarttext(t_lists *data, char *pcname)
{
	data->starttext = ft_strjoin2("\033[32m", getenv("LOGNAME"));
	data->starttext = ft_strjoin(data->starttext, "@");
	data->starttext = ft_strjoin(data->starttext, pcname);
	data->starttext = ft_strjoin(data->starttext, " ~ ");
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
