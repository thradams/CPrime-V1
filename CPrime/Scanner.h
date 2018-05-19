
#pragma once

#include "Array.h"
#include "BasicScanner.h"
#include "Map.h"
#include "List.h"
#include "Macro.h"


typedef struct
{
  String FullPath;
  String IncludePath;
  int FileIndex;
  bool PragmaOnce;
  bool bDirectInclude;
  bool bSystemLikeInclude;
} TFile;

void TFile_Delete(TFile* p);

typedef Map TFileMap;

void TFileMap_Destroy(TFileMap* p);
Result TFileMap_Set(TFileMap *map, const char*key, TFile *data);
TFile*  TFileMap_Find(TFileMap* map, const char* key);
Result TFileMap_DeleteItem(TFileMap *map, const char* key);
void TFile_DeleteVoid(void* p);


typedef struct
{
    TFile* _auto * _auto _size(Size) pItems;
    int Size;
    int Capacity;
} TFileArray;

void TFileArray_Init(TFileArray* p);
void TFileArray_Destroy(TFileArray* p);
void TFileArray_PushBack(TFileArray* p, TFile* pItem);
void TFileArray_Reserve(TFileArray* p, int n);


typedef struct
{
    ScannerItem*  pHead, *pTail;
}TScannerItemList;


void TScannerItemList_Destroy(TScannerItemList* p);
void TScannerItemList_Init(TScannerItemList* p);
void TScannerItemList_PushBack(TScannerItemList* p, ScannerItem* pItem);
void TScannerItemList_Swap(TScannerItemList* a, TScannerItemList* b);
void TScannerItemList_Clear(TScannerItemList* p);
void TScannerItemList_PopFront(TScannerItemList* p);

typedef enum
{
    NONE, // inclui
    I1,   // inclui
    I0,
    E0,
    E1, // inclui
} State;

typedef struct
{
    State* _auto _size(Size) pItems;
    int Size;
    int Capacity;
} StackInts;

void StackInts_Init(StackInts* p);
void StackInts_Destroy(StackInts* p);

typedef struct
{
  //Stack de basicscanner
  BasicScannerStack stack;

  //Mapa dos defines
  MacroMap  Defines2;

  //Stack usado para #if #else etc
  StackInts StackIfDef;

  //lista de arquivos marcados com pragma once
  TFileMap FilesIncluded;

  //Lista de diretorios de include
  StrArray IncludeDir;

  //Lista de diretorios de include
  StrArray Sources;

  //string para debug
  StrBuilder DebugString;


  //String que mantem o erro
  StrBuilder ErrorString;

  //True indica error
  bool bError;

  TScannerItemList AcumulatedTokens;
  ///////////////////////////////////////////////////
} Scanner;

void Scanner_SetError(Scanner* pScanner, const char* fmt, ...);

void Scanner_GetFilePositionString(Scanner* pScanner, StrBuilder* sb);


Result Scanner_InitString(Scanner* pScanner,
  const char* name,
  const char* text);

Result PushExpandedMacro(Scanner * pScanner, const char * defineName, const char * defineContent);


Result Scanner_Init(Scanner* pScanner);

typedef enum
{
  FileIncludeTypeQuoted,
  FileIncludeTypeIncludes,
  FileIncludeTypeFullPath,
} FileIncludeType;

void Scanner_IncludeFile(Scanner* pScanner,
  const char* fileName,
  FileIncludeType fileIncludeType, bool bSkipeBof);


void Scanner_Destroy(Scanner* pScanner);

//int Scanner_GetFileIndex(Scanner * pScanner);

int EvalExpression(const char* s, Scanner* pScanner);
void Scanner_PrintDebug(Scanner* pScanner);
void Scanner_GetError(Scanner* pScanner, StrBuilder* str);

void GetSources(const char* fileIn, StrArray* sources);
void PrintPreprocessedToFile(const char* fileIn,
  const char* configFileName);

void PrintPreprocessedToConsole(const char* fileIn,
                                const char* configFileName);

int Scanner_GetNumberOfScannerItems(Scanner * pScanner);


//NOVA INTERFACE

int Scanner_FileIndexAt(Scanner * pScanner, int index);
int Scanner_LineAt(Scanner * pScanner, int index);
bool Scanner_IsActiveAt(Scanner* pScanner, int index);
Tokens Scanner_TokenAt(Scanner * pScanner, int index);
const char * Scanner_LexemeAt(Scanner * pScanner, int index);
void Scanner_PrintItems(Scanner* pScanner);

void Scanner_Match(Scanner * pScanner);
bool Scanner_MatchToken(Scanner * pScanner, Tokens token, bool bActive);

