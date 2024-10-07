/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:43 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/07 13:14:26 by mfleury          ###   ########.fr       */
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

int	main (int argc, char *argv[]/*, char *envp[]*/)
{
	int		p_fd[2];
	int		fd[2];
	pid_t	pid;
	char	buf;
	char	**args;
	//char*str;

	if (argc < 0) // back to 5
		exit_error(ERR_ARG_NUM);
	check_files(argv[1], argv[1]);	// update 2nd arg
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[2], O_WRONLY);
	//if (fd[-0] == -1 || fd[1] == -1)
    //		exit_error(ERR_OPEN_FILE);
	if (pipe(p_fd) == -1)
		exit_error(ERR_PIPE_CREA);
	pid = fork();
	if (pid == -1)
		exit_error(ERR_FORK_CREA);
	dup2(fd[0], p_fd[0]);
//	dup2(fd[1], p_fd[1]);
	if (pid == 0)
	{
		close(p_fd[1]);
		while (read(p_fd[0], &buf, 1) != 0)
			write(STDIN_FILENO, &buf, 1);
		close(p_fd[0]);
		exit(0);
	}
	else
	{
		close(p_fd[0]);
		args = ft_split(argv[2] ,' ');
		if (args == NULL)
			exit_error(ERR_MALLOC);
		execve(args[0], args, NULL);	
		close(p_fd[1]);
		wait(NULL);
		exit(0);
	}
	return (0);
}
