/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:40:08 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 00:16:14 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ifendispipe(t_data *data)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (data->commandline[i])
		i++;
	while (data->commandline[i - 1] == '|')
	{
		temp = readline("> ");
		if (temp == NULL)
			return (1);
		data->commandline = ft_strjoin(data->commandline, " ");
		data->commandline = ft_strjoin(data->commandline, temp);
		free(temp);
		temp = ft_strtrim(data->commandline, " ");
		free(data->commandline);
		data->commandline = ft_strdup(temp);
		while (data->commandline[i])
			i++;
		if (temp)
			free(temp);
	}
	return (0);
}

int	ifdoubleinput2(t_data *data, int i)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup("");
	temp2 = ft_strdup("");
	while (ft_strcmp(data->arguments[i], temp))
	{
		if (temp)
			free(temp);
		temp = readline("> ");
		if (temp == NULL)
			return (1);
		if (ft_strcmp(data->arguments[i], temp))
		{
			if (temp2[0] != '\0')
				temp2 = ft_strjoin(temp2, "\n");
			temp2 = ft_strjoin(temp2, temp);
		}
	}
	free(data->arguments[i]);
	data->arguments[i] = ft_strdup(temp2);
	return (0);
}

int	ifdoubleinput(t_data *data)
{
	int		i;

	i = 0;
	while (data->arguments[i])
	{
		if (!ft_strcmp(data->arguments[i], "<<") && data->arguments[i + 1])
		{
			i++;
			if (ifdoubleinput2(data, i))
				return (1);
		}
		i++;
	}
	return (0);
}
