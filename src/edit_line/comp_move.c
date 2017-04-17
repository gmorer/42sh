/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:12:02 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:12:03 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** deplace a droite la position initiale pendant la completion
*/

void				s_right(t_info *info)
{
	while (info->arg->current != 1)
		info->arg = info->arg->next;
	info->arg->current = 0;
	info->arg->next->current = 1;
	while (info->arg->start != 1)
		info->arg = info->arg->next;
}

/*
** deplace a gauche la position initiale pendant la completion
*/

void				s_left(t_info *info)
{
	while (info->arg->current != 1)
		info->arg = info->arg->next;
	info->arg->current = 0;
	info->arg->prev->current = 1;
	while (info->arg->start != 1)
		info->arg = info->arg->next;
}
