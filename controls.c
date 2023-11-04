/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:52:17 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/04 11:19:30 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializefunction(char **envp, int argc, char **argv)
{
	char	*pcname;

	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	pcname = getpcname();
	findstarttext(pcname);
	g_data->path = ft_split(getenv("PATH"), ':');
	g_data->envp = copyenv(envp);
	g_data->exportp = copyenv(envp);
}

void	freeendwhile(void)
{
	int	i;

	i = 0;
	free(g_data->commandline);
	while (g_data->arguments[i])
		free(g_data->arguments[i++]);
	free(g_data->arguments);
	free(g_data->foundedpath);
}
