/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:25:45 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/25 15:27:51 by gmorer           ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/types.h>
# include <signal.h>
# include <termios.h>
# include <pwd.h>
# include <stdio.h>
# include <termios.h>
# include "libft.h"
# include "get_next_line.h"
# define OSX_PATH "/etc/paths"
# define LINUX_PATH "/etc/login.defs"
# ifdef __APPLE__
#  define LINUX 0
# endif
# ifndef __APPLE__
#  define LINUX 1
# endif

typedef struct	s_data
{
	char		*name;
	char		*full_path;
}			t_data;

typedef struct	s_binary
{
	t_data		*data;
	struct s_binary *next;
}			t_binary;

typedef struct	s_process
{
	struct s_process	*next;			/* next process in pipeline */
	char				**argv;			/* for exec */
	pid_t				pid;			/* process ID */
	char				completed;		/* true if process has completed */
	char				stopped;		/* true if process has stopped */
	int					status;			/* reported status value */
}				t_process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct s_job	*next;				/* next active job */
	char			*command;			/* command line, used for messages */
	t_process		*first_process;		/* list of processes in this job */
	pid_t			pgid;				/* process group ID */
	char			notified;			/* true if user told about stopped job */
	struct termios	tmodes;				/* saved terminal modes */
	int				stdin; 				/* standard i/o channels */
	int				stdout;
	int				stderr;
}				t_job;

typedef struct s_shell
{
	pid_t			pgid;
	struct termios	tmodes;
	int				terminal;
	int				is_interactive;
}				t_shell;

t_shell		*init_mainprocess(void);
t_binary	**ft_add_hash_to_tab(char *binary, char *path, t_binary **table, char **env);
char	*toexec(char **env, char *argv);
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
int		ft_setenv(char	**argv, char ***env, t_binary ***table);
int		ft_cd(char **argv, char ***env);
char	**ft_strstrdelone(int i, char **str)	;
char	**ft_strstradd(char *str, char **argv);
char	**argvsplit(char *argv);
char	*rmchar(char *str, char c);
char	**argvclean(char **argv, char **env);
char	*getenvline(char **env, char *argv);
char	**ft_save_env(char **env);
int		casenofor(char **env, char *argv);
int		redirectfunction_builtin(char **argv, char ***env, t_binary ***table);
void	ft_strstrfree(char **str);
int		ft_exec(char *bin, char **temp, char ***env);
char	*toexec(char **env, char *argv);
size_t	ft_strstrlen(char **c);
char	**ft_strstrnew(size_t i);
char	**ft_strstrjoin(char **s1, char **s2);
char	**ft_strstrdup(char **tab);
int		ft_signal();
char	**init(char **oldenv);
int		uppercase(char *argv1, char *argv2, char *argv3);
#endif
