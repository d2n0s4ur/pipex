/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:34:42 by jnoh              #+#    #+#             */
/*   Updated: 2022/04/11 19:39:09 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	offset;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			offset = i;
			j = 0;
			while (haystack[i + j] != '\0' && haystack[i + j] == needle[j] \
				&& i + j < len)
				j++;
			if (j == ft_strlen(needle))
				return ((char *)haystack + offset);
		}
		i++;
	}
	return (0);
}
