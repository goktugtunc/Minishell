/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:38:50 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 12:22:17 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parserlongcontroller(t_lists *data, int i)
{
	return (data->commandline[i] && data->commandline[i] != ' '
		&& data->commandline[i] != '<' && data->commandline[i] != '>'
		&& data->commandline[i] != '|');
}

int	pipecontrol(t_lists *data, char *a, int i)
{
	a[0] = data->commandline[i];
	a[1] = '\0';
	return (++i);
}

int	ifmultiquote(t_lists *data, char *a, int i, int *j)
{
	while (parserlongcontroller(data, i))
	{
		if (data->commandline[i] == '\"')
		{
			a[(*j)++] = data->commandline[i++];
			while (data->commandline[i] != '\"' && data->commandline[i])
				a[(*j)++] = data->commandline[i++];
			a[(*j)++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<'
			|| data->commandline[i] == '>' || !data->commandline[i]
			|| data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(data, i) && data->commandline[i] != '\"')
		{
			if (data->commandline[i] == '\'')
				i = ifsinglequote(data, a, i, j);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}

int	ifsinglequote(t_lists *data, char *a, int i, int *j)
{
	while (parserlongcontroller(data, i))
	{
		if (data->commandline[i] == '\'')
		{
			a[(*j)++] = data->commandline[i++];
			while (data->commandline[i] != '\'' && data->commandline[i])
				a[(*j)++] = data->commandline[i++];
			a[(*j)++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<'
			|| data->commandline[i] == '>' || !data->commandline[i]
			|| data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(data, i) && data->commandline[i] != '\'')
		{
			if (data->commandline[i] == '\"')
				i = ifmultiquote(data, a, i, j);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}
