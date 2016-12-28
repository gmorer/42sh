/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 18:29:48 by rvievill          #+#    #+#             */
/*   Updated: 2016/12/22 13:26:58 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"

/*
** fonction pour selectioner un element pendant la completion
*/

void			space(t_info *info)
{
	t_arg		*tmp;

	tmp = info->arg;
	while (tmp->current != 1)
		tmp = tmp->next;
	if (tmp->selected == 0)
		tmp->selected = 1;
	else
		tmp->selected = 0;
	s_right(info);
}
