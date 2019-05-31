#pragma once
#pragma source

#include <stdbool.h>
#include "StringEx.h"



struct SymbolMapItem
{
    struct SymbolMapItem* pNext;
    unsigned int HashValue;
    char* /*@auto*/ Key;
    struct TTypePointer* pValue;
};

struct SymbolMap
{
    struct SymbolMapItem** pHashTable;
    int nHashTableSize;
    int  nCount;
    struct SymbolMap* pPrevious;
};


#define SYMBOLMAP_INIT { NULL, 100, 0 , NULL}

int SymbolMap_SetAt(struct SymbolMap* pMap,
                    const char* Key,
                    struct TTypePointer* newValue);


struct TTypePointer* SymbolMap_Find(struct SymbolMap* pMap,
    const char* Key);

bool SymbolMap_RemoveKey(struct SymbolMap* pMap,
                         const char* Key,
                         struct TTypePointer** ppValue);

void SymbolMap_Init(struct SymbolMap* p);
void SymbolMap_Destroy(struct SymbolMap* p);

struct SymbolMap* SymbolMap_Create();
void SymbolMap_Delete(struct SymbolMap* p);

struct SymbolMapItem* SymbolMap_FindBucket(struct SymbolMap* pMap, const char* Key);

void SymbolMap_Swap(struct SymbolMap* pA, struct SymbolMap* pB);

void SymbolMap_Print(struct SymbolMap* pMap);
bool SymbolMap_IsTypeName(struct SymbolMap* pMap, const char* identifierName);

struct SymbolMapItem* SymbolMap_GetAssocAt(struct SymbolMap* pMap,
    const char* Key,
                                           unsigned int* nHashBucket,
                                           unsigned int* HashValue);

struct TStructUnionSpecifier* SymbolMap_FindStructUnion(struct SymbolMap* pMap, const char* structTagName);
struct TEnumSpecifier* SymbolMap_FindEnum(struct SymbolMap* pMap, const char* enumTagName);


struct TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindTypedefDeclarationTarget(struct SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindFunction(struct SymbolMap* pMap, const char* funcName);

struct TDeclaration* SymbolMap_FindObjFunction2(struct SymbolMap* pMap,
    const char* objName,
                                                const char* funcName);

struct TDeclarationSpecifiers* SymbolMap_FindTypedefTarget(struct SymbolMap* pMap,
    const char* typedefName,
                                                           struct TDeclarator* declarator);

struct TDeclarationSpecifiers* SymbolMap_FindTypedefFirstTarget(struct SymbolMap* pMap,
    const char* typedefName,
                                                                struct TDeclarator* declarator);
