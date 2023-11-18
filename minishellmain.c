/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 00:55:22 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	exitstatus ayarlanacak - $? denildiğinde çıkacak değer
	signal fonksiyonları ayarlanacak
*/

void	commandfinderv2(t_data *data)
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

void	startprogram2(t_data *data)
{
	data->errorstatus = 0;
	data->commandline = readline("minishell");
	if (data->commandline == NULL)
		ifsendeof(data);
	if (data->commandline[0])
		add_history(data->commandline);
	else
		free(data->commandline);
	quoteerror(data);
}

void	startprogram(t_data *data)
{
	while (1)
	{
		startprogram2(data);
		if (data->errorstatus == 0 && data->commandline[0])
		{
			data->parts = NULL;
			parser(data);
			if (data->parsererrorcode == 0)
			{
				transformdollar(data, 0);
				data->exitstatus = 127;
				removequotes(data);
				data->parts = lastparse(data->arguments, 1, -1, data);
				commandfinderv2(data);
			}
			else if (data->parsererrorcode != 3)
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
