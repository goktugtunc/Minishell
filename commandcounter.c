/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandcounter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:32:38 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/28 18:36:25 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isinnail(command)
{
}

int	commandcounter(char *command)
{
	int		i;
	char	**commandarray;
	int		commandcount;

	i = 0;
	commandarray = ft_split(command, ' ');
	commandcount = 0;
	while (command[i])
	{
		if (command[i] == 34)
		{
			commandcount++;
			i++;
			while (command[i] == 34 && (command[i] == ' ' || command[i] == '<' || command[i] == '>'))
				i++;
		}
		i++;
	}
}
