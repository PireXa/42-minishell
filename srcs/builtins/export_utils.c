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

void	delete_export(t_exporttable *lst)
{
	t_exporttable	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->k);
		free(tmp->value);
		free(tmp);
	}
}

void	sortlistutils2(t_exporttable *l, int *i_j, char *tkey, char *tvalue)
{
	char	*tmpkey2;
	char	*tmpvalue2;

	tmpkey2 = ind(l, i_j[1])->k;
	ind(l, i_j[0])->k = tmpkey2;
	ind(l, i_j[1])->k = tkey;
	tmpvalue2 = ind(l, i_j[1])->value;
	ind(l, i_j[0])->value = tmpvalue2;
	ind(l, i_j[1])->value = tvalue;
}

void	sortlistutils(t_exporttable *l, int *i)
{
	char	*tmpkey;
	char	*tmpvalue;

	if (ft_strncmp(ind(l, i[0])->k, ind(l, i[1])->k, slen(ind(l, i[0])->k)) > 0)
	{
		tmpkey = ind(l, i[0])->k;
		tmpvalue = ind(l, i[0])->value;
		sortlistutils2(l, i, tmpkey, tmpvalue);
	}
}

void	ft_sort_list(t_exporttable *l, int size)
{
	int		*i_j;

	i_j = (int [2]){0, 0};
	while (i_j[0] < size)
	{
		i_j[1] = i_j[0] + 1;
		while (i_j[1] < size)
		{
			sortlistutils(l, i_j);
			i_j[1]++;
		}
		i_j[0]++;
	}
}

t_exporttable	*ind(t_exporttable *list, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		list = list->next;
		i++;
	}
	return (list);
}
