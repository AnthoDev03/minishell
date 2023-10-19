#include "gc.h"

static GarbageCollector	*get_garbage_collector(void)
{
	static GarbageCollector	gc;

	gc.head = NULL;
	return (&gc);
}

void	gc_init(void)
{
	GarbageCollector	*gc;

	gc = get_garbage_collector();
	gc->head = NULL;
}

void	*gc_malloc(size_t size)
{
	GarbageCollector	*gc;
	void				*mem;
	MemoryBlock			*new_block;

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
	GarbageCollector	*gc;
	MemoryBlock			*current;
	MemoryBlock			*temp;

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
