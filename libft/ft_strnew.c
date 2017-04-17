/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:41:46 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:41:46 by rvievill         ###   ########.fr       */
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
