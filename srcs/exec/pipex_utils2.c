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

char	**cpydp(char **dp)
{
	char	**new;
	int		i;

	i = 0;
	while (dp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (dp[i])
	{
		new[i] = ft_strdup(dp[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_heredoc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
}

int	mexenoheredoc(char *cmd)
{
	int	fd;
	int	fd2;

	fd2 = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_heredoc(cmd, fd2);
	close(fd2);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}

int	ve_la_isso_bem(t_cmds *tmp)
{
	int	fd;

	fd = open(tmp->cmd, O_RDONLY);
	if (fd == -1)
		return (-42);
	else
		return (fd);
}
