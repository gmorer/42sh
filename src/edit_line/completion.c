/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:12:16 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 16:09:44 by rvievill         ###   ########.fr       */
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
		ft_strdel(&info.file);
		free(info.dir);
	}
	g_shell->comp = 0;
}
