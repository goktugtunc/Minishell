/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/04 17:36:02 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	TODO
	Exportla ekleyip sıraladığında bazen garbage değer atıyor.
	Yeni değer eklerken ilk pointer a yer ataması yapmıyorum. Oyüzden de garbage değer atıyor ve kodda hataya sebep oluyor.
	Şuanda da 2 kere aynı şeyi yazdığımda bir alan açmadığı için segment yiyorum freelerken.
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

void	isupdate(char **str, int j)
{
	int	i;

	i = 0;
	i = 0;
	if (!ft_strchr(str[j], '='))
	{
		while (g_data->exportp[i])
		{
			if (ft_strcmp(g_data->exportp[i], str[j]) == 0)
				free(g_data->exportp[i]);
			i++;
		}
		return ;
	}
	while (g_data->exportp[i])
	{
		if (ft_strcmp(ft_split(str[j], '=')[0], ft_split(g_data->exportp[i], '=')[0]) == 0)
			free(g_data->exportp[i]);
		i++;
	}
	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strcmp(ft_split(str[j], '=')[0], ft_split(g_data->envp[i], '=')[0]) == 0)
			free(g_data->envp[i]);
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
			isupdate(str, i);
			if (ft_strchr(str[i], '='))
			{
				// g_data->envp[commandpointerlen(g_data->envp) + 1] = NULL;
				g_data->envp[commandpointerlen(g_data->envp)] = ft_strdup(str[i]);
			}
			// g_data->exportp[g_data->exportlen + 1] = NULL;
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
