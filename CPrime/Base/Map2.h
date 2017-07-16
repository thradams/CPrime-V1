#pragma once

#include <stdbool.h>
#include "StringEx.h"

typedef struct MapItem2
{
	struct MapItem2* pNext;
	unsigned int HashValue;
	String Key;
	void* pValue;
} MapItem2;

typedef struct
{
	MapItem2** pHashTable;
	unsigned int nHashTableSize;
	size_t  nCount;
} Map2;


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map2_SetAt(Map2* pMap,
	const char* Key,
	void* newValue,
	void** ppPreviousValue);


bool Map2_Lookup(Map2* pMap,
	const char*  Key,
	void** rValue);

bool Map2_RemoveKey(Map2* pMap,
	const char*  Key,
	void** ppValue);

void Map2_Init(Map2* p);
void Map2_Destroy(Map2* p);

Map2*  Map2_Create();
void Map2_Delete(Map2 * p);

void Map2_Swap(Map2 * pA, Map2 * pB);
