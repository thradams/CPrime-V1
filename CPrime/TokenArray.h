#pragma once
#pragma source

#include "StringEx.h"
#include "StrBuilder.h"


struct TokenArray
{
    struct PPToken* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

#define TOKENARRAY_INIT {0, 0, 0}

void      TokenArray_Reserve(struct TokenArray* p, int nelements);
int      TokenArray_Grow(struct TokenArray* p, int nelements);
void     TokenArray_Pop(struct TokenArray* p);

struct PPToken* TokenArray_PopFront(struct TokenArray* p);

struct PPToken* TokenArray_Top(struct TokenArray* p);
void      TokenArray_PushBack(struct TokenArray* p, struct PPToken* pItem);
void     TokenArray_Clear(struct TokenArray* p);
void     TokenArray_Init(struct TokenArray* p);
struct TokenArray* TokenArray_Create(void);
void     TokenArray_Destroy(struct TokenArray* st);
void     TokenArray_Delete(struct TokenArray* st);
void     TokenArray_Swap(struct TokenArray* p1, struct TokenArray* p2);


void TokenArray_AppendCopy(struct TokenArray* pArrayTo, const struct TokenArray* pArrayFrom);
void TokenArray_AppendMove(struct TokenArray* pArrayTo, struct TokenArray* pArrayFrom);
void TokenArray_Print(const struct TokenArray* tokens);
void TokenArray_ToStrBuilder(const struct TokenArray* tokens, StrBuilder* strBuidler);

struct PPToken* TokenArray_Find(const struct TokenArray* pArray, const char* lexeme);
void TokenArray_Erase(struct TokenArray* pArray, int begin, int end);


///////////////////////////////


struct TokenArrayMapItem
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    char* /*@auto*/ Key;
    struct TokenArray* pValue;
};

struct TokenArrayMap
{
    struct TokenArrayMapItem** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
};


#define TOKENARRAYMAP_INIT { NULL, 0, 0 }

int TokenArrayMap_SetAt(struct TokenArrayMap* pMap,
                        const char* Key,
                        struct TokenArray* newValue);

bool TokenArrayMap_Lookup(const struct TokenArrayMap* pMap,
                          const char* Key,
                          struct TokenArray** rValue);

bool TokenArrayMap_RemoveKey(struct TokenArrayMap* pMap,
                             const char* Key);

void TokenArrayMap_Init(struct TokenArrayMap* p);
void TokenArrayMap_Destroy(struct TokenArrayMap* p);



void TokenArrayMap_Swap(struct TokenArrayMap* pA, struct TokenArrayMap* pB);


struct TokenSet
{
    struct PPToken* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};
#define TOKENSET_INIT { NULL, 0, 0 }

void TokenSet_PushBack(struct TokenSet* p, struct PPToken* pItem);
void TokenSetAppendCopy(struct TokenSet* pArrayTo, const struct TokenSet* pArrayFrom);
struct PPToken* TokenSet_Find(const struct TokenSet* pArray, const char* lexeme);
void TokenSet_Destroy(struct TokenSet* pArray);

void SetIntersection(const struct TokenSet* p1,
                     const struct TokenSet* p2,
                     struct TokenSet* pResult);