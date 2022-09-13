/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:07:40 by jnoh              #+#    #+#             */
/*   Updated: 2022/03/15 14:13:09 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*to_free;

	if (!lst || !del)
		return ;
	if (!(*lst))
		return ;
	tmp = *lst;
	while (tmp)
	{
		del(tmp->content);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	*lst = 0;
}
