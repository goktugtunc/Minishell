/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:04:15 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/18 14:26:45 by gotunc           ###   ########.fr       */
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

char	*addstring(char *str, int startindex, int endindex, char *addstr, t_data *data)
{
	char	*firststr;
	char	*temp;
	char	*thirdstr;
	int		i;

	i = -1;
	firststr = malloc(sizeof(char) * (startindex + 1));
	thirdstr = malloc(sizeof(char) * (ft_strlen(str) - endindex + 1));
	while (++i < startindex)
		firststr[i] = str[i];
	firststr[i] = 0;
	i = 0;
	while (str[endindex])
		thirdstr[i++] = str[endindex++];
	thirdstr[i] = 0;
	if (findenvpindex2(addstr + 1, data) != -1)
		temp = ft_split(data->envp[findenvpindex2(addstr + 1, data)], '=')[1];
	else if (!ft_strcmp(addstr, "$?"))
		temp = ft_itoa(data->exitstatus);
	else
		temp = ft_strdup("\0");
	free(str);
	return (ft_strjoin(ft_strjoin(firststr, temp), thirdstr));
}

void	transformdollar2(t_data *data, char *temp, int i, int j)
{
	int	m;

	m = 0;
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
			temp = dollarfill(data, i, j, m);
			data->arguments[i] = addstring(data->arguments[i],
					j, m, temp, data);
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
	char	*temp;

	i = -1;
	j = 0;
	temp = NULL;
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
			transformdollar2(data, temp, i, 0);
			if (quote == 1)
				addquote(data->arguments, i);
		}
	}
}
