/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:18:57 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:18:58 by rvievill         ###   ########.fr       */
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
