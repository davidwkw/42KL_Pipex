#ifndef PIPEX_H

# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

enum
{
	false,
	true
};

typedef struct s_subprocess
{
	pid_t pid;
	int stdin_fd;
	int stdout_fd;
}	t_subprocess;

void	error(char *msg);
int		ft_open(const char *pathname, int flags, mode_t mode);
void	ft_close(const int fd);
void	ft_mv_fd(const int fd1, const int fd2);
void	ft_pipe(int pipefd[2]);

#endif
