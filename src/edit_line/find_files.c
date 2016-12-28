/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:59:18 by rvievill          #+#    #+#             */
/*   Updated: 2016/12/23 16:00:44 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"

/*
** recupere le chemin au mooment de la completion
*/

char			**find_files(t_cursor *cursor, t_info *info, int i)
{
	int			j;

	j = i;
	while (j > 0 && cursor->line[j - 1] != ' ')
		j--;
	info->dir = ft_strsub(cursor->line, j, i - j);
	select_dir(info);
	return (NULL);
}
