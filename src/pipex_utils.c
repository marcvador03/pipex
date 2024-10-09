/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:22:58 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/09 10:45:16 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str)
{
	perror(str);
	exit(-1);
}

char	**search_path(char *envp[])
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0 && ft_strlen(envp[i]) > 5)
		{
			res = ft_split(envp[i] + 5, ':');
			if (res == NULL)
				exit_error(ERR_MALLOC);
		}
		i++;
	}
	return (res);
}

char	*get_cmd(char *cmd, char *envp[])
{
	char	*cmd_in;
	char	*cmd_out;
	char	**paths;
	int		i;

	paths = search_path(envp);
	cmd_in = ft_strjoin("/", cmd);
	if (cmd_in == NULL)
		exit_error(ERR_MALLOC);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_out = ft_strjoin(paths[i], cmd_in);
		if (cmd_out == NULL)
			exit_error(ERR_MALLOC);
		if (access(cmd_out, F_OK) == 0)	
			return (free(paths), free(cmd_in), cmd_out);
		i++;
	}
	return (free(paths), free(cmd_in), NULL);
	
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
