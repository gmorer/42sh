/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:56:41 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/05 13:25:34 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void			specific_dir(t_info *inf, char *file)
{
	DIR				*dirp;
	struct dirent	*d;
	int				i;
	int				size_file;

	i = 0;
	size_file = 0;
	if (file)
		size_file = ft_strlen(file);
	if ((dirp = opendir(inf->dir)))
	{
		while ((d = readdir(dirp)))
		{
			if (ft_strncmp(file, d->d_name, size_file) == 0
			&& size_file != (int)ft_strlen(d->d_name)
			&& ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, "..") && ++i)
				create_lst(d->d_name, inf);
		}
		if (inf->arg)
		{
			stoc(inf);
			fill_info_size(inf, i);
		}
	}
}

static void			cur_dir(t_info *inf)
{
	DIR				*dirp;
	struct dirent	*d;
	int				i;

	i = 0;
	if ((dirp = opendir(".")))
	{
		while ((d = readdir(dirp)))
		{
			if (ft_strncmp(d->d_name, inf->dir, ft_strlen(inf->dir)) == 0
			&& ft_strlen(inf->dir) != ft_strlen(d->d_name)
			&& ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, "..") && ++i)
				create_lst(d->d_name, inf);
		}
		if (inf->arg)
		{
			stoc(inf);
			fill_info_size(inf, i);
		}
	}
}

static char			*find_path(char *dir)
{
	char			*path;
	int				i;

	i = 0;
	if (dir[0] == '/' && dir[1] != '.' && opendir(dir))
		return (NULL);
	else
	{
		path = ft_strdup(ft_strchr(dir, '/'));
		return (path);
	}
}

void				select_dir(t_info *info)
{
	DIR				*dirp;
	char			*file;
	char			*tmp;
	int				size;

	file = find_path(info->dir);
	info->arg = NULL;
	if (file != NULL)
	{
		size = ft_strlen(info->dir);
		tmp = ft_strdup(info->dir);
		free(info->dir);
		info->dir = ft_strsub(tmp, 0, size - ft_strlen(file) + 1);
		free(tmp);
	}
	if (ft_strcmp(info->dir, ".") == 0 || (dirp = opendir(info->dir)) == NULL)
		cur_dir(info);
	else
		specific_dir(info, file ? file + 1 : file);
	ft_strdel(&file);
}
