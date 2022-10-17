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

void free_double_array(char **array)
{
    int i;

    i = -1;
    while (array[++i])
        free(array[i]);
    free(array);
}

static t_minithings *build_export_table(t_minithings *minithings, char **envp)
{
    int i;
    char **envp_line;

    i = 0;
    envp_line = ft_split(envp[i], '=');
    minithings->export = malloc(sizeof(t_exporttable *));
    add_export_node_front(minithings->export, add_export_node(envp_line[0], envp_line[1]));
    free_double_array(envp_line);
    i++;
    while (envp[i])
    {
        envp_line = ft_split(envp[i], '=');
        add_export_node_back(minithings->export, add_export_node(envp_line[0], envp_line[1]));
        free_double_array(envp_line);
        i++;
    }
    return (minithings);
}

int main(int ac, char **av, char **envp)
{
    t_minithings *minithings;

    minithings = (t_minithings *)malloc(sizeof(t_minithings *) * 2);
    minithings = build_export_table(minithings, envp);
    while(ac != ft_strlen(av[ac]))
    {
        sig_handler();
        minithings->line = readline(BLUE"amazing"YELLOW"shell: "RES);
        if (!minithings->line)
            exit(1);
        add_history(minithings->line);
        minithings->cmds = parser(minithings->line, minithings->export);
        //print_triple_pointer(minithings->cmds);
        commands(minithings, envp);
        free_triple_pointer(minithings->cmds);
    }
}
