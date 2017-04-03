/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:02:08 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/25 13:28:24 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

int					lstlen(t_arg *arg)
{
	int				i;

	i = 0;
	arg = arg->next;
	while (arg->start != 1)
	{
		arg = arg->next;
		i++;
	}
	return (i);
}

void				fill_info_size(t_info *info, int ac)
{
	t_arg			*tmp;
	struct winsize	size;

	info->len = 0;
	tmp = info->arg;
	info->len = ft_strlen(tmp->name);
	tmp = tmp->next;
	ioctl(0, TIOCGWINSZ, &size);
	while (tmp->start != 1)
	{
		if ((int)ft_strlen(tmp->name) > info->len)
			info->len = ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	info->len++;
	info->len_arg = ac;
	info->nb_param = ac - 1;
	info->column = size.ws_col / info->len;
	info->line = info->nb_param / info->column;
	if ((info->line * info->column) == info->nb_param)
		info->line = (info->nb_param / info->column);
	else
		info->line = (info->nb_param / info->column) + 1;
	info->nb_param < info->column ? info->column = info->nb_param + 1 : 0;
}

void				stoc(t_info *info)
{
	t_arg			*start;

	start = info->arg;
	while (info->arg->next)
		info->arg = info->arg->next;
	start->prev = info->arg;
	info->arg->next = start;
	info->arg = start;
}

void				clear_line(t_cursor *cursor, int start, int end, int col)
{
	go_pos(cursor, start, col);
	while (start < end)
	{
		tputs(tgetstr("ce", 0), 1, my_putchar);
		start++;
		go_pos(cursor, start, 0);
	}
	tputs(tgetstr("ce", 0), 1, my_putchar);
}
