/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcontrol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:13:29 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 03:13:28 by gotunc           ###   ########.fr       */
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
	if (!ft_strcmp(data->arguments[0], "|") && data->parsererrorcode == 0
		&& g_global.error == 0)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		data->exitstatus = 258;
		data->parsererrorcode = 3;
	}
	while (data->arguments[i] && g_global.error == 0)
		i++;
	if (isredirection(data->arguments[i - 1]) && data->parsererrorcode == 0
		&& g_global.error == 0)
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
	while (data->arguments[i] && data->arguments[i + 1]
		&& data->parsererrorcode == 0 && g_global.error == 0)
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
	errorcontrol2(data);
}
