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

int uneven_quotes(char *input, char duborsing)
{
    int i;
    int quotes;

    i = -1;
    quotes = 0;
    while (input[++i])
    {
        if (input[i] == duborsing)
            quotes++;
    }
    if (quotes % 2 != 0)
        return (1);
    return (0);
}

void    print_triple_pointer(char ***triple)
{
    int i;
    int j;

    i = 0;
    while(triple[i])
    {
        j = 0;
        printf("New Command\n");
        while (triple[i][j])
        {
            printf("%s\n", triple[i][j]);
            j++;
        }
        i++;
    }
}

t_cmds **build_cmdtable(t_minithings *mt, t_cmds **cmds)
{
    int i;
    int s;
    i = 0;

    *cmds = NULL;
    if (!mt->line)
        return (NULL);
    while (i < ft_strlen(mt->line))
    {
        if (mt->line[i] == '\'')
        {
            if (uneven_quotes(mt->line, '\'') == 0)
            {
                i++;
                s = i;
                while (mt->line[i] != '\'')
                    i++;
                ft_lstadd_back(cmds, ft_lstnew(ft_substr(mt->line, s, i - s)));

            }
            else
            {
                printf("missing closing single quote\n");
                return (NULL);
            }
        }
        else if (mt->line[i] == '\"')
        {
            if (uneven_quotes(mt->line, '\"') == 0)
            {
                i++;
                s = i - 1;
                while (mt->line[i] != '\"')
                    i++;
                ft_lstadd_back(cmds, ft_lstnew(ft_substr(mt->line, s, i - s)));
            }
            else
            {
                printf("missing closing double quote\n");
                return (NULL);
            }
        }
        else if (mt->line[i] == '|')
        {
            ft_lstadd_back(cmds, ft_lstnew("|"));
        }
        else if (mt->line[i] == ' ')
        {
            while (mt->line[i] == ' ') {
                i++;
            }
            if (mt->line[i] != '|' && mt->line[i - 2] != '|')
                ft_lstadd_back(cmds, ft_lstnew(" "));
            i--;
        }
        else
        {
            s = i;
            while (mt->line[i] != ' ' && mt->line[i] != '|'
            && mt->line[i] != '\'' && mt->line[i] != '"' && mt->line[i] != '\0')
                i++;
            ft_lstadd_back(cmds, ft_lstnew(ft_substr(mt->line, s, i - s)));
            i--;
        }
        i++;
    }
    return (cmds);
}

char ***build_triple_pointer(t_cmds **cmds)
{
    int size;
    char ***triple;
    int i;

    size = pipe_counter(*cmds) + 1;
    triple = malloc(sizeof(char **) * (size + 1));
    i = -1;

    if (!*cmds)
        return (NULL);
    while (++i < size)
    {
        triple[i] = cmd_maker(*cmds, i + 1);
    }
    triple[i] = NULL;
    print_triple_pointer(triple);
    return (triple);
}