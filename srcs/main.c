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

#include"../inc/minishell.h"

void free_double_array(char **array)
{
    int i;

    i = -1;
    while (array[++i])
        free(array[i]);
    free(array);
}

char *ft_strjoin_triple(char *s1, char *s2, char *s3)
{
    char *str;
    int i;
    int j;
    int l;

    i = -1;
    j = -1;
    l = -1;
    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
    while (s1[++i])
        str[i] = s1[i];
    while (s2[++j])
        str[i + j] = s2[j];
    while (s3[++l])
        str[i + j + l] = s3[l];
    str[i + j + l] = '\0';
    return (str);
}

char *paint_prompt(char *str, char *color)
{
    char *tmp;

    tmp = ft_strjoin_triple(color, str, RES);
    free(str);
    return (tmp);
}
char *paint_prompt_2(char *str, char *color)
{
    char *tmp;

    tmp = ft_strjoin_triple(color, str, RES);
    return (tmp);
}


char *get_prompt(void)
{
    char *prompt;
    char *cwd;
    char *user;
    char *tmp;

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

static t_minithings *build_export_table(t_minithings *minithings, char **envp)
{
    int i;
    char **envp_line;

    i = 0;
    envp_line = ft_split(envp[i], '=');
    minithings->export = malloc(sizeof(t_exporttable *));
    (*minithings->export) = NULL;
    add_export_node_front(minithings->export, add_export_node(envp_line[0], envp_line[1]));
    free_double_array(envp_line);
    i++;
    while (envp[i])
    {
        envp_line = ft_split(envp[i], '=');
        add_export_node_back(minithings->export, add_export_node(envp_line[0], envp_line[1]));
        free_double_array(envp_line);
        i++;
    }
    return (minithings);
}

int main(int ac, char **av, char **envp)
{
    t_minithings *minithings;
    char    *colorful_path;

    minithings = (t_minithings *)malloc(sizeof(t_minithings) * 2);
    build_export_table(minithings, envp);
    while(ac != ft_strlen(av[ac]))
    {
        sig_handler();
        colorful_path = get_prompt();
        minithings->line = readline(colorful_path);
        free(colorful_path);
        if (!minithings->line)
            exit(1);
        add_history(minithings->line);
        minithings->cmds = parser(minithings->line, minithings->export);
        if (minithings->cmds) {
            commands(minithings, envp);
            free_triple_pointer(minithings->cmds);
        }
        else {
            free(minithings->cmds);
        }
        free(minithings->line);
    }
}
