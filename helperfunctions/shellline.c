/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:20:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 03:12:33 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpcname(void)
{
	char	*pcname;
	int		fd[2];
	pid_t	id;
	int		bytesread;
	char	**temp;

	temp = ft_split("scutil --get ComputerName", ' ');
	pcname = malloc(256 * sizeof(char));
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil", temp, NULL);
	}
	else
	{
		wait(NULL);
		bytesread = read(fd[0], pcname, sizeof(pcname));
		if (bytesread == -1)
			ft_error("File read error!");
		pcname[bytesread] = '\0';
		freedoublepointer(temp);
	}
	return (pcname);
}

void	findstarttext(char *pcname, t_data *data)
{
	char	**pwd;
	char	*temp;
	int		i;

	i = 0;
	temp = getcwd(NULL, 0);
	pwd = ft_split(temp, '/');
	free(temp);
	data->simplestarttext = ft_strjoin2("Miniroot - ", getenv("LOGNAME"));
	data->simplestarttext = ft_strjoin(data->simplestarttext, "@");
	data->simplestarttext = ft_strjoin(data->simplestarttext, pcname);
	data->starttext = ft_strjoin2(data->simplestarttext, " ");
	temp = getcwd(NULL, 0);
	if (ft_strcmp(temp, getenv("HOME")) == 0)
		data->starttext = ft_strjoin(data->starttext, "~");
	else
		data->starttext = ft_strjoin(data->starttext,
				pwd[commandpointerlen(pwd) - 1]);
	data->starttext = ft_strjoin(data->starttext, " % ");
	while (pwd[i])
		free(pwd[i++]);
	free(pwd[i]);
	free(pwd);
	free(temp);
	free(pcname);
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}
