/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/10 00:32:12 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_cmd(char *argv, char *envp[])
{
	char	**args;
	char	*cmd;

	args = ft_split(argv, ' ');
	if (args == NULL)
		exit_error(ERR_MALLOC);
	cmd = args[0];
	if (access(cmd, F_OK) == -1)
	{
		cmd = get_cmd(args[0], envp);
		if (cmd == NULL)
		{
			free_split(args);
			exit_error(ERR_MALLOC);
		}
	}
	if (execve(cmd, args, envp) == -1)
	{
		free_split(args);
		exit_error(ERR_EXEC);
	}
	free_split(args);
}

void	create_child(int *p_fd, char *argv[], char *envp[])
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec_cmd(argv[2], envp);
}

void	create_parent(int *p_fd, char *argv[], char *envp[])
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec_cmd(argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		p_fd[2];
	pid_t	pid;

	errno = 0;
	if (argc != 5)
		exit_error(ERR_ARG_NUM);
	check_files(argv[1]);
	if (pipe(p_fd) == -1)
		exit_error(ERR_PIPE_CREA);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK_CREA);
	if (pid == 0)
		create_child(p_fd, argv, envp);
	else
		create_parent(p_fd, argv, envp);
	exit(EXIT_SUCCESS);
}
