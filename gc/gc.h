#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include <stdlib.h>
#include <stdio.h>
void gc_init();
void* gc_malloc(size_t size);
void gc_free_all();

#endif // GARBAGE_COLLECTOR_H
