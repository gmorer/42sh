/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selet.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:36:17 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/05 13:25:26 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			check_select(t_cursor *cursor, char buff[5])
{
	int			i;
	int			line;
	int			col;

	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (cursor->beg_select != -1 && cursor->end_select != -1 &&
			BUFF != ALT_C && BUFF != ALT_X && BUFF != ALT_L && BUFF != ALT_R)
	{
		cursor->beg_select = -1;
		cursor->end_select = -1;
		set_pos(cursor, i, &line, &col);
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		go_pos(cursor, line, col);
	}
}

void			select_left(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (cursor->cur_col > cursor->l_marge)
	{
		if (cursor->beg_select == -1 && cursor->end_select == -1)
		{
			cursor->beg_select = i;
			cursor->end_select = i - 1;
		}
		else
			cursor->end_select--;
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		set_pos(cursor, i, &line, &col);
		go_pos(cursor, line, col - 1);
		set_marge(cursor);
	}
}

void			select_right(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (cursor->cur_col < cursor->r_marge - 1)
	{
		if (cursor->beg_select == -1 && cursor->end_select == -1)
		{
			cursor->beg_select = i;
			cursor->end_select = i + 1;
		}
		else
			cursor->end_select++;
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		set_pos(cursor, i, &line, &col);
		go_pos(cursor, line, col + 1);
		set_marge(cursor);
	}
}
