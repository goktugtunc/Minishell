/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublepointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 04:57:39 by goktugtunc        #+#    #+#             */
/*   Updated: 2023/11/05 12:51:00 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**adddoublepointer(char **dp, char *add)
{
	int		i;
	char	**returndp;

	returndp = malloc(sizeof(char *) * (commandpointerlen(dp) + 2));
	i = 0;
	while (dp[i])
	{
		returndp[i] = ft_strdup(dp[i]);
		free(dp[i]);
		i++;
	}
	free(dp[i]);
	returndp[i] = ft_strdup(add);
	returndp[i + 1] = NULL;
	free(dp);
	return (returndp);
}

char	**removedoublepointerarg(char **dp, int	i)
{
	char **returndp;
	int	j;
	int	rdpi;

	returndp = malloc(sizeof(char *) * commandpointerlen(dp));
	rdpi = 0;
	j = 0;
	while (dp[j])
	{
		if (j != i)
		{
			returndp[rdpi] = ft_strdup(dp[j]);
			rdpi++;
		}
		free(dp[j]);
		j++;
	}
	free(dp[j]);
	returndp[rdpi] = NULL;
	free(dp);
	return (returndp);
}
