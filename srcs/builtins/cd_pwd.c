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

void	cd(t_minithings *minithings, int indx)
{
	if (!minithings->cmds[indx][1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			printf("amazingshell: cd: HOME not set\n");
			change_errorcode(minithings->export, "1");
		}
		else
			change_errorcode(minithings->export, "0");
	}
	else if (minithings->cmds[indx][2])
	{
		printf("amazingshell: cd: too many arguments\n");
		change_errorcode(minithings->export, "1");
	}
	else if (chdir(minithings->cmds[indx][1]) != 0)
	{
		printf("amazingshell: cd: ");
		printf("%s: No such file or directory\n", minithings->cmds[indx][1]);
		change_errorcode(minithings->export, "1");
	}
	else
		change_errorcode(minithings->export, "0");
}

void	pwd(t_minithings *minithings)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	change_errorcode(minithings->export, "0");
}
