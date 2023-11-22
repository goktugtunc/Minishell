/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:10:23 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:50:34 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echonflagcontroller(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	print_twodstr(char **str, int flagcontrol)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
		if (!str[i] && flagcontrol == 0)
			printf("\n");
	}
}

void	echocommand(char **str)
{
	if (str[1])
	{
		if (echonflagcontroller(str[1]) == 1)
			print_twodstr(&str[2], 1);
		else
			print_twodstr(&str[1], 0);
	}
	else
		printf("\n");
}
