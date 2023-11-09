/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:38:50 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/02 14:29:50 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parserlongcontroller(int i)
{
	return (g_data->commandline[i] && g_data->commandline[i] != ' '
		&& g_data->commandline[i] != '<' && g_data->commandline[i] != '>'
		&& g_data->commandline[i] != '|');
}

int	pipecontrol(char *a, int i)
{
	a[0] = g_data->commandline[i];
	a[1] = '\0';
	return (++i);
}

int	ifmultiquote(char *a, int i, int *j)
{
	while (parserlongcontroller(i))
	{
		if (g_data->commandline[i] == '\"')
		{
			a[(*j)++] = g_data->commandline[i++];
			while (g_data->commandline[i] != '\"' && g_data->commandline[i])
				a[(*j)++] = g_data->commandline[i++];
			a[(*j)++] = g_data->commandline[i++];
		}
		if (g_data->commandline[i] == ' ' || g_data->commandline[i] == '<'
			|| g_data->commandline[i] == '>' || !g_data->commandline[i]
			|| g_data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(i) && g_data->commandline[i] != '\"')
		{
			if (g_data->commandline[i] == '\'')
				i = ifsinglequote(a, i, j);
			else
				a[(*j)++] = g_data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}

int	ifsinglequote(char *a, int i, int *j)
{
	while (parserlongcontroller(i))
	{
		if (g_data->commandline[i] == '\'')
		{
			a[(*j)++] = g_data->commandline[i++];
			while (g_data->commandline[i] != '\'' && g_data->commandline[i])
				a[(*j)++] = g_data->commandline[i++];
			a[(*j)++] = g_data->commandline[i++];
		}
		if (g_data->commandline[i] == ' ' || g_data->commandline[i] == '<'
			|| g_data->commandline[i] == '>' || !g_data->commandline[i]
			|| g_data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(i) && g_data->commandline[i] != '\'')
		{
			if (g_data->commandline[i] == '\"')
				i = ifmultiquote(a, i, j);
			else
				a[(*j)++] = g_data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}
