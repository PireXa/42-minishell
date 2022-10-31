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

void	ft_sort_list(t_exporttable *l, int size)
{
	int		i;
	int		j;
	char	*tmpkey;
	char	*tmpvalue;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(ind(l, i)->k, ind(l, j)->k, slen(ind(l, i)->k)) > 0)
			{
				tmpkey = ind(l, i)->k;
				tmpvalue = ind(l, i)->value;
				char	*tmpkey2;
				tmpkey2 = ind(l, j)->k;
				ind(l, i)->k = tmpkey2;
				ind(l, j)->k = tmpkey;
				char	*tmpvalue2;
				tmpvalue2 = ind(l, j)->value;
				ind(l, i)->value = tmpvalue2;
				ind(l, j)->value = tmpvalue;
			}
			j++;
		}
		i++;
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

void	value_modifier(t_exporttable **export, char *value, int i)
{
	ind(*export, i)->value = ft_strdup(value);
	change_errorcode(export, "0");
}

t_exporttable	*copy_list(t_exporttable *export)
{
	t_exporttable	*new;
	t_exporttable	*tmp;

	new = NULL;
	while (export)
	{
		tmp = envvaradd(export->k, export->value, &export);
		nodeback(&new, tmp);
		export = export->next;
	}
	return (new);
}

void	show_export_list(t_minithings *minithings, int flag)
{
	t_exporttable	*tmp;
	t_exporttable	*tmp2;

	tmp = copy_list(*minithings->export);
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
	{
		while (tmp2)
		{
			if (slen(tmp2->value) > 0)
				printf("%s=%s\n", tmp2->k, tmp2->value);
			tmp2 = tmp2->next;
		}
	}
	delete_export(tmp);
	change_errorcode(minithings->export, "0");
}
