/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:07:12 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void execute(char **cmd, t_minithings *minithings, char **envp, int indx)
{
	int		i;
	char	*path;

    i = -1;

    if (is_builtin(cmd[0]))
    {
        builtins(minithings, indx);
        return;
    }
    path = find_path(cmd[0], minithings->export);
    if (!path)
	{
        printf("minishell: command not found: %s\n", cmd[0]);
        while (cmd[++i]) {
            free(cmd[i]);
        }
        free(cmd);
        exit(EXIT_FAILURE);
    }
    execve(path, cmd, envp);
}

void child_one(char **cmds, t_minithings *minithings, char **envp, int indx)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmds, minithings, envp, indx);
        exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
