#include "minishell.h"

void pipecommand(void)
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
