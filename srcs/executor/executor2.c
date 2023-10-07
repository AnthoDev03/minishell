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

void	execute_command(t_node *node)
{
  int   i = 0;
	char	*builtins[] = {"cd", "echo", "env", "exit", "pwd", "unset",
			"export"};
	char	*args[3] = {node->value, NULL, NULL};
	pid_t	pid;

	void (*funcs[])(t_node *) = {cd_command, echo_command, env_command,
		exit_command, pwd_command, unset_command, export_command};
	while (i < 7)
	{
		if (strcmp(node->value, builtins[i]) == 0)
		{
			funcs[i](node);
			return ;
		}
    i++;
	}
	if (node->left)
		args[1] = node->left->value;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		ft_execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	wait_for_child(pid);
}
