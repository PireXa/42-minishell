/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	i = -1;
	if (!s1)
		exit(42);
	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	while (s1[++i] && i < n)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

int	ft_strlen_vars(t_cmds *vars)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = vars;
	while (tmp)
	{
		i += slen(tmp->cmd);
		tmp = tmp->next;
	}
	return (i);
}

int	get_var_name(char *in, int start, t_cmds **lst)
{
	int	i;
	int	ctr;
	int	var_len;

	i = start - 1;
	ctr = 0;
	var_len = 0;
	while (in[++i])
	{
		while (in[i] && in[i] != '$')
			i++;
		if (in[i] == '$')
			i++;
		while (in[i] && in[i] != ' ' && in[i] != '$'
			&& in[i] != '"' && in[i++] != '\'')
			ctr++;
		ft_lstadd_back(lst, ft_lstnew(
				ft_strndup(in + i - ctr, ctr)));
		if (ctr != 0)
			var_len += ctr + 1;
		ctr = 0;
		i--;
	}
	return (var_len);
}

void	get_val_from_export(t_exporttable **export,
							t_cmds **vars, t_cmds **values)
{
	t_cmds			*tmp;
	t_exporttable	*tmp2;

	tmp = *vars;
	tmp2 = *export;
	while (tmp)
	{
		while (tmp2)
		{
			if (ft_strcmp(tmp->cmd, tmp2->k) == 0)
			{
				ft_lstadd_back(values, ft_lstnew(ft_strdup(tmp2->value)));
				break ;
			}
			tmp2 = tmp2->next;
		}
		if (tmp2 == NULL)
			ft_lstadd_back(values, ft_lstnew(ft_strdup("")));
		tmp2 = *export;
		tmp = tmp->next;
	}
}

void	dollar_expanded(char *in, char *new_str, int *ij, t_cmds **vars)
{
	int		i;
	int		j;
	int		g;
	t_cmds	*tmpvars;

	tmpvars = *vars;
	i = ij[0] - 1;
	j = -1;
	while (in[++i] != ij[1])
	{
		if (in[i] == '$')
		{
			g = -1;
			while (tmpvars->cmd[++g])
				new_str[++j] = tmpvars->cmd[g];
			while (in[++i] && in[i] != ' ' && in[i] != '$'
				&& in[i] != '"' && in[i] != '\'')
				;
			i--;
			tmpvars = tmpvars->next;
		}
		else
			new_str[++j] = in[i];
	}
	new_str[++j] = '\0';
}
