/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:36:52 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:36:53 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*s2;

	if (!s1)
		return (NULL);
	if ((s2 = malloc(sizeof(char) * ft_strlen(s1) + 1)) == NULL)
		return (NULL);
	s2 = ft_strcpy(s2, s1);
	return (s2);
}

char	*ft_strndup(char *s1, int n)
{
	char *s2;

	s2 = ft_strnew(n);
	s2 = ft_strncpy(s2, s1, n);
	return (s2);
}
