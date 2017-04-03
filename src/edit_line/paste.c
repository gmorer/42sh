/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:47:38 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 12:00:41 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			paste(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			size;
	int			j;
	int			line;
	int			col;

	(void)hist;
	j = 0;
	size = ft_strlen(cursor->str_cpy);
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if ((int)ft_strlen(cursor->line) + size >= cursor->buff_size)
		extend_str(cursor);
	move_str(&cursor->line, i, size, cursor->buff_size);
	while (j < size)
	{
		cursor->line[i] = cursor->str_cpy[j];
		i++;
		j++;
	}
	set_pos(cursor, i, &line, &col);
	putstr_cmd(cursor, i - size);
	go_pos(cursor, line, col);
	set_marge(cursor);
}
