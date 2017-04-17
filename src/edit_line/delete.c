/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:12:45 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:12:49 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** recupere la position actuelle du curseur, ensuite decale la chaine de 1
** vers la droite puis affiche la chaine du debut
*/

void			backspace(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	if (cursor->cur_col != cursor->l_marge || cursor->cur_line != 1)
	{
		i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
		move_str(&cursor->line, i, -1, cursor->buff_size);
		clear_line(cursor, 1, cursor->nb_line, 3);
		go_pos(cursor, 1, 3);
		putstr_cmd(cursor, 0);
		if (cursor->cur_col == 0)
		{
			go_pos(cursor, cursor->cur_line - 1, cursor->max_col + 1);
			cursor->nb_line--;
			set_marge(cursor);
		}
		set_pos(cursor, i - 1, &line, &col);
		go_pos(cursor, line, col);
		set_marge(cursor);
	}
}
