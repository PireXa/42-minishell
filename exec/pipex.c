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

char	*find_path(char *cmd, t_exporttable **envp)
{
	char			**paths;
	char			*path;
	int				i;
	char			*part_path;
	t_exporttable	*tmp;

	i = 0;
	tmp = *envp;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strnstr(tmp->k, "PATH", 4) == 0 && tmp->next != NULL)
		tmp = tmp->next;
	paths = ft_split(tmp->value, ':');
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
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
