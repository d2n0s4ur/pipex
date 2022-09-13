/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:10:48 by jnoh              #+#    #+#             */
/*   Updated: 2022/03/13 20:33:09 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_nb_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		n = n * (-1);
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ret;
	size_t	i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_get_nb_len(n);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	if (n < 0)
	{
		ret[0] = '-';
		n = n * (-1);
	}
	if (n == 0)
		ret[0] = '0';
	i = len - 1;
	while (n > 0)
	{
		ret[i--] = (n % 10) + '0';
		n = n / 10;
	}
	ret[len] = 0;
	return (ret);
}
