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

void	dollar_else(t_parser *ctr, char *i,
	t_cmds	**cmds, t_extab	**export)
{
	char	*str4;
	char	*str6;
	char	*str7;

	str4 = only_z(i, ctr->start, export);
	str6 = ft_strdup(get_last_content_in_cmds(cmds));
	if (!str6)
		str7 = ft_strdup(str4);
	else
		str7 = ft_strjoin(str6, str4);
	delete_elem(cmds, sizelst(cmds) - 1);
	if (i[ctr->start + 1] == ' ')
		ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str7, " "), 0, 0));
	else
		ft_lstaddback(cmds, ft_lstnew(ft_strdup(str7), 0, 0));
	free(str4);
	free(str6);
	free(str7);
}

void	dollar_if(t_parser *ctr, char *i,
	t_cmds	**cmds, t_extab	**export)
{
	char	*str5;
	char	*str4;

	str5 = only_z(i, ctr->start, export);
	str4 = ft_strdup(str5);
	if (i[ctr->start - 1] == ' ')
		ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str4, " "), 0, 0));
	else
		command_dollar(cmds, str4);
	free(str4);
	free(str5);
}

t_parser	*dollar(t_parser *ctr, char *i,
	t_cmds	**cmds, t_extab	**export)
{
	ctr->start = ctr->i;
	while (i[++ctr->i] && i[ctr->i] != ' '
		&& i[ctr->i] != '$' && i[ctr->i] != '"' && i[ctr->i] != '|')
		;
	if (i[ctr->i] == ' ' && i[ctr->i + 1] != '|'
		&& i[ctr->i + 1] && i[ctr->i + 1] != ' ')
		dollar_if(ctr, i, cmds, export);
	else
	{
		if (i[ctr->start - 1] == ' ')
			ft_lstaddback(cmds, ft_lstnew(only_z(i, ctr->start, export), 0, 0));
		else
			dollar_else(ctr, i, cmds, export);
	}
	ctr->i--;
	return (ctr);
}

t_parser	*every(t_parser *ctr, char *i, t_cmds **cmds)
{
	ctr->start = ctr->i;
	ft_lstaddback(cmds, ft_lstnew(str_super_dup(i, ctr->start, '0'), 0, 0));
	while (i[ctr->i] && i[ctr->i] != ' ' && i[ctr->i] != '$'
		&& i[ctr->i] != '"' && i[ctr->i] != '|' && i[ctr->i] != '\'')
		ctr->i++;
	ctr->i--;
	return (ctr);
}

char	***return_parser(t_parser *ctr, t_cmds **cmds)
{
	char	***cmd;
	int		cmd_ctr;

	cmd_ctr = pipe_counter(*cmds) + 1;
	cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
	ctr->i = -1;
	while (++ctr->i < cmd_ctr)
		cmd[ctr->i] = cmd_maker(*cmds, ctr->i + 1);
	cmd[ctr->i] = NULL;
	delete_linked_list(*cmds);
	free(cmds);
	cleanup(cmd);
	free(ctr);
	return (cmd);
}
