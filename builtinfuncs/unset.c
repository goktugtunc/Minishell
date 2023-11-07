/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:24:07 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/07 02:23:30 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unsetcommand(char **str)
{
	int	i;

	i = 0;
	if (commandpointerlen(str) == 1)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (str[++i])
	{
		if (exportparser(str[i]))
		{
			if (findenvpindex(str[i], ft_strlen(str[i])) != -1)
			{
				g_data->envp = removedoublepointerarg(g_data->envp,
						findenvpindex(str[i], ft_strlen(str[i])));
			}
			if (findexportindex(str[i], ft_strlen(str[i])) != -1)
				g_data->exportp = removedoublepointerarg(g_data->exportp,
						findexportindex(str[i], ft_strlen(str[i])));
		}
		else
			printf("bash: unset: `%s': not a valid identifier\n", str[i]);
	}
}
