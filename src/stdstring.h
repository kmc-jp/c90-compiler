#ifndef INCLUDE_GUARD_UUID_AC04F0D5_11C0_431B_A82E_4E56DA9456AF
#define INCLUDE_GUARD_UUID_AC04F0D5_11C0_431B_A82E_4E56DA9456AF

#include "allocator.h"
#include "utility.h"

typedef struct String* StringRef;

/* npos */
/* represent index of end of string */
extern const size_t string_npos;

AllocatorRef string_default_allocator(void);

/* string generator */
/* behavior is undefined if src is NULL */
StringRef make_string(const char* src, size_t length, AllocatorRef allocator);
/* constructor */
/* behavior is undefined if src is NULL */
/* returned object is intialized by src */
/* returned object must be destructed by string_dtor */
StringRef string_ctor(const char* src, AllocatorRef allocator);
/* destructor */
/* *pself is set to NULL after destruction */
void string_dtor(StringRef* pself);
/* operator= */
void string_copy(StringRef self, StringRef src);
/* assign */
/* behavior is undefined if src is NULL */
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
/* clear */
void string_clear(StringRef self);
/* insert */
/* behavior is undefined if index is out of range */
void string_insert(StringRef self, size_t index, StringRef data);
/* erase */
/* remove from index to the end if 'index + count' is out of range */
/* remove from index to the end if count is string_npos */
/* behavior is undefined if index is out of range */
void string_erase(StringRef self, size_t index, size_t count);
/* push_back */
void string_push_back(StringRef self, char data);
/* pop_back */
/* behavior is undefined if self is empty */
void string_pop_back(StringRef self);
/* append */
void string_append(StringRef self, StringRef data);
/* compare */
/* return negative value if self is lexicographically less than other */
/* return 0 if self and other is equal */
/* return positive value if self is lexicographically greater than other */
int string_compare(StringRef self, StringRef other);
/* replace */
/* index and count is treated same as string_erase */
void string_replace(StringRef self, size_t index, size_t count,
                    StringRef data);
/* substr */
/* index and count is treated same as string_erase */
/* returned object must be destructed */
StringRef string_substr(StringRef self, size_t index, size_t count);
/* copy */
/* correspoinding to std::basic_string::copy */
/* index and count is treated same as string_erase */
/* characters copied to dst is not null-terminated */
/* return the number of characters copied to dst */
/* behavior is undefined if dst has not enough storage */
size_t string_copy_to(StringRef self, char* dst, size_t count, size_t index);
/* resize */
/* additional null-characters are appended
   if the current length of self is less than size */
void string_resize(StringRef self, size_t size);
/* swap */
void string_swap(StringRef self, StringRef other);
/* find */
/* return index of the first character of the first matched substring in self */
/* otherwise, return string_npos */
/* behavior is undefined if str is NULL */
size_t string_find(StringRef self, const char* str);
/* find_first_of */
/* return index of the first matched character in self */
/* otherwise, return string_npos */
/* behavior is undefined if str is NULL */
size_t string_find_first_of(StringRef self, const char* str);
/* find_first_not_of */
/* return index of the first matched character in self */
/* otherwise, return string_npos */
/* behavior is undefined if str is NULL */
size_t string_find_first_not_of(StringRef self, const char* str);

#endif  /* INCLUDE_GUARD_UUID_AC04F0D5_11C0_431B_A82E_4E56DA9456AF */
