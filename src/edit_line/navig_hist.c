/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navig_hist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:15:37 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/04 12:33:42 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void		cl(t_cursor *cursor)
{
	int			size;
	char		tmp[cursor->buff_size];

	ft_memmove(tmp, cursor->line, cursor->buff_size);
	size = ft_strlen(cursor->line);
	cursor->line = ft_memset(cursor->line, ' ', size);
	go_pos(cursor, 1, 3);
	putstr_cmd(cursor, 0);
	ft_memmove(cursor->line, tmp, cursor->buff_size);
}

void			up_hist(t_cursor *cursor, t_hist **hist)
{
	if (hist && *hist)
	{
		cl(cursor);
		ft_strdel(&cursor->line);
		while (cursor->buff_size < (int)ft_strlen((*hist)->cmd))
			cursor->buff_size *= 2;
		cursor->line = ft_strnew(cursor->buff_size);
		ft_memmove(cursor->line, (*hist)->cmd, ft_strlen((*hist)->cmd));
		if ((*hist)->prev)
			*hist = (*hist)->prev;
		cursor->nb_line = ft_strlen(cursor->line) / cursor->max_col + 1;
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		set_marge(cursor);
	}
}

void			down_hist(t_cursor *cursor, t_hist **hist)
{
	if (hist && *hist)
	{
		cl(cursor);
		ft_bzero(cursor->line, cursor->buff_size);
		if ((*hist)->next)
		{
			ft_strdel(&cursor->line);
			*hist = (*hist)->next;
			while (cursor->buff_size < (int)ft_strlen((*hist)->cmd))
				cursor->buff_size *= 2;
			cursor->line = ft_strnew(cursor->buff_size);
			ft_memmove(cursor->line, (*hist)->cmd, ft_strlen((*hist)->cmd));
		}
		cursor->nb_line = ft_strlen(cursor->line) / cursor->max_col + 1;
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		set_marge(cursor);
	}
}
