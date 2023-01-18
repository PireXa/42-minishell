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

void	execute(t_redirs redirs, t_mthings *mt, char **envp, int indx)
{
	char	*path;

	if (redirs.out != -2)
		dup2(redirs.out, 1);
	if (redirs.in != -2)
	{
		dup2(redirs.in, 0);
	}
	if (is_builtin(redirs.cmd[0]))
	{
		builtins(mt, indx);
		free_double_array(redirs.cmd);
		return ;
	}
	path = find_path(redirs.cmd[0], mt->export);
	write(mt->wcode, "0\n", 2);
	execve(path, redirs.cmd, envp);
	free(path);
	write(mt->wcode, "127\n", 4);
	printf("Error: command not found\n");
}

void	child_one(t_redirs redirs, t_mthings *mt, char **envp, int indx)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (redirs.out == -2)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		execute(redirs, mt, envp, indx);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	deletemerdas(t_redirs redirs, t_mthings *mt)
{
	printf("minishell: No such file or directory\n");
	free_double_array(redirs.cmd);
	delete_linked_list(*mt->ins);
	free(mt->ins);
	delete_linked_list(*mt->outs);
	free(mt->outs);
}

int	childthings(t_mthings *mt, t_redirs redirs, char **envp, int nbr_cmds)
{
	int	i;

	i = -1;
	if (ft_strcmp(mt->ins[0]->cmd, "SEMINS") != 0)
	{
		dup2(redirs.in, 0);
	}
	while (++i < nbr_cmds - 1)
	{
		redirs = meteredirs(mt->cmds[i], mt->ins, mt->outs);
		if (redirs.in == -42)
		{
			deletemerdas(redirs, mt);
			return (-42);
		}
		if (ft_strcmp(mt->cmds[i][0], "SOREDIR167483") == 0)
		{
			free_double_array(redirs.cmd);
			return (i);
		}
		child_one(redirs, mt, envp, i);
	}
	return (i);
}
