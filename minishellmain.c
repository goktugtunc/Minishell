/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/09 00:51:56 by gotunc           ###   ########.fr       */
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

void	commandfinder(void)
{
	int	i;

	i = 0;
	while (g_data->parts[i].type)
	{
		if (!ft_strcmp(g_data->parts[i].type, "word"))
		{
			if (g_data->parts[i + 1].type && g_data->parts[i + 2].type)
			{
				if (!ft_strcmp(g_data->parts[i + 1].type, "pipe") && !ft_strcmp(g_data->parts[i + 2].type, "word"))
				{
				}
				else if (!ft_strcmp(g_data->parts[i + 1].type, "multipleinput") && !ft_strcmp(g_data->parts[i + 2].str[0], "EOM"))
				{
				}
				i += 3;
			}
			else if (g_data->parts[i + 1].type)
			{
				i += 2;
			}
			else
			{
				i++;
			}
		}
		else if (!ft_strcmp(g_data->parts[i].type, "pipe"))
		{
			if (g_data->parts[i + 1].type)
			{
			}
			else
			{
			}
		}
		else if (!ft_strcmp(g_data->parts[i].type, "simpleinput"))
		{
			if (!ft_strcmp(g_data->parts[i + 1].type, "word"))
			{
				simpleinputcommand1(i);
				i += 2;
			}
			else
			{
			}
		}
		else if (!ft_strcmp(g_data->parts[i].type, "multipleinput"))
		{
			if (g_data->parts[i + 1].type)
			{
			}
			else
			{
			}
		}
		else if (!ft_strcmp(g_data->parts[i].type, "simpleoutput"))
		{
			if (!ft_strcmp(g_data->parts[i + 1].type, "word"))
			{
				simpleoutputcommand1(i);
				i += 2;
			}
			else if (g_data->parts[i + 1].type)
			{
				printf("%s:\033[0m \033[31;4msyntax error near unexpected token `%s'\033[0m\n", g_data->simplestarttext, g_data->parts[i + 1].str[0]);
				i += 2;
			}
			else
			{
			}
		}
		else if (!ft_strcmp(g_data->parts[i].type, "multipleoutput"))
		{
			if (g_data->parts[i + 1].type)
			{
			}
			else
			{
			}
		}
	}
}

void	startprogram(void)
{
	while (1)
	{
		g_data->errorstatus = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
			ifsendeof();
		if (g_data->commandline && g_data->commandline[0])
			add_history(g_data->commandline);
		quoteerror();
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			parser();
			transformdollar(g_data); // burada dolar işlemlerini yapıyorum ancak şuanda doğru çalışmıyor. ft_strlen kadar yollamaktansa yeni bir fonksiyon ile stringin eşittirden öncekinin tamamıyla kıyaslamam lazım. $$ ve $? işaretlerini kontrol etmeliyim.
			g_data->parts = lastparse(g_data->arguments, 1, -1);
			//commandfinder(); // Bu fonksiyonda teker teker argümanları pipe input ya da output olma durumuna göre yönlendireceğim.
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
