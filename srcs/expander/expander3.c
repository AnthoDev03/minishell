/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:37:29 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:37:32 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	resize_expander_buffer(t_expander *exp, size_t required_size)
{
	char		*new_str;
	ptrdiff_t	offset;

	while (exp->buffer_size < required_size)
	{
		offset = exp->write_pos - exp->expanded_str;
		exp->buffer_size *= 2;
		new_str = malloc(exp->buffer_size);
		if (!new_str)
		{
			write(2, "Memory allocation failed\n", 25);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new_str, exp->expanded_str, offset);
		free(exp->expanded_str);
		exp->expanded_str = new_str;
		exp->write_pos = exp->expanded_str + offset;
	}
}

static void	copy_env_to_expander(t_expander *exp, char *env_value)
{
	size_t	required_size;

	required_size = (exp->write_pos - exp->expanded_str) + ft_strlen(env_value)
		+ 1;
	resize_expander_buffer(exp, required_size);
	ft_strcpy(exp->write_pos, env_value);
	exp->write_pos += ft_strlen(env_value);
}

void	expand_env_var(t_expander *exp)
{
	char	*env_value;
	char	var_name[256];

	get_env_var_name(exp, var_name);
	// Check if var_name is "?"
	if (ft_strcmp(var_name, "?") == 0)
	{
		copy_env_to_expander(exp, "0");
		return;
	}
	// If var_name is empty, it means it was just a lone $
	if (ft_strlen(var_name) == 0)
	{
		*(exp->write_pos)++ = '$';
		return;
	}
	env_value = getenv(var_name);
	if (env_value)
	{
		copy_env_to_expander(exp, env_value);
	}
}
