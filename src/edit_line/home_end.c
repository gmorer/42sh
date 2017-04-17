/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:14:37 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/06 14:27:44 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			home(t_cursor *cursor, t_hist **hist)
{
	(void)hist;
	go_home(cursor);
	set_marge(cursor);
	while (cursor->cur_col < 3)
	{
		tputs(tgetstr("nd", 0), 1, my_putchar);
		cursor->cur_col++;
	}
}

void			end(t_cursor *cursor, t_hist **hist)
{
	(void)hist;
	go_home(cursor);
	while (cursor->cur_col > 0)
	{
		tputs(tgetstr("le", 0), 1, my_putchar);
		cursor->cur_col--;
	}
	while (cursor->cur_line != cursor->nb_line)
	{
		tputs(tgetstr("do", 0), 1, my_putchar);
		cursor->cur_line++;
	}
	set_marge(cursor);
	while (cursor->cur_col < cursor->r_marge)
	{
		tputs(tgetstr("nd", 0), 1, my_putchar);
		cursor->cur_col++;
	}
}
