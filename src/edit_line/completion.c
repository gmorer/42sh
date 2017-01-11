/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:15:05 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/05 13:20:35 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** debut de la completion, check si la completion ets faisable puis appelle les
** fonction necessaire a sa realisation.
*/

void			completion(t_cursor *cursor, t_hist **hist)
{
	t_info		info;
	int			i;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (cursor->line[i] == ' ' || cursor->line[i] == '\0')
	{
		find_files(cursor, &info, i);
		if (info.arg)
			ft_select(&info, cursor);
	}
}
