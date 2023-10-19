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
#include "../../gc/gc.h"
#include "../../include/minishell.h"

int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	return (status);
}

void	execute_pipeline(t_node *root, char **copyenv)
{
	int				pipe_fd[2];
	int				saved_stdin;
	pid_t			pid;
	t_pipeline_data	data;

	setup_pipe(pipe_fd);
	pid = fork();
	data.pipe_fd = pipe_fd;
	data.root = root;
	data.saved_stdin = &saved_stdin;
	data.copyenv = copyenv;
	if (pid == -1)
	{
		perror("fork");
		close_pipes(pipe_fd);
		return ;
	}
	else if (pid == 0)
		child_pipeline(pipe_fd, root, copyenv);
	else
		parent_pipeline(pid, &data);
}

void	child_pipeline(int *pipe_fd, t_node *root, char **copyenv)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 in child_pipeline");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	execute(root->left, copyenv);
	exit(0);
}

void	parent_pipeline(pid_t pid, t_pipeline_data *data)
{
	int	child_status;

	*(data->saved_stdin) = dup(STDIN_FILENO);
	close(data->pipe_fd[1]);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 in parent_pipeline");
		exit(EXIT_FAILURE);
	}
	close(data->pipe_fd[0]);
	child_status = wait_for_child(pid);
	if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
		return ;
	if (data->root->right->type == NODE_PIPE)
		execute_pipeline(data->root->right, data->copyenv);
	else
		execute(data->root->right, data->copyenv);
	restore_fd(STDIN_FILENO, *(data->saved_stdin));
}

void	execute_redirect_in(t_node *root, char **copyenv)
{
	int	fd;
	int	saved_stdin;

	fd = open_file_read(root->value);
	if (fd == -1)
		return ;
	setup_redirection(STDIN_FILENO, fd, &saved_stdin);
	execute(root->left, copyenv);
	restore_fd(STDIN_FILENO, saved_stdin);
}
