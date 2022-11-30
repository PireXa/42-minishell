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

int	search_ls(char ***cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		if (ft_strcmp(cmds[i][0], "ls") == 0)
			return (1);
	return (0);
}

void	commands_utils(char ***cmds, t_minithings *mt, char **envp, int ncmd)
{
	int		pid;
	int		status;
	int		e_stat;
	char	*adeus;
	char	*adeus1;

	pid = fork();
	sig_handler_block();
	if (pid == 0)
	{
		while (cmds[++ncmd])
			;
		pipex(ncmd, cmds, envp, mt);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		e_stat = WEXITSTATUS(status);
		adeus1 = ft_itoa(e_stat);
		adeus = ft_strjoin(adeus1, "\n");
		write(mt->wcode, adeus, slen(adeus));
		free(adeus);
		free(adeus1);
	}
}

char	****buildquad2(char ***cmds)
{
	char	****quad;

	if (search_ls(cmds))
		quad = buildquadpoint(cmds, searchlastls(cmds));
	else
	{
		quad = (char ****)malloc(sizeof(char ***) * 2);
		quad[0] = copytriple(cmds, 0, triplesize(cmds));
		quad[1] = NULL;
	}
	return (quad);
}

int	commandexist(t_minithings *mt, char **cmd)
{
	char	*path;

	if (is_builtin(cmd[0]))
		return (1);
	path = find_path(cmd[0], mt->export);
	if (!path)
	{
		write(mt->wcode, "127\n", 4);
		printf("minishell: command not found: %s\n", cmd[0]);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

void	commands(t_minithings *minithings, char **envp)
{
	int		nbr_cmds;
	char	****quad;
	int		i;

	i = -1;
	nbr_cmds = -1;
	quad = buildquad2(minithings->cmds);
	while (++i < 2 && quad[i])
	{
		if (ft_strcmp(quad[i][0][0], "exit") == 0)
		{
			exitin(quad, minithings, i);
			return ;
		}
		else if (is_builtin(quad[i][0][0]) && !quad[i][1])
		{
			builtins(minithings, 0);
			freequadpointer(quad);
			return ;
		}
		if (commandexist(minithings, quad[i][0]))
			commands_utils(quad[i], minithings, envp, nbr_cmds);
	}
	freequadpointer(quad);
}
