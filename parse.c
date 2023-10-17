/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 13:29:33 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *command, t_lists *data)
{
	int	i;
	int	argcount;

	i = 0;
	argcount = 0;
	if (lettercount(command, 34) % 2 != 0 || lettercount(command, 39) % 2 != 0)
	{
		printf("\033[31;4mMinishell: Command is invalid: %s\n\033[0m", command);
		return (0);
	}
	data->commandcount = commandcount(command); // bu fonksiyon eklenecek
	while (command[i]) // bu döngüyü kullanarak kaç tane girdi olması gerektiğini hesaplayacağım
	{
		i++;
	}
	return (1);
}
