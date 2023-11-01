/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 08:56:36 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	parse(char *command)
//{
//	int	i;
//	int	argcount;

//	i = -1;
//	argcount = 0;
//	if (lettercount(command, 34) % 2 != 0 || lettercount(command, 39) % 2 != 0)
//	{
//		printf("\033[31;4mMinishell: Command is invalid: %s\n\033[0m", command);
//		return (0);
//	}
//	while (command[++i])
//	{
//		while (command[i] == ' ')
//			i++;
//		if (command[i] == 34)
//		{
//			i++;
//			#pragma region eski_cifttirnakkontrol
//			//if (command[i - 1] == 34 && i > 0)
//			//	i++;
//			//if ((command[i - 1] == ' '
//			//	|| command[i - 1] == '>' || command[i - 1] == '<' || i == 0) && command[i - 1] != 34)
//			//	argcount++;
//			#pragma endregion
//			while (command[i++] != 34)
//				continue ;
//			if (command[i++] != 34)
//				argcount++;
//		}
//		if (command[i] == 39)
//		{
//			i++;
//			//if (command[i - 1] == ' '
//			//	|| command[i - 1] == '>' || command[i - 1] == '<' || i == 0)
//			//	argcount++;
//			while (command[i++] != 39)
//				continue ;
//			if (command[i++] != 39)
//				argcount++;
//		}
//		if (command[i] == '<')
//		{
//			if (command[i + 1] == '<')
//				i++;
//			argcount += 1;
//			i++;
//		}
//		if (command[i] == '>')
//		{
//			if (command[i + 1] == '>')
//				i++;
//			argcount += 1;
//			i++;
//		}
//		if ((i > 0 && (command[i - 1] == ' ' || command[i - 1] == '<' || command[i - 1] == '>') && ft_isprint(command[i])) || (i == 0 && ft_isprint(command[i])))
//			argcount++;
//	}
//	printf("%d\n", argcount);
//	return (1);
//}
//asdas ">>""<<"<'>'
// yukarıdaki parse eski parse dır. Belki ihtiyaç olursa kullanılabilir.

//int	parse2(char	*command, int i, int j, t_lists *data)
//{
//	while (command[i] == ' ')
//		i++;
//	if (command[i] == 34)
//	{
//		while (command[i] == 34)
//		{
//			i++;
//			while (command[i] != 34 && command[i])
//				data->tempstr[j++] = command[i++];
//			data->tempstr[j] = '\0';
//			data->newstr = ft_strjoin(data->newstr, data->tempstr);
//			j = 0;
//			i++;
//		}
//		i--;
//	}
//	else if (command[i] == 39)
//	{
//		while (command[i] == 39)
//		{
//			i++;
//			while (command[i] != 39 && command[i])
//				data->tempstr[j++] = command[i++];
//			data->tempstr[j] = '\0';
//			data->newstr = ft_strjoin(data->newstr, data->tempstr);
//			j = 0;
//			i++;
//		}
//		i--;
//	}
//	return (i);
//}

//int	parse(char *command, t_lists *data)
//{
//	int		i;
//	int		j;

//	i = 0;
//	j = 0;
//	if (check_quote(command) != 0)
//	{
//		printf("\033[31;4mMinishell: Command is invalid: %s\n\033[0m", command);
//		data->errorcontrol = 1;
//		return (0);
//	}
//	command = ft_strtrim(command, " ");
//	data->newstr = malloc((ft_strlen(command) + 1) * sizeof(char));
//	data->tempstr = malloc((ft_strlen(command) + 1) * sizeof(char));
//	while (command[i])
//	{
//		if (command[i] == ' ' || command[i] == 34 || command[i] == 39)
//			i = parse2(command, i, j, data);
//		else if (command[i] == '>')
//		{
//			if (command[i + 1] == '>')
//			{
//				data->newstr = ft_strjoin(data->newstr, ">>");
//				i++;
//			}
//			else
//				data->newstr = ft_strjoin(data->newstr, ">");
//		}
//		else if (command[i] == '<')
//		{
//			if (command[i + 1] == '<')
//			{
//				data->newstr = ft_strjoin(data->newstr, "<<");
//				i++;
//			}
//			else
//				data->newstr = ft_strjoin(data->newstr, "<");
//		}
//		// if ()
//		// {
//			while (command[i] != ' ' && command[i] != '<'
//				&& command[i] != '>' && command[i])
//				data->tempstr[j++] = command[i++];
//			data->tempstr[j] = '\0';
//			data->newstr = ft_strjoin(data->newstr, data->tempstr);
//			i--;
//		// }
//		data->newstr = ft_strjoin(data->newstr, " ");
//		i++;
//		j = 0;
//		printf("%s\n", data->newstr);
//	}
//	data->arguments = ft_split(data->newstr, ' ');
//	//printf("1%s\n", data->arguments[0]);
//	return (1);
//} // fonksiyon güçlendirilip hataları giderilecek!

//void	parse3(t_lists *data)
//{
//	int		i;
//	char	*holeline;
//	char	*firstpart;
//	char	*secondpart;

//	i = 0;
//	check_quote1(data);
//	holeline = ft_strtrim(data->commandline, " ");
//	while (holeline[i] && holeline[i] != '|' && holeline[i] != '<' && holeline[i] != '>')
//		i++;
//	firstpart = ft_substr(holeline, 0, i);
//	data->my_first_commends = ft_split2(firstpart, ' ', data->containquote);
//	if (holeline[i] == '|')
//		i++;
//	else if ((holeline[i] == '<' && holeline[i + 1] == '<') || (holeline[i] == '>' && holeline[i + 1] == '>'))
//		i++;
//	if (holeline[i] == '<' || holeline[i] == '>')
//		i++;
//	secondpart = ft_substr(holeline, i, ft_strlen(holeline) - i);
//	data->my_second_commends = ft_split2(secondpart, ' ', data->containquote);
//	print_twoDstr(data->my_first_commends);
//	print_twoDstr(data->my_second_commends);
//}

int	tektirnakvarsa(t_lists *data, char *a, int i);

int	cifttirnakvarsa(t_lists *data, char *a, int i)
{
	int	j;

	j = 0;
	while (data->commandline[i] && data->commandline[i] != ' ' && data->commandline[i] != '<' && data->commandline[i] != '>')
	{
		if (data->commandline[i] == '\"')
		{
			a[j++] = data->commandline[i++];
			while (data->commandline[i] != '\"' && data->commandline[i])
				a[j++] = data->commandline[i++];
			a[j++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<' || data->commandline[i] == '>' || !data->commandline[i])
			break ;
		while (data->commandline[i] && data->commandline[i] != ' ' && data->commandline[i] != '<' && data->commandline[i] != '>' && data->commandline[i] != '\"')
		{
			if (data->commandline[i] == '\'')
				i = tektirnakvarsa(data, a, i);
			else
				a[j++] = data->commandline[i++];
		}
	}
	a[j] = '\0';
	return (i);
}

int	tektirnakvarsa(t_lists *data, char *a, int i)
{
	int	j;

	j = 0;
	while (data->commandline[i] && data->commandline[i] != ' ' && data->commandline[i] != '<' && data->commandline[i] != '>')
	{
		if (data->commandline[i] == '\'')
		{
			a[j++] = data->commandline[i++];
			while (data->commandline[i] != '\'' && data->commandline[i])
				a[j++] = data->commandline[i++];
			a[j++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<' || data->commandline[i] == '>' || !data->commandline[i])
			break ;
		while (data->commandline[i] && data->commandline[i] != ' ' && data->commandline[i] != '<' && data->commandline[i] != '>' && data->commandline[i] != '\'')
		{
			if (data->commandline[i] == '\"')
				i = cifttirnakvarsa(data, a, i);
			else
				a[j++] = data->commandline[i++];
		}
	}
	a[j] = '\0';
	return (i);
}

int	kucukturvarsa(t_lists *data, char *a, int i, int m)
{
	a[1] = '\0';
	a[2] = '\0';
	if (data->commandline[i] == '<')
	{
		if (data->commandline[i + 1] == '<')
		{
			a[0] = '<';
			a[1] = '<';
			m = 2;
		}
		else
			a[0] = '<';
	}
	else
	{
		if (data->commandline[i + 1] == '>')
		{
			a[0] = '>';
			a[1] = '>';
			m = 2;
		}
		else
			a[0] = '>';
	}
	return (i + m);
}

int	elsedurumu(t_lists *data, char *a, int i)
{
	int		j;

	j = 0;
	while (data->commandline[i] && ((data->commandline[i] != ' '
				&& data->commandline[i] != '<' && data->commandline[i] != '>'
				&& check_quote(data->commandline, i) == 0)
			|| (check_quote(data->commandline, i) != 0)))
	{
		a[j++] = data->commandline[i++];
	}
	a[j] = '\0';
	return (i);
}

void	parser4(t_lists *data)
{
	int		i;
	int		argi;
	char	*a;

	i = 0;
	argi = 0;
	data->commandline = ft_strtrim(data->commandline, " ");
	data->arguments = malloc(5 * sizeof(char *));
	a = malloc(600);
	while (data->commandline[i])
	{
		if (data->commandline[i] == ' ')
			i++;
		else
		{
			if (data->commandline[i] == '\"')
				i = cifttirnakvarsa(data, a, i);
			else if (data->commandline[i] == '\'')
				i = tektirnakvarsa(data, a, i);
			else if (data->commandline[i] == '<' || data->commandline[i] == '>')
				i = kucukturvarsa(data, a, i, 1);
			else
				i = elsedurumu(data, a, i);
			data->arguments[argi++] = ft_strdup(a);
		}
	}
	data->arguments[argi] = NULL;
}
