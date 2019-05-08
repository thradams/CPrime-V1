#pragma once

#include "StringEx.h"
#include "StrBuilder.h"


typedef struct
{
    struct PPToken* /*@auto*/* /*@auto [Size]*/ pItems;
    int Size;
    int Capacity;
} TokenArray;

#define TOKENARRAY_INIT {0, 0, 0}

void      TokenArray_Reserve(TokenArray* p, int nelements);
int      TokenArray_Grow(TokenArray* p, int nelements);
void     TokenArray_Pop(TokenArray* p);

struct PPToken* TokenArray_PopFront(TokenArray* p);

struct PPToken* TokenArray_Top(TokenArray* p);
void      TokenArray_PushBack(TokenArray* p, struct PPToken* pItem);
void     TokenArray_Clear(TokenArray* p);
void     TokenArray_Init(TokenArray* p);
TokenArray* TokenArray_Create(void);
void     TokenArray_Destroy(TokenArray* st);
void     TokenArray_Delete(TokenArray* st);
void     TokenArray_Swap(TokenArray* p1, TokenArray* p2);

//


bool TokenArray_Contain(TokenArray* pArray, struct PPToken* pToken);

void TokenArray_AppendCopy(TokenArray* pArrayTo, const TokenArray* pArrayFrom);
void TokenArray_AppendMove(TokenArray* pArrayTo, TokenArray* pArrayFrom);
void TokenArray_Print(const TokenArray* tokens);
void TokenArray_ToStrBuilder(const TokenArray* tokens, StrBuilder* strBuidler);

struct PPToken* TokenArray_Find(const TokenArray* pArray, const char* lexeme);
void TokenArray_Erase(TokenArray* pArray, int begin, int end);


///////////////////////////////




typedef struct TokenArrayMapItem
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    String Key;
    TokenArray* pValue;
} TokenArrayMapItem;

typedef struct
{
    TokenArrayMapItem** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
} TokenArrayMap;


#define TOKENARRAYMAP_INIT { NULL, 0, 0 }

int TokenArrayMap_SetAt(TokenArrayMap* pMap,
    const char* Key,
    TokenArray* newValue);

bool TokenArrayMap_Lookup(const TokenArrayMap* pMap,
    const char* Key,
    TokenArray** rValue);

bool TokenArrayMap_RemoveKey(TokenArrayMap* pMap,
    const char* Key);

void TokenArrayMap_Init(TokenArrayMap* p);
void TokenArrayMap_Destroy(TokenArrayMap* p);



void TokenArrayMap_Swap(TokenArrayMap* pA, TokenArrayMap* pB);


typedef struct
{
    struct PPToken* /*@auto*/* /*@auto [Size]*/ pItems;
    int Size;
    int Capacity;
} TokenSet;
#define TOKENSET_INIT { NULL, 0, 0 }

void TokenSet_PushBack(TokenSet* p, struct PPToken* pItem);
void TokenSetAppendCopy(TokenSet* pArrayTo, const TokenSet* pArrayFrom);
struct PPToken* TokenSet_Find(const TokenSet* pArray, const char* lexeme);
void TokenSet_Destroy(TokenSet* pArray);

void SetIntersection(const TokenSet* p1,
    const TokenSet* p2,
    TokenSet* pResult);