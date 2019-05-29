#pragma once
#pragma source

#include <stdbool.h>
#include "PPToken.h"
#include "TokenArray.h"
#include "StrBuilder.h"
#include "Map2.h"

struct Macro
{
  String * /*@auto*/ Name;
  bool bIsFunction;
  struct TokenArray TokenSequence;
  struct TokenArray FormalArguments;
  int FileIndex;
} ;

struct Macro* Macro_Create(void);


typedef struct MacroMapItem
{
  struct MapItem2* pNext;
  unsigned int HashValue;
  String * /*@auto*/Key;
  struct Macro* pValue;
} MacroMapItem;

typedef struct
{
  MacroMapItem** pHashTable;
  unsigned int nHashTableSize;
  int  nCount;
} MacroMap;


#define MACROMAP_INIT { NULL, 0, 0 }

int MacroMap_SetAt(MacroMap* pMap,
                    const char* Key,
                    struct Macro* newValue);

bool MacroMap_Lookup(const MacroMap* pMap,
                      const char*  Key,
                      struct Macro** rValue);

bool MacroMap_RemoveKey(MacroMap* pMap,
                         const char*  Key);

void MacroMap_Init(MacroMap* p);
void MacroMap_Destroy(MacroMap* p);

void MacroMap_Swap(MacroMap * pA, MacroMap * pB);

struct Macro* MacroMap_Find(const MacroMap* pMap, const char*  Key);



void ExpandMacro(const struct TokenArray* tsOriginal,
                 const MacroMap* macros,
                 bool get_more,
                 bool skip_defined,
    bool evalmode,
                 struct Macro* caller,
                 struct TokenArray* pOutputSequence);

void ExpandMacroToText(const struct TokenArray* pTokenSequence,
                       const MacroMap* macros,
                       bool get_more,
                       bool skip_defined,
    bool evalmode,
                       struct Macro* caller,
                       StrBuilder* strBuilder);

