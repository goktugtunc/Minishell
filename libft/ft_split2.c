/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:54:31 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 12:09:44 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nailcounter(char *s, int i)
{
	int	counter;
	int	j;

	j = 0;
	counter = 0;
	while (s[i] && j < i)
	{
		if (s[i] == 34)
									// 01101101 --- 
									// 01101011 
									'm' & 1 != 'l' & 1 && i < 8
									m = m >> 1;
									n = 
									if ((c & 1) == 1)
		j++;
	}
}

int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		result[i++] = ft_substr(s, 0, j);
		s += j;
	}
	result[i] = NULL;
	return (result);
}
