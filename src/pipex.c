/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/06 23:36:14 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str)
{
	perror(str);
	exit(-1);
}

void	check_files(char *path1, char *path2)
{
	int	fd[2];

	fd[0] = access(path1, F_OK);
	fd[1]= access(path1, F_OK);
	if (fd[0] == -1  || fd[1] == -1)
		exit_error(ERR_MISSING_FILE);
	fd[0] = access(path1, R_OK);
	fd[1]= access(path2, R_OK & W_OK);
	if (fd[0] == -1  || fd[1] == -1)
		exit_error(ERR_FILE_PERM);
}

int	main (int argc, char *argv[], char **env)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 2) // back to 5
		exit_error(ERR_ARG_NUM);
	check_files(argv[1], argv[1]);	// update 2nd arg
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[2], O_WRONLY);
	if (fd[-0] == -1 || fd[1] == -1)
		exit_error(ERR_OPEN_FILE);
	if (pipe(fd) == -1)
		exit_error(ERR_PIPE_CREA);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK_CREA);
	return (0);
}
