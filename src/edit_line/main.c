/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 17:20:11 by rvievill          #+#    #+#             */
/*   Updated: 2016/12/19 15:53:24 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"

int		main(void)
{
	char	*line;
	t_hist	*hist;

	hist = NULL;
	while (1)
	{
		edit_line(&line, &hist);
		if (!ft_strcmp("exit", line))
			break ;
		free(line);
	}
	return (0);
}
