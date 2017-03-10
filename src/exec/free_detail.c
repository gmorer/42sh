/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_detail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 10:56:38 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/08 16:44:09 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		free_detail(t_detail *node)
{
	if (node)
	{
		if (node->redir_str)
		{
			ft_strstrfree(node->redir_str);
			node->redir_str = NULL;
		}
		if (node->argv)
		{
			ft_strstrfree(node->argv);
			node->argv = NULL;
		}
		if (node->redir)
			free(node->redir);
		if (node->fd_file)
			free(node->fd_file);
		if (node->fd_std)
			free(node->fd_std);
		free(node);
		return (0);
	}
	return (1);
}
