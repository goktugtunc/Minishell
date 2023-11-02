/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/02 14:29:10 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpcname(void)
{
	char	*pcname;
	int		fd[2];
	pid_t	id;
	int		bytesread;

	pcname = malloc(256 * sizeof(char));
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

void	findstarttext(char *pcname)
{
	g_data->starttext = ft_strjoin2("\033[32m", getenv("LOGNAME"));
	g_data->starttext = ft_strjoin(g_data->starttext, "@");
	g_data->starttext = ft_strjoin(g_data->starttext, pcname);
	g_data->starttext = ft_strjoin(g_data->starttext, " ~ ");
	g_data->starttext = ft_strjoin(g_data->starttext, "\033[0m");
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}
