/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:47 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:33:51 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../gc/gc.h"
void	handle_var_set(char **env, char *key, char *value)
{
	int		len;
	char	**env_ptr;

	len = ft_strlen(key);
	env_ptr = env;
	while (*env_ptr)
	{
		if (ft_strncmp(*env_ptr, key, len) == 0 && (*env_ptr)[len] == '=')
		{
			replace_existing_var(env_ptr, key, value);
			return;
		}
		env_ptr++;
	}
	if (!is_key_present(env, key, len))
	{
		char **new_env = add_new_env_var(env, key, value);
		// Ici, vous pourriez décider de libérer l'ancien 'env' si nécessaire
		env = new_env; // Cette ligne peut nécessiter une gestion au niveau supérieur pour mettre à jour la référence.
	}
}

void	set_env_var(t_node *commandNode, char **copyenv)
{
	char	*key;
	char	*equal_sign;
	char	*value;

	key = commandNode->left->value;
	equal_sign = ft_strchr(key, '=');
	if (!equal_sign || equal_sign == key)
	{
		printf("Malformed input: %s. Expected format: KEY=VALUE\n", key);
		return ;
	}
	*equal_sign = '\0';
	value = equal_sign + 1;
	
handle_var_set(copyenv, key, value);

	*equal_sign = '=';
}

void	export_command(t_node *commandNode, char **env)
{
	if (!commandNode->left || !commandNode->left->value)
		env_command(env);
	else
		set_env_var(commandNode, env);
}
