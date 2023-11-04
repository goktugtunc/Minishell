/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/04 03:47:11 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	TODO
	Exportla ekleyip sıraladığında bazen garbage değer atıyor.
	Sıralama doğru ama fonksiyon ilk çalıştığında ve büyük harf verildiğinde
	çalışıyor ama direkt o anki fonksiyonun çalışışında o çıktıda girilen değeri vermiyor.
	Tekrar export denildiğinde çalışıyor.
	Muhtemelen NULL ataması ile ilgili.
*/

void	sortexport(void)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	while (g_data->exportp[i])
	{
		j = 0;
		while (g_data->exportp[j])
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
	sortexport();
	while (i < commandpointerlen(g_data->exportp))
	{
		printf("declare -x %s\n", g_data->exportp[i]);
		i++;
	}
}
