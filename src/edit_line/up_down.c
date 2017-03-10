/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:41:02 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/09 10:27:14 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			up(t_cursor *cursor, t_hist **hist)
{
	int			col;
	int			line;

	(void)hist;
	col = cursor->cur_col;
	if (cursor->cur_col < 3 && cursor->cur_line - 1 == 1)
		col = 3;
	if (cursor->cur_line > 1)
	{
		line = cursor->cur_line - 1;
		go_pos(cursor, line, col);
		set_marge(cursor);
	}
}

void			down(t_cursor *cursor, t_hist **hist)
{
	int			col;
	int			size;
	int			line;
	int			i;

	(void)hist;
	size = ft_strlen(cursor->line);
	col = cursor->cur_col;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (i + cursor->max_col > size)
		col = size % cursor->max_col + 3;
	if (cursor->cur_line < cursor->nb_line)
	{
		line = cursor->cur_line + 1;
		go_pos(cursor, line, col);
		set_marge(cursor);
	}
}
