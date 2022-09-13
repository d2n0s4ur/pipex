/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:52:52 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/16 23:44:23 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

void	error_handle(char *str, char *arg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	error_handle_exit(char *str, char *arg)
{
	error_handle(str, arg);
	exit(1);
}

char	*ft_strndup_escape(char *src, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	mal_len;

	i = 0;
	mal_len = 0;
	while (i < len && src[i])
	{
		if (src[i++] == '\\')
			i++;
		mal_len++;
	}
	ret = (char *)malloc(sizeof(char) * (mal_len + 1));
	if (!ret)
		return (0);
	mal_len = 0;
	i = 0;
	while (i < len && src[i])
	{
		if (src[i] == '\\')
			i++;
		ret[mal_len++] = src[i++];
	}
	ret[mal_len] = 0;
	return (ret);
}

void	ft_free_parent(t_arg *arg)
{
	size_t	i;

	i = 0;
	close(arg->infile_fd);
	close(arg->outfile_fd);
	if (arg->path)
	{
		while (arg->path[i])
		{
			free(arg->path[i]);
			i++;
		}
		free(arg->path);
	}	
}

void	ft_free_child(t_arg *arg)
{
	size_t	i;

	i = 0;
	if (arg->cmd_arg)
	{
		while (arg->cmd_arg[i])
		{
			free(arg->cmd_arg[i]);
			i++;
		}
		free(arg->cmd_arg);
	}
	if (arg->cmd)
		free(arg->cmd);
}
