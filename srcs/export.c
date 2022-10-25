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

t_exporttable *add_export_node(char *key, char *value)
{
    t_exporttable *new;

    new = malloc(sizeof(t_exporttable));
    if (!new)
        return (NULL);
    if (ft_strcmp(key, "") == 0)
    {
        printf("amazingshell: export: `=%s': not a valid identifier\n", value);
        return (NULL);
    }
    if (!value)
        value = "";
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
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
    tmp->next = (*lst)->next;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

int ft_strstr_index(char *str, char *to_find)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == to_find[j])
        {
            while (str[i] == to_find[j])
            {
                i++;
                j++;
            }
            if (to_find[j] == '\0')
            {
                printf("str[i] = %c\n", str[i]);
                printf("to_find = %s\n", to_find);
                return (str[i]);
            }
            else
                j = 0;
        }
        i++;
    }
    return (-1);
}

char **key_and_value(char **cmd, char *line, int *p)
{
    char **key_value;
    int i;

    i = 0;
    key_value = malloc(sizeof(char *) * 3);
    while (cmd[p[0]][i] && cmd[p[0]][i] != '=') {
        i++;
    }
    key_value[0] = ft_substr(cmd[p[0]], 0, i);
    if (cmd[p[0]][i] == '=' && (ft_strstr_index(line, cmd[p[0]]) == '"' || ft_strstr_index(line, cmd[p[0]]) == '\'')){
        printf("2\n");
        p[0]++;
        key_value[1] = ft_substr(cmd[p[0]], 0, ft_strlen(cmd[p[0]]));
    }
    else if (cmd[p[0]][i] == '='){
        printf("1\n");
        key_value[1] = ft_substr(cmd[p[0]], i + 1, ft_strlen(cmd[p[0]]) - i);
    }
    else
    {
        printf("3\n");
        key_value[1] = NULL;
    }
    key_value[2] = NULL;
    return (key_value);
}

void export(t_minithings *minithings)
{
    int *i;
    char **onevar;
    int ind;

    i = malloc(sizeof(int));
    i[0] = 0;
    if (ft_strcmp(minithings->cmds[0][0], "export") == 0 && !minithings->cmds[0][1])
        show_export_list(minithings, 0);
    else if (minithings->cmds[0][1]) {
        while (minithings->cmds[0][++i[0]]) {
            printf("i[0] = %d\n", i[0]);
            onevar = key_and_value(minithings->cmds[0], minithings->line, i);
            printf("onevar[0] = %s\n", onevar[0]);
            printf("onevar[1] = %s\n", onevar[1]);
            printf("i[0] = %d\n\n", i[0]);
            if ((ind = check_duplicated(minithings->export, onevar[0]))) {
                if (onevar[1]) {
                    value_modifier(minithings->export, onevar[1], ind);
                }
            } else
                add_export_node_back(minithings->export, add_export_node(onevar[0], onevar[1]));
            free_double_array(onevar);
        }
    }
    free(i);
}
