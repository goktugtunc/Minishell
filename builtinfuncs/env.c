/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:52:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 01:24:05 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isprintableenv(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '=') == NULL)
			return (0);
		i++;
	}
	return (1);
}

void	envcommand(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (commandpointerlen(str) == 1 || isprintableenv(str))
	{
		while (i < commandpointerlen(data->envp))
			printf("%s\n", data->envp[i++]);
		if (commandpointerlen(str) != 1)
		{
			i = 0;
			while (str[++i])
				printf("%s\n", str[i]);
		}
		return ;
	}
	i = 0;
	while (str[++i])
	{
		if (ft_strchr(str[i], '=') == NULL)
		{
			printf("env: %s: No such file or directory\n", str[i]);
			return ;
		}
	}
}
