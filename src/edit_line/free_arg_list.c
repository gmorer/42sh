/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arg_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:13:58 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:05:48 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void		free_node(t_arg *node)
{
	if (node && node->name)
	{
		free(node->name);
		node->name = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

void			free_arg_list(t_arg *cur)
{
	t_arg		*begin;
	t_arg		*tmp;

	if (!cur->name)
		return ;
	begin = cur;
	cur = cur->next;
	while (cur && cur != begin)
	{
		tmp = cur->next;
		free_node(cur);
		cur = tmp;
	}
	free_node(cur);
	cur = NULL;
}
