/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/09 20:39:38 by amonem           ###   ########.fr       */
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
	//else if (ft_strcmp(str[0], "exit") == 0)
	//	exitcommand(str);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand();
	else
		ft_chiled(str);
	//else if (ft_strcmp(str[0], "unset") == 0) // goktug tarafından yapılacak
	//	unsetcommand(str);
	//else
	//	normalcommands(str);
}
void	ft_dorequire(void)
{
	if (g_data->commandcount > 1 && ft_strcmp(g_data->parts[1].str[0], "|") == 0)
	{
		ft_chiledforpipe();
	}
	else if(g_data->commandline)
	{
		decisionmechanism(g_data->parts[0].str);
	}
}
void	startprogram(void)
{
	while (TRUE)
	{
		g_data->errorstatus = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
		{
			ifsendeof();
		}
		quoteerror();
		if (g_data->commandline)
			add_history(g_data->commandline);
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			parser();
			g_data->parts = lastparse();
			if (g_data->commandcount > 1 && ft_strcmp(g_data->parts[1].str[0], ">") == 0)
			{
				ft_odd_right_redirection();
			}
			if (1)
			{
				ft_odd_left_redirection();
			}
			else
				ft_dorequire();
			// if (g_data->commandcount > 1 && ft_strcmp(g_data->parts[1].str[0], "|") == 0)
			// {
			// 	ft_chiledforpipe();
			// }

			// else if(g_data->commandline)
			// {
			// 	decisionmechanism(g_data->parts[0].str);
			// }
			// find path ekledim bu sayede çalışacak komutun hangi yolda olduğunu
			// ve böyle bir komutun olup olmadığını bulabiliriz
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

//asdas>asdasd 3  asdas , > , asdasd
//"asdasd>asdasd" 1  "asdasd>asdasd"
//"asdas>"asdasda 1  "asdas>"asdasda 
//"asdas>">>sdasas 3 "asdas>" , >> , sdasas
//asdas ">>""<<"<'>' 4  asdas , ">>""<<" , < , '>'
//>>>>> 3  >> , >> , >

//asdsd  >  "askdasj"  3