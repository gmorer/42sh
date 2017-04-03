/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:15:05 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/25 17:42:36 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"

t_shell	*g_shell;

/*
** debut de la completion, check si la completion ets faisable puis appelle les
** fonction necessaire a sa realisation.
*/

void			completion(t_cursor *cursor, t_hist **hist)
{
	t_info		info;
	int			i;

	(void)hist;
	g_shell->comp = 1;
	g_shell->info = &info;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	if (cursor->line[i] == ' ' || cursor->line[i] == '\0')
	{
		find_files(cursor, &info, i);
		if (info.arg)
			ft_select(&info, cursor);
		free(info.dir);
	}
	g_shell->comp = 0;
}
