/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:31:56 by jnoh              #+#    #+#             */
/*   Updated: 2022/04/15 18:55:37 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_pos_num(int nb, int fd)
{
	char	c[12];
	int		index;

	index = 0;
	c[0] = 0;
	while (nb > 0)
	{
		c[index] = nb % 10 + '0';
		nb = nb / 10;
		index++;
	}
	while (index > 0)
	{
		write(fd, &c[index - 1], 1);
		index--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	minus;
	char	zero;

	zero = '0';
	minus = '-';
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
	{
		write(fd, &zero, 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, &minus, 1);
		n = n * (-1);
	}
	ft_put_pos_num(n, fd);
}
