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
