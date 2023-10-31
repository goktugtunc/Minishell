/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/31 16:35:16 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_twoDstr(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}
int	count_words_firstpart(char const *s)
{
	int	count;

	count = 0;
	while (*s && *s != '|' && *s != '<')
	{
		while (*s == ' ')
			s++;
		if (*s)
			count++;
		while (*s && *s != ' ' && *s != '|' && *s != '<' && *s != '>')
			s++;
	}
	return (count);
}
int	checkifquot(t_lists *data)
{
	char *str;
	int i;
	int checkquot;
	int checkapostroph;

	checkquot = 0;
	i = 0;
	checkapostroph = 0;
	str = ft_strtrim(data->commandline, " ");
	while(str[i])
	{
		if (str[i] == '\"')
		{
			while(str[i])
			{
				if (str[i] == '\"')
				i++;
			}
		}
		else if (str[i] == '\'')
			checkapostroph++;
		i++;
	}
	// ft_strtrim(data->commandline, " ");
	// if (ft_strchr(str, '\''))
	// 	return (1);
	// if (ft_strchr(str, '\"'))
	// 	return (1);
	 return (0);
}


void	startprogram(t_lists *data)
{
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
			printf("*%s\n", data->commandline);
		}
		//parse(data->commandline, data);
		parser4(data);
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