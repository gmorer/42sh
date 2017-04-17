/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_detail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:51:29 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/08 13:03:59 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_detail(t_detail *node)
{
	t_detail	*tmp;

	while (node)
	{
		if (node->redir_str)
			ft_strstrfree(node->redir_str);
		if (node->argv)
			ft_strstrfree(node->argv);
		if (node->redir)
			free(node->redir);
		if (node->fd_std)
			free(node->fd_std);
		if (node->fd_file)
			free(node->fd_file);
		tmp = node->next;
		free(node);
		node = tmp;
	}
}
