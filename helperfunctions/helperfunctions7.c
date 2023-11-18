/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:04:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 14:25:24 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_len(t_red *red)
{
	int	i;

	i = 0;
	while (red[i].type)
	{
		i++;
	}
	return (i - 1);
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
		ft_chiledforpipe(&(data->parts[i - 1]), &(data->parts[i + 1]), data);
	}
	else
	{
		ft_output_all(&(data->parts[0]), data);
	}
}
