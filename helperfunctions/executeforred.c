/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeforred.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:42:59 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:51:09 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**with_out_redir(char **str, int x)
{
	char	**new;
	int		i;
	int		j;

	j = 0;
	x = 0;
	i = 0;
	new = (char **)malloc(sizeof(char *) * words_of_parts_outredir(str) + 1);
	while (str[i] && str[i][0] != '|')
	{
		if (str[i][0] != '<' && str[i][0] != '>')
		{
			new[j] = ft_strdup(str[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

int	check_redir(char **str)
{
	int	i;

	i = 0;
	while (str[i] && str[i][0] != '|')
	{
		if (str[i][0] == '<' || str[i][0] == '>'
			|| !ft_strcmp(str[i], "simpleoutput")
			|| !ft_strcmp(str[i], "simpleinput")
			|| !ft_strcmp(str[i], "multipleoutput")
			|| !ft_strcmp(str[i], "multipleinput"))
			return (1);
		i++;
	}
	return (0);
}

void	ft_input_all(t_parse *part, t_data *data)
{
	int	i;

	if (check_redir(data->arguments) && part->red)
	{
		i = red_len(part->red);
		while (i + 1)
		{
			if (part->red[i].str[0] == '<' && part->red[i].str[1] == '<')
			{
				ft_multiple_left_redirection(&(part->red[i].str[2]),
					data, part);
				return ;
			}
			else if (part->red[i].str[0] == '<')
			{
				ft_odd_left_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			i--;
		}
	}
	decisionmechanism(part[0].str, data);
}

void	ft_output_all(t_parse *part, t_data *data)
{
	int	i;

	if (check_redir(data->arguments) && part->red)
	{
		i = red_len(part->red);
		while (i + 1)
		{
			if (part->red[i].str[0] == '>' && part->red[i].str[1] == '>')
			{
				ft_multiple_right_redirection(&(part->red[i].str[2]),
					data, part);
				ft_sub_output(part, i - 1);
				return ;
			}
			else if (part->red[i].str[0] == '>')
			{
				ft_odd_right_redirection(&(part->red[i].str[1]), data, part);
				ft_sub_output(part, i - 1);
				return ;
			}
			i--;
		}
	}
	ft_input_all(part, data);
}
