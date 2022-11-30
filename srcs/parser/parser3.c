/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_str_ui_len(const char *s, int start, int letra)
{
	int	i;

	i = start;
	while (s[i] && s[i] != letra)
		i++;
	return (i - start);
}

char	*str_space_dup(const char *s1, int start, int letra)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	if (!s1)
		exit(42);
	str = (char *)malloc(ft_str_ui_len(s1, start, letra) + 1);
	if (!str)
		return (NULL);
	i = start;
	while (s1[i] && s1[i] != letra)
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	pipe_counter(t_cmds *fds)
{
	int	i;

	i = 0;
	while (fds)
	{
		if (fds->cmd && ft_strcmp(fds->cmd, "|314159265358979323846") == 0)
			i++;
		fds = fds->next;
	}
	return (i);
}

int	str_super_len(char *in, int start)
{
	int	i;

	i = start - 1;
	while (in[++i] && in[i] != 32 && in[i] != 36 && in[i] != 34
		&& in[i] != '|')
		;
	return (i);
}
