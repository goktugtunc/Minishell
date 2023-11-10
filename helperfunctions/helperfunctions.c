/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/08 21:41:34 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lastarg(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i - 1);
}

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
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil",
			ft_split("scutil --get ComputerName", ' '), NULL);
	}
	else
	{
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
	char	**pwd;

	pwd = ft_split(getcwd(NULL, 0), '/');
	g_data->simplestarttext = ft_strjoin2("\033[32m", getenv("LOGNAME"));
	g_data->simplestarttext = ft_strjoin(g_data->simplestarttext, "@");
	g_data->simplestarttext = ft_strjoin(g_data->simplestarttext, pcname);
	g_data->starttext = ft_strjoin2(g_data->simplestarttext, " ");
	if (ft_strcmp(getcwd(NULL, 0), getenv("HOME")) == 0)
		g_data->starttext = ft_strjoin(g_data->starttext, "~");
	else
		g_data->starttext = ft_strjoin(g_data->starttext, pwd[lastarg(pwd)]);
	g_data->starttext = ft_strjoin(g_data->starttext, " % \033[0m");
}

void	quoteerror(void)
{
	if (check_quote(g_data->commandline,
			ft_strlen(g_data->commandline)) != 0)
	{
		printf("\033[31;4m%sQuote Error!\n\033[0m",
			ft_strtrim(g_data->starttext, "\033[320m"));
		free(g_data->commandline);
		g_data->errorstatus = 1;
	}
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}
