/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:52:17 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/28 18:36:30 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializefunction(t_lists *data, char **envp, int argc, char **argv)
{
	char	*pcname;

	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	pcname = getpcname();
	findstarttext(data, pcname);
	data->path = ft_split(getenv("PATH"), ':');
	data->envp = copyenv(envp);
}
