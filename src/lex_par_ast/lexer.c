/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:23:57 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 18:03:03 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "split.h"

/*
** Fusionne 2 chaines en mettant un caractere special au milieu
*/

static char	*trijoin(char *str1, char *str2, int merge, char *space)
{
	char	*swap;
	char	*tmp;
	char	*res;
	int		i;

	swap = ft_strnew(1);
	swap[0] = 0;
	if (merge == 2)
	{
		i = ft_strlen(str1) - 1;
		while (i >= 0 && str1 && str1[i] && str1[i] != ' ' && str1[i] != 7)
			if (ft_isdigit(str1[i--]) == 0)
				swap[0] = 7;
		swap[0] == 0 ? swap[0] = ' ' : 0;
		if (space && (*space == ' ' || *space == '\t' || *space == '\n')
				&& !check_nbr(space))
			swap[0] = 7;
	}
	else
		swap[0] = (merge == 1 ? ' ' : 7);
	tmp = ft_strjoin(str1, swap);
	res = ft_strjoin(tmp, str2);
	ft_strdel(&tmp);
	ft_strdel(&swap);
	return (res);
}

/*
** Ajoute un maillon a la liste
*/

t_lex		*add_link(char *str, t_lex *prev, int add, int merge)
{
	t_lex	*res;
	char	*tmp;

	res = NULL;
	if (ft_strlen(str) == 0 || !str)
		return (prev);
	if (add)
	{
		res = (t_lex *)ft_memalloc(sizeof(t_lex));
		res->str = ft_strdup(str);
		res->placed = 0;
		res->prev = prev;
		res->next = NULL;
		prev ? prev->next = res : 0;
	}
	else
	{
		if (!prev)
			prev = add_link("\a", NULL, 1, 0);
		tmp = prev->str;
		prev->str = trijoin(tmp, str, merge, prev->space);
		ft_strdel(&tmp);
	}
	ft_strcmp(str, "\a") ? ft_strdel(&str) : 0;
	return (res ? res : prev);
}

/*
** Donne a i la taille du prochain token a ajouter
*/

static int	get_expr(char **line, int *i, t_lex **res)
{
	if (redirection(line, res) == 0)
		return (1);
	if ((*line)[0] == '|' || (*line)[0] == '&')
	{
		if ((*line)[1] && (*line)[0] == (*line)[1])
			(*i) += 2;
		else if (!(*line)[1] || (*line[1] != (*line)[0]))
			(*i)++;
	}
	(*line)[0] == ';' ? (*i)++ : 0;
	if ((*i) == 0)
	{
		while ((*line)[*i] && (*line)[*i] != '|' && (*line)[*i] != '&'
			&& (*line)[*i] != ';' && (*line)[*i] != ' ' && (*line)[*i] != '\n'
			&& (*line)[*i] != '\t')
		{
			if (((*line)[*i] == '\'' || (*line)[*i] == '\"')
					&& (is_reachable(*line, *i)))
				*i = quote_scope(*line, (*line)[*i], *i + 1);
			(*i)++;
		}
	}
	return (0);
}

/*
** Creation de la liste contenant tous les tokens
*/

t_lex		*lexer(char **line, char *cursor, int i)
{
	char		*swap;
	t_lex		*res;

	res = NULL;
	if (!(*line))
		return (res);
	while (*cursor)
	{
		i = 0;
		res ? res->space = cursor : 0;
		while (*cursor == ' ' || *cursor == '\n' || *cursor == '\t')
			cursor++;
		if (get_expr(&cursor, &i, &res) == 0 && i > 0)
		{
			swap = ft_strndup(cursor, i);
			if (res && is_sep(res->str))
				res = add_link(swap, res, 1, 0);
			else
				res = add_link(swap, res, is_sep(swap), 0);
		}
		cursor += i;
	}
	ft_strdel(line);
	return (to_start(res));
}
