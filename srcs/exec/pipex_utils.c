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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

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

char	*normi(t_path *path)
{
	char	*tmp;

	free_double_array(path->paths);
	tmp = ft_strdup(path->path);
	free(path->path);
	free(path);
	return (tmp);
}

char	*find_path(char *cmd, t_extab **envp)
{
	t_path	*path;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path = malloc(sizeof(t_path));
	path->i = -1;
	path->tmp = *envp;
	while (ft_strnstr(path->tmp->k, "PATH", 4) == 0 && path->tmp->next != NULL)
		path->tmp = path->tmp->next;
	path->paths = ft_split(path->tmp->value, ':');
	while (path->paths[++path->i])
	{
		path->part_path = ft_strjoin(path->paths[path->i], "/");
		path->path = ft_strjoin(path->part_path, cmd);
		free(path->part_path);
		if (access(path->path, F_OK) == 0)
			return (normi(path));
		free(path->path);
	}
	free_double_array(path->paths);
	free(path);
	return (0);
}
