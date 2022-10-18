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

void    delete_export(t_exporttable *lst)
{
    t_exporttable *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

void    ft_sort_list(t_exporttable *tab, int size)
{
    int i;
    int j;
    char *tmpkey;
    char *tmpvalue;

    i = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (ft_strncmp(indxexport(tab, i)->key,
                           indxexport(tab, j)->key,
                           ft_strlen(indxexport(tab, i)->key)) > 0)
            {
                tmpkey = indxexport(tab, i)->key;
                tmpvalue = indxexport(tab, i)->value;
                indxexport(tab, i)->key = indxexport(tab, j)->key;
                indxexport(tab, j)->key = tmpkey;
                indxexport(tab, i)->value = indxexport(tab, j)->value;
                indxexport(tab, j)->value = tmpvalue;
            }
            j++;
        }
        i++;
    }
}

t_exporttable 	*indxexport(t_exporttable *list, int index) {
    int i;

    i = 0;
    while (i < index) {
        list = list->next;
        i++;
    }
    return (list);
}

int     check_duplicated(t_exporttable **export, char *str)
{
    int i;

    i = 0;
    while (i < ft_lstsize(*export))
    {
        if (ft_strcmp(indxexport(*export, i)->key, str) == 0)
            return (i);
        i++;
    }
    return (0);
}

void    value_modifier(t_exporttable **export, char *value, int i)
{
    indxexport(*export, i)->value = ft_strdup(value);
}

t_exporttable *copy_list(t_exporttable *list)
{
    t_exporttable *new;
    t_exporttable *tmp;

    new = NULL;
    while (list)
    {
        tmp = add_export_node(list->key, list->value);
        add_export_node_back(&new, tmp);
        list = list->next;
    }
    return (new);
}

void show_export_list(t_minithings *minithings, int flag)
{
    t_exporttable *tmp;
    t_exporttable *tmp2;

    tmp = copy_list(*minithings->export);
    tmp2 = tmp;
    if (flag == 0)
    {
        ft_sort_list(tmp, ft_lstsize(tmp2));
        while (tmp2)
        {
            printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
            tmp2 = tmp2->next;
        }
    }
    else if (flag == 1)
        while (tmp2)
        {
            if (ft_strlen(tmp2->value) > 0)
                printf("%s=%s\n", tmp2->key, tmp2->value);
            tmp2 = tmp2->next;
        }
    delete_export(tmp);
}