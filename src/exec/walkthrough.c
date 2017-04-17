/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walkthrough.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:15:08 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 19:15:09 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lex_par_ast.h"

/*
** Renvoie le maillon 'commande' precedant tree
*/

static t_node	*get_prev_cmd(t_node *tree)
{
	if (!tree || !tree->prev
			|| (tree->prev->left == tree && !tree->prev->prev))
		return (NULL);
	if (tree->prev->right == tree)
		return (tree->prev->left);
	if (tree->prev->prev)
		return (tree->prev->prev->left);
	return (NULL);
}

/*
** Renvoie le maillon 'commande' suivant tree
*/

static t_node	*get_next_cmd(t_node *tree)
{
	if (!tree)
		return (NULL);
	if (tree->lst)
	{
		if (tree->ret_cmd == -1)
			return (tree);
		return (get_next_cmd(tree->prev));
	}
	if (tree->left && tree->left->ret_cmd == -1)
		return (tree->left);
	else if (!tree->right)
		return (NULL);
	if (tree->right->lst)
	{
		if (tree->right->ret_cmd == -1)
			return (tree->right);
		return (NULL);
	}
	return (get_next_cmd(tree->right));
}

/*
** Cherche le prochain maillon a executer, et le dernier execute
*/

static int		init(t_node **tree, t_node **last, t_node **next, t_node **sep)
{
	if (!(*tree))
		return (1);
	*last = NULL;
	*next = NULL;
	*sep = NULL;
	*next = get_next_cmd(*tree);
	*last = get_prev_cmd(*next);
	if (!(*next))
	{
		while ((*tree)->prev)
			*tree = (*tree)->prev;
		free_tree(*tree);
		return (1);
	}
	*sep = *last ? (*last)->prev : NULL;
	return (0);
}

/*
** Renvoie le maillon 'commande' suivant a executer
*/

t_node			*walkthrough(t_node *tree)
{
	t_node	*last;
	t_node	*next;
	t_node	*sep;

	if (init(&tree, &last, &next, &sep))
		return (NULL);
	if (!sep)
		return (next);
	if (ft_strcmp(sep->str, "&&") == 0)
	{
		if (last->ret_cmd == 0)
			return (next);
		tree->ret_cmd = 1;
		return (walkthrough(next));
	}
	if (ft_strcmp(sep->str, "||") == 0)
	{
		if (last->ret_cmd == 1)
			return (next);
		next->ret_cmd = 0;
		return (walkthrough(next));
	}
	return (next);
}
