/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 02:18:40 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startprogram(t_lists *data)
{
	char	*command;

	while (1)
	{
		command = readline(data->starttext);
		if (command == NULL)
		{
			printf("\r%sExit!\n", data->starttext);	
			exit(1);
		}
		//parse(d);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lists	*data;

	data = malloc(sizeof(t_lists));
	signal(SIGINT, ifsendsigint);
	controller(data, envp, argc, argv);
	data->envp = envp;
	data->argv = argv;
	data->argc = argc;
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