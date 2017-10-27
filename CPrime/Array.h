
#pragma once

#include "Result.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    void** pItems;
    int size;
    int capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

Result Array_Reserve(Array* p, int nelements);
Result Array_Grow(Array* p, int nelements);
void Array_Pop(Array* p, void(*pfDestroyData)(void*));
void* Array_PopGet(Array* p);
void* Array_Top(Array* p);
Result Array_Push(Array* p, void* pItem);
void Array_Clear(Array* p, void(*pfDestroyData)(void*));
void Array_Init(Array* p);

void Array_Destroy(Array* st, void(*pfDestroyData)(void*));

void Array_Swap(Array* p1, Array* p2);
void* Array_PopFront(Array* p);
void* Array_RemoveAt(Array* p, int index);
//////


typedef struct
{
    const char** pItems;
    int size;
    int capacity;

} StrArray;

#define STRARRAY_INIT { NULL , 0 , 0 }

Result StrArray_Reserve(StrArray* p, int nelements);
Result StrArray_Push(StrArray* p, const char* pItem);
void StrArray_Clear(StrArray* p);
void StrArray_Init(StrArray* p);
void StrArray_Destroy(StrArray* st);
void StrArray_Swap(StrArray* p1, StrArray* p2);
