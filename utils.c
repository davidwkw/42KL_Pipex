#include "pipex.h"

void	error(char *msg)
{
	ft_putendl_fd(msg, 2);
	perror("Error");
	exit(errno);
}

void	ft_close(const int fd)
{
	if (close(fd) == -1)
		error("Error closing fd");
}

int		ft_open(const char *pathname, int flags, mode_t mode)
{
	int fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
		error("Error opening file");
	return (fd);
}

void	ft_mv_fd(const int fd1, const int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error("Could not duplicate pipe");
	ft_close(fd1);
}

void	ft_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		error("Failed to create pipe");
}
