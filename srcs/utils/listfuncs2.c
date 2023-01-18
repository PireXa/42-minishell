/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINISHELL                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void	delete_elem(t_cmds **lst, int index)
{
	t_cmds	*tmp;
	t_cmds	*prev;

	if (index < 0)
		return ;
	tmp = *lst;
	if (index == 0)
	{
		*lst = tmp->next;
		free(tmp->cmd);
		free(tmp);
		return ;
	}
	while (index--)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp->cmd);
	free(tmp);
}

int	sizelst(t_cmds **lst)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	addinindex(t_cmds **lst, t_cmds *new, int index)
{
	t_cmds	*tmp;
	t_cmds	*prev;

	tmp = *lst;
	if (index == 0)
	{
		new->next = tmp;
		*lst = new;
		return ;
	}
	while (index-- && tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (index > 0)
	{
		ft_lstaddback(lst, new);
		return ;
	}
	prev->next = new;
	new->next = tmp;
}
