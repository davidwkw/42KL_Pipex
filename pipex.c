/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:06:56 by kwang             #+#    #+#             */
/*   Updated: 2022/03/30 18:15:02 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	fork_execute(char *argv[], char *envp[], )
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, envp) == -1)
			error("Execve failed\n");
	}
	else
		return (pid);

}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t pid;

	if (argc < 1)
	{
		pid = fork_execute(argv, envp);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
