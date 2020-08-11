
#pragma once
#pragma source


#include "BasicScanner.h"
#include "Map.h"

#include "Macro.h"
#include "Options.h"
#include "StrArray.h"

# //BEGIN_EXPORT
#include <stdbool.h>

struct TFile
{
    char* /*@auto*/ FullPath;
    char* /*@auto*/ IncludePath;
    int FileIndex;
    bool PragmaOnce;
    bool bDirectInclude;
    bool bSystemLikeInclude;
};

void TFile_Delete(struct TFile * p);

typedef struct Map TFileMap;

void TFileMap_Destroy(TFileMap * p);
bool TFileMap_Set(TFileMap * map, const char * key, struct TFile * data);
struct TFile * TFileMap_Find(TFileMap * map, const char * key);
bool TFileMap_DeleteItem(TFileMap * map, const char * key);
void TFile_DeleteVoid(void * p);

 
struct TFileArray
{
    struct TFile * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

void TFileArray_Init(struct TFileArray * p);
void TFileArray_Destroy(struct TFileArray * p);
void TFileArray_PushBack(struct TFileArray * p, struct TFile * pItem);
void TFileArray_Reserve(struct TFileArray * p, int n);


struct TScannerItemList
{
    struct ScannerItem * pHead, * pTail;
};


void TScannerItemList_Destroy(struct TScannerItemList * p);
void TScannerItemList_Init(struct TScannerItemList * p);
void TScannerItemList_PushBack(struct TScannerItemList * p, struct ScannerItem * pItem);
void TScannerItemList_Swap(struct TScannerItemList * a, struct TScannerItemList * b);
void TScannerItemList_Clear(struct TScannerItemList * p);
void TScannerItemList_PopFront(struct TScannerItemList * p);

struct FileNode
{
    char * /*@auto*/ Key;
    struct FileNode * /*@auto*/ pNext;
};


struct FileNode * FileNode_Create(const char * key);

void FileNode_Delete(struct FileNode * p);
void FileNode_Free(struct FileNode * p);

struct FileNodeMap
{
    int Capacity;
    struct FileNode * /*@auto*/ * /*@auto*/ /*@[Capacity]*/ pNodes;
};

void FileNodeMap_Destroy(struct FileNodeMap * p);


struct FileNode * FileNodeMap_Lookup(struct FileNodeMap * t, const char * key);

void FileNodeMap_Insert(struct FileNodeMap * t, struct FileNode * pNewNode);

struct FileNodeList
{
    struct FileNode * /*@auto*/ pHead, * pTail;
};
void FileNodeList_Swap(struct FileNodeList * a, struct FileNodeList * b);
void FileNodeList_Destroy(struct FileNodeList * pItems);
void FileNodeList_Init(struct FileNodeList * pItems);
void FileNodeList_PushItem(struct FileNodeList * pItems,
                           struct FileNode * pItem);
void FileNodeList_PushBack(struct FileNodeList * pItems,
                           const char * fileName);

enum PPState
{
    PPState_NONE, // inclui
    PPState_I1,   // inclui
    PPState_I0,
    PPState_E0,
    PPState_E1, // inclui
};

struct TPPStateStack
{
    enum PPState* /*@auto*/ /*@[Size]*/pItems;
    int Size;
    int Capacity;
};

void PPStateStack_Init(struct TPPStateStack * p);
void PPStateStack_Destroy(struct TPPStateStack * p);

struct Scanner
{
    //Stack de basicscanner
    struct BasicScannerStack stack;

    //Mapa dos defines
    struct MacroMap  Defines2;

    //Stack usado para #if #else etc
    struct TPPStateStack StackIfDef;

    //lista de arquivos marcados com pragma once
    TFileMap FilesIncluded;

    //Lista de diretorios de include
    struct StrArray IncludeDir;

    //Lista de diretorios de include
    struct FileNodeList Sources;

    //char para debug
    struct StrBuilder DebugString;


    //char que mantem o erro
    struct StrBuilder ErrorString;

    //True indica error
    bool bError;

    struct TScannerItemList AcumulatedTokens;

    struct Options * pOptions;
    ///////////////////////////////////////////////////
};

void Scanner_SetError(struct Scanner * pScanner, const char * fmt, ...);

void Scanner_GetFilePositionString(struct Scanner * pScanner, struct StrBuilder * sb);


bool Scanner_InitString(struct Scanner * pScanner,
                        const char * name,
                        const char * Text);

bool PushExpandedMacro(struct Scanner * pScanner, const char * defineName, const char * defineContent);


bool Scanner_Init(struct Scanner * pScanner);

enum FileIncludeType
{
    FileIncludeTypeQuoted,
    FileIncludeTypeIncludes,
    FileIncludeTypeFullPath,
};

void Scanner_IncludeFile(struct Scanner * pScanner,
                         const char * fileName,
                         enum FileIncludeType fileIncludeType, bool bSkipeBof);


void Scanner_Destroy(struct Scanner * pScanner);
void Scanner_Reset(struct Scanner * pScanner);

int EvalExpression(const char * s, struct Scanner * pScanner);
void Scanner_PrintDebug(struct Scanner * pScanner);
void Scanner_GetError(struct Scanner * pScanner, struct StrBuilder * str);

void GetSources(const char * configFile, const char * fileIn, bool bRecursiveSearch, struct FileNodeList * sources);
void PrintPreprocessedToFile(const char * fileIn,
                             const char * configFileName);

void PrintPreprocessedToString2(struct StrBuilder * fp, const char * input, const char * configFileName);
void PrintPreprocessedToConsole(const char * fileIn,
                                const char * configFileName);

int Scanner_GetNumberOfScannerItems(struct Scanner * pScanner);


//NOVA INTERFACE

int Scanner_FileIndexAt(struct Scanner * pScanner, int index);
int Scanner_LineAt(struct Scanner * pScanner, int index);
bool Scanner_IsActiveAt(struct Scanner * pScanner, int index);
enum Tokens Scanner_TokenAt(struct Scanner * pScanner, int index);
const char * Scanner_LexemeAt(struct Scanner * pScanner, int index);
void Scanner_PrintItems(struct Scanner * pScanner);

void Scanner_Match(struct Scanner * pScanner);
bool Scanner_MatchToken(struct Scanner * pScanner, enum Tokens token, bool bActive);

# //END_EXPORT

