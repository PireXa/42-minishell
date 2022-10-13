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

void commands(t_minithings *minithings, char **envp)
{
    int nbr_cmds;
    int pid;

    nbr_cmds = -1;
    sig_handler_block();
    if (ft_strncmp(minithings->cmds[0][0], "exit", 4) == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (is_builtin(minithings->cmds[0][0]) && !minithings->cmds[1])
    {
        builtins(minithings);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        while (minithings->cmds[++nbr_cmds])
            ;
        pipex(nbr_cmds, minithings->cmds, envp, minithings);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
