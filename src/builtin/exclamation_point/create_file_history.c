/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:01:37 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/07 15:57:22 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			file_history(char *line)
{
	int			fd;
	int			ret;

	umask(0);
	if ((fd = open(".my_history", O_WRONLY | O_CREAT, 0666)) > 0)
	{
		lseek(fd, 0, SEEK_END);
		ft_putendl_fd(line, fd);
		close(fd);
	}
}
