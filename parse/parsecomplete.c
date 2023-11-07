/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecomplete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:43:56 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/07 19:27:25 by gotunc           ###   ########.fr       */
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
	if (src[0][0] && src[0][0] != '<' && src[0][0] != '>' && src[0][0] != '|')
		words = words_of_parts(src);
	else
		words = 1;
	dest = (char **)malloc(sizeof(char **) * words + 1);
	while (i < words)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int	countfrompars(void)
{
	char	**str;
	int		i;
	int		count;
	int		tru;

	tru = 1;
	count = 0;
	i = 0;
	str = g_data->arguments;
	while (str[i])
	{
		if ((str[i][0] == '|') || (str[i][0] == '>' || str[i][0] == '<'))
		{
			tru = 1;
			count++;
		}
		else if (tru == 1)
		{
			tru = 0;
			count++;
		}
		i++;
	}
	g_data->commandcount = count;
	return (count);
}

char	*lastparse2(char *str)
{
	if (ft_strcmp(str, "|"))
		return (ft_strdup("pipe"));
	else if (ft_strcmp(str, "<"))
		return (ft_strdup("simpleinput"));
	else if (ft_strcmp(str, "<<"))
		return (ft_strdup("multipleinput"));
	else if (ft_strcmp(str, ">"))
		return (ft_strdup("simpleoutput"));
	else if (ft_strcmp(str, ">>"))
		return (ft_strdup("multipleoutput"));
	return (NULL);
}


t_parse	*lastparse(void)
{
	t_parse	*last;
	char	**str;
	int		i;
	int		j;
	int		tru;

	tru = 1;
	j = 0;
	i = -1;
	str = g_data->arguments;
	last = (t_parse *)malloc(sizeof(t_parse) * countfrompars());
	while (str[++i])
	{
		if (str[i][0] == '|' || str[i][0] == '>' || str[i][0] == '<')
		{
			tru = 1;
			last[j].str = towdcopy(&str[i]);
			last[j].type = lastparse2(str[i]);
			printf("%s\n", last[j].type);
			j++;
		}
		else if (tru == 1)
		{
			tru = 0;
			last[j].str = towdcopy(&str[i]);
			last[j].type = ft_strdup("word");
			printf("%s\n", last[j].type);
			j++;
		}
	}
	return (last);
}
