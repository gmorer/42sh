/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:14:59 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:59:37 by rvievill         ###   ########.fr       */
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
	char	tmp[max];
	int		j;

	j = 0;
	ft_bzero(tmp, max);
	ft_strcpy(tmp, &(*line)[i]);
	while (i < max)
	{
		if (i + way < max)
			(*line)[i + way] = tmp[j];
		i++;
		j++;
	}
}
