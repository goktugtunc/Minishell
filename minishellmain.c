/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 01:48:03 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decisionmechanism(char **str, t_data *data)
{
	if (ft_strcmp(str[0], "cd") == 0)
		cdcommand(str, data);
	else if (ft_strcmp(str[0], "echo") == 0)
		echocommand(str);
	else if (ft_strcmp(str[0], "env") == 0)
		envcommand(data);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str, 0, 0, data);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand(data);
	else if (ft_strcmp(str[0], "unset") == 0)
		unsetcommand(str, data);
	else if (ft_strcmp(str[0], "exit") == 0)
		exitcommand();
	else
		ft_chiled(str, data);
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

// en sonda pipe varsa yeni satırda girdi istenecek.
// << 
// char	send_redir(t_red *red)
// {
// 	int	command;
// 	int		i;
// 	char	*input;
// 	char	*output;
	
// 	command = 0;
// 	i = 0;
// 	while(red[i].str && red[i].str[0] != '|')
// 	{
// 		if (red[i].str[0] == '>')
// 		{
// 			if(output)
// 				free(output);
// 			output = ft_strdup(red[i].str);
// 		}
// 		else if (red[i].str[0] == '<')
// 		{
// 			if(input)
// 				free(input);
// 			input = ft_strdup(red[i].str);
// 		}
// 		i++;
// 	}
// }

void	commandfinderpipe(t_data *data)
{
	int	i;
	int	tru;

	tru = 0;
	i = 0;

	while (ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		i++;
	}
	if (!ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		ft_chiledforpipe(&(data->parts[i - 1]), &(data->parts[i + 1]), data);
	}
	else
	{
		ft_output_all(&(data->parts[0]), data);
	}
}

int	find_inout(t_parse *parts)
{
	int	i;

	i = 0;
	while (ft_strcmp(parts[i].type, "multipleoutput")
		&& ft_strcmp(parts[i].type, "simpleoutput")
		&& ft_strcmp(parts[i].type, "simpleinput"))
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

int		red_len(t_red *red)
{
	int	i;

	i = 0;
	while(red[i].type)
	{
		i++;
	}
	return (i - 1);
}
int x = 0;

void	ft_input_all(t_parse *part, t_data *data)
{
	int i;

	if (check_redir(data->arguments)&& part->red)
	{
		i = red_len(part->red);
		while(i + 1)
		{
			if (part->red[i].str[0] == '<' && part->red[i].str[1] == '<')
			{

				ft_multiple_left_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			else if (part->red[i].str[0] == '<')
			{

				ft_odd_left_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			i--;
		}
	}
	commandfinderother(part, data);
}

void	ft_output_all(t_parse *part, t_data *data)
{
	int i;

	if (check_redir(data->arguments) && part->red)
	{
		i = red_len(part->red);
		while(i + 1)
		{
			if (part->red[i].str[0] == '>' && part->red[i].str[1] == '>')
			{
				ft_multiple_right_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			else if (part->red[i].str[0] == '>')
			{
				ft_odd_right_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			i--;
		}
	}
	ft_input_all(part, data);
}

void	commandfinderother(t_parse *parts, t_data *data)
{
	// int	i;
	// int	command;
	// int		i;
	// char	*input;
	// char	*output;
	
	// command = 0;
	// i = 0;
	// while(red[i].str && red[i].str[0] != '|')
	// {
	// 	if (red[i].str[0] == '>')
	// 	{
	// 		if(output)
	// 			free(output);
	// 		output = ft_strdup(red[i].str);
	// 	}
	// 	else if (red[i].str[0] == '<')
	// 	{
	// 		if(input)
	// 			free(input);
	// 		input = ft_strdup(red[i].str);
	// 	}
	// 	i++;
	// }
	// i = find_inout(parts);
	// if (i == 0)
	// 	command = 1;
	// if (i != -1 && (parts[i].type) && parts[i + 1].type &&  !ft_strcmp(parts[i].str[1], "word"))
	// {
	// 	if (!ft_strcmp(parts[i].type, "multipleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
	// 		ft_multiple_right_redirection(parts[i + 1].str[0], command, data);
	// 	else if (!ft_strcmp(parts[i].type, "simpleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
	// 		ft_odd_right_redirection(parts[i + 1].str[0], command, data);
	// 	else if (!ft_strcmp(parts[i].type, "simpleinput") && !ft_strcmp(parts[i + 1].type, "word"))
	// 		ft_odd_left_redirection(parts[i + 1].str[0], command, data);
	// }
	// else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput")
	// 		|| !ft_strcmp(parts[i].type, "simpleoutput")
	// 		|| !ft_strcmp(parts[i].type, "multipleoutput"))
	// 	&& parts[i + 1].type)
	// {
	// 	if (!ft_strcmp(parts[i + 1].type, "simpleoutput")
	// 		|| !ft_strcmp(parts[i + 1].type, "simpleinput")
	// 		|| !ft_strcmp(parts[i + 1].type, "multipleoutput")
	// 		|| !ft_strcmp(parts[i + 1].type, "multipleinput"))
	// 		printf("bash: syntax error near unexpected token `%s'\n", parts[i + 1].str[0]);
	// }
	// else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput")
	// 		|| !ft_strcmp(parts[i].type, "simpleoutput")
	// 		|| !ft_strcmp(parts[i].type, "multipleoutput"))
	// 	&& !parts[i + 1].type)
	// 	printf("bash: syntax error near unexpected token `newline'\n");
	// else
		decisionmechanism(parts[0].str, data);
}


void	startprogram(t_data *data)
{
	while (1)
	{
		data->errorstatus = 0;
		data->commandline = readline(data->starttext);
		if (data->commandline == NULL)
			ifsendeof(data);
		if (data->commandline && data->commandline[0])
			add_history(data->commandline);
		else
			free(data->commandline);
		quoteerror(data);
		if (data->errorstatus == 0 && data->commandline[0] != '\0')
		{
			parser(data);
			//parse2(data);
			transformdollar(data);
			removequotes(data);
			data->parts = lastparse(data->arguments, 1, -1, data);
			commandfinderpipe(data);
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
			freeendwhile(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	signal(SIGQUIT, ifsendsigquit);
	initializefunction(envp, argc, argv, data);
	startprogram(data);
	return (0);
}
