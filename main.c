#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int	main(int argc, char **argv, char **envp)
{
	execve("./hello.txt", argv, envp);

	printf("%d\n", errno);
	perror("Error: ");
	return (0);
}
