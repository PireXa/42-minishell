/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:31:50 by fde-albe          #+#    #+#             */
/*   Updated: 2022/07/27 19:08:26 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

# define BUFFER_SIZE 10

int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	**ft_split(char const *s, char c);

int	ft_strlen(const char *str);

char	*ft_substr(char const *s,  int start, size_t len);

char	*ft_strdup(const char *s1);

char	*ft_strjoin(char *s1, char *s2);

int		is_barra_e_hihfen(char *s1, char *s2);

char	*ft_str_barra(const char *s1);

char	*ft_str_after_barra(const char *s1);

void	arranjar_cmd(char **cmd);

char	*ft_strchr(const char *s, int c);

void	child_one(char *av, char **envp);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_here_doc(char *limiter, int ac);

char	*get_next_line(int fd);

char	*ft_exstrchr(char *s);

char	*ft_strnldup(char *s1);

size_t	ft_strlcpy(char *dst, char *src, size_t size);

void	*ft_calloc(size_t count, size_t size);

int		open_file(char *argv, int i);

char	*find_path(char *cmd, char **envp);

void	execute(char *av, char **envp);

char	*ft_strnstr(const char	*big, const char *little, size_t len);

#endif
