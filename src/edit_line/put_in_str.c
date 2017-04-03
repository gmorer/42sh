/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:56:47 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 15:25:03 by rvievill         ###   ########.fr       */
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

static void		write_in_line(int *i, t_cursor *cur, t_info *info)
{
	char		*file;
	int			j;
	int			size;

	if (info->arg->selected != 1)
		return ;
	j = 0;
	if (lstlen(info->arg) > 1)
		file = ft_strjoin(info->dir, info->arg->name);
	else
		file = ft_strdup(info->arg->name);
	size = (!info->size ? ft_strlen(info->dir) : info->size);
	if ((int)ft_strlen(file) + (int)ft_strlen(cur->line) > cur->buff_size)
		extend_str(cur);
	if (*i + (int)ft_strlen(info->dir) < (int)ft_strlen(cur->line))
		move_str(&cur->line, *i, size, cur->buff_size);
	while (file[j])
	{
		cur->line[*i] = file[j++];
		(*i)++;
	}
	free(file);
	cur->line[(*i)++] = ' ';
}

void			put_in_str(t_cursor *cur, t_info *f)
{
	int			i;
	int			size;
	int			line;
	int			col;

	size = (!f->size ? ft_strlen(f->dir) : f->size);
	i = cur->cur_col - 3 + cur->max_col * (cur->cur_line - 1) - size;
	if (size && f->dir && f->dir[size - 1] != '/' && ft_isfolder(f->dir))
		f->dir = ft_freejoin(f->dir, "/");
	write_in_line(&i, cur, f);
	f->arg = f->arg->next;
	while (f->arg->start != 1)
	{
		write_in_line(&i, cur, f);
		f->arg = f->arg->next;
	}
	go_pos(cur, 1, 3);
	putstr_cmd(cur, 0);
	set_pos(cur, i, &line, &col);
	go_pos(cur, line, nb_selected(f->arg) > 0 ? col : col + size);
	set_marge(cur);
}
