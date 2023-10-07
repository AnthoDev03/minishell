#include "../../include/minishell.h"

void	handle_var_set(char *key, char *value)
{
	int		len;
	char	**env;

	len = ft_strlen(key);
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
		{
			replace_existing_var(env, key, value);
			return ;
		}
		env++;
	}
	if (!is_key_present(env, key, len))
		add_new_env_var(key, value);
}

void	set_env_var(t_node *commandNode)
{
	char	*key;
	char	*equal_sign;
	char	*value;

	key = commandNode->left->value;
	equal_sign = ft_strchr(key, '=');
	if (!equal_sign)
	{
		printf("Malformed input: %s. Expected format: KEY=VALUE\n", key);
		return ;
	}
	*equal_sign = '\0';
	value = equal_sign + 1;
	handle_var_set(key, value);
	*equal_sign = '=';
}

void	export_command(t_node *commandNode)
{
	if (!commandNode->left || !commandNode->left->value)
		print_env_vars();
	else
		set_env_var(commandNode);
}
