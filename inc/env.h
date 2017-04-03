/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:23:34 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/01 11:45:40 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "builtin.h"
# include "shell.h"
# include "env.h"
# include "exec.h"

# define OSX_PATH "/etc/paths"
# define LINUX_PATH "/etc/login.defs"
# ifdef __APPLE__
#  define LINUX 0
# endif
# ifndef __APPLE__
#  define LINUX 1
# endif

typedef struct	s_option
{
	int			opt_i;
	int			opt_p;
	int			opt_s;
	int			opt_u;
	int			opt_v;
}				t_option;

int				get_next_line(int fd, char **temp);
char			**ft_shlvl(char **env);
char			**init_env(char **environ);
int				ft_isin(char *str, char c);
int				casenofor(char *argv);
char			*rmno(char *str, int x);
char			*getenvline(char *argv);
int				option_i(char **argv, t_detail *node);
int				option_u(char **argv);
int				option_v(char **argv, t_detail *node, int i);
int				no_option(char **argv, t_detail *node, int j);
void			show_env(void);
int				free_hist(t_hist *hist);
int				free_shell(t_shell **g_shell);
int				free_cursor(t_cursor *cursor);

#endif
