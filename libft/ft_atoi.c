/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:44:24 by jnoh              #+#    #+#             */
/*   Updated: 2022/03/13 20:29:37 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	result;

	minus = 1;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		minus = minus - (str[i++] == '-') * 2;
	result = 0;
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (result > (unsigned long long)(-1ULL / 2) && minus == 1)
		return (-1);
	if (result > (unsigned long long)(-1ULL / 2 + 1) && minus == -1)
		return (0);
	return (result * minus);
}
