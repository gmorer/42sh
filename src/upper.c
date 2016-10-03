/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:47:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/03 16:06:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_write(int oflag, )
{

}

int		uppercase(char *argv1, char *argv2, char *argv3)
{
	char		*save;
	struct stat	file;
	int			oflag;
	
	oflag = O_RDWR;
	save = NULL;
	if(!(lstat(argv3, file)))
	{
		fd = open(argv3, O_CREAT);
		close (fd);
	}
	if (ft_strcmp(argv2, ">>") == 0)
		oflag = O_RDWR;
	else
		oflag = O_WRONLY;

}
