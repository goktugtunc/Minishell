/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/21 16:42:20 by gotunc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include "libft/libft.h"

typedef struct s_lists{
	char	*allpath;
	char	**path;
	char	**arguments;
	char	*newstr;
	char	*tempstr;
	char	*username;
	int		commandcount;
	char	*pcname;
	char	*starttext;
	int		argc;
	char	**argv;
	char	**envp;
}	t_lists;

void	getusernameandpcname(t_lists *data);
void	findstarttext(t_lists *data);
void	initializefunction(t_lists *data, char **envp, int argc, char **argv);
void	ifsendsigint(int signal);
void	ft_error(char *a);
int		lettercount(char *text, char letter);
int		parse(char *command, t_lists *data);

#endif

//fork pipe fd[0] ve fd[1] öğren.