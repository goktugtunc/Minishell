/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecomplete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:43:56 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/14 02:00:12 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	words_of_parts(char **argu)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (argu[i])
	{
		if (argu[i][0] == '|' || argu[i][0] == '<' || argu[i][0] == '>')
			return (count);
		i++;
		count++;
	}
	return (count);
}

char	**towdcopy(char **src)
{
	char	**dest;
	int		i;
	int		words;

	i = 0;
	 //&& src[0][0] != '<' && src[0][0] != '>' 
	if (src[0][0] && src[0][0] != '|' && src[0][0] != '<' && src[0][0] != '>')
		words = words_of_parts(src);
	else if((src[0][0] == '<' || src[0][0] == '>') && src[1] && src[1][0] != '<' && src[1][0] != '>' )
		words = 2;
	else
		words = 1;
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int	countfrompars(t_data *data)
{
	char	**str;
	int		i;
	int		count;
	int		tru;

	tru = 1;
	count = 0;
	i = 0;
	str = data->arguments;
	data->commandcount = 0;
	while (str[i])
	{
		if ((str[i][0] == '|') || (str[i][0] == '>' || str[i][0] == '<'))
		{
			if (str[i][0] == '|')
				data->commandcount++;
			else if (str[i + 1])
			{
				i++;
				data->commandcount--;
			}
			tru = 1;
			count++;
		}
		else if (tru == 1)
		{
			tru = 0;
			count++;
			data->commandcount++;
		}
		i++;
	}
	return (count);
}

char	*lastparse2(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (ft_strdup("pipe"));
	else if (!ft_strcmp(str, "<"))
		return (ft_strdup("simpleinput"));
	else if (!ft_strcmp(str, "<<"))
		return (ft_strdup("multipleinput"));
	else if (!ft_strcmp(str, ">"))
		return (ft_strdup("simpleoutput"));
	else if (!ft_strcmp(str, ">>"))
		return (ft_strdup("multipleoutput"));
	return (NULL);
}

t_parse	*lastparse(char **str, int tru, int i, t_data *data)
{
	t_parse	*last;
	int		j;

	j = 0;
	last = (t_parse *)malloc(sizeof(t_parse) * (countfrompars(data) + 1));
	while (str[++i])
	{
		if (str[i][0] == '|' || str[i][0] == '>' || str[i][0] == '<')
		{
			tru = 1;
			last[j].str = towdcopy(&str[i]);
			last[j].type = lastparse2(str[i]);
			j++;
		}
		else if (tru == 1)
		{
			tru = 0;
			last[j].str = towdcopy(&str[i]);
			last[j].type = ft_strdup("word");
			j++;
		}
		if ((str[i][0] == '>' || str[i][0] == '<') && str[i + 1] && str[i + 1][0] != '<' &&
			str[i + 1][0] != '>')
			i++;
	}
	last[j].type = NULL;
	return (last);
}
