/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:35:31 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:35:34 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

int	calculate_ast_depth(t_node *node)
{
	int		depth;
	t_node	*temp;

	depth = 0;
	temp = node;
	while (temp)
	{
		depth++;
		if (temp->left)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return (depth);
}

char	**populate_args_from_ast(char **args, t_node *node, int depth)
{
	int		index;
	t_node	*temp;

	index = 0;
	temp = node;
	while (temp && index < depth)
	{
		args[index] = temp->value;
		index++;
		if (temp->left)
			temp = temp->left;
		else
			temp = temp->right;
	}
	args[index] = NULL;
	return (args);
}

char	**create_args_from_ast(t_node *node)
{
	int		depth;
	char	**args;

	depth = calculate_ast_depth(node);
	args = gc_malloc((depth + 1) * sizeof(char *));
	if (!args)
	{
		perror("gc_malloc");
		exit(EXIT_FAILURE);
	}
	return (populate_args_from_ast(args, node, depth));
}

static char	**convert_env_list_to_array(t_env *env_list)
{
	int		count;
	t_env	*tmp;
	char	**env_array;
	int		i;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env_array = gc_malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		env_array[i] = tmp->value;
		i++;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	execute_external_command(t_node *node, t_env *env_list)
{
	pid_t	pid;
	char	**args;
	char	**converted_env;

	args = create_args_from_ast(node);
	if (node->left)
		args[1] = node->left->value;
	converted_env = convert_env_list_to_array(env_list);
	if (!converted_env)
	{
		perror("Memory allocation failed");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		ft_execvp(args[0], args, converted_env);
		exit(EXIT_FAILURE);
	}
	wait_for_child(pid);
}
