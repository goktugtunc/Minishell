/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/26 00:08:14 by goktugtunc       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startprogram(t_lists *data)
{
	while (True)
	{
		data->errorcontrol = 0;
		data->commandline = readline(data->starttext);
		if (data->commandline == NULL)
			ifSendEOF(data);
		parse(data->commandline, data);
		if (data->errorcontrol == 0)
		{
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lists	*data;

	data = malloc(sizeof(t_lists));
	signal(SIGINT, ifsendsigint);
	initializefunction(data, envp, argc, argv);
	startprogram(data);
	return (0);
}

//asdas>asdasd 3  asdas , > , asdasd
//"asdasd>asdasd" 1  "asdasd>asdasd"
//"asdas>"asdasda 1  "asdas>"asdasda 
//"asdas>">>sdasas 3 "asdas>" , >> , sdasas
//asdas ">>""<<"<'>' 4  asdas , ">>""<<" , < , '>'
//>>>>> 3  >> , >> , >

//asdsd  >  "askdasj"  3