#include "new-vector.h"

/* vector of Type */
struct Vector {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
};

static VectorRef vectorref_alloc(void) {
  const VectorRef self = safe_malloc(struct Vector);
  self->start_ = self->finish_ = self->end_ = NULL;
  return self;
}
