/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:40 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:08:54 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_str_cmdpath(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	a;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	str[0] = '/';
	i = 1;
	a = -1;
	while (s1[++a] && s1[a] != ' ')
		str[i++] = s1[a];
	str[i] = 0;
	return (str);
}

int	ft_access(char	*tmp, char	**paths, char *cmd, char *path)
{
	int	i;

	if (access(tmp, X_OK) == 0)
	{
		i = -1;
		while (paths[++i])
			free(paths[i]);
		free(paths);
		free(cmd);
		free(path);
		return (1);
	}
	return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    if (!s1 || !s2)
        return (-1);
    while (i < n && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i == n)
        return (0);
    return (s1[i] - s2[i]);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0444);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0444);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0444);
	if (file == -1)
		exit(EXIT_FAILURE);
	return (file);
}
