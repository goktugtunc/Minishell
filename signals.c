/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 00:53:21 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ifsendsigquit(int signal)
{
	(void)signal;
	rl_redisplay();
	return ;
}

void	ifsendsigint(int signal)
{
	if (g_global.heredoc)
	{
		(void)signal;
		g_global.error = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 3);
		return ;
	}
	else
	{
		if (g_global.execstatus)
		{
			ft_putstr_fd("\n", 2);
			printf("\033[1A");
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		}
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 4);
		rl_replace_line("", 0);
	}
}

void	ifsendeof(t_data *data)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit                                        \n", data->starttext);
	exit(0);
}

void	delete_ctrl(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}
