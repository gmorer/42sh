/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:13:30 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:17:23 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** remet les marge a 0 et augment le nb de ligne puis place le cursuer a la
** ligne quand on est au bout du shell
*/

static void			return_line(t_cursor *cursor)
{
	cursor->l_marge = 0;
	cursor->r_marge = 0;
	while (cursor->cur_col > 0)
	{
		tputs(tgetstr("le", 0), 1, my_putchar);
		cursor->cur_col--;
	}
	tputs(tgetstr("do", 0), 1, my_putchar);
	cursor->cur_line++;
	cursor->nb_line = ((ft_strlen(cursor->line) + 3) / cursor->max_col) + 1;
}

/*
** fait l'affiche surligner quand on sleectione des caractere pour la copie
** ou le couper.
*/

void				display(t_cursor *cur, int i)
{
	int				beg;
	int				end;

	beg = cur->beg_select;
	end = cur->end_select;
	if (beg > end)
		ft_swap(&beg, &end);
	if (i >= 0 && i >= beg && i <= end)
	{
		ft_putstr("\033[7;37m");
		ft_putchar(cur->line[i]);
		ft_putstr("\033[0m");
	}
	else
		ft_putchar(cur->line[i]);
}

/*
** recoit la chaine a l'index ou l'affichage dois se faire
*/

void				putstr_cmd(t_cursor *curs, int i)
{
	while (curs->line[i])
	{
		curs->cur_col++;
		display(curs, i);
		if (curs->cur_col >= curs->max_col)
			return_line(curs);
		i++;
	}
}
