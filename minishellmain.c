/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/07 18:24:46 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decisionmechanism(char **str)
{
	if (ft_strcmp(str[0], "cd") == 0)
		cdcommand(str);
	else if (ft_strcmp(str[0], "echo") == 0)
		echocommand(str);
	else if (ft_strcmp(str[0], "env") == 0)
		envcommand(str);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str, 0, 0);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand();
	else if (ft_strcmp(str[0], "unset") == 0)
		unsetcommand(str);
	else if (ft_strcmp(str[0], "exit") == 0)
		exitcommand();
	else
		ft_chiled(str);
}

void	startprogram(void)
{
	while (1)
	{
		g_data->errorstatus = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
			ifsendeof();
		quoteerror();
		if (g_data->commandline)
			add_history(g_data->commandline);
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			parser();
			g_data->parts = lastparse();
			if (g_data->commandcount > 1)
			{
				ft_chiledforpipe();
			}
			else if (g_data->commandline)
			{
				decisionmechanism(g_data->parts[0].str);
			}
			freeendwhile();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	initializefunction(envp, argc, argv);
	startprogram();
	return (0);
}
