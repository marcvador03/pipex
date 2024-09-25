/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfleury <mfleury@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:01:41 by mfleury           #+#    #+#             */
/*   Updated: 2024/07/05 00:05:21 by mfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_split_size(char *s, char c)
{
	int		i;
	int		cnt;
	char	tmp;

	i = 0;
	if (s == NULL)
		return (0);
	if (ft_strlen(s) == 0)
		cnt = 0;
	else
		cnt = 1;
	tmp = '\0';
	while (s[i] != '\0')
	{
		if (s[i] == c && tmp != c)
			cnt++;
		tmp = s[i];
		i++;
	}
	return (cnt);
}

static int	ft_split_loop(char *s, char c, char **sub_str, int len)
{
	int	i;

	i = 0;
	while (s[i + len] != '\0' && s[i + len] != c)
		i++;
	*sub_str = ft_substr(s, len, i);
	if (s[i + len] != '\0')
		while (s[i + len + 1] == c)
			i++;
	return (i);
}

static void	ft_split_free(char **ptr, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		cnt;
	int		len;
	char	**ptr;
	char	*str;

	str = ft_strtrim((char *)s, &c);
	cnt = ft_split_size(str, c);
	ptr = (char **)malloc((cnt + 1) * sizeof(char *));
	if (ptr == NULL || str == NULL)
		return (NULL);
	i = -1;
	len = 0;
	while (++i < cnt && *str != '\0')
	{
		len = len + ft_split_loop(str, c, &ptr[i], len) + 1;
		if (ptr[i] == NULL)
		{
			ft_split_free(ptr, i);
			return (NULL);
		}
	}
	free(str);
	ptr[cnt] = 0;
	return (ptr);
}
