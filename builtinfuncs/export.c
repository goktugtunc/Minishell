/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/04 11:36:49 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exportcommand(char **str) // fonksiyonda string i sıralayacak bir algoritma yazmam gerekiyor. Bir de parse yapılacak. Girilen parametrenin başında sayı olmayacak . olmayacak gibi
{
	int	i;

	i = 0;
	if (commandpointerlen(str) != 1)
	{
		i = 1;
		while (i < commandpointerlen(str))
		{
			if (ft_strchr(str[i], '='))
			{
				g_data->envp[commandpointerlen(g_data->envp) + 1] = NULL;
				g_data->envp[commandpointerlen(g_data->envp)] = ft_strdup(str[i]);
			}
			g_data->exportp[commandpointerlen(g_data->exportp) + 1] = NULL;
			g_data->exportp[commandpointerlen(g_data->exportp)] = ft_strdup(str[i]);
			i++;
		}
	}
	while (i < commandpointerlen(g_data->exportp))
	{
		printf("declare -x %s\n", g_data->exportp[i]);
		i++;
	}
}
