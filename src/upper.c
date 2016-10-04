/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:47:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/05 01:31:02 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFF_SIZE_UPPER 1

int			uppercase(char *argv1, char *argv2, char *argv3)
{
	char		*save;
	struct stat	file;
	int			fd;
	
	save = NULL;
	if (ft_strcmp(argv2, ">") != 0 && ft_strcmp(argv2, ">>") != 0)
		return (0);
	if((lstat(argv3, &file)) == -1)
	{
		fd = open(argv3, O_CREAT, 0644);
		close (fd);
	}
	if (ft_strcmp(argv2, ">>") == 0)
		fd = open(argv3, O_RDWR | O_APPEND);
	else
		fd = open(argv3, O_WRONLY | O_TRUNC);
	ft_putstr_fd(argv1, fd);
	ft_putchar_fd('\0', fd);
	//ft_putchar_fd(EOF, fd);
	close(fd);
	return (0);
}
