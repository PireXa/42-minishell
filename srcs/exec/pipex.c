/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:09:53 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
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

char	*find_path(char *cmd, t_exporttable **envp)
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

void	pipex(int nbr_cmds, char ***cmds, char **envp, t_minithings *mt)
{
	int	i;

	if (nbr_cmds >= 1)
	{
		i = -1;
		while (++i < nbr_cmds - 1)
		{
			child_one(cmds[i], mt, envp, i);
		}
		execute(cmds[nbr_cmds - 1], mt, envp, i);
	}
}
