/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:19:05 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 14:12:06 by gotunc           ###   ########.fr       */
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

void	printexport(t_data *data)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	status = 0;
	while (data->exportp[i])
	{
		while (data->exportp[i][j])
		{
			printf("%c", data->exportp[i][j]);
			if (status == 0 && data->exportp[i][j] == '=')
			{
				status = 1;
				printf("\"");
			}
			j++;
		}
		printf("\"\n");
		status = 0;
		i++;
		j = 0;
	}
}

int	count_redir(char **str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>' || str[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

void	print2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("*%s\n", str[i]);
		i++;
	}
}

int	words_of_parts_outredir(char **argu)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (argu[i][0] == '|')
		return (1);
	while (argu[i])
	{
		if (argu[i][0] == '<' || argu[i][0] == '>')
		{
			count--;
			i++;
		}
		if (argu[i][0] == '|')
			return (count);
		i++;
		count++;
	}
	return (count);
}
