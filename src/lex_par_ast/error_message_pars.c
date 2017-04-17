/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:23:50 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 17:53:16 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

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

t_lex			*sep_pars_error(t_lex *cursor, int err)
{
	if (err == 0)
		ft_putendl_fd("Invalid null command.", 2);
	if (err == 1)
	{
		ft_putstr_fd("Parse error near '", 2);
		ft_putstr_fd(cursor->str, 2);
		ft_putendl_fd("'", 2);
	}
	return (cursor);
}

t_detail		*redir_pars_error(t_detail *cursor, int type)
{
	if (type == 0)
		ft_putendl_fd("Bad format for redirect.", 2);
	else if (type == 1)
		ft_putendl_fd("Missing name for redirect.", 2);
	return (cursor);
}
