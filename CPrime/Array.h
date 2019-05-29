
#pragma once
#pragma source

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    void ** pItems;
    int size;
    int capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

bool Array_Reserve(Array * p, int nelements);
bool Array_Grow(Array * p, int nelements);
void Array_Pop(Array * p, void(*pfDestroyData)(void *));
void * Array_PopGet(Array * p);
void * Array_Top(Array * p);
bool Array_Push(Array * p, void * pItem);
void Array_Clear(Array * p, void(*pfDestroyData)(void *));
void Array_Init(Array * p);

void Array_Destroy(Array * st, void(*pfDestroyData)(void *));

void Array_Swap(Array * p1, Array * p2);
void * Array_PopFront(Array * p);



struct StrArray
{
    const char ** pItems;
    int size;
    int capacity;

};

#define STRARRAY_INIT { NULL , 0 , 0 }

bool StrArray_Reserve(struct StrArray * p, int nelements);
bool StrArray_Push(struct StrArray * p, const char * pItem);
void StrArray_Clear(struct StrArray * p);
void StrArray_Init(struct StrArray * p);
void StrArray_Destroy(struct StrArray * st);
void StrArray_Swap(struct StrArray * p1, struct StrArray * p2);
