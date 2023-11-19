/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:53:45 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 17:41:18 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwdcommand(t_data *data)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(data->envp[findenvpindex("PWD=", 4, data)], '=');
	printf("%s\n", temp[1]);
	while (temp[i])
		free(temp[i++]);
	free(temp);
}
