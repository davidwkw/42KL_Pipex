#include "pipex.h"

void	error(char *msg)
{
	ft_putstr_fd(msg, 1);
	perror("Error: ");
	exit(1);
}
