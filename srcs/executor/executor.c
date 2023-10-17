/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:35:20 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:56:53 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	setup_redirection(int oldfd, int newfd, int *saved)
{
	*saved = dup(oldfd);
	if (dup2(newfd, oldfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(newfd);
}

static void	write_to_tempfile(int tempfile_fd, char *delimiter)
{
	char	*buffer;

	while (readline("") != NULL)
	{
		buffer = readline("");
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0
			&& buffer[ft_strlen(delimiter)] == '\n')
		{
			free(buffer);
			break ;
		}
		write(tempfile_fd, buffer, ft_strlen(buffer));
		write(tempfile_fd, "\n", 1);
		free(buffer);
	}
}

FILE	*setup_append_redirection(char *delimiter)
{
	int	tempfile_fd;

	tempfile_fd = open(TMP_FILENAME, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (tempfile_fd == -1)
	{
		perror("open");
		return (NULL);
	}
	write_to_tempfile(tempfile_fd, delimiter);
	lseek(tempfile_fd, 0, SEEK_SET);
	dup2(tempfile_fd, STDIN_FILENO);
	close(tempfile_fd);
	return (stdin);
}

void	cleanup_append_redirection(int saved_stdin, FILE *tempfile)
{
	restore_fd(STDIN_FILENO, saved_stdin);
	fclose(tempfile);
}

void	execute(t_node *root, char **copyenv)
{
	if (!root)
		return ;
	if (root->type == NODE_COMMAND)
		execute_command(root, copyenv);
	else if (root->type == NODE_PIPE)
		execute_pipeline(root, copyenv);
	else if (root->type == NODE_REDIRECT_IN)
		execute_redirect_in(root, copyenv);
	else if (root->type == NODE_REDIRECT_OUT)
		execute_redirect_out(root, copyenv);
	else if (root->type == NODE_REDIRECT_IN_APPEND)
		execute_redirect_in_append(root, copyenv);
	else if (root->type == NODE_REDIRECT_OUT_APPEND)
		execute_redirect_out_append(root, copyenv);
	else
		write(2, "Error: Unknown node type\n", 23);
}
