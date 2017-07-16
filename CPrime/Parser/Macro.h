#pragma once
#include <stdbool.h>
#include "PPToken.h"
#include "TokenArray.h"
#include "..\Base\StrBuilder.h"
#include "..\Base\Map2.h"

typedef struct
{
  String Name;
  bool bIsFunction;
  TokenArray TokenSequence;
  TokenArray FormalArguments;
  int FileIndex;
} Macro;



#define MACRO_INIT { STRING_INIT, false , TOKENARRAY_INIT, TOKENARRAY_INIT, -1}
Macro* Macro_Create();


typedef struct MacroMapItem
{
  struct MapItem2* pNext;
  unsigned int HashValue;
  String Key;
  Macro* pValue;
} MacroMapItem;

typedef struct
{
  MacroMapItem** pHashTable;
  unsigned int nHashTableSize;
  size_t  nCount;
} MacroMap;


#define MACROMAP_INIT { NULL, 0, 0 }

int MacroMap_SetAt(MacroMap* pMap,
                    const char* Key,
                    Macro* newValue);

bool MacroMap_Lookup(const MacroMap* pMap,
                      const char*  Key,
                      Macro** rValue);

bool MacroMap_RemoveKey(MacroMap* pMap,
                         const char*  Key);

void MacroMap_Init(MacroMap* p);
void MacroMap_Destroy(MacroMap* p);

void MacroMap_Swap(MacroMap * pA, MacroMap * pB);

Macro* MacroMap_Find(const MacroMap* pMap, const char*  Key);



void ExpandMacro(const TokenArray* tsOriginal,
                 const MacroMap* macros,
                 bool get_more,
                 bool skip_defined,
                 Macro* caller,
                 TokenArray* pOutputSequence);

void ExpandMacroToText(const TokenArray* pTokenSequence,
                       const MacroMap* macros,
                       bool get_more,
                       bool skip_defined,
                       Macro* caller,
                       StrBuilder* strBuilder);

