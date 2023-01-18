/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*ez_utils(t_parser *ctr, char *in, t_extab **et, t_cmds **cmds)
{
	if (in[ctr->i] == '\'')
		return (barra(ctr, in, cmds));
	else if (in[ctr->i] == '"')
		return (aspas(ctr, in, cmds, et));
	else if (in[ctr->i] == '$')
		return (dollar(ctr, in, cmds, et));
	else if (in[ctr->i] == '|')
		ft_lstaddback(cmds, ft_lstnew(
				ft_strdup("|314159265358979323846"),
				0, 0));
	else if (in[ctr->i] != ' ')
		return (every(ctr, in, cmds));
	return (ctr);
}

int	mclean(t_cmds **cmds, t_parser *ctr, t_mthings *mt, char *input)
{
	cleanup_redirsnomeio(cmds);
	if (redirsdiferentesjuntas(cmds) == 1)
	{
		missing_command_after_redir(ctr, cmds);
		return (1);
	}
	cleanup_redirects(cmds);
	cleanup_pipes(cmds);
	cleanup_output(cmds, mt);
	cleanup_input(cmds, mt);
	if ((ft_strcmp(ft_last_cmd(*cmds)->cmd, "|314159265358979323846") == 0
			&& input[slen(input) - 1] == '|')
		|| (ft_strcmp((*cmds)->cmd, "|314159265358979323846") == 0)
		|| doispipesseguidos(cmds) == 1
		|| ft_strcmp(ft_last_cmd(*cmds)->cmd, "|314159265358979323846") == 0)
	{
		missing_command_after_pipe(ctr, cmds);
		return (1);
	}
	return (0);
}
