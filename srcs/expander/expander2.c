/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:37:20 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:37:23 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	init_expander(t_expander *exp, char *input)
{
	exp->current = input;
	exp->in_single_quotes = 0;
	exp->in_double_quotes = 0;
	exp->buffer_size = ft_strlen(input) + 1;
	exp->expanded_str = malloc(exp->buffer_size);
	exp->write_pos = exp->expanded_str;
}

void	handle_single_quote(t_expander *exp)
{
	exp->in_single_quotes = !exp->in_single_quotes;
	*(exp->write_pos)++ = *(exp->current)++;
}

void	handle_double_quote(t_expander *exp)
{
	exp->in_double_quotes = !exp->in_double_quotes;
	*(exp->write_pos)++ = *(exp->current)++;
}


void	get_env_var_name(t_expander *exp, char *var_name)
{
	const char	*end_pos = exp->current + 1;

	if (*end_pos == '?')
	{
		ft_strcpy(var_name, "?");
		exp->current += 2;
		return;
	}
	while (ft_isalnum(*end_pos) || *end_pos == '_')
		end_pos++;
	ft_strncpy(var_name, exp->current + 1, end_pos - exp->current - 1);
	var_name[end_pos - exp->current - 1] = '\0';
	exp->current = end_pos;
}

