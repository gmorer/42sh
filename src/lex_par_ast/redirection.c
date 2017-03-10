/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:29:56 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/09 12:33:22 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

/*
 ** Ajoute le prefixe de la redir au maillon actuel
 ** (ex : dans '2>&-', ajoute '2')
*/

static void		add_prefix(char **line, t_lex **res)
{
	int	length;

	length = target(*line, 1);
	if (!length)
		return ;
	*res = add_link(ft_strndup(*line, length), *res, 0, 0);
	advance_pos(line, length);
}

/*
 ** Ajoute le(s) caractere(s) de redir de la redir au maillon actuel
 ** (ex : dans '2>&-', ajoute '>')
*/

static void		add_redir(char **line, t_lex **res)
{
	int	length;

	length = target(*line, 5);
	if (!length)
		return ;
	*res = add_link(ft_strndup(*line, length), *res, 0, 2);
	advance_pos(line, length);
}

/*
 ** Ajoute le suffixe de la redir au maillon actuel
 ** (ex : dans '2>&-', ajoute '&-')
*/

static void		add_suffix(char **line, t_lex **res)
{
	int	length;

	if (**line == ' ' || **line == '\n')
		advance_pos(line, target(*line, 7));
	length = ft_smallest(target(*line, 0), target(*line, 2));
	if (!length)
		return ;
	*res = add_link(ft_strndup(*line, length), *res, 0, 1);
	advance_pos(line, length);
}

/*
 ** Cherche une redir dans la chaine, si il y en a une,
 ** ajoute la redirection formatee au maillon actuel
*/

int				redirection(char **line, t_lex **res)
{
	int		length;

	if ((length = redir_in_scope(*line, target(*line, 4))) != 0)
	{
		if ((int)ft_strlen(*line) == 1)
		{
			*res = add_link(ft_strdup(*line), *res, 0, 1);
			advance_pos(line, 1);
			return (0);
		}
		length = agreg_prefix(*line, target(*line, 1));
		length ? *res = add_link(ft_strndup(*line, length), *res, 0, 0) : 0;
		advance_pos(line, length);
		add_prefix(line, res);
		add_redir(line, res);
		add_suffix(line, res);
		return (0);
	}
	return (1);
}

/*
 ** Retourne l'index du debut de la redirection
*/

int				agreg_prefix(char *line, int limit)
{
	int		stock;

	stock = limit;
	if (!line[limit])
		limit--;
	while (line[limit] && line[limit] != 32)
	{
		if (line[limit] == '<' || line[limit] == '>')
			limit--;
		if (ft_isdigit(line[limit]) == 0)
			return (stock);
		if (limit == 0)
			return (limit);
		limit--;
	}
	return (limit);
}
