#include "gc.h"

typedef struct MemoryBlock {
    void *addr;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct {
    MemoryBlock *head;
} GarbageCollector;

// This function provides access to a function-static GarbageCollector.
static GarbageCollector* get_garbage_collector() {
    static GarbageCollector gc = {NULL};
    return &gc;
}

void gc_init() {
    GarbageCollector *gc = get_garbage_collector();
    gc->head = NULL;
}

void* gc_malloc(size_t size) {
    GarbageCollector *gc = get_garbage_collector();

    void *mem = malloc(size);
    if (!mem) {
        perror("gc_malloc");
        exit(EXIT_FAILURE);
    }

    MemoryBlock *new_block = malloc(sizeof(MemoryBlock));
    if (!new_block) {
        perror("gc_malloc block");
        free(mem);
        exit(EXIT_FAILURE);
    }

    new_block->addr = mem;
    new_block->next = gc->head;
    gc->head = new_block;

    return mem;
}

void gc_free_all() {
    GarbageCollector *gc = get_garbage_collector();

    MemoryBlock *current = gc->head;
    MemoryBlock *temp;

    while (current != NULL) {
        free(current->addr);
        temp = current;
        current = current->next;
        free(temp);
    }

    gc->head = NULL;
}
