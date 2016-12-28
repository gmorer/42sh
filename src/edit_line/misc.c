/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:11:12 by rvievill          #+#    #+#             */
/*   Updated: 2016/12/14 19:47:47 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"

int				my_putchar(int c)
{
	return (write(1, &c, 1));
}

void			set_marge(t_cursor *cursor)
{
	if (cursor->cur_line == 1)
		cursor->l_marge = 3;
	else
		cursor->l_marge = 0;
	if (cursor->cur_line < cursor->nb_line)
		cursor->r_marge = cursor->max_col;
	else
		cursor->r_marge = ft_strlen(cursor->line) % cursor->max_col + 3;
}

void			set_pos(t_cursor *cursor, int i, int *line, int *col)
{
	if (i < cursor->max_col - 3)
	{
		*line = 1;
		*col = i + 3;
	}
	else
	{
		*line = ((i - cursor->max_col + 3) / cursor->max_col) + 2;
		*col = i - (cursor->max_col * (*line - 1)) + 3;
	}
}