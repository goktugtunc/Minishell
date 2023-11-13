/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 00:35:43 by gotunc           ###   ########.fr       */
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

void	findstarttext(char *pcname, t_data *data)
{
	char	**pwd;

	pwd = ft_split(getcwd(NULL, 0), '/');
	data->simplestarttext = ft_strjoin2("\033[32m", getenv("LOGNAME"));
	data->simplestarttext = ft_strjoin(data->simplestarttext, "@");
	data->simplestarttext = ft_strjoin(data->simplestarttext, pcname);
	data->starttext = ft_strjoin2(data->simplestarttext, " ");
	if (ft_strcmp(getcwd(NULL, 0), getenv("HOME")) == 0)
		data->starttext = ft_strjoin(data->starttext, "~");
	else
		data->starttext = ft_strjoin(data->starttext, pwd[lastarg(pwd)]);
	data->starttext = ft_strjoin(data->starttext, " % \033[0m");
}

void	quoteerror(t_data *data)
{
	if (check_quote(data->commandline,
			ft_strlen(data->commandline)) != 0)
	{
		printf("\033[31;4m%sQuote Error!\n\033[0m",
			ft_strtrim(data->starttext, "\033[320m"));
		free(data->commandline);
		data->errorstatus = 1;
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
