/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/10 12:44:57 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"

static int	ft_checklink(char *path)
{
	struct stat tmp;

	if (stat(path, &tmp) == -1)
		return (0);
	return (1);
}

static char	*getexec(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*ofile;
	char			*tmp;
	char			*tmp1;

	(void)file;
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	tmp1 = NULL;
	while ((ofile = readdir(dir)) && (ft_strcmp(ofile->d_name, file) ||
				ft_checklink((tmp1 = ft_strjoin(tmp, ofile->d_name))) == 0))
		if (ft_strcmp(ofile->d_name, file) == 0)
			free(tmp1);
	if (ofile && ft_strcmp(ofile->d_name, file) == 0)
		free(tmp1);
	free(tmp);
	if (ofile && ofile->d_name[0] != '.')
	{
		closedir(dir);
		return (path);
	}
	closedir(dir);
	return (NULL);
}

int			ft_strcmpset(char *str1, char *str2)
{
	int i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	if (!str1 && !str2)
		return (0);
	if (!str1)
		return (-1);
	if (!str2)
		return (1);
	while (str1[i1] && str2[i2])
		if (str1[i1] == 7)
			i1++;
		else if (str2[i2] == 7)
			i2++;
		else if (str2[i2] != str1[i1])
			return (1);
		else
		{
			i1++;
			i2++;
		}
	return (0);
}

char		*toexec(char *argv)
{
	char	**path;
	size_t	i;
	size_t	len;
	char	*temp;
	char	*temp2;

	if (casenofor("PATH") == -1)
		return (NULL);
	temp = getenvline("PATH=");
	path = ft_strsplit(temp, ':');
	free(temp);
	len = ft_strlen(path[0]);
	len = ft_strstrlen(path);
	i = 0;
	while (i < len && getexec(path[i], argv) == NULL)
		i++;
	if (i == len)
		ft_strstrfree(path);
	if (i == len)
		return (NULL);
	temp = ft_strjoin(path[i], "/");
	ft_strstrfree(path);
	temp2 = ft_strjoin(temp, argv);
	free(temp);
	return (temp2);
}

char		*give_path(char *name, t_binary **table)
{
	int			hash;
	t_binary	*bin;

	if (!table)
	{
		return (NULL);
	}
	hash = ft_hash_algo(name);
	bin = table[hash];
	while (bin)
	{
		if (bin->data)
		{
			if (ft_strcmp(bin->data->name, name) == 0)
			{
				return (ft_strdup(bin->data->full_path));
			}
		}
		bin = bin->next;
	}
	return (NULL);
}
