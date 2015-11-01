#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

void* safe_malloc_impl(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "malloc error: failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
void safe_free_impl(void** ptr) {
  free(*ptr);
  *ptr = NULL;
}
