/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 01:20:51 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isthere(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strcmp(ft_split(data->envp[i], '=')[0], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	sortexport(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (data->exportp[i])
	{
		j = 0;
		while (data->exportp[j])
		{
			if (ft_strcmp(data->exportp[i], data->exportp[j]) < 0)
			{
				temp = data->exportp[i];
				data->exportp[i] = data->exportp[j];
				data->exportp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	isupdate2(char *str, int i, t_data *data)
{
	while (--i != -1)
	{
		if (ft_strchr(data->exportp[i], '='))
		{
			if (ft_strcmp(ft_split(str, '=')[0],
				ft_split(data->exportp[i], '=')[0]) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
		}
		else
			if (ft_strcmp(ft_split(str, '=')[0], data->exportp[i]) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
	}
}

void	isupdate(char *str, int i, t_data *data)
{
	if (!ft_strchr(str, '='))
	{
		while (--i != -1)
		{
			if (ft_strcmp(data->exportp[i], str) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
		}
		return ;
	}
	isupdate2(str, commandpointerlen(data->exportp), data);
	i = commandpointerlen(data->envp);
	while (--i != -1)
	{
		if (ft_strcmp(ft_split(str, '=')[0],
			ft_split(data->envp[i], '=')[0]) == 0)
			data->envp = removedoublepointerarg(data->envp, i);
	}
}

void	exportcommand(char **str, int i, int error, t_data *data)
{
	if (str[1])
	{
		while (str[++i])
		{
			if (exportparser(str[i]))
			{
				if (!isthere(str[i], data))
				{
					isupdate(str[i], commandpointerlen(data->exportp), data);
					if (ft_strchr(str[i], '='))
						data->envp = adddoublepointer(data->envp, str[i]);
					data->exportp = adddoublepointer(data->exportp, str[i]);
				}
			}
			else
				if (error == 0 && ++error == 1)
					printf("export: not valid in this context: %s\n", str[i]);
		}
	}
	sortexport(data);
	i = -1;
	if (error == 0 && !str[1])
		while (data->exportp[++i])
			printf("declare -x %s\n", data->exportp[i]);
}
