#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	**ft_spit(char const *s, char c);

size_t	ft_strlen(const char *str);

char	*ft_subst(char const *s, unsigned int start, size_t len);

char	*ft_stdup(const char *s1);

char	*ft_stjoin(char const *s1, char const *s2);

int		is_barra_e_hihfen(char *s1, char *s2);

char	*ft_str_barra(const char *s1);

char	*ft_str_after_barra(const char *s1);

void	arranjar_cmd(char **cmd);

char	*ft_strhr(const char *s, int c);

void	childone(char *av, char **envp);

int		ft_stncmp(const char *s1, const char *s2, size_t n);

void	ft_here_doc(char *limiter, int ac);

char	*gnl(int fd);

char	*ft_exstchr(char *s);

char	*ft_stnldup(char *s1);

size_t	ft_stlcpy(char *dst, char *src, size_t size);

void	*ft_caloc(size_t count, size_t size);

int		open_file(char *argv, int i);

char	*findpath(char *cmd, char **envp);

void	exec(char *av, char **envp);

char	*ft_stnstr(const char	*big, const char *little, size_t len);

#endif
