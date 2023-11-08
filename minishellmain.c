/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/08 04:13:03 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decisionmechanism(char **str)
{
	if (ft_strcmp(str[0], "cd") == 0)
		cdcommand(str);
	else if (ft_strcmp(str[0], "echo") == 0)
		echocommand(str);
	else if (ft_strcmp(str[0], "env") == 0)
		envcommand(str);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str, 0, 0);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand();
	else if (ft_strcmp(str[0], "unset") == 0)
		unsetcommand(str);
	else if (ft_strcmp(str[0], "exit") == 0)
		exitcommand();
	else
		ft_chiled(str);
}

//void	commandfinder(void)
//{
//	int	i;

//	i = 0;
//	if (g_data->parts[i].type == "word" && g_data->parts[i + 1].type == "pipe" && g_data->parts[i + 2].type == "word")
//	{
//	}
//}

char	*dollarfill(char *str, int startindex, int endindex)
{
	char	*temp;
	int		i;
	int		j;

	i = startindex;
	j = 0;
	temp = malloc(sizeof(char) * (endindex - startindex + 1));
	while (i < endindex)
	{
		temp[j++] = str[i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*addstring(char *str, int startindex, int endindex, char *addstr)
{
	char	*firststr;
	char	**temp;
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
	if (findenvpindex(addstr + 1, ft_strlen(addstr) - 1) != -1)
		temp = ft_split(g_data->envp[findenvpindex(addstr + 1, ft_strlen(addstr) - 1)], '=');
	else
	{
		temp = NULL;
	}
	return (ft_strjoin(ft_strjoin(firststr, temp[1]), thirdstr));
}

void	ifindollar(void)
{
	int		i;
	int		j;
	int		m;
	char	*temp;

	i = 0;
	j = 0;
	m = 0;
	while (g_data->arguments[i])
	{
		j = 0;
		while (g_data->arguments[i][j])
		{
			if (g_data->arguments[i][j] == '$')
			{
				m = j + 1;
				while (!ft_isdigit(g_data->arguments[i][j + 1]) && (ft_isalnum(g_data->arguments[i][m]) || g_data->arguments[i][m] == '_') && g_data->arguments[i][m])
					m++;
				temp = dollarfill(g_data->arguments[i], j, m);
				g_data->arguments[i] = addstring(g_data->arguments[i], j, m, temp);
				printf("%s\n", g_data->arguments[i]);
				j = m;
			}
			else
				j++;
		}
		i++;
	}
}

void	startprogram(void)
{
	while (1)
	{
		g_data->errorstatus = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
			ifsendeof();
		quoteerror();
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			if (g_data->commandline)
				add_history(g_data->commandline);
			parser();
			ifindollar(); // burada dolar işlemlerini yapıyorum ancak şuanda doğru çalışmıyor. ft_strlen kadar yollamaktansa yeni bir fonksiyon ile stringin eşittirden öncekinin tamamıyla kıyaslamam lazım. $$ ve $? işaretlerini kontrol etmeliyim.
			g_data->parts = lastparse(g_data->arguments, 1);
			//commandfinder(); Bu fonksiyonda teker teker argümanları pipe input ya da output olma durumuna göre yönlendireceğim.
			if (g_data->commandcount > 1)
			{
				ft_chiledforpipe();
			}
			else if (g_data->commandline)
			{
				decisionmechanism(g_data->parts[0].str);
			}
			freeendwhile();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	initializefunction(envp, argc, argv);
	startprogram();
	return (0);
}
