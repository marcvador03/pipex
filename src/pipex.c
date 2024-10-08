/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/08 19:19:04 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str)
{
	perror(str);
	exit(-1);
}

void	create_child(int *p_fd, char *argv[], char *envp[])
{
	char	**args;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	args = ft_split(argv[2] ,' ');
	if (args == NULL)
		exit_error(ERR_MALLOC);
	if (execve(args[0], args, envp) == -1)
		exit_error(ERR_EXEC);	
}

void	create_parent(int *p_fd, char *argv[], char *envp[])
{
	int		fd;
	char	**args;

	fd = open(argv[4], O_WRONLY);
	if (fd == -1)
		exit_error(ERR_OPEN_FILE);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	args = ft_split(argv[3] ,' ');
	if (args == NULL)
		exit_error(ERR_MALLOC);
	if (execve(args[0], args, envp) == -1)
		exit_error(ERR_EXEC);	
}

void	check_files(char *path1, char *path2)
{
	int		fd[2];

	fd[0] = access(path1, F_OK);
	fd[1]= access(path1, F_OK);
	if (fd[0] == -1  || fd[1] == -1)
		exit_error(ERR_MISSING_FILE);
	fd[0] = access(path1, R_OK);
	fd[1]= access(path2, R_OK & W_OK);
	if (fd[0] == -1  || fd[1] == -1)
		exit_error(ERR_FILE_PERM);
}

int	main (int argc, char *argv[], char *envp[])
{
	int		p_fd[2];
	pid_t	pid;

	if (argc != 5) // back to 5
		exit_error(ERR_ARG_NUM);
	check_files(argv[1], argv[1]);	// update 2nd arg
	//fd[1] = open(argv[2], O_WRONLY);
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
