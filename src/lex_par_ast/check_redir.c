/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 17:48:13 by acottier          #+#    #+#             */
/*   Updated: 2017/04/16 19:17:03 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "exec.h"

t_detail		*check_redir(t_detail *cursor)
{
	int			i;
	char		*file;
	t_detail	*error;

	i = 0;
	error = NULL;
	while (!error && cursor && cursor->redir_str && cursor->redir_str[i])
	{
		file = get_file(cursor->redir_str[i]);
		if (!file)
			error = cursor;
		ft_strdel(&file);
		i++;
	}
	return (error ? redir_pars_error(error, 1) : NULL);
}
