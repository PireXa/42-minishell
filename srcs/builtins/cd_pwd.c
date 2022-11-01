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

void	cd(t_minithings *mt, int indx)
{
	if (!mt->cmds[indx][1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			printf("amazingshell: cd: HOME not set\n");
			write(mt->wcode, "1\n", 2);
		}
		else
			write(mt->wcode, "0\n", 2);
	}
	else if (mt->cmds[indx][2])
	{
		printf("amazingshell: cd: too many arguments\n");
		write(mt->wcode, "1\n", 2);
	}
	else if (chdir(mt->cmds[indx][1]) != 0)
	{
		printf("amazingshell: cd: ");
		printf("%s: No such file or directory\n", mt->cmds[indx][1]);
		write(mt->wcode, "1\n", 2);
	}
	else
		write(mt->wcode, "0\n", 2);
}

void	pwd(t_minithings *mt)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	write(mt->wcode, "0\n", 2);
}
