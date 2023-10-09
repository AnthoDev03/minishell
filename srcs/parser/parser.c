/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:37:57 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:38:00 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_nodetype	parse_redirection_type(t_token token)
{
	if (token.type == TOKEN_REDIRECT_IN)
		return (NODE_REDIRECT_IN);
	else if (token.type == TOKEN_REDIRECT_OUT)
		return (NODE_REDIRECT_OUT);
	else if (token.type == TOKEN_REDIRECT_IN_APPEND)
		return (NODE_REDIRECT_IN_APPEND);
	else if (token.type == TOKEN_REDIRECT_OUT_APPEND)
		return (NODE_REDIRECT_OUT_APPEND);
	write(2, "Error : Unexpected token type in parse\n", 40);
	exit(EXIT_FAILURE);
}

static t_node	*handle_redirections(t_token *tokens, int *index, t_node *root)
{
	t_node		*redirect_node;
	t_nodetype	redirect_type;

	while (tokens[*index].type == TOKEN_REDIRECT_IN
		|| tokens[*index].type == TOKEN_REDIRECT_OUT
		|| tokens[*index].type == TOKEN_REDIRECT_IN_APPEND
		|| tokens[*index].type == TOKEN_REDIRECT_OUT_APPEND)
	{
		redirect_type = parse_redirection_type(tokens[*index]);
		(*index)++;
		redirect_node = parse_redirect(tokens, index, redirect_type);
		if (!redirect_node)
		{
			free_tree(root);
			return (NULL);
		}
		redirect_node->left = root;
		root = redirect_node;
	}
	return (root);
}

t_node	*parse(t_token *tokens)
{
	int		index;
	t_node	*root;

	index = 0;
	root = parse_pipeline(tokens, &index);
	root = handle_redirections(tokens, &index, root);
	return (root);
}
