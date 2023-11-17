/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 00:59:20 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ifsendsigquit(int signal)
{
	rl_redisplay(); // control 4 basıldığında yazı çıkmamasını sağlamalıyım.
	(void)signal;
	return ;
}

void	ifsendsigint(int signal)
{
	(void)signal;
}

void	ifsendeof(t_data *data)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit\n", data->starttext);
	exit(1);
}
