/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:06:54 by jnoh              #+#    #+#             */
/*   Updated: 2022/04/11 19:38:52 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[len - 1 - i] = \
			((unsigned char *)src)[len - 1 - i];
			i++;
		}
	}
	return (dst);
}
