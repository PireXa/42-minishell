/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/10/21 16:39:50 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries

# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<signal.h>
# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include<sys/wait.h>
# include<fcntl.h>

// COLORS

# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;92m"
# define RES "\e[0m"

// BUFFER_SIZE FOR GNL

# define BUFFER_SIZE 100

// Structures

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

typedef struct s_exporttable
{
	char					*k;
	char					*value;
	struct s_exporttable	*next;
}				t_exporttable;

typedef struct s_cmds
{
	char			*cmd;
	struct s_cmds	*next;
}			t_cmds;

typedef struct s_lists
{
	t_exporttable	**export;
	char			*line;
	char			***cmds;
}				t_minithings;

typedef struct	s_parser {
	int			i;
	int			start;
}				t_parser;

// Functions

t_exporttable	*envvaradd(char *key, char *value, t_exporttable **export);
void			sig_handler(void);
void			sig_handler_block(void);
void			commands(t_minithings *minithings, char **envp);
void			builtins(t_minithings *minithings, int indx);
int				is_builtin(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, int start, size_t len);
char			**ft_split(char const *s, char c);
void			pipex(int nbr_cmds, char ***cm, char **en, t_minithings *mt);
int				ft_strcmp(const char *s1, const char *s2);
void			export(t_minithings *mt);
void			show_export_list(t_minithings *minithings, int flag);
void			nodefront(t_exporttable **head, t_exporttable *new);
void			nodeback(t_exporttable **lst, t_exporttable *new);
t_exporttable	*ind(t_exporttable *list, int index);
int				ft_lstsize(t_exporttable *lst);
int				check_duplicated(t_exporttable **export, char *str);
void			value_modifier(t_exporttable **export, char *value, int i);
void			unset(t_minithings *minithings);
void			ft_sort_list(t_exporttable *l, int size);
t_cmds			*ft_lstnew(void *content);
void			ft_lstadd_back(t_cmds **lst, t_cmds *new);
char			**ft_split(char const *s, char c);
int				slen(const char *str);
char			*ft_substr(char const *s, int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
void			child_one(char **av, t_minithings *mt, char **envp, int indx);
void			execute(char **cmds, t_minithings *mt, char **envp, int indx);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_exstrchr(char *s);
char			*ft_strnldup(char *s1);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strnstr(const char	*big, const char *little, size_t len);
char			*find_path(char *cmd, t_exporttable **envp);
char			***parser(char *line, t_exporttable **export);
void			free_triple_pointer(char ***triple);
void			free_double_array(char **array);
int				dpsize(char **input);
int				ft_isnumber(char *str);
char			*ft_itoa(int c);
t_parser		barra(t_parser ctr, char *input, t_cmds **cmds);
t_parser		aspas(t_parser ctr, char *input, t_cmds **cmds, t_exporttable **export);
char 			*only_z(char *input, int start, t_exporttable **export);
t_parser		dollar(t_parser ctr, char *input, t_cmds **cmds, t_exporttable **export);
char			***ez_parsing(t_parser ctr, char *input, t_exporttable **export);
char			***return_parser(t_parser ctr, t_cmds **cmds);
char			*pipe_str(void);
char			*str_super_dup(char *input, int start, int flag);
t_parser		every(t_parser ctr, char *input, t_cmds **cmds);
char			**cmd_maker(t_cmds *fds, int nbr);
int				pipe_counter(t_cmds *fds);
void			delete_linked_list(t_cmds *list);
void			cleanup(char ***cmd);
char			*str_space_dup(const char *s1, int start, int letra);
char 			*dollar_expansion(char *input, int start, int divider, t_exporttable **export);
void			change_errorcode(t_exporttable **export, char *code);
void			echo(t_minithings *mt, int indx);
void			cd(t_minithings *mt, int indx);
void			pwd(t_minithings *mt);
void			exitin(char ****quad, t_minithings *minithings, int i);
void			freequadpointer(char ****quad);

#endif
