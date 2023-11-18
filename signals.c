/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 00:47:37 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ifsendsigquit(int signal)
{
	//rl_redisplay(); // control 4 basıldığında yazı çıkmamasını sağlamalıyım.
	(void)signal;
	rl_redisplay();
	//return ;
}

void	ifsendsigint(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ifsendeof(t_data *data)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit\n", data->starttext);
	exit(1);
}
