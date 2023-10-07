/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:26:56 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:27:00 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t	countchar;

	countchar = 0;
	while (countchar < num)
	{
		if (*(unsigned char *)ptr1 != *(unsigned char *)ptr2)
		{
			return ((*(unsigned char *)ptr1) - (*(unsigned char *)ptr2));
		}
		countchar++;
		ptr1 = (unsigned char *)ptr1 + 1;
		ptr2 = (unsigned char *)ptr2 + 1;
	}
	return (0);
}
