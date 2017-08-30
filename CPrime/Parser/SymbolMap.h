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
    TTypePointer* newValue);


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
bool SymbolMap_IsTypeName(SymbolMap* pMap, const char* identifierName);

struct TStructUnionSpecifier* SymbolMap_FindStructUnion(SymbolMap* pMap, const char* structTagName);
struct TEnumSpecifier* SymbolMap_FindEnum(SymbolMap* pMap, const char* enumTagName);

struct TTypePointer;
typedef struct TTypePointer TTypePointer;
typedef TTypePointer TTypeSpecifier;
TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindTypedefDeclarationTarget(SymbolMap* pMap,
    const char* typedefName);
struct TDeclaration* SymbolMap_FindFunction(SymbolMap* pMap, const char* funcName);
