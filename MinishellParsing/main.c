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

    if (!*lst)
    {
        *lst = new;
        return ;
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

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_str_ui_len(const char *s, int start, int letra) {
    int i;

    i = start;
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
    str[i] = 0;
    //printf("str: %s\n", str);
    return (str);
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

    cmd = malloc(sizeof(char *) * (arg_ctr(fds, nbr) + 1));
    printf("arg_ctr(fds, nbr) = %d\n", arg_ctr(fds, nbr));
    //free (cmd);
}
int main() {
    char *tmp = "echo \"fork abc\" 12345 | wc -l | cat srcs/main.c | grep \"echo\" | wc -l \"ewifjwei | wd nide\"";
    //char *tmp = "echo irvire irejg \"ur4h4 ruth4\"";
    t_fds **fds = malloc(sizeof(t_fds *));
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
            ft_lstadd_back(fds, ft_lstnew(str_space_dup(tmp, start, '"')));
            while (tmp[++i] != '"')
                ;
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
    print_stacks(*fds);
    //printf("fds : %s\n", (*fds)->cmd);
    int cmd_ctr = pipe_counter(*fds) + 1;
    printf("cmd_ctr: %d\n", cmd_ctr);
    char ***cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
    i = -1;
    while (++i < cmd_ctr) {
        cmd[i] = cmd_maker(*fds, i + 1);
        //printf("cmd[%d] = %s\n", i, cmd[i][0]);
        printf("\n\n");
    }
    return 0;
}
