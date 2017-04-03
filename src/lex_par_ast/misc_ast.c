/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:41:24 by acottier          #+#    #+#             */
/*   Updated: 2017/03/22 17:39:24 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "exec.h"
#include <split.h>

/*
** Free tout l'arbre binaire
*/

void		free_tree(t_node *tree)
{
	t_detail	*tmp;

	tmp = NULL;
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	tree->str ? free(tree->str) : 0;
	free_detail(tree->lst);
	free(tree);
}

/*
** Initialise le nouveau node a ses valeurs par defaut
*/

static void	node_init(t_node **node)
{
	(*node)->ret_cmd = -1;
	(*node)->prev = NULL;
	(*node)->left = NULL;
	(*node)->right = NULL;
	(*node)->in = dup(0);
	(*node)->out = dup(1);
	(*node)->err = dup(2);
	(*node)->fg = 1;
}

/*
** Recherche en descendant la liste, renvoie :
** le prochain token separateur;
** OU
** le dernier token de la liste;
** OU
** NULL;
*/

t_lex		*get_sep_link(t_lex *lex)
{
	if (!(lex))
		return (NULL);
	if (!lex->lst)
		lex = lex->next;
	while (lex)
	{
		if (!lex->lst)
			return (lex);
		if (!(lex->next))
			return (NULL);
		lex = lex->next;
	}
	return (NULL);
}

/*
** Cree et renvoie un node de separateur
*/

t_node		*mknode_sep(t_lex *lex, t_node *prev)
{
	t_node	*res;

	res = NULL;
	res = (t_node *)malloc(sizeof(t_node));
	lex->placed = 1;
	node_init(&res);
	res->str = ft_strdup(lex->str);
	res->lst = NULL;
	if (prev)
	{
		res->prev = prev;
		prev->right = res;
	}
	return (res);
}

/*
** Cree et renvoie un node simple (left et right a NULL)
*/

t_node		*mknode_simple(t_lex *lex, t_node *prev)
{
	t_node	*res;

	if (!lex)
		return (NULL);
	res = NULL;
	res = (t_node *)malloc(sizeof(t_node));
	if (lex->placed == 1)
		return (NULL);
	lex->placed = 1;
	node_init(&res);
	res->str = ft_strdup(lex->str);
	res->lst = lex->lst;
	res->prev = prev;
	if (prev)
	{
		if (lex->next)
			prev->left = res;
		else
			prev->right = res;
	}
	return (res);
}
