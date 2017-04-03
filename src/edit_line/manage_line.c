/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:08:04 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/10 13:18:35 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void		extend_str(t_cursor *cur)
{
	char	tmp[ft_strlen(cur->line)];

	cur->buff_size *= 2;
	ft_strcpy(tmp, cur->line);
	free(cur->line);
	cur->line = ft_strnew(cur->buff_size);
	ft_strcpy(cur->line, tmp);
}

void		move_str(char **line, int i, int way, int max)
{
	int		limit;
	char	tmp[max];
	int		j;

	j = 0;
	ft_bzero(tmp, max);
	ft_strcpy(tmp, &(*line)[i]);
	if (way < 0)
		limit = max;
	else
		limit = ft_strlen(*line);
	while (i < limit)
	{
		(*line)[i + way] = tmp[j];
		i++;
		j++;
	}
}
