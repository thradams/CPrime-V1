
#pragma once

#include "Result.h"
#include <stdbool.h>
#include <CRTDEFS.H>
#include <stdlib.h>

typedef struct
{
    void** pItems;
    size_t size;
    size_t capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

Result Array_Reserve(Array* p, size_t nelements);
Result Array_Grow(Array* p, size_t nelements);
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
    size_t size;
    size_t capacity;

} StrArray;

#define STRARRAY_INIT { NULL , 0 , 0 }

Result StrArray_Reserve(StrArray* p, size_t nelements);
Result StrArray_Push(StrArray* p, const char* pItem);
void StrArray_Clear(StrArray* p);
void StrArray_Init(StrArray* p);
void StrArray_Destroy(StrArray* st);
void StrArray_Swap(StrArray* p1, StrArray* p2);

typedef struct
{
    int* pItems;
    size_t size;
    size_t capacity;

} ArrayInt;

Result ArrayInt_Reserve(ArrayInt* p, size_t nelements);

bool ArrayInt_IsEmpty(ArrayInt* p);

int ArrayInt_Pop(ArrayInt* p);

int ArrayInt_Top(ArrayInt* p);

Result ArrayInt_Push(ArrayInt* p, int pItem);

void ArrayInt_Clear(ArrayInt* p);

void ArrayInt_Init(ArrayInt* p);

void ArrayInt_Destroy(ArrayInt* st);

#define ArrayT(T) struct\
{\
  T** pItems;\
  size_t size;\
  size_t capacity;\
}

#define ARRAYT_INIT {NULL, 0 , 0 }
#define ArrayT_Push(p, pItem)\
  Array_Push((Array*)p, (void*)pItem)

#define ArrayT_Init(p)\
  do {\
   (p)->pItems = NULL;\
   (p)->size = 0;\
   (p)->capacity = 0; \
  } while(0)


#define ArrayT_Reserve(p, n)\
  Array_Reserve((Array*)p, n)

#define ArrayT_Destroy(T, p)\
  do{\
   for (int i = 0; i < (p)->size; i++)\
   {\
     T##_Delete((p)->pItems[i]);\
   }\
   free((p)->pItems);\
  }  while (0)

