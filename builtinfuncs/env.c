/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:52:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:50:38 by amonem           ###   ########.fr       */
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

void	envcommand(t_data *data)
{
	int	i;

	i = 0;
	while (i < commandpointerlen(data->envp))
		printf("%s\n", data->envp[i++]);
}
