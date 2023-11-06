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
	int i;
	char *check;

	i = 0;
	(void)env;
	while (g_data->path[i])
	{
		check = ft_strjoin(g_data->path[i], "/");
		check = ft_strjoin(check, str);
		if (access(check, F_OK) == 0)
			return (check);
		else if (access(str, X_OK) == 0)
			return (str);
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
