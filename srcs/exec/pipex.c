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

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}

int	meteins(t_cmds **ins)
{
	int		fd;
	t_cmds	*tmp;

	tmp = *ins;
	while (tmp && ft_strcmp(tmp->cmd, "PIPETEMPIPE") != 0)
	{
		if (ft_strcmp(tmp->cmd, "SEMINS") == 0)
		{
			fd = -2;
			tmp = tmp->next;
			delete_elem(ins, 0);
			break ;
		}
		if (tmp->cmd[slen(tmp->cmd) - 1] == ' ')
			tmp->cmd[slen(tmp->cmd) - 1] = 0;
		if (tmp->redirect == 1)
			fd = ve_la_isso_bem(tmp);
		else
			fd = mexenoheredoc(tmp->cmd);
		tmp = tmp->next;
		delete_elem(ins, 0);
	}
	if (tmp)
		delete_elem(ins, 0);
	return (fd);
}

int	meteouts(t_cmds **outs)
{
	int		fd;
	t_cmds	*tmp;

	tmp = *outs;
	while (tmp && ft_strcmp(tmp->cmd, "PIPETEMPIPE") != 0)
	{
		if (ft_strcmp(tmp->cmd, "SEMOUTS") == 0)
		{
			fd = -2;
			tmp = tmp->next;
			delete_elem(outs, 0);
			break ;
		}
		if (tmp->cmd[slen(tmp->cmd) - 1] == ' ')
			tmp->cmd[slen(tmp->cmd) - 1] = 0;
		if (tmp->redirect == 4)
			fd = open(tmp->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(tmp->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp = tmp->next;
		delete_elem(outs, 0);
	}
	if (tmp)
		delete_elem(outs, 0);
	return (fd);
}

t_redirs	meteredirs(char **cmd, t_cmds **ins, t_cmds **outs)
{
	t_redirs	redirs;

	redirs.cmd = cpydp(cmd);
	redirs.in = meteins(ins);
	redirs.out = meteouts(outs);
	return (redirs);
}

void	pipex(int nbr_cmds, char ***cmds, char **envp, t_mthings *mt)
{
	t_redirs	redirs;
	int			i;

	redirs.in = -2;
	redirs.out = -2;
	if (nbr_cmds >= 1)
	{
		i = childthings(mt, redirs, envp, nbr_cmds);
		if (i == -42)
			return ;
		redirs = meteredirs(cmds[nbr_cmds - 1], mt->ins, mt->outs);
		if (redirs.in == -42)
		{
			free_double_array(redirs.cmd);
			printf("minishell: No such file or directory\n");
			return ;
		}
		if (ft_strcmp(cmds[i][0], "SOREDIR167483") == 0)
		{
			free_double_array(redirs.cmd);
			return ;
		}
		execute(redirs, mt, envp, i);
	}
}
