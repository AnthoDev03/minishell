/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:34:06 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:34:11 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	print_env_vars(void)
{
	char	**env;

	env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

char	*create_new_entry(char *key, char *value)
{
	int		len;
	char	*new_entry;

	len = strlen(key) + strlen(value) + 2;
	new_entry = malloc(len);
	if (!new_entry)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (NULL);
	}
	strcpy(new_entry, key);
	strcat(new_entry, "=");
	strcat(new_entry, value);
	return (new_entry);
}


void replace_existing_var(char **env, char *key, char *value) 
{
    char *new_entry = create_new_entry(key, value);
    if (new_entry) {
        free(*env);   // Free the existing entry before replacing
        *env = new_entry;
    }
}


int	is_key_present(char **env, char *key, int len)
{
	while (*env)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
			return (1);
		env++;
	}
	return (0);
}


void	add_new_env_var(char *key, char *value)
{
	int		count;
	char	**new_environ;
	int		idx;

	idx = 0;
	count = 0;
	while (environ[count])
		count++;
	new_environ = malloc(sizeof(char *) * (count + 2));
	if (!new_environ)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return;
	}
	while (idx < count)
	{
		new_environ[idx] = environ[idx];
		idx++;
	}
	new_environ[count] = create_new_entry(key, value);
	new_environ[count + 1] = NULL;
	// Do not free the original environ as it may not be dynamically allocated
	environ = new_environ;
}
