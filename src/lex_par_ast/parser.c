/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:11:01 by acottier          #+#    #+#             */
/*   Updated: 2017/03/08 14:18:33 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "exec.h"

/*
** Verifie la syntaxe des maillons de la liste principale
** (alternance cmd / sep, pas de '&& ou '||' a la fin)
*/

static t_lex	*check_sep_syntax(t_lex *lex)
{
	t_lex	*error;

	if (!lex)
		return (NULL);
	if (lex->lst)
		return (NULL);
	if ((ft_strcmp(lex->str, ";") || ft_strcmp(lex->str, "&")) && !lex->next)
		return (sep_pars_error(lex, 0));
	if ((lex->prev && !lex->prev->lst) || (lex->next && !lex->next->lst))
		return (sep_pars_error(lex, 1));
	if ((error = check_sep_syntax(pars_next_sep(lex))))
		return (error);
	return (NULL);
}

/*
** Appel en cas d'erreur de syntaxe, free toutes les listes
*/

static t_lex	*free_all(t_lex *main_lst)
{
	t_detail	*cursor;
	t_detail	*tmp;
	t_lex		*main_tmp;

	while (main_lst)
	{
		cursor = main_lst->lst;
		while (cursor)
		{
			if (cursor->redir_str)
				free(cursor->redir_str);
			if (cursor->argv)
				ft_strstrfree(cursor->argv);
			tmp = cursor->next;
			free(cursor);
			cursor = tmp;
		}
		if (main_lst->str)
			free(main_lst->str);
		main_tmp = main_lst->next;
		free(main_lst);
		main_lst = main_tmp;
	}
	return (NULL);
}

/*
** Retourne un int correspondant au symbole de redirection
** d'un maillon comprenant une redirection (parcours recursif)
*/

static void		assign_redir(t_detail *link, char *file)
{
	int			i;

	i = 0;
	if (!link)
		return ;
	while (link->redir_str && link->redir_str[i])
	{
		if (ft_strstr(link->redir_str[i], ">>"))
			link->redir[i] = DB_R;
		else if (ft_strstr(link->redir_str[i], "<<"))
		{
			link->redir[i] = DB_L;
			file = get_file(link->redir_str[i]);
			heredoc(link, DB_L, file, i);
		}
		else if (ft_strstr(link->redir_str[i], ">"))
			link->redir[i] = S_R;
		else if (ft_strstr(link->redir_str[i], "<"))
			link->redir[i] = S_L;
		else
			link->redir[i] = -1;
		i++;
	}
	assign_redir(link->next, NULL);
	return (file ? free(file) : 0);
}

/*
** Verifie le positionnement des tokens selon leur type (parcours recursif)
*/

static t_detail	*check_cmd_syntax(t_detail *link)
{
	t_detail	*error;

	if (!link)
		return (NULL);
	if (link->redir_str && check_redir_tab(link->redir_str))
		return (cmd_pars_error(link, 4));
	if (link->pipe && (!link->next || (link->next && !link->next->argv)))
		return (cmd_pars_error(link, 5));
	if ((error = check_cmd_syntax(link->next)))
		return (error);
	return (NULL);
}

/*
** Assigne le type des tokens et verifie leur placement
** Appelle la fonction de creation des sous-listes, donne leurs types aux
** maillons et aux redirs des sous-listes
*/

t_lex			*parser(t_lex *lex)
{
	t_lex		*cursor;
	t_detail	*det_error;
	t_lex		*sep_error;

	cursor = lex;
	det_error = NULL;
	sep_error = NULL;
	while (cursor && !det_error)
	{
		if (!is_sep(cursor->str))
		{
			cursor->lst = str_to_lst(cursor->str);
			assign_redir(cursor->lst, NULL);
			det_error = check_cmd_syntax(cursor->lst);
		}
		else
			cursor->lst = NULL;
		cursor = cursor->next;
	}
	if (det_error)
		return (free_all(lex));
	sep_error = check_sep_syntax(lex);
	return (sep_error ? free_all(lex) : lex);
}
