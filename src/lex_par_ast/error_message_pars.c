/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:53:43 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/02 12:28:40 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

/*
** Choix du message d'erreur selon le code renvoye
** (parsing de sous_liste/commandes)
*/

t_detail		*cmd_pars_error(t_detail *cursor, int err)
{
	if (err == 1 || err == 2)
	{
		ft_putstr_fd("Parse error near '", 2);
		ft_putstr_fd(cursor->argv[0], 2);
		ft_putendl_fd("'", 2);
	}
	if (err == 3)
		ft_putendl_fd("Ambiguous output redirect.", 2);
	if (err == 4)
		ft_putendl_fd("Missing name for redirect.", 2);
	if (err == 5)
		ft_putendl_fd("Invalid null command.", 2);
	if (err == 2)
		return (cursor->next);
	if (err == 6)
		ft_putendl_fd("Parse error near '|'", 2);
	return (cursor);
}

/*
** Choix du message d'erreur selon le code renvoye
** (parsing des separateurs)
*/

t_lex		*sep_pars_error(t_lex *cursor, int err)
{
	if (err == 0)
		ft_putendl("Invalid null command.");
	if (err == 1)
	{
		ft_putstr_fd("Parse error near '", 2);
		ft_putstr_fd(cursor->str, 2);
		ft_putendl_fd("'", 2);
	}
	return (cursor);
}
