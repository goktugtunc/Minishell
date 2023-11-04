/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:05:18 by goktugtunc        #+#    #+#             */
/*   Updated: 2023/11/04 10:51:48 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (line[i] && i <= control)
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

void	print_twodstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	commandpointerlen(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		i++;
	return (i);
}
