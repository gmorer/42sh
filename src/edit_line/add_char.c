/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:38:20 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/05 13:20:04 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** verifie si le caractere envoyer est dans la table ascii puis place cette
** lettre dans le buffer
*/

void			add_char(char buff[5], t_cursor *cursor)
{
	int			i;
	int			line;
	int			col;

	if (BUFF >= ' ' && BUFF < 127)
	{
		cursor->r_marge++;
		i = cursor->cur_col - 3 + (cursor->max_col * (cursor->cur_line - 1));
		if ((int)ft_strlen(cursor->line) + 1 >= cursor->buff_size)
			extend_str(cursor);
		move_str(&cursor->line, i, 1, cursor->buff_size);
		cursor->line[i] = BUFF;
		set_pos(cursor, i + 1, &line, &col);
		putstr_cmd(cursor, i);
		go_pos(cursor, line, col);
		set_marge(cursor);
	}
}
