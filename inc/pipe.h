#ifndef PIPE_H
# define PIPE_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

typedef struct s_data
{
	char	**envp;
	char	**argv;
	int		argc;
	int		infile;
	int		outfile;
}				t_data;

void	pipex(t_data *data);
void	handle_child(t_data *data, int tmp_fd, int i, int *pipe_fd);
void	ft_exec(t_data *data, char **cmd_args);
char	**fetch_paths(t_data *data);
void	free_arr(char **arr);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif
