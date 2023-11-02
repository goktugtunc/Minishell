/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/02 14:29:43 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lessorgreatersign(char *a, int i, int m)
{
	a[1] = '\0';
	a[2] = '\0';
	if (g_data->commandline[i] == '<')
	{
		if (g_data->commandline[i + 1] == '<')
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
		if (g_data->commandline[i + 1] == '>')
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

int	elsestatus(char *a, int i)
{
	int		j;

	j = 0;
	while (g_data->commandline[i] && ((g_data->commandline[i] != ' '
				&& g_data->commandline[i] != '<'
				&& g_data->commandline[i] != '>'
				&& g_data->commandline[i] != '|'
				&& check_quote(g_data->commandline, i) == 0)
			|| (check_quote(g_data->commandline, i) != 0)))
	{
		a[j++] = g_data->commandline[i++];
	}
	a[j] = '\0';
	return (i);
}

int	parserv2(char *a, int i, int argi)
{
	int	j;

	j = 0;
	if (g_data->commandline[i] == '\"')
		i = ifmultiquote(a, i, &j);
	else if (g_data->commandline[i] == '\'')
		i = ifsinglequote(a, i, &j);
	else if (g_data->commandline[i] == '<' || g_data->commandline[i] == '>')
		i = lessorgreatersign(a, i, 1);
	else if (g_data->commandline[i] == '|')
		i = pipecontrol(a, i);
	else
		i = elsestatus(a, i);
	g_data->arguments[argi] = ft_strdup(a);
	free(a);
	return (i);
}

void	parser(void)
{
	int		i;
	int		argi;
	char	*a;

	i = 0;
	argi = 0;
	g_data->commandline = ft_strtrim2(g_data->commandline, " ");
	g_data->arguments = malloc(
			ft_strlen(g_data->commandline) * sizeof(char *) + 1);
	while (g_data->commandline[i])
	{
		a = malloc(ft_strlen(g_data->commandline) + 1);
		if (g_data->commandline[i] == ' ')
			i++;
		else
			i = parserv2(a, i, argi++);
	}
	g_data->arguments[argi] = NULL;
}
