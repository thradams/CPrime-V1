
#pragma once
#pragma source

#include <stdbool.h>
#include <stdlib.h>

struct Array
{
    void** pItems;
    int size;
    int capacity;

};

#define ARRAY_INIT { NULL , 0 , 0 }

bool Array_Reserve(struct Array* p, int nelements);
bool Array_Grow(struct Array* p, int nelements);
void Array_Pop(struct Array* p, void(*pfDestroyData)(void*));
void* Array_PopGet(struct Array* p);
void* Array_Top(struct Array* p);
bool Array_Push(struct Array* p, void* pItem);
void Array_Clear(struct Array* p, void(*pfDestroyData)(void*));
void Array_Init(struct Array* p);

void Array_Destroy(struct Array* st, void(*pfDestroyData)(void*));

void Array_Swap(struct Array* p1, struct Array* p2);
void* Array_PopFront(struct Array* p);



struct StrArray
{
    const char** pItems;
    int size;
    int capacity;

};

#define STRARRAY_INIT { NULL , 0 , 0 }

bool StrArray_Reserve(struct StrArray* p, int nelements);
bool StrArray_Push(struct StrArray* p, const char* pItem);
void StrArray_Clear(struct StrArray* p);
void StrArray_Init(struct StrArray* p);
void StrArray_Destroy(struct StrArray* st);
void StrArray_Swap(struct StrArray* p1, struct StrArray* p2);
