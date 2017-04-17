/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:27:20 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 19:54:51 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lex_par_ast.h"

# define BAD_OPT -1
# define OPT_L 0
# define OPT_P 1

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
int				check_variable(char *var);
int				special_char(char *str, char **res, int *k, int *i);
int				err_msg(char *str, int error, int type);
char			*clear_path(char *path);
void			replace_env(char *type, char *type2, char *content);
int				get_opt(char **argv, int *i, int *error);

#endif
