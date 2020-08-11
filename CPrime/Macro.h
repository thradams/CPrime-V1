#pragma once
#pragma source

#include <stdbool.h>
#include "PPToken.h"
#include "TokenArray.h"
#include "StrBuilder.h"
#include "Map2.h"

# //BEGIN_EXPORT

struct Macro
{
    char* /*@auto*/ Name;
    bool bIsFunction;
    struct TokenArray TokenSequence;
    struct TokenArray FormalArguments;
    int FileIndex;
};

struct Macro* Macro_Create(void);


struct MacroMapItem
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    char* /*@auto*/Key;
    struct Macro* pValue;
};

struct MacroMap
{
    struct MacroMapItem** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
};


#define MACROMAP_INIT { NULL, 0, 0 }

int MacroMap_SetAt(struct MacroMap* pMap,
                   const char* Key,
                   struct Macro* newValue);

bool MacroMap_Lookup(const struct MacroMap* pMap,
                     const char* Key,
                     struct Macro** rValue);

bool MacroMap_RemoveKey(struct MacroMap* pMap,
                        const char* Key);

void MacroMap_Init(struct MacroMap* p);
void MacroMap_Destroy(struct MacroMap* p);

void MacroMap_Swap(struct MacroMap* pA, struct MacroMap* pB);

struct Macro* MacroMap_Find(const struct MacroMap* pMap, const char* Key);



void ExpandMacro(const struct TokenArray* tsOriginal,
                 const struct MacroMap* macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro* caller,
                 struct TokenArray* pOutputSequence);

void ExpandMacroToText(const struct TokenArray* pTokenSequence,
                       const struct MacroMap* macros,
                       bool get_more,
                       bool skip_defined,
                       bool evalmode,
                       struct Macro* caller,
                       struct StrBuilder* strBuilder);


# //END_EXPORT

