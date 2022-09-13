/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:22:53 by jnoh              #+#    #+#             */
/*   Updated: 2022/03/15 14:13:32 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ret;
	t_list	*lst_tmp;

	if (!lst || !f)
		return (0);
	lst_tmp = lst;
	ret = 0;
	while (lst_tmp)
	{
		tmp = ft_lstnew(f(lst_tmp->content));
		if (!tmp)
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		ft_lstadd_back(&ret, tmp);
		lst_tmp = lst_tmp->next;
	}
	return (ret);
}
