/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:08:43 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 00:41:25 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_of_str(char **argu)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (argu[i])
	{
		i++;
	}
	return (i);
}

char	**ft_towdcopy(char **src)
{
	char	**dest;
	int		i;
	int		words;

	i = 0;
	words = count_of_str(src);
	dest = (char **)malloc(sizeof(char **) * words + 1);
	while (i < words)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	*get_the_path(char **env, char *str, t_data *data)
{
	int		i;
	char	*check;

	i = 0;
	(void)env;
	while (data->path[i])
	{
		check = ft_strjoin2(data->path[i], "/");
		check = ft_strjoin(check, str);
		if (access(check, F_OK) == 0)
			return (check);
		else if (access(str, X_OK) == 0)
			return (str);
		free(check);
		i++;
	}
	return (NULL);
}

void	ft_chiled(char **str, t_data *data)
{
	int		chiled;
	char	*temp;

	chiled = fork();
	if (chiled == 0)
	{
		temp = get_the_path(data->envp, str[0], data);
		if (execve(temp,
				str, data->envp) == -1)
		{
			dup2(data->fderr, 1);
			if (str[0][0])
				printf("-bash: %s: command not found\n", str[0]);
			exit (0);
		}
	}
	wait(NULL);
}

void	echocommand(char **str)
{
	if (str[1])
	{
		if (echonflagcontroller(str[1]) == 1)
			print_twodstr(&str[2], 1);
		else
			print_twodstr(&str[1], 0);
	}
	else
		printf("\n");
}
