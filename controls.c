/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:52:17 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 03:10:52 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializefunction(char **envp, int argc, char **argv, t_data *data)
{
	char	*pcname;

	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	pcname = getpcname();
	findstarttext(pcname, data);
	data->path = ft_split(getenv("PATH"), ':');
	data->envp = copyenv(envp);
	data->exportp = copyenv(envp);
	data->exportlen = commandpointerlen(data->exportp);
	g_global.error = 0;
	data->exitstatus = 0;
	g_global.execstatus = 0;
	g_global.heredoc = 0;
	data->arguments = NULL;
	data->commandline = NULL;
	data->parts = NULL;
}
