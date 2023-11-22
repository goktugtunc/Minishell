/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freevarforwhile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:56:42 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:51:11 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preparewhile2(t_data *data)
{
	data->parsererrorcode = 0;
	g_global.error = 0;
	g_global.execstatus = 0;
	data->errorstatus = 0;
	data->commandcount = 0;
	data->commandline = NULL;
	data->arguments = NULL;
	data->parts = NULL;
}

void	prep_parts_red(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->parts[i].type != NULL)
	{
		if (data->parts[i].red)
		{
			while (data->parts[i].red[j].type)
			{
				free(data->parts[i].red[j].str);
				data->parts[i].red[j].str = NULL;
				free(data->parts[i].red[j].type);
				data->parts[i].red[j++].type = NULL;
			}
			j = 0;
			free(data->parts[i].red);
			data->parts[i].red = NULL;
		}
		freedoublepointer(data->parts[i].str);
		free(data->parts[i].type);
		i++;
	}
	free(data->parts);
}

void	preparewhile(t_data *data)
{
	if (data->commandline && data->commandline[0])
	{
		free(data->commandline);
		if (data->arguments)
		{
			freedoublepointer(data->arguments);
		}
		if (data->parts)
		{
			prep_parts_red(data);
		}
	}
	preparewhile2(data);
}
