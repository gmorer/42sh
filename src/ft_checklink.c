#include "minishell.h"

int ft_checklink(char *path)
{
	struct stat tmp;

	lstat(path, &tmp);
	if (!(S_ISLNK(tmp.st_mode)))
		return (1);
	if (stat(path, &tmp) == -1)
		return (0);
	return (1);
}
