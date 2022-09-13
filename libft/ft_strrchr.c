/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:41:05 by jnoh              #+#    #+#             */
/*   Updated: 2022/03/12 14:51:10 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	index;
	int		found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			index = i;
			found = 1;
		}
		i++;
	}
	if (s[i] == '\0' && (char)c == 0)
	{
		index = i;
		found = 1;
	}
	if (found == 1)
		return ((char *)(s + index));
	return (0);
}
