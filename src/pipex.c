/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/09 10:50:03 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_cmd(char argv[], char *envp[])
{
	char	**args;
	char	*cmd;
	
	args = ft_split(argv ,' ');
	if (args == NULL)
		exit_error(ERR_MALLOC);
	cmd = args[0];
	if (access(cmd, F_OK) == -1)
		cmd = get_cmd(args[0], envp);
	if (execve(cmd, args, envp) == -1)
		exit_error(ERR_EXEC);	
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

	fd = open(argv[4], O_WRONLY);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec_cmd(argv[3], envp);
}

int	main (int argc, char *argv[], char *envp[])
{
	int		p_fd[2];
	pid_t	pid;

	if (argc != 5) // back to 5
		exit_error(ERR_ARG_NUM);
	check_files(argv[1], argv[4]);	// update 2nd arg
	if (pipe(p_fd) == -1)
		exit_error(ERR_PIPE_CREA);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK_CREA);
	if (pid == 0)
		create_child(p_fd, argv, envp);
	else
		create_parent(p_fd, argv, envp);
	return (0);
}
