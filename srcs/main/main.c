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

int	g_ec = 0;

void	build_export_table(t_mthings *mt, char **envp)
{
	int		i;
	char	**el;
	char	tmp[1024];

	i = 0;
	el = ft_split(envp[i], '=');
	getcwd(tmp, sizeof(tmp));
	mt->efpath = ft_strjoin(tmp, "/.e");
	mt->export = malloc(sizeof(t_extab *));
	(*mt->export) = NULL;
	mt->wcode = open(mt->efpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	nodefront(mt->export, envvaradd("?", "0", mt));
	free_double_array(el);
	while (envp[i])
	{
		el = ft_split(envp[i], '=');
		nodeback(mt->export, envvaradd(el[0], el[1], mt));
		free_double_array(el);
		i++;
	}
}

void	free_export_table(t_extab *export)
{
	t_extab	*tmp;

	while (export)
	{
		tmp = export;
		free(tmp->k);
		free(tmp->value);
		export = export->next;
		free(tmp);
	}
	free(export);
}

void	do_things(t_mthings *mt, char **envp)
{
	(void)envp;
	if (g_ec != 0)
		exitcode_gvar(mt);
	mt->cmds = parser(mt->line, mt->export, mt);
	if (mt->cmds)
	{
		commands(mt, envp);
		free_triple_pointer(mt->cmds);
		exitcode_file(mt);
	}
	else
	{
		printf("minishell: parsing error\n");
		change_errorcode(mt->export, "1\n");
	}
	free(mt->line);
	delete_linked_list(*mt->ins);
	free(mt->ins);
	delete_linked_list(*mt->outs);
	free(mt->outs);
	unlink(".heredoc");
}

void	insandouts(t_mthings *mt)
{
	mt->ins = malloc(sizeof(t_cmds *));
	(*mt->ins) = NULL;
	ft_lstaddback(mt->ins, ft_lstnew(ft_strdup("exit"), 0, 0));
	mt->outs = malloc(sizeof(t_cmds *));
	(*mt->outs) = NULL;
	ft_lstaddback(mt->outs, ft_lstnew(ft_strdup("echo"), 0, 0));
}

int	main(int ac, char **av, char **envp)
{
	t_mthings	*mt;
	char		*colorful_path;

	mt = (t_mthings *) malloc(sizeof(t_mthings));
	build_export_table(mt, envp);
	while (ac != slen(av[ac]))
	{
		insandouts(mt);
		sig_handler();
		colorful_path = get_prompt();
		mt->line = readline(colorful_path);
		free(colorful_path);
		if (!mt->line)
			megafree(mt);
		if (!only_space(mt->line))
		{
			add_history(mt->line);
			if (slen(mt->line) > 0)
				do_things(mt, envp);
		}
		else
			free_emptyline(mt);
	}
}
