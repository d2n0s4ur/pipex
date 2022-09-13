/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:18:24 by jnoh              #+#    #+#             */
/*   Updated: 2022/08/16 23:40:44 by jnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

typedef struct s_arg {
	char	*cmd;
	char	**cmd_arg;
	char	**path;
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
}	t_arg;

void	error_handle(char *str, char *arg);
void	error_handle_exit(char *str, char *arg);
char	**get_pathlist(char *envp[]);
char	**get_cmd_argv_func(char *arg);
char	*ft_strndup_escape(char *src, size_t len);
void	ft_free_parent(t_arg *arg);
void	ft_free_child(t_arg *arg);
int		pipex(t_arg *args, char *argv[], char *envp[]);

#endif