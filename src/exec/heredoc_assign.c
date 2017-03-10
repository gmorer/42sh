/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:50:09 by acottier          #+#    #+#             */
/*   Updated: 2017/02/27 18:37:00 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "exec.h"

void	heredoc_assign(t_node *tree)
{
	if (tree)
	{
		heredoc_assign(tree->left);
		if (tree->lst)
			if (select_redir(tree))
				tree->ret_cmd = 1;
		heredoc_assign(tree->right);
	}
}
