/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/10 16:51:37 by gotunc           ###   ########.fr       */
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
	int			j;
}	t_data;

t_data			*g_data;

char	*getpcname(void);
void	findstarttext(char *pcname);
int		findpath(char *searchedpath);
void	initializefunction(char **envp, int argc, char **argv);
void	ifsendsigint(int signal);
void	ft_error(char *a);
char	**copyenv(char **env);
void	ifsendeof(void);
int		check_quote(char *line, int control);
void	parser(void);
void	print_twodstr(char **str, int flagcontrol);
int		parserlongcontroller(int i);
int		ifmultiquote(char *a, int i, int *j);
int		ifsinglequote(char *a, int i, int *j);
int		pipecontrol(char *a, int i);
t_parse	*lastparse(char **str, int tru, int i);
void	freeendwhile(void);
void	quoteerror(void);
int		commandpointerlen(char **d);
void	cdcommand(char **a);
void	pwdcommand(void);
int		findpathindex(char *searchedpath);
int		findenvpindex(char *searchedenvp, int searchindex);
int		findenvpindex2(char *searchedenvp);
int		lastarg(char **a);
void	envcommand(char **str);
void	exportcommand(char **str, int i, int error);
char	**adddoublepointer(char **dp, char *add);
char	**removedoublepointerarg(char **dp, int i);
void	echocommand(char **str);
void	ft_chiled(char **str);
char	*get_the_path(char **env, char *str);
void	decisionmechanism(char **str);
int		exportparser(char *str);
int		findexportindex(char *searchedenvp, int searchindex);
void	unsetcommand(char **str);
void	exitcommand(void);
char	*simpleinputcommand1(int i);
char	*simpleoutputcommand1(int i);
void	transformdollar(t_data *data);
void	ifsendsigquit(int signal);
int		pipecommand(char **s1, char **s2, int i);
int		ft_chiledforpipe(char **str1, char **str2);
void	echocommand(char **str);
void	ft_chiled(char **str);
char	*get_the_path(char **env, char *str);
void	decisionmechanism(char **str);
void	ft_dorequire(void);
void	ft_odd_right_redirection(char *str);
void	ft_odd_left_redirection(void);
void	commandfinder(void);
char	*removequotes2(char *str);
void	removequotes(t_data *data);
int		echonflagcontroller(char *str);
//void	goheredoc(char **str);
void	findwildcard(t_data *data);

#endif