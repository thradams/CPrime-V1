
#pragma once
#pragma source

#include "Array.h"
#include "BasicScanner.h"
#include "Map.h"
#include "List.h"
#include "Macro.h"
#include "Options.h"

typedef struct
{
  String * /*@auto*/ FullPath;
  String * /*@auto*/ IncludePath;
  int FileIndex;
  bool PragmaOnce;
  bool bDirectInclude;
  bool bSystemLikeInclude;
} TFile;

void TFile_Delete(TFile* p);

typedef Map TFileMap;

void TFileMap_Destroy(TFileMap* p);
bool TFileMap_Set(TFileMap *map, const char*key, TFile *data);
TFile*  TFileMap_Find(TFileMap* map, const char* key);
bool TFileMap_DeleteItem(TFileMap *map, const char* key);
void TFile_DeleteVoid(void* p);


typedef struct
{
    TFile* /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
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

struct FileNode
{
  char* /*@auto*/ Key;
  struct FileNode* /*@auto*/ pNext;
};


struct FileNode* FileNode_Create(const char* key);

void FileNode_Delete(struct FileNode* p);
struct FileNodeMap
{
  int Capacity;
  struct FileNode* /*@auto*/* /*@auto*/ /*@[Capacity]*/ pNodes;
};

void FileNodeMap_Destroy(struct FileNodeMap* p);


struct FileNode* FileNodeMap_Lookup(struct FileNodeMap* t, const char* key);

void FileNodeMap_Insert(struct FileNodeMap* t, struct FileNode* pNewNode);

struct FileNodeList
{
  struct FileNode* /*@auto*/ pHead, * pTail;
};
void FileNodeList_Swap(struct FileNodeList* a, struct FileNodeList* b);
void FileNodeList_Destroy(struct FileNodeList* pItems);
void FileNodeList_PushItem(struct FileNodeList* pItems,
    struct FileNode* pItem);
void FileNodeList_PushBack(struct FileNodeList* pItems,
  const char* fileName);

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
    State* /*@auto*/ /*@[Size]*/pItems;
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
  struct StrArray IncludeDir;

  //Lista de diretorios de include
  struct FileNodeList Sources;

  //string para debug
  StrBuilder DebugString;


  //String que mantem o erro
  StrBuilder ErrorString;

  //True indica error
  bool bError;

  TScannerItemList AcumulatedTokens;

  Options* pOptions;
  ///////////////////////////////////////////////////
} Scanner;

void Scanner_SetError(Scanner* pScanner, const char* fmt, ...);

void Scanner_GetFilePositionString(Scanner* pScanner, StrBuilder* sb);


bool Scanner_InitString(Scanner* pScanner,
  const char* name,
  const char* Text);

bool PushExpandedMacro(Scanner * pScanner, const char * defineName, const char * defineContent);


bool Scanner_Init(Scanner* pScanner);

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

void GetSources(const char* configFile, const char* fileIn, bool bRecursiveSearch, struct FileNodeList* sources);
void PrintPreprocessedToFile(const char* fileIn,
  const char* configFileName);

void PrintPreprocessedToString2(StrBuilder* fp, const char *input, const char* configFileName);
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

