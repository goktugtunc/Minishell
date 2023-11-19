/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freevarforwhile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:56:42 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 03:24:42 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preparewhile2(t_data *data)
{
	data->parsererrorcode = 0;
	g_global.error = 0;
	g_global.execstatus = 0;
	data->errorstatus = 0;
	data->commandline = NULL;
	data->arguments = NULL;
	data->parts = NULL;
}

void	preparewhile(t_data *data)
{
	int	i;

	i = 0;
	if (data->commandline && data->commandline[0])
	{
		free(data->commandline);
		if (data->arguments)
		{
			freedoublepointer(data->arguments);
		}
		i = 0;
		if (data->parts)
		{
			while (data->parts[i].type != NULL)
			{
				freedoublepointer(data->parts[i].str);
				free(data->parts[i].type);
				i++;
			}
			free(data->parts);
		}
	}
	preparewhile2(data);
}
