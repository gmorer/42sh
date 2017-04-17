/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:27:34 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/12 16:49:39 by rvievill         ###   ########.fr       */
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
int				option_i(char **argv, int i);
int				no_option(char **argv, int j);
void			show_env(void);
int				free_hist(t_hist *hist);
int				free_shell(t_shell **g_shell);
int				free_cursor(t_cursor *cursor);
char			**temp_env(char **env, char *str);
int				verif_opt(t_option comp);
void			print_arg(char **argv, int i);
char			*backslash(char *str, char *bs, int bs_nb);

#endif
