/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:24:07 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 00:34:59 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unsetcommand(char **str, t_data *data)
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
			if (findenvpindex(str[i], ft_strlen(str[i]), data) != -1)
			{
				data->envp = removedoublepointerarg(data->envp,
						findenvpindex(str[i], ft_strlen(str[i]), data));
			}
			if (findexportindex(str[i], ft_strlen(str[i]), data) != -1)
				data->exportp = removedoublepointerarg(data->exportp,
						findexportindex(str[i], ft_strlen(str[i]), data));
		}
		else
			printf("bash: unset: `%s': not a valid identifier\n", str[i]);
	}
}
