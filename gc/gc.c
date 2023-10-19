/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:06:05 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 12:08:57 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gc.h"

static t_garbagecollector	*get_garbage_collector(void)
{
	static t_garbagecollector	gc;

	gc.head = NULL;
	return (&gc);
}

void	gc_init(void)
{
	t_garbagecollector	*gc;

	gc = get_garbage_collector();
	gc->head = NULL;
}

void	*gc_malloc(size_t size)
{
	t_garbagecollector	*gc;
	void				*mem;
	t_memoryblock		*new_block;

	gc = get_garbage_collector();
	mem = malloc(size);
	if (!mem)
	{
		perror("gc_malloc");
		exit(EXIT_FAILURE);
	}
	new_block = malloc(sizeof(MemoryBlock));
	if (!new_block)
	{
		perror("gc_malloc block");
		free(mem);
		exit(EXIT_FAILURE);
	}
	new_block->addr = mem;
	new_block->next = gc->head;
	gc->head = new_block;
	return (mem);
}

void	gc_free_all(void)
{
	t_garbagecollector	*gc;
	t_memoryblock		*current;
	t_memoryblock		*temp;

	gc = get_garbage_collector();
	current = gc->head;
	while (current != NULL)
	{
		free(current->addr);
		temp = current;
		current = current->next;
		free(temp);
	}
	gc->head = NULL;
}
