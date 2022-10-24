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

void	swap(t_exporttable *st)
{
    char *holdkey;
    char *holdvalue;

    if (ft_lstsize(st) < 2)
        return ;
    holdkey = st->key;
    holdvalue = st->value;
    st->key = indxexport(st, 1)->key;
    st->value = indxexport(st, 1)->value;
    indxexport(st, 1)->key = holdkey;
    indxexport(st, 1)->value = holdvalue;
}

void delete_node(t_exporttable **export, int index)
{
    t_exporttable *tmp;

    if (index == 1)
    {
        swap(*export);
    }
    tmp = indxexport(*export, index);
    indxexport(*export, index - 1)->next = indxexport(*export, index + 1);
    free(tmp->key);
    free(tmp->value);
    free(tmp);
}

void unset(t_minithings *minithings)
{
    int i;
    int j;
    char **inputs;

    inputs = minithings->cmds[0];
    j = 1;
    while(inputs[j])
    {
        if (ft_strchr(inputs[j], '='))
        {
            printf("amazingshell: unset: `");
            printf(inputs[j], 2);
            printf("': not a valid identifier\n");
            j++;
            continue ;
        }
        i = check_duplicated(minithings->export, inputs[j]);
        if (i)
            delete_node(minithings->export, i);
        j++;
    }
}