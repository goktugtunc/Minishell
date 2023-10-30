/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/30 14:10:16 by amonem           ###   ########.fr       */
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

void	parse3(t_lists *data)
{
	char	*holeline;
	char	*firstpart;
	char	*secondpart;
	int	i;
	
	i = 0;
	if (check_quote1(data) != 0)
	{
		printf("\033[31;4mMinishell: Command is invalid: %s\n\033[0m", data->commandline);
		data->errorcontrol = 1;
		//return (0);
	}
	holeline = ft_strtrim(data->commandline, " ");
	while(holeline[i] && holeline[i] != '|' && holeline[i] != '<' && holeline[i] != '>')
		i++;
	firstpart = ft_substr(holeline, 0, i);
	data->my_first_commends = ft_split2(firstpart, ' ', data->containquote);
	if(holeline[i] == '|')
		i++;
	else if((holeline[i] == '<' && holeline[i + 1] == '<') || (holeline[i] == '>' && holeline[i + 1] == '>'))
		i++;
	
	if(holeline[i] == '<' || holeline[i] == '>')
		i++;
	secondpart = ft_substr(holeline, i, ft_strlen(holeline) - i);
	data->my_second_commends = ft_split2(secondpart, ' ', data->containquote);
	print_twoDstr(data->my_first_commends);
	print_twoDstr(data->my_second_commends);
}

void	startprogram(t_lists *data)
{
	while (True)
	{
		data->errorcontrol = 0;
		data->commandline = readline(data->starttext);
		if (data->commandline == NULL)//// what if the user entered nothing ?
			ifSendEOF(data);
		//parse(data->commandline, data);
		parse3(data);

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