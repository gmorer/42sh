/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:11:55 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 10:30:46 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** verifie si le caractere envoyer est dans la table ascii puis place cette
** lettre dans le buffer
*/

void			add_char(char buff[5], t_cursor *cur)
{
	int			i;
	int			line;
	int			col;

	if (BUFF >= ' ' && BUFF < 127)
	{
		check_select(cur, buff);
		cur->r_marge++;
		i = cur->cur_col - 3 + (cur->max_col * (cur->cur_line - 1));
		if ((int)ft_strlen(cur->line) + 1 >= cur->buff_size)
			extend_str(cur);
		move_str(&cur->line, i, 1, cur->buff_size);
		cur->line[i] = BUFF;
		set_pos(cur, i + 1, &line, &col);
		putstr_cmd(cur, i);
		go_pos(cur, line, col);
		set_marge(cur);
	}
}
