/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:40:26 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/02 14:21:43 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	findpath(char *searchedpath)
{
	int		i;
	char	*foundedpath;

	i = 0;
	while (g_data->path[i])
	{
		foundedpath = ft_strjoin2(g_data->path[i], "/");
		foundedpath = ft_strjoin2(foundedpath, searchedpath);
		if (access(foundedpath, F_OK) == 0)
		{
			g_data->foundedpath = foundedpath;
			return (1);
		}
		i++;
		free(foundedpath);
	}
	return (0);
}
