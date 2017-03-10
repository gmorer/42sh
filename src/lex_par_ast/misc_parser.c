/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:38:59 by acottier          #+#    #+#             */
/*   Updated: 2017/03/06 12:31:38 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

/*
** Verifie si les redir_str contiennent bien une expression
** suivant la redirection
*/

int			check_redir_tab(char **redir_str)
{
	char	*cursor;
	int		i;

	i = 0;
	cursor = NULL;
	while (redir_str[i])
	{
		cursor = ft_strrchr(redir_str[i], '>');
		if (!cursor)
			cursor = ft_strrchr(redir_str[i], '<');
		if (cursor)
			cursor++;
		if (cursor && *cursor == ' ')
			cursor++;
		if (!cursor)
			return (1);
		i++;
	}
	return (0);
}

/*
** Renvoie le prochain maillon separateur de la liste t_lex
*/

t_lex		*pars_next_sep(t_lex *lex)
{
	if (!lex)
		return (NULL);
	lex = lex->next;
	while (lex)
	{
		if (!lex->lst)
			return (lex);
		lex = lex->next;
	}
	return (lex);
}

/*
** Donne l'index du prochain caractere recherche, selon le type
*/

int			target(char *str, int type)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (type == 0 && (str[i] == '&' || str[i] == '|' || str[i] == ';'))
			return (i);
		else if (type == 1 && (str[i] == '<' || str[i] == '>'))
			return (i);
		else if (type == 2 && (str[i] == '<' || str[i] == '>' || str[i] == ' '
					|| str[i] == '\n'))
			return (i);
		else if (type == 3 && (str[i] == '&' || str[i] == '|' || str[i] == ';')
				&& str[i + 1] && str[i + 1] == str[i])
			return (i);
		else if (type == 4 && (str[i] == ' ' || str[i] == '\n'))
			return (i);
		else if (type == 5)
			return (str[i] == str[i + 1] ? 2 : 1);
		else if (type == 6 && (str[i] == '|' || str[i] == ';'))
			return (i);
		else if (type == 7 && (str[i] != ' ' && str[i] != '\n'))
			return (i);
	}
	return (i);
}

/*
** Renvoie le premier maillon de la liste
*/

t_lex		*to_start(t_lex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
