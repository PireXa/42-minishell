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

#include "pipex_bonus.h"
#include "../../inc/minishell.h"

char	*findpath(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_stnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_spit(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_stjoin(paths[i], "/");
		path = ft_stjoin(part_path, cmd);
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

int	redirects(int ac, char **av, char **envp)
{
	int		*i_fd1_fd2;

	i_fd1_fd2 = (int [3]){0, 0, 0};
	printf("ac = %d\n", ac);
	if (ac >= 4)
	{
		if (ft_stncmp(av[1], "here_doc", 8) == 0)
		{
			i_fd1_fd2[0] = 3;
			i_fd1_fd2[2] = open_file(av[ac - 1], 0);
			ft_here_doc(av[2], ac);
		}
		else
		{
			i_fd1_fd2[0] = 2;
			if (ft_strncmp(av[0], "STANDARD_INPUT", 14) != 0)
				i_fd1_fd2[1] = open_file(av[0], 2);
			else
				i_fd1_fd2[1] = 0;
			if (ft_strncmp(av[ac - 1], "STANDARD_OUTPUT", 14) != 0)
			{
				printf("av[ac - 1] = %s\n", av[ac - 1]);
				i_fd1_fd2[2] = open_file(av[ac - 1], 1);
			}
			else
			{
				i_fd1_fd2[2] = 1;
			}
			dup2(i_fd1_fd2[1], STDIN_FILENO);
		}
		while (i_fd1_fd2[0] < ac -2)
			childone(av[i_fd1_fd2[0]++], envp);
		dup2(i_fd1_fd2[2], STDOUT_FILENO);
		exec(av[ac - 2], envp);
	}
	return (0);
}
