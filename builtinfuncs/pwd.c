/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:53:45 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/21 23:07:35 by gotunc           ###   ########.fr       */
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
	freedoublepointer(temp);
}
