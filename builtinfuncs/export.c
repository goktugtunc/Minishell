/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/04 15:52:47 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	TODO
	Exportla ekleyip sıraladığında bazen garbage değer atıyor.
	Muhtemelen NULL ataması ile ilgili.
*/

void	sortexport(void)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	printf("***%d***\n", g_data->exportlen);
	while (i < g_data->exportlen)
	{
		j = 0;
		while (j < g_data->exportlen)
		{
			if (ft_strcmp(g_data->exportp[i], g_data->exportp[j]) < 0)
			{
				temp = g_data->exportp[i];
				g_data->exportp[i] = g_data->exportp[j];
				g_data->exportp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	exportcommand(char **str) // fonksiyonda string i sıralayacak bir algoritma yazmam gerekiyor. Bir de parse yapılacak. Girilen parametrenin başında sayı olmayacak . olmayacak gibi
{
	int	i;

	printf("***%d***\n", g_data->exportlen);
	i = 0;
	if (commandpointerlen(str) != 1)
	{
		i = 1;
		while (i < commandpointerlen(str))
		{
			if (ft_strchr(str[i], '='))
			{
				// g_data->envp[commandpointerlen(g_data->envp) + 1] = NULL;
				g_data->envp[commandpointerlen(g_data->envp)] = ft_strdup(str[i]);
			}
			g_data->exportp[g_data->exportlen + 1] = NULL;
			g_data->exportp[g_data->exportlen] = ft_strdup(str[i]);
			g_data->exportlen++;
			i++;
		}
	}
	i = 0;
	while (i < g_data->exportlen)
	{
		printf("%s\n", g_data->exportp[i]);
		i++;
	}
	sortexport();
	i = 0;
	while (i < g_data->exportlen)
	{
		printf("declare -x %s\n", g_data->exportp[i]);
		i++;
	}
}
