#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "quotes.h"

void	print_stacks(t_fds *stck_a)
{
    printf("\n################\n");
    while (stck_a)
    {
        printf("%s\n", stck_a->cmd);
        stck_a = stck_a->next;
    }
    printf("\n################\n");
}

/*t_fds	*indx(t_fds *list, int index) {
    int i;

    i = 0;
    while (i < index) {
        list = list->next;
        i++;
    }
    return (list);
}*/

t_fds *ft_lstnew(char *cmd)
{
    t_fds *new;

    new = malloc(sizeof(t_fds));
    if (!new)
        return (NULL);
    new->cmd = cmd;
    new->next = NULL;
    return (new);
}

void ft_lstadd_back(t_fds **lst, t_fds *new)
{
    t_fds *tmp;

    if (*lst == NULL) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

/*int ft_lstsize(t_fds*lst)
{
    int i;

    i = 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}*/

char *ft_strdup(char *str)
{
    int i;
    char *new;

    i = 0;
    while (str[i])
        i++;
    new = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
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

int ft_str_ui_len(const char *s, int start, int letra) {
    int i;

    i = start;
    //printf("start: %d\n", start);
    while (s[i] && s[i] != letra) {
        //printf("string lenght s[i] = %c\n", s[i]);
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
    //printf("s1 = %s\n", s1);
    //printf("TAMANHO DESTA MERDA: %d\n", ft_str_ui_len(s1, start, letra) + 1);
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
    /*printf("i = %d\n", i);
    printf("str: %s\n", str);
    printf("\n\n");*/
    return (str);
}

int dollar(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (str[i] == '$')
            return (1);
    return (0);
}

char *env_str(char *str, int start, int letra)
{
    int i;
    int ctr;
    char *var_name;

    i = start - 1;
    ctr = 0;
    while (str[++i] != letra && str[i] != ' ')
        ctr++;
    var_name = malloc(ctr + 1);
    i = start - 1;
    ctr = -1;
    while (str[++i] != letra && str[i] != ' ')
        var_name[++ctr] = str[i];
    return (var_name);
}
int char_count(t_fds **vars, char *str, int start, int letra)
{
    int i;
    int ctr;
    //char *var_name;

    i = start - 1;
    ctr = 0;
    while (str[++i] != letra){
        if (str[i] == '$')
        {
            ft_lstadd_back(vars, ft_lstnew(env_str(str, i + 1, letra)));
        }
    }
    return (ctr);
}

char *dollar_str(t_fds **vars, char *str, int start, int letra)
{
    int i;
    char *value;

    i = start - 1;
    char_count(vars, str, start, letra);
}

int pipe_counter(t_fds *fds) {
    int i;

    i = 0;
    while (fds) {
        if (fds->cmd[0] == '|')
            i++;
        fds = fds->next;
    }
    return (i);
}

int arg_ctr(t_fds *fds, int nbr) {
    int i;

    i = 0;
    while (fds && nbr > 0) {
        //printf("nbr: %d\n", nbr);
        //printf("fds->cmd: %s\n", fds->cmd);
        if (nbr == 1)
            i++;
        if (fds->cmd[0] == '|') {
            nbr--;
        }
        if (fds->next == NULL)
            i++;
        fds = fds->next;
    }
    //printf("##############\n");
    return (i - 1);
}

char **cmd_maker(t_fds *fds, int nbr)
{
    char **cmd;
    int argn;
    int i;

    i = -1;
    argn = arg_ctr(fds, nbr);
    cmd = malloc(sizeof(char *) * (argn + 1));
    //printf("argn = %d\n", argn);
    while (nbr > 1 && fds->next)
    {
        //printf("fds->cmd: %s\n", fds->cmd);
        if (fds->cmd[0] == '|' || fds->next == NULL)
            nbr--;
        fds = fds->next;
    }
    //printf("fds->cmd: %s\n", fds->cmd);
    while (++i < argn && fds)
    {
        //printf("copiador fds->cmd: %s\n", fds->cmd);
        cmd[i] = ft_strdup(fds->cmd);
        fds = fds->next;
    }
    cmd[i] = NULL;
    return (cmd);
}

void    delete_linked_list(t_fds *list)
{
    t_fds *tmp;

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

int main(int ac, char **av, char **envp)
{
    //char *tmp = "echo \"fork abc\" 12345 | wc -l | cat srcs/main.c | grep \"echo\" | wc -l \"ewifjwei | wd nide\"";
    //char *tmp = "export | wc -l | cat srcs/main.c | grep \"echo\" | wc -l \"ewifjwei | wd nide\"";
    //char *tmp = "echo ola | ola | adeus";
    char *tmp = "echo \"na fds adoro $coiso e $cenas\"";
    t_fds **fds = (t_fds **)malloc(sizeof(t_fds *) * 1);
    t_fds **vars = (t_fds **)malloc(sizeof(t_fds *) * 1);

    *fds = NULL;
    *vars = NULL;
    int i = -1;
    int size = ft_strlen(tmp);
    int start = 0;

    printf("cmd : %s\n", tmp);
    while (++i < size) {
        //printf("\nwhile tmp[i] = %c\n", tmp[i]);
        if (tmp[i] == ' ') {
            //printf("start ' ': %d\n", start);
            ft_lstadd_back(fds, ft_lstnew(str_space_dup(tmp, start, ' ')));
            start = i + 1;
        }
        else if (tmp[i] == '"')
        {
            i++;
            start++;
            //printf("start \": %c\n", tmp[start]);
            while (tmp[++i] != '"')
                ;
            dollar_str(vars, tmp, start, '"');
            /*if (dollar)
             * ft_lstadd_back(fds, ft_lstnew(dollar_str(tmp, start, '"')));
            else*/
                ft_lstadd_back(fds, ft_lstnew(str_space_dup(tmp, start, '"')));
            i += 2;
            start = i;
            //printf("found 2 quote i = %c\n", tmp[i]);
        }
        else if (tmp[i] == '|') {
            ft_lstadd_back(fds, ft_lstnew(pipe_str()));
            //printf("start '|': %d\n", start);
            i += 2;
            start = i;
        }
    }
    if (tmp[i - 3] != '\"')
        ft_lstadd_back(fds, ft_lstnew(str_space_dup(tmp, start, ' ')));
    //printf("fds : %s\n", (*fds)->cmd);
    int cmd_ctr = pipe_counter(*fds) + 1;
    //printf("cmd_ctr: %d\n", cmd_ctr);
    char ***cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
    i = -1;
    while (++i < cmd_ctr) {
        cmd[i] = cmd_maker(*fds, i + 1);
        //printf("cmd[%d] = %s\n", i, cmd[i][0]);
        //printf("\n\n");
    }
    cmd[i] = NULL;
    print_stacks(*vars);
    print_stacks(*fds);
    print_triple_pointer(cmd);
    delete_linked_list(*fds);
    free(fds);
    free_triple_pointer(cmd);
    return 0;
}
