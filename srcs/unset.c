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
    if (index == 1)
    {
        swap(*export);
    }
    free(indxexport(*export, index));
    indxexport(*export, index - 1)->next = indxexport(*export, index + 1);
}

void unset(t_minithings *minithings)
{
    int i;
    int j;
    char **inputs;

    inputs = minithings->cmds[0];
    j = 1;
    while(inputs[j]) {
        i = check_duplicated(minithings->export, inputs[j]);
        if (i)
            delete_node(minithings->export, i);
        j++;
    }
}