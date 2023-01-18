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

void	nodefront(t_extab **head, t_extab *new)
{
	if (!head || !new)
		return ;
	new->next = *head;
	*head = new;
}

void	nodeback(t_extab **lst, t_extab *new)
{
	t_extab	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp->next = (*lst)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_strstr_index(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == to_find[j])
		{
			while (str[i] == to_find[j] && str[i] && to_find[j])
			{
				i++;
				j++;
			}
			if (to_find[j] == '\0')
				return (str[i]);
			else
				j = 0;
		}
		i++;
	}
	return (-1);
}
