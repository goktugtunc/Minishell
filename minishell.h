/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goktugtunc <goktugtunc@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/26 00:21:54 by goktugtunc       ###   ########.fr       */
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
	argstruct	**argument;
	int			errorcontrol;
	char		*commandline;
	char		**path;
	char		**arguments;
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

#endif

//fork pipe fd[0] ve fd[1] öğren.