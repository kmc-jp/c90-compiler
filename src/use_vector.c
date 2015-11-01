#include "use_vector.h"
#include "utility.h"

DEFINE_VECTOR(char)
DEFINE_DEFAULT_METHODS(char)

void do_initialize_vector() {
  /* Initialization code follows */
  INITIALIZE_DEFAULT_METHODS(char);
}

void initialize_vector() {
  static bool is_first = true;
  if (is_first) {
    do_initialize_vector();
    is_first = false;
  }
}
