/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/02 14:26:13 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startprogram(void)
{
	while (TRUE)
	{
		g_data->errorcontrol = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
			ifsendeof();
		if (check_quote(g_data->commandline,
				ft_strlen(g_data->commandline)) != 0)
		{
			while (check_quote(g_data->commandline,
					ft_strlen(g_data->commandline)))
			{
				g_data->templine = readline("> ");
				g_data->commandline = ft_strjoin(g_data->commandline,
						g_data->templine);
				free(g_data->templine);
			}
		}
		//add_history(g_data->commandline); geçmişe kullanılan komutu ekler ama sıkıntıları var
		parser();
		g_data->parts = lastparse();
		// find path ekledim bu sayede çalışacak komutun hangi yolda olduğunu
		// ve böyle bir komutun olup olmadığını bulabiliriz
		free(g_data->arguments);
		if (g_data->errorcontrol == 0)
		{
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	initializefunction(envp, argc, argv);
	startprogram();
	return (0);
}

//asdas>asdasd 3  asdas , > , asdasd
//"asdasd>asdasd" 1  "asdasd>asdasd"
//"asdas>"asdasda 1  "asdas>"asdasda 
//"asdas>">>sdasas 3 "asdas>" , >> , sdasas
//asdas ">>""<<"<'>' 4  asdas , ">>""<<" , < , '>'
//>>>>> 3  >> , >> , >

//asdsd  >  "askdasj"  3