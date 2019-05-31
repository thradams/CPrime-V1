#pragma once
#pragma source

#include <stdbool.h>
#include "StringEx.h"

struct MapItem2
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    char* /*@auto*/ Key;
    void* pValue;
};

struct Map2
{
    struct MapItem2** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
};


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map2_SetAt(struct Map2* pMap,
               const char* Key,
               void* newValue,
               void** ppPreviousValue);


bool Map2_Lookup(struct Map2* pMap,
                 const char* Key,
                 void** rValue);

bool Map2_RemoveKey(struct Map2* pMap,
                    const char* Key,
                    void** ppValue);

void Map2_Init(struct Map2* p);
void Map2_Destroy(struct Map2* p, void (*DeleteFunc)(void*));

struct Map2* Map2_Create(void);


void Map2_Swap(struct Map2* pA, struct Map2* pB);
void Map2_Delete(struct Map2* p, void(*DeleteFunc)(void*));