/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfolder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:21:36 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/11 11:21:43 by gmorer           ###   ########.fr       */
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
