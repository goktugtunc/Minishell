/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 21:49:02 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startprogram(t_lists *data)
{
	while (TRUE)
	{
		data->errorcontrol = 0;
		data->commandline = readline(data->starttext);
		if (data->commandline == NULL)
			ifsendeof(data);
		if (check_quote(data->commandline, ft_strlen(data->commandline)) != 0)
		{
			while (check_quote(data->commandline, ft_strlen(data->commandline)))
			{
				data->templine = readline("> ");
				data->commandline = ft_strjoin(data->commandline,
						data->templine);
				free(data->templine);
			}
		}
		parser(data);
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