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

int ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int ft_atoi(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

void	exitin(char ****quad, t_minithings *minithings, int i)
{
	int	exitcode;

	printf("exit\n");
	if (quad[i][0][1])
	{
		if (!ft_isnumber(quad[i][0][1]))
		{
			printf("exit: %s: numeric argument required\n", quad[i][0][1]);
			exitcode = 2;
		}
		else if (quad[i][0][2])
		{
			printf("exit: too many arguments\n");
			change_errorcode(minithings->export, "1");
			return ;
		}
		else
			exitcode = ft_atoi(quad[i][0][1]);
	}
	else
		exitcode = 0;
	freequadpointer(quad);
	exit(exitcode);
}
