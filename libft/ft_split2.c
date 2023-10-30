/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:49:22 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/28 18:39:49 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h> 
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
int ft_quote(char *s, int quote, char ***result, int *x)
{
	int j;
	int i;

	i = *x;
	j = 0;
	if (*s == '\"' && quote)
	{
		s++;
		j= 0;
		while (s[j] != '\"')
			j++;
		(*result)[i++] = ft_substr(s, 0, j);
		*x = i;
		return (j + 1);
	}
	if (*s == '\'' && quote)
	{
		s++;
		j= 0;
		while (s[j] != '\'')
			j++;
		(*result)[i++] = ft_substr(s, 0, j);
		*x = i;
		return (j + 1);
	}
	*x= i;
	return (j);
}
char	**ft_split2(char *s, char c, int quote)
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
	j = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		j = 0;
		if (s[j] == '\"' || s[j] == '\'')
		{
			s += (ft_quote(s, quote, &result, &i) + 1);
			if (!(*s))
				break;
		}
		else 
		{
			j = 0;
			if (s[j] != c && s[j] && (s[j] != '\"' && s[j] != '\''))
			{
				while (s[j] != c && s[j] && (s[j] != '\"' && s[j] != '\''))
					j++;
				result[i++] = ft_substr(s, 0, j);
			}
			else 
				j++;
			if (s[j] == 0)
				break;
			s += j;
		}
	}
	result[i] = NULL;
	return (result);
}
