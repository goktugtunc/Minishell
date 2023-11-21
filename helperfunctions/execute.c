/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:05:10 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/21 21:51:27 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		i++;
	}
	if (!ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		ft_chiledfpi(&(data->parts[i - 1]), &(data->parts[i + 1]), data);
	}
	else
	{
		ft_output_all(&(data->parts[0]), data);
	}
}
