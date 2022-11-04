/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/11/01 11:48:20 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

char	*only_z(char *input, int start, t_exporttable **export)
{
	char	*var_value;
	char	*key;

	if (input[start] == '$')
		start++;
	key = str_super_dup(input, start, '$');
	var_value = search_export(export, key);
	free(key);
	return (var_value);
}

int	uneven_quotes(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"')
		{
			while (input[++i] != '"')
				if (input[i] == '\0')
					return (1);
		}
		else if (input[i] == '\'')
			while (input[++i] != '\'')
				if (input[i] == '\0')
					return (1);
	}
	return (0);
}

int	dpsize(char **input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (0);
	while (input[i])
		i++;
	return (i);
}

void	quotes(t_exporttable **export)
{
	printf("Error: uneven quotes\n");
	change_errorcode(export, "127");
}

char	***parser(char *input, t_exporttable **export)
{
	t_parser	*ctr;

	if (!input)
	{
		return (NULL);
	}
	if (uneven_quotes(input) == 1)
	{
		quotes(export);
		return (NULL);
	}
	ctr = (t_parser *)malloc(sizeof(t_parser));
	return (ez_parsing(ctr, input, export));
}
