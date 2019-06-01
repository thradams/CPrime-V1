
#pragma once
#pragma source

#include <stdbool.h>
#include <stdlib.h>

struct StrArray
{
    const char* /*@auto*/ * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;

};

#define STRARRAY_INIT { NULL , 0 , 0 }

void StrArray_Push(struct StrArray* p, const char* pItem);
void StrArray_Init(struct StrArray* p);
void StrArray_Destroy(struct StrArray* st);
void StrArray_Swap(struct StrArray* p1, struct StrArray* p2);
