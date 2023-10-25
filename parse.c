/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/25 20:36:58 by goktugtunc       ###   ########.fr       */
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

int	parse2(char	*command, int i, int j, t_lists *data)
{
	while (command[i] == ' ')
		i++;
	if (command[i] == 34)
	{
		while (command[i] == 34)
		{
			i++;
			while (command[i] != 34 && command[i])
				data->tempstr[j++] = command[i++];
			data->tempstr[j] = '\0';
			data->newstr = ft_strjoin(data->newstr, data->tempstr);
			j = 0;
			i++;
		}
		i--;
	}
	else if (command[i] == 39)
	{
		while (command[i] == 39)
		{
			i++;
			while (command[i] != 39 && command[i])
				data->tempstr[j++] = command[i++];
			data->tempstr[j] = '\0';
			data->newstr = ft_strjoin(data->newstr, data->tempstr);
			j = 0;
			i++;
		}
		i--;
	}
	return (i);
}

int	parse(char *command, t_lists *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (check_quote(command) != 0)
	{
		printf("\033[31;4mMinishell: Command is invalid: %s\n\033[0m", command);
		return (0);
	}
	command = ft_strtrim(command, " ");
	data->newstr = malloc((ft_strlen(command) + 1) * sizeof(char));
	data->tempstr = malloc((ft_strlen(command) + 1) * sizeof(char));
	while (command[i])
	{
		if (command[i] == ' ' || command[i] == 34 || command[i] == 39)
			i = parse2(command, i, j, data);
		else if (command[i] == '>')
		{
			if (command[i + 1] == '>')
			{
				data->newstr = ft_strjoin(data->newstr, ">>");
				i++;
			}
			else
				data->newstr = ft_strjoin(data->newstr, ">");
		}
		else if (command[i] == '<')
		{
			if (command[i + 1] == '<')
			{
				data->newstr = ft_strjoin(data->newstr, "<<");
				i++;
			}
			else
				data->newstr = ft_strjoin(data->newstr, "<");
		}
		else
		{
			while (command[i] != ' ' && command[i] != '<'
				&& command[i] != '>' && command[i])
				data->tempstr[j++] = command[i++];
			data->tempstr[j] = '\0';
			data->newstr = ft_strjoin(data->newstr, data->tempstr);
			i--;
		}
		data->newstr = ft_strjoin(data->newstr, " ");
		i++;
		j = 0;
		printf("%s\n", data->newstr);
	}
	data->arguments = ft_split(data->newstr, ' ');
	return (1);
} // fonksiyon güçlendirilip hataları giderilecek!
