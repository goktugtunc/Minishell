/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gotunc <gotunc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:35:12 by gotunc            #+#    #+#             */
/*   Updated: 2023/10/17 01:14:40 by gotunc           ###   ########.fr       */
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
	char	*path;
	char	*username;
	char	*pcname;
	char	*starttext;
	int		argc;
	char	**argv;
	char	**envp;
}	t_lists;

char	*findpath(char **envp);
void	getusernameandpcname(t_lists *data);
void	findstarttext(t_lists *data);
void	controller(t_lists *data, char **envp, int argc, char **argv);
void	ifsendsigint(int signal);
void	ifsendsigkill(int signal);
void	ft_error(char *a);

#endif

//fork pipe fd[0] ve fd[1] öğren.