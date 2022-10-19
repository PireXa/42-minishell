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

char *ft_strdupquote(char *str)
{
    char *new;
    int i;

    i = 0;
    new = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i] && str[i + 1] != '"')
    {
        new[i] = str[i];
        i++;
    }
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char **quote_splitter(char *line)
{
    char **split;
    char *tmp;
    int i;
    char *res;
    int flag;

    i = -1;
    flag = 0;
    tmp = ft_strchr(line, '"');
    if (tmp) {
        tmp++;
        res = ft_strchr(tmp, '"');
        if (res) {
            res = ft_strdupquote(tmp);
        }
    }
    split = ft_split(line, ' ');
    while (split[++i])
    {
        tmp = ft_strchr(split[i], '"');
        if (tmp && flag == 0)
        {
            //free(split[i]);
            split[i] = ft_strdup(res);
            //printf("split das qyuotes%s\n", i, split[i]);
            i++;
            split[i] = NULL;
            flag = 1;
        }
        else if(tmp && flag == 1)
            free(split[i]);
    }

    return (split);
}