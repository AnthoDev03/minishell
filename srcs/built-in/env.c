/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:07 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:33:13 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	env_command(t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->value);
		env_list = env_list->next;
	}
}
