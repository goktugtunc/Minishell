/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:38:50 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 01:02:54 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parserlongcontroller(int i, t_data *data)
{
	return (data->commandline[i] && data->commandline[i] != ' '
		&& data->commandline[i] != '<' && data->commandline[i] != '>'
		&& data->commandline[i] != '|');
}

int	pipecontrol(char *a, int i, t_data *data)
{
	a[0] = data->commandline[i];
	a[1] = '\0';
	return (++i);
}

int	ifmultiquote(char *a, int i, int *j, t_data *data)
{
	while (parserlongcontroller(i, data))
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
		while (parserlongcontroller(i, data) && data->commandline[i] != '\"')
		{
			if (data->commandline[i] == '\'')
				i = ifsinglequote(a, i, j, data);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}

int	ifsinglequote(char *a, int i, int *j, t_data *data)
{
	while (parserlongcontroller(i, data))
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
		while (parserlongcontroller(i, data) && data->commandline[i] != '\'')
		{
			if (data->commandline[i] == '\"')
				i = ifmultiquote(a, i, j, data);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}
