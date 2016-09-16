/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfolder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 11:35:21 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/16 12:11:08 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isfolder(char *path)
{
	struct stat file;

	if ((stat(path, &file)) == -1)
		return (-1);
	if (S_ISREG(file.st_mode) == 1)
		return (0);
	return (1);
}
