/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:38:04 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:38:07 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

t_node	*create_node(t_nodetype type, char *value)
{
	t_node	*new_node;

	new_node = gc_malloc(sizeof(t_node));
	if (!new_node)
	{
		write(1, "Error: Memory allocation failed\n", 29);
		return (NULL);
	}
	new_node->type = type;
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	free_tree(t_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->value)
		free(root->value);
	free(root);
}

t_node	*parse_command(t_token *tokens, int *index)
{
	t_node	*cmd_node;
	t_node	*last_arg_node;
	t_node	*arg_node;

	if (tokens[*index].type != TOKEN_COMMAND)
		return (NULL);
	cmd_node = create_node(NODE_COMMAND, tokens[(*index)++].value);
	last_arg_node = NULL;
	while (tokens[*index].type == TOKEN_ARGUMENT)
	{
		arg_node = create_node(NODE_ARGUMENT, tokens[(*index)++].value);
		if (!last_arg_node)
			cmd_node->left = arg_node;
		else
			last_arg_node->right = arg_node;
		last_arg_node = arg_node;
	}
	return (cmd_node);
}

t_node	*parse_redirect(t_token *tokens, int *index, t_nodetype redirect_type)
{
	t_node	*redirect_node;

	redirect_node = create_node(redirect_type, NULL);
	if (tokens[*index].type != TOKEN_ARGUMENT)
	{
		free_tree(redirect_node);
		return (NULL);
	}
	redirect_node->value = ft_strdup(tokens[(*index)++].value);
	return (redirect_node);
}

t_node	*parse_pipeline(t_token *tokens, int *index)
{
	t_node	*left_node;
	t_node	*right_node;
	t_node	*pipe_node;

	left_node = parse_command(tokens, index);
	while (tokens[*index].type == TOKEN_PIPE)
	{
		(*index)++;
		if (tokens[*index].type == TOKEN_ARGUMENT)
			tokens[*index].type = TOKEN_COMMAND;
		right_node = parse_command(tokens, index);
		if (!right_node)
		{
			free_tree(left_node);
			return (NULL);
		}
		pipe_node = create_node(NODE_PIPE, NULL);
		pipe_node->left = left_node;
		pipe_node->right = right_node;
		left_node = pipe_node;
	}
	return (left_node);
}
