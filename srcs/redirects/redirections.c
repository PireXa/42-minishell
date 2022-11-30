//
// Created by pirexa on 30-11-2022.
//

#include "../../inc/minishell.h"

//make function that takes a double pointer and joins it into a single string with spaces between each word
char *double_pointer_join(char **str, int start)
{
	char *new;
	char *tmp;
	int i;

	i = start;
	new = NULL;
	new = malloc(slen(str[i]) + 1);
	strcpy(new, str[i]);
	tmp = new;
	new  = ft_strjoin(new, " ");
	free(tmp);
	while (str[++i])
	{
		tmp = new;
		new = ft_strjoin(tmp, str[i]);
		free(tmp);
		tmp = new;
		new = ft_strjoin(tmp, " ");
		free(tmp);
	}
	return (new);
}

char *double_pointer_join_maior(char **str, int start)
{
	char *new;
	char *tmp;
	int i;

	i = start;
	new = NULL;
	new = malloc(slen(str[i]) + 1);
	strcpy(new, str[i]);
	tmp = new;
	new  = ft_strjoin(new, " ");
	free(tmp);
	while (str[++i] && ft_strchr(str[i], '>') == NULL)
	{
		tmp = new;
		new = ft_strjoin(tmp, str[i]);
		free(tmp);
		tmp = new;
		new = ft_strjoin(tmp, " ");
		free(tmp);
	}
	return (new);
}

int size_triple_pointer(char ***str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int size_double_pointer(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	print_double_pointer(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int search_chr_double_pointer(char **str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], c))
			return (i);
		i++;
	}
	return (-1);
}

void put_output(char **tmp, char **cmds, int j)
{
	j++;
	if (search_chr_double_pointer(cmds, '>') != -1)
	{
		if (cmds[size_double_pointer(cmds) - 1][0] == '>')
			tmp[j] = ft_strdup(cmds[size_double_pointer(cmds) - 1] + 1);
		else
			tmp[j] = ft_strdup(cmds[size_double_pointer(cmds) - 1]);
	}
	else
		tmp[j] = ft_strdup("STANDARD_OUTPUT");
	j++;
	tmp[j] = NULL;
}

int srch_tptr(char ***str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (search_chr_double_pointer(str[i], c) != -1)
			return (i);
		i++;
	}
	return (-1);
}

int	redirections(t_minithings *mt, char **envp)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	if (srch_tptr(mt->cmds, '>') != -1|| srch_tptr(mt->cmds, '<') != -1)
	{
		tmp = malloc(sizeof (char *) * size_triple_pointer(mt->cmds) + 90);
		if (mt->cmds[i][0][0] == '<')
		{
			if (mt->cmds[i][0][1])
				tmp[0] = ft_strdup(mt->cmds[i][j] + 1);
			else
			{
				j++;
				tmp[0] = ft_strdup(mt->cmds[i][j]);
			}
			tmp[1] = double_pointer_join(mt->cmds[i], 2);
			i++;
		}
		else
			tmp[0] = ft_strdup("STANDARD_INPUT");
		j++;
		while (mt->cmds[i] && mt->cmds[i + 1])
		{
			tmp[j] = double_pointer_join(mt->cmds[i], 0);
			j++;
			i++;
		}
		tmp[j] = double_pointer_join_maior(mt->cmds[i], 0);
		put_output(tmp, mt->cmds[i], j);
		print_double_pointer(tmp);
		redirects(size_double_pointer(tmp), tmp, envp);
		free_double_array(tmp);
		return (1);
	}
	return (0);
}
