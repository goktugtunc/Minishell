/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:13:39 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:50:41 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exitcommand(t_data *data)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit                                        \n", data->starttext);
	printf("\t\033[32m   _____\n");
	printf("\t  /     \\\n");
	printf("\t /       \\\n");
	printf("\t|   .   . |\n");
	printf("\t|  ´   ´  |\n");
	printf("\t|   ___   |\n");
	printf("\t|  /   \\  |\n");
	printf("\t \\       /\n");
	printf("\t  \\_____/\n\n\033[0m");
	exit(0);
}
