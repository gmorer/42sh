/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:34:49 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/02 15:33:26 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** retourne en 0 ; 0 par rapport au prompt et non a shell
*/

static void			go_start(int size, t_cursor *cursor)
{
	int				i;

	i = 0;
	while (i <= size)
	{
		tputs(tgetstr("le", 0), 1, my_putchar);
		i++;
	}
	while (cursor->cur_line <= cursor->nb_line)
	{
		tputs(tgetstr("do", 0), 1, my_putchar);
		cursor->cur_line++;
	}
}

/*
** check si la touche presse est liee a une fonction grace a un tableau de
** struct avec un pointeur sur fonction et un int pour la touche
*/

static int			catch_key(t_cursor *curs, char buff[5], t_hist **hist)
{
	const t_key		key[17] = {{LEFT, &left}, {RIGHT, &right},
		{HOME, &home}, {END, &end}, {OPT_UP, &up}, {OPT_DOWN, &down},
		{PAGEUP, &next_word}, {PAGEDO, &prev_word}, {BACKSPACE, &backspace},
		{ALT_R, &select_right}, {ALT_L, &select_left}, {ALT_C, &copy},
		{ALT_V, &paste}, {ALT_X, &cut}, {UP, &up_hist}, {DOWN, &down_hist},
		{TAB, &completion}};
	int				i;

	i = 0;
	while (i < 17)
	{
		if (BUFF == key[i].key)
		{
			check_select(curs, buff);
			key[i].f(curs, hist);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** le debut de l'editiond de ligne:
** affichage du prompte, appelle a toute les fonction pour catch les touche,
** et affectation de la ligne a envoyer au lexer.
*/

int					edit_line(char **line, t_hist **hist)
{
	t_cursor		*cursor;
	char			buff[5];

	cursor = NULL;
	BUFF = 0;
	if (init_term(&cursor))
		return (-1);
	while (BUFF != 10)
	{
		BUFF = 0;
		tputs(tgetstr("ve", 0), 1, my_putchar);
		read(0, buff, 4);
		if (catch_key(cursor, buff, hist) == 1)
			add_char(buff, cursor);
		tputs(tgetstr("vi", 0), 1, my_putchar);
	}
	*line = ft_strsub(cursor->line, 0, ft_strlen(cursor->line));
	create_hist(hist, line);
	go_start(ft_strlen(cursor->line) % cursor->max_col + 3, cursor);
	term_dfl(cursor);
	return (0);
}
