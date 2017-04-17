/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:30:55 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:30:56 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *list;

	if (!alst)
		return ;
	while (*alst)
	{
		list = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = list;
	}
}
