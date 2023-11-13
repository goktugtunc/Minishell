/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/13 21:58:00 by amonem           ###   ########.fr       */
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

// void	ft_dorequire(void)
// {
// 	if (g_data->commandcount > 1 && ft_strcmp(g_data->parts[1].str[0], "|") == 0)
// 	{
// 		ft_chiledforpipe(g_data->parts[0].str, g_data->parts[2].str);
// 	}
// 	else if(g_data->commandline)
// 	{
// 		decisionmechanism(g_data->parts[0].str);
// 	}
// }

// void	commandfinder(void)
// {
// 	int	i;

// 	i = 0;
// 	while (g_data->parts[i].type)
// 	{
// 		if (!ft_strcmp(g_data->parts[i].type, "word"))
// 		{
// 			if (g_data->parts[i + 1].type && g_data->parts[i + 2].type)
// 			{
// 				if (!ft_strcmp(g_data->parts[i + 1].type, "pipe") && !ft_strcmp(g_data->parts[i + 2].type, "word"))
// 				{
// 					ft_chiledforpipe(g_data->parts[i].str, g_data->parts[i + 2].str);
// 					i += g_data->j;
// 					//printf("**%d\n", g_data->j);
// 				}
// 				else if (!ft_strcmp(g_data->parts[i + 1].type, "multipleoutput") && !ft_strcmp(g_data->parts[i + 2].type, "word"))
// 					ft_multiple_right_redirection(g_data->parts[i + 2].str[0], i);
// 				else if (!ft_strcmp(g_data->parts[i + 1].type, "simpleoutput") && !ft_strcmp(g_data->parts[i + 2].type, "word"))
// 					ft_odd_right_redirection(g_data->parts[i + 2].str[0], i);
// 				else if (!ft_strcmp(g_data->parts[i + 1].type, "simpleinput") && !ft_strcmp(g_data->parts[i + 2].type, "word"))
// 					ft_odd_left_redirection(g_data->parts[i + 2].str[0], i);
// 				i += 3;
// 			}
// 			else if (g_data->parts[i + 1].type)
// 			{
// 				if (g_data->parts[i + 2].type)
// 				{
// 				}
// 				i += 2;
// 			}
// 			else
// 			{
// 				decisionmechanism(g_data->parts[i].str);
// 				i++;
// 			}
// 		}
// 		else if (!ft_strcmp(g_data->parts[i].type, "pipe"))
// 		{
// 			if (g_data->parts[i + 1].type)
// 			{
// 			}
// 			else
// 			{
// 			}
// 		}
// 		else if (!ft_strcmp(g_data->parts[i].type, "simpleinput"))
// 		{
// 			if (!ft_strcmp(g_data->parts[i + 1].type, "word"))
// 			{
// 				i += 2;
// 			}
// 			else
// 			{
// 			}
// 		}
// 		else if (!ft_strcmp(g_data->parts[i].type, "multipleinput"))
// 		{
// 			if (g_data->parts[i + 1].type)
// 			{
// 			}
// 			else
// 			{
// 			}
// 		}
// 		else if (!ft_strcmp(g_data->parts[i].type, "simpleoutput"))
// 		{
// 			if (!ft_strcmp(g_data->parts[i + 1].type, "word"))
// 			{
// 				simpleoutputcommand1(i);
// 				i += 2;
// 			}
// 			else if (g_data->parts[i + 1].type)
// 			{
// 				printf("%s:\033[0m \033[31;4msyntax error near unexpected token `%s'\033[0m\n", g_data->simplestarttext, g_data->parts[i + 1].str[0]);
// 				i += 2;
// 			}
// 			else
// 			{
// 			}
// 		}
// 		else if (!ft_strcmp(g_data->parts[i].type, "multipleoutput"))
// 		{
// 			if (g_data->parts[i + 1].type)
// 			{
// 			}
// 			else
// 			{
// 			}
// 		}
// 	}
// }

void	commandfinderpipe(void)
{
	int	i;
	int	tru;

	tru = 0;
	i = 0;
	while (ft_strcmp(g_data->parts[i].type, "pipe") && g_data->parts[i + 1].type)
	{
		if ((!ft_strcmp(g_data->parts[i + 1].type, "simpleoutput") ||
			!ft_strcmp(g_data->parts[i + 1].type, "simpleinput") ||
			!ft_strcmp(g_data->parts[i + 1].type, "multipleoutput")))
			tru = 0;
		i++;
	}
	if (!ft_strcmp(g_data->parts[i].type, "pipe") && g_data->parts[i + 1].type)
	{
		if (tru == 0)
			ft_chiledforpipe(&(g_data->parts[0]), &(g_data->parts[i + 1]));
		else
			ft_chiledforpipe(&(g_data->parts[i - 1]), &(g_data->parts[i + 1]));
	}
	else
	{
		commandfinderother(&(g_data->parts[0]));
	}
}

int	find_inout(t_parse *parts)
{
	int	i;

	i = 0;
	while(ft_strcmp(parts[i].type, "multipleoutput") &&
		ft_strcmp(parts[i].type, "simpleoutput") &&
		ft_strcmp(parts[i].type, "simpleinput"))
		{
			i++;
			if (!parts[i].type)
				return (-1);
		}
	return (i);
}

// t_parse	join_redirection(t_parse *parts)
// {
// 	int		i;
// 	char	**redirections;
// 	char	**str;
// 	t_parse	*redir;

// 	str = (char *)malloc(sizeof(char *) * 2 + 1);
// 	redir = (t_parse *)malloc(sizeof(t_parse) * 2);
// 	redirections = (char *)malloc(sizeof(char *) * 2 + 1);
// 	i = 0;
// 	while(parts[i].type && (ft_strcmp(parts[i].str[0] , "<")) &&
// 		(ft_strcmp(parts[i].str[0] , ">")) &&
// 		(ft_strcmp(parts[i].str[0] , ">>")))
// 			i++;
// 	redirections[0] = ft_strdup(parts[i].str[0]);
// 	redirections[1] = ft_strdup(parts[i + 1].str[0]);
// 	redirections[2] = NULL;
// 	redir[1].str = redirections;
// }

void	commandfinderother(t_parse *parts)
{
	int	i;
	int	command;

	command = 0;
	i = find_inout(parts);
	if (i == 0)
		command = 1;
	if (i != -1 && (parts[i].type) && parts[i + 1].type &&  !ft_strcmp(parts[i].str[1], "word"))
	{
		if (!ft_strcmp(parts[i].type, "multipleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_multiple_right_redirection(parts[i + 1].str[0], command);
		else if (!ft_strcmp(parts[i].type, "simpleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_odd_right_redirection(parts[i + 1].str[0], command);
		else if (!ft_strcmp(parts[i].type, "simpleinput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_odd_left_redirection(parts[i + 1].str[0], command);
	}
	else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput") ||
		!ft_strcmp(parts[i].type, "simpleoutput") ||
		!ft_strcmp(parts[i].type, "multipleoutput")) && parts[i + 1].type)
		{
			if (!ft_strcmp(parts[i + 1].type, "simpleoutput"))
				printf("bash: syntax error near unexpected token `>'\n");
			if (!ft_strcmp(parts[i + 1].type, "simpleinput"))
				printf("bash: syntax error near unexpected token `<'\n");
			if (!ft_strcmp(parts[i + 1].type, "multipleoutput"))
				printf("bash: syntax error near unexpected token `>>'\n");
			if (!ft_strcmp(parts[i + 1].str[0], "<<"))
				printf("bash: syntax error near unexpected token `<<'\n");
		}
	else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput") ||
		!ft_strcmp(parts[i].type, "simpleoutput") ||
		!ft_strcmp(parts[i].type, "multipleoutput")) && !parts[i + 1].type)
		printf("bash: syntax error near unexpected token `newline'\n");
	else
		decisionmechanism(parts[0].str);
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
		else
			free(g_data->commandline);
		quoteerror();
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			parser();

			transformdollar(g_data);
			removequotes(g_data);

			g_data->parts = lastparse(g_data->arguments, 1, -1);
			commandfinderpipe();

			// commandfinder(); // Bu fonksiyonda teker teker argümanları pipe input ya da output olma durumuna göre yönlendireceğim.
			//if (g_data->commandcount > 1 && ft_strcmp(g_data->parts[1].str[0], ">") == 0)
			//{
			//	ft_odd_right_redirection();
			//}
			//if (1)
			//{
			//	ft_odd_left_redirection();
			//}
			//else
			//	ft_dorequire();
			freeendwhile();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	signal(SIGQUIT, ifsendsigquit);
	initializefunction(envp, argc, argv);
	startprogram();
	return (0);
}
