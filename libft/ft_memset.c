/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:27:46 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:27:49 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	v;
	size_t			i;

	v = c;
	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = v;
		i++;
	}
	return (p);
}
