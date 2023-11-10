/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:10:23 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/10 17:39:37 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequotes2(char *str)
{
	int		i;
	int		status;
	char	*returnvalue;
	int		j;

	returnvalue = malloc(ft_strlen(str) + 1);
	status = 0;
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && status == 1)
			status = 0;
		else if (str[i] == '\"' && status == 0)
			status = 1;
		else if (str[i] == '\'' && status == 2)
			status = 0;
		else if (str[i] == '\'' && status == 0)
			status = 2;
		else
			returnvalue[j++] = str[i];
	}
	returnvalue[j] = 0;
	return (returnvalue);
}

void	removequotes(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	char	**returnvalue;

	i = 0;
	j = 0;
	returnvalue = malloc(sizeof(char *)
			* (commandpointerlen(data->arguments) + 1));
	while (data->arguments[i])
	{
		temp = data->arguments[i];
		returnvalue[i] = removequotes2(temp);
		free(temp);
		i++;
	}
	free(data->arguments[i]);
	free(data->arguments);
	returnvalue[i] = NULL;
	data->arguments = returnvalue;
}

int	echonflagcontroller(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

//void	goheredoc(char **str) // HEREDOC echo veya ls gibi şeyleri yazdırırken sıkıntı çıkarıyor düzeltilecek.
//{
//	char	*temp;
//	char	*returnval;

//	temp = NULL;
//	returnval = NULL;
//	while (1)
//	{
//		temp = readline("> ");
//		if (ft_strcmp(str[0], temp))
//		{
//			if (!returnval)
//				returnval = ft_strdup(temp);
//			else
//			{
//				returnval = ft_strjoin(returnval, "\n");
//				returnval = ft_strjoin(returnval, temp);
//			}
//			free(temp);
//		}
//		else
//			break ;
//	}
//	free(str[0]);
//	str[0] = returnval;
//}

char	**findfiles(void)
{
	char	*files;
	int		fd[2];
	pid_t	id;
	int		bytesread;

	files = malloc(999 * sizeof(char));
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/bin/ls",
			ft_split("ls", ' '), NULL);
	}
	else
	{
		wait(NULL);
		bytesread = read(fd[0], files, 999);
		if (bytesread == -1)
			ft_error("File read error!");
		files[bytesread] = '\0';
	}
	return (ft_split(files, '\n'));
}

void	changewildcard(t_data *data, int i, int len)
{
	char	**str;
	char	**temp;
	int		j;
	int		tempi;

	j = 0;
	tempi = i;
	temp = malloc(sizeof(char *) * (len - i));
	str = findfiles();
	free(data->arguments[tempi]);
	while (data->arguments[++tempi])
	{
		temp[j++] = ft_strdup(data->arguments[tempi]);
		free(data->arguments[tempi]);
	}
	temp[j] = NULL;
	j = -1;
	while (str[++j])
		data->arguments[i++] = ft_strdup(ft_strtrim(str[j], "\n"));
	j = 0;
	while (temp[j])
		data->arguments[i++] = ft_strdup(temp[j++]);
	data->arguments[i] = NULL;
}

void	findwildcard(t_data *data)
{
	int	i;

	i = 0;
	while (data->arguments[i])
	{
		if (!ft_strcmp(data->arguments[i], "*"))
			changewildcard(data, i, commandpointerlen(data->arguments));
		i++;
	}
}
