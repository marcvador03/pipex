/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:55:02 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/11 11:51:38 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "errors.h"
# include "../libft/ft_printf/ft_printf.h"

void	exit_error(char *str, int err);
void	check_files(char *path1);
char	*get_cmd(char *args, char *envp[]);
void	free_split(char **ptr);

#endif
