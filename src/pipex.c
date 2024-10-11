/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/11 12:05:40 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exec_cmd(char *argv, char *envp[])
{
	char	**args;
	char	*cmd;

	args = ft_split(argv, ' ');
	if (args == NULL)
		exit_error(ERR_MALLOC, ENOSPC);
	cmd = args[0];
	if (access(cmd, F_OK) == -1)
	{
		cmd = get_cmd(args[0], envp);
		if (cmd == NULL)
			return (free_split(args), -1);
	}
	if (execve(cmd, args, envp) == -1)
		return (free_split(args), errno);
	free_split(args);
	return (0);
}

void	create_child_in(int *p_fd, char *argv[], char *envp[])
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE, 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	if (exec_cmd(argv[2], envp) != 0)
		exit_error(ERR_EXEC, 0);
	close(p_fd[1]);
	close(fd);
}

void	create_child_out(int *p_fd, char *argv[], char *envp[])
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE, 0);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	if (exec_cmd(argv[3], envp) != 0)
		exit_error(ERR_EXEC, 0);
	close(p_fd[0]);
	close(fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		p_fd[2];
	pid_t	pid[2];
	int		wstatus;

	wstatus = 0;
	if (argc != 5)
		exit_error(ERR_ARG_NUM, EINVAL);
	check_files(argv[1]);
	if (pipe(p_fd) == -1)
		exit_error(ERR_PIPE_CREA, 0);
	pid[0] = fork();
	if (pid[0] == -1)
		exit_error(ERR_FORK_CREA, 0);
	if (pid[0] == 0)
		create_child_in(p_fd, argv, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		exit_error(ERR_FORK_CREA, 0);
	if (pid[1] == 0)
		create_child_out(p_fd, argv, envp);
	if (waitpid(0, &wstatus, 0) == -1)
		exit_error(ERR_WAITPID, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
