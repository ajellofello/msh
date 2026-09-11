#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

void* xmalloc(const size_t size);
void* xcalloc(const size_t n, const size_t size);
void* xrealloc(void* p, const size_t size);

#endif

