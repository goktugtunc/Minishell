/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:13:29 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 16:05:48 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isredirection(char *a)
{
	if (!ft_strcmp(a, "<"))
		return (1);
	else if (!ft_strcmp(a, ">"))
		return (1);
	else if (!ft_strcmp(a, ">>"))
		return (1);
	else if (!ft_strcmp(a, "<<"))
		return (1);
	else
		return (0);
}

void	errorcontrol2(t_data *data)
{
	int	i;

	i = 0;
	if (!ft_strcmp(data->arguments[0], "|"))
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		data->exitstatus = 258;
		data->parsererrorcode = 3;
	}
	while (data->arguments[i])
		i++;
	if (isredirection(data->arguments[i - 1]))
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		data->exitstatus = 258;
		data->parsererrorcode = 3;
	}
}

void	errorcontrol(t_data *data, int err)
{
	int	i;

	i = 0;
	errorcontrol2(data);
	while (data->arguments[i] && data->arguments[i + 1]
		&& data->parsererrorcode == 0)
	{
		if (!ft_strcmp(data->arguments[i], "|")
			&& !ft_strcmp(data->arguments[i + 1], "|"))
			err = 1;
		else if (isredirection(data->arguments[i])
			&& isredirection(data->arguments[i + 1]))
			err = 1;
		else if (isredirection(data->arguments[i])
			&& !ft_strcmp(data->arguments[i + 1], "|"))
			err = 1;
		if (err == 1)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n",
				data->arguments[i + 1]);
			data->exitstatus = 258;
			data->parsererrorcode = 3;
		}
		i++;
	}
}

int	iscommandinbuiltin(char *s)
{
	if (!ft_strcmp(s, "cd") || !ft_strcmp(s, "echo") || !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "unset") || !ft_strcmp(s, "exit"))
		return (1);
	return (0);
}