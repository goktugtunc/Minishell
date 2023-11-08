/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputandoutput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:59:52 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/08 18:53:18 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*simpleinputcommand1(int i)
{
	int	fd;

	fd = open(g_data->parts[i + 1].str[0], O_RDWR);
	if (fd == -1)
	{
		printf("%s:\033[0m \033[31;4m%s: No such file or directory\033[0m\n", g_data->simplestarttext, g_data->parts[i + 1].str[0]);
	}
	else
		close(fd);
	return (NULL);
}

char	*simpleoutputcommand1(int i)
{
	int	fd;

	fd = open(g_data->parts[i + 1].str[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
	close(fd);
	return (NULL);
}
