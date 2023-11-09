#include "minishell.h"

void pipecommand(char **s1, char **s2, int i, int j)
{
	int fds[2];
	int chiled;
	pipe(fds);
	chiled = fork();
	if (chiled == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		decisionmechanism(s1);
		close(fds[1]);
		exit(0);
	}
	close(fds[1]);
	wait(NULL);
	dup2(fds[0], 0);
	if (i > 1)
		pipecommand(g_data->parts[j + 2].str, g_data->parts[j + 4].str, i - 2, j + 2);
	else
		decisionmechanism(s2);
	close(fds[0]);
	exit(0);
}

void	ft_chiledforpipe(void)//////should give variable inside to index it 
{
	int chiled;

	chiled = fork();
	if (chiled == 0)
	{
		pipecommand(g_data->parts[0].str, g_data->parts[2].str, g_data->commandcount - 2, 0);
	}
	wait(NULL);
}

