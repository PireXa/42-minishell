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

void	swap(t_exporttable *st)
{
	char	*holdkey;
	char	*holdvalue;

	if (ft_lstsize(st) < 2)
		return ;
	holdkey = st->k;
	holdvalue = st->value;
	st->k = ind(st, 1)->k;
	st->value = ind(st, 1)->value;
	ind(st, 1)->k = holdkey;
	ind(st, 1)->value = holdvalue;
}

void	delete_node(t_exporttable **export, int index)
{
	t_exporttable	*tmp;
	t_exporttable	*prev;

	tmp = *export;
	if (index == 0)
	{
		*export = tmp->next;
		free(tmp->k);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (index--)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp->k);
	free(tmp->value);
	free(tmp);
}

void	change_unset_exitcode(t_minithings *minithings, int error)
{
	if (error)
		change_errorcode(minithings->export, "1");
	else
		change_errorcode(minithings->export, "0");
}

void	unset(t_minithings *minithings)
{
	int		i;
	int		j;
	char	**inputs;
	int		error;

	inputs = minithings->cmds[0];
	j = 1;
	error = 0;
	while (inputs[j])
	{
		if (ft_strchr(inputs[j], '='))
		{
			printf("amazingshell: unset: `");
			printf(inputs[j], 2);
			printf("': not a valid identifier\n");
			j++;
			error = 1;
			continue ;
		}
		i = check_duplicated(minithings->export, inputs[j]);
		if (i)
			delete_node(minithings->export, i);
		j++;
	}
	change_unset_exitcode(minithings, error);
}
