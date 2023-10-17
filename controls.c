/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:52:17 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/16 22:34:13 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	controller(t_lists *data, char **envp, int argc, char **argv)
{
	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	getusernameandpcname(data);
	findstarttext(data);
	data->path = findpath(envp);
}
