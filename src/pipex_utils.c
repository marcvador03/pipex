/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:22:58 by mfleury           #+#    #+#             */
/*   Updated: 2024/10/10 00:32:12 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_split(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
}

void	exit_error(char *str)
{
	if (errno == 0)
		ft_printf("Error encountered: %s\n", str);
	else
		strerror(errno);
	exit(EXIT_FAILURE);
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
			res = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (res);
}

char	*get_cmd(char *args, char *envp[])
{
	char	*cmd_in;
	char	*cmd_out;
	char	**paths;
	int		i;

	paths = search_path(envp);
	if (paths == NULL)
		return (NULL);
	cmd_in = ft_strjoin("/", args);
	if (cmd_in == NULL)
		return (free_split(paths), NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_out = ft_strjoin(paths[i], cmd_in);
		if (cmd_out == NULL)
			return (free_split(paths), free(cmd_in), NULL);
		if (access(cmd_out, F_OK) == 0)
			return (free_split(paths), free(cmd_in), cmd_out);
		i++;
		free(cmd_out);
	}
	return (free_split(paths), free(cmd_in), NULL);
}

void	check_files(char *path1)
{
	int		fd[2];

	fd[0] = access(path1, F_OK);
	if (fd[0] == -1)
		exit_error(ERR_MISSING_FILE);
	fd[0] = access(path1, R_OK);
	if (fd[0] == -1)
		exit_error(ERR_FILE_PERM);
}
