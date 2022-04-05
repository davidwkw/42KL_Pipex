/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:06:56 by kwang             #+#    #+#             */
/*   Updated: 2022/04/05 21:10:54 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*search_append_path(char *name, char *envp[])
{
	int		i;
	char	*temp;
	char	*full_name;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp = ft_strjoin("/", name);
			paths = ft_split(envp[i] + 5, ':');
			i = -1;
			while (paths[++i])
			{
				full_name = ft_strjoin(paths[i], temp);
				if (access(full_name, F_OK | X_OK) == 0)
					return (full_name);
				free(full_name);
			}
			free(temp);
			break;
		}
	}
	return (name);
}

static void	fork_execute(char *argv, char *envp[], t_subprocess *subprocess)
{
	int		pipefd[2];
	char	**args;

	ft_pipe(pipefd);
	subprocess->pid = fork();
	if (subprocess->pid == 0)
	{
		ft_close(pipefd[0]);
		ft_mv_fd(subprocess->stdin_fd, STDIN_FILENO);
		if (subprocess->stdout_fd == -1)
			ft_mv_fd(pipefd[1], STDOUT_FILENO);
		else
		{
			ft_close(pipefd[1]);
			ft_mv_fd(subprocess->stdout_fd, STDOUT_FILENO);
		}
		args = ft_split(argv, ' ');
		args[0] = search_append_path(args[0], envp);
		execve(args[0], args, envp);
		error("Execve failed");
	}
	else if (subprocess->pid < 0)
		error("Fork failure");
	else
	{
		ft_close(pipefd[1]);
		ft_close(subprocess->stdin_fd);
		subprocess->stdin_fd = pipefd[0];
	}
}

static int		heredoc(char *limiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error("Pipe failure\n");
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		if (get_next_line(0, &line) < 1)
			break;
		if (ft_strlen(line) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
		line = NULL;
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

static pid_t	pipex(int argc, char *argv[], char *envp[], int bonus)
{
	int				i;
	t_subprocess	subprocess;

	subprocess.pid = -1;
	if (bonus)
		subprocess.stdin_fd = heredoc(argv[1]);
	else
		subprocess.stdin_fd = ft_open(argv[1], O_RDONLY, S_IRUSR);
	subprocess.stdout_fd = -1;
	i = 1;
	while (++i < (argc - 2))
		fork_execute(argv[i], envp, &subprocess);
	if (bonus)
		subprocess.stdout_fd = ft_open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, S_IWUSR);
	else
		subprocess.stdout_fd = ft_open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR);
	fork_execute(argv[argc - 2], envp, &subprocess);
	close(subprocess.stdin_fd);
	close(subprocess.stdout_fd);
	return (subprocess.pid);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		bonus;
	int		exit_status;
	pid_t	last_pid;

	if (argc < 5)
	{
		errno = EXIT_FAILURE;
		error("Usage: ./pipex file1 cmd1 cmd2 ... file2 or ./pipex here_doc <LIMITER> cmd1 cmd2 file");
	}
	bonus = false;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		bonus = true;
	last_pid = pipex(argc - bonus, argv + bonus, envp, bonus);
	waitpid(last_pid, &exit_status, 0);
	while (wait(NULL) != -1)
		;
	return (exit_status);
}
