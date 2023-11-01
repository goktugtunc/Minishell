/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 15:15:47 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	startprogram(t_lists *data)
{
	t_parse *parts = NULL;

	while (TRUE)
	{
		data->errorcontrol = 0;
		data->commandline = readline(data->starttext);
		if (data->commandline == NULL)
			ifSendEOF(data);
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
		parts = lastparse(data);
		print_twoDstr(parts[0].str);
		printf("%s\n", parts[0].type);
		print_twoDstr(parts[1].str);
		printf("%s\n", parts[1].type);

		print_twoDstr(parts[2].str);
		printf("%s\n", parts[2].type);

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