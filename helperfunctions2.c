/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:05:18 by goktugtunc        #+#    #+#             */
/*   Updated: 2023/10/30 20:35:46 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copyenv(char **env)
{
	char	**copiedenv;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copiedenv = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		copiedenv[i] = ft_strdup(env[i]);
	copiedenv[i] = NULL;
	return (copiedenv);
}

int	check_quote(char *line, int control)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (sign == 0)
				sign = 1;
			else if (sign == 1)
				sign = 0;
		}
		else if (line[i] == '\"')
		{
			if (sign == 0)
				sign = 2;
			else if (sign == 2)
				sign = 0;
		}
		i++;
	}
	return (sign);
}

int	check_quote1(t_lists *data)
{
	int		i;
	int		sign;
	char	*line;

	data->containquote = 0;
	line = data->commandline;
	sign = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			data->containquote = 1;
			if (sign == 0)
				sign = 1;
			else if (sign == 1)
				sign = 0;
		}
		else if (line[i] == '\"')
		{
			data->containquote = 1;
			if (sign == 0)
				sign = 2;
			else if (sign == 2)
				sign = 0;
		}
		i++;
	}
	return (sign);
}
