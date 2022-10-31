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

static void	echo_option(t_minithings *minithings, int indx, int i)
{
	if (minithings->cmds[indx][1][1] == 'n')
	{
		i += 2;
		while (minithings->cmds[indx][++i])
			printf("%s", minithings->cmds[indx][i]);
	}
	else
	{
		i++;
		while (minithings->cmds[indx][++i])
			printf("%s", minithings->cmds[indx][i]);
		printf("\n");
	}
}

void	echo(t_minithings *minithings, int indx)
{
	int	i;

	i = -1;
	if (!minithings->cmds[indx][1])
	{
		printf("\n");
		change_errorcode(minithings->export, "0");
		return ;
	}
	if (minithings->cmds[indx][1][0] == '-')
		echo_option(minithings, indx, i);
	else
	{
		i++;
		while (minithings->cmds[indx][++i])
		{
			printf("%s", minithings->cmds[indx][i]);
		}
		printf("\n");
	}
	change_errorcode(minithings->export, "0");
}
