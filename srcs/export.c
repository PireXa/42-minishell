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

t_exporttable *add_export_node(void *key, void *value)
{
    t_exporttable *new;

    new = malloc(sizeof(t_exporttable));
    if (!new)
        return (NULL);
    if (!value)
        value = "";
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_export_node_front(t_exporttable **head, t_exporttable *new)
{
    if (!head || !new)
        return ;
    new->next = *head;
    *head = new;
}

void add_export_node_back(t_exporttable **lst, t_exporttable *new)
{
    t_exporttable *tmp;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

char **key_and_value(char *str)
{
    char **key_value;
    int i;

    i = 0;
    key_value = malloc(sizeof(char *) * 2);
    while (str[i] && str[i] != '=')
        i++;
    key_value[0] = ft_substr(str, 0, i);
    if (str[i] == '=')
        key_value[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
    else
        key_value[1] = NULL;
    return (key_value);
}

void export(t_minithings *minithings)
{
    int i;
    char **onevar;
    int ind;

    i = 0;
    if (ft_strcmp(minithings->cmds[0][0], "export") == 0 && !minithings->cmds[0][1])
        show_export_list(minithings, 0);
    else if (minithings->cmds[0][1])
        while (minithings->cmds[0][++i])
        {
            onevar = key_and_value(minithings->cmds[0][i]);
            if ((ind = check_duplicated(minithings->export, onevar[0])))
            {
                if (onevar[1])
                    value_modifier(minithings->export, onevar[1], ind);
            }
            else
                add_export_node_back(minithings->export, add_export_node(onevar[0], onevar[1]));
        }
}
