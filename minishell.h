/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/01 21:49:31 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include "libft/libft.h"
# define TRUE 1
# define FALSE 0

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

typedef struct s_lists{
	t_argstruct	**argument;// its enough to be char **argument;
	int			errorcontrol;
	int			containquote;
	char		*commandline;
	char		*templine;
	char		*redirections;
	char		**path;
	char		**arguments;
	char		**my_first_commends;
	char		**my_second_commends;
	char		**redirection;
	char		*newstr;
	char		*tempstr;
	char		*username;
	int			commandcount;
	char		*starttext;
	char		**envp;
}	t_lists;

char	*getpcname(void);
void	findstarttext(t_lists *data, char *pcname);
void	initializefunction(t_lists *data, char **envp, int argc, char **argv);
void	ifsendsigint(int signal);
void	ft_error(char *a);
char	**copyenv(char **env);
void	ifsendeof(t_lists *data);
int		check_quote(char *line, int control);
void	parser(t_lists *data);
void	print_twodstr(char **str);
int		parserlongcontroller(t_lists *data, int i);
int		ifmultiquote(t_lists *data, char *a, int i, int *j);
int		ifsinglequote(t_lists *data, char *a, int i, int *j);
int		pipecontrol(t_lists *data, char *a, int i);

#endif

//fork pipe fd[0] ve fd[1] öğren.