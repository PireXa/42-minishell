/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 14:22:32 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cleanup_echo(char ***cmd, int i, int j)
{
	while (cmd[i][j] != NULL)
	{
		if (j == 0 || (j == dpsize(cmd[i])
				&& cmd[i][j][slen(cmd[i][j]) - 1] == ' '))
		{
			cmd[i][j][slen(cmd[i][j]) - 1] = '\0';
			j++;
		}
		else
		{
			j++;
		}
	}
}

void	cleanup_else(char ***cmd, int i, int j)
{
	while (cmd[i][j])
	{
		if (slen(cmd[i][j]) && cmd[i][j][slen(cmd[i][j]) - 1] == ' ')
			cmd[i][j][slen(cmd[i][j]) - 1] = '\0';
		j++;
	}
}

void	cleanup(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp("echo ", cmd[i][0]) == 0)
			cleanup_echo(cmd, i, j);
		else
			cleanup_else(cmd, i, j);
		i++;
		j = 0;
	}
}

char	*dollar_expansion(char *input, int start,
						int divider, t_extab **export)
{
	t_cmds		**vars;
	t_cmds		**values;
	int			var_len;
	char		*new_str;
	int			*i;

	i = (int [2]){start, divider};
	vars = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
	*vars = NULL;
	values = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
	*values = NULL;
	var_len = get_var_name(input, i[0], vars);
	get_val_from_export(export, vars, values);
	new_str = (char *)malloc(sizeof(char) * (ft_str_ui_len(input,
					i[0], i[1]) - var_len + ft_strlen_vars(*values) + 2));
	dollar_expanded(input, new_str, i, values);
	delete_linked_list(*vars);
	free(vars);
	delete_linked_list(*values);
	free(values);
	return (new_str);
}

char	*search_export(t_extab **export, char *key)
{
	t_extab	*tmp;
	char	*value;

	tmp = *export;
	while (tmp)
	{
		if (ft_strcmp(tmp->k, key) == 0)
		{
			value = ft_strdup(tmp->value);
			return (value);
		}
		tmp = tmp->next;
	}
	value = ft_strdup("");
	return (value);
}
