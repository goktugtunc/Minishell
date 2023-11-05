/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:03 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/05 19:18:50 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_of_str(char **argu)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(argu[i])
	{
		i++;
	}
	return (i);
}

char **ft_towDcopy(char **src)
{
	char	**dest;
	int		i;
	int		words;

	i = 0;
	words = count_of_str(src);
	dest = (char **)malloc(sizeof(char **) * words + 1);
	while(i < words)
	{
		dest[i] = ft_strdup(src[i]); 
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char *get_the_path(char **env, char *str)
{
	char **splited_path;
	int i;
	char *check;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i] ,"PATH", 4) == 0)
			splited_path = ft_towDcopy(ft_split(env[i] + 5, ':'));
		i++;
	}
	i = 0;
	while (splited_path[i])
	{
		check = ft_strjoin(splited_path[i], "/");
		check = ft_strjoin(check, str);
		if (access(check, F_OK | X_OK) == 0)
			return (check);
		free(check);
		i++;
	}
	return (NULL);
}

void	ft_chiled(char **str)
{
	int chiled;
	chiled = fork();
	if (chiled == 0)
		{
			if (execve(get_the_path(g_data->envp, str[0]), str, g_data->envp) == -1)
			{
				printf("-bash: %s: command not found\n", str[0]);
				exit (0);
			}
			//
		}
		wait(NULL);
}

void	echocommand(char **str)
{
	print_twodstr(&str[1]);
}
void	decisionmechanism(char **str)
{
	if (ft_strcmp(str[0], "cd") == 0)
		cdcommand(str);
	else if (ft_strcmp(str[0], "echo") == 0)
		echocommand(str);
	else if (ft_strcmp(str[0], "env") == 0)
		envcommand(str);
	//else if (ft_strcmp(str[0], "exit") == 0)
	//	exitcommand(str);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand();
	else
		ft_chiled(g_data->parts[0].str);
	//else if (ft_strcmp(str[0], "unset") == 0) // goktug tarafından yapılacak
	//	unsetcommand(str);
	//else
	//	normalcommands(str);
}
void pipecommand()
{
	int fds[2];
	int chiled;
	pipe(fds);
	chiled = fork();
	if (chiled == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		decisionmechanism(g_data->parts[0].str);
		exit(0);			
	}
	dup2(fds[0], 0);
	close(fds[1]);
	if (execve(get_the_path(g_data->envp, g_data->parts[2].str[0]), g_data->parts[2].str, g_data->envp) == -1)
	{
		printf("-bash: %s: command not found\n", g_data->parts[2].str[0]);
		exit (0);
	}	
}

void	ft_chiledforpipe(void)
{
	int chiled;
	chiled = fork();
	if (chiled == 0)
			pipecommand();	
		wait(NULL);
}

void	startprogram(void)
{
	while (TRUE)
	{
		g_data->errorstatus = 0;
		g_data->commandline = readline(g_data->starttext);
		if (g_data->commandline == NULL)
			ifsendeof();
		quoteerror();
		if (g_data->commandline && g_data->commandline[0])
			add_history(g_data->commandline);
		if (g_data->errorstatus == 0 && g_data->commandline[0] != '\0')
		{
			parser();
			g_data->parts = lastparse();
			if (g_data->commandcount > 1)
			{
				ft_chiledforpipe();
			}
			else if(g_data->commandline)
			{
				decisionmechanism(g_data->parts[0].str);
			}
			// find path ekledim bu sayede çalışacak komutun hangi yolda olduğunu
			// ve böyle bir komutun olup olmadığını bulabiliriz
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

//asdas>asdasd 3  asdas , > , asdasd
//"asdasd>asdasd" 1  "asdasd>asdasd"
//"asdas>"asdasda 1  "asdas>"asdasda 
//"asdas>">>sdasas 3 "asdas>" , >> , sdasas
//asdas ">>""<<"<'>' 4  asdas , ">>""<<" , < , '>'
//>>>>> 3  >> , >> , >

//asdsd  >  "askdasj"  3