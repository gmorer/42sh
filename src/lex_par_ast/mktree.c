/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:39:40 by acottier          #+#    #+#             */
/*   Updated: 2017/03/23 13:20:30 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

/*
 ** Free la liste de tokens
*/

static void		free_list(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->next)
		free_list(lex->next);
	free(lex->str);
	free(lex);
}

/*
 ** S'appelle en recursif pour creer toutes les branches (redirections)
 ** d'une expression delimitee par &&, || ou ;
*/

static void		build_branch(t_node **tree, t_lex *lex)
{
	t_lex	*cursor;

	if (!lex)
		return ;
	if (!get_sep_link(lex))
		*tree = mknode_simple(lex, *tree);
	else
	{
		cursor = get_sep_link(lex);
		*tree = mknode_sep(cursor, *tree);
		(*tree)->left = mknode_simple(lex, *tree);
		if ((*tree)->left && !ft_strcmp((*tree)->str, "&"))
			(*tree)->left->fg = 0;
		build_branch(tree, cursor->next);
	}
}

/*
 ** Cree l'AST, et renvoie sa racine
 ** Free la liste de tokens
*/

t_node			*mktree(t_lex *lex)
{
	t_node		*tree;

	if (!lex)
		return (NULL);
	tree = NULL;
	build_branch(&tree, lex);
	free_list(lex);
	while (tree && tree->prev)
		tree = tree->prev;
	return (tree);
}
