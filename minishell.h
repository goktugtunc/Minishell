/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/28 14:58:36 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include "libft/libft.h"
# define True 1
# define False 0

typedef enum argmenttype{
	WORD,
	INPUT_RDR,
	OUTPUT_RDR,
	DOUBLE_OUTPUT_RDR,
	DOUBLE_INPUT_RDR,
	PIPE,
	DOLLAR
} argtype;

typedef struct arguments{
	char				*arg;
	argtype				type;
	struct arguments	*next;
} argstruct;

typedef struct s_lists{
	argstruct	**argument;// its enough to be char **argument;
	int			errorcontrol;
	int			containquote;
	char		*commandline;
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
int		lettercount(char *text, char letter);
int		parse(char *command, t_lists *data);
char	**copyenv(char **env);
void	ifSendEOF(t_lists *data);
int		check_quote(char *line);
int	check_quote1(t_lists *data);

#endif

//fork pipe fd[0] ve fd[1] öğren.