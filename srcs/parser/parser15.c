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

void	cleanup_input2(t_mthings *mt)
{
	int		i;

	i = 0;
	if (!*mt->ins)
	{
		ft_lstaddback(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0));
		return ;
	}
	if (ft_strcmp(idx(mt->ins, 0)->cmd, "PIPETEMPIPE") == 0)
	{
		addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0), 0);
		i++;
	}
	if (ft_strcmp(idx(mt->ins, sizelst(mt->ins))->cmd, "PIPETEMPIPE") == 0)
		addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"),
				0, 0), sizelst(mt->ins));
	while (i <= sizelst(mt->ins))
	{
		if (ft_strcmp(idx(mt->ins, i)->cmd, "PIPETEMPIPE") == 0
			&& ft_strcmp(idx(mt->ins, i + 1)->cmd, "PIPETEMPIPE") == 0)
			addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0), i++ + 1);
		i++;
	}
}

void	loopdoinput(t_cmds **cmds, t_mthings *mt, int *ij, int *apagar)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "|314159265358979323846") == 0 && tmp->next)
		{
			ft_lstaddback(mt->ins, ft_lstnew(ft_strdup("PIPETEMPIPE"), 0, 0));
			tmp = tmp->next;
			ij[1]++;
		}
		if ((tmp->redirect == 1 || tmp->redirect == 2))
		{
			apagar[ij[0]++] = ij[1];
			ft_lstaddback(mt->ins, ft_lstnew(ft_strdup(tmp->cmd),
					0, tmp->redirect));
		}
		ij[1]++;
		tmp = tmp->next;
	}
	while (ij[0]-- > 0)
		delete_elem(cmds, apagar[ij[0]]);
	cleanup_input2(mt);
}

void	cleanup_input(t_cmds **cmds, t_mthings *mt)
{
	int		apagar[347];
	int		ij[2];

	ij[0] = 0;
	ij[1] = 0;
	apagar[0] = 454545;
	delete_linked_list(*mt->ins);
	free(mt->ins);
	mt->ins = malloc(sizeof(t_cmds));
	*mt->ins = NULL;
	loopdoinput(cmds, mt, ij, apagar);
}

void	cleanup_pipes(t_cmds **c)
{
	t_cmds	*tmp;
	int		*nri;

	tmp = *c;
	nri = (int [3]){0, 0, 0};
	while (tmp)
	{
		if (tmp->redirect == 0)
		{
			nri[0] = 1;
			nri[1] = 0;
		}
		else if (tmp->redirect > 0)
			nri[1] = 1;
		tmp = tmp->next;
		nri[2]++;
	}
	if (nri[0] == 0 && nri[1] == 1)
		addinindex(c, ft_lstnew(ft_strdup("SOREDIR167483"), 0, 0), nri[2] - 1);
}
