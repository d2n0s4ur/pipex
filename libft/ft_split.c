/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:05:04 by jnoh              #+#    #+#             */
/*   Updated: 2022/04/16 16:05:29 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free_element(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

static char	*ft_strndup(char const *str, size_t	len)
{
	char	*ret;

	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, str, len);
	ret[len] = 0;
	return (ret);
}

static int	ft_do_split(char **ret, char const *str, char c)
{
	size_t	i;
	size_t	index;
	size_t	len;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			len = 0;
			while (str[i + len] != c && str[i + len])
				len++;
			ret[index] = ft_strndup(str + i, len);
			if (!ret[index])
				return (ft_free_element(ret));
			index++;
			i = i + len;
		}
		else
			i++;
	}
	ret[index] = 0;
	return (1);
}

static size_t	ft_get_split_size(char const *str, char c)
{
	size_t	size;
	size_t	i;
	int		flag;

	flag = 1;
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (flag == 0)
				size++;
			flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	if (flag == 0)
		size++;
	return (size);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	size_t	size;

	if (!str)
	{
		ret = (char **)malloc(1 * sizeof(char *));
		if (!ret)
			return (0);
		ret[0] = (char *)(0);
		return (ret);
	}
	size = ft_get_split_size(str, c);
	ret = (char **)malloc((size + 1) * sizeof(char *));
	if (ret == 0)
		return (0);
	if (!ft_do_split(ret, str, c))
		return (0);
	return (ret);
}
