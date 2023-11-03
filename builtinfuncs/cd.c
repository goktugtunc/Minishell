/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:20:24 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/03 23:27:19 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	makepwd(char *oldpwd, char *newpwd)
{
	int		oldpwdindex;
	int		pwdindex;
	char	**newstarttext;

	oldpwdindex = findenvpindex("OLDPWD=", 7);
	pwdindex = findenvpindex("PWD=", 4);
	free(g_data->envp[oldpwdindex]);
	free(g_data->envp[pwdindex]);
	g_data->envp[oldpwdindex] = ft_strjoin2("OLDPWD=", oldpwd);
	g_data->envp[pwdindex] = ft_strjoin2("PWD=", newpwd);
	free(g_data->starttext);
	if (ft_strcmp(getcwd(NULL, 0), getenv("HOME")) == 0)
	{
		g_data->starttext = ft_strjoin2(g_data->simplestarttext, " ~ \033[0m");
	}
	else
	{
		newstarttext = ft_split(g_data->envp[pwdindex], '/');
		g_data->starttext = ft_strjoin2(g_data->simplestarttext, " ");
		g_data->starttext = ft_strjoin(g_data->starttext, newstarttext[lastarg(newstarttext)]);
		g_data->starttext = ft_strjoin(g_data->starttext, " % \033[0m");
	}
}

void	cdcommand(char **a)
{
	int		i;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	i = commandpointerlen(a);
	if (i == 1 || (i == 2 && ft_strcmp(a[1], "~") == 0))
	{
		chdir(getenv("HOME"));
		makepwd(pwd, getcwd(NULL, 0));
	}
	else
	{
		if (chdir(a[1]))
		{
			perror(a[1]);
		}
		else
			makepwd(pwd, getcwd(NULL, 0));
	}
}
