/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINISHELL                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

t_extab	*envvaradd(char *k, char *v, t_mthings *mt)
{
	t_extab	*new;

	if (ft_strcmp(k, "") == 0 || (k[0] >= '0' && k[0] <= '9'))
	{
		write(mt->wcode, "1\n", 2);
		printf("minishell: export: `%s=%s': not a valid identifier\n", k, v);
		return (NULL);
	}
	new = malloc(sizeof(t_extab));
	if (!new)
		return (NULL);
	if (!v)
		v = "";
	new->k = ft_strdup(k);
	new->value = ft_strdup(v);
	new->next = NULL;
	write(mt->wcode, "0\n", 2);
	return (new);
}

char	**key_and_value(char **cmd, char *line, int *p)
{
	char	**key_value;
	int		i;

	i = 0;
	key_value = malloc(sizeof(char *) * 3);
	while (cmd[p[0]][i] && cmd[p[0]][i] != '=')
		i++;
	key_value[0] = ft_substr(cmd[p[0]], 0, i);
	if (cmd[p[0]][i] == '=' && (ft_strstr_index(line, cmd[p[0]]) == '"'
	|| ft_strstr_index(line, cmd[p[0]]) == '\''
	|| ft_strstr_index(line, cmd[p[0]]) == '$'))
	{
		p[0]++;
		key_value[1] = ft_substr(cmd[p[0]], 0, slen(cmd[p[0]]));
	}
	else if (cmd[p[0]][i] == '=')
		key_value[1] = ft_substr(cmd[p[0]], i + 1, slen(cmd[p[0]]) - i);
	else
		key_value[1] = NULL;
	key_value[2] = NULL;
	return (key_value);
}

void	change_errorcode(t_extab **export, char *code)
{
	t_extab	*tmp;

	tmp = *export;
	while (tmp->k[0] != '?')
	{
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(code);
	tmp->value[slen(tmp->value) - 1] = '\0';
}

void	mod_or_add(t_mthings *mt, int ind, char **var)
{
	if (ind)
	{
		if (var[1])
			valmod(mt->export, var[1], ind, mt);
	}
	else
	{
		nodeback(mt->export, envvaradd(var[0], var[1], mt));
	}
	free_double_array(var);
}

void	export(t_mthings *mt)
{
	int		*i;
	char	**var;
	int		ind;

	i = malloc(sizeof(int));
	i[0] = 0;
	if (ft_strcmp(mt->cmds[0][0], "export") == 0 && !mt->cmds[0][1])
		show_export_list(mt, 0);
	else if (mt->cmds[0][1])
	{
		while (mt->cmds[0][++i[0]])
		{
			var = key_and_value(mt->cmds[0], mt->line, i);
			ind = check_duplicated(mt->export, var[0]);
			mod_or_add(mt, ind, var);
		}
	}
	free(i);
}
