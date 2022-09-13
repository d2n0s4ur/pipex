/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:28:05 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/16 23:31:28 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

static int	check_executable(char **path, char *cmd)
{
	char	*tmp;
	char	*slashed_cmd;

	slashed_cmd = ft_strjoin("/", cmd);
	while (*path)
	{
		tmp = ft_strjoin(*path, slashed_cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(slashed_cmd);
			free(tmp);
			return (126);
		}
		free(tmp);
		path++;
	}
	free(slashed_cmd);
	if (access(cmd, F_OK) == 0)
		return (126);
	return (127);
}

static char	*get_fullpath_cmd(char **path, char *cmd, int *status)
{
	char	*tmp;
	char	*slashed_cmd;

	slashed_cmd = ft_strjoin("/", cmd);
	while (*path)
	{
		tmp = ft_strjoin(*path, slashed_cmd);
		if (access(tmp, X_OK | F_OK) == 0)
		{
			free(slashed_cmd);
			return (tmp);
		}
		free(tmp);
		path++;
	}
	free(slashed_cmd);
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	*status = check_executable(path, cmd);
	return (0);
}

static void	exe_cmd1(t_arg *args, char *argv[], char *envp[])
{
	int	status;

	args->cmd_arg = get_cmd_argv_func(argv[2]);
	args->cmd = get_fullpath_cmd(args->path, args->cmd_arg[0], &status);
	if (dup2(args->infile_fd, STDIN_FD) == -1)
	{
		ft_free_child(args);
		exit(1);
	}
	if (!(args->cmd))
	{
		ft_free_child(args);
		if (status == 127)
			error_handle(argv[2], "command not found");
		else
			error_handle("permission denied", argv[2]);
		exit (status);
	}
	dup2(args->pipe_fd[1], STDOUT_FD);
	close(args->pipe_fd[0]);
	execve(args->cmd, args->cmd_arg, envp);
}

static void	exe_cmd2(t_arg *args, char *argv[], char *envp[])
{
	int	status;

	args->cmd_arg = get_cmd_argv_func(argv[3]);
	args->cmd = get_fullpath_cmd(args->path, args->cmd_arg[0], &status);
	if (!(args->cmd))
	{
		ft_free_child(args);
		if (status == 127)
			error_handle(argv[3], "command not found");
		else
			error_handle("permission denied", argv[3]);
		exit (status);
	}
	dup2(args->pipe_fd[0], STDIN_FD);
	dup2(args->outfile_fd, STDOUT_FD);
	close(args->pipe_fd[1]);
	execve(args->cmd, args->cmd_arg, envp);
}

int	pipex(t_arg *args, char *argv[], char *envp[])
{
	int	status1;
	int	status2;

	args->pid1 = fork();
	if (args->pid1 < 0)
		error_handle_exit(strerror(errno), 0);
	if (args->pid1 == 0)
		exe_cmd1(args, argv, envp);
	args->pid2 = fork();
	if (args->pid2 < 0)
		error_handle_exit(strerror(errno), 0);
	if (args->pid2 == 0)
		exe_cmd2(args, argv, envp);
	close(args->pipe_fd[0]);
	close(args->pipe_fd[1]);
	waitpid(args->pid1, &status1, 0);
	waitpid(args->pid2, &status2, 0);
	if (status1 == 127 || status2 == 127)
		return (127);
	return (((status2 >> 8) & 0xff));
}
