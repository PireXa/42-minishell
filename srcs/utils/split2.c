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

extern int	g_ec;

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	j--;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
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
	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg == 1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

void	exitcode_gvar(t_minithings *mt)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_itoa(g_ec);
	tmp = ft_strjoin(tmp2, "\n");
	change_errorcode(mt->export, tmp);
	free(tmp);
	free(tmp2);
	g_ec = 0;
}

void	exitcode_file(t_minithings *mt)
{
	char	*exitvalue;

	mt->rcode = open(mt->efpath, O_RDONLY);
	exitvalue = get_next_line(mt->rcode);
	while (exitvalue)
	{
		if (slen(exitvalue) > 0)
			change_errorcode(mt->export, exitvalue);
		free(exitvalue);
		exitvalue = get_next_line(mt->rcode);
	}
	free(exitvalue);
	close(mt->rcode);
}
