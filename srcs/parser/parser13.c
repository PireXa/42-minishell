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

t_parser	*aspas(t_parser *ctr, char *input,
				t_cmds **cmds, t_extab **export)
{
	ctr->start = ctr->i + 1;
	while (input[++ctr->i] != '"')
		;
	if (ft_strchr(input + ctr->start, '$'))
		adollar(ctr, input, cmds, export);
	else
		aspas_no_dollar(ctr, input, cmds);
	return (ctr);
}

char	*get_last_content_in_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;

	if (!cmds || !*cmds)
		return (NULL);
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->cmd);
}

void	command_dollar(t_cmds **cmds, char *str4)
{
	char	*str6;
	char	*str7;

	str6 = ft_strdup(ft_last_cmd(*cmds)->cmd);
	str7 = ft_strjoin(str6, str4);
	delete_elem(cmds, sizelst(cmds) - 1);
	ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str7, " "), 0, 0));
	free(str6);
	free(str7);
}

void	*missing_command_after_redir(t_parser *ctr, t_cmds **cmds)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	delete_linked_list(*cmds);
	free(cmds);
	free(ctr);
	return (NULL);
}
