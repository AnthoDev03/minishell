/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:30:31 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:30:55 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *string, int character)
{
	int		i;
	char	ch;

	i = 0;
	ch = character;
	while (string[i] != ch)
	{
		if (string[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)string + i);
}
