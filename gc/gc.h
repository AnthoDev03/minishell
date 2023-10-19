#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdio.h>
# include <stdlib.h>

void					gc_init(void);
void					*gc_malloc(size_t size);
void					gc_free_all(void);

typedef struct MemoryBlock
{
	void				*addr;
	struct MemoryBlock	*next;
}						MemoryBlock;

typedef struct
{
	MemoryBlock			*head;
}						GarbageCollector;

#endif
