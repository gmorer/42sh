/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 20:23:55 by acottier          #+#    #+#             */
/*   Updated: 2017/03/02 14:55:48 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "split.h"

/*
** Avance le curseur tant que la quote fermante n'est pas trouvee
*/

int			quote_scope(char *line, char quote, int i)
{
	while (line[i])
	{
		if (line[i] == quote && is_reachable(line, i))
			return (i);
		i++;
	}
	return (i--);
}

/*
** Avance le curseur de line et l'index i de length ou jusqu'a la fin de
** si depassement
*/

void		advance_pos(char **line, int length)
{
	if ((int)ft_strlen(*line) <= length)
		*line += ft_strlen(*line);
	else
		(*line) += length;
}

/*
** Detecte la presence d'un chevron entre line[0] et line[scope]
*/

int			redir_in_scope(char *line, int scope)
{
	int		res1;
	int		res2;
	int		fres;

	res1 = 0;
	res2 = 0;
	if (ft_strnchr(line, '<', scope) != 0)
	{
		res1 = ft_strlenchr(line, '<');
		(!res1) ? res1++ : 0;
	}
	if (ft_strnchr(line, '>', scope) != 0)
	{
		res2 = ft_strlenchr(line, '>');
		(!res2) ? res2++ : 0;
	}
	if (res1 == 0 && res2 == 0)
		return (0);
	if (ft_smallest(res1, res2) != 0)
		fres = ft_smallest(res1, res2);
	else
		fres = ft_biggest(res1, res2);
	if (ft_strnchr(line, 34, fres) != 0 || ft_strnchr(line, 39, fres) != 0)
		return (0);
	return (fres);
}

/*
** Detecte si la chaine a jouter est un separateur principal
*/

int			is_sep(char *str)
{
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||") || !ft_strcmp(str, ";")
			|| !ft_strcmp(str, "&"))
		return (1);
	return (0);
}
