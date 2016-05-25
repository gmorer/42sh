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

char	*rmchar(char *str, size_t i);
char	**argvclean(char **argv, char **env);
char	*getenvline(char **env, char *argv);
char	**getline(char **env, char *argv);
int		casenofor(char **env, char *argv);
int		redirectfunction(char **argv, char **env);
void	ft_strstrfree(char **str);
int		ft_exec(char *bin, char **temp, char **env);
char	*toexec(char **env, char *argv);
size_t	ft_strstrlen(char **c);
char	**ft_strstrnew(size_t i);
char	**ft_strstrjoin(char **s1, char **s2);
char	**ft_strstrdup(char **tab);
char	**ft_strstrdelfirst(char **c);
#endif
