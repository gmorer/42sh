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
# include "libft/libft.h"

size_t	ft_strstrlen(char **c);
char**	ft_strstrnew(size_t i);
char**	ft_strstrjoin(char **s1, char **s2);
char**	ft_strstrdup(char **tab);
char**	ft_strstrdelfirst(char **c);
#endif
