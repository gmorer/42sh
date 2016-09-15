/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:25:45 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/15 17:55:22 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct		s_data
{
	char		*name;
	char		*full_path;
}			t_data;

typedef struct		s_binary
{
	t_data		*data;
	struct s_binary *next;
}			t_binary;

int		ft_count_binary(char **env);
char	*ft_give_path(char *name, t_binary **table, char **env);
int		ft_free_hash_tab(char **env, t_binary ***table);
int		ft_show_hash_tab(char **env, t_binary **table);
t_binary	**ft_init_hash_table(char ***env);
int		ft_hash_algo(char *str, char **env);
int		ft_checklink(char *path);
int		ft_redirect(char **str, char ***env, t_binary ***table);
char	**ft_shlvl(char **env);
int		ft_echo(char **argv);
char	*charadd(char *str, char c);
char	*argvtest(char *str, char **env);
void	prompt(char **env, int returnvalue);
int		ft_setenv(char	**argv, char ***env);
int		ft_cd(char **argv, char ***env);
char	**ft_strstrdelone(int i, char **str)	;
char	**ft_strstradd(char *str, char **argv);
char	**argvsplit(char *argv);
char	*rmchar(char *str, char c);
char	**argvclean(char **argv, char **env);
char	*getenvline(char **env, char *argv);
char	**getline(char **env, char *argv);
int		casenofor(char **env, char *argv);
int		redirectfunction_builtin(char **argv, char ***env, t_binary ***table);
void	ft_strstrfree(char **str);
int		ft_exec(char *bin, char **temp, char ***env);
char	*toexec(char **env, char *argv);
size_t	ft_strstrlen(char **c);
char	**ft_strstrnew(size_t i);
char	**ft_strstrjoin(char **s1, char **s2);
char	**ft_strstrdup(char **tab);
#endif
