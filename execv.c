/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:08:43 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 01:01:56 by amonem           ###   ########.fr       */
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

void	runexecve(t_data *data, char **str, int fds[2], int chiled)
{
	char	*temp;

	if (chiled == 0)
	{
		temp = get_the_path(data->envp, str[0], data);
		if (execve(temp,
				str, data->envp) == -1)
		{
			dup2(data->fderr, 1);
			close(fds[0]);
			write(fds[1], "1", 1);
			close(fds[1]);
			if (str[0][0])
				printf("-bash: %s: command not found\n", str[0]);
			exit (0);
		}
	}
	wait(NULL);
	close(fds[1]);
	temp = malloc(3);
	read(fds[0], temp, 2);
	close(fds[0]);
	if (temp[0] == '1')
		data->exitstatus = 127;
	free(temp);
}

void	ft_chiled(char **str, t_data *data)
{
	int		chiled;
	int		fds[2];

	g_global.execstatus = 1;
	data->exitstatus = 0;
	pipe(fds);
	chiled = fork();
	if (chiled == -1)
		exit(1);
	runexecve(data, str, fds, chiled);
}
