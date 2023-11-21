/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecomplete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:43:56 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/21 21:59:46 by amonem           ###   ########.fr       */
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
	if (src[0][0] && src[0][0] != '|' && src[0][0] != '<' && src[0][0] != '>')
		words = words_of_parts(src);
	else if ((src[0][0] == '<' || src[0][0] == '>') && src[1])
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

int	countfrompars(t_data *data, int i, int count, int tru)
{
	char	**str;

	str = data->arguments;
	while (str[++i])
	{
		if ((str[i][0] == '|') || (str[i][0] == '>' || str[i][0] == '<'))
		{
			if (str[i][0] == '|')
				data->commandcount++;
			else if (str[i + 1])
				i++;
			tru = 1;
			count++;
		}
		else if (tru == 1)
		{
			tru = 0;
			count++;
			data->commandcount++;
		}
	}
	return (count);
}

char	*lastparse_define_type(char *str)
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

// void join_redirection(t_lastparse *l)
// {
// 	t_lastparse lp;

// 	lp = *l;
// 	lp.last[lp.j - 1].red[lp.z].str = ft_strjoin2(lp.str[lp.i], lp.str[lp.i + 1]);
// 	lp.last[lp.j - 1].red[lp.z].type = lastparse_define_type(lp.str[lp.i]);
// 	lp.z++;
// }

// void init_parse_pipe(t_lastparse *l)
// {
// 	t_lastparse lp;

// 	lp = *l;
// 	if (check_redir(&((lp.str)[lp.fpi])))
// 		lp.last[lp.j - 1].red[lp.z].type = NULL;
// 	lp.fpi = lp.i + 1;
// 	lp.tru = 1;
// 	lp.last[lp.j].red = NULL;
// 	lp.last[lp.j].str = towdcopy(&(lp.str[lp.i]));
// 	lp.last[lp.j++].type = lastparse_define_type(lp.str[lp.i]);
// }

// void	last_parseinit(t_lastparse *l)
// {
// 	t_lastparse lp;

// 	lp = *l;
// 	while ((lp.str)[++(lp.i)])
// 	{
// 		if ((lp.str)[lp.i][0] == '|')
// 			init_parse_pipe(&lp);
// 		else if ((lp.str[lp.i][0] == '>' || lp.str[lp.i][0] == '<')
// 			&& lp.str[lp.i + 1] && check_redir(&(lp.str[lp.fpi])))
// 		{
// 			if (lp.tru == 1)
// 			{
// 				lp.last[lp.j].red = malloc(sizeof(t_red)
// 						* (count_redir(&((lp.str)[lp.fpi])) + 1));
// 				lp.tru = 0;
// 				lp.z = 0;
// 				lp.last[lp.j].str = with_out_redir(&(lp.str[lp.fpi]), lp.i);
// 				(lp.last)[lp.j++].type = ft_strdup("word");
// 			}
// 			join_redirection(&lp);
// 		}
// 		else if (lp.tru == 1 && !check_redir(&(lp.str[lp.fpi])))
// 		{
// 			lp.tru = 0;
// 			lp.last[lp.j].red = NULL;
// 			lp.last[lp.j].str = towdcopy(&(lp.str[lp.i]));
// 			lp.last[lp.j++].type = ft_strdup("word");
// 		}
// 	}
// 	(lp.last)[lp.j].type = NULL;
// 	if (check_redir(&((lp.str)[lp.fpi])))
// 		(lp.last)[lp.j - 1].red[lp.z].type = NULL;
// }

// t_parse	*lastparse(char **str, int tru, int i, t_data *data)
// {
// 	t_lastparse lp;
// 	t_parse	*last;
// 	int		j;
// 	int		z;
// 	int		fpi;

// 	fpi = 0;
// 	z = 0;
// 	j = 0;
// 	last = malloc(sizeof(t_parse) * (countfrompars(data, -1, 0, 1) + 1));
// 	lp.i = i;
// 	lp.j = j;
// 	lp.z = z;
// 	lp.last = last;
// 	lp.fpi = fpi;
// 	lp.tru = tru;
// 	lp.str = str;
// 	last_parseinit(&lp);
// 	last = lp.last;
// 	return (last);
// }


// t_parse	*lastparse(char **str, int tru, int i, t_data *data)
// {
// 	t_parse	*last;
// 	int		j;
// 	int		z;
// 	int		fpi;

// 	fpi = 0;
// 	z = 0;
// 	j = 0;
// 	last = malloc(sizeof(t_parse) * (countfrompars(data, -1, 0, 1) + 1));
// 	while (str[++i])
// 	{
// 		if (str[i][0] == '|')
// 		{
// 			if (check_redir(&str[fpi]))
// 				last[j - 1].red[z].type = NULL;
// 			fpi = i + 1;
// 			tru = 1;
// 			last[j].str = towdcopy(&str[i]);
// 			last[j].type = lastparse_define_type(str[i]);
// 			j++;
// 		}
// 		else if ((str[i][0] == '>' || str[i][0] == '<')
// 			&& str[i + 1] && check_redir(&str[fpi]))
// 		{
// 			if (tru == 1)
// 			{
// 				last[j].red = malloc(sizeof(t_red)
// 						* (count_redir(&str[fpi]) + 1));
// 				tru = 0;
// 				z = 0;
// 				last[j].str = with_out_redir(&str[fpi], i);
// 				last[j].type = ft_strdup("word");
// 				j++;
// 			}
// 			last[j - 1].red[z].str = ft_strjoin2(str[i], str[i + 1]);
// 			last[j - 1].red[z].type = lastparse_define_type(str[i]);
// 			z++;
// 		}
// 		else if (tru == 1 && !check_redir(&str[fpi]))
// 		{
// 			tru = 0;
// 			last[j].red = NULL;
// 			last[j].str = towdcopy(&str[i]);
// 			last[j].type = ft_strdup("word");
// 			j++;
// 		}
// 	}
// 	last[j].type = NULL;
// 	if (check_redir(&str[fpi]))
// 		last[j - 1].red[z].type = NULL;
// 	return (last);
// }


