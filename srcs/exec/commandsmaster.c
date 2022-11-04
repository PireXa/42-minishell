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
	int	pid;

	pid = fork();
	sig_handler_block();
	if (pid == 0)
	{
		while (cmds[++ncmd])
			;
		pipex(ncmd, cmds, envp, mt);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

char	****buildquad2(char ****quad, char ***cmds)
{
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

void	commands(t_minithings *minithings, char **envp)
{
	int		nbr_cmds;
	char	****quad;
	int		i;

	i = -1;
	nbr_cmds = -1;
	quad = NULL;
	quad = buildquad2(quad, minithings->cmds);
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
		commands_utils(quad[i], minithings, envp, nbr_cmds);
	}
	freequadpointer(quad);
}
