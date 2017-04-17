/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:31:23 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:31:24 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lsttmp;
	t_list	*new;

	if (!lst)
		return (NULL);
	lsttmp = f(lst);
	new = lsttmp;
	while ((lst = lst->next))
	{
		lsttmp->next = f(lst);
		lsttmp = lsttmp->next;
	}
	return (new);
}
