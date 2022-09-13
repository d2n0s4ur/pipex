/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:35:44 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/16 23:20:22 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

static size_t	get_cmd_argv_cnt(char *arg)
{
	size_t	ret;
	size_t	offset;

	ret = 0;
	while (*arg && *arg != ' ')
		arg++;
	if (*arg == ' ')
		ret++;
	while (*arg)
	{
		arg++;
		if (*arg == 34 || *arg == 39 || *arg == 96)
		{
			offset = 1;
			while (*(arg + offset) && *(arg + offset) != *arg)
				offset++;
			if (*(arg + offset) == 0)
				return (++ret);
			ret++;
			arg = arg + offset;
		}
	}
	return (++ret);
}

static void	get_cmd_argv_logic(char **ret, char *arg, size_t *count)
{
	size_t	offset;

	while (*arg)
	{
		if ((*arg == 34 || *arg == 39 || *arg == 96) && *(arg - 1) != '\\')
		{
			offset = 1;
			while (*(arg + offset) && (*(arg + offset) != *arg || \
				(*(arg + offset) == *arg && *(arg + offset - 1) == '\\')))
				offset++;
			if (*(arg + offset) == 0)
			{
				ret[(*count)++] = ft_strndup_escape(arg, offset);
				ret[*count] = 0;
				return ;
			}
			ret[(*count)++] = ft_strndup_escape(arg + 1, offset - 1);
			arg = arg + offset;
		}
		arg++;
	}
	ret[*count] = 0;
	return ;
}

static char	**get_cmd_argv(char *arg)
{
	char	**ret;
	size_t	size;
	size_t	offset;
	size_t	count;

	ret = 0;
	count = 0;
	offset = 0;
	size = get_cmd_argv_cnt(arg);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		error_handle_exit(strerror(errno), 0);
	while (*(arg + offset) && *(arg + offset) != ' ')
		offset++;
	if (*(arg + offset) == ' ')
	{
		ret[count++] = ft_strndup_escape(arg, offset);
		arg = arg + offset;
	}
	get_cmd_argv_logic(ret, arg, &count);
	return (ret);
}

char	**get_cmd_argv_func(char *arg)
{
	if (!ft_strchr(arg, 34) && !ft_strchr(arg, 39) && !ft_strchr(arg, 96))
		return (ft_split(arg, ' '));
	return (get_cmd_argv(arg));
}

char	**get_pathlist(char *envp[])
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (0);
}
