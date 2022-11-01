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

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

void	builtins(t_minithings *minithings, int indx)
{
	if (ft_strcmp(minithings->cmds[indx][0], "cd") == 0)
		cd(minithings, indx);
	else if (ft_strcmp(minithings->cmds[indx][0], "pwd") == 0)
		pwd(minithings);
	else if (ft_strcmp(minithings->cmds[indx][0], "env") == 0)
		show_export_list(minithings, 1);
	else if (ft_strncmp(minithings->cmds[indx][0], "echo", 4) == 0)
		echo(minithings, indx);
	else if (ft_strncmp(minithings->cmds[indx][0], "export", 6) == 0)
		export(minithings);
	else if (ft_strncmp(minithings->cmds[indx][0], "unset", 5) == 0)
		unset(minithings);
}
