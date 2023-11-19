/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:04:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/19 13:34:36 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollarfill(t_data *data, int m, int startindex, int endindex)
{
	char	*temp;
	int		i;
	int		j;

	i = startindex;
	j = 0;
	temp = malloc(sizeof(char) * (endindex - startindex + 1));
	while (i < endindex)
	{
		temp[j++] = data->arguments[m][i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*addstring(int argi, int startindex, int endindex, t_data *data)
{
	char	*firststr;
	char	*temp;
	char	*thirdstr;
	char	*addstr;
	int		i;

	addstr = dollarfill(data, argi, startindex, endindex);
	i = -1;
	firststr = malloc(sizeof(char) * (startindex + 1));
	thirdstr = malloc((ft_strlen(data->arguments[argi]) - endindex + 1));
	while (++i < startindex)
		firststr[i] = data->arguments[argi][i];
	firststr[i] = 0;
	i = 0;
	while (data->arguments[argi][endindex])
		thirdstr[i++] = data->arguments[argi][endindex++];
	thirdstr[i] = 0;
	if (findenvpindex2(addstr + 1, data) != -1)
		temp = ft_split(data->envp[findenvpindex2(addstr + 1, data)], '=')[1];
	else if (!ft_strcmp(addstr, "$?"))
		temp = ft_itoa(data->exitstatus);
	else
		temp = ft_strdup("\0");
	free(data->arguments[argi]);
	return (ft_strjoin(ft_strjoin(firststr, temp), thirdstr));
}

void	transformdollar2(t_data *data, int i, int m, int j)
{
	while (data->arguments[i][j])
	{
		if (data->arguments[i][j] == '$')
		{
			m = j + 1;
			if (data->arguments[i][m] == '?')
				m++;
			else if (ft_isdigit(data->arguments[i][m])
				|| (!ft_isalnum(data->arguments[i][m])
					&& data->arguments[i][m] != ' '))
				m++;
			else
			{
				while (!ft_isdigit(data->arguments[i][j + 1])
						&& (ft_isalnum(data->arguments[i][m])
							|| data->arguments[i][m] == '_')
						&& data->arguments[i][m])
					m++;
			}
			data->arguments[i] = addstring(i,
					j, m, data);
			j = m;
		}
		j++;
	}
}

void	addquote(char **arguments, int i)
{
	char	*temp;

	temp = ft_strjoin2("\"", arguments[i]);
	free(arguments[i]);
	arguments[i] = ft_strjoin(temp, "\"");
}

void	transformdollar(t_data *data, int quote)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (data->arguments[++i])
	{
		if (data->arguments[i][0] != '\''
			&& ft_strchr(data->arguments[i], '$'))
		{
			if (data->arguments[i][0] == '\"'
				|| data->arguments[i]
				[ft_strlen(data->arguments[i]) - 1] == '\"')
			{
				data->arguments[i] = ft_strtrim2(data->arguments[i], "\"");
				quote = 1;
			}
			transformdollar2(data, i, 0, 0);
			if (quote == 1)
				addquote(data->arguments, i);
		}
	}
}
