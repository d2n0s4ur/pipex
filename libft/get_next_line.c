/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:45:21 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/08 13:16:14 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup_until_add(char *src, int until, int add)
{
	size_t	len;
	char	*ret;
	size_t	i;

	if (!src)
		return (0);
	len = 0;
	while (src[len] != (char)until)
		len++;
	if (add != -1)
		ret = (char *)malloc((len + 2) * sizeof(char));
	else
		ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (i < len)
	{
		ret[i] = src[i];
		i++;
	}
	if (add != -1)
		ret[i++] = (char)add;
	ret[i] = 0;
	return (ret);
}

static char	*ft_strcat(char *s1, char *s2)
{
	char	*ret;
	size_t	len1;
	size_t	len2;

	if (!s1 && s2)
		return (ft_strdup_until_add(s2, 0, -1));
	if (s1 && !s2)
		return (ft_strdup_until_add(s1, 0, -1));
	if (!s1 && !s2)
	{
		ret = (char *)malloc(1 * sizeof(char));
		if (!ret)
			return (0);
		ret[0] = 0;
		return (ret);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, len2);
	ret[len1 + len2] = 0;
	return (ret);
}

static void	ft_free(char **to_free)
{
	free(*to_free);
	*to_free = 0;
}

static int	ft_get_line(char **buffer, char **lastbuffer, char **ret, int fd)
{
	int		read_size;
	char	*tmp;

	while (1)
	{
		if (ft_strchr(*lastbuffer, '\n'))
		{
			*ret = ft_strdup_until_add(*lastbuffer, '\n', '\n');
			tmp = *lastbuffer;
			*lastbuffer = ft_strdup_until_add(ft_strchr(tmp, '\n') + 1, 0, -1);
			ft_free(&tmp);
			return (1);
		}
		read_size = read(fd, *buffer, BUFFER_SIZE);
		if (read_size < 0 || (read_size == 0 && !ft_strchr(*lastbuffer, '\n')))
		{
			*ret = 0;
			return (read_size);
		}
		(*buffer)[read_size] = 0;
		tmp = *lastbuffer;
		*lastbuffer = ft_strcat(tmp, *buffer);
		ft_free(&tmp);
	}
}

char	*get_next_line(int fd)
{
	static char	*lastbuffer;
	char		*buffer;
	char		*ret;
	int			result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	result = ft_get_line(&buffer, &lastbuffer, &ret, fd);
	ft_free(&buffer);
	if (result == -1)
		ft_free(&lastbuffer);
	else if (result == 0)
	{
		ret = ft_strdup_until_add(lastbuffer, 0, -1);
		if (ret && !ft_strlen(ret))
			ft_free(&ret);
		if (!ft_strlen(lastbuffer))
			ret = 0;
		ft_free(&lastbuffer);
	}
	return (ret);
}
