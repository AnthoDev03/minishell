/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:35:47 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:35:50 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	return (status);
}

void	execute_pipeline(t_node *root)
{
	int		pipe_fd[2];
	int		saved_stdin;
	pid_t	pid;

	setup_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close_pipes(pipe_fd);
		return ;
	}
	else if (pid == 0)
		child_pipeline(pipe_fd, root);
	else
		parent_pipeline(pipe_fd, root, &saved_stdin, pid);
}

void	child_pipeline(int *pipe_fd, t_node *root)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 in child_pipeline");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	execute(root->left);
	exit(0);
}

void	parent_pipeline(int *pipe_fd, t_node *root, int *saved_stdin, pid_t pid)
{
	int	child_status;

	*saved_stdin = dup(STDIN_FILENO);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 in parent_pipeline");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	child_status = wait_for_child(pid);
	if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
		return ;
	if (root->right->type == NODE_PIPE)
		execute_pipeline(root->right);
	else
		execute(root->right);
	restore_fd(STDIN_FILENO, *saved_stdin);
}

void	execute_redirect_in(t_node *root)
{
	int	fd;
	int	saved_stdin;

	fd = open_file_read(root->value);
	if (fd == -1)
		return ;
	setup_redirection(STDIN_FILENO, fd, &saved_stdin);
	execute(root->left);
	restore_fd(STDIN_FILENO, saved_stdin);
}
