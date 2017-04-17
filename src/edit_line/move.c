/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:15:26 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:15:28 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void	right(t_cursor *cursor, t_hist **hist)
{
	int	i;
	int	line;
	int	col;

	(void)hist;
	if (cursor->r_marge >= cursor->cur_col + 1)
	{
		cursor->cur_col++;
		i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
		set_pos(cursor, i, &line, &col);
		go_pos(cursor, line, col);
		set_marge(cursor);
	}
}

void	left(t_cursor *cursor, t_hist **hist)
{
	(void)hist;
	if (cursor->l_marge < cursor->cur_col)
	{
		(cursor->cur_col)--;
		tputs(tgetstr("le", 0), 1, my_putchar);
	}
	else if (cursor->cur_line > 1)
	{
		(cursor->cur_line)--;
		tputs(tgetstr("up", 0), 1, my_putchar);
		set_marge(cursor);
		go_pos(cursor, cursor->cur_line, cursor->max_col - 1);
	}
}

void	next_word(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	while (cursor->line[i] && cursor->line[i] != ' ')
		i++;
	while (cursor->line[i] && cursor->line[i] == ' ')
		i++;
	set_pos(cursor, i, &line, &col);
	go_pos(cursor, line, col);
	set_marge(cursor);
}

void	prev_word(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	while (i > 0 && cursor->line[i] != ' ')
		i--;
	while (i > 0 && cursor->line[i] == ' ')
		i--;
	set_pos(cursor, i, &line, &col);
	go_pos(cursor, line, col);
	set_marge(cursor);
}
