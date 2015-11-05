#ifndef KMC_C89_COMPILER_STDSTRING_H
#define KMC_C89_COMPILER_STDSTRING_H

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

#endif  /* KMC_C89_COMPILER_STDSTRING_H */
