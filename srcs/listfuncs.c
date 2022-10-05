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

#include"../inc/minishell.h"

t_cmds *ft_lstnew(void *content)
{
    t_cmds *new;

    new = malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->cmd = content;
    new->next = NULL;
    return (new);
}


void ft_lstadd_back(t_cmds **lst, t_cmds *new)
{
    t_cmds *tmp;

    if (*lst == NULL) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void ft_lstadd_front(t_cmds **lst, t_cmds *new)
{
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    new->next = *lst;
    *lst = new;
}

int ft_lstsize(t_exporttable *lst)
{
    int i;

    i = 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}

t_list	*indx(t_list *list, int index) {
    int i;

    i = 0;
    while (i < index) {
        list = list->next;
        i++;
    }
    return (list);
}