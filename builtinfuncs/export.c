/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:13:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/05 07:01:01 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	TODO
	isupdate fonksiyonunda envp de değer silmeye çalıştığımda segment alıyor.
	o fonksiyon genel olarak hatalı.
	muhtemelen if else koşullarıyla alakalı.
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

void	isupdate(char **str, int j)
{
	int	i;

	i = 0;
	if (!ft_strchr(str[j], '='))
	{
		while (g_data->exportp[i])
		{
			if (ft_strcmp(g_data->exportp[i], str[j]) == 0)
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
			i++;
		}
		return ;
	}
	while (g_data->exportp[i])
	{
		if (ft_strchr(g_data->exportp[i], '='))
		{
			if (ft_strcmp(ft_split(str[j], '=')[0], ft_split(g_data->exportp[i], '=')[0]) == 0)
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
		}
		else
			if (ft_strcmp(ft_split(str[j], '=')[0], g_data->exportp[i]))
				g_data->exportp = removedoublepointerarg(g_data->exportp, i);
		i++;
	}
	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strcmp(ft_split(str[j], '=')[0], ft_split(g_data->envp[i], '=')[0]) == 0)
			g_data->envp = removedoublepointerarg(g_data->envp, i);
		i++;
	}
}

void	exportcommand(char **str) // fonksiyonda string i sıralayacak bir algoritma yazmam gerekiyor. Bir de parse yapılacak. Girilen parametrenin başında sayı olmayacak . olmayacak gibi
{
	int	i;

	i = 0;
	if (str[1])
	{
		i = 1;
		while (str[i])
		{
			isupdate(str, i);
			if (ft_strchr(str[i], '='))
			{
				g_data->envp = adddoublepointer(g_data->envp, str[i]);
			}
			g_data->exportp = adddoublepointer(g_data->exportp, str[i]);
			i++;
		}
	}
	sortexport();
	i = 0;
	while (g_data->exportp[i])
	{
		printf("declare -x %s\n", g_data->exportp[i]);
		i++;
	}
}
