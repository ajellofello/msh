#include <stdlib.h>
#include <stdio.h>

#include "alloc.h"

void* xmalloc(const size_t size)
{
  void* mem = malloc(size);

  if (!mem)
  {
    perror("malloc");
    exit(1);
  }
  return mem;
}

void* xcalloc(const size_t n, const size_t size)
{
  void* mem = calloc(n, size);

  if (!mem)
  {
    perror("calloc");
    exit(1);
  }
  return mem;
}

void* xrealloc(void* p, const size_t size)
{
  void* mem = realloc(p, size);

  if (!mem)
  {
    perror("realloc");
    exit(1);
  }
  return mem;
}

