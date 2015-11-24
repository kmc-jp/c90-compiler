#include "new-vector.h"

/* vector of Type */
struct Vector {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
};
