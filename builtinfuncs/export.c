/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/07 01:58:22 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isthere(char *str)
{
	int	i;

	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strcmp(ft_split(g_data->envp[i], '=')[0], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	sortexport(void)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (g_data->exportp[i])
	{
		j = 0;
		while (g_data->exportp[j])
		{
			if (ft_strcmp(g_data->exportp[i], g_data->exportp[j]) < 0)
			{
				temp = g_data->exportp[i];
				g_data->exportp[i] = g_data->exportp[j];
				g_data->exportp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	isupdate2(char *str, int i)
{
	while (--i != -1)
	{
		if (ft_strchr(g_data->exportp[i], '='))
		{
			if (ft_strcmp(ft_split(str, '=')[0],
				ft_split(g_data->exportp[i], '=')[0]) == 0)
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
		}
		else
			if (ft_strcmp(ft_split(str, '=')[0], g_data->exportp[i]) == 0)
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
	}
}

void	isupdate(char *str, int i)
{
	if (!ft_strchr(str, '='))
	{
		while (--i != -1)
		{
			if (ft_strcmp(g_data->exportp[i], str) == 0)
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
		}
		return ;
	}
	isupdate2(str, commandpointerlen(g_data->exportp));
	i = commandpointerlen(g_data->envp);
	while (--i != -1)
	{
		if (ft_strcmp(ft_split(str, '=')[0],
			ft_split(g_data->envp[i], '=')[0]) == 0)
			g_data->envp = removedoublepointerarg(g_data->envp, i);
	}
}

void	exportcommand(char **str, int i, int error)
{
	if (str[1])
	{
		while (str[++i])
		{
			if (exportparser(str[i]))
			{
				if (!isthere(str[i]))
				{
					isupdate(str[i], commandpointerlen(g_data->exportp));
					if (ft_strchr(str[i], '='))
						g_data->envp = adddoublepointer(g_data->envp, str[i]);
					g_data->exportp = adddoublepointer(g_data->exportp, str[i]);
				}
			}
			else
				if (error == 0 && ++error == 1)
					printf("export: not valid in this context: %s\n", str[i]);
		}
	}
	sortexport();
	i = -1;
	if (error == 0 && !str[1])
		while (g_data->exportp[++i])
			printf("declare -x %s\n", g_data->exportp[i]);
}
