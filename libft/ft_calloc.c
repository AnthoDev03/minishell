/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:24:38 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:24:43 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*memory;

	total_size = num_elements * element_size;
	memory = malloc(total_size);
	if (memory == NULL)
	{
		return (NULL);
	}
	ft_memset(memory, 0, total_size);
	return (memory);
}
