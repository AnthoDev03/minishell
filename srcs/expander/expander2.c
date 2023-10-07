#include "../../include/minishell.h"

void	init_expander(t_expander *exp, char *input)
{
	exp->current = input;
	exp->in_single_quotes = 0;
	exp->in_double_quotes = 0;
	exp->buffer_size = strlen(input) + 1;
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

	while (isalnum(*end_pos) || *end_pos == '_')
		end_pos++;
	strncpy(var_name, exp->current + 1, end_pos - exp->current - 1);
	var_name[end_pos - exp->current - 1] = '\0';
	exp->current = end_pos;
}

void	expand_env_var(t_expander *exp)
{
	char		*env_value;
	size_t		remaining_size;
	ptrdiff_t	offset;

	char var_name[256];
		// Maximum size for an environment variable name. You can
						// adjust this value.
	get_env_var_name(exp, var_name);
	env_value = getenv(var_name);
	if (env_value)
	{
		remaining_size = exp->buffer_size - (exp->write_pos
				- exp->expanded_str);
		while (remaining_size < strlen(env_value) + 1)
		{
			offset = exp->write_pos - exp->expanded_str;
			exp->buffer_size *= 2;
			exp->expanded_str = realloc(exp->expanded_str, exp->buffer_size);
			exp->write_pos = exp->expanded_str + offset;
			remaining_size = exp->buffer_size - (exp->write_pos
					- exp->expanded_str);
		}
		strcpy(exp->write_pos, env_value);
		exp->write_pos += strlen(env_value);
	}
}
