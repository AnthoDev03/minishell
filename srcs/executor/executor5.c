#include "../../include/minishell.h"

void	dup_to(int oldfd, int newfd, int *saved)
{
	*saved = dup(oldfd);
	if (dup2(newfd, oldfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	close_pipes(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	restore_fd(int oldfd, int saved)
{
	dup2(saved, oldfd);
	close(saved);
}

void	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

