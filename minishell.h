/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/17 16:40:09 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

typedef struct s_parse
{
	char	**str;
	char	*type;
}	t_parse;

typedef struct s_data{
	t_parse		*parts;
	int			exitstatus;
	char		*commandline;
	char		*templine;
	char		**path;
	char		*foundedpath;
	char		**arguments;
	char		*simplestarttext;
	char		*starttext;
	char		**envp;
	char		**exportp;
	int			errorstatus;
	int			exportlen;
	int			commandcount;
	int			fderr;
	int			parsererrorcode;
}	t_data;

t_data			*g_data;

char	*getpcname(void);
void	findstarttext(char *pcname, t_data *data);
int		findpath(char *searchedpath, t_data *data);
void	initializefunction(char **envp, int argc, char **argv, t_data *data);
void	ifsendsigint(int signal);
void	ft_error(char *a);
char	**copyenv(char **env);
void	ifsendeof(t_data *data);
int		check_quote(char *line, int control);
void	parser(t_data *data);
void	print_twodstr(char **str, int flagcontrol);
int		parserlongcontroller(int i, t_data *data);
int		ifmultiquote(char *a, int i, int *j, t_data *data);
int		ifsinglequote(char *a, int i, int *j, t_data *data);
int		pipecontrol(char *a, int i, t_data *data);
t_parse	*lastparse(char **str, int tru, int i, t_data *data);
void	freeendwhile(t_data *data);
void	quoteerror(t_data *data);
int		commandpointerlen(char **d);
void	cdcommand(char **a, t_data *data);
void	pwdcommand(t_data *data);
int		findpathindex(char *searchedpath, t_data *data);
int		findenvpindex(char *searchedenvp, int searchindex, t_data *data);
int		findenvpindex2(char *searchedenvp, t_data *data);
int		lastarg(char **a);
void	envcommand(t_data *data);
void	exportcommand(char **str, int i, int error, t_data *data);
char	**adddoublepointer(char **dp, char *add);
char	**removedoublepointerarg(char **dp, int i);
void	echocommand(char **str);
char	*get_the_path(char **env, char *str, t_data *data);
int		exportparser(char *str);
int		findexportindex(char *searchedexportp, int searchindex, t_data *data);
void	unsetcommand(char **str, t_data *data);
void	exitcommand(void);
char	*simpleinputcommand1(int i, t_data *data);
char	*simpleoutputcommand1(int i, t_data *data);
void	transformdollar(t_data *data);
void	ifsendsigquit(int signal);
void	pipecommand(t_parse *part1, t_parse *part2, int i, t_data *data);
void	ft_chiledforpipe(t_parse *part1, t_parse *part2, t_data *data);
void	echocommand(char **str);
void	ft_chiled(char **str, t_data *data);
void	decisionmechanism(char **str, t_data *data);
void	ft_dorequire(void);
void	ft_odd_right_redirection(char *str, int i, t_data *data);
void	ft_odd_left_redirection(char *str, int i, t_data *data);
void	commandfinder(void);
char	*removequotes2(char *str);
void	removequotes(t_data *data);
int		echonflagcontroller(char *str);
void	ft_multiple_right_redirection(char *str, int i, t_data *data);
void	commandfinderother(t_parse *parts, t_data *data);
int		ifendispipe(t_data *data);
void	ifdoubleinput(t_data *data);
void	preparewhile(t_data *data);
void	freedoublepointer(char **str);

#endif