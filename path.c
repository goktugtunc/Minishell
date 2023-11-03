/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:40:26 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/03 22:49:16 by gotunc           ###   ########.fr       */
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
		foundedpath = ft_strjoin(foundedpath, searchedpath);
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

int	findpathindex(char *searchedpath)
{
	int	i;

	i = 0;
	while (g_data->path[i])
	{
		if (ft_strcmp(g_data->path[i], searchedpath))
			return (i);
		i++;
	}
	return (-1);
}

int	findenvpindex(char *searchedenvp, int searchindex)
{
	int	i;

	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strncmp(g_data->envp[i], searchedenvp, searchindex) == 0)
			return (i);
		i++;
	}
	return (-1);
}
