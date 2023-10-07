/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:32:45 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:32:47 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fs;
	size_t	len_s;
	size_t	offset;

	if (s == NULL || f == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	offset = 0;
	fs = (char *)malloc(len_s + 1);
	if (fs == NULL)
		return (NULL);
	while (offset < len_s)
	{
		fs[offset] = f(offset, s[offset]);
		offset++;
	}
	fs[len_s] = '\0';
	return (fs);
}
