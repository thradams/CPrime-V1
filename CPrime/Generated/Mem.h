#pragma once
#include <stdlib.h>

#if _DEBUG
#define Malloc(x) DebugMalloc(__FILE__, __LINE__, (x))
#define Realloc(x, s) DebugRealloc(__FILE__, __LINE__, (x), (s))
void* DebugMalloc(const char* fileName, int line, size_t size);
void *DebugRealloc(const char* fileName, int line, void *ptr, size_t new_size);
void Free(void* ptr);
#else
#define Malloc(x) malloc(x)
#define Realloc(x, s) realloc((x), (s))
#define Free(x) free(x)
#endif


void PrintMemory();