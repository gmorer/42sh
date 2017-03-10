/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 18:48:38 by acottier          #+#    #+#             */
/*   Updated: 2017/02/22 14:55:48 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"

int				exec_check(t_node *node)
{
	char	*sep;
	t_node	*last;

	sep = node->str;
	last = (node->prev ? node->prev->left : node);
	if (ft_strcmp(sep, "&&") == 0)
		return (last->ret_cmd == 0 ? 1 : 0);
	if (ft_strcmp(sep, "||") == 0)
		return (last->ret_cmd == 0 ? 0 : 1);
	return (1);
}
