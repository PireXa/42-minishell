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
# define GREEN "\e[1;92m"
# define RES "\e[0m"

// BUFFER_SIZE FOR GNL

# define BUFFER_SIZE 10

// Structures

typedef struct s_exporttable
{
	char					*k;
	char					*value;
	struct s_exporttable	*next;
}				t_extab;

/*
 quotes: 0 = no quotes, 1 = single quotes, 2 = double quotes
 redirect: 0 = no redirect
 redirect: 1 = input
 redirect: 2 = HEREDOC
 redirect: 3 = output
 redirect: 4 = append
*/
typedef struct s_cmds
{
	char			*cmd;
	int				quotes;
	int				redirect;
	struct s_cmds	*next;
}			t_cmds;

typedef struct s_lists
{
	t_extab			**export;
	char			*line;
	char			***cmds;
	t_cmds			**ins;
	t_cmds			**outs;
	char			*efpath;
	int				wcode;
	int				rcode;
}				t_mthings;

typedef struct s_parser
{
	int			i;
	int			start;
}				t_parser;

typedef struct s_path
{
	char			**paths;
	char			*path;
	int				i;
	char			*part_path;
	t_extab			*tmp;
}					t_path;

typedef struct s_coisas
{
	char			**cmd;
	int				in;
	int				out;
}					t_redirs;

// Functions

t_extab			*envvaradd(char *k, char *v, t_mthings *mt);
void			sig_handler(void);
void			sig_handler_block(void);
void			commands(t_mthings *mt, char **envp);
void			builtins(t_mthings *minithings, int indx);
int				is_builtin(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, int start, size_t len);
char			**ft_split(char const *s, char c);
void			pipex(int nbr_cmds, char ***cm, char **en, t_mthings *mt);
int				ft_strcmp(const char *s1, const char *s2);
void			export(t_mthings *mt);
void			show_export_list(t_mthings *minithings, int flag);
void			nodefront(t_extab **head, t_extab *new);
void			nodeback(t_extab **lst, t_extab *new);
t_extab			*ind(t_extab *tmp, int index);
int				ft_lstsize(t_extab *lst);
int				check_duplicated(t_extab **export, char *str);
void			valmod(t_extab **exp, char *v, int i, t_mthings *mt);
void			unset(t_mthings *minithings);
void			ft_sort_list(t_extab *l, int size);
t_cmds			*ft_lstnew(void *content, int quotes, int redirect);
void			ft_lstaddback(t_cmds **lst, t_cmds *new);
char			**ft_split(char const *s, char c);
int				slen(const char *str);
char			*ft_substr(char const *s, int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
void			child_one(t_redirs red, t_mthings *mt, char **envp, int indx);
void			execute(t_redirs redirs, t_mthings *mt, char **envp, int indx);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_exstrchr(char *s);
char			*ft_strnldup(char *s1);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strnstr(const char	*big, const char *little, size_t len);
char			*find_path(char *cmd, t_extab **envp);
char			***parser(char *line, t_extab **expor, t_mthings *mt);
void			free_triple_pointer(char ***triple);
void			free_double_array(char **array);
int				dpsize(char **input);
int				ft_isnumber(char *str);
t_parser		*barra(t_parser *p, char *in, t_cmds **cmd);
t_parser		*aspas(t_parser *ct, char *i, t_cmds **c, t_extab **e);
char			*only_z(char *input, int start, t_extab **export);
t_parser		*dollar(t_parser *ct, char *i, t_cmds **c, t_extab **e);
char			***ezpars(t_parser *c, char *i, t_extab **expo, t_mthings *mt);
char			***return_parser(t_parser *ctr, t_cmds **cmds);
char			*str_super_dup(char *input, int start, int flag);
t_parser		*every(t_parser *ctr, char *input, t_cmds **cmds);
char			**cmd_maker(t_cmds *fds, int nbr);
int				pipe_counter(t_cmds *fds);
void			delete_linked_list(t_cmds *list);
void			cleanup(char ***cmd);
char			*str_space_dup(const char *s1, int start, int letra);
char			*dollar_expansion(char *i, int s, int d, t_extab **expo);
void			change_errorcode(t_extab **export, char *code);
void			echo(t_mthings *mt, int indx);
void			cd(t_mthings *mt, int indx);
void			pwd(t_mthings *mt);
void			exitin(char ****quad, t_mthings *mt, int i);
void			freequadpointer(char ****quad);
char			*get_next_line(int fd);
char			****buildquadpoint(char ***cmds, int *ls);
int				triplesize(char ***cmds);
char			***copytriple(char ***cmds, int s, int end);
int				*searchlastls(char ***cmds);
void			delete_export(t_extab *lst);
char			*get_prompt(void);
int				ft_str_ui_len(const char *s, int start, int letra);
int				str_super_len(char *in, int start);
int				arg_ctr(t_cmds *fds, int nbr);
char			*ft_strndup(const char *s1, size_t n);
int				ft_strlen_vars(t_cmds *vars);
int				get_var_name(char *n, int start, t_cmds **lst);
void			get_val_from_export(t_extab **e, t_cmds **a, t_cmds **v);
void			dollar_expanded(char *in, char *new_str, int *ij, t_cmds **v);
char			*search_export(t_extab **export, char *key);
void			adollar(t_parser *ct, char *i, t_cmds **c, t_extab **e);
void			aspas_no_dollar(t_parser *p, char *in, t_cmds **cmd);
int				ft_strstr_index(char *str, char *to_find);
void			free_export_table(t_extab *export);
int				only_space(char *str);
void			megafree(t_mthings *mt);
char			*ft_itoa(int n);
void			*missing_command_after_pipe(t_parser *ctr, t_cmds **cmds);
t_cmds			*ft_last_cmd(t_cmds *cmds);
void			exitcode_gvar(t_mthings *mt);
void			exitcode_file(t_mthings *mt);
int				pipepipe(char *input);
void			cleanup_redirects(t_cmds **cmds);
void			cleanup_output(t_cmds **cmds, t_mthings *mt);
void			cleanup_input(t_cmds **cmds, t_mthings *mt);
t_cmds			*idx(t_cmds **cmds, int index);
void			addinindex(t_cmds **lst, t_cmds *new, int index);
void			delete_elem(t_cmds **lst, int index);
int				sizelst(t_cmds **lst);
void			cleanup_redirsnomeio(t_cmds **cmds);
void			*missing_command_after_redir(t_parser *ctr, t_cmds **cmds);
t_redirs		meteredirs(char **cmd, t_cmds **ins, t_cmds **outs);
int				childthings(t_mthings *mt, t_redirs redirs, char **env, int n);
void			ft_heredoc(char *limiter, int fd);
int				ve_la_isso_bem(t_cmds *tmp);
int				mexenoheredoc(char *cmd);
void			ft_putendl_fd(char *s, int fd);
char			**cpydp(char **dp);
char			*normi(t_path *path);
char			*find_path(char *cmd, t_extab **envp);
int				redirnotok(char *input);
int				is_whitespace(char *str);
int				redirsdiferentesjuntas(t_cmds **cmds);
int				doispipesseguidos(t_cmds **cmds);
t_parser		*ez_utils(t_parser *p, char *i, t_extab **e, t_cmds **c);
int				mclean(t_cmds **cmds, t_parser *ctr, t_mthings *mt, char *in);
char			*get_last_content_in_cmds(t_cmds **cmds);
void			command_dollar(t_cmds **cmds, char *str4);
void			free_emptyline(t_mthings *mt);
void			cleanup_pipes(t_cmds **c);
void			printlist(t_cmds **cmds);

#endif