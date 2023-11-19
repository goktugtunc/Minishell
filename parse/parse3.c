/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:40:08 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 18:17:47 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ifendispipe2(t_data *data, int i, char *temp)
{
	while (data->commandline[i])
		i++;
	while (data->commandline[i - 1] == '|')
	{
		g_global.heredoc = 1;
		temp = readline("> ");
		if (temp == NULL && g_global.error == 0)
			return (1);
		if (g_global.error == 1)
		{
			free(temp);
			return (0);
		}
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

int	ifendispipe(t_data *data, int i)
{
	while (data->commandline[i])
		i++;
	if (data->commandline[--i] == '|')
	{
		while (--i != -1)
		{
			if (data->commandline[i] == '<' || data->commandline[i] == '|'
				|| data->commandline[i] == '>')
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				data->exitstatus = 258;
				return (1);
			}
			else if (data->commandline[i] != ' ')
				break ;
		}
		if (ifendispipe2(data, 0, NULL))
		{
			g_global.heredoc = 0;
			return (1);
		}
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
		{
			free(temp2);
			return (1);
		}
		if (g_global.error == 1)
		{
			free(temp);
			free(temp2);
			return (0);
		}
		if (ft_strcmp(data->arguments[i], temp))
		{
			temp2 = ft_strjoin(temp2, temp);
			temp2 = ft_strjoin(temp2, "\n");
		}
	}
	free(data->arguments[i]);
	data->arguments[i] = ft_strdup(temp2);
	free(temp);
	free(temp2);
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
			g_global.heredoc = 1;
			i++;
			if (ifdoubleinput2(data, i))
				return (1);
			if (g_global.error == 1)
				return (0);
		}
		i++;
	}
	return (0);
}
