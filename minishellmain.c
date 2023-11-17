/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/17 18:23:56 by gotunc           ###   ########.fr       */
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

void	commandfinderpipe(t_data *data)
{
	int	i;
	int	tru;

	tru = 0;
	i = 0;
	while (ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		if ((!ft_strcmp(data->parts[i + 1].type, "simpleoutput") ||
			!ft_strcmp(data->parts[i + 1].type, "simpleinput") ||
			!ft_strcmp(data->parts[i + 1].type, "multipleoutput")))
			tru = 0;
		i++;
	}
	if (!ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		if (tru == 0)
			ft_chiledforpipe(&(data->parts[0]), &(data->parts[i + 1]), data);
		else
			ft_chiledforpipe(&(data->parts[i - 1]), &(data->parts[i + 1]), data);
	}
	else
	{
		commandfinderother(&(data->parts[0]), data);
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

void	commandfinderother(t_parse *parts, t_data *data)
{
	int	i;
	int	command;

	command = 0;
	i = find_inout(parts);
	if (i == 0)
		command = 1;
	if (i != -1 && (parts[i].type) && parts[i + 1].type && !ft_strcmp(parts[i].str[1], "word"))
	{
		if (!ft_strcmp(parts[i].type, "multipleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_multiple_right_redirection(parts[i + 1].str[0], command, data);
		else if (!ft_strcmp(parts[i].type, "simpleoutput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_odd_right_redirection(parts[i + 1].str[0], command, data);
		else if (!ft_strcmp(parts[i].type, "simpleinput") && !ft_strcmp(parts[i + 1].type, "word"))
			ft_odd_left_redirection(parts[i + 1].str[0], command, data);
	}
	else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput")
			|| !ft_strcmp(parts[i].type, "simpleoutput")
			|| !ft_strcmp(parts[i].type, "multipleoutput"))
		&& parts[i + 1].type)
	{
		if (!ft_strcmp(parts[i + 1].type, "simpleoutput")
			|| !ft_strcmp(parts[i + 1].type, "simpleinput")
			|| !ft_strcmp(parts[i + 1].type, "multipleoutput")
			|| !ft_strcmp(parts[i + 1].type, "multipleinput"))
			printf("bash: syntax error near unexpected token `%s'\n", parts[i + 1].str[0]);
	}
	else if (i != -1 && (!ft_strcmp(parts[i].type, "simpleinput")
			|| !ft_strcmp(parts[i].type, "simpleoutput")
			|| !ft_strcmp(parts[i].type, "multipleoutput"))
		&& !parts[i + 1].type)
		printf("bash: syntax error near unexpected token `newline'\n");
	else
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
		if (data->commandline[0])
			add_history(data->commandline);
		else
			free(data->commandline);
		quoteerror(data);
		if (data->errorstatus == 0 && data->commandline[0])
		{
			parser(data);
			if (data->parsererrorcode == 0)
			{
				transformdollar(data);
				data->exitstatus = 127;
				removequotes(data);
				data->parts = lastparse(data->arguments, 1, -1, data);
				commandfinderpipe(data);
			}
			else
			{
				printf("> bash: syntax error: unexpected end of file\n");
				data->exitstatus = 258;
			}
		}
		preparewhile(data);
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
