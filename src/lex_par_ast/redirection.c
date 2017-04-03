/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 17:56:09 by acottier          #+#    #+#             */
/*   Updated: 2017/04/03 12:31:22 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

/*
** Ajoute le suffixe de la redir au maillon actuel
** (ex : dans '2>&-', ajoute '&-')
*/

static void		add_suffix(char **line, t_lex **res)
{
	int		length;
	char	*tmp;

	if (**line == ' ' || **line == '\n')
		advance_pos(line, target(*line, 7));
	length = ft_smallest(target(*line, 6), target(*line, 2));
	if (**line == '&' && *(*line + 1) && *(*line + 1) == ' ')
		length += ft_smallest(target(*line, 6), target(*line, 1));
	if (!length)
		return ;
	tmp = ft_strndup(*line, length);
	*res = add_link(tmp, *res, 0, 1);
	advance_pos(line, length);
}

/*
** Ajoute le(s) caractere(s) de redir de la redir au maillon actuel
** (ex : dans '2>&-', ajoute '>')
*/

static void		add_redir(char **line, t_lex **res)
{
	int		length;
	char	*tmp;

	length = target(*line, 5);
	if (!length)
		return ;
	tmp = ft_strndup(*line, length);
	*res = add_link(tmp, *res, 0, 2);
	advance_pos(line, length);
}

/*
** Ajoute le prefixe de la redir au maillon actuel
** (ex : dans '2>&-', ajoute '2')
*/

static void		add_prefix(char **line, t_lex **res)
{
	int		length;
	char	*tmp;

	length = target(*line, 1);
	if (!length)
		return ;
	tmp = ft_strndup(*line, length);
	*res = add_link(tmp, *res, 0, 0);
	advance_pos(line, length);
}

/*
** Cherche une redir dans la chaine, si il y en a une,
** ajoute la redirection formatee au maillon actuel
*/

int				redirection(char **line, t_lex **res)
{
	int		length;
	int		scope;
	char	*cmd;

	scope = ft_smallest(target(*line, 0), target(*line, 4));
	length = redir_in_scope(*line, scope);
	if (length)
	{
		if ((int)ft_strlen(*line) == 1)
		{
			cmd = ft_strdup(*line);
			*res = add_link(cmd, *res, 0, 1);
			advance_pos(line, 1);
			return (0);
		}
		length = agreg_prefix(*line, target(*line, 1));
		cmd = (length ? ft_strndup(*line, length) : NULL);
		length ? *res = add_link(cmd, *res, is_sep(cur_lex_str(*res)), 0) : 0;
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
	if (!line[limit] && limit > 0)
		limit--;
	while (limit >= 0 && line[limit] && line[limit] != 32)
	{
		if (line[limit] == '<' || line[limit] == '>')
			limit--;
		if (limit >= 0 && ft_isdigit(line[limit]) == 0)
			return (stock);
		if (limit == 0)
			return (limit);
		limit--;
	}
	return (limit >= 0 ? limit : 0);
}
