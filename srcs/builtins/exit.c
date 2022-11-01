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

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = slen(str) - 1;
	while (i < j)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	while (n > 0)
	{
		str[i++] = n % 10 + '0';
		n = n / 10;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
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
			write(minithings->wcode, "1\n", 2);
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
