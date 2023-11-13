/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 00:58:27 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lessorgreatersign(char *a, int i, int m, t_data *data)
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

int	elsestatus(char *a, int i, t_data *data)
{
	int		j;

	j = 0;
	while (data->commandline[i] && ((data->commandline[i] != ' '
				&& data->commandline[i] != '<'
				&& data->commandline[i] != '>'
				&& data->commandline[i] != '|'
				&& check_quote(data->commandline, i) == 0)
			|| (check_quote(data->commandline, i) != 0)))
	{
		a[j++] = data->commandline[i++];
	}
	a[j] = '\0';
	return (i);
}

int	parserv2(char *a, int i, int argi, t_data *data)
{
	int	j;

	j = 0;
	if (data->commandline[i] == '\"')
		i = ifmultiquote(a, i, &j, data);
	else if (data->commandline[i] == '\'')
		i = ifsinglequote(a, i, &j, data);
	else if (data->commandline[i] == '<' || data->commandline[i] == '>')
		i = lessorgreatersign(a, i, 1, data);
	else if (data->commandline[i] == '|')
		i = pipecontrol(a, i, data);
	else
		i = elsestatus(a, i, data);
	data->arguments[argi] = ft_strdup(a);
	free(a);
	return (i);
}

void	parser(t_data *data)
{
	int		i;
	int		argi;
	char	*a;
	char	*temp;

	temp = ft_strdup(data->commandline);
	i = 0;
	argi = 0;
	free(data->commandline);
	data->commandline = ft_strtrim(temp, " ");
	data->arguments = malloc(
			ft_strlen(data->commandline) * sizeof(char *) + 1);
	while (data->commandline[i])
	{
		a = malloc(ft_strlen(data->commandline) + 1);
		if (data->commandline[i] == ' ')
			i++;
		else
			i = parserv2(a, i, argi++, data);
	}
	data->arguments[argi] = NULL;
}
