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

int	check_duplicated(t_exporttable **export, char *str)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(*export))
	{
		if (ft_strcmp(ind(*export, i)->k, str) == 0)
			return (i);
		i++;
	}
	return (0);
}

void	valmod(t_exporttable **export, char *value, int i, t_minithings *mt)
{
	ind(*export, i)->value = ft_strdup(value);
	write(mt->wcode, "0\n", 2);
}

t_exporttable	*copy_list(t_exporttable *export, t_minithings *minithings)
{
	t_exporttable	*new;
	t_exporttable	*tmp;

	new = NULL;
	while (export)
	{
		tmp = envvaradd(export->k, export->value, minithings);
		nodeback(&new, tmp);
		export = export->next;
	}
	return (new);
}

void	showenv(t_exporttable *tmp2)
{
	while (tmp2)
	{
		if (slen(tmp2->value) > 0)
			printf("%s=%s\n", tmp2->k, tmp2->value);
		tmp2 = tmp2->next;
	}
}

void	show_export_list(t_minithings *minithings, int flag)
{
	t_exporttable	*tmp;
	t_exporttable	*tmp2;

	tmp = copy_list(*minithings->export, minithings);
	tmp2 = tmp;
	if (flag == 0)
	{
		ft_sort_list(tmp, ft_lstsize(tmp2));
		while (tmp2)
		{
			if (tmp2->k[0] != '?')
				printf("declare -x %s=\"%s\"\n", tmp2->k, tmp2->value);
			tmp2 = tmp2->next;
		}
	}
	else
		showenv(tmp2);
	delete_export(tmp);
	write(minithings->wcode, "0\n", 2);
}
