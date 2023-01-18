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

void	cleanup_output2(t_mthings *mt)
{
	int		i;

	i = 0;
	if (!*mt->outs)
	{
		ft_lstaddback(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0));
		return ;
	}
	if (ft_strcmp(idx(mt->outs, 0)->cmd, "PIPETEMPIPE") == 0)
	{
		addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0), 0);
		i++;
	}
	if (ft_strcmp(idx(mt->outs, sizelst(mt->outs))->cmd, "PIPETEMPIPE") == 0)
		addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"),
				0, 0), sizelst(mt->outs));
	while (i <= sizelst(mt->outs))
	{
		if (ft_strcmp(idx(mt->outs, i)->cmd, "PIPETEMPIPE") == 0
			&& ft_strcmp(idx(mt->outs, i + 1)->cmd, "PIPETEMPIPE") == 0)
			addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"),
					0, 0), i++ + 1);
		i++;
	}
}

void	loopdoout(t_cmds **cmds, t_mthings *mt, int *ij, int *apagar)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "|314159265358979323846") == 0 && tmp->next)
		{
			ft_lstaddback(mt->outs, ft_lstnew(ft_strdup("PIPETEMPIPE"), 0, 0));
			tmp = tmp->next;
			ij[1]++;
		}
		if ((tmp->redirect == 3 || tmp->redirect == 4))
		{
			apagar[ij[0]++] = ij[1];
			ft_lstaddback(mt->outs, ft_lstnew(ft_strdup(tmp->cmd),
					0, tmp->redirect));
		}
		ij[1]++;
		tmp = tmp->next;
	}
	while (ij[0]-- > 0)
		delete_elem(cmds, apagar[ij[0]]);
	cleanup_output2(mt);
}

void	cleanup_output(t_cmds **cmds, t_mthings *mt)
{
	int		apagar[347];
	int		ij[2];

	ij[0] = 0;
	ij[1] = 0;
	apagar[0] = 454545;
	delete_linked_list(*mt->outs);
	free(mt->outs);
	mt->outs = malloc(sizeof(t_cmds));
	*mt->outs = NULL;
	loopdoout(cmds, mt, ij, apagar);
}
