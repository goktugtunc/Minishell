/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublepointer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:09:14 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 03:21:35 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	commandpointerlen(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		i++;
	return (i);
}

char	**copyenv(char **env)
{
	char	**copiedenv;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copiedenv = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		copiedenv[i] = ft_strdup(env[i]);
	copiedenv[i] = NULL;
	return (copiedenv);
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
