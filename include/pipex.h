/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:02 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/09 10:36:13 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h> //close read write access dup dup2 execve fork pipe
# include <stdio.h> //perror
# include <sys/types.h> // fork waitpid
# include <sys/wait.h> //waitpid
# include <stdlib.h> //malloc
# include <string.h> //strerror
# include <errno.h> //strerror
# include <fcntl.h>

# include "../libft/libft.h"
# include "errors.h"
# include "../libft/ft_printf/ft_printf.h"

void	exit_error(char *str);
void	check_files(char *path1, char *path2);
char	*get_cmd(char *cmd_in, char *envp[]);

#endif
