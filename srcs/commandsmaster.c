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

int search_ls(char ***cmds)
{
    int i;

    i = -1;
    while (cmds[++i])
    {
        if (ft_strcmp(cmds[i][0], "ls") == 0)
            return (1);
    }
    return (0);
}

int *searchlastls(char ***cmds)
{
    int i;
    int *ls;

    i = -1;
    ls = malloc(sizeof(int) * 2);
    ls[0] = -1;
    ls[1] = -1;
    while (cmds[++i])
    {
        if (ft_strcmp(cmds[i][0], "ls") == 0) {
            if (ls[0] == -1)
                ls[0] = i;
            ls[1] = i;
        }
    }
    return (ls);
}

char ***copytriple(char ***cmds, int start, int end)
{
    char ***new;
    int i;
    int j;
    int k;

    i = -1;
    new = (char ***)malloc(sizeof(char **) * (end - start + 2));
    while (++i < end - start)
    {
        j = -1;
        new[i] = (char **)malloc(sizeof(char *) * (doublepointersize(cmds[start + i]) + 1));
        while (cmds[start + i][++j])
        {
            new[i][j] = (char *)malloc(sizeof(char) * (ft_strlen(cmds[start + i][j]) + 1));
            k = -1;
            while (cmds[start + i][j][++k])
                new[i][j][k] = cmds[start + i][j][k];
            new[i][j][k] = '\0';
        }
        new[i][j] = NULL;
    }
    new[i] = NULL;
    return (new);
}

int triplesize(char ***cmds)
{
    int i;

    i = -1;
    while (cmds[++i])
        ;
    return (i);
}

char ****buildquadpoint(char ***cmds, int *ls)
{
    char ****quad;

    quad = malloc(sizeof(char ***) * 3);
    quad[0] = copytriple(cmds, ls[1], triplesize(cmds));
    quad[1] = copytriple(cmds, 0, ls[0]);
    quad[2] = NULL;
    if (quad[0][0] == NULL)
    {
        free(quad[0]);
        quad[0] = NULL;
    }
    if (quad[1][0] == NULL)
    {
        free(quad[1]);
        quad[1] = NULL;
    }
    //print_triple_pointer(quad[1]);
    free(ls);
    return (quad);
}

void    printquad(char ****quad)
{
    int i;
    int j;
    int k;

    i = -1;
    while (quad[++i])
    {
        j = -1;
        while (quad[i][++j])
        {
            k = -1;
            while (quad[i][j][++k])
                printf("%s ", quad[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
}

void freequadpointer(char ****quad)
{
    int i;
    int j;
    int k;

    i = -1;
    while (quad[++i])
    {
        j = -1;
        while (quad[i][++j])
        {
            k = -1;
            while (quad[i][j][++k])
                free(quad[i][j][k]);
            free(quad[i][j]);
        }
        free(quad[i]);
    }
    free(quad);
}

void commands(t_minithings *minithings, char **envp)
{
    int nbr_cmds;
    int pid;
    char ****quad;
    int i;

    i = -1;
    nbr_cmds = -1;
    if (search_ls(minithings->cmds))
    {
        quad = buildquadpoint(minithings->cmds, searchlastls(minithings->cmds));
        //printquad(quad);
    }
    else
    {
        quad = (char ****)malloc(sizeof(char ***) * 2);
        quad[0] = copytriple(minithings->cmds, 0, triplesize(minithings->cmds));
        quad[1] = NULL;
    }
    while (++i < 2 && quad[i])
    {
        if (ft_strncmp(quad[i][0][0], "exit", 4) == 0)
        {
            printf("exit\n");
            freequadpointer(quad);
            exit(1);
        }
        else if (is_builtin(quad[i][0][0]) && !quad[i][1])
        {
            builtins(minithings, 0);
            freequadpointer(quad);
            return;
        }
        pid = fork();
        sig_handler_block();
        if (pid == 0)
        {
            while (quad[i][++nbr_cmds]) { ; }
            pipex(nbr_cmds, quad[i], envp, minithings);
            exit(0);
        }
        waitpid(pid, NULL, 0);
    }
    freequadpointer(quad);
}
