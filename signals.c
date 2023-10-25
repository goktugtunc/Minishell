/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/25 17:52:19 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ifsendsigint(int signal)
{
	(void)signal;
}

void	ifSendEOF(t_lists *data)
{
	printf("\r%sExit!\n", data->starttext);
	exit(1);
}
