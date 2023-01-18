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

char	*str_super_dup(char *input, int start, int flag)
{
	int		i;
	int		j;
	char	*new_str;

	i = start - 1;
	j = -1;
	new_str = (char *)malloc(sizeof(char) * (str_super_len(input, start) + 2));
	while (input[++i] && input[i] != ' ' && input[i] != '$'
		&& input[i] != '"' && input[i] != '|' && input[i] != '\'')
		new_str[++j] = input[i];
	if (input[i] == ' ' && input[i + 1] != '|' && flag != '$')
	{
		new_str[++j] = ' ';
		new_str[++j] = '\0';
	}
	else
		new_str[++j] = '\0';
	return (new_str);
}

int	arg_ctr(t_cmds *fds, int nbr)
{
	int	i;

	i = 0;
	while (fds && nbr > 0)
	{
		if (nbr == 1)
			i++;
		if (fds->cmd && fds->cmd[0] == '|' && fds->cmd[1] != ' ')
			nbr--;
		if (fds->next == NULL)
			i++;
		fds = fds->next;
	}
	return (i - 1);
}

char	**cmd_maker(t_cmds *fds, int nbr)
{
	char	**cmd;
	int		argn;
	int		i;

	i = -1;
	argn = arg_ctr(fds, nbr);
	cmd = malloc(sizeof(char *) * (argn + 2));
	while (nbr > 1 && fds->next)
	{
		if ((fds->cmd[0] == '|' && fds->cmd[1] != ' ') || fds->next == NULL)
			nbr--;
		fds = fds->next;
	}
	while (++i < argn && fds)
	{
		cmd[i] = ft_strdup(fds->cmd);
		fds = fds->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	delete_linked_list(t_cmds *list)
{
	t_cmds	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	free_triple_pointer(char ***triple)
{
	int	i;
	int	j;

	i = 0;
	while (triple[i])
	{
		j = 0;
		while (triple[i][j])
		{
			free(triple[i][j]);
			j++;
		}
		free(triple[i]);
		i++;
	}
	free(triple);
}
