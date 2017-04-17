/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:24:12 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 15:58:24 by acottier         ###   ########.fr       */
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
	if (!is_reachable(line, fres))
		return (0);
	return (fres);
}

/*
** Detecte si la chaine a jouter est un separateur principal
*/

int			is_sep(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||") || !ft_strcmp(str, ";")
			|| !ft_strcmp(str, "&"))
		return (1);
	return (0);
}

int			check_nbr(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (0);
	else
	{
		while (str[i] && str[i] != '>' && str[i] != '<')
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
		return (1);
	}
}
