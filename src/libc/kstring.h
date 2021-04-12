#pragma once

#include <stddef.h>
#include <stdint.h>

#include "kassert.h"

void* kmemcpy(void* destination, const void* source, size_t num);

void* kmemmove(void* destination, const void* source, size_t num);

void* kmemch(void* ptr, int value, size_t num);

int kmemcmp(const void* ptr1, const void* ptr2, size_t num);

void* kmemset(void *const ptr, const int32_t value, size_t num);

char* kstrcat(char* destination, const char* source);

char* kstrncat(char* const destination, const char* source, size_t num);

char* kstrchr(char* str, int character);

char* kstrrchr(char* str, int character);

int32_t kstrcmp(const char* lhs, const char* rhs);

int32_t kstrncmp(const char* const lhs, const char* const rhs, const size_t sz);

int kstrcoll(const char* str1, const char* str2);

char* kstrcpy(char* destination, const char* source);

char* kstrncpy(char* destination, const char* source, size_t num);

size_t kstrspn(const char* str1, const char* str2);

size_t kstrlen(const char* str);

char* kint_to_string(int64_t input, char* string_ret, size_t ret_size, uint32_t base, bool lowercase);

