/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:10:23 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 01:26:26 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequotes2(char *str)
{
	int		i;
	int		status;
	char	*returnvalue;
	int		j;

	returnvalue = malloc(ft_strlen(str) + 1);
	status = 0;
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && status == 1)
			status = 0;
		else if (str[i] == '\"' && status == 0)
			status = 1;
		else if (str[i] == '\'' && status == 2)
			status = 0;
		else if (str[i] == '\'' && status == 0)
			status = 2;
		else
			returnvalue[j++] = str[i];
	}
	returnvalue[j] = 0;
	return (returnvalue);
}

void	removequotes(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	char	**returnvalue;

	i = 0;
	j = 0;
	returnvalue = malloc(sizeof(char *)
			* (commandpointerlen(data->arguments) + 1));
	while (data->arguments[i])
	{
		temp = data->arguments[i];
		returnvalue[i] = removequotes2(temp);
		free(temp);
		i++;
	}
	free(data->arguments[i]);
	free(data->arguments);
	returnvalue[i] = NULL;
	data->arguments = returnvalue;
}

int	echonflagcontroller(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	freedoublepointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	preparewhile(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->parsererrorcode = 0;
	g_global.error = 0;
	g_global.execstatus = 0;
	if (data->commandline && data->commandline[0] && data->errorstatus == 0)
	{
		free(data->commandline);
		if (data->arguments)
			freedoublepointer(data->arguments);
		i = 0;
		if (data->parts)
		{
			while (data->parts[i].type != NULL)
			{
				while (data->parts[i].str[j])
					free(data->parts[i].str[j++]);
				free(data->parts[i].str[j]);
				free(data->parts[i].type);
				i++;
				j = 0;
			}
			free(data->parts->str);
			free(data->parts);
		}
	}
	data->errorstatus = 0;
}
