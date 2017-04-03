/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:34:49 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 16:34:46 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "env.h"

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
	int					i;
	static const t_key	key[17] = {{LEFT, &left}, {RIGHT, &right},
		{HOME, &home}, {END, &end}, {OPT_UP, &up}, {OPT_DOWN, &down},
		{PAGEUP, &next_word}, {PAGEDO, &prev_word}, {BACKSPACE, &backspace},
		{ALT_R, &select_right}, {ALT_L, &select_left}, {ALT_C, &copy},
		{ALT_V, &paste}, {ALT_X, &cut}, {UP, &up_hist}, {DOWN, &down_hist},
		{TAB, &completion}};

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
** ecrit exit si ctrl D et que la ligne est vide et qu'on est pas dasn une
** execution type << ou " ou ' sinon quite juste les quotes
*/

static int			ctrl_d(char buff[5], t_cursor *cur, int quot)
{
	if (quot != 1 && !g_shell->quote[0] && !g_shell->quote[1]
		&& (BUFF == -1 || BUFF == 4) && ft_strlen(cur->line) == 0)
	{
		ft_putendl("exit");
		exit(134);
	}
	if (quot == 1 && (BUFF == -1 || BUFF == 4) && ft_strlen(cur->line) == 0)
		return (1);
	return (0);
}

/*
** le debut de l'editiond de ligne:
** affichage du prompte, appelle a toute les fonction pour catch les touche,
** et affectation de la ligne a envoyer au lexer.
*/

int					edit_line(char **line, t_hist **hist, int quot)
{
	t_cursor		*cur;
	char			buff[5];

	cur = NULL;
	BUFF = 0;
	if (init_term(&cur))
		return (-1);
	while (BUFF != 10)
	{
		BUFF = 0;
		tputs(tgetstr("ve", 0), 1, my_putchar);
		read(0, buff, 4);
		if (BUFF == 27)
			return (free_cursor(cur));
		if (ctrl_d(buff, cur, quot))
			return (free_cursor(cur));
		if (catch_key(cur, buff, hist) == 1)
			add_char(buff, cur);
		tputs(tgetstr("vi", 0), 1, my_putchar);
	}
	*line = ft_strsub(cur->line, 0, ft_strlen(cur->line));
	create_hist(hist, line);
	go_start(ft_strlen(cur->line) % cur->max_col + 3, cur);
	term_dfl(cur);
	return (free_cursor(cur));
}
