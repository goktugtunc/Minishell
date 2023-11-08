/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/09 00:40:39 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ifsendsigint(int signal)
{
	(void)signal;
}

void	ifsendeof(void)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit\n", g_data->starttext);
	exit(1);
}
