/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:31:33 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:31:33 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*new_content;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	if (!(content))
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new_content = malloc(content_size)))
		{
			free(new);
			return (NULL);
		}
		new->content = ft_memcpy(new_content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
