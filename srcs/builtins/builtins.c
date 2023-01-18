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
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(str, "export", 7) == 0)
		return (2);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (2);
	if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	return (0);
}

void	builtins(t_mthings *minithings, int indx)
{
	if (ft_strncmp(minithings->cmds[indx][0], "cd", 3) == 0)
		cd(minithings, indx);
	else if (ft_strcmp(minithings->cmds[indx][0], "pwd") == 0)
		pwd(minithings);
	else if (ft_strcmp(minithings->cmds[indx][0], "env") == 0)
		show_export_list(minithings, 1);
	else if (ft_strncmp(minithings->cmds[indx][0], "echo", 5) == 0)
		echo(minithings, indx);
	else if (ft_strncmp(minithings->cmds[indx][0], "export", 7) == 0)
		export(minithings);
	else if (ft_strncmp(minithings->cmds[indx][0], "unset", 6) == 0)
		unset(minithings);
}
