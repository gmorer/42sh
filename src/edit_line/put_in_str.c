/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:56:47 by rvievill          #+#    #+#             */
/*   Updated: 2017/02/21 12:43:36 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static int		nb_selected(t_arg *arg)
{
	int			i;

	i = 0;
	if (arg->selected == 1)
		i++;
	arg = arg->next;
	while (arg->start != 1)
	{
		if (arg->selected == 1)
			i++;
		arg = arg->next;
	}
	return (i);
}

static void		write_in_line(int *i, t_cursor *cur, t_info *info, int nb)
{
	char		*dir;
	char		*file;
	int			j;
	int			size;

	j = 0;
	if (lstlen(info->arg) > 1)
	{
		dir = ft_strdup(info->dir);
		file = ft_strjoin(dir, info->arg->name);
	}
	else
		file = ft_strdup(info->arg->name);
	size = ft_strlen(file);
	if ((int)ft_strlen(file) + (int)ft_strlen(cur->line) > cur->buff_size)
		extend_str(cur);
	if (*i + (int)ft_strlen(info->dir) < (int)ft_strlen(cur->line))
		move_str(&cur->line, *i, nb > 0 ? size + 1 : size, cur->buff_size);
	while (file[j])
	{
		cur->line[*i] = file[j++];
		(*i)++;
	}
	cur->line[*i] = ' ';
	(*i)++;
}

void			put_in_str(t_cursor *cur, t_info *info)
{
	int			i;
	int			size;
	int			nb_select;
	int			nb;

	nb_select = nb_selected(info->arg);
	nb = nb_select;
	i = cur->cur_col - 3 + cur->max_col * (cur->cur_line - 1);
	size = ft_strlen(info->dir);
	if (size > 0 && info->dir[size - 1] != '/' && opendir(info->dir))
		info->dir = ft_strjoin(info->dir, "/");
	i -= size;
	if (info->arg->selected == 1)
		write_in_line(&i, cur, info, --nb_select);
	info->arg = info->arg->next;
	while (info->arg->start != 1)
	{
		if (info->arg->selected == 1)
			write_in_line(&i, cur, info, --nb_select);
		info->arg = info->arg->next;
	}
	go_pos(cur, 1, 3);
	putstr_cmd(cur, 0);
	go_pos(cur, cur->cur_line, nb > 0 ? i + 3 : i + 4);
	set_marge(cur);
}
