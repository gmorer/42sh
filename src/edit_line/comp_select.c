/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:12:09 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:12:10 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

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
