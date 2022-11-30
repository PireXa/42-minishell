/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_triple(char *s1, char *s2, char *s3)
{
	char	*str;
	int		i;
	int		j;
	int		l;

	i = -1;
	j = -1;
	l = -1;
	str = (char *)malloc(sizeof(char) * (slen(s1) + slen(s2) + slen(s3) + 1));
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	while (s3[++l])
		str[i + j + l] = s3[l];
	str[i + j + l] = '\0';
	return (str);
}

char	*paint_prompt(char *str, char *color)
{
	char	*tmp;

	tmp = ft_strjoin_triple(color, str, RES);
	free(str);
	return (tmp);
}

char	*paint_prompt_2(char *str, char *color)
{
	char	*tmp;

	tmp = ft_strjoin_triple(color, str, RES);
	return (tmp);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*user;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	user = getenv("USER");
	cwd = paint_prompt(cwd, YELLOW);
	user = paint_prompt_2(user, GREEN);
	tmp = ft_strjoin_triple(user, ":", cwd);
	prompt = ft_strjoin_triple(tmp, " $> ", "");
	free(tmp);
	free(cwd);
	free(user);
	return (prompt);
}

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
