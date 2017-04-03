/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:44:48 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/03 18:22:03 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lex_par_ast.h"

typedef struct	s_builtin
{
	char		*name;
	int			(*fbuiltin)(char **argv);

}				t_builtin;

int				builtin(t_detail *node);
int				ft_jobs(char **argv);
int				ft_cd(char **argv);
int				ft_fg(char **argv);
int				ft_bg(char **argv);
int				ft_hashtab(char **argv);
int				ft_unsetenv(char **argv);
int				ft_setenv(char **argv);
int				ft_exit(char **argv);
int				ft_echo(char **argv);
int				ft_env(char **argv);

#endif
