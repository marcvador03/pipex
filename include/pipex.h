/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:02 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/05 17:26:41 by mfleury          ###   ########.fr       */
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
#endif
