/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:19:25 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:19:29 by rvievill         ###   ########.fr       */
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
