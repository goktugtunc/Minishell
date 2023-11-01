/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 10:20:37 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lessorgreatersign(t_lists *data, char *a, int i, int m)
{
	a[1] = '\0';
	a[2] = '\0';
	if (data->commandline[i] == '<')
	{
		if (data->commandline[i + 1] == '<')
		{
			a[0] = '<';
			a[1] = '<';
			m = 2;
		}
		else
			a[0] = '<';
	}
	else
	{
		if (data->commandline[i + 1] == '>')
		{
			a[0] = '>';
			a[1] = '>';
			m = 2;
		}
		else
			a[0] = '>';
	}
	return (i + m);
}

int	elsestatus(t_lists *data, char *a, int i)
{
	int		j;

	j = 0;
	while (data->commandline[i] && ((data->commandline[i] != ' '
				&& data->commandline[i] != '<' && data->commandline[i] != '>'
				&& check_quote(data->commandline, i) == 0)
			|| (check_quote(data->commandline, i) != 0)))
	{
		a[j++] = data->commandline[i++];
	}
	a[j] = '\0';
	return (i);
}

int	parserv2(t_lists *data, char *a, int i, int argi)
{
	int	j;

	j = 0;
	if (data->commandline[i] == '\"')
		i = ifmultiquote(data, a, i, &j);
	else if (data->commandline[i] == '\'')
		i = ifsinglequote(data, a, i, &j);
	else if (data->commandline[i] == '<' || data->commandline[i] == '>')
		i = lessorgreatersign(data, a, i, 1);
	else
		i = elsestatus(data, a, i);
	data->arguments[argi] = ft_strdup(a);
	return (i);
}

void	parser(t_lists *data)
{
	int		i;
	int		argi;
	char	*a;

	i = 0;
	argi = 0;
	data->commandline = ft_strtrim(data->commandline, " ");
	data->arguments = malloc(ft_strlen(data->commandline) * sizeof(char *) + 1);
	a = malloc(ft_strlen(data->commandline) + 1);
	while (data->commandline[i])
	{
		if (data->commandline[i] == ' ')
			i++;
		else
			i = parserv2(data, a, i, argi++);
	}
	data->arguments[argi] = NULL;
}
