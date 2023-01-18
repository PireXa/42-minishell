/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:07:12 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void	cleanup_utils(t_cmds **cmds, t_cmds *tmp, int j)
{
	char	*tmp2;

	if (tmp->next && slen(tmp->cmd) == 2)
	{
		tmp->redirect = 1;
		free(tmp->cmd);
		tmp->cmd = ft_strdup(tmp->next->cmd);
		delete_elem(cmds, j + 1);
	}
	else if (slen(tmp->cmd) >= 2 && tmp->cmd[1] != '>')
	{
		tmp->redirect = 1;
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 1);
		free(tmp2);
	}
	else if (tmp->cmd[1] == '>')
	{
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 1);
		free(tmp2);
	}
}

void	cleanup_utils2(t_cmds **cmds, t_cmds *tmp, int j)
{
	char	*tmp2;

	if (tmp->next && slen(tmp->cmd) == 3)
	{
		tmp->redirect = 2;
		tmp->cmd = ft_strdup(tmp->next->cmd);
		delete_elem(cmds, j + 1);
	}
	else if (slen(tmp->cmd) >= 3)
	{
		tmp->redirect = 2;
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 2);
		free(tmp2);
	}
}

void	cleanup_utils3(t_cmds **cmds, t_cmds *tmp, int j)
{
	char	*tmp2;

	if (tmp->next && slen(tmp->cmd) == 2)
	{
		tmp->redirect = 3;
		free(tmp->cmd);
		tmp->cmd = ft_strdup(tmp->next->cmd);
		delete_elem(cmds, j + 1);
	}
	else if (slen(tmp->cmd) >= 2 && tmp->cmd[1] != '<')
	{
		tmp->redirect = 3;
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 1);
		free(tmp2);
	}
	else if (tmp->cmd[1] == '<')
	{
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 1);
		free(tmp2);
		cleanup_redirects(cmds);
	}
}

void	cleanup_utils4(t_cmds **cmds, t_cmds *tmp, int j)
{
	char	*tmp2;

	if (tmp->next && slen(tmp->cmd) == 3)
	{
		tmp->redirect = 4;
		free(tmp->cmd);
		tmp->cmd = ft_strdup(tmp->next->cmd);
		delete_elem(cmds, j + 1);
	}
	else if (slen(tmp->cmd) > 2 && tmp->cmd[2] != '<')
	{
		tmp->redirect = 4;
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 2);
		free(tmp2);
	}
	else if (tmp->cmd[2] == '<')
	{
		tmp2 = tmp->cmd;
		tmp->cmd = ft_strdup(tmp2 + 2);
		free(tmp2);
		cleanup_redirects(cmds);
	}
}

void	cleanup_redirects(t_cmds **cmds)
{
	int		j;
	t_cmds	*tmp;

	j = 0;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd[0] == '<' && tmp->cmd[1] != '<' && tmp->quotes == 0)
			cleanup_utils(cmds, tmp, j);
		if (!ft_strncmp(tmp->cmd, "<<", 2) && tmp->quotes == 0)
			cleanup_utils2(cmds, tmp, j);
		if (tmp->cmd[0] == '>' && tmp->cmd[1] != '>' && tmp->quotes == 0)
			cleanup_utils3(cmds, tmp, j);
		if (!ft_strncmp(tmp->cmd, ">>", 2) && tmp->quotes == 0)
			cleanup_utils4(cmds, tmp, j);
		j++;
		tmp = tmp->next;
	}
}
