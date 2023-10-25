/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:05:18 by goktugtunc        #+#    #+#             */
/*   Updated: 2023/10/25 20:19:30 by goktugtunc       ###   ########.fr       */
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

int	check_quote(char *line)
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
