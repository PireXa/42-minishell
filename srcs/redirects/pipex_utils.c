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

#include "pipex_bonus.h"

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

char	*check_commands(char *raw_cmd, char **envp)
{
	int			*i_a;
	char		**paths;
	char		*path;
	char		*cmd;
	char		*tmp;

	i_a = (int [2]){-1, -1};
	i_a[0] = -1;
	while (ft_memcmp(envp[++i_a[0]], "PATH=", 5))
		;
	path = ft_subst(envp[i_a[0]], 5, ft_strlen(envp[i_a[0]]) - 5);
	paths = ft_spit(path, ':');
	cmd = ft_str_cmdpath(raw_cmd);
	while (paths[++i_a[1]])
	{
		tmp = ft_stjoin(paths[i_a[1]], cmd);
		if (ft_access(tmp, paths, cmd, path))
			return (tmp);
		free(tmp);
	}
	exit(0);
}

int	ft_stncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && ((unsigned char)s1[i] == (unsigned char)s2[i]
			&& ((unsigned char)s1[i]) && ((unsigned char)s2[i])))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 777);
	else if (i == 1)
	{
		file = open(argv, O_RDWR | O_CREAT | O_TRUNC, 777);
		printf("file: %d\n", file);
	}
	else if (i == 2)
		file = open(argv, O_RDONLY, 777);
	if (file == -1)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	return (file);
}
