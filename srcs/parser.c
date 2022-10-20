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

void    print_stacks(t_cmds *stck_a)
{
    printf("\n################\n");
    while (stck_a)
    {
        printf("%s<-------\n", stck_a->cmd);
        stck_a = stck_a->next;
    }
    printf("\n################\n");
}

int ft_str_ui_len(const char *s, int start, int letra) {
    int i;

    i = start;
    while (s[i] && s[i] != letra) {
        i++;
    }
    return (i - start);
}

char *pipe_str(void){
    char *str;

    str = malloc(sizeof(char) * 2);
    str[0] = '|';
    str[1] = '\0';
    return (str);
}

char *str_space_dup(const char *s1, int start, int letra)
{
    char *str;
    size_t i;
    size_t j;

    j = 0;
    if (!s1) {
        exit(42);
    }
    str = (char *)malloc(ft_str_ui_len(s1, start, letra) + 1);
    if (!str) {
        return (NULL);
    }
    i = start;
    while (s1[i] && s1[i] != letra)
    {
        str[j] = s1[i];
        j++;
        i++;
    }
    str[j] = '\0';
    ft_strlen(str);
    return (str);
}

int pipe_counter(t_cmds *fds) {
    int i;

    i = 0;
    while (fds) {
        if (fds->cmd && fds->cmd[0] == '|')
            i++;
        fds = fds->next;
    }
    return (i);
}

int str_super_len(char *input, int start){
    int i;

    i = start - 1;
    while (input[++i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '|')
        ;
    return (i);
}

char *str_super_dup(char *input, int start, int flag)
{
    int i;
    int j;
    char *new_str;

    i = start - 1;
    j = -1;
    new_str = (char *)malloc(sizeof(char) * (str_super_len(input, start) + 1));
    while (input[++i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '|'){
        new_str[++j] = input[i];
    }
    if (input[i] == ' ' && input[i + 1] != '|' && flag != '$')
    {
        new_str[++j] = ' ';
        new_str[++j] = '\0';
    }
    else {
        new_str[++j] = '\0';
    }
    return (new_str);
}

int arg_ctr(t_cmds *fds, int nbr) {
    int i;

    i = 0;
    while (fds && nbr > 0) {
        if (nbr == 1)
            i++;
        if (fds->cmd && fds->cmd[0] == '|') {
            nbr--;
        }
        if (fds->next == NULL)
            i++;
        fds = fds->next;
    }
    return (i - 1);
}

char **cmd_maker(t_cmds *fds, int nbr)
{
    char **cmd;
    int argn;
    int i;

    i = -1;
    argn = arg_ctr(fds, nbr);
    cmd = malloc(sizeof(char *) * (argn + 1));
    while (nbr > 1 && fds->next)
    {
        if (fds->cmd[0] == '|' || fds->next == NULL)
            nbr--;
        fds = fds->next;
    }
    while (++i < argn && fds)
    {
        cmd[i] = ft_strdup(fds->cmd);
        fds = fds->next;
    }
    cmd[i] = NULL;
    return (cmd);
}

void    delete_linked_list(t_cmds *list)
{
    t_cmds *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->cmd);
        free(tmp);
    }
}

void free_triple_pointer(char ***triple)
{
    int i;
    int j;

    i = 0;
    while (triple[i])
    {
        j = 0;
        while (triple[i][j])
        {
            free(triple[i][j]);
            j++;
        }
        free(triple[i]);
        i++;
    }
    free(triple);
}

void    print_triple_pointer(char ***triple)
{
    int i;
    int j;

    i = 0;
    while (triple[i])
    {
        j = 0;
        printf("New Comand\n");
        while (triple[i][j])
        {
            printf("%s\n", triple[i][j]);
            j++;
        }
        i++;
    }
}

void delete_last_node(t_cmds *node)
{
    t_cmds *tmp;

    while (node->next)
    {
        tmp = node;
        node = node->next;
    }
    free(tmp->next->cmd);
    free(tmp->next);
    tmp->next = NULL;
}

char *ft_strndup(const char *s1, size_t n)
{
    char *str;
    size_t i;

    i = -1;
    if (!s1) {
        exit(42);
    }
    str = (char *)malloc(n + 1);
    if (!str) {
        return (NULL);
    }
    while (s1[++i] && i < n)
        str[i] = s1[i];
    str[i] = '\0';
    return (str);
}

int ft_strlen_vars(t_cmds *vars)
{
    int i;
    t_cmds *tmp;

    i = 0;
    tmp = vars;
    while (tmp)
    {
        i += ft_strlen(tmp->cmd);
        tmp = tmp->next;
    }
    return (i);
}

int    get_var_name(char *input, int start, t_cmds **lst)
{
    int i;
    int ctr;
    int var_len;

    i = start - 1;
    ctr = 0;
    var_len = 0;
    while (input[++i]) {
        while (input[i] && input[i] != '$')
            i++;
        if (input[i] == '$')
            i++;
        while (input[i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '\'') {
            ctr++;
            i++;
        }
        ft_lstadd_back(lst, ft_lstnew(ft_strndup(input + i - ctr, ctr)));
        if (ctr != 0)
            var_len += ctr + 1;
        ctr = 0;
        i--;
    }
    return (var_len);
}

void get_val_from_export(t_exporttable **export, t_cmds **vars, t_cmds **values)
{
    t_cmds *tmp;
    t_exporttable *tmp2;

    tmp = *vars;
    tmp2 = *export;
    while (tmp)
    {
        while (tmp2)
        {
            if (ft_strcmp(tmp->cmd, tmp2->key) == 0)
            {
                //free(tmp->cmd);
                ft_lstadd_back(values, ft_lstnew(ft_strdup(tmp2->value)));
                break;
            }
            tmp2 = tmp2->next;
        }
        if (tmp2 == NULL)
            ft_lstadd_back(values, ft_lstnew(ft_strdup("")));
        tmp2 = *export;
        tmp = tmp->next;
    }
/*    printf("Values from export\n");
    print_stacks(*vars);*/
 }

void dollar_expanded(char *input, char *new_str, int start, int divider, t_cmds **vars)
{
    int i;
    int j;
    int g;
    t_cmds *tmpvars;

    tmpvars = *vars;
    i = start - 1;
    j = -1;
    g = -1;
    while (input[++i] != divider)
    {
        if (input[i] == '$')
        {
            g = -1;
            while (tmpvars->cmd[++g])
                new_str[++j] = tmpvars->cmd[g];
            while (input[++i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '\'')
                ;
            i--;
            tmpvars = tmpvars->next;
        }
        else
            new_str[++j] = input[i];
    }
    new_str[++j] = '\0';
}

char  *dollar_expansion(char *input, int start, int divider, t_exporttable **export)
{
    t_cmds   **vars;
    t_cmds   **values;
    int     var_len;
    char   *new_str;

    vars = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *vars = NULL;
    values = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *values = NULL;
    var_len = get_var_name(input, start, vars);
    get_val_from_export(export, vars, values);
    new_str = (char *)malloc(sizeof(char) * (ft_str_ui_len(input, start, divider) - var_len + ft_strlen_vars(*vars) + 1));
    dollar_expanded(input, new_str, start, divider, values);
    delete_linked_list(*vars);
    free(vars);
    delete_linked_list(*values);
    free(values);
    return (new_str);
}

char *search_export(t_exporttable **export, char *key)
{
    t_exporttable *tmp;
    char *value;

    tmp = *export;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0) {
            //printf("Found key %s\n", tmp->value);
            value = ft_strdup(tmp->value);
            return (value);
        }
        tmp = tmp->next;
    }
    value = ft_strdup("");
    return (value);
}

char *only_$(char *input, int start, t_exporttable **export)
{
    char *var_value;
    char *key;

    if (input[start] == '$')
        start++;
    key = str_super_dup(input, start, '$');
    var_value = search_export(export, key);
    free(key);
    return (var_value);
}

int uneven_quotes(char *input, char duborsing)
{
    int i;
    int quotes;

    i = -1;
    quotes = 0;
    while (input[++i])
    {
        if (input[i] == duborsing)
            quotes++;
    }
    if (quotes % 2 != 0)
        return (1);
    return (0);
}

int doublepointersize(char **input)
{
    int i;

    i = 0;
    if (input == NULL)
        return (0);
    while (input[i])
        i++;
    return (i);
}

void    cleanup(char ***cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i] != NULL)
    {
        if (ft_strcmp("echo " , cmd[i][0]) == 0)
        {
            while (cmd[i][j] != NULL)
            {
                if (j == 0 || (j == doublepointersize(cmd[i]) && cmd[i][j][ft_strlen(cmd[i][j]) - 1] == ' '))
                {
                    cmd[i][j][ft_strlen(cmd[i][j]) - 1] = '\0';
                    j++;
                }
                else{
                    j++;
                }
            }
        }
        else
            while (cmd[i][j])
            {
                if (cmd[i][j][ft_strlen(cmd[i][j]) - 1] == ' ')
                    cmd[i][j][ft_strlen(cmd[i][j]) - 1] = '\0';
                j++;
            }
        i++;
        j = 0;
    }
}

char ***parser(char *input, t_exporttable **export)
{
    t_cmds **cmds = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *cmds = NULL;
    int i = -1;
    int size = ft_strlen(input);
    int start;

    if (!input)
        return (NULL);
    if (uneven_quotes(input, '"') == 1 || uneven_quotes(input, '\'') == 1)
    {
        printf("Error: uneven quotes\n");
        return (NULL);
    }
    while (++i < size) {
        if (input[i] == '\'')
        {
            start = i + 1;
            while (input[++i] != '\'')
                ;
            if (input[i + 1] == ' ')
            {
                char *str = str_space_dup(input, start, '\'');
                ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str, " ")));
                free(str);
            }
            else
                ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, start, '\'')));
        }
        else if (input[i] == '"')
        {
            start = i + 1;
            while (input[++i] != '"')
                ;
            if (ft_strchr(input + start, '$')) {
                if (input[i + 1] == ' ')
                {
                    char *str2 = dollar_expansion(input, start, '"', export);
                    ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str2, " ")));
                    free(str2);
                }
                else
                    ft_lstadd_back(cmds, ft_lstnew(dollar_expansion(input, start, '"', export)));
            }
            else
            {
                if (input[i + 1] == ' ')
                {
                    char *str3 = str_space_dup(input, start, '"');
                    ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str3, " ")));
                    free(str3);
                }
                else
                    ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, start, '"')));
            }
        }
        else if (input[i] == '$')
        {
            start = i;
            while (input[++i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '|')
                ;
            i--;
            ft_lstadd_back(cmds, ft_lstnew(only_$(input, start, export)));
        }
        else if (input[i] == '|') {
            ft_lstadd_back(cmds, ft_lstnew(pipe_str()));
        }
        else if (input[i] != ' ') {
            start = i;
            ft_lstadd_back(cmds, ft_lstnew(str_super_dup(input, start, '0')));
            while (input[i] && input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '|') {
                i++;
            }
            i--;
        }
    }
    //print_stacks(*cmds);
    int cmd_ctr = pipe_counter(*cmds) + 1;
    char ***cmd;
    cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
    i = -1;
    while (++i < cmd_ctr) {
        cmd[i] = cmd_maker(*cmds, i + 1);
    }
    cmd[i] = NULL;
    delete_linked_list(*cmds);
    free(cmds);
    cleanup(cmd);
    return (cmd);
}