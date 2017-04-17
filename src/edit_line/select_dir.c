/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:16:54 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 16:07:56 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "env.h"

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
			if ((!file || (ft_strncmp(file, d->d_name, size_file) == 0
			&& size_file != (int)ft_strlen(d->d_name)
			&& ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, ".."))) && ++i)
				create_lst(d->d_name, inf);
		}
		if (inf->arg)
		{
			stoc(inf);
			fill_info_size(inf, i);
		}
		closedir(dirp);
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
		closedir(dirp);
	}
}

static void			find_path(char **dir, char **file)
{
	char	*pathend;
	char	*path;

	pathend = ft_strrchr(*dir, '/');
	if (pathend)
	{
		if (*(pathend + 1))
		{
			*file = ft_strdup(pathend + 1);
			path = ft_strndup(*dir, ft_strlen(*dir) - ft_strlen(pathend) + 1);
			ft_strdel(dir);
			*dir = path;
		}
	}
}

void				select_dir(t_info *info)
{
	DIR				*dirp;
	char			*file;

	file = NULL;
	dirp = NULL;
	find_path(&info->dir, &file);
	info->size = ft_strlen(file);
	info->arg = NULL;
	info->file = ft_strdup(file);
	if (ft_strcmp(info->dir, ".") == 0 || (dirp = opendir(info->dir)) == NULL)
		cur_dir(info);
	else
	{
		closedir(dirp);
		specific_dir(info, file);
	}
	free(file);
}
