/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:41:42 by gmorer            #+#    #+#             */
/*   Updated: 2017/02/17 20:32:40 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*n;

	if ((n = malloc(sizeof(*n) * (size + 1))) == NULL)
		return (NULL);
	ft_bzero(n, size + 1);
	return (n);
}
