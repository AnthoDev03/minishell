/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:37:10 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:37:13 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

char	*expand_env_variables(char *input, t_env *env_list)
{
	t_expander	exp;

	if (!input)
		return (NULL);
	init_expander(&exp, input);
	while (*(exp.current))
	{
		if (*(exp.current) == '\'' && !exp.in_double_quotes)
			handle_single_quote(&exp);
		else if (*(exp.current) == '"' && !exp.in_single_quotes)
			handle_double_quote(&exp);
		else if (*(exp.current) == '$' && (exp.in_double_quotes
				|| (!exp.in_single_quotes && !exp.in_double_quotes))
			&& (exp.current == input || *(exp.current - 1) != '\\'))
			expand_env_var(&exp, env_list);
		else
			*(exp.write_pos)++ = *(exp.current)++;
	}
	*(exp.write_pos) = '\0';
	return (exp.expanded_str);
}

char	*get_value_from_env_list(char *var_name, t_env *env_list)
{
	size_t	name_len;

	name_len = ft_strlen(var_name);
	while (env_list)
	{
		if (ft_strncmp(env_list->value, var_name, name_len) == 0
			&& env_list->value[name_len] == '=')
			return (env_list->value + name_len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}
