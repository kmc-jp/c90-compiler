#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

const bool true = 1;
const bool false = 0;

void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "malloc error: failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
void safe_free_impl(void** ptr) {
  free(&ptr);
  *ptr = NULL;
}
