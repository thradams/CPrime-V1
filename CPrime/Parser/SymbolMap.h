#pragma once

#include <stdbool.h>
#include "..\Base\StringEx.h"

struct TTypePointer;
typedef struct TTypePointer TTypePointer;

typedef struct SymbolMapItem
{
	struct SymbolMapItem* pNext;
	unsigned int HashValue;
	String Key;
    TTypePointer* pValue;
} SymbolMapItem;

typedef struct SymbolMap
{
	SymbolMapItem** pHashTable;
	unsigned int nHashTableSize;
	size_t  nCount;
    struct SymbolMap* pPrevious;
} SymbolMap;


#define SYMBOLMAP_INIT { NULL, 100, 0 , NULL}

int SymbolMap_SetAt(SymbolMap* pMap,
	const char* Key,
    TTypePointer* newValue,
    TTypePointer** ppPreviousValue);


TTypePointer* SymbolMap_Find(SymbolMap* pMap,
	 const char*  Key);

bool SymbolMap_RemoveKey(SymbolMap* pMap,
	const char*  Key,
    TTypePointer** ppValue);

void SymbolMap_Init(SymbolMap* p);
void SymbolMap_Destroy(SymbolMap* p);

SymbolMap*  SymbolMap_Create();
void SymbolMap_Delete(SymbolMap * p);

SymbolMapItem* SymbolMap_FindBucket(SymbolMap* pMap, const char*  Key);

void SymbolMap_Swap(SymbolMap * pA, SymbolMap * pB);

void SymbolMap_Print(SymbolMap* pMap);
int SymbolMap_IsTypeName(SymbolMap* pMap, const char* identifierName);
