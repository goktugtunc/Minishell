/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandcounter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:32:38 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 11:23:22 by gotunc           ###   ########.fr       */
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
