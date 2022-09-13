/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:03:15 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/16 22:49:10 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

static void	arg_init(t_arg *args, char *argv[], char *envp[])
{
	ft_memset(args, 0, sizeof(args));
	args->path = get_pathlist(envp);
	args->infile_fd = open(argv[1], O_RDONLY);
	if (args->infile_fd < 0)
		error_handle(argv[1], strerror(errno));
	args->outfile_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (args->outfile_fd < 0)
		error_handle_exit(argv[4], strerror(errno));
	if (pipe(args->pipe_fd) < 0)
		error_handle_exit(strerror(errno), 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_arg	args;
	int		status;

	if (argc != 5)
		error_handle_exit("usage", "./pipex file1 cmd1 cmd2 file2");
	arg_init(&args, argv, envp);
	status = pipex(&args, argv, envp);
	ft_free_parent(&args);
	exit (status);
	return (0);
}
