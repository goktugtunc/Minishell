/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:52:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/08 22:01:28 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envcommand(char **str)
{
	int	i;

	i = 0;
	while (i < commandpointerlen(g_data->envp))
	{
		printf("%s\n", g_data->envp[i]);
		i++;
	}
	i = 1;
	while (i < commandpointerlen(str))
	{
		if (ft_strchr(str[i], '='))
		{
			printf("%s\n", str[i]);
		}
		else
		{
			perror(ft_strjoin2("env: ", str[i]));
			return ;
		}
		i++;
	}
}
