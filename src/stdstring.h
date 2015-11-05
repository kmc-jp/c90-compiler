#ifndef KMC_C89_COMPILER_STDSTRING_H
#define KMC_C89_COMPILER_STDSTRING_H

#include "utility.h"

typedef struct String* StringRef;

/* constructor */
/* returned object is intialized by src */
/* returned object must be destructed by string_dtor */
StringRef string_ctor(const char* src);
/* destructor */
/* *pself is set to NULL after destruction */
void string_dtor(StringRef* pself);
/* operator= */
void string_copy(StringRef self, StringRef src);
/* assign */
void string_assign(StringRef self, const char* src);
/* at */
/* behavior is undefined if index is out of range */
char string_at(StringRef self, size_t index);
/* front */
/* return null-character if self is empty */
char string_front(StringRef self);
/* back */
/* return null-character if self is empty */
char string_back(StringRef self);
/* data */
char* string_data(StringRef self);
/* begin */
/* same as data */
char* string_begin(StringRef self);
/* end */
/* return pointer to the null character following the last character */
char* string_end(StringRef self);
/* empty */
bool string_empty(StringRef self);
/* length */
size_t string_length(StringRef self);
/* reserve */
void string_reserve(StringRef self, size_t size);
/* capacity */
size_t string_capacity(StringRef self);
/* shrink_to_fit */
void string_shrink_to_fit(StringRef self);

#endif  /* KMC_C89_COMPILER_STDSTRING_H */
