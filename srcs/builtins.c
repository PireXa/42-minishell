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

void builtins(char *line)
{
    if (ft_strncmp(line, "exit", 4) == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (ft_strncmp(line, "cd", 1) == 0) {
        if (ft_strlen(line) == 2)
            chdir(getenv("HOME"));
        else
            chdir(line + 3);
    }
    else if (ft_strncmp(line, "pwd", 3) == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    else
        return ;
}