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

#include"../../inc/minishell.h"

t_parser	*barra(t_parser *p, char *in, t_cmds **cmd)
{
	char	*str;

	p->start = p->i + 1;
	while (in[++p->i] != '\'')
		;
	if (in[p->i + 1] == ' ')
	{
		str = str_space_dup(in, p->start, '\'');
		ft_lstaddback(cmd, ft_lstnew(ft_strjoin(str, " "), 2, 0));
		free(str);
	}
	else
		ft_lstaddback(cmd, ft_lstnew(str_space_dup(in, p->start, '\''), 2, 0));
	return (p);
}

void	adollar(t_parser *ctr, char *input,
				t_cmds **cmds, t_extab **export)
{
	char	*str2;

	if (input[ctr->i + 1] == ' ')
	{
		str2 = dollar_expansion(input, ctr->start, '"', export);
		ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str2, " "), 2, 0));
		free(str2);
	}
	else
		ft_lstaddback(cmds, ft_lstnew(
				dollar_expansion(input, ctr->start, '"', export), 2, 0));
}

void	aspas_no_dollar(t_parser *p, char *in, t_cmds **cmd)
{
	char	*str;

	if (in[p->i + 1] == ' ')
	{
		str = str_space_dup(in, p->start, '"');
		ft_lstaddback(cmd, ft_lstnew(ft_strjoin(str, " "), 2, 0));
		free(str);
	}
	else
		ft_lstaddback(cmd, ft_lstnew(str_space_dup(in, p->start, '"'), 2, 0));
}

t_cmds	*ft_last_cmd(t_cmds *cmds)
{
	if (!cmds)
	{
		cmds = ft_lstnew("", 0, 0);
		return (cmds);
	}
	while (cmds->next)
		cmds = cmds->next;
	return (cmds);
}

void	*missing_command_after_pipe(t_parser *ctr, t_cmds **cmds)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	delete_linked_list(*cmds);
	free(cmds);
	free(ctr);
	return (NULL);
}
