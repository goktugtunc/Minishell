/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/06 21:36:26 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define TRUE 1
# define FALSE 0

typedef struct s_parse
{
	char	**str;
	char	*type;
}	t_parse;

typedef enum argumenttype{
	WORD,
	INPUT_RDR,
	OUTPUT_RDR,
	DOUBLE_OUTPUT_RDR,
	DOUBLE_INPUT_RDR,
	PIPE,
	DOLLAR
}	t_argtype;

typedef struct arguments{
	char				*arg;
	t_argtype			type;
	struct arguments	*next;
}	t_argstruct;

typedef struct s_data{
	t_argstruct	**argument;// its enough to be char **argument;
	t_parse		*parts;
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
void	print_twodstr(char **str);
int		parserlongcontroller(int i);
int		ifmultiquote(char *a, int i, int *j);
int		ifsinglequote(char *a, int i, int *j);
int		pipecontrol(char *a, int i);
t_parse	*lastparse(void);
void	freeendwhile(void);
void	quoteerror(void);
int		commandpointerlen(char **d);
void	cdcommand(char **a);
void	pwdcommand(void);
int		findpathindex(char *searchedpath);
int		findenvpindex(char *searchedenvp, int searchindex);
int		lastarg(char **a);
void	envcommand(char **str);
void	exportcommand(char **str);
char	**adddoublepointer(char **dp, char *add);
char	**removedoublepointerarg(char **dp, int	i);
void	pipecommand(void);
void	ft_chiledforpipe(void);
void	echocommand(char **str);
void	ft_chiled(char **str);
char *get_the_path(char **env, char *str);
void	decisionmechanism(char **str);
#endif

//fork pipe fd[0] ve fd[1] öğren.