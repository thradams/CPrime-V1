


#include <stdio.h>

#include <time.h>  


#include <stdlib.h>








#include <stdbool.h>



typedef struct
{
    void ** pItems;
    int size;
    int capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

bool Array_Reserve(Array * p, int nelements);
bool Array_Grow(Array * p, int nelements);
void Array_Pop(Array * p, void(*pfDestroyData)(void *));
void * Array_PopGet(Array * p);
void * Array_Top(Array * p);
bool Array_Push(Array * p, void * pItem);
void Array_Clear(Array * p, void(*pfDestroyData)(void *));
void Array_Init(Array * p);

void Array_Destroy(Array * st, void(*pfDestroyData)(void *));

void Array_Swap(Array * p1, Array * p2);
void * Array_PopFront(Array * p);



struct StrArray
{
    const char ** pItems;
    int size;
    int capacity;

};

#define STRARRAY_INIT { NULL , 0 , 0 }

bool StrArray_Reserve(struct StrArray * p, int nelements);
bool StrArray_Push(struct StrArray * p, const char * pItem);
void StrArray_Clear(struct StrArray * p);
void StrArray_Init(struct StrArray * p);
void StrArray_Destroy(struct StrArray * st);
void StrArray_Swap(struct StrArray * p1, struct StrArray * p2);



#define ForEachListItem(T, var, list)\
  for (T * var = (list)->pHead ; var != NULL; var =  var->pNext)

#define List_IsFirstItem(pList, pItem) ((pList)->pHead == (pItem))








#if _DEBUG
#define Malloc(x) DebugMalloc(__FILE__, __LINE__, (x))
#define Realloc(x, s) DebugRealloc(__FILE__, __LINE__, (x), (s))
void * DebugMalloc(const char * fileName, int line, size_t size);
void * DebugRealloc(const char * fileName, int line, void * ptr, size_t new_size);
void Free(void * ptr);
#else
#define Malloc(x) malloc(x)
#define Realloc(x, s) realloc((x), (s))
#define Free(x) free(x)
#endif


void PrintMemory();

#include <string.h>



typedef char String;



String * StrDup(const char * p);
int StrIComp(char const* a, char const* b);
char* StrIStr(const char* str1, const char* str2);
bool IsSuffix(const char * s, const char * suffix);

#define PTR_STRING_REPLACE(a, b)\
do\
{\
  Free(a);\
  if (b)\
  {\
   a = Malloc(strlen(b) + 1);\
   if (a)\
    strcpy(a, b);\
  }\
  else\
  {\
    a = 0;\
  }\
} while (0)


#define PTR_SWAP(a, b)\
do\
{\
  void* t = (a);\
  (a) = (b);\
  (b) = t;\
} while (0)











#include <stdarg.h>

#include <wchar.h>




typedef struct
{
    char*  c_str;
    int size;
    int capacity;

} StrBuilder;

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

void StrBuilder_Init(StrBuilder* p);

bool StrBuilder_Reserve(StrBuilder* p, int nelements);

void StrBuilder_Attach(StrBuilder* wstr,
                       char* psz,
                       int nBytes);

void StrBuilder_Destroy(StrBuilder* wstr);
void StrBuilder_Swap(StrBuilder* str1, StrBuilder* str2);


void StrBuilder_Clear(StrBuilder* wstr);

bool StrBuilder_SetN(StrBuilder* p,
                       const char* source,
                       int nelements);

bool StrBuilder_Set(StrBuilder* p,
                      const char* source);

bool StrBuilder_AppendN(StrBuilder* p,
                          const char* source,
                          int nelements);

bool StrBuilder_Append(StrBuilder* p,
                         const char* source);

char* StrBuilder_Release(StrBuilder* p);


void StrBuilder_AppendFmt(StrBuilder * p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(StrBuilder * p, int nspaces, const char* fmt, ...);

bool StrBuilder_AppendWChar(StrBuilder * p, wchar_t wch);
bool StrBuilder_AppendW(StrBuilder * p, const wchar_t* psz);
bool StrBuilder_AppendChar(StrBuilder * p, char wch);
void StrBuilder_Trim(StrBuilder* p);
bool StrBuilder_AppendUpper(StrBuilder *p, const char* s);

bool StrBuilder_AppendIdent(StrBuilder* p,
	int nspaces,
	const char* source);


void StrBuilder_AppendFmtLn(StrBuilder * p,
    int nspaces,
    const char* fmt,
    ...);
void StrBuilder_AppendFmtV(StrBuilder * p, const char* fmt, va_list va);








struct Stream
{
    
    String* /*@auto*/ NameOrFullPath;
    String* /*@auto*/ FullDir2;
     
    
    String * /*@auto*/ Text;
    int TextLen;

    wchar_t Character;
    int Position;
    int Line;
    int Column;
};



bool Stream_Init(struct Stream* pfStream,
    const char* name,
    const char* psz);

bool Stream_InitFile(struct Stream* pfStream,
    const char* fileName);

void Stream_Destroy(struct Stream* pfStream);

wchar_t Stream_LookAhead(struct Stream* pStream);

void Stream_Match(struct Stream* pStream);
bool Stream_MatchChar(struct Stream* pStream, wchar_t ch);





#define LOCALSTRBUILDER_NCHARS 7

struct LocalStrBuilder
{
  char* c_str;
  int size;
  int capacity;
  char chars[LOCALSTRBUILDER_NCHARS + 1];

};


void LocalStrBuilder_Init(struct LocalStrBuilder* p);

void LocalStrBuilder_Swap(struct LocalStrBuilder* pA, struct LocalStrBuilder* pB);

void LocalStrBuilder_Destroy(struct LocalStrBuilder* p);

void LocalStrBuilder_Reserve(struct LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Print(struct LocalStrBuilder* p);

void LocalStrBuilder_Clear(struct LocalStrBuilder* p);

void LocalStrBuilder_Grow(struct LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Append(struct LocalStrBuilder* p, const char* source);
void LocalStrBuilder_AppendChar(struct LocalStrBuilder* p, char ch);
void LocalStrBuilder_Set(struct LocalStrBuilder* p, const char* source);


#define LANGUAGE_EXTENSIONS



typedef enum
{
    TK_NONE,
    TK_BOF,
    TK_EOF,
    TK_ENDMARK,
    TK_LINE_COMMENT,
    TK_COMMENT,
    TK_OPEN_COMMENT,
    TK_CLOSE_COMMENT,
    TK_STRING_LITERAL,
    TK_IDENTIFIER,
    TK_SPACES,
    TK_DECIMAL_INTEGER,
    TK_HEX_INTEGER,
    TK_OCTAL_INTEGER,
    TK_FLOAT_NUMBER,
    TK_MACROPLACEHOLDER,
    TK_BREAKLINE,
    TK_BACKSLASHBREAKLINE,
    CHAR1, 
    CHARACTER_TABULATION,
    TK_PREPROCESSOR,
    TK_ERROR, 


    
    TK_EXCLAMATION_MARK,
    TK_QUOTATION_MARK,
    TK_NUMBER_SIGN,

    TK_DOLLAR_SIGN,
    TK_PERCENT_SIGN,
    TK_AMPERSAND,
    TK_APOSTROPHE,
    TK_LEFT_PARENTHESIS,
    TK_RIGHT_PARENTHESIS,
    TK_ASTERISK,
    TK_PLUS_SIGN,
    TK_COMMA,
    TK_HYPHEN_MINUS,
    TK_HYPHEN_MINUS_NEG,
    TK_FULL_STOP,
    TK_SOLIDUS,

    TK_COLON,
    TK_SEMICOLON,
    TK_LESS_THAN_SIGN,
    TK_EQUALS_SIGN,
    TK_GREATER_THAN_SIGN,
    TK_QUESTION_MARK,
    TK_COMMERCIAL_AT,

    TK_LEFT_SQUARE_BRACKET,
    REVERSE_SOLIDUS,
    TK_RIGHT_SQUARE_BRACKET,
    TK_CIRCUMFLEX_ACCENT,
    TK_LOW_LINE,
    TK_GRAVE_ACCENT,

    TK_LEFT_CURLY_BRACKET,
    TK_VERTICAL_LINE,
    TK_RIGHT_CURLY_BRACKET,
    TK_TILDE, 

    
    TK_ARROW,
    TK_PLUSPLUS,
    TK_MINUSMINUS,
    TK_LESSLESS,
    TK_GREATERGREATER,
    TK_LESSEQUAL,
    TK_GREATEREQUAL,
    TK_EQUALEQUAL,
    TK_NOTEQUAL,
    TK_ANDAND,
    TK_OROR,
    TK_MULTIEQUAL,
    TK_DIVEQUAL,
    TK_PERCENT_EQUAL,
    TK_PLUSEQUAL,
    TK_MINUS_EQUAL,
    TK_ANDEQUAL,
    TK_CARETEQUAL,
    TK_OREQUAL,
    TK_NUMBERNUMBER,
    TK_LESSCOLON,
    TK_COLONGREATER,
    TK_LESSPERCENT,
    TK_PERCENTGREATER,
    TK_PERCENTCOLON,
    TK_DOTDOTDOT,
    TK_GREATERGREATEREQUAL,
    TK_LESSLESSEQUAL,
    TK_PERCENTCOLONPERCENTCOLON,

    TK_CHAR_LITERAL,

    TK_AUTO,



    TK_BREAK,
    TK_CASE,
    TK_CHAR,
    TK_CONST,
    TK_CONTINUE,
    TK_DEFAULT,
    TK_DO,
    TK_DOUBLE,
    TK_ELSE,
    TK_ENUM,
    TK_EXTERN,
    TK_FLOAT,
    TK_FOR,
    TK_GOTO,
    TK_IF,
    TK_INT,
    TK_LONG,
    
    
    TK__INT8,
    TK__INT16,
    TK__INT32,
    TK__INT64,
    TK__WCHAR_T,
    
    TK_REGISTER,
    TK_RETURN,
    TK_SHORT,
    TK_SIGNED,
    TK_SIZEOF,
    TK_STATIC,
    TK_STRUCT,
    TK_SWITCH,
    TK_TYPEDEF,
    TK_UNION,
    TK_UNSIGNED,
    TK_VOID,
    TK_VOLATILE,
    TK_WHILE,
    TK__THREAD_LOCAL,
    TK__BOOL,
    TK__COMPLEX,
    TK__ATOMIC,
    TK_RESTRICT,
    TK__STATIC_ASSERT,
    TK_INLINE,
    TK__INLINE,
    TK__FORCEINLINE, 
    TK__NORETURN,
    TK__ALIGNAS,
    TK__GENERIC,
    TK__IMAGINARY,
    TK__ALINGOF,

    
    TK__ASM, 

    
    TK_PRE_INCLUDE,
    TK_PRE_PRAGMA,
    TK_PRE_IF,
    TK_PRE_ELIF,
    TK_PRE_IFNDEF,
    TK_PRE_IFDEF,
    TK_PRE_ENDIF,
    TK_PRE_ELSE,
    TK_PRE_ERROR,
    TK_PRE_LINE,
    TK_PRE_UNDEF,
    TK_PRE_DEFINE,
    
    TK_MACRO_CALL,
    TK_MACRO_EOF,
    TK_FILE_EOF,



} Tokens;


struct ScannerItem
{
    struct LocalStrBuilder lexeme;
    Tokens token;
    int Line /*@= -1*/;
    int FileIndex /*@= -1*/;
    bool bActive /*@= 1*/;
    struct ScannerItem * pNext;
};


const char * TokenToString(Tokens tk);

void ScannerItem_Init(struct ScannerItem * scannerItem);
void ScannerItem_Reset(struct ScannerItem * scannerItem);
void ScannerItem_Swap(struct ScannerItem * scannerItem, struct ScannerItem * other);
void ScannerItem_Destroy(struct ScannerItem * scannerItem);
void ScannerItem_Copy(struct ScannerItem * scannerItem, struct ScannerItem * other);
struct ScannerItem * ScannerItem_Create(void);
void ScannerItem_Delete(struct ScannerItem * scannerItem);

typedef enum
{
    BasicScannerType_Macro,
    BasicScannerType_Token,
    BasicScannerType_File,
} BasicScannerType;

typedef struct BasicScanner
{
    BasicScannerType Type;
    struct Stream stream;
    struct ScannerItem currentItem;

    
    bool bLineStart;
    bool bMacroExpanded;
    int FileIndex;
    Tokens m_Token;
    struct BasicScanner * pPrevious;

} BasicScanner;


const char * BasicScanner_Lexeme(BasicScanner * scanner);
bool        BasicScanner_IsLexeme(BasicScanner * scanner, const char * psz);

void        BasicScanner_Match(BasicScanner * scanner);
bool         BasicScanner_MatchToken(BasicScanner * scanner, Tokens token);
bool      BasicScanner_InitFile(BasicScanner * pScanner, const char * fileName);
bool      BasicScanner_CreateFile(const char * fileName, BasicScanner ** pp);
void        BasicScanner_Delete(BasicScanner * pScanner);

bool BasicScanner_Init(BasicScanner * pScanner,
                       const char * name,
                       const char * Text,
                       BasicScannerType Type);

bool BasicScanner_Create(BasicScanner ** pp,
                         const char * name,
                         const char * Text,
                         BasicScannerType Type);

void BasicScanner_Destroy(BasicScanner * pScanner);



typedef BasicScanner * BasicScannerStack;
#define ITEM_STACK_INIT NULL
void BasicScannerStack_Init(BasicScannerStack * stack);
void BasicScannerStack_Push(BasicScannerStack * stack, BasicScanner * pItem);
BasicScanner * BasicScannerStack_PopGet(BasicScannerStack * stack);
void BasicScannerStack_Pop(BasicScannerStack * stack);
void BasicScannerStack_PopIfNotLast(BasicScannerStack * stack);
void BasicScannerStack_Destroy(BasicScannerStack * stack);

#define ForEachBasicScanner(pItem, stack)\
    for (BasicScanner* pItem = stack;\
      pItem;\
      pItem = pItem->pPrevious)




#include <inttypes.h>




struct BucketItem
{
    String * /*@auto*/ key;
    void * data;
    uint32_t hash;
};
#define BUCKET_ITEM_INIT { NULL, NULL, 0 }

typedef struct
{
    struct BucketItem ** data;
    int size;
    int capacity;

} Bucket;
#define BUCKET_INIT {NULL , 0,0 }

typedef struct
{
    Bucket ** data;
    int size;
} Buckets;
#define BUCKETS_INIT { NULL, 0}

typedef struct
{
    Buckets buckets;
    int Size;
} Map;

#define MAP_INIT {BUCKETS_INIT, 0}

bool Map_Init(Map * map, int nBuckets);

void Map_Swap(Map * map, Map * map2);

void Map_Destroy(Map * map, void(*pfDestroyData)(void *));

void Map_Delete(Map * map, void(*pfDestroyData)(void *));
bool Map_Create(Map ** map, int nBuckets);

bool Map_Set(Map * map, const char * key, void * data);
bool Map_SetMoveKey(Map * map, String ** key, void * data);

bool Map_Find(Map * map, const char * key, void ** pp);
void * Map_Find2(Map * map, const char * key);
bool Map_DeleteItem(Map * map, const char * key, void(*pfDestroyData)(void *));
bool Map_DeleteItemOpt(Map * map, const char * key, void(*pfDestroyData)(void *));

void Map_Print(Map * map);






typedef struct
{
    Buckets buckets;
    int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

bool MultiMap_Init(MultiMap * map, int nBuckets);
void MultiMap_Destroy(MultiMap * map, void(*pfDestroyData)(void *));


bool MultiMap_Add(MultiMap * map, const char * key, void * data);




Bucket * MultiMap_FindBucket(MultiMap * map, const char * key);
void MultiMap_Swap(MultiMap * map, MultiMap * map2);













struct TokenArray
{
    struct PPToken * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

#define TOKENARRAY_INIT {0, 0, 0}

void      TokenArray_Reserve(struct TokenArray * p, int nelements);
int      TokenArray_Grow(struct TokenArray * p, int nelements);
void     TokenArray_Pop(struct TokenArray * p);

struct PPToken * TokenArray_PopFront(struct TokenArray * p);

struct PPToken * TokenArray_Top(struct TokenArray * p);
void      TokenArray_PushBack(struct TokenArray * p, struct PPToken * pItem);
void     TokenArray_Clear(struct TokenArray * p);
void     TokenArray_Init(struct TokenArray * p);
struct TokenArray * TokenArray_Create(void);
void     TokenArray_Destroy(struct TokenArray * st);
void     TokenArray_Delete(struct TokenArray * st);
void     TokenArray_Swap(struct TokenArray * p1, struct TokenArray * p2);


void TokenArray_AppendCopy(struct TokenArray * pArrayTo, const struct TokenArray * pArrayFrom);
void TokenArray_AppendMove(struct TokenArray * pArrayTo, struct TokenArray * pArrayFrom);
void TokenArray_Print(const struct TokenArray * tokens);
void TokenArray_ToStrBuilder(const struct TokenArray * tokens, StrBuilder * strBuidler);

struct PPToken * TokenArray_Find(const struct TokenArray * pArray, const char * lexeme);
void TokenArray_Erase(struct TokenArray * pArray, int begin, int end);





typedef struct TokenArrayMapItem
{
    struct MapItem2 * pNext;
    unsigned int HashValue;
    String * /*@auto*/ Key;
    struct TokenArray * pValue;
} TokenArrayMapItem;

typedef struct
{
    TokenArrayMapItem ** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
} TokenArrayMap;


#define TOKENARRAYMAP_INIT { NULL, 0, 0 }

int TokenArrayMap_SetAt(TokenArrayMap * pMap,
                        const char * Key,
                        struct TokenArray * newValue);

bool TokenArrayMap_Lookup(const TokenArrayMap * pMap,
                          const char * Key,
                          struct TokenArray ** rValue);

bool TokenArrayMap_RemoveKey(TokenArrayMap * pMap,
                             const char * Key);

void TokenArrayMap_Init(TokenArrayMap * p);
void TokenArrayMap_Destroy(TokenArrayMap * p);



void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB);


typedef struct
{
    struct PPToken * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
} TokenSet;
#define TOKENSET_INIT { NULL, 0, 0 }

void TokenSet_PushBack(TokenSet * p, struct PPToken * pItem);
void TokenSetAppendCopy(TokenSet * pArrayTo, const TokenSet * pArrayFrom);
struct PPToken * TokenSet_Find(const TokenSet * pArray, const char * lexeme);
void TokenSet_Destroy(TokenSet * pArray);

void SetIntersection(const TokenSet * p1,
                     const TokenSet * p2,
                     TokenSet * pResult);

enum PPTokenType
{
    PPTokenType_Identifier,
    PPTokenType_Number,
    PPTokenType_CharConstant,
    PPTokenType_StringLiteral,
    PPTokenType_Punctuator,
    PPTokenType_Spaces,
    PPTokenType_Other,
};

struct PPToken
{
    enum PPTokenType Token;
    String * /*@auto*/Lexeme;
    TokenSet HiddenSet;
};

#define TOKEN_INIT { PPTokenType_Other, NULL, TOKENSET_INIT }


void PPToken_Destroy(struct PPToken* p);

struct PPToken* PPToken_Create(const char* s, enum PPTokenType token);
struct PPToken* PPToken_Clone(struct PPToken* p);
void PPToken_Delete(struct PPToken* p);
void PPToken_DeleteVoid(void* pv);
void PPToken_Swap(struct PPToken* pA, struct PPToken* pB);


bool PPToken_IsIdentifier(struct PPToken* pHead);
bool PPToken_IsSpace(struct PPToken* pHead);
bool PPToken_IsStringizingOp(struct PPToken* pHead);
bool PPToken_IsConcatOp(struct PPToken* pHead);
bool PPToken_IsStringLit(struct PPToken* pHead);
bool PPToken_IsCharLit(struct PPToken* pHead);
bool PPToken_IsOpenPar(struct PPToken* pHead);
bool PPToken_IsChar(struct PPToken* pHead, char ch);
bool PPToken_IsLexeme(struct PPToken* pHead, const char* ch);






typedef struct MapItem2
{
    struct MapItem2 * pNext;
    unsigned int HashValue;
    String * /*@auto*/ Key;
    void * pValue;
} MapItem2;

typedef struct
{
    MapItem2 ** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
} Map2;


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map2_SetAt(Map2 * pMap,
               const char * Key,
               void * newValue,
               void ** ppPreviousValue);


bool Map2_Lookup(Map2 * pMap,
                 const char * Key,
                 void ** rValue);

bool Map2_RemoveKey(Map2 * pMap,
                    const char * Key,
                    void ** ppValue);

void Map2_Init(Map2 * p);
void Map2_Destroy(Map2 * p, void (*DeleteFunc)(void *));

Map2 * Map2_Create(void);


void Map2_Swap(Map2 * pA, Map2 * pB);
void Map2_Delete(Map2 * p, void(*DeleteFunc)(void *));

struct Macro
{
    String * /*@auto*/ Name;
    bool bIsFunction;
    struct TokenArray TokenSequence;
    struct TokenArray FormalArguments;
    int FileIndex;
};

struct Macro * Macro_Create(void);


struct MacroMapItem
{
    struct MapItem2 * pNext;
    unsigned int HashValue;
    String * /*@auto*/Key;
    struct Macro * pValue;
};

struct MacroMap
{
    struct MacroMapItem ** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
};


#define MACROMAP_INIT { NULL, 0, 0 }

int MacroMap_SetAt(struct MacroMap * pMap,
                   const char * Key,
                   struct Macro * newValue);

bool MacroMap_Lookup(const struct MacroMap * pMap,
                     const char * Key,
                     struct Macro ** rValue);

bool MacroMap_RemoveKey(struct MacroMap * pMap,
                        const char * Key);

void MacroMap_Init(struct MacroMap * p);
void MacroMap_Destroy(struct MacroMap * p);

void MacroMap_Swap(struct MacroMap * pA, struct MacroMap * pB);

struct Macro * MacroMap_Find(const struct MacroMap * pMap, const char * Key);



void ExpandMacro(const struct TokenArray * tsOriginal,
                 const struct MacroMap * macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro * caller,
                 struct TokenArray * pOutputSequence);

void ExpandMacroToText(const struct TokenArray * pTokenSequence,
                       const struct MacroMap * macros,
                       bool get_more,
                       bool skip_defined,
                       bool evalmode,
                       struct Macro * caller,
                       StrBuilder * strBuilder);




enum CompilerTarget
{
    CompilerTarget_Annotated,
    CompilerTarget_Preprocessed,
    CompilerTarget_CXX
};

struct Options
{
    bool bExpandMacros;
    bool bIncludeComments /*@=1*/;

    enum CompilerTarget Target;

    
    bool bCannonical;

    bool bAmalgamate;

    bool bNoImplicitTag;
};

#define OPTIONS_INIT {false, true, CompilerTarget_Annotated,  false, false, false}
void Options_Destroy(struct Options* options);

typedef struct
{
    String * /*@auto*/ FullPath;
    String * /*@auto*/ IncludePath;
    int FileIndex;
    bool PragmaOnce;
    bool bDirectInclude;
    bool bSystemLikeInclude;
} TFile;

void TFile_Delete(TFile * p);

typedef Map TFileMap;

void TFileMap_Destroy(TFileMap * p);
bool TFileMap_Set(TFileMap * map, const char * key, TFile * data);
TFile * TFileMap_Find(TFileMap * map, const char * key);
bool TFileMap_DeleteItem(TFileMap * map, const char * key);
void TFile_DeleteVoid(void * p);


typedef struct
{
    TFile * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
} TFileArray;

void TFileArray_Init(TFileArray * p);
void TFileArray_Destroy(TFileArray * p);
void TFileArray_PushBack(TFileArray * p, TFile * pItem);
void TFileArray_Reserve(TFileArray * p, int n);


typedef struct
{
    struct ScannerItem * pHead, * pTail;
}TScannerItemList;


void TScannerItemList_Destroy(TScannerItemList * p);
void TScannerItemList_Init(TScannerItemList * p);
void TScannerItemList_PushBack(TScannerItemList * p, struct ScannerItem * pItem);
void TScannerItemList_Swap(TScannerItemList * a, TScannerItemList * b);
void TScannerItemList_Clear(TScannerItemList * p);
void TScannerItemList_PopFront(TScannerItemList * p);

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
    PPState_NONE, 
    PPState_I1,   
    PPState_I0,
    PPState_E0,
    PPState_E1, 
};

typedef struct
{
    enum PPState * /*@auto*/ /*@[Size]*/pItems;
    int Size;
    int Capacity;
} StackInts;

void StackInts_Init(StackInts * p);
void StackInts_Destroy(StackInts * p);

typedef struct
{
    
    BasicScannerStack stack;

    
    struct MacroMap  Defines2;

    
    StackInts StackIfDef;

    
    TFileMap FilesIncluded;

    
    struct StrArray IncludeDir;

    
    struct FileNodeList Sources;

    
    StrBuilder DebugString;


    
    StrBuilder ErrorString;

    
    bool bError;

    TScannerItemList AcumulatedTokens;

    struct Options * pOptions;
    
} Scanner;

void Scanner_SetError(Scanner * pScanner, const char * fmt, ...);

void Scanner_GetFilePositionString(Scanner * pScanner, StrBuilder * sb);


bool Scanner_InitString(Scanner * pScanner,
                        const char * name,
                        const char * Text);

bool PushExpandedMacro(Scanner * pScanner, const char * defineName, const char * defineContent);


bool Scanner_Init(Scanner * pScanner);

typedef enum
{
    FileIncludeTypeQuoted,
    FileIncludeTypeIncludes,
    FileIncludeTypeFullPath,
} FileIncludeType;

void Scanner_IncludeFile(Scanner * pScanner,
                         const char * fileName,
                         FileIncludeType fileIncludeType, bool bSkipeBof);


void Scanner_Destroy(Scanner * pScanner);
void Scanner_Reset(Scanner * pScanner);

int EvalExpression(const char * s, Scanner * pScanner);
void Scanner_PrintDebug(Scanner * pScanner);
void Scanner_GetError(Scanner * pScanner, StrBuilder * str);

void GetSources(const char * configFile, const char * fileIn, bool bRecursiveSearch, struct FileNodeList * sources);
void PrintPreprocessedToFile(const char * fileIn,
                             const char * configFileName);

void PrintPreprocessedToString2(StrBuilder * fp, const char * input, const char * configFileName);
void PrintPreprocessedToConsole(const char * fileIn,
                                const char * configFileName);

int Scanner_GetNumberOfScannerItems(Scanner * pScanner);




int Scanner_FileIndexAt(Scanner * pScanner, int index);
int Scanner_LineAt(Scanner * pScanner, int index);
bool Scanner_IsActiveAt(Scanner * pScanner, int index);
Tokens Scanner_TokenAt(Scanner * pScanner, int index);
const char * Scanner_LexemeAt(Scanner * pScanner, int index);
void Scanner_PrintItems(Scanner * pScanner);

void Scanner_Match(Scanner * pScanner);
bool Scanner_MatchToken(Scanner * pScanner, Tokens token, bool bActive);







struct TTypePointer;
typedef struct TTypePointer TTypePointer;

struct SymbolMapItem
{
    struct SymbolMapItem* pNext;
    unsigned int HashValue;
    String* /*@auto*/ Key;
    TTypePointer* pValue;
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
    TTypePointer* newValue);


TTypePointer* SymbolMap_Find(struct SymbolMap* pMap,
    const char* Key);

bool SymbolMap_RemoveKey(struct SymbolMap* pMap,
    const char* Key,
    TTypePointer** ppValue);

void SymbolMap_Init(struct SymbolMap* p);
void SymbolMap_Destroy(struct SymbolMap* p);

struct SymbolMap* SymbolMap_Create();
void SymbolMap_Delete(struct SymbolMap* p);

struct SymbolMapItem* SymbolMap_FindBucket(struct SymbolMap* pMap, const char* Key);

void SymbolMap_Swap(struct SymbolMap* pA, struct SymbolMap* pB);

void SymbolMap_Print(struct SymbolMap* pMap);
bool SymbolMap_IsTypeName(struct SymbolMap* pMap, const char* identifierName);

struct SymbolMapItem * SymbolMap_GetAssocAt(
    struct SymbolMap * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue);

struct TStructUnionSpecifier* SymbolMap_FindStructUnion(struct SymbolMap* pMap, const char* structTagName);
struct TEnumSpecifier* SymbolMap_FindEnum(struct SymbolMap* pMap, const char* enumTagName);

struct TTypePointer;
typedef struct TTypePointer TTypePointer;

struct TTypeSpecifier;
typedef struct TTypeSpecifier TTypeSpecifier;

TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindTypedefDeclarationTarget(struct SymbolMap* pMap,
    const char* typedefName);
struct TDeclaration* SymbolMap_FindFunction(struct SymbolMap* pMap, const char* funcName);
struct TDeclaration* SymbolMap_FindObjFunction2(struct SymbolMap* pMap,
    const char* objName,
    const char* funcName);



struct TDeclarator;

struct TDeclarationSpecifiers* SymbolMap_FindTypedefTarget(struct SymbolMap* pMap,
    const char* typedefName,
    struct TDeclarator* declarator);

struct TDeclarationSpecifiers* SymbolMap_FindTypedefFirstTarget(struct SymbolMap* pMap,
    const char* typedefName,
    struct TDeclarator* declarator);



#define CAST(FROM, TO) \
static inline TO *  FROM##_As_##TO( FROM*  p)\
{\
if (p != NULL &&  p->Type == TO##_ID)\
    return (  TO * )p;\
  return NULL;\
}\
static inline  FROM *  TO##_As_##FROM( TO*  p)\
{\
    return (  FROM * )p;\
}

#define CASTSAME(FROM, TO) \
static inline struct TO * FROM##_As_##TO(struct FROM* p) { return (struct TO * ) p; }\
static inline struct FROM * TO##_As_##FROM(struct TO* p) { return (struct FROM *) p; }


 

typedef enum EType
{
    TypeNull,
    TDeclaration_ID,
    TGroupDeclaration_ID,
    TStaticAssertDeclaration_ID,
    TEofDeclaration_ID,
    TInitDeclarator_ID,

    TSingleTypeSpecifier_ID,
    TEnumSpecifier_ID,
    TStructUnionSpecifier_ID,
    TStorageSpecifier_ID,
    TAtomicTypeSpecifier_ID,
    TTemplateTypeSpecifier_ID,
    TStructDeclaration_ID,
    TAlignmentSpecifier_ID,
    TTypeQualifier_ID,
    TFunctionSpecifier_ID,
    TCompoundStatement_ID,
    TExpressionStatement_ID,
    TSwitchStatement_ID,
    TLabeledStatement_ID,
    TForStatement_ID,
    TJumpStatement_ID,
    TAsmStatement_ID,
    TWhileStatement_ID,
    TDoStatement_ID,
    TIfStatement_ID,
    TypeName_ID,
    TEnumerator_ID,

    TInitializerListType_ID,

    TPrimaryExpression_ID,
    TUnaryExpressionOperator_ID,
    TCastExpressionType_ID,
    TPrimaryExpressionValue_ID,
    TPrimaryExpressionLiteral_ID,
    TPostfixExpressionCore_ID,
    TBinaryExpression_ID,
    TTernaryExpression_ID,
    TPrimaryExpressionLambda_ID,
    TParameter_ID
} EType;

struct TTypePointer
{
    EType Type;
};


#define CASE(T) case T##_ID


typedef struct
{
    int FileIndex;
    int Line;
} TPosition;
#define TPOSITION_INIT {0,0}

struct TExpression;
typedef struct TExpression TExpression;


typedef struct
{
     
    EType Type /*@=TStaticAssertDeclaration_ID*/;

    TExpression * /*@auto*/  pConstantExpression;
    String * /*@auto*/ Text;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    TScannerItemList ClueList4;
    TScannerItemList ClueList5;

} TStaticAssertDeclaration;

TStaticAssertDeclaration * TStaticAssertDeclaration_Create();
void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration * p);


typedef struct
{
     
    EType Type /*@=TEofDeclaration_ID*/;
    TScannerItemList ClueList0;
} TEofDeclaration;

TEofDeclaration * TEofDeclaration_Create();
void TEofDeclaration_Delete(TEofDeclaration * p);

struct TStatement;
typedef struct TStatement TStatement;

struct TGroupDeclaration;
typedef struct TGroupDeclaration TGroupDeclaration;

struct /*@<TStaticAssertDeclaration |
  TDeclaration |
  TGroupDeclaration |
  TEofDeclaration>*/ TAnyDeclaration
{
    EType Type;
};

typedef struct TAnyDeclaration TAnyDeclaration;
void TAnyDeclaration_Delete(TAnyDeclaration * p);


struct TBlockItem;
typedef struct TBlockItem TBlockItem;

typedef struct {
     
    TBlockItem * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
} TBlockItemList;

void TBlockItemList_Destroy(TBlockItemList * p);
void TBlockItemList_Init(TBlockItemList * p);
void TBlockItemList_PushBack(TBlockItemList * p, TBlockItem * pItem);


typedef struct
{
    EType Type  /*@=TCompoundStatement_ID*/;
    TBlockItemList BlockItemList;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;

} TCompoundStatement;

TCompoundStatement * TCompoundStatement_Create();
void TCompoundStatement_Delete(TCompoundStatement * p);


typedef struct TTypeQualifier
{
     

     

    EType Type /*@=TTypeQualifier_ID*/;
    String * /*@auto*/ SizeIdentifier;
    Tokens Token;
    TScannerItemList ClueList0;

} TTypeQualifier;

void TTypeQualifier_Copy(TTypeQualifier * dest, TTypeQualifier * src);
bool TTypeQualifier_Compare(TTypeQualifier * p1, TTypeQualifier * p2);

typedef struct {
     

    TTypeQualifier * /*@auto*/ Data[4];
    int Size;

} TTypeQualifierList;

void TTypeQualifierList_Init(TTypeQualifierList * p);
void TTypeQualifierList_Destroy(TTypeQualifierList * p);
void TTypeQualifierList_PushBack(TTypeQualifierList * p, TTypeQualifier * pItem);
void TTypeQualifierList_Copy(TTypeQualifierList * dest, TTypeQualifierList * src);

TTypeQualifier * TTypeQualifier_Create(void);
void TTypeQualifier_Delete(TTypeQualifier * p);


typedef struct
{
    EType Type /*@=TExpressionStatement_ID*/;
    TExpression * /*@auto*/    pExpression;
    TScannerItemList ClueList0;
} TExpressionStatement;

TExpressionStatement * TExpressionStatement_Create(void);
void TExpressionStatement_Delete(TExpressionStatement * p);

typedef struct
{
    EType Type /*@=TJumpStatement_ID*/;
    Tokens token;
    String * /*@auto*/ Identifier;
    TExpression * /*@auto*/   pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TJumpStatement;

TJumpStatement * TJumpStatement_Create(void);
void TJumpStatement_Delete(TJumpStatement * p);


typedef struct
{
    EType Type  /*@=TAsmStatement_ID*/;
    TScannerItemList ClueList;
} TAsmStatement;

TAsmStatement * TAsmStatement_Create(void);
void TAsmStatement_Delete(TAsmStatement * p);

typedef struct
{
    EType Type  /*@=TForStatement_ID*/;
    TAnyDeclaration * /*@auto*/   pInitDeclarationOpt;
    TExpression * /*@auto*/   pExpression1;
    TExpression * /*@auto*/  pExpression2;
    TExpression * /*@auto*/   pExpression3;
    TStatement * /*@auto*/   pStatement;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    TScannerItemList ClueList4;
} TForStatement;

TForStatement * TForStatement_Create(void);
void TForStatement_Delete(TForStatement * p);

typedef struct
{
    EType Type  /*@=TWhileStatement_ID*/;
    TExpression * /*@auto*/   pExpression;
    TStatement * /*@auto*/   pStatement;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TWhileStatement;

TWhileStatement * TWhileStatement_Create(void);
void TWhileStatement_Delete(TWhileStatement * p);

typedef struct
{
    EType Type  /*@=TDoStatement_ID*/;
    TExpression * /*@auto*/    pExpression;
    TStatement * /*@auto*/    pStatement;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
    TScannerItemList ClueList3; 
    TScannerItemList ClueList4; 

} TDoStatement;

TDoStatement * TDoStatement_Create(void);
void TDoStatement_Delete(TDoStatement * p);

typedef struct
{
    EType Type  /*@=TLabeledStatement_ID*/;

    TStatement * /*@auto*/   pStatementOpt;
    TExpression * /*@auto*/   pExpression;
    String * /*@auto*/ Identifier;
    Tokens token;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TLabeledStatement;

TLabeledStatement * TLabeledStatement_Create(void);
void TLabeledStatement_Delete(TLabeledStatement * p);


typedef struct
{
    EType Type  /*@=TSwitchStatement_ID*/;
    TExpression * /*@auto*/   pConditionExpression;
    TStatement * /*@auto*/    pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TSwitchStatement;

TSwitchStatement * TSwitchStatement_Create(void);
void TSwitchStatement_Delete(TSwitchStatement * p);


typedef struct
{
    EType Type  /*@=TIfStatement_ID*/;
    TExpression * /*@auto*/    pConditionExpression;
    TStatement * /*@auto*/   pStatement;
    TStatement * /*@auto*/   pElseStatement;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
    TScannerItemList ClueList3; 
} TIfStatement;

TIfStatement * TIfStatement_Create(void);
void TIfStatement_Delete(TIfStatement * p);


struct /*@<TCompoundStatement |
  TExpressionStatement |
  TLabeledStatement |
  TJumpStatement |
  TIfStatement |
  TDoStatement |
  TForStatement |
  TAsmStatement |
  TWhileStatement |
  TSwitchStatement>*/ TStatement
{
    EType Type;
};

typedef struct TStatement TStatement;
void TStatement_Delete(TStatement * p);

CAST(TStatement, TCompoundStatement)
CAST(TStatement, TExpressionStatement)
CAST(TStatement, TLabeledStatement)
CAST(TStatement, TJumpStatement)
CAST(TStatement, TIfStatement)
CAST(TStatement, TDoStatement)
CAST(TStatement, TForStatement)
CAST(TStatement, TAsmStatement)
CAST(TStatement, TWhileStatement)
CAST(TStatement, TSwitchStatement)


struct TDeclaration;
typedef struct TDeclaration TDeclaration;

 
struct /*@<TDeclaration | TStatement>*/ TBlockItem
{
    EType Type;
};

typedef struct TBlockItem TBlockItem;
void TBlockItem_Delete(TBlockItem * p);

CASTSAME(TBlockItem, TStatement)
CAST(TBlockItem, TCompoundStatement)
CAST(TBlockItem, TExpressionStatement)
CAST(TBlockItem, TLabeledStatement)
CAST(TBlockItem, TJumpStatement)
CAST(TBlockItem, TIfStatement)
CAST(TBlockItem, TDoStatement)
CAST(TBlockItem, TForStatement)
CAST(TBlockItem, TAsmStatement)

CAST(TBlockItem, TWhileStatement)
CAST(TBlockItem, TSwitchStatement)

CAST(TBlockItem, TDeclaration)
CAST(TBlockItem, TStaticAssertDeclaration)
CASTSAME(TBlockItem, TAnyDeclaration)

typedef struct TPointer
{
     
    TTypeQualifierList Qualifier;
    struct TPointer * pNext;
    TScannerItemList ClueList0;
} TPointer;

TPointer * TPointer_Create(void);
void TPointer_Delete(TPointer * p);
void TPointer_Copy(TPointer * dest, TPointer * src);


typedef struct TPointerList
{
     
    TPointer * pHead, * pTail;
} TPointerList;

void TPointerList_PushBack(TPointerList * pList, TPointer * pItem);


void TPointerList_Destroy(TPointerList * p);
bool TPointerList_IsPointer(TPointerList * pPointerlist);

bool TPointerList_IsAutoPointer(TPointerList * pPointerlist);
bool TPointerList_IsAutoPointerToAutoPointer(TPointerList * pPointerlist);
bool TPointerList_IsPointerToObject(TPointerList * pPointerlist);
bool TPointerList_IsAutoPointerToObject(TPointerList * pPointerlist);
bool TPointerList_IsAutoPointerToPointer(TPointerList * pPointerlist);
bool TPointerList_IsPointer(TPointerList * pPointerlist);
void TPointerList_Swap(TPointerList * a, TPointerList * b);
bool TPointerList_IsAutoPointerSizeToObject(TPointerList * pPointerlist);
bool TPointerList_IsPointerN(TPointerList * pPointerlist, int n);
const char * TPointerList_GetSize(TPointerList * pPointerlist);

typedef struct
{
     
    EType Type  /*@=TFunctionSpecifier_ID*/;
    Tokens Token;
    TScannerItemList ClueList0;
} TFunctionSpecifier;


TFunctionSpecifier * TFunctionSpecifier_Create(void);
void TFunctionSpecifier_Delete(TFunctionSpecifier * p);
bool TFunctionSpecifier_Compare(TFunctionSpecifier * p1, TFunctionSpecifier * p2);

typedef struct
{
     
    EType Type  /*@=TStorageSpecifier_ID*/;
    Tokens Token;
    TScannerItemList ClueList0;
} TStorageSpecifier;

TStorageSpecifier * TStorageSpecifier_Create(void);
void TStorageSpecifier_Delete(TStorageSpecifier * p);
bool TStorageSpecifier_Compare(TStorageSpecifier *p1, TStorageSpecifier *p2);

typedef struct
{
     
    EType Type  /*@=TAlignmentSpecifier_ID*/;
    String * /*@auto*/ TypeName;
} TAlignmentSpecifier;

TAlignmentSpecifier * TAlignmentSpecifier_Create(void);
void TAlignmentSpecifier_Delete(TAlignmentSpecifier * p);


typedef struct TEnumerator
{
     
    struct TEnumerator * pNext;
    String * /*@auto*/ Name;
    TExpression * /*@auto*/   pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
    bool bHasComma;
} TEnumerator;

TEnumerator * TEnumerator_Create(void);
void TEnumerator_Delete(TEnumerator * p);


typedef struct
{
     
    TEnumerator * pHead, * pTail;
} TEnumeratorList;
void TEnumeratorList_Destroy(TEnumeratorList * p);
void TEnumeratorList_Init(TEnumeratorList * p);

typedef struct TEnumSpecifier
{
     

    EType Type  /*@=TEnumSpecifier_ID*/;
    String * /*@auto*/ Name;
    TEnumeratorList EnumeratorList;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
} TEnumSpecifier;

TEnumSpecifier * TEnumSpecifier_Create(void);
void TEnumSpecifier_Delete(TEnumSpecifier * p);
bool TEnumSpecifier_CompareTagName(TEnumSpecifier * p1, TEnumSpecifier * p2);

typedef struct TSingleTypeSpecifier
{
     
    EType Type  /*@=TSingleTypeSpecifier_ID*/;
    Tokens Token2;
    String * /*@auto*/ TypedefName;
    TScannerItemList ClueList0;
} TSingleTypeSpecifier;

TSingleTypeSpecifier * TSingleTypeSpecifier_Create(void);
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier * p);

const char * TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier * p);
bool TSingleTypeSpecifier_Compare(TSingleTypeSpecifier * p1, TSingleTypeSpecifier * p2);

struct TTypeSpecifier;
typedef struct TTypeSpecifier TTypeSpecifier;


 

struct /*@<TStorageSpecifier |
  TTypeSpecifier |
  TTypeQualifier |
  TFunctionSpecifier |
  TAlignmentSpecifier>*/ TDeclarationSpecifier
{
    EType Type;
};

typedef struct TDeclarationSpecifier TDeclarationSpecifier;

CAST(TDeclarationSpecifier, TStorageSpecifier)
CAST(TDeclarationSpecifier, TFunctionSpecifier)
CAST(TDeclarationSpecifier, TAlignmentSpecifier)
CAST(TDeclarationSpecifier, TSingleTypeSpecifier)
CAST(TDeclarationSpecifier, TEnumSpecifier)

 
struct /*@<TTypeSpecifier | TTypeQualifier>*/ TSpecifierQualifier
{
    EType Type;
};


 
typedef struct TSpecifierQualifier TSpecifierQualifier;
void TSpecifierQualifier_Delete(TSpecifierQualifier * p);

CAST(TSpecifierQualifier, TStorageSpecifier)
CAST(TSpecifierQualifier, TAlignmentSpecifier)
CAST(TSpecifierQualifier, TSingleTypeSpecifier)

CAST(TSpecifierQualifier, TTypeQualifier)
CAST(TSpecifierQualifier, TEnumSpecifier)


typedef struct {
     
    TSpecifierQualifier * /*@auto*/ * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
} TSpecifierQualifierList;

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList * pDeclarationSpecifiers);
void TSpecifierQualifierList_PushBack(TSpecifierQualifierList * p, TSpecifierQualifier * pItem);

const char * TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList * p);
TDeclarationSpecifier * TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList * p);
bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList * p);
bool TSpecifierQualifierList_Compare(TSpecifierQualifierList * p1, TSpecifierQualifierList * p2);

bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList * p, Tokens token, const char * lexeme);
bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList * p);
bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList * p);
bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList * p);
bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList * p);


typedef struct TDeclarationSpecifiers {
     
    TDeclarationSpecifier * /*@auto*/ * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
} TDeclarationSpecifiers;

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers * pDeclarationSpecifiers);
void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers * pDeclarationSpecifiers);
void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers * p, TDeclarationSpecifier * pItem);
TDeclarationSpecifier* TDeclarationSpecifiers_GetMainSpecifier(TDeclarationSpecifiers* p, enum EType type);


const char * TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers * pDeclarationSpecifiers);
bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers * pDeclarationSpecifiers, Tokens token, const char * lexeme);


typedef struct TStructUnionSpecifier TStructUnionSpecifier;

TStructUnionSpecifier* TDeclarationSpecifiers_GetCompleteStructUnionSpecifier(struct SymbolMap* pSymbolMap,
    TDeclarationSpecifiers* pDeclarationSpecifiers);

struct TParameter;
typedef struct TParameter TParameter;

typedef struct
{
     

    TParameter * pHead, * pTail;
} TParameterList;

void TParameterList_Destroy(TParameterList * p);
void TParameterList_Init(TParameterList * p);
const char * TParameter_GetName(TParameter * p);
bool TParameter_IsDirectPointer(TParameter * p);

typedef struct TParameterTypeList
{
     
    TParameterList ParameterList;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    bool bVariadicArgs;
} TParameterTypeList;

void TParameterTypeList_Init(TParameterTypeList * p);
void TParameterTypeList_Destroy(TParameterTypeList * p);
TParameterTypeList * TParameterTypeList_Create();
void TParameterTypeList_Delete(TParameterTypeList * p);

const char * TParameterTypeList_GetFirstParameterName(TParameterTypeList * p);
const char * TParameterTypeList_GetSecondParameterName(TParameterTypeList * p);
TParameter * TParameterTypeList_FindParameterByName(TParameterTypeList * p, const char * name);
TParameter * TParameterTypeList_GetParameterByIndex(TParameterTypeList * p, int index);
void TParameterTypeList_GetArgsString(TParameterTypeList * p, StrBuilder * sb);
bool TParameterTypeList_HasNamedArgs(TParameterTypeList * p);

typedef struct TDesignator
{
     
    String * /*@auto*/ Name;
    TExpression * /*@auto*/  pExpression;
    struct TDesignator * pNext;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
} TDesignator;


TDesignator * TDesignator_Create(void);
void TDesignator_Delete(TDesignator * p);


typedef struct
{
     
    TDesignator * /*@auto*/ pHead, * pTail;
} TDesignatorList;
void TDesignatorList_Destroy(TDesignatorList * p);
void TDesignatorList_Init(TDesignatorList * p);
void TDesignatorList_PushBack(TDesignatorList * p, TDesignator * pItem);

typedef struct TDesignation
{
     
    TDesignatorList DesignatorList;
    TScannerItemList ClueList0;
} TDesignation;

TDesignation * TDesignation_Create(void);
void TDesignation_Delete(TDesignation * p);

struct TInitializer;
typedef struct TInitializer TInitializer;
void TInitializer_Delete(TInitializer * p);

typedef struct TInitializerListItem
{
     
    TDesignatorList  DesignatorList;
    TInitializer * /*@auto*/  pInitializer;
    struct TInitializerListItem * pNext;
    TScannerItemList ClueList;
    bool bDefault;
} TInitializerListItem;

TInitializerListItem * TInitializerListItem_Create();
void TInitializerListItem_Delete(TInitializerListItem * p);



typedef struct TInitializerList
{
     

    TInitializerListItem * /*@auto*/ pHead, * pTail;
} TInitializerList;

void TInitializerList_Init(TInitializerList * p);
void TInitializerList_Destroy(TInitializerList * p);


typedef struct
{
     
     

    EType Type  /*@=TInitializerListType_ID*/;
    TInitializerList InitializerList;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    bool bDefault;
} TInitializerListType;

TInitializerListType * TInitializerListType_Create(void);
void TInitializerListType_Delete(TInitializerListType * p);



struct /*@<TInitializerListType | TExpression>*/ TInitializer
{
     
    EType Type;
};
typedef struct TInitializer TInitializer;

CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;
typedef struct TDirectDeclarator TDirectDeclarator;

typedef struct TDeclarator
{
     

     

    TPointerList PointerList;
    TDirectDeclarator * /*@auto*/  pDirectDeclarator;
    TScannerItemList ClueList;
} TDeclarator;

TDeclarator * TDeclarator_Create();
void TDeclarator_Delete(TDeclarator * p);
void TDeclarator_Init(TDeclarator * p);
void TDeclarator_Destroy(TDeclarator * p);
const char * TDeclarator_GetName(TDeclarator * p);
void TDeclarator_Swap(TDeclarator * a, TDeclarator * b);

typedef enum TDirectDeclaratorType
{
    TDirectDeclaratorTypeNone,
    TDirectDeclaratorTypeIdentifier,
    TDirectDeclaratorTypeDeclarator,
    TDirectDeclaratorTypeFunction,
    TDirectDeclaratorTypeArray,

}TDirectDeclaratorType;

typedef struct TDirectDeclarator
{
     

    String * /*@auto*/ Identifier;
    TDeclarator * /*@auto*/ pDeclarator;
    struct TDirectDeclarator * /*@auto*/  pDirectDeclarator;
    TPosition Position;
    TParameterTypeList  Parameters;
    TExpression * /*@auto*/  pExpression;
    TDirectDeclaratorType DeclaratorType; 
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
} TDirectDeclarator;


TDirectDeclarator * TDirectDeclarator_Create();
void TDirectDeclarator_Delete(TDirectDeclarator * p);

typedef struct TInitDeclarator
{
     
    TDeclarator * /*@auto*/  pDeclarator;
    TInitializer * /*@auto*/   pInitializer;
    struct TInitDeclarator * pNext;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; 
} TInitDeclarator;


TInitDeclarator * TInitDeclarator_Create();
void TInitDeclarator_Delete(TInitDeclarator * p);

typedef TInitDeclarator TStructDeclarator;


typedef struct TInitDeclaratorList
{
     
    TInitDeclarator * pHead, * pTail;
} TInitDeclaratorList;

void TInitDeclaratorList_Destroy(TInitDeclaratorList * p);
void TInitDeclaratorList_Init(TInitDeclaratorList * p);
const char * TDeclarator_GetName(TDeclarator * p);
const char * TInitDeclarator_FindName(TInitDeclarator * p);


typedef struct TStructDeclaratorList
{
     
    TInitDeclarator * /*@auto*/ pHead, * pTail;
} TStructDeclaratorList;


void TStructDeclaratorList_Destroy(TStructDeclaratorList * p);
void TStructDeclaratorList_Init(TStructDeclaratorList * p);
void TStructDeclaratorList_Add(TStructDeclaratorList * p, TInitDeclarator * pItem);


typedef struct TStructDeclaration
{
     

    EType Type  /*@=TStructDeclaration_ID*/;

    TSpecifierQualifierList SpecifierQualifierList;
    TStructDeclaratorList DeclaratorList;
    TScannerItemList ClueList1;
} TStructDeclaration;


TStructDeclaration * TStructDeclaration_Create();
void TStructDeclaration_Delete(TStructDeclaration * p);


 
struct /*@<TStructDeclaration | TStaticAssertDeclaration>*/ TAnyStructDeclaration
{
    EType Type;
};

typedef struct TAnyStructDeclaration TAnyStructDeclaration;
void TAnyStructDeclaration_Delete(TAnyStructDeclaration * p);

CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)
CAST(TAnyStructDeclaration, TEofDeclaration)

typedef struct
{
    TAnyStructDeclaration * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
} TStructDeclarationList;

void TStructDeclarationList_Destroy(TStructDeclarationList * p);
void TStructDeclarationList_Init(TStructDeclarationList * p);
void TStructDeclarationList_PushBack(TStructDeclarationList * p, TAnyStructDeclaration * pItem);


typedef struct TUnionSetItem
{
    struct TUnionSetItem * pNext;
    Tokens Token;
    Tokens TokenFollow;
    String * /*@auto*/ Name;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TUnionSetItem;

TUnionSetItem * TUnionSetItem_Create();
void TUnionSetItem_Delete(TUnionSetItem *);

typedef struct TUnionSet
{
    TUnionSetItem * pHead, * pTail;

    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    

} TUnionSet;
void TUnionSet_Init(TUnionSet * p);
void TUnionSet_Destroy(TUnionSet * p);
void TUnionSet_PushBack(TUnionSet * p, TUnionSetItem * pItem);

typedef struct TStructUnionSpecifier
{
     

     

    EType Type  /*@=TStructUnionSpecifier_ID*/;
    TStructDeclarationList StructDeclarationList;
    String * /*@auto*/ TagName;

    Tokens Token;


    TUnionSet UnionSet;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
    TScannerItemList ClueList3; 


} TStructUnionSpecifier;

TStructUnionSpecifier * TStructUnionSpecifier_Create();
void TStructUnionSpecifier_Delete(TStructUnionSpecifier * p);
void TStructUnionSpecifier_SetFunctionImplicitTag(TStructUnionSpecifier* p,
    const char* funcName,
    TDeclaration* pFuncDeclaration);


struct TAtomicTypeSpecifier;
typedef struct TAtomicTypeSpecifier TAtomicTypeSpecifier;


struct /*@<TSingleTypeSpecifier |
  TAtomicTypeSpecifier |
  TEnumSpecifier |
  TStructUnionSpecifier>*/ TTypeSpecifier
{
    EType Type;
};

bool TTypeSpecifier_Compare(TTypeSpecifier * p1, TTypeSpecifier * p2);

typedef struct TTypeSpecifier TTypeSpecifier;

CAST(TTypeSpecifier, TSingleTypeSpecifier)
CAST(TTypeSpecifier, TEnumSpecifier)
CAST(TTypeSpecifier, TStructUnionSpecifier)
CAST(TDeclarationSpecifier, TStructUnionSpecifier)
CAST(TSpecifierQualifier, TStructUnionSpecifier)
CAST(TTypeSpecifier, TAtomicTypeSpecifier)

#define FUNCTION_TAG_DESTROY "destroy"
#define FUNCTION_TAG_INIT "init"
#define FUNCTION_TAG_DELETE "delete"
#define FUNCTION_TAG_CREATE "create"


typedef struct TDeclaration
{
     

     

    EType Type  /*@=TDeclaration_ID*/;
    TDeclarationSpecifiers Specifiers;
    TInitDeclaratorList InitDeclaratorList;

    
    TCompoundStatement * /*@auto*/  pCompoundStatementOpt;

    int FileIndex;
    int Line;

    TScannerItemList ClueList0; 
    TScannerItemList ClueList00; 
    TScannerItemList ClueList001; 

    bool bDefault;
    String* /*@auto*/ FunctionTag;
    bool bAutoTag;
    TScannerItemList ClueList1;


} TDeclaration;


TDeclaration * TDeclaration_Create();
void TDeclaration_Delete(TDeclaration * p);

TDeclarationSpecifiers * TDeclaration_GetArgTypeSpecifier(TDeclaration * p, int index);

const char * TDeclaration_GetArgName(TDeclaration * p, int index);
int TDeclaration_GetNumberFuncArgs(TDeclaration * p);

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration * p);

TCompoundStatement * TDeclaration_Is_FunctionDefinition(TDeclaration * p);

TDeclarator * TDeclaration_FindDeclarator(TDeclaration * p, const char * name);
const char * TDeclaration_GetFunctionName(TDeclaration * p);
const char* TDeclaration_FindFunctionTagName(TDeclaration* p, struct SymbolMap* pMap);


CAST(TAnyDeclaration, TStaticAssertDeclaration)
CAST(TAnyDeclaration, TDeclaration)
CAST(TAnyDeclaration, TEofDeclaration)

bool TAnyDeclaration_IsTypedef(TAnyDeclaration * pDeclaration);
bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration * pDeclaration);
int TAnyDeclaration_GetFileIndex(TAnyDeclaration * pDeclaration);


typedef struct TParameter
{
     

    struct TParameter * pNext;
    TDeclarationSpecifiers Specifiers;
    TDeclarator Declarator;
    TScannerItemList ClueList0; 
    bool bHasComma;
} TParameter;

TParameter * TParameter_Create();
void TParameter_Delete(TParameter * p);

void TParameter_Swap(TParameter * a, TParameter * b);
const char * TParameter_GetName(TParameter * p);
const char * TParameter_GetTypedefName(TParameter * p);


typedef struct
{
    TAnyDeclaration * /*@auto*/ * /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
} TDeclarations;

void TDeclarations_Destroy(TDeclarations * p);
void TDeclarations_Init(TDeclarations * p);
void TDeclarations_PushBack(TDeclarations * p, TAnyDeclaration * pItem);

typedef struct TGroupDeclaration
{
     
    EType Type  /*@=TGroupDeclaration_ID*/;
    TDeclarations Declarations;
    String * /*@auto*/ Identifier;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TGroupDeclaration;

TGroupDeclaration * TGroupDeclaration_Create();
void TGroupDeclaration_Delete(TGroupDeclaration * p);


typedef struct
{
    
    TDeclarations Declarations;

    
    TFileArray Files2;

    
    
    struct SymbolMap GlobalScope;


    
    struct MacroMap Defines;

    StrBuilder sbPreDeclaration;

} TProgram;


void TProgram_Init(TProgram * p);
void TProgram_Destroy(TProgram * p);
TDeclaration * TProgram_GetFinalTypeDeclaration(TProgram * p, const char * typeName);
TDeclaration * TProgram_FindDeclaration(TProgram * p, const char * name);



typedef struct TTypeName
{
     
    EType Type  /*@=TypeName_ID*/;
    TSpecifierQualifierList SpecifierQualifierList;
    TDeclarator Declarator;
} TTypeName;

TTypeName * TTypeName_Create();
void TTypeName_Destroy(TTypeName * p);
void TTypeName_Delete(TTypeName * p);
void TTypeName_Init(TTypeName * p);

typedef struct TAtomicTypeSpecifier
{
     
    EType Type  /*@=TAtomicTypeSpecifier_ID*/;
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TAtomicTypeSpecifier;


TAtomicTypeSpecifier * TAtomicTypeSpecifier_Create();
void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier * p);
bool TAtomicTypeSpecifier_Compare(TAtomicTypeSpecifier *p1, TAtomicTypeSpecifier * p2);


bool EvaluateConstantExpression(TExpression * p, int * pResult);

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration * p);

TDeclaration * TProgram_FindFunctionDeclaration(TProgram * p, const char * name);

bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers * pDeclarationSpecifiers);



typedef struct
{
     

    EType Type /*@=TPrimaryExpressionValue_ID*/;
    Tokens token;
    String * /*@auto*/ lexeme;
    TExpression * /*@auto*/   pExpressionOpt; 
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TPrimaryExpressionValue;

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue * p);
void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue * p);
TPrimaryExpressionValue * TPrimaryExpressionValue_Create();
void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue * p);

typedef struct TPrimaryExpressionLiteralItem
{
    struct TPrimaryExpressionLiteralItem * pNext;
    String * /*@auto*/ lexeme;
    TScannerItemList ClueList0;
} TPrimaryExpressionLiteralItem;

TPrimaryExpressionLiteralItem * TPrimaryExpressionLiteralItem_Create();
void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem * p);

typedef struct
{
    TPrimaryExpressionLiteralItem * pHead, * pTail;
} TPrimaryExpressionLiteralItemList;

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList * p);
void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList * p);
void TPrimaryExpressionLiteralItemList_Add(TPrimaryExpressionLiteralItemList * p, TPrimaryExpressionLiteralItem * pItem);


typedef struct
{
    EType Type /*@=TPrimaryExpressionLiteral_ID*/;
    TPrimaryExpressionLiteralItemList List;
} TPrimaryExpressionLiteral;


TPrimaryExpressionLiteral * TPrimaryExpressionLiteral_Create();
void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral * p);


typedef struct
{
    EType Type /*@=TBinaryExpression_ID*/;
    Tokens token;
    TExpression * /*@auto*/   pExpressionLeft;
    TExpression * /*@auto*/    pExpressionRight;
    TPosition Position;

    TScannerItemList ClueList0;

} TBinaryExpression;

TBinaryExpression * TBinaryExpression_Create(void);
void TBinaryExpression_Delete(TBinaryExpression * p);

typedef struct
{
    EType Type /*@=TTernaryExpression_ID*/;
    Tokens token;
    TExpression * /*@auto*/   pExpressionLeft;
    TExpression * /*@auto*/    pExpressionMiddle;
    TExpression * /*@auto*/    pExpressionRight;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TTernaryExpression;

TTernaryExpression * TTernaryExpression_Create(void);
void TTernaryExpression_Delete(TTernaryExpression * p);


struct TTypeName;
typedef struct TTypeName TTypeName;

typedef struct TPostfixExpressionCore
{
    EType Type  /*@=TPostfixExpressionCore_ID*/;
    Tokens token;
    String * /*@auto*/ lexeme;
    TExpression * /*@auto*/   pExpressionLeft;
    TExpression * /*@auto*/   pExpressionRight;

    struct TPostfixExpressionCore * /*@auto*/  pNext;
    TInitializerList InitializerList;
    String * /*@auto*/ Identifier;
    TTypeName * /*@auto*/  pTypeName;  

    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    TScannerItemList ClueList4;

} TPostfixExpressionCore;

TPostfixExpressionCore * TPostfixExpressionCore_Create();
void TPostfixExpressionCore_Delete(TPostfixExpressionCore * p);


typedef struct
{
    EType Type  /*@=TCastExpressionType_ID*/;
    TExpression * /*@auto*/    pExpression;
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TCastExpressionType;

TCastExpressionType * TCastExpressionType_Create();
void TCastExpressionType_Delete(TCastExpressionType * p);


typedef struct
{
    EType Type  /*@=TUnaryExpressionOperator_ID*/;
    Tokens token;
    TExpression * /*@auto*/   pExpressionRight;
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
} TUnaryExpressionOperator;


TUnaryExpressionOperator * TUnaryExpressionOperator_Create();
void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator * p);

struct /*@<TPrimaryExpressionLiteral |
  TPrimaryExpressionValue |
  TBinaryExpression |
  TUnaryExpressionOperator |
  TPostfixExpressionCore |
  TPostfixExpressionCore |
  TCastExpressionType |
  TTernaryExpression |
  TPrimaryExpressionLambda>*/ TExpression
{
    EType Type;
};

typedef struct TExpression TExpression;
void TExpression_Delete(TExpression * p);


CAST(TExpression, TPrimaryExpressionLiteral)
CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)


typedef struct TPrimaryExpressionLambda
{
    EType Type /*@=TPrimaryExpressionLambda_ID*/;

    TCompoundStatement * pCompoundStatement;
    TParameterTypeList * /*@auto*/ pParameterTypeListOpt;
    TScannerItemList ClueList0; 
    TScannerItemList ClueList1; 
    TScannerItemList ClueList2; 
    TScannerItemList ClueList3; 
} TPrimaryExpressionLambda;

TPrimaryExpressionLambda * TPrimaryExpressionLambda_Create();
void TPrimaryExpressionLambda_Delete(TPrimaryExpressionLambda * p);




void TProgram_PrintAstToFile(TProgram* pProgram,
                          const char* fileName,
                         const char* inputFileName);



void PrintLiteralString(FILE* fp, const char* psz);

















struct IntegerStack
{
    int * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};


#define INTEGER_STACK_INIT {0,0,0}
typedef enum
{
    SearchNone,
    SearchAll,
    SearchDestroy,
    SearchInit,
    SearchDelete,
} Search;


typedef struct PrintCodeOptions
{
    struct Options Options;

    
    
    struct IntegerStack Stack;
    bool bInclude;
    int IdentationLevel;
    

} PrintCodeOptions;

#define CODE_PRINT_OPTIONS_INIT {OPTIONS_INIT, INTEGER_STACK_INIT, true, 0}

void PrintCodeOptions_Destroy(PrintCodeOptions * options);

void TProgram_PrintCodeToFile(TProgram * pProgram,
                              struct Options * options,
                              const char * fileName,
                              const char * userpath);

void TProgram_PrintCodeToString(TProgram * pProgram,
                                struct Options * options,
                                StrBuilder * output);


void TTypeName_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeName * p, StrBuilder * fp);



void TSpecifierQualifierList_CodePrint(TProgram * program,
                                       PrintCodeOptions * options,
                                       TSpecifierQualifierList * pDeclarationSpecifiers,

                                       StrBuilder * fp);


void TDeclarationSpecifiers_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarationSpecifiers * pDeclarationSpecifiers, StrBuilder * fp);

typedef enum
{
    ActionDestroy,
    ActionDestroyContent,
    ActionDelete,
    ActionCreate,
    ActionInit,
    ActionInitContent,
    ActionStaticInit,
} Action;

void InstanciateDestroy2(TProgram * program,
                         PrintCodeOptions * options,
                         TSpecifierQualifierList * pSpecifierQualifierList,
                         TDeclarator * pDeclatator,                        
                         TInitializer * pInitializer,
                         TParameterTypeList * pArgsOpt,
                         const char * pInitExpressionText, 
                         const char * pszAutoPointerLenExpressionOpt, 
                                                                     
                         const Action action,
                         Search search,
                         bool * pbHasInitializers,
                         StrBuilder * fp);


#define SYMBOL_BUCKETS_SIZE 1000

struct ParserOptions
{
    bool bNoImplicitTag;
};

typedef struct {
  
  bool bError;

  
  StrBuilder ErrorMessage;

  
  Scanner Scanner;

  TScannerItemList ClueList;

  struct SymbolMap GlobalScope;
  struct SymbolMap* pCurrentScope;
  
  int IncludeLevel;
  bool bPreprocessorEvalFlag;

  struct ParserOptions ParserOptions;
} Parser;

bool Parser_InitFile(Parser *parser, const char *fileName);

bool Parser_InitString(Parser *parser, const char *name, const char *Text);

void Parser_Destroy(Parser *parser);

bool Parser_HasError(Parser *pParser);

const char *GetCompletationMessage(Parser *parser);

bool GetAST(const char *filename, const char *configFileName,
            struct Options* options,
            TProgram *pProgram);

void ConstantExpression(Parser *ctx, TExpression **ppExpression);
Tokens Parser_MatchToken(Parser *parser, Tokens tk, TScannerItemList *listOpt);

Tokens Parser_LookAheadToken(Parser *parser);

bool GetASTFromString(const char*  sourceCode,
    struct Options * options,
  TProgram* pProgram);






#define CPRIME_MAX_DRIVE 255
#define CPRIME_MAX_DIR 255
#define CPRIME_MAX_FNAME 255
#define CPRIME_MAX_EXT 255
#define CPRIME_MAX_PATH 260

void GetFullPath(const char* fileName, char** out);
void GetFullPathS(const char* fileName, char* out);
void GetFullDir(const char* fileName, char** out);
bool IsFullPath(const char * path);
bool IsInPath(const char * filePath, const char* path);
bool FileExists(const char* fullPath);
void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext);
void MakePath(char* path, char* drv, char* dir, char* name, char* ext);
void MkDir(char* path);
void GetFullDirS(const char* fileName, char* out, int len);















void TProgram_PrintAstToXML(TProgram * pProgram,
                            const char * fileName,
                            const char * inputFileName);


#define CONFIG_FILE_NAME "config.txt"
#define EXECUTABLE_NAME "cpc"

int Compile(const char* configFileName,
    const char* inputFileName,
    const char* outputFileName,
    struct Options* options,
    bool bPrintASTFile)
{
    int bSuccess = 0;
    TProgram program;
    TProgram_Init(&program);

    clock_t tstart = clock();

    printf("Parsing...\n");
    if (GetAST(inputFileName, configFileName, options, &program))
    {
        bSuccess = 1;


        char drive[CPRIME_MAX_DRIVE];
        char dir[CPRIME_MAX_DIR];
        char fname[CPRIME_MAX_FNAME];
        char ext[CPRIME_MAX_EXT];
        SplitPath(inputFileName, drive, dir, fname, ext); 


        printf("Generating code for %s...\n", inputFileName);
        if (outputFileName[0] != '\0')
        {
            if (bPrintASTFile)
            {
                
                TProgram_PrintAstToXML(&program, outputFileName, inputFileName);
            }
            else
            {
                TProgram_PrintCodeToFile(&program, options, outputFileName, inputFileName);
            }
        }
        else
        {
            char outc[CPRIME_MAX_DRIVE + CPRIME_MAX_DIR + CPRIME_MAX_FNAME + CPRIME_MAX_EXT + 1];

            if (bPrintASTFile)
            {
                
                
                
                MakePath(outc, drive, dir, fname, ".xml");
                TProgram_PrintAstToXML(&program, outc, inputFileName);
            }
            else
            {
                
                MakePath(outc, drive, dir, fname, ext);
                TProgram_PrintCodeToFile(&program, options, outc, inputFileName);
            }
        }

        clock_t tend = clock();
        printf("Completed in %d second(s)\n", (int)((tend - tstart) / CLOCKS_PER_SEC));

    }
    TProgram_Destroy(&program);
    return bSuccess;
}

void PrintHelp()
{
    printf("Syntax: " EXECUTABLE_NAME " [options] [file ...]\n");
    printf("\n");
    printf("Examples: " EXECUTABLE_NAME " hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h hello.c -o hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h -P hello.c\n");
    printf("          " EXECUTABLE_NAME " -E hello.c\n");
    printf("          " EXECUTABLE_NAME " -P hello.c\n");
    printf("          " EXECUTABLE_NAME " -A hello.c\n");
    printf("\n");
    printf("PrintCodeOptions:\n");
    printf("-config FILE                          Configuration fp.\n");
    printf("-outDir                               Set the directory for output.\n");
    printf("-help                                 Print this message.\n");
    printf("-o FILE                               Sets ouput file name.\n");
    printf("-E                                    Preprocess to console.\n");
    printf("-P                                    Preprocess to file.\n");
    printf("-A                                    Output AST to file.\n");    
    printf("-cx                                   Generate C'.\n");
    printf("-ca                                   Generated C annotated\n");
    printf("-removeComments                       Remove comments from output\n");
    printf("-buildfile                            Compile all sources defined in inputfile\n");
    printf("                                      (not recursive)\n");
    printf("-build                                Build of all sources used by the input file\n");
    printf("                                      -build with -o generates amalgamation\n");
    printf("                                      -outDir can define build output\n");
    printf("-sources                              Prints all sources used\n");
    printf("-noImplicitTag                        Disable implicit function tags\n");

}



char * CompileText(int type, int bNoImplicitTag, char * input)
{
    char * output = NULL;

    struct Options options2 = OPTIONS_INIT;
    options2.Target = (enum CompilerTarget) type;
    options2.bNoImplicitTag = bNoImplicitTag;

    TProgram program;
    TProgram_Init(&program);
    if (GetASTFromString(input, &options2 ,&program))
    {
        

        StrBuilder sb = STRBUILDER_INIT;
        StrBuilder_Reserve(&sb, 500);
        if (options2.Target == CompilerTarget_Preprocessed)
        {
            PrintPreprocessedToString2(&sb, input, NULL);
        }
        else
        {
            TProgram_PrintCodeToString(&program, &options2, &sb);
        }
        output = sb.c_str;
    }
    return output;
}


int main(int argc, char * argv[])
{
    printf("\n");
    printf("C' Version " __DATE__ "\n");
    printf("https://github.com/thradams/CPrime\n\n");

#ifdef _DEBUG
    
#endif
    if (argc < 2)
    {
        PrintHelp();
        return 1;
    }

    char outputDirFullPath[CPRIME_MAX_PATH] = { 0 };

    char cxconfigFileFullPath[CPRIME_MAX_PATH];
    GetFullDirS(argv[0], cxconfigFileFullPath, CPRIME_MAX_PATH);
    strcat(cxconfigFileFullPath, CONFIG_FILE_NAME);


    if (FileExists(cxconfigFileFullPath))
    {
        printf("using config file %s\n", cxconfigFileFullPath);
        
    }
    else
    {
        cxconfigFileFullPath[0] = 0;
    }


    char outputFileFullPath[CPRIME_MAX_PATH] = { 0 };
    char inputFileFullPath[CPRIME_MAX_PATH] = { 0 };


    struct Options options = OPTIONS_INIT;
    options.Target = CompilerTarget_Annotated;

    bool bPrintPreprocessedToFile = false;
    bool bPrintPreprocessedToConsole = false;
    bool bPrintASTFile = false;
    bool bBuildFile = false;
    bool bBuild = false;
    bool bSources = false;

    clock_t tstart = clock();
    struct FileNodeList sources = { 0 };


    for (int i = 1; i < argc; i++)
    {
        const char * option = argv[i];
        if (strcmp(option, "-P") == 0)
        {
            options.Target = CompilerTarget_Preprocessed;
            bPrintPreprocessedToFile = true;
        }
        else if (strcmp(option, "-E") == 0)
        {
            options.Target = CompilerTarget_Preprocessed;
            bPrintPreprocessedToConsole = true;
        }
        else if (strcmp(option, "-r") == 0)
        {
            bPrintPreprocessedToConsole = true;
        }
        else if (strcmp(option, "-A") == 0)
        {
            bPrintASTFile = true;
        }
        else if (strcmp(option, "-a") == 0)
        {
            options.bAmalgamate = true;
        }
        else if (strcmp(option, "-help") == 0)
        {
            PrintHelp();
            return 0;
        }
        else if (strcmp(option, "-buildfile") == 0)
        {
            
            bBuildFile = true;
        }
        else if (strcmp(option, "-build") == 0)
        {
            bBuild = true;
        }
        else if (strcmp(option, "-sources") == 0)
        {
            bSources = true;
        }
        else if (strcmp(option, "-cx") == 0)
        {
            options.Target = CompilerTarget_CXX;
        }
        else if (strcmp(option, "-ca") == 0)
        {
            options.Target = CompilerTarget_Annotated;
        }
        else if (strcmp(option, "-removeComments") == 0)
        {
            options.bIncludeComments = false;
        }
        else if (strcmp(option, "-noImplicitTag") == 0)
        {
            options.bNoImplicitTag = true;
        }
        else if (strcmp(option, "-pr") == 0)
        {
            options.Target = CompilerTarget_Preprocessed;
        }
        else if (strcmp(option, "-outDir") == 0)
        {
            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], outputDirFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
                break;
            }
        }
        else if (strcmp(option, "-config") == 0)
        {

            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], cxconfigFileFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
                break;
            }
        }
        else if (strcmp(option, "-o") == 0)
        {
            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], outputFileFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
            }
        }
        else
        {
            GetFullPathS(argv[i], inputFileFullPath);
        }
    }


    int numberOfFiles = 1;

    
    if ((bBuildFile || bBuild)
        && outputFileFullPath[0] == '\0'
        )
    {
        printf("Output dir : %s\n", outputDirFullPath);
        if (bBuildFile)
        {
            GetSources(NULL, inputFileFullPath, false, &sources);
        }
        else
        {
            GetSources(cxconfigFileFullPath, inputFileFullPath, true, &sources);
        }
        if (sources.pHead != NULL)
        {
            char inputFileFullDir[CPRIME_MAX_PATH];
            GetFullDirS(inputFileFullPath, inputFileFullDir, CPRIME_MAX_PATH);
            const int inputFullDirLength = strlen(inputFileFullDir);

            
            if (outputDirFullPath[0] != '\0')
            {
                MkDir(outputDirFullPath);
            }

            char outputItemPath[2000] = { 0 };
            struct FileNode * pCurrent = sources.pHead;
            while (pCurrent != NULL)
            {
                outputItemPath[0] = 0;
                if (outputDirFullPath[0] != '\0')
                {
                    strcat(outputItemPath, outputDirFullPath);
                    strcat(outputItemPath, "\\");
                }
                strcat(outputItemPath, pCurrent->Key + inputFullDirLength);

                if (!Compile(cxconfigFileFullPath, pCurrent->Key, outputItemPath, &options, bPrintASTFile))
                {
                    numberOfFiles++;
                    break;
                }
                else
                {
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
    else if (bSources)
    {
        GetSources(cxconfigFileFullPath, inputFileFullPath, true, &sources);
        int fileCount = 0;
        struct FileNode * pCurrent = sources.pHead;
        while (pCurrent != NULL)
        {
            fileCount++;
            printf("%d: %s\n", fileCount, pCurrent->Key);
            pCurrent = pCurrent->pNext;
        }
    }
    else
    {
        if (bPrintPreprocessedToFile)
        {
            PrintPreprocessedToFile(inputFileFullPath, cxconfigFileFullPath);
        }
        else if (bPrintPreprocessedToConsole)
        {
            PrintPreprocessedToConsole(inputFileFullPath, cxconfigFileFullPath);
        }
        else
        {
            
            options.bAmalgamate = bBuild && outputFileFullPath[0] != '\0';

            Compile(cxconfigFileFullPath, inputFileFullPath, outputFileFullPath, &options, bPrintASTFile);
            numberOfFiles++;
        }
    }



    clock_t tend = clock();
    printf("Total %d files in = %d seconds\n", numberOfFiles, (int)((tend - tstart) / CLOCKS_PER_SEC));

    FileNodeList_Destroy(&sources);


    PrintMemory();
    return 0;
}







#include <assert.h>



bool TFunctionSpecifier_Print(TFunctionSpecifier * p, bool b, FILE * fp);
bool StorageSpecifier_Print(TStorageSpecifier * p, bool b, FILE * fp);
bool TTypeQualifierList_Print(TTypeQualifierList * p, bool b, FILE * fp);
bool TDeclarator_Print(TDeclarator * p, bool b, FILE * fp);
bool TAnyDeclaration_Print(TAnyDeclaration * pDeclaration, bool b, FILE * fp);
bool TTypeSpecifier_Print(TTypeSpecifier * p, bool b, FILE * fp);
bool TStructDeclaration_Print(TAnyStructDeclaration * p, bool b, FILE * fp);
bool TTypeQualifier_Print(TTypeQualifier * p, bool b, FILE * fp);
bool TDeclaration_Print(TDeclaration * p, bool b, FILE * fp);
bool TExpression_Print(TExpression * p, const char * name, bool b, FILE * fp);
bool TStatement_Print(TStatement * p, bool b, FILE * fp);
bool TBlockItem_Print(TBlockItem * p, bool b, FILE * fp);
bool TInitializer_Print(TInitializer * p, bool b, FILE * fp);
bool TPointer_Print(TPointer * pPointer, bool b, FILE * fp);
bool TParameter_Print(TParameter * p, bool b, FILE * fp);
bool TInitializerListItem_Print(TInitializerListItem * p, bool b, FILE * fp);

bool TCompoundStatement_Print(TCompoundStatement * p, bool b, FILE * fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"compound-statement\": [");

    for (int j = 0; j < p->BlockItemList.Size; j++)
    {
        TBlockItem * pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_Print(pBlockItem, j > 0, fp);
    }

    fprintf(fp, "]");
    return b;
}


bool TLabeledStatement_Print(TLabeledStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"labeled-statement\"");

    if (p->pStatementOpt)
    {
        fprintf(fp, ",");
        fprintf(fp, "\"statement\": {");
        b = TStatement_Print(p->pStatementOpt, false, fp);
        fprintf(fp, "}");
    }

    return b;
}

bool TForStatement_Print(TForStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"for-statement\"");
    fprintf(fp, ",");



    if (p->pInitDeclarationOpt != NULL)
    {
        fprintf(fp, "\"initdecl\":");
        b = TAnyDeclaration_Print(p->pInitDeclarationOpt, b, fp);
        
        b = true;
    }

    b = TExpression_Print(p->pExpression1, "expr1", true, fp);
    
    b = TExpression_Print(p->pExpression2, "expr2", b, fp);
    
    b = TExpression_Print(p->pExpression3, "expr3", b, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TWhileStatement_Print(TWhileStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"while-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TDoStatement_Print(TDoStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"do-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}

void PrintLiteralString(FILE * fp, const char * psz)
{
    fprintf(fp, "\"");

    while (*psz)
    {
        switch (*psz)
        {
            case '"':
                fprintf(fp, "\\\"");
                break;

            case '/':
                fprintf(fp, "\\/");
                break;

            case '\b':
                fprintf(fp, "\\b");
                break;

            case '\f':
                fprintf(fp, "\\f");
                break;

            case '\n':
                fprintf(fp, "\\n");
                break;

            case L'\r':
                fprintf(fp, "\\r");
                break;

            case L'\t':
                fprintf(fp, "\\t");
                break;

            case L'\\':
                fprintf(fp, "\\\\");
                break;

            default:
                fprintf(fp, "%c", *psz);
                break;
        }

        psz++;
    }

    fprintf(fp, "\"");
}

bool TExpressionStatement_Print(TExpressionStatement * p, bool b, FILE * fp)
{
    TExpression_Print(p->pExpression, "expression-statement", b, fp);
    
    
    
    return true;
}


bool TJumpStatement_Print(TJumpStatement * p, bool b, FILE * fp)
{
    fprintf(fp, "\"type\":\"jump-statement\"");
    
    
    b = TExpression_Print(p->pExpression, "statement", false, fp);
    
    return true;
}

bool TAsmStatement_Print(TAsmStatement * p, bool b, FILE * fp)
{
    fprintf(fp, "\"type\":\"asm-statement\"");
    return true;
}

bool TSwitchStatement_Print(TSwitchStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"switch-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pConditionExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pExpression, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TIfStatement_Print(TIfStatement * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "\"type\":\"if-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pConditionExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}

bool TStatement_Print(TStatement * p, bool b, FILE * fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TExpressionStatement_ID:
            b = TExpressionStatement_Print((TExpressionStatement *)p, b, fp);
            break;

        case TSwitchStatement_ID:
            b = TSwitchStatement_Print((TSwitchStatement *)p, b, fp);
            break;

        case TLabeledStatement_ID:
            b = TLabeledStatement_Print((TLabeledStatement *)p, b, fp);
            break;

        case TForStatement_ID:
            b = TForStatement_Print((TForStatement *)p, b, fp);
            break;

        case TJumpStatement_ID:
            b = TJumpStatement_Print((TJumpStatement *)p, b, fp);
            break;

        case TAsmStatement_ID:
            b = TAsmStatement_Print((TAsmStatement *)p, b, fp);
            break;

        case TCompoundStatement_ID:
            b = TCompoundStatement_Print((TCompoundStatement *)p, b, fp);
            break;

        case TIfStatement_ID:
            b = TIfStatement_Print((TIfStatement *)p, b, fp);
            break;

        case TDoStatement_ID:
            TDoStatement_Print((TDoStatement *)p, b, fp);
            break;

        default:
            
            break;
    }

    return b;
}

bool TBlockItem_Print(TBlockItem * p, bool b, FILE * fp)
{
    if (p == NULL)
    {
        
        return false;
    }

    if (b)
    {
        fprintf(fp, ",");
    }

    switch (p->Type)
    {
        case TStaticAssertDeclaration_ID:
            break;

        case TSwitchStatement_ID:
            fprintf(fp, "{");
            b = TSwitchStatement_Print((TSwitchStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TJumpStatement_ID:
            fprintf(fp, "{");
            b = TJumpStatement_Print((TJumpStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TForStatement_ID:
            fprintf(fp, "{");
            b = TForStatement_Print((TForStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TIfStatement_ID:
            fprintf(fp, "{");
            b = TIfStatement_Print((TIfStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TWhileStatement_ID:
            fprintf(fp, "{");
            b = TWhileStatement_Print((TWhileStatement *)p, b, fp);
            fprintf(fp, "}");
            break;

        case TDoStatement_ID:
            fprintf(fp, "{");
            b = TDoStatement_Print((TDoStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TDeclaration_ID:
            b = TDeclaration_Print((TDeclaration *)p, false, fp);
            break;

        case TLabeledStatement_ID:
            fprintf(fp, "{");
            b = TLabeledStatement_Print((TLabeledStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TCompoundStatement_ID:
            fprintf(fp, "{");
            b = TCompoundStatement_Print((TCompoundStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TExpressionStatement_ID:
            fprintf(fp, "{");
            b = TExpressionStatement_Print((TExpressionStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        case TAsmStatement_ID:
            fprintf(fp, "{");
            b = TAsmStatement_Print((TAsmStatement *)p, false, fp);
            fprintf(fp, "}");
            break;

        default:
            
            break;
    }

    return b;
}

bool TPostfixExpressionCore_Print(TPostfixExpressionCore * p, bool b, FILE * fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "\"postfix\":{");
    b = false;

    if (p->pExpressionLeft)
    {
        b = TExpression_Print(p->pExpressionLeft, "l", b, fp);
    }


    switch (p->token)
    {
        case TK_FULL_STOP:
        case TK_ARROW:
            if (b)
            {
                fprintf(fp, ",");
            }

            fprintf(fp, "\"identifier\":\"%s\"", p->Identifier);
            b = true;
            break;

        case TK_LEFT_SQUARE_BRACKET:
            b = TExpression_Print(p->pExpressionRight, "r", b, fp);
            break;

        case TK_LEFT_PARENTHESIS:
            b = TExpression_Print(p->pExpressionRight, "r", b, fp);
            break;

        case TK_PLUSPLUS:
        case TK_MINUSMINUS:
            break;
        default:
            
            break;
    }

    if (b)
    {
        fprintf(fp, ",");
    }


    fprintf(fp, "\"op\":\"%s\"", TokenToString(p->token));
    b = true;
    if (p->pNext)
    {
        if (b)
        {
            fprintf(fp, ",");
        }

        fprintf(fp, "\"next\":{");
        b = TPostfixExpressionCore_Print(p->pNext, false, fp);
        fprintf(fp, "}");
    }

    fprintf(fp, "}");
    b = true;
    return b;
}

bool TTypeName_Print(TTypeName * p, const char * name, bool b, FILE * fp)
{
    fprintf(fp, "\"type\":{");
    
    

    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "}");
    return b;
}

bool TExpression_Print(TExpression * p, const char * name, bool b, FILE * fp)
{
    if (p == NULL)
    {
        
        return b;
    }

    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "\"%s\":{", name);
    b = false;

    switch (p->Type)
    {
        CASE(TBinaryExpression) :
            b = TExpression_Print(((TBinaryExpression *)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((TBinaryExpression *)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"binary\":\"%s\"", TokenToString(((TBinaryExpression *)p)->token));

        
        break;

        CASE(TTernaryExpression) :
            b = TExpression_Print(((TTernaryExpression *)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression *)p)->pExpressionMiddle, "m-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression *)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"ternary\":\"%s\"", TokenToString(((TTernaryExpression *)p)->token));

        
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue * pPrimaryExpressionValue =
                (TPrimaryExpressionValue *)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                b = TExpression_Print(pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
            }
            else
            {

                fprintf(fp, "\"lexeme\":");
                PrintLiteralString(fp, pPrimaryExpressionValue->lexeme);
            }

            b = true;
        }
        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore * pPostfixExpressionCore =
                (TPostfixExpressionCore *)p;
            b = TPostfixExpressionCore_Print(pPostfixExpressionCore, b, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator * pTUnaryExpressionOperator =
                (TUnaryExpressionOperator *)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                


                
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
                {
                    TTypeName_Print(&pTUnaryExpressionOperator->TypeName, "", b, fp);
                    
                    
                    

                    
                    
                      
                    

                    
                    

                    
                }
                else
                {
                    b = TExpression_Print(pTUnaryExpressionOperator->pExpressionRight, "expr", b, fp);
                }
            }
            else
            {
                b = TExpression_Print(pTUnaryExpressionOperator->pExpressionRight, "expr", b, fp);
            }

            fprintf(fp, ",\"unary\":\"%s\"", TokenToString(((TBinaryExpression *)p)->token));
        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType *)p;

            b = TExpression_Print(pCastExpressionType->pExpression, "expr", b, fp);


            
            TTypeName_Print(&pCastExpressionType->TypeName, "cast", b, fp);
            
            

            
            
              
            

            
            

            

        }
        break;

        default:

            
            break;
    }

    fprintf(fp, "}");
    return b;
}


bool TEnumerator_Print(TEnumerator * pTEnumerator, bool b, FILE * fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"name\":\"%s\"", pTEnumerator->Name);
    
    if (pTEnumerator->pExpression)
    {
        TExpression_Print(pTEnumerator->pExpression, "expr", true, fp);
    }
    else
    {
        
    }
    fprintf(fp, "}");
    return true;
}

bool TEnumSpecifier_Print(TEnumSpecifier * p, bool b, FILE * fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"enum-specifier\": {");
    fprintf(fp, "\"name\":\"%s\",", p->Name);
    fprintf(fp, "\"enumerator-list\":[");

    
    int i = 0;
    ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
    {
        

        if (i > 0)
            fprintf(fp, ",");

        TEnumerator_Print(pTEnumerator, false, fp);
        i++;
    }

    fprintf(fp, "]");
    fprintf(fp, "}");
    return true;
}


bool TStructUnionSpecifier_Print(TStructUnionSpecifier * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "{");
    if (p->Token == TK_STRUCT)
        fprintf(fp, "\"type:\":\"struct-specifier\",");
    else if (p->Token == TK_UNION)
        fprintf(fp, "\"type:\":\"union-specifier\",");

    fprintf(fp, "\"name\":\"%s\",", p->TagName);

    fprintf(fp, "\"struct-declaration-list\":[");

    for (int i = 0; i < p->StructDeclarationList.Size; i++)
    {
        TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];

        if (i > 0)
            fprintf(fp, ",");

        b = TStructDeclaration_Print(pStructDeclaration, b, fp);
    }

    fprintf(fp, "]");
    fprintf(fp, "}");

    return true;
}

bool TSingleTypeSpecifier_Print(TSingleTypeSpecifier * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    b = true;
    fprintf(fp, "\"type\":\"type-specifier\",");
    fprintf(fp, "\"lexeme\":");

    fprintf(fp, "\"");

    if (p->Token2 == TK_IDENTIFIER)
    {
        fprintf(fp, "%s", p->TypedefName);
    }
    else
    {
        fprintf(fp, "%s", TokenToString(p->Token2));
    }

    fprintf(fp, "\"");

    fprintf(fp, "}");

    return b;
}

bool TTypeSpecifier_Print(TTypeSpecifier * p, bool b, FILE * fp)
{
    if (p == NULL)
    {
        
        if (b)
        {
            fprintf(fp, ",");
        }

        fprintf(fp, "\"type-specifier\":null");
        return true;
    }

    switch (p->Type)
    {
        case TStructUnionSpecifier_ID:
            
            b = TStructUnionSpecifier_Print((TStructUnionSpecifier *)p, b, fp);
            break;

        case TEnumSpecifier_ID:
            b = TEnumSpecifier_Print((TEnumSpecifier *)p, b, fp);
            break;

        case TSingleTypeSpecifier_ID:
            b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier *)p, b, fp);
            break;

        default:
            break;
    }

    return b;
}

bool TDesignator_Print(TDesignator * p, bool b, FILE * fp)
{
    if (b)
        fprintf(fp, ",");

    fprintf(fp, "{");

    
    if (p->Name)
    {
        
        fprintf(fp, "\"member-name\":\"%s\"", p->Name);
    }

    else
    {
        
        TExpression_Print(p->pExpression, "index", b, fp);
    }

    fprintf(fp, "}");
    return b;
}

bool TInitializerList_Print(TInitializerList * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(TInitializerListItem, pItem, p)

    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TInitializerListItem_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializer_Print(TInitializer * p, bool b, FILE * fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TPrimaryExpression_ID:
        case TUnaryExpressionOperator_ID:
        case TCastExpressionType_ID:
        case TPrimaryExpressionValue_ID:
        case TPostfixExpressionCore_ID:
        case TBinaryExpression_ID:
        case TTernaryExpression_ID:

            
            b = TExpression_Print((TExpression *)p, "initializer-expression", false, fp);
            
            break;

        case TInitializerListType_ID:
            fprintf(fp, "\"initializer\":");
            b = TInitializerList_Print(&((TInitializerListType *)p)->InitializerList, b, fp);
            break;

        default:
            
            break;
    }

    return b;
}


bool TPointerList_Print(TPointerList * p, bool b, FILE * fp)
{
    b = false;


    fprintf(fp, "[");
    int i = 0;
    
    ForEachListItem(TPointer, pItem, p)
    {
        if (i > 0)
            fprintf(fp, ",");

        
        b = TPointer_Print(pItem, b, fp);
        i++;
    }

    fprintf(fp, "]");
    b = true;


    return b;
}

bool TParameterList_Print(TParameterList * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(TParameter, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TParameter_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}
bool TParameterTypeList_Print(TParameterTypeList * p, bool b, FILE * fp)
{
    return TParameterList_Print(&p->ParameterList, b, fp);
}

bool TStructDeclarator_Print(TStructDeclarator * p, bool b, FILE * fp)
{

    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(p->pDeclarator, b, fp);

    if (p->pInitializer)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        
        TInitializer_Print(p->pInitializer, b, fp);

    }

    fprintf(fp, "}");
    return true;
}

bool TInitDeclarator_Print(TInitDeclarator * p, bool b, FILE * fp)
{

    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(p->pDeclarator, b, fp);

    if (p->pInitializer)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        
        TInitializer_Print(p->pInitializer, b, fp);

    }

    fprintf(fp, "}");
    return true;
}

bool TDirectDeclarator_Print(TDirectDeclarator * pDirectDeclarator,
                             bool b,
                             FILE * fp)
{
    fprintf(fp, "{");
    b = false;

    if (pDirectDeclarator->Identifier)
    {
        
        fprintf(fp, "\"identifier\":");
        fprintf(fp, "\"%s\"", pDirectDeclarator->Identifier);
        b = true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        
        fprintf(fp, "\"declarator\":");
        b = TDeclarator_Print(pDirectDeclarator->pDeclarator, b, fp);
    }

    if (pDirectDeclarator->pExpression)
    {
         
        b = TExpression_Print(pDirectDeclarator->pExpression, "assignment-expression", b, fp);
    }

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        
        fprintf(fp, ",");
        fprintf(fp, "\"parameter-type-list\":");
        TParameterTypeList_Print(&pDirectDeclarator->Parameters, b, fp);
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_Print(pDirectDeclarator->pDirectDeclarator, b, fp);
    }


    fprintf(fp, "}");
    return b;
}

bool TDeclarator_Print(TDeclarator * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"pointer\":");
    b = TPointerList_Print(&p->PointerList, b, fp);

    if (b)
    {
        fprintf(fp, ",");
    }

    if (p->pDirectDeclarator)
    {
        fprintf(fp, "\"direct-declarator\":");
        b = TDirectDeclarator_Print(p->pDirectDeclarator, b, fp);
    }

    fprintf(fp, "}");
    return true;
}

bool TStructDeclaratorList_Print(TStructDeclaratorList * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TStructDeclarator_Print(pItem, b, fp);

    }

    fprintf(fp, "]");
    return true;
}

bool TInitDeclaratorList_Print(TInitDeclaratorList * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            fprintf(fp, ",");

        b = TInitDeclarator_Print(pInitDeclarator, b, fp);
    }

    fprintf(fp, "]");
    return true;
}

bool SpecifierQualifier_Print(TSpecifierQualifier * pItem, bool b, FILE * fp)
{
    switch (pItem->Type)
    {
        CASE(TStorageSpecifier) :
            b = StorageSpecifier_Print((TStorageSpecifier *)pItem, b, fp);
        break;
        CASE(TTypeQualifier) :
            b = TTypeQualifier_Print((TTypeQualifier *)pItem, b, fp);
        break;
        CASE(TFunctionSpecifier) :
            b = TFunctionSpecifier_Print((TFunctionSpecifier *)pItem, b, fp);
        break;

        CASE(TSingleTypeSpecifier) :
            b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier *)pItem, b, fp);
        break;

        CASE(TStructUnionSpecifier) :
            b = TStructUnionSpecifier_Print((TStructUnionSpecifier *)pItem, b, fp);
        break;

        CASE(TEnumSpecifier) :
            b = TEnumSpecifier_Print((TEnumSpecifier *)pItem, b, fp);
        break;

        
        
        
        default:
            
            break;
    }
    return b;
}
bool SpecifierQualifierList_Print(TSpecifierQualifierList * p, bool b, FILE * fp)
{
    fprintf(fp, "\"specifier-qualifier-list\" : [");
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pItem = p->pData[i];
        if (b)
            fprintf(fp, ",");

        b = SpecifierQualifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    return b;
}

bool TStructDeclarationBase_Print(TStructDeclaration * p, bool b, FILE * fp)
{
    fprintf(fp, "{");

    b = SpecifierQualifierList_Print(&p->SpecifierQualifierList, false, fp);
    
    

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"declarators\":");
    b = TStructDeclaratorList_Print(&p->DeclaratorList, b, fp);
    fprintf(fp, "}");
    return true;
}

bool TStructDeclaration_Print(TAnyStructDeclaration * p, bool b, FILE * fp)
{
    switch (p->Type)
    {
        case TStructDeclaration_ID:
            b = TStructDeclarationBase_Print((TStructDeclaration *)p, b, fp);
            break;

        default:
            
            break;
    }

    return b;
}

bool StorageSpecifier_Print(TStorageSpecifier * p, bool b, FILE * fp)
{
    b = true;
    fprintf(fp, "{");
    fprintf(fp, "\"type\":\"storage-specifer\",");
    fprintf(fp, "\"lexeme\":\"");

    fprintf(fp, TokenToString(p->Token));

    fprintf(fp, "\"}");

    return b;
}

bool TFunctionSpecifier_Print(TFunctionSpecifier * p, bool b, FILE * fp)
{
    int i = 0;


    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"function-specifers\" : {");

    if (p->Token == TK_INLINE)
    {
        if (i > 0)
            fprintf(fp, ",");

        fprintf(fp, "\"inline\":true");
        i++;
    }

    if (p->Token == TK__NORETURN)
    {
        if (i > 0)
            fprintf(fp, ",");

        fprintf(fp, "\"noreturn\":true");
        i++;
    }




    fprintf(fp, "\"}");
    return b;
}



bool TTypeQualifier_Print(TTypeQualifier * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"type\": \"type-qualifier\",");
    fprintf(fp, "\"lexeme\": \"");


    fprintf(fp, "%s", TokenToString(p->Token));


    fprintf(fp, "\"}");

    return true;
}

bool TTypeQualifierList_Print(TTypeQualifierList * p, bool b, FILE * fp)
{
    fprintf(fp, "\"type-qualifier-list\":[");
    b = false;
    for (int i = 0; i < p->Size; i++)
    {
        TTypeQualifier * pItem = p->Data[i];

        if (b)
        {
            fprintf(fp, ",");
        }
        b = TTypeQualifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    return b;
}



bool TPointer_Print(TPointer * pPointer, bool b, FILE * fp)
{
    fprintf(fp, "{");
    TTypeQualifierList_Print(&pPointer->Qualifier, false, fp);
    fprintf(fp, "}");
    return true;
}

bool TDeclarationSpecifier_Print(TDeclarationSpecifier * pItem, bool b, FILE * fp)
{
    switch (pItem->Type)
    {
        CASE(TStorageSpecifier) :
            b = StorageSpecifier_Print((TStorageSpecifier *)pItem, b, fp);
        break;
        CASE(TTypeQualifier) :
            b = TTypeQualifier_Print((TTypeQualifier *)pItem, b, fp);
        break;

        CASE(TFunctionSpecifier) :
            b = TFunctionSpecifier_Print((TFunctionSpecifier *)pItem, b, fp);
        break;

        CASE(TSingleTypeSpecifier) :
            b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier *)pItem, b, fp);
        break;

        CASE(TStructUnionSpecifier) :
            b = TStructUnionSpecifier_Print((TStructUnionSpecifier *)pItem, b, fp);
        break;

        CASE(TEnumSpecifier) :
            b = TEnumSpecifier_Print((TEnumSpecifier *)pItem, b, fp);
        break;

        default:
            
            break;
            
            
            

    }
    return b;
}
bool TDeclarationSpecifiers_Print(TDeclarationSpecifiers * pDeclarationSpecifiers, bool b, FILE * fp)
{
    fprintf(fp, "\"declarations-specifiers\": [");
    b = false;

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pItem = pDeclarationSpecifiers->pData[i];


        if (b)
        {
            fprintf(fp, ",");
        }
        b = TDeclarationSpecifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    
    
    
    
    return b;
}

bool TDeclaration_Print(TDeclaration * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"init-declarator-list\":");
    b = TInitDeclaratorList_Print(&p->InitDeclaratorList, b, fp);

    if (p->pCompoundStatementOpt != NULL)
    {
        TCompoundStatement_Print(p->pCompoundStatementOpt, b, fp);
    }

    fprintf(fp, "}");
    return true;
}


bool TParameter_Print(TParameter * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(&p->Declarator, b, fp);
    fprintf(fp, "}");
    return b;
}

bool TAnyDeclaration_Print(TAnyDeclaration * pDeclaration, bool b, FILE * fp)
{
    switch (pDeclaration->Type)
    {
        case TEofDeclaration_ID:
            break;

        case TStaticAssertDeclaration_ID:
            break;

        case TDeclaration_ID:
            b = TDeclaration_Print((TDeclaration *)pDeclaration, b, fp);
            break;

        default:
            
            break;
    }

    return b;
}

bool TDesignatorList_Print(TDesignatorList * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TDesignator_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializerListItem_Print(TInitializerListItem * p, bool b, FILE * fp)
{
    fprintf(fp, "{");
    b = false;

    if (p->DesignatorList.pHead)
    {
        fprintf(fp, "\"designation\":");
        b = TDesignatorList_Print(&p->DesignatorList, b, fp);
    }

    if (b)
        fprintf(fp, ",");

    if (p->pInitializer)
    {
        fprintf(fp, "\"initializer\":");
        b = TInitializer_Print(p->pInitializer, b, fp);
    }
    fprintf(fp, "}");
    return true;
}


bool TDeclarations_Print(TDeclarations * p, bool b, FILE * fp)
{
    b = false;
    fprintf(fp, "[");

    for (int i = 0; i < p->Size; i++)
    {
        if (i > 0)
            fprintf(fp, ",");

        TAnyDeclaration * pItem = p->pItems[i];
        b = TAnyDeclaration_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


void TProgram_PrintAstToFile(TProgram * pProgram,
                             const char * fileName,
                             const char * inputFileName)
{
    FILE * fp = fopen(fileName, "w");
    


    bool b = false;
    fprintf(fp, "[");

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        TAnyDeclaration * pItem = pProgram->Declarations.pItems[i];
        if (b)
            fprintf(fp, ",");
        b = TAnyDeclaration_Print(pItem, b, fp);

    }

    fprintf(fp, "]");

    fclose(fp);
}















bool IsAutoToken(Tokens token)
{
    return token == TK_AUTO;
}

bool IsSizeToken(Tokens token)
{
    
    return token == TK_LEFT_SQUARE_BRACKET;
}

void TDeclarations_Destroy(TDeclarations * p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TDeclarations_Init(TDeclarations * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void TDeclarations_Reserve(TDeclarations * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TAnyDeclaration** pnew = p->pItems;
        pnew = (TAnyDeclaration**)Realloc(pnew, n * sizeof(TAnyDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TDeclarations_PushBack(TDeclarations * p, TAnyDeclaration * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TDeclarations_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

TGroupDeclaration * TGroupDeclaration_Create() /*@default*/
{
    TGroupDeclaration *p = (TGroupDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TGroupDeclaration_ID;
        TDeclarations_Init(&p->Declarations);
        p->Identifier = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TGroupDeclaration_Delete(TGroupDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarations_Destroy(&p->Declarations);
        Free((void*)p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TStructDeclarationList_Destroy(TStructDeclarationList * p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TStructDeclarationList_Init(TStructDeclarationList * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TStructDeclarationList_Reserve(TStructDeclarationList * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TAnyStructDeclaration** pnew = p->pItems;
        pnew = (TAnyStructDeclaration**)Realloc(pnew, n * sizeof(TAnyStructDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}


void TStructDeclarationList_PushBack(TStructDeclarationList * p, TAnyStructDeclaration * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TStructDeclarationList_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

void TBlockItemList_Init(TBlockItemList * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TBlockItemList_Destroy(TBlockItemList * p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TBlockItem_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TBlockItemList_Reserve(TBlockItemList * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TBlockItem** pnew = p->pItems;
        pnew = (TBlockItem**)Realloc(pnew, n * sizeof(TBlockItem*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TBlockItemList_PushBack(TBlockItemList * p, TBlockItem * pItem)/*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TBlockItemList_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

TCompoundStatement * TCompoundStatement_Create() /*@default*/
{
    TCompoundStatement *p = (TCompoundStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCompoundStatement_ID;
        TBlockItemList_Init(&p->BlockItemList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TCompoundStatement_Delete(TCompoundStatement * p) /*@default*/
{
    if (p != NULL)
    {
        TBlockItemList_Destroy(&p->BlockItemList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

TLabeledStatement * TLabeledStatement_Create(void) /*@default*/
{
    TLabeledStatement *p = (TLabeledStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TLabeledStatement_ID;
        p->pStatementOpt = NULL;
        p->pExpression = NULL;
        p->Identifier = NULL;
        p->token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TLabeledStatement_Delete(TLabeledStatement * p)/*@default*/
{
    if (p != NULL)
    {
        TStatement_Delete(p->pStatementOpt);
        TExpression_Delete(p->pExpression);
        Free((void*)p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
TForStatement * TForStatement_Create(void)/*@default*/
{
    TForStatement *p = (TForStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TForStatement_ID;
        p->pInitDeclarationOpt = NULL;
        p->pExpression1 = NULL;
        p->pExpression2 = NULL;
        p->pExpression3 = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

void TForStatement_Delete(TForStatement * p)/*@default*/
{
    if (p != NULL)
    {
        TAnyDeclaration_Delete(p->pInitDeclarationOpt);
        TExpression_Delete(p->pExpression1);
        TExpression_Delete(p->pExpression2);
        TExpression_Delete(p->pExpression3);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}

TWhileStatement * TWhileStatement_Create(void) /*@default*/
{
    TWhileStatement *p = (TWhileStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TWhileStatement_ID;
        p->pExpression = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TWhileStatement_Delete(TWhileStatement * p)/*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

TDoStatement * TDoStatement_Create(void) /*@default*/
{
    TDoStatement *p = (TDoStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TDoStatement_ID;
        p->pExpression = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

void TDoStatement_Delete(TDoStatement * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}


TExpressionStatement * TExpressionStatement_Create(void) /*@default*/
{
    TExpressionStatement *p = (TExpressionStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TExpressionStatement_ID;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TExpressionStatement_Delete(TExpressionStatement * p)/*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

TJumpStatement * TJumpStatement_Create(void) /*@default*/
{
    TJumpStatement *p = (TJumpStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TJumpStatement_ID;
        p->token = TK_NONE;
        p->Identifier = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TJumpStatement_Delete(TJumpStatement * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Identifier);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}




TAsmStatement * TAsmStatement_Create(void) /*@default*/
{
    TAsmStatement *p = (TAsmStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAsmStatement_ID;
        TScannerItemList_Init(&p->ClueList);
    }
    return p;
}

void TAsmStatement_Delete(TAsmStatement * p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList);
        Free((void*)p);
    }
}

TSwitchStatement * TSwitchStatement_Create(void) /*@default*/
{
    TSwitchStatement *p = (TSwitchStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSwitchStatement_ID;
        p->pConditionExpression = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TSwitchStatement_Delete(TSwitchStatement * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConditionExpression);
        TStatement_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}


TIfStatement * TIfStatement_Create(void) /*@default*/
{
    TIfStatement *p = (TIfStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TIfStatement_ID;
        p->pConditionExpression = NULL;
        p->pStatement = NULL;
        p->pElseStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TIfStatement_Delete(TIfStatement * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConditionExpression);
        TStatement_Delete(p->pStatement);
        TStatement_Delete(p->pElseStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

void TStatement_Delete(TStatement * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((TExpressionStatement*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}



void TBlockItem_Delete(TBlockItem * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((TExpressionStatement*)p);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((TDeclaration*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue * p) /*@default*/
{
    p->Type = TPrimaryExpressionValue_ID;
    p->token = TK_NONE;
    p->lexeme = NULL;
    p->pExpressionOpt = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue * p) /*@default*/
{
    Free((void*)p->lexeme);
    TExpression_Delete(p->pExpressionOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

TPrimaryExpressionValue * TPrimaryExpressionValue_Create() /*@default*/
{
    TPrimaryExpressionValue *p = (TPrimaryExpressionValue*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TPrimaryExpressionValue_Init(p);
    }
    return p;
}

void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue * p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionValue_Destroy(p);
        Free((void*)p);
    }
}

TPrimaryExpressionLambda * TPrimaryExpressionLambda_Create() /*@default*/
{
    TPrimaryExpressionLambda *p = (TPrimaryExpressionLambda*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLambda_ID;
        p->pCompoundStatement = NULL;
        p->pParameterTypeListOpt = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TPrimaryExpressionLambda_Delete(TPrimaryExpressionLambda * p) /*@default*/
{
    if (p != NULL)
    {
        TParameterTypeList_Delete(p->pParameterTypeListOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

void TPostfixExpressionCore_Delete(TPostfixExpressionCore * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->lexeme);
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TPostfixExpressionCore_Delete(p->pNext);
        TInitializerList_Destroy(&p->InitializerList);
        Free((void*)p->Identifier);
        TTypeName_Delete(p->pTypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}

TBinaryExpression * TBinaryExpression_Create(void) /*@default*/
{
    TBinaryExpression *p = (TBinaryExpression*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TBinaryExpression_ID;
        p->token = TK_NONE;
        p->pExpressionLeft = NULL;
        p->pExpressionRight = NULL;
        p->Position.FileIndex = 0;
        p->Position.Line = 0;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TBinaryExpression_Delete(TBinaryExpression * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}


void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionRight);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}


void TCastExpressionType_Delete(TCastExpressionType * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

TTernaryExpression * TTernaryExpression_Create(void) /*@default*/
{
    TTernaryExpression *p = (TTernaryExpression*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTernaryExpression_ID;
        p->token = TK_NONE;
        p->pExpressionLeft = NULL;
        p->pExpressionMiddle = NULL;
        p->pExpressionRight = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TTernaryExpression_Delete(TTernaryExpression * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionMiddle);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->lexeme);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}
TPrimaryExpressionLiteralItem * TPrimaryExpressionLiteralItem_Create() /*@default*/
{
    TPrimaryExpressionLiteralItem *p = (TPrimaryExpressionLiteralItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->lexeme = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

TPrimaryExpressionLiteral * TPrimaryExpressionLiteral_Create() /*@default*/
{
    TPrimaryExpressionLiteral *p = (TPrimaryExpressionLiteral*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLiteral_ID;
        TPrimaryExpressionLiteralItemList_Init(&p->List);
    }
    return p;
}


void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral * p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionLiteralItemList_Destroy(&p->List);
        Free((void*)p);
    }
}

void TExpression_Delete(TExpression * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((TCastExpressionType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


TEofDeclaration * TEofDeclaration_Create() /*@default*/
{
    TEofDeclaration *p = (TEofDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEofDeclaration_ID;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}


void TEofDeclaration_Delete(TEofDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}



TStaticAssertDeclaration * TStaticAssertDeclaration_Create() /*@default*/
{
    TStaticAssertDeclaration *p = (TStaticAssertDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStaticAssertDeclaration_ID;
        p->pConstantExpression = NULL;
        p->Text = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
        TScannerItemList_Init(&p->ClueList5);
    }
    return p;
}

void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConstantExpression);
        Free((void*)p->Text);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        TScannerItemList_Destroy(&p->ClueList5);
        Free((void*)p);
    }
}

TEnumerator * TEnumerator_Create(void) /*@default*/
{
    TEnumerator *p = (TEnumerator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->Name = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        p->bHasComma = false;
    }
    return p;
}

void TEnumerator_Delete(TEnumerator * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Name);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TEnumeratorList_Init(TEnumeratorList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TEnumeratorList_Destroy(TEnumeratorList * p)
{
    TEnumerator * pCurrent = p->pHead;
    while (pCurrent)
    {
        TEnumerator * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TEnumerator_Delete(pItem);
    }
}

TEnumSpecifier * TEnumSpecifier_Create(void) /*@default*/
{
    TEnumSpecifier *p = (TEnumSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEnumSpecifier_ID;
        p->Name = NULL;
        TEnumeratorList_Init(&p->EnumeratorList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TEnumSpecifier_Delete(TEnumSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Name);
        TEnumeratorList_Destroy(&p->EnumeratorList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

bool TEnumSpecifier_CompareTagName(TEnumSpecifier * p1, TEnumSpecifier * p2)
{
    bool result = false;

    if (p1->Name && p2->Name && strcmp(p1->Name, p2->Name) == 0)
    {
        result = true;
    }
    return result;
}

TUnionSetItem * TUnionSetItem_Create() /*@default*/
{
    TUnionSetItem *p = (TUnionSetItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->Token = TK_NONE;
        p->TokenFollow = TK_NONE;
        p->Name = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TUnionSetItem_Delete(TUnionSetItem * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Name);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TUnionSet_Init(TUnionSet * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TUnionSet_Destroy(TUnionSet * p)
{
    
    TUnionSetItem * pCurrent = p->pHead;
    while (pCurrent)
    {
        TUnionSetItem * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TUnionSetItem_Delete(pItem);
    }
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);

}


void TUnionSet_PushBack(TUnionSet * pList, TUnionSetItem * pItem)
{
    if (pList->pHead == NULL)
    {
        pList->pHead = (pItem);
    }
    else
    {
        pList->pTail->pNext = pItem;
    }
    pList->pTail = pItem;
}




TStructUnionSpecifier * TStructUnionSpecifier_Create() /*@default*/
{
    TStructUnionSpecifier *p = (TStructUnionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStructUnionSpecifier_ID;
        TStructDeclarationList_Init(&p->StructDeclarationList);
        p->TagName = NULL;
        p->Token = TK_NONE;
        TUnionSet_Init(&p->UnionSet);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}
void TStructUnionSpecifier_Delete(TStructUnionSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclarationList_Destroy(&p->StructDeclarationList);
        Free((void*)p->TagName);
        TUnionSet_Destroy(&p->UnionSet);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

bool TStructUnionSpecifier_CompareTagName(TStructUnionSpecifier * p1, TStructUnionSpecifier * p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        if (p1->TagName && p2->TagName && strcmp(p1->TagName, p2->TagName) == 0)
        {
            result = true;
        }
    }
    return result;
}

int StrCmpNull(char const * s1, char const * s2)
{
    if (s1 == 0)
        return -1;
    return strcmp(s1, s2);
}


TSingleTypeSpecifier * TSingleTypeSpecifier_Create(void) /*@default*/
{
    TSingleTypeSpecifier *p = (TSingleTypeSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSingleTypeSpecifier_ID;
        p->Token2 = TK_NONE;
        p->TypedefName = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier * p) /*@default*/
{
    Free((void*)p->TypedefName);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TSingleTypeSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TSingleTypeSpecifier_Compare(TSingleTypeSpecifier * p1, TSingleTypeSpecifier * p2)
{
    bool result = false;
    if (p1->Token2 == p2->Token2)
    {
        if (p1->TypedefName && p2->TypedefName &&
            strcmp(p1->TypedefName, p2->TypedefName) == 0)
        {
            result = true;
        }
    }
    return result;
}

const char * TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier * p)
{
    const char * result = NULL;
    if (p->Token2 == TK_IDENTIFIER)
    {
        result = p->TypedefName;
    }
    return result;
}

bool TTypeSpecifier_Compare(TTypeSpecifier * p1, TTypeSpecifier * p2)
{
    bool result = false;

    if (p1->Type != p2->Type)
    {
        return false;
    }

    switch (p1->Type)
    {
    case TStructUnionSpecifier_ID:
        result = TStructUnionSpecifier_CompareTagName((TStructUnionSpecifier *)p1, (TStructUnionSpecifier *)p2);
        break;
    case TAtomicTypeSpecifier_ID:
        result = TAtomicTypeSpecifier_Compare((TAtomicTypeSpecifier *)p1, (TAtomicTypeSpecifier *)p2);
        break;
    case TSingleTypeSpecifier_ID:
        result = TSingleTypeSpecifier_Compare((TSingleTypeSpecifier *)p1, (TSingleTypeSpecifier *)p2);
        break;
    case TEnumSpecifier_ID:
        result = TEnumSpecifier_CompareTagName((TEnumSpecifier *)p1, (TEnumSpecifier *)p2);
        break;
    default:
        break;
    }
    return result;
}

void TTypeSpecifier_Delete(TTypeSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)p);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)p);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)p);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)p);
                break;
                default:
                break;
            }
    }
}


void TDeclarator_Init(TDeclarator * p) /*@default*/
{
    p->PointerList.pHead = NULL;
    p->PointerList.pTail = NULL;
    p->pDirectDeclarator = NULL;
    TScannerItemList_Init(&p->ClueList);
}

TDeclarator * TDeclarator_Create() /*@default*/
{
    TDeclarator *p = (TDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TDeclarator_Init(p);
    }
    return p;
}

void TDeclarator_Destroy(TDeclarator * p) /*@default*/
{
    TPointerList_Destroy(&p->PointerList);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TScannerItemList_Destroy(&p->ClueList);
}

void TDeclarator_Swap(TDeclarator * a, TDeclarator * b)
{
    TDeclarator t = *a;
    *a = *b;
    *b = t;
}

void TDeclarator_Delete(TDeclarator * p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarator_Destroy(p);
        Free((void*)p);
    }
}

TInitDeclarator * TInitDeclarator_Create() /*@default*/
{
    TInitDeclarator *p = (TInitDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pDeclarator = NULL;
        p->pInitializer = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TInitDeclarator_Destroy(TInitDeclarator * p) /*@default*/
{
    TDeclarator_Delete(p->pDeclarator);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TInitDeclarator_Delete(TInitDeclarator * p) /*@default*/
{
    if (p != NULL)
    {
        TInitDeclarator_Destroy(p);
        Free((void*)p);
    }
}

void TParameterTypeList_Init(TParameterTypeList * p) /*@default*/
{
    TParameterList_Init(&p->ParameterList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    p->bVariadicArgs = false;
}
void TParameterTypeList_Destroy(TParameterTypeList * p) /*@default*/
{
    TParameterList_Destroy(&p->ParameterList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

TParameterTypeList * TParameterTypeList_Create() /*@default*/
{
    TParameterTypeList *p = (TParameterTypeList*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TParameterTypeList_Init(p);
    }
    return p;
}
void TParameterTypeList_Delete(TParameterTypeList * p) /*@default*/
{
    if (p != NULL)
    {
        TParameterTypeList_Destroy(p);
        Free((void*)p);
    }
}

const char * TParameterTypeList_GetFirstParameterName(TParameterTypeList * p)
{
    const char * name = "";
    if (p->ParameterList.pHead)
    {
        name = TDeclarator_GetName(&p->ParameterList.pHead->Declarator);
    }
    return name;
}

bool TParameterTypeList_HasNamedArgs(TParameterTypeList * p)
{
    bool result = false;
    if (p != NULL)
    {
        ForEachListItem(TParameter, pParameter, &p->ParameterList)
        {
            const char * parameterName = TParameter_GetName(pParameter);
            if (parameterName != NULL)
            {
                result = true;
                break;
            }
        }
    }
    return result;
}



void TParameterTypeList_GetArgsString(TParameterTypeList * p, StrBuilder * sb)
{
    if (p != NULL)
    {
        int index = 0;
        ForEachListItem(TParameter, pParameter, &p->ParameterList)
        {
            const char * parameterName = TParameter_GetName(pParameter);
            if (parameterName)
            {
                if (index > 0)
                {
                    StrBuilder_Append(sb, ", ");
                }

                StrBuilder_Append(sb, parameterName);
            }

            index++;
        }
    }
}

TParameter * TParameterTypeList_GetParameterByIndex(TParameterTypeList * p, int index)
{
    TParameter * pParameterResult = NULL;


    if (index == 0)
    {
        
        
        
        if (p->ParameterList.pHead)
        {
            if (p->ParameterList.pHead->Specifiers.Size == 1 &&
                p->ParameterList.pHead->Specifiers.pData[0]->Type == TSingleTypeSpecifier_ID)
            {
                TSingleTypeSpecifier * pSingleTypeSpecifier =
                    p->ParameterList.pHead->Specifiers.pData[0];
                if (pSingleTypeSpecifier)
                {
                    if (pSingleTypeSpecifier->Token2 == TK_VOID)
                    {
                        if (p->ParameterList.pHead->Declarator.PointerList.pHead == 0)
                        {
                            return NULL;
                        }
                    }
                }
            }
        }
    }

    int indexLocal = 0;

    ForEachListItem(TParameter, pParameter, &p->ParameterList)
    {
        if (indexLocal == index)
        {
            pParameterResult = pParameter;
            break;
        }
        indexLocal++;
    }

    return pParameterResult;
}

TParameter * TParameterTypeList_FindParameterByName(TParameterTypeList * p, const char * name)
{
    TParameter * pParameterResult = NULL;
    if (name)
    {
        ForEachListItem(TParameter, pParameter, &p->ParameterList)
        {
            
            const char * parameterName = TParameter_GetName(pParameter);
            if (parameterName && strcmp(parameterName, name) == 0)
            {
                pParameterResult = pParameter;
                break;
            }
        }
    }
    return pParameterResult;
}

const char * TParameterTypeList_GetSecondParameterName(TParameterTypeList * p)
{
    const char * name = "";
    if (p->ParameterList.pHead &&
        p->ParameterList.pHead->pNext)
    {
        name = TDeclarator_GetName(&p->ParameterList.pHead->pNext->Declarator);
    }
    return name;
}

void TDirectDeclarator_Destroy(TDirectDeclarator * p) /*@default*/
{
    Free((void*)p->Identifier);
    TDeclarator_Delete(p->pDeclarator);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TParameterTypeList_Destroy(&p->Parameters);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
}

void TDirectDeclarator_Delete(TDirectDeclarator * p) /*@default*/
{
    if (p != NULL)
    {
        TDirectDeclarator_Destroy(p);
        Free((void*)p);
    }
}

TDeclarationSpecifier * TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList * p)
{
    TDeclarationSpecifier * pSpecifier = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];
        if (pSpecifierQualifier->Type == TSingleTypeSpecifier_ID ||
            pSpecifierQualifier->Type == TStructUnionSpecifier_ID ||
            pSpecifierQualifier->Type == TEnumSpecifier_ID)
        {
            
            pSpecifier = (TDeclarationSpecifier *)pSpecifierQualifier;
            break;
        }
    }
    return pSpecifier;
}

const char * TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList * p)
{
    const char * typedefName = NULL;

    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];


        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            typedefName = pSingleTypeSpecifier->TypedefName;
            break;
        }
    }
    return typedefName;
}

bool TSpecifierQualifierList_Compare(TSpecifierQualifierList * p1, TSpecifierQualifierList * p2)
{
    if (p1->Size != p2->Size)
    {
        return false;
    }

    bool bResult = false;
    for (int i = 0; i < p1->Size; i++)
    {
        if (p1->pData[i]->Type == p2->pData[i]->Type)
        {
            switch (p1->pData[i]->Type)
            {

                CASE(TSingleTypeSpecifier) :
                    if (!TSingleTypeSpecifier_Compare((TSingleTypeSpecifier *)p1->pData[i],
                        (TSingleTypeSpecifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;

                CASE(TStorageSpecifier) :
                    if (!TStorageSpecifier_Compare((TStorageSpecifier *)p1->pData[i],
                        (TStorageSpecifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;
                CASE(TTypeQualifier) :
                    if (!TTypeQualifier_Compare((TTypeQualifier *)p1->pData[i],
                        (TTypeQualifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;
                CASE(TFunctionSpecifier) :
                    if (!TFunctionSpecifier_Compare((TFunctionSpecifier *)p1->pData[i],
                        (TFunctionSpecifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;


                CASE(TStructUnionSpecifier) :
                    if (!TStructUnionSpecifier_CompareTagName((TStructUnionSpecifier *)p1->pData[i],
                        (TStructUnionSpecifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;

                CASE(TEnumSpecifier) :
                    if (!TEnumSpecifier_CompareTagName((TEnumSpecifier *)p1->pData[i],
                        (TEnumSpecifier *)p2->pData[i]))
                    {
                        return false;
                    }
                break;

            default:
                
                break;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList * p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];
        TStorageSpecifier * pStorageSpecifier =
            TSpecifierQualifier_As_TStorageSpecifier(pSpecifierQualifier);
        if (pStorageSpecifier &&
            pStorageSpecifier->Token == TK_TYPEDEF)
        {
            bResult = true;
            break;
        }
    }
    return bResult;
}

bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList * p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];

        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token2 == TK_CHAR)
        {
            bResult = true;
            break;
        }
    }
    return bResult;
}


bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList * p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
        if (pSingleTypeSpecifier &&
            (pSingleTypeSpecifier->Token2 == TK_INT ||
                pSingleTypeSpecifier->Token2 == TK_SHORT ||
                pSingleTypeSpecifier->Token2 == TK_SIGNED ||
                pSingleTypeSpecifier->Token2 == TK_UNSIGNED ||
                pSingleTypeSpecifier->Token2 == TK__INT8 ||
                pSingleTypeSpecifier->Token2 == TK__INT16 ||
                pSingleTypeSpecifier->Token2 == TK__INT32 ||
                pSingleTypeSpecifier->Token2 == TK__INT64 ||
                pSingleTypeSpecifier->Token2 == TK__WCHAR_T)
            )
        {
            bResult = true;
            break;
        }
    }
    return bResult;
}


bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList * p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
        if (pSingleTypeSpecifier &&
            (pSingleTypeSpecifier->Token2 == TK_DOUBLE ||
                pSingleTypeSpecifier->Token2 == TK_FLOAT))
        {
            bResult = true;
            break;
        }
    }
    return bResult;
}

bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList * p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifierQualifier = p->pData[i];
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);

        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token2 == TK__BOOL)
        {
            bResult = true;
            break;
        }
    }
    return bResult;
}

const char * TDeclarator_GetName(TDeclarator * p)
{
    if (p == NULL)
    {
        return NULL;
    }
    TDirectDeclarator * pDirectDeclarator = p->pDirectDeclarator;
    while (pDirectDeclarator != NULL)
    {
        if (pDirectDeclarator->Identifier != NULL &&
            pDirectDeclarator->Identifier[0] != 0)
        {
            return pDirectDeclarator->Identifier;
        }

        if (pDirectDeclarator->pDeclarator)
        {
            const char * name =
                TDeclarator_GetName(pDirectDeclarator->pDeclarator);
            if (name != NULL)
            {
                return name;
            }
        }
        pDirectDeclarator =
            pDirectDeclarator->pDirectDeclarator;
    }
    return NULL;
}

const char * TInitDeclarator_FindName(TInitDeclarator * p)
{
    
    return TDeclarator_GetName(p->pDeclarator);
}



TAlignmentSpecifier * TAlignmentSpecifier_Create(void) /*@default*/
{
    TAlignmentSpecifier *p = (TAlignmentSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAlignmentSpecifier_ID;
        p->TypeName = NULL;
    }
    return p;
}
void TAlignmentSpecifier_Destroy(TAlignmentSpecifier * p) /*@default*/
{
    Free((void*)p->TypeName);
}

void TAlignmentSpecifier_Delete(TAlignmentSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TAlignmentSpecifier_Destroy(p);
        Free((void*)p);
    }
}


TStructDeclaration * TStructDeclaration_Create() /*@default*/
{
    TStructDeclaration *p = (TStructDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStructDeclaration_ID;
        p->SpecifierQualifierList.pData = NULL;
        p->SpecifierQualifierList.Size = 0;
        p->SpecifierQualifierList.Capacity = 0;
        TStructDeclaratorList_Init(&p->DeclaratorList);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TStructDeclaratorList_Destroy(TStructDeclaratorList * p)
{
    TInitDeclarator * pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitDeclarator * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitDeclarator_Delete(pItem);
    }
}

void TStructDeclaratorList_Init(TStructDeclaratorList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TStructDeclaratorList_Add(TStructDeclaratorList * pList, TInitDeclarator * pItem)
{
    if (pList->pHead == NULL)
    {
        pList->pHead = pItem;
        pList->pTail = pItem;
    }
    else
    {
        pList->pTail->pNext = pItem;
        pList->pTail = pItem;
    }
}

void TStructDeclaration_Destroy(TStructDeclaration * p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TStructDeclaratorList_Destroy(&p->DeclaratorList);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TStructDeclaration_Delete(TStructDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclaration_Destroy(p);
        Free((void*)p);
    }
}


void TAnyStructDeclaration_Delete(TAnyStructDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((TStaticAssertDeclaration*)p);
                break;
                case TStructDeclaration_ID:
                    TStructDeclaration_Delete((TStructDeclaration*)p);
                break;
                default:
                break;
            }
    }
}

bool TPointerList_IsAutoPointer(TPointerList * pPointerlist)
{
    bool bIsPointer = false;
    bool bIsAuto = false;
    if (pPointerlist)
    {
        bIsPointer = (pPointerlist->pHead != NULL);

        
        TPointer * pItem = pPointerlist->pHead;
        
        while (pItem)
        {
            for (int i = 0; i < pItem->Qualifier.Size; i++)
            {
                TTypeQualifier * pQualifier = pItem->Qualifier.Data[i];
                if (IsAutoToken(pQualifier->Token))
                {
                    bIsAuto = true;
                    break;
                }
            }
            if (bIsAuto && bIsPointer)
                break;

            pItem = pItem->pNext;
        }
    }
    return bIsAuto;
}

void TPointerList_Destroy(TPointerList * p)
{
    TPointer * pCurrent = p->pHead;
    while (pCurrent)
    {
        TPointer * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TPointer_Delete(pItem);
    }
}

TPointer * TPointer_Create(void) /*@default*/
{
    TPointer *p = (TPointer*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeQualifierList_Init(&p->Qualifier);
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TPointer_Destroy(TPointer * p) /*@default*/
{
    TTypeQualifierList_Destroy(&p->Qualifier);
    TScannerItemList_Destroy(&p->ClueList0);
}

void TPointerList_PushBack(TPointerList * pList, TPointer * pItem)
{
    if ((pList)->pHead == NULL)
    {
        (pList)->pHead = (pItem);
        (pList)->pTail = (pItem);
    }
    else
    {
        (pList)->pTail->pNext = (pItem);
        (pList)->pTail = (pItem);
    }
}

void TPointer_Delete(TPointer * p) /*@default*/
{
    if (p != NULL)
    {
        TPointer_Destroy(p);
        Free((void*)p);
    }
}

void TPointerList_Printf(TPointerList * p)
{
    ForEachListItem(TPointer, pItem, p)
    {
        printf("*");

        for (int i = 0; i < pItem->Qualifier.Size; i++)
        {
            if (i > 0)
                printf(" ");
            TTypeQualifier * pQualifier = pItem->Qualifier.Data[i];
            printf("%s", TokenToString(pQualifier->Token));

            if (IsSizeToken(pQualifier->Token))
            {
                printf("(%s)", pQualifier->SizeIdentifier);
            }
        }
    }
    printf("\n");
}

void TPointerList_Swap(TPointerList * a, TPointerList * b)
{
    TPointerList t = *a;
    *a = *b;
    *b = t;
}

void TPointer_Copy(TPointer * dest, TPointer * src)
{
    TTypeQualifierList_Copy(&dest->Qualifier, &src->Qualifier);
}

bool TPointerList_IsPointer(TPointerList * pPointerlist)
{
    return pPointerlist->pHead != NULL;
}


const char * TPointerList_GetSize(TPointerList * pPointerlist)
{
    

    const char * pszResult = NULL;

    if (pPointerlist)
    {
        ForEachListItem(TPointer, pItem, pPointerlist)
        {
            for (int i = 0; i < pItem->Qualifier.Size; i++)
            {
                TTypeQualifier * pQualifier = pItem->Qualifier.Data[i];

                if (IsSizeToken(pQualifier->Token))
                {
                    pszResult = pQualifier->SizeIdentifier;
                    break;
                }
            }
        }
    }
    return pszResult;
}

bool TPointerList_IsPointerN(TPointerList * pPointerlist, int n)
{
    int k = 0;
    if (pPointerlist)
    {
        ForEachListItem(TPointer, pItem, pPointerlist)
        {

            k++;

        }
    }
    return k == n;
}

bool TPointerList_IsPointerToObject(TPointerList * pPointerlist)
{
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL)
    {
        if (pPointer->Qualifier.Size == 0)
        {
            pPointer = pPointer->pNext;
            if (pPointer == NULL)
            {
                bResult = true;
            }
        }
    }


    return bResult;
}

bool TPointerList_IsAutoPointerToObject(TPointerList * pPointerlist)
{
    
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL && pPointer->pNext == NULL)
    {
        
        
        for (int i = 0; i < pPointer->Qualifier.Size; i++)
        {
            if (IsAutoToken(pPointer->Qualifier.Data[i]->Token))
            {
                bResult = true;
                break;
            }
        }
    }

    return bResult;
}


bool TPointerList_IsAutoPointerSizeToObject(TPointerList * pPointerlist)
{
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL)
    {
        if (pPointer->Qualifier.Size == 2 &&
            pPointer->pNext == NULL)
        {
            bResult = (IsAutoToken(pPointer->Qualifier.Data[0]->Token) &&
                IsSizeToken(pPointer->Qualifier.Data[1]->Token)) ||
                (IsSizeToken(pPointer->Qualifier.Data[0]->Token) &&
                    IsAutoToken(pPointer->Qualifier.Data[0]->Token));
        }
    }


    return bResult;
}

bool TPointerList_IsAutoPointerToPointer(TPointerList * pPointerlist)
{
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL)
    {
        if (pPointer->Qualifier.Size == 1 &&
            IsAutoToken(pPointer->Qualifier.Data[0]->Token))
        {
            pPointer = pPointer->pNext;
            if (pPointer != NULL)
            {
                if (pPointer->Qualifier.Size == 0)
                {
                    bResult = true;
                }
            }
        }
    }


    return bResult;
}


bool TPointerList_IsAutoPointerToAutoPointer(TPointerList * pPointerlist)
{
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL)
    {
        if (pPointer->Qualifier.Size == 1 &&
            IsAutoToken(pPointer->Qualifier.Data[0]->Token))
        {
            pPointer = pPointer->pNext;
            if (pPointer != NULL)
            {
                if (pPointer->Qualifier.Size == 1 &&
                    IsAutoToken(pPointer->Qualifier.Data[0]->Token))
                {
                    bResult = true;
                }
                else if (pPointer->Qualifier.Size == 2)
                {
                    
                    
                    bResult = IsAutoToken(pPointer->Qualifier.Data[0]->Token) ||
                        IsAutoToken(pPointer->Qualifier.Data[1]->Token);
                }
            }
        }
    }

    return bResult;
}



void TTypeQualifierList_Destroy(TTypeQualifierList * p)   
{
    for (int i = 0; i < p->Size; i++)
    {
        TTypeQualifier_Delete(p->Data[i]);
    }
}


void TTypeQualifierList_Init(TTypeQualifierList * p)
{
    p->Data[0] = NULL;
    p->Size = 0;
}

void TTypeQualifierList_Copy(TTypeQualifierList * dest, TTypeQualifierList * src)
{
    TTypeQualifierList_Destroy(dest);
    TTypeQualifierList_Init(dest);

    for (int i = 0; i < src->Size; i++)
    {
        TTypeQualifier * pItem = TTypeQualifier_Create();
        TTypeQualifier_Copy(pItem, src->Data[i]);
        TTypeQualifierList_PushBack(dest, pItem);
    }
}

void TTypeQualifierList_PushBack(TTypeQualifierList * p, TTypeQualifier * pItem)
{

    if (p->Size + 1 > 4)
    {
        

    }
    else
    {
        p->Data[p->Size] = pItem;
        p->Size++;
    }

}

TTypeQualifier * TTypeQualifier_Create(void) /*@default*/
{
    TTypeQualifier *p = (TTypeQualifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTypeQualifier_ID;
        p->SizeIdentifier = NULL;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TTypeQualifier_Destroy(TTypeQualifier * p) /*@default*/
{
    Free((void*)p->SizeIdentifier);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TTypeQualifier_Delete(TTypeQualifier * p) /*@default*/
{
    if (p != NULL)
    {
        TTypeQualifier_Destroy(p);
        Free((void*)p);
    }
}

void TTypeQualifier_Copy(TTypeQualifier * dest, TTypeQualifier * src)
{
    PTR_STRING_REPLACE(dest->SizeIdentifier, src->SizeIdentifier);
    dest->Token = src->Token;
    
    
}

bool TTypeQualifier_Compare(TTypeQualifier * p1, TTypeQualifier * p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        if (p1->SizeIdentifier == p2->SizeIdentifier)
        {
            result = true;
        }
    }
    return result;
}

TStorageSpecifier * TStorageSpecifier_Create(void) /*@default*/
{
    TStorageSpecifier *p = (TStorageSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStorageSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TStorageSpecifier_Destroy(TStorageSpecifier * p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TStorageSpecifier_Delete(TStorageSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TStorageSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TStorageSpecifier_Compare(TStorageSpecifier * p1, TStorageSpecifier * p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        result = true;
    }
    return result;
}
void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}
bool TAtomicTypeSpecifier_Compare(TAtomicTypeSpecifier * p1, TAtomicTypeSpecifier * p2)
{
    
    
      
    
      
    
    
    assert(false);
    return true;
}
void TSpecifierQualifierList_Destroy(TSpecifierQualifierList * pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TSpecifierQualifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TSpecifierQualifierList_Reserve(TSpecifierQualifierList * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TSpecifierQualifier** pnew = p->pData;
        pnew = (TSpecifierQualifier**)Realloc(pnew, n * sizeof(TSpecifierQualifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TSpecifierQualifierList_PushBack(TSpecifierQualifierList * p, TSpecifierQualifier * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TSpecifierQualifierList_Reserve(p, n);
    }
    p->pData[p->Size] = pItem;
    p->Size++;
}




bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList * p, Tokens token, const char * lexeme)
{
    bool bResult = false;

    bool bStruct = false;
    bool bEnum = false;

    bool bTypeDef = false;
    bool bInt = false;
    for (int i = 0; i < p->Size; i++)
    {
        TSpecifierQualifier * pSpecifier = p->pData[i];
        switch (pSpecifier->Type)
        {
            CASE(TSingleTypeSpecifier) :
            {     TSingleTypeSpecifier * pTSingleTypeSpecifier =
                (TSingleTypeSpecifier *)pSpecifier;
            switch (pTSingleTypeSpecifier->Token2)
            {
            case TK_INT:
                bInt = true;
                break;
            case TK_DOUBLE:
                break;

            case TK_IDENTIFIER:
                bTypeDef = true;
                break;
            default:
                
                break;
            }
            }
            break;

            CASE(TStructUnionSpecifier) :
                bStruct = true;
            break;

            CASE(TEnumSpecifier) :
                bEnum = true;
            break;

            CASE(TStorageSpecifier) :

                break;
            CASE(TTypeQualifier) :

                break;
            CASE(TFunctionSpecifier) :

                break;
            CASE(TAlignmentSpecifier) :

                break;
        default:
            
            break;
        }
    }


    if (token == TK_IDENTIFIER)
    {
        if (!bTypeDef && !bInt)
        {
            
            
            
            
            bResult = true;
        }
    }
    else
    {
        
        bResult = true;
    }
    return bResult;

}


TDeclarationSpecifier * TDeclarationSpecifiers_GetMainSpecifier(TDeclarationSpecifiers * p, enum EType type)
{
    TDeclarationSpecifier * pSpecifier = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        TDeclarationSpecifier * pSpecifierQualifier = p->pData[i];
        if (pSpecifierQualifier->Type == type)
        {
            
            pSpecifier = (TDeclarationSpecifier *)pSpecifierQualifier;
            break;
        }
    }
    return pSpecifier;
}

bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers * pDeclarationSpecifiers,
    Tokens token,
    const char * lexeme)
{
    bool bResult = false;
    bool bStruct = false;
    bool bEnum = false;

    TStructUnionSpecifier * pTStructUnionSpecifier = NULL;
    TEnumSpecifier * pEnumSpecifier = NULL;
    bool bTypeDef = false;
    bool bOther = false;

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pSpecifier = pDeclarationSpecifiers->pData[i];

        switch (pSpecifier->Type)
        {
            CASE(TSingleTypeSpecifier) :
            {     TSingleTypeSpecifier * pTSingleTypeSpecifier =
                (TSingleTypeSpecifier *)pSpecifier;
            switch (pTSingleTypeSpecifier->Token2)
            {
                
                
                    
                    
                    

            case TK_IDENTIFIER:
                bTypeDef = true;
                break;
            default:
                bOther = true;
                break;
                
                break;
            }
            }
            break;

            CASE(TStructUnionSpecifier) :
                bStruct = true;
            pTStructUnionSpecifier = (TStructUnionSpecifier *)pSpecifier;
            break;

            CASE(TEnumSpecifier) :
                bEnum = true;
            pEnumSpecifier = (TEnumSpecifier *)pSpecifier;
            break;

            CASE(TStorageSpecifier) :

                break;
            CASE(TTypeQualifier) :

                break;
            CASE(TFunctionSpecifier) :

                break;
            CASE(TAlignmentSpecifier) :

                break;

        default:
            
            break;
        }
    }


    if (token == TK_IDENTIFIER)
    {
        if (pTStructUnionSpecifier)
        {
            
            if (pTStructUnionSpecifier->TagName &&
                strcmp(pTStructUnionSpecifier->TagName, lexeme) == 0)
            {
                
            }
            else
            {
                bResult = true;
            }
        }
        else if (pEnumSpecifier)
        {
            
            if (pEnumSpecifier->Name &&
                strcmp(pEnumSpecifier->Name, lexeme) == 0)
            {
                
            }
            else
            {
                bResult = true;
            }
        }
        else if (!bTypeDef && !bOther)
        {
            
            
            
            
            bResult = true;
        }
    }
    else
    {
        
        bResult = true;
    }
    return bResult;
}

TStructUnionSpecifier * TDeclarationSpecifiers_GetCompleteStructUnionSpecifier(struct SymbolMap * pSymbolMap,
    TDeclarationSpecifiers * pDeclarationSpecifiers)
{
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;

    TDeclarationSpecifier * pFirstArgSpecifier =
        TDeclarationSpecifiers_GetMainSpecifier(pDeclarationSpecifiers, TStructUnionSpecifier_ID);

    if (pFirstArgSpecifier == NULL)
    {
        pFirstArgSpecifier = TDeclarationSpecifiers_GetMainSpecifier(pDeclarationSpecifiers, TSingleTypeSpecifier_ID);
    }

    if (pFirstArgSpecifier)
    {
        pStructUnionSpecifier =
            TDeclarationSpecifier_As_TStructUnionSpecifier(pFirstArgSpecifier);

        if (pStructUnionSpecifier && pStructUnionSpecifier->TagName && pStructUnionSpecifier->StructDeclarationList.Size == 0)
        {
            
            pStructUnionSpecifier =
                SymbolMap_FindStructUnion(pSymbolMap, pStructUnionSpecifier->TagName);
        }
        else
        {
            TDeclarator declarator;
            TDeclarator_Init(&declarator);


            TSingleTypeSpecifier * pSingleTypeSpecifier =
                TDeclarationSpecifier_As_TSingleTypeSpecifier(pFirstArgSpecifier);
            if (pSingleTypeSpecifier)
            {
                if (pSingleTypeSpecifier->TypedefName)
                {
                    TDeclarationSpecifiers * p2 =
                        SymbolMap_FindTypedefTarget(pSymbolMap, pSingleTypeSpecifier->TypedefName, &declarator);

                    if (p2)
                    {
                        pStructUnionSpecifier =
                            TDeclarationSpecifiers_GetMainSpecifier(p2, TStructUnionSpecifier_ID);

                        if (pStructUnionSpecifier &&
                            pStructUnionSpecifier->StructDeclarationList.Size == 0 &&
                            pStructUnionSpecifier->TagName != NULL)
                        {
                            pStructUnionSpecifier =
                                SymbolMap_FindStructUnion(pSymbolMap, pStructUnionSpecifier->TagName);
                        }
                    }
                }

            }
        }
    }
    return pStructUnionSpecifier;
}

const char * TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers * pDeclarationSpecifiers)
{
    if (pDeclarationSpecifiers == NULL)
    {
        return NULL;
    }
    const char * typeName = NULL;


    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pItem = pDeclarationSpecifiers->pData[i];

        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TDeclarationSpecifier_As_TSingleTypeSpecifier(pItem);
        if (pSingleTypeSpecifier != NULL)
        {
            if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
            {
                typeName = pSingleTypeSpecifier->TypedefName;
                break;
            }
        }
    }
    return typeName;
}

void TSpecifierQualifier_Delete(TSpecifierQualifier * pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifier_Delete(TDeclarationSpecifier * pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
                break;
                case TStorageSpecifier_ID:
                    TStorageSpecifier_Delete((TStorageSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
                break;
                case TAlignmentSpecifier_ID:
                    TAlignmentSpecifier_Delete((TAlignmentSpecifier*)pItem);
                break;
                case TFunctionSpecifier_ID:
                    TFunctionSpecifier_Delete((TFunctionSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers * pDeclarationSpecifiers) /*@default*/
{
    pDeclarationSpecifiers->pData = NULL;
    pDeclarationSpecifiers->Size = 0;
    pDeclarationSpecifiers->Capacity = 0;
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers * pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TDeclarationSpecifiers_Reserve(TDeclarationSpecifiers * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TDeclarationSpecifier** pnew = p->pData;
        pnew = (TDeclarationSpecifier**)Realloc(pnew, n * sizeof(TDeclarationSpecifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers * p, TDeclarationSpecifier * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TDeclarationSpecifiers_Reserve(p, n);
    }
    p->pData[p->Size] = pItem;
    p->Size++;
}


TDeclarator * TDeclaration_FindDeclarator(TDeclaration * p, const char * name)
{
    if (p == NULL)
    {
        return NULL;
    }
    TDeclarator * pResult = NULL;

    ForEachListItem(TInitDeclarator, pInitDeclarator, &p->InitDeclaratorList)
    {
        if (pInitDeclarator->pDeclarator &&
            pInitDeclarator->pDeclarator->pDirectDeclarator &&
            pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier)
        {
            if (strcmp(pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier, name) == 0)
            {
                pResult = pInitDeclarator->pDeclarator;
                break;
            }
        }
    }
    return pResult;
}

TFunctionSpecifier * TFunctionSpecifier_Create(void) /*@default*/
{
    TFunctionSpecifier *p = (TFunctionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TFunctionSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TFunctionSpecifier_Destroy(TFunctionSpecifier * p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TFunctionSpecifier_Delete(TFunctionSpecifier * p) /*@default*/
{
    if (p != NULL)
    {
        TFunctionSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TFunctionSpecifier_Compare(TFunctionSpecifier * p1, TFunctionSpecifier * p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        result = true;
    }
    return result;
}



bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration * p)
{
    bool bIsStructOrUnion = false;
    for (int i = 0; i < p->Specifiers.Size; i++)
    {
        TDeclarationSpecifier * pItem = p->Specifiers.pData[i];
        if (TDeclarationSpecifier_As_TStructUnionSpecifier(pItem))
        {
            bIsStructOrUnion = true;
            break;
        }

    }
    return bIsStructOrUnion;
}

void TInitDeclaratorList_Init(TInitDeclaratorList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitDeclaratorList_Destroy(TInitDeclaratorList * p)
{
    TInitDeclarator * pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitDeclarator * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitDeclarator_Delete(pItem);
    }

}



void TDeclaration_Delete(TDeclaration * p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TInitDeclaratorList_Destroy(&p->InitDeclaratorList);
        TCompoundStatement_Delete(p->pCompoundStatementOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList00);
        TScannerItemList_Destroy(&p->ClueList001);
        Free((void*)p->FunctionTag);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
TDeclaration * TDeclaration_Create() /*@default*/
{
    TDeclaration *p = (TDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TDeclaration_ID;
        TDeclarationSpecifiers_Init(&p->Specifiers);
        TInitDeclaratorList_Init(&p->InitDeclaratorList);
        p->pCompoundStatementOpt = NULL;
        p->FileIndex = 0;
        p->Line = 0;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList00);
        TScannerItemList_Init(&p->ClueList001);
        p->bDefault = false;
        p->FunctionTag = NULL;
        p->bAutoTag = false;
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TParameter_Swap(TParameter * a, TParameter * b)
{
    TParameter temp = *a;
    *a = *b;
    *b = temp;
}

const char * TDeclarationSpecifier_GetTypedefName(TDeclarationSpecifiers * p)
{
    const char * typedefName = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        TDeclarationSpecifier * pSpecifier = p->pData[i];
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TDeclarationSpecifier_As_TSingleTypeSpecifier(pSpecifier);
        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            typedefName = pSingleTypeSpecifier->TypedefName;
        }
    }
    return typedefName;
}

const char * TParameter_GetName(TParameter * p)
{
    
    return TDeclarator_GetName(&p->Declarator);
}

const char * TParameter_GetTypedefName(TParameter * p)
{
    return TDeclarationSpecifier_GetTypedefName(&p->Specifiers);
}

bool TDeclarator_IsDirectPointer(TDeclarator * p)
{
    int n = 0;
    ForEachListItem(TPointer, pPointer, &p->PointerList)
    {
        n++;
        if (n > 1)
        {
            break;
        }
    }
    return n == 1;
}

bool TParameter_IsDirectPointer(TParameter * p)
{
    return TDeclarator_IsDirectPointer(&p->Declarator);
}


TParameter * TParameter_Create() /*@default*/
{
    TParameter *p = (TParameter*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        TDeclarationSpecifiers_Init(&p->Specifiers);
        TDeclarator_Init(&p->Declarator);
        TScannerItemList_Init(&p->ClueList0);
        p->bHasComma = false;
    }
    return p;
}

void TParameter_Delete(TParameter * p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TDeclarator_Destroy(&p->Declarator);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

void TParameterList_Init(TParameterList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TParameterList_Destroy(TParameterList * p)
{
    TParameter * pCurrent = p->pHead;
    while (pCurrent)
    {
        TParameter * p = pCurrent;
        pCurrent = pCurrent->pNext;
        TParameter_Delete(p);
    }
}


bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration * pAnyDeclaration)
{
    TDeclaration * pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
    if (pDeclaration != NULL)
    {
        return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
    }

    return false;
}

bool TDeclarationSpecifiers_IsStatic(TDeclarationSpecifiers * pDeclarationSpecifiers)
{
    bool bResult = false;
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {
            CASE(TStorageSpecifier) :
            {
                TStorageSpecifier * pStorageSpecifier =
                    (TStorageSpecifier *)pItem;

                if (pStorageSpecifier->Token == TK_STATIC)
                {
                    bResult = true;
                }
            }

            break;
        default:
            
            break;
        }

        if (bResult)
        {
            break;
        }
    }
    return bResult;
}

bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers * pDeclarationSpecifiers)
{
    bool bResult = false;
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {
            CASE(TStorageSpecifier) :
            {
                TStorageSpecifier * pStorageSpecifier =
                    (TStorageSpecifier *)pItem;

                if (pStorageSpecifier->Token == TK_TYPEDEF)
                {
                    bResult = true;
                }
            }

            break;
        default:
            
            break;
        }

        if (bResult)
        {
            break;
        }
    }
    return bResult;
}

bool TAnyDeclaration_IsTypedef(TAnyDeclaration * pDeclaration)
{
    bool bResult = false;
    switch (pDeclaration->Type)
    {
    case TDeclaration_ID:
    {
        TDeclaration * p = (TDeclaration *)pDeclaration;
        bResult = TDeclarationSpecifiers_IsTypedef(&p->Specifiers);
    }
    break;
    default:
        
        break;
    }
    return bResult;
}

int TAnyDeclaration_GetFileIndex(TAnyDeclaration * pDeclaration)
{
    int result = -1;
    switch (pDeclaration->Type)
    {
    case TDeclaration_ID:
        result = ((TDeclaration *)pDeclaration)->FileIndex;
        break;
    case TStaticAssertDeclaration_ID:
        break;
    default:
        
        break;
    }
    return result;
}

void TAnyDeclaration_Delete(TAnyDeclaration * pDeclaration) /*@default*/
{
    if (pDeclaration != NULL)
    {
            switch (pDeclaration->Type)
            {
                case TGroupDeclaration_ID:
                    TGroupDeclaration_Delete((TGroupDeclaration*)pDeclaration);
                break;
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((TStaticAssertDeclaration*)pDeclaration);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((TDeclaration*)pDeclaration);
                break;
                case TEofDeclaration_ID:
                    TEofDeclaration_Delete((TEofDeclaration*)pDeclaration);
                break;
                default:
                break;
            }
    }
}

void TDesignation_Destroy(TDesignation * pDesignation) /*@default*/
{
    TDesignatorList_Destroy(&pDesignation->DesignatorList);
    TScannerItemList_Destroy(&pDesignation->ClueList0);
}

TDesignator * TDesignator_Create(void) /*@default*/
{
    TDesignator *p = (TDesignator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Name = NULL;
        p->pExpression = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}
void TDesignator_Destroy(TDesignator * p) /*@default*/
{
    Free((void*)p->Name);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}
void TDesignator_Delete(TDesignator * p) /*@default*/
{
    if (p != NULL)
    {
        TDesignator_Destroy(p);
        Free((void*)p);
    }
}


TInitializerListType * TInitializerListType_Create(void) /*@default*/
{
    TInitializerListType *p = (TInitializerListType*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TInitializerListType_ID;
        TInitializerList_Init(&p->InitializerList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        p->bDefault = false;
    }
    return p;
}
void TInitializerListType_Destroy(TInitializerListType * p) /*@default*/
{
    TInitializerList_Destroy(&p->InitializerList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
}
void TInitializerListType_Delete(TInitializerListType * p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListType_Destroy(p);
        Free((void*)p);
    }
}

void TInitializerList_Init(TInitializerList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitializerList_Destroy(TInitializerList * p)
{
    TInitializerListItem * pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitializerListItem * p = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitializerListItem_Delete(p);
    }

}

void TInitializer_Delete(TInitializer * p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((TCastExpressionType*)p);
                break;
                case TInitializerListType_ID:
                    TInitializerListType_Delete((TInitializerListType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


void TDesignatorList_Init(TDesignatorList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TDesignatorList_Destroy(TDesignatorList * p)
{
    TDesignator * pCurrent = p->pHead;
    while (pCurrent)
    {
        TDesignator * p = pCurrent;
        pCurrent = pCurrent->pNext;
        TDesignator_Delete(p);
    }

}

void TDesignatorList_PushBack(TDesignatorList * pList, TDesignator * pItem)
{
    if (pList->pHead == NULL)
    {
        pList->pHead = pItem;
    }
    else
    {
        pList->pTail->pNext = pItem;
    }
    pList->pTail = pItem;
}

void TInitializerListItem_Destroy(TInitializerListItem * p) /*@default*/
{
    TDesignatorList_Destroy(&p->DesignatorList);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList);
}

TInitializerListItem * TInitializerListItem_Create() /*@default*/
{
    TInitializerListItem *p = (TInitializerListItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TDesignatorList_Init(&p->DesignatorList);
        p->pInitializer = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList);
        p->bDefault = false;
    }
    return p;
}
void TInitializerListItem_Delete(TInitializerListItem * p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListItem_Destroy(p);
        Free((void*)p);
    }
}




TDeclaration * TProgram_FindDeclaration(TProgram * p, const char * name)
{
    TTypePointer * pt = SymbolMap_Find(&p->GlobalScope, name);
    if (pt != NULL &&
        pt->Type == TDeclaration_ID)
    {
        return (TDeclaration *)pt;
    }
    return NULL;
    
}

TDeclaration * TProgram_FindFunctionDeclaration(TProgram * p, const char * name)
{
    TTypePointer * pt = SymbolMap_Find(&p->GlobalScope, name);
    if (pt != NULL &&
        pt->Type == TDeclaration_ID)
    {
        return (TDeclaration *)pt;
    }
    return NULL;
}




TDeclaration * TProgram_GetFinalTypeDeclaration(TProgram * p, const char * typeName)
{
    return SymbolMap_FindTypedefDeclarationTarget(&p->GlobalScope, typeName);
}


void TProgram_Init(TProgram * p) /*@default*/
{
    TDeclarations_Init(&p->Declarations);
    TFileArray_Init(&p->Files2);
    SymbolMap_Init(&p->GlobalScope);
    MacroMap_Init(&p->Defines);
    StrBuilder_Init(&p->sbPreDeclaration);
}


void TProgram_Destroy(TProgram * p) /*@default*/
{
    TDeclarations_Destroy(&p->Declarations);
    TFileArray_Destroy(&p->Files2);
    SymbolMap_Destroy(&p->GlobalScope);
    MacroMap_Destroy(&p->Defines);
    StrBuilder_Destroy(&p->sbPreDeclaration);
}





static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
    int * pResult)
{

    int result = *pResult;

    if (p->pExpressionLeft)
    {
        int left;
        EvaluateConstantExpression(p->pExpressionLeft, &left);
    }

    
    {
        
        
        
    }

    switch (p->token)
    {
    case TK_FULL_STOP:
        
        
        break;
    case TK_ARROW:
        
        
        
        break;

    case TK_LEFT_SQUARE_BRACKET:
    {
        int index;
        
        EvaluateConstantExpression(p->pExpressionRight, &index);
        
        
    }
    break;

    case TK_LEFT_PARENTHESIS:
    {
        EvaluateConstantExpression(p->pExpressionRight, &result);
    }
    break;

    case TK_PLUSPLUS:
        
        break;
    case TK_MINUSMINUS:
        
        break;
    default:
        
        break;
    }



    if (p->pNext)
    {
        int result2 = result;
        TPostfixExpressionCore_CodePrint2(p->pNext, &result2);
        result = result2;
    }

    return true;
}



bool EvaluateConstantExpression(TExpression * p, int * pResult)
{
    int result = -987654321;

    if (p == NULL)
    {
        return false;
    }
    bool b = false;

    switch (p->Type)
    {
        CASE(TBinaryExpression) :
        {
            TBinaryExpression * pBinaryExpression =
                (TBinaryExpression *)p;

            int left;
            b = EvaluateConstantExpression(pBinaryExpression->pExpressionLeft, &left);

            int right;
            b = EvaluateConstantExpression(pBinaryExpression->pExpressionRight, &right);

            switch (pBinaryExpression->token)
            {
            case TK_ASTERISK:
                result = (left * right);
                b = true;
                break;
            case TK_PLUS_SIGN:
                result = (left + right);
                b = true;
                break;
            case TK_HYPHEN_MINUS:
                result = (left - right);
                b = true;
                break;
            case TK_ANDAND:
                result = (left && right);
                b = true;
                break;
            case TK_OROR:
                result = (left || right);
                b = true;
                break;
            case TK_NOTEQUAL:
                result = (left != right);
                b = true;
                break;
            case TK_EQUALEQUAL:
                result = (left == right);
                b = true;
                break;
            case TK_GREATEREQUAL:
                result = (left >= right);
                b = true;
                break;
            case TK_LESSEQUAL:
                result = (left <= right);
                b = true;
                break;
            case TK_GREATER_THAN_SIGN:
                result = (left > right);
                b = true;
                break;
            case TK_LESS_THAN_SIGN:
                result = (left < right);
                b = true;
                break;
            case TK_AMPERSAND:
                result = (left & right);
                b = true;
                break;
            case TK_GREATERGREATER:
                result = (left >> right);
                b = true;
                break;
            case TK_LESSLESS:
                result = (left << right);
                b = true;
                break;
            case TK_VERTICAL_LINE:
                result = (left | right);
                b = true;
                break;

            case TK_SOLIDUS:
                if (right != 0)
                {
                    result = (left / right);
                    b = true;
                }
                else
                {
                    b = false;
                    
                }
                break;


            default:
                
                
                b = false;
                break;
            }

            
        }
        break;

        CASE(TTernaryExpression) :
        {
            int e1, e2, e3;
            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionLeft, &e1);

            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionMiddle, &e2);

            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionRight, &e3);
            
        }
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue * pPrimaryExpressionValue =
                (TPrimaryExpressionValue *)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                b = EvaluateConstantExpression(pPrimaryExpressionValue->pExpressionOpt, &result);
            }
            else
            {
                switch (pPrimaryExpressionValue->token)
                {
                case TK_IDENTIFIER:
                    result = 0; 
                    b = true;
                    break;

                case TK_DECIMAL_INTEGER:
                    result = atoi(pPrimaryExpressionValue->lexeme);
                    b = true;
                    break;

                case TK_HEX_INTEGER:
                    result = strtol(pPrimaryExpressionValue->lexeme, NULL, 16);
                    b = true;
                    break;

                case TK_CHAR_LITERAL:
                    if (pPrimaryExpressionValue->lexeme != NULL)
                    {
                        
                        result = pPrimaryExpressionValue->lexeme[1];
                        b = true;
                    }
                    else
                    {
                        result = 0;
                    }
                    break;
                default:
                    b = false;
                    
                    break;
                }

            }
        }
        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore * pPostfixExpressionCore =
                (TPostfixExpressionCore *)p;
            b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
            
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {

            TUnaryExpressionOperator * pTUnaryExpressionOperator =
                (TUnaryExpressionOperator *)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {

                
                {

                    
                    
                    


                }
                
                {
                    b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionRight, &result);
                }
            }
            else
            {
                int localResult;
                b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionRight, &localResult);
                switch (pTUnaryExpressionOperator->token)
                {
                case TK_EXCLAMATION_MARK:
                    result = !localResult;
                    b = true;
                    break;
                case TK_HYPHEN_MINUS:
                    result = -localResult;
                    b = true;
                    break;
                default:
                    
                    break;
                }
            }


        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType *)p;


            
            
            

            b = EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
            

        }
        break;

    default:
        
        break;
    }

    
    *pResult = result;
    return b;
}



TDeclarationSpecifiers * TDeclaration_GetArgTypeSpecifier(TDeclaration * p, int index)
{
    TDeclarationSpecifiers * pResult = NULL;
    TParameterTypeList * pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
    {
        if (n == index)
        {
            pResult = &pItem->Specifiers;
            break;
        }
        n++;
    }
    return pResult;
}

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration * p)
{
    TParameterTypeList * pParameterTypeList = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
                    {
                        pParameterTypeList =
                            &p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Parameters;

                    }
                }
            }
        }
    }
    return pParameterTypeList;
}


const char * TDeclaration_FindFunctionTagName(TDeclaration * p, struct SymbolMap * pMap)
{
    if (p->FunctionTag)
        return p->FunctionTag;
    const char * funcName = TDeclaration_GetFunctionName(p);
    if (funcName)
    {
        struct SymbolMapItem * pBucket = SymbolMap_FindBucket(pMap, funcName);

        while (pBucket)
        {
            if (pBucket->pValue->Type == TDeclaration_ID &&
                strcmp(pBucket->Key, funcName) == 0)
            {
                TDeclaration * pDeclaration = (TDeclaration *)pBucket->pValue;
                if (pDeclaration->FunctionTag)
                    return pDeclaration->FunctionTag;
            }
            pBucket = pBucket->pNext;
        }
    }
    return NULL;
}

const char * TDeclaration_GetFunctionName(TDeclaration * p)
{
    if (p == NULL)
        return NULL;

    const char * functionName = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
                    {
                        functionName =
                            p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
                    }
                }
            }
        }
    }
    return functionName;
}

TCompoundStatement * TDeclaration_Is_FunctionDefinition(TDeclaration * p)
{
    TCompoundStatement * pCompoundStatement = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
                    {
                        pCompoundStatement = p->pCompoundStatementOpt;
                    }
                }
            }
        }
    }
    return pCompoundStatement;
}

TStructUnionSpecifier * TDeclarationSpecifiers_Find_StructUnionSpecifier(TDeclarationSpecifiers * p)
{
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;

    for (int i = 0; i < p->Size; i++)
    {
        TDeclarationSpecifier * pDeclarationSpecifier = p->pData[i];

        pStructUnionSpecifier =
            TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclarationSpecifier);
        if (pStructUnionSpecifier)
        {
            break;
        }
    }
    return pStructUnionSpecifier;
}

TStructUnionSpecifier * TParameter_Is_DirectPointerToStruct(TProgram * program, TParameter * pParameter)
{
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (TParameter_IsDirectPointer(pParameter))
    {
        const char * typedefName = TParameter_GetTypedefName(pParameter);
        if (typedefName != NULL)
        {
            TDeclaration * pArgType = TProgram_FindDeclaration(program, TParameter_GetTypedefName(pParameter));
            if (pArgType)
            {
                pStructUnionSpecifier =
                    TDeclarationSpecifiers_Find_StructUnionSpecifier(&pArgType->Specifiers);
            }
        }
    }
    return pStructUnionSpecifier;
}

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList * p)
{
    TPrimaryExpressionLiteralItem * pCurrent = p->pHead;
    while (pCurrent)
    {
        TPrimaryExpressionLiteralItem * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TPrimaryExpressionLiteralItem_Delete(pItem);
    }
}

void TPrimaryExpressionLiteralItemList_Add(TPrimaryExpressionLiteralItemList * pList, TPrimaryExpressionLiteralItem * pItem)
{
    if (pList->pHead == NULL)
    {
        pList->pHead = pItem;
        pList->pTail = pItem;
    }
    else
    {
        pList->pTail->pNext = pItem;
        pList->pTail = pItem;
    }

}

const char * TDeclaration_GetArgName(TDeclaration * p, int index)
{
    const char * argName = NULL;
    TParameterTypeList * pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
    {
        if (n == index)
        {
            argName = TParameter_GetName(pItem);
            break;
        }
        n++;
    }
    return argName;
}


int TDeclaration_GetNumberFuncArgs(TDeclaration * p)
{
    TParameterTypeList * pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
    {
        n++;
    }
    return n;
}






TDirectDeclarator * TDirectDeclarator_Create() /*@default*/
{
    TDirectDeclarator *p = (TDirectDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Identifier = NULL;
        p->pDeclarator = NULL;
        p->pDirectDeclarator = NULL;
        p->Position.FileIndex = 0;
        p->Position.Line = 0;
        TParameterTypeList_Init(&p->Parameters);
        p->pExpression = NULL;
        p->DeclaratorType = TDirectDeclaratorTypeNone;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}


TTypeName * TTypeName_Create() /*@default*/
{
    TTypeName *p = (TTypeName*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeName_Init(p);
    }
    return p;
}


void TTypeName_Destroy(TTypeName * p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TDeclarator_Destroy(&p->Declarator);
}

void TTypeName_Delete(TTypeName * p) /*@default*/
{
    if (p != NULL)
    {
        TTypeName_Destroy(p);
        Free((void*)p);
    }
}


TAtomicTypeSpecifier * TAtomicTypeSpecifier_Create() /*@default*/
{
    TAtomicTypeSpecifier *p = (TAtomicTypeSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAtomicTypeSpecifier_ID;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}




TPostfixExpressionCore * TPostfixExpressionCore_Create() /*@default*/
{
    TPostfixExpressionCore *p = (TPostfixExpressionCore*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPostfixExpressionCore_ID;
        p->token = TK_NONE;
        p->lexeme = NULL;
        p->pExpressionLeft = NULL;
        p->pExpressionRight = NULL;
        p->pNext = NULL;
        TInitializerList_Init(&p->InitializerList);
        p->Identifier = NULL;
        p->pTypeName = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

TCastExpressionType * TCastExpressionType_Create() /*@default*/
{
    TCastExpressionType *p = (TCastExpressionType*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCastExpressionType_ID;
        p->pExpression = NULL;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


TUnaryExpressionOperator * TUnaryExpressionOperator_Create() /*@default*/
{
    TUnaryExpressionOperator *p = (TUnaryExpressionOperator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TUnaryExpressionOperator_ID;
        p->token = TK_NONE;
        p->pExpressionRight = NULL;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}











bool Array_Reserve(Array * p, int nelements)
{
    bool result = true;
    if (nelements > p->capacity)
    {
        void ** pnew = p->pItems;
        pnew = (void **)Realloc(pnew, nelements * sizeof(void *));
        if (pnew)
        {
            p->pItems = pnew;
            p->capacity = nelements;
        }
        else
        {
            result = false  ;
        }
    }
    return result;
}


bool Array_Grow(Array * p, int nelements)
{
    bool result = true;
    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;
        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }
        result = Array_Reserve(p, new_nelements);
    }
    return result;
}


void * Array_PopGet(Array * p)
{
    void * pItem = 0;
    if (p->size > 0)
    {
        pItem = p->pItems[p->size - 1];
        p->pItems[p->size - 1] = NULL;
        p->size--;
    }
    else
    {
        
    }
    return pItem;
}

void Array_Pop(Array * p, void(*pfDestroyData)(void *))
{
    void * pItem = Array_PopGet(p);
    if (pfDestroyData)
    {
        pfDestroyData(pItem);
    }
}

void * Array_Top(Array * p)
{
    
    return p->pItems[p->size - 1];
}

bool Array_Push(Array * p, void * pItem)
{
    bool result = Array_Grow(p, p->size + 1);
    if (result == true)
    {
        p->pItems[p->size] = pItem;
        p->size++;
    }
    return result;
}

void Array_Clear(Array * p, void(*pfDestroyData)(void *))
{
    for (int i = 0; i < p->size; i++)
    {
        if (pfDestroyData)
            pfDestroyData(p->pItems[i]);
    }
    Free(p->pItems);
    p->pItems = NULL;
    p->size = 0;
    p->capacity = 0;
}


void Array_Init(Array * p)
{
    p->capacity = 0;
    p->size = 0;
    p->pItems = NULL;
}

void Array_Destroy(Array * st, void (*pfDestroyData)(void *))
{
    Array_Clear(st, pfDestroyData);
}

void Array_Swap(Array * p1, Array * p2)
{
    int c = p1->capacity;
    int s = p1->size;
    void ** pp = p1->pItems;
    p1->capacity = p2->capacity;
    p1->size = p2->size;
    p1->pItems = p2->pItems;
    p2->capacity = c;
    p2->size = s;
    p2->pItems = pp;
}


bool StrArray_Reserve(struct StrArray * p, int nelements)
{
    return Array_Reserve((Array *)p, nelements);
}

bool StrArray_Push(struct StrArray * p, const char * pItem)
{
    char * s = StrDup(pItem);

    {
        bool result = Array_Push((Array *)p, s);
        if (result != true)
        {
            Free(s);
        }
    }
    return true;
}

static void Array_DeleteStrVoid(void * p)
{
    Free(p);
    
}

void StrArray_Clear(struct StrArray * p)
{
    Array_Clear((Array *)p, Array_DeleteStrVoid);
}

void StrArray_Init(struct StrArray * p)
{
    Array_Init((Array *)p);
}

void StrArray_Destroy(struct StrArray * p)
{
    Array_Destroy((Array *)p, &Array_DeleteStrVoid);
}

void StrArray_Swap(struct StrArray * p1, struct StrArray * p2)
{
    struct StrArray temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}



void * Array_PopFront(Array * p)
{
    void * pItem = NULL;
    
    if (p->size > 0)
    {
        pItem = p->pItems[0];
        if (p->size > 1)
        {
            memmove(p->pItems, p->pItems + 1, sizeof(void *) * (p->size - 1));
        }
        p->size--;
    }
    return pItem;
}






#include <ctype.h>


char * StrDup(const char * p)
{
    char * a = 0;
    if (p)
    {
        a = Malloc(strlen(p) + 1);
        if (a)
            strcpy(a, p);
    }
    else
    {
        a = Malloc(1);
        if (a)
        {
            a[0] = '\0';
        }
    }
    return a;
}

int StrIComp(char const* a, char const* b)
{
    for (;; a++, b++)
    {
        int d = tolower((unsigned char)* a) - tolower((unsigned char)* b);
        if (d != 0 || !*a)
            return d;
    }
}

char* StrIStr(const char* str1, const char* str2)
{
    const char* p1 = str1;
    const char* p2 = str2;
    const char* r = *p2 == 0 ? str1 : 0;

    while (*p1 != 0 && *p2 != 0)
    {
        if (tolower((unsigned char)* p1) == tolower((unsigned char)* p2))
        {
            if (r == 0)
            {
                r = p1;
            }

            p2++;
        }
        else
        {
            p2 = str2;
            if (r != 0)
            {
                p1 = r + 1;
            }

            if (tolower((unsigned char)* p1) == tolower((unsigned char)* p2))
            {
                r = p1;
                p2++;
            }
            else
            {
                r = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}

bool IsSuffix(const char * s, const char * suffix)
{
    bool bResult = false;
    int len = (int)strlen(s);
    int len2 = (int)strlen(suffix);
    if (len > len2)
    {
        const char * pEndPart = &s[len - len2];
        if (StrIComp(pEndPart, suffix) == 0) 
        {
            bResult = true;
        }
    }
    return bResult;

}







#if _DEBUG
#include <crtdbg.h>

void * DebugMalloc(const char * fileName, int line, size_t size)
{
    void * p = _malloc_dbg(size, _CLIENT_BLOCK, fileName, line);
    assert(p);
    return p;
}

void Free(void * ptr)
{
    _free_dbg(ptr, _CLIENT_BLOCK);
}
void * DebugRealloc(const char * fileName, int line, void * ptr, size_t new_size)
{
    void * p = _realloc_dbg(ptr, new_size, _CLIENT_BLOCK, fileName, line);
    assert(p);
    return p;
}

void PrintMemory()
{
    _CrtMemDumpAllObjectsSince(NULL);
}
#else
void PrintMemory() {}
#endif











struct FileNode * FileNode_Create(const char * key)
{
    struct FileNode * p = (struct FileNode *) Malloc(sizeof * p);
    if (p)
    {
        int len = strlen(key);
        p->Key = Malloc(len + 1);
        if (p->Key)
        {
            strcpy(p->Key, key);
            p->Key[len] = 0;
        }

        p->pNext = 0;
    }
    return p;
}

void FileNode_Free(struct FileNode * p)
{
    
    if (p != NULL)
    {
        Free((void *)p->Key);
        Free((void *)p);
    }
}
void FileNode_Delete(struct FileNode * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Key);
        FileNode_Delete(p->pNext);
        Free((void*)p);
    }
}



void FileNodeMap_Destroy(struct FileNodeMap * p) /*@default*/
{
    for (int i = 0; i < p->Capacity; i++)
    {
        FileNode_Delete(p->pNodes[i]);
    }
    Free((void*)p->pNodes);
}

static unsigned int HashCode(const char * Key)
{
    
    
    unsigned int uHashVal = 2166136261U;
    unsigned int uFirst = 0;
    unsigned int uLast = (unsigned int)strlen(Key);
    unsigned int uStride = 1 + uLast / 10;

    for (; uFirst < uLast; uFirst += uStride)
    {
        uHashVal = 16777619U * uHashVal ^ (unsigned int)Key[uFirst];
    }

    return (uHashVal);
}


struct FileNode * FileNodeMap_Lookup(struct FileNodeMap * t, const char * key)
{
    if (t->pNodes == NULL)
        return NULL;
    unsigned int pos = HashCode(key) % t->Capacity;
    struct FileNode * temp = t->pNodes[pos];
    while (temp)
    {
        if (strcmp(temp->Key, key) == 0)
        {
            return temp;
        }
        temp = temp->pNext;
    }
    return 0;

}

void FileNodeMap_Insert(struct FileNodeMap * t, struct FileNode * pNewNode)
{
    if (t->pNodes == NULL)
    {
        int capacity = t->Capacity;
        if (capacity == 0)
        {
            capacity = 100;
        }

        t->pNodes = (struct FileNode **)Malloc(sizeof(struct FileNode *) * capacity);
        if (t->pNodes != NULL)
        {
            memset(t->pNodes, 0, sizeof(struct FileNode *) * capacity);
            t->Capacity = capacity;
        }
        else
        {
            
            return;
        }
    }

    assert(FileNodeMap_Lookup(t, pNewNode->Key) == NULL);

    int pos = HashCode(pNewNode->Key) % t->Capacity;
    struct FileNode * pList = t->pNodes[pos];
    struct FileNode * pTemp = pList;
    pNewNode->pNext = pList;
    t->pNodes[pos] = pNewNode;
}

void FileNodeList_Init(struct FileNodeList * pItems)
{
    pItems->pHead = 0;
    pItems->pTail = 0;
}

void FileNodeList_Swap(struct FileNodeList * a, struct FileNodeList * b)
{
    struct FileNodeList t = *a;
    *a = *b;
    *b = t;
}


void FileNodeList_Destroy(struct FileNodeList * pItems) /*@default*/
{
    FileNode_Delete(pItems->pHead);
}

void FileNodeList_PushBack(struct FileNodeList * pItems,
    const char * fileName)
{
    struct FileNode * pItem = FileNode_Create(fileName);
    if (pItems->pHead == 0)
    {
        pItems->pHead = pItem;
    }
    else
    {
        pItems->pTail->pNext = pItem;
    }
    pItems->pTail = pItem;
}

void FileNodeList_PushItem(struct FileNodeList * pItems,
    struct FileNode * pItem)
{
    if (pItems->pHead == 0)
    {
        pItems->pHead = pItem;
    }
    else
    {
        pItems->pTail->pNext = pItem;
    }
    pItems->pTail = pItem;
}

BasicScanner * Scanner_Top(Scanner * pScanner);

void Scanner_MatchDontExpand(Scanner * pScanner);

enum PPTokenType TokenToPPToken(Tokens token)
{
    enum PPTokenType result = PPTokenType_Other;

    switch (token)
    {
        case TK_AUTO:

        case TK_BREAK:
        case TK_CASE:
        case TK_CHAR:
        case TK_CONST:
        case TK_CONTINUE:
        case TK_DEFAULT:

        case TK_DO:
        case TK_DOUBLE:
        case TK_ELSE:
        case TK_ENUM:
        case TK_EXTERN:
        case TK_FLOAT:
        case TK_FOR:
        case TK_GOTO:
        case TK_IF:
        case TK_INT:
        case TK_LONG:
        
        
        case TK__INT8:
        case TK__INT16:
        case TK__INT32:
        case TK__INT64:
        case TK__WCHAR_T:
        
        case TK_REGISTER:
        case TK_RETURN:
        case TK_SHORT:
        case TK_SIGNED:
        case TK_SIZEOF:
        case TK_STATIC:
        case TK_STRUCT:
        case TK_SWITCH:
        case TK_TYPEDEF:
        case  TK_UNION:
        case TK_UNSIGNED:
        case TK_VOID:
        case TK_VOLATILE:
        case TK_WHILE:
        case TK__THREAD_LOCAL:
        case TK__BOOL:
        case TK__COMPLEX:
        case TK__ATOMIC:
        case TK_RESTRICT:
        case TK__STATIC_ASSERT:
        case TK_INLINE:
        case TK__INLINE:
        case TK__FORCEINLINE: 
        case TK__NORETURN:
        case TK__ALIGNAS:
        case TK__GENERIC:
        case  TK__IMAGINARY:
        case TK__ALINGOF:
        case TK_IDENTIFIER:
        result = PPTokenType_Identifier;
        break;

        case TK_LINE_COMMENT:
        case TK_COMMENT:
        case TK_OPEN_COMMENT:
        case TK_CLOSE_COMMENT:
        case TK_SPACES:
        result = PPTokenType_Spaces;
        break;

        case TK_HEX_INTEGER:
        case TK_DECIMAL_INTEGER:
        case TK_FLOAT_NUMBER:
        result = PPTokenType_Number;
        break;

        case TK_CHAR_LITERAL:
        result = PPTokenType_CharConstant;
        break;

        case TK_STRING_LITERAL:
        result = PPTokenType_StringLiteral;
        break;

        case TK_ARROW:
        case TK_PLUSPLUS:
        case TK_MINUSMINUS:
        case TK_LESSLESS:
        case TK_GREATERGREATER:
        case TK_LESSEQUAL:
        case TK_GREATEREQUAL:
        case TK_EQUALEQUAL:
        case TK_NOTEQUAL:
        case TK_ANDAND:
        case TK_OROR:
        case TK_MULTIEQUAL:
        case TK_DIVEQUAL:
        case TK_PERCENT_EQUAL:
        case TK_PLUSEQUAL:
        case TK_MINUS_EQUAL:
        case TK_ANDEQUAL:
        case TK_CARETEQUAL:
        case TK_OREQUAL:
        case TK_NUMBERNUMBER:
        case TK_LESSCOLON:
        case TK_COLONGREATER:
        case TK_LESSPERCENT:
        case TK_PERCENTGREATER:
        case TK_PERCENTCOLON:
        case TK_DOTDOTDOT:
        case TK_GREATERGREATEREQUAL:
        case TK_LESSLESSEQUAL:
        case TK_PERCENTCOLONPERCENTCOLON:

        case     TK_EXCLAMATION_MARK:
        case    TK_QUOTATION_MARK:
        case    TK_NUMBER_SIGN:

        case    TK_DOLLAR_SIGN:
        case     TK_PERCENT_SIGN:
        case    TK_AMPERSAND:
        case     TK_APOSTROPHE:
        case    TK_LEFT_PARENTHESIS:
        case    TK_RIGHT_PARENTHESIS:
        case    TK_ASTERISK:
        case    TK_PLUS_SIGN:
        case    TK_COMMA:
        case    TK_HYPHEN_MINUS:
        case    TK_HYPHEN_MINUS_NEG:
        case    TK_FULL_STOP:
        case    TK_SOLIDUS:

        case    TK_COLON:
        case    TK_SEMICOLON:
        case    TK_LESS_THAN_SIGN:
        case    TK_EQUALS_SIGN:
        case    TK_GREATER_THAN_SIGN:
        case    TK_QUESTION_MARK:
        case    TK_COMMERCIAL_AT:

        case     TK_LEFT_SQUARE_BRACKET:
        case    REVERSE_SOLIDUS:
        case     TK_RIGHT_SQUARE_BRACKET:
        case    TK_CIRCUMFLEX_ACCENT:
        case    TK_LOW_LINE:
        case    TK_GRAVE_ACCENT:

        case    TK_LEFT_CURLY_BRACKET:
        case    TK_VERTICAL_LINE:
        case    TK_RIGHT_CURLY_BRACKET:
        case    TK_TILDE: 

        result = PPTokenType_Punctuator;
        break;
        default:
        
        result = PPTokenType_Punctuator;
        break;
    }

    return result;
}

TFile * TFile_Create() /*@default*/
{
    TFile *p = (TFile*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->FullPath = NULL;
        p->IncludePath = NULL;
        p->FileIndex = 0;
        p->PragmaOnce = false;
        p->bDirectInclude = false;
        p->bSystemLikeInclude = false;
    }
    return p;
}

void TFile_Destroy(TFile * p) /*@default*/
{
    Free((void*)p->FullPath);
    Free((void*)p->IncludePath);
}

void TFile_Delete(TFile * p) /*@default*/
{
    if (p != NULL)
    {
        TFile_Destroy(p);
        Free((void*)p);
    }
}

void TFile_DeleteVoid(void * p)
{
    TFile_Delete((TFile *)p);
}

void TFileMap_Destroy(TFileMap * p)
{
    Map_Destroy(p, TFile_DeleteVoid);
}

void TFileArray_Init(TFileArray * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void TFileArray_Destroy(TFileArray * p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TFile_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}

void TFileArray_Reserve(TFileArray * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TFile** pnew = p->pItems;
        pnew = (TFile**)Realloc(pnew, n * sizeof(TFile*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}

void TFileArray_PushBack(TFileArray * p, TFile * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TFileArray_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

bool TFileMap_Set(TFileMap * map, const char * key, TFile * pFile)
{
    
    
    
    
    pFile->FileIndex = map->Size;
    bool result = Map_Set(map, key, pFile);
    PTR_STRING_REPLACE(pFile->FullPath, key);
    return result;
}

TFile * TFileMap_Find(TFileMap * map, const char * key)
{
    
    return (TFile *)Map_Find2(map, key);
}

bool TFileMap_DeleteItem(TFileMap * map, const char * key)
{
    return Map_DeleteItem(map, key, TFile_DeleteVoid);
}



bool IsIncludeState(enum PPState e)
{
    return e == PPState_NONE || e == PPState_I1 || e == PPState_E1;
}

void StackInts_Init(StackInts * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void StackInts_Destroy(StackInts * p)
{
    Free(p->pItems);
}

void StackInts_Pop(StackInts * p)
{
    if (p->Size > 0)
    {
        p->Size--;
    }
}

void StackInts_Reserve(StackInts * p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        enum PPState* pnew = p->pItems;
        pnew = (enum PPState*)Realloc(pnew, n * sizeof(enum PPState));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}

void StackInts_PushBack(StackInts * p, enum PPState e) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        StackInts_Reserve(p, n);
    }
    p->pItems[p->Size] = e;
    p->Size++;
}

enum PPState StateTop(Scanner * pScanner)
{
    if (pScanner->StackIfDef.Size == 0)
        return PPState_NONE;

    return pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1];
}

void StatePush(Scanner * pScanner, enum PPState s)
{
    StackInts_PushBack(&pScanner->StackIfDef, s);
}

void StatePop(Scanner * pScanner)
{
    StackInts_Pop(&pScanner->StackIfDef);
}

void Scanner_GetError(Scanner * pScanner, StrBuilder * str)
{
    StrBuilder_Append(str, pScanner->DebugString.c_str);
    StrBuilder_Append(str, "\n");

    ForEachBasicScanner(p, pScanner->stack)
    {
        StrBuilder_AppendFmt(str, "%s(%d)\n",
            p->stream.NameOrFullPath,
            p->stream.Line);
    }
}


void Scanner_GetFilePositionString(Scanner * pScanner, StrBuilder * sb)
{
    BasicScanner * pScannerTop = Scanner_Top(pScanner);

    if (pScannerTop != NULL)
    {
        StrBuilder_Set(sb,
            pScannerTop->stream.NameOrFullPath);
    }

    if (pScannerTop)
    {
        StrBuilder_AppendFmt(sb, "(%d): ", pScannerTop->stream.Line);
    }
    else
    {
        StrBuilder_Append(sb, "(1): ");
    }
}

void Scanner_SetError(Scanner * pScanner, const char * fmt, ...)
{
    if (!pScanner->bError)
    {
        pScanner->bError = true;

        if (Scanner_Top(pScanner))
        {
            StrBuilder_AppendFmt(&pScanner->ErrorString, "%s(%d) :",
                Scanner_Top(pScanner)->stream.NameOrFullPath,
                Scanner_Top(pScanner)->stream.Line);
        }
        else
        {
            StrBuilder_Append(&pScanner->ErrorString, "(0) :");
        }


        va_list args;
        va_start(args, fmt);
        StrBuilder_AppendFmtV(&pScanner->ErrorString, fmt, args);
        va_end(args);
    }
}

void Scanner_PrintDebug(Scanner * pScanner)
{
    printf("include stack---\n");

    ForEachBasicScanner(p, pScanner->stack)
    {
        printf("%s(%d):\n", p->stream.NameOrFullPath, p->stream.Line);
    }

    printf("---\n");
}

static bool AddStandardMacro(Scanner * pScanner, const char * name,
    const char * value)
{
    struct Macro * pDefine1 = Macro_Create();
    PTR_STRING_REPLACE(pDefine1->Name, name);
    
    TokenArray_PushBack(&pDefine1->TokenSequence,
        PPToken_Create(value, PPTokenType_Other));
    pDefine1->FileIndex = 0;
    MacroMap_SetAt(&pScanner->Defines2, name, pDefine1);
    return true;
}
static void Scanner_PushToken(Scanner * pScanner, Tokens token,
    const char * lexeme, bool bActive);

static bool Scanner_InitCore(Scanner * pScanner)
{

    TScannerItemList_Init(&pScanner->AcumulatedTokens);
    pScanner->pOptions = NULL;
    
    
    Map_Init(&pScanner->FilesIncluded, 100);
    MacroMap_Init(&pScanner->Defines2);
    StrBuilder_Init(&pScanner->DebugString);

    StrBuilder_Init(&pScanner->ErrorString);

    pScanner->bError = false;
    StackInts_Init(&pScanner->StackIfDef);

    BasicScannerStack_Init(&pScanner->stack);

    StrArray_Init(&pScanner->IncludeDir);
    FileNodeList_Init(&pScanner->Sources);

    
    
    

    
    
    
    
    
    AddStandardMacro(pScanner, "__LINE__", "0");
    AddStandardMacro(pScanner, "__FILE__", "\"__FILE__\"");
    AddStandardMacro(pScanner, "__DATE__", "\"__DATE__\"");
    AddStandardMacro(pScanner, "__TIME__", "\"__TIME__\"");
    AddStandardMacro(pScanner, "__STDC__", "1");
    AddStandardMacro(pScanner, "__COUNTER__", "0");
    

    Scanner_PushToken(pScanner, TK_BOF, "", true);

    return true;
}

bool Scanner_InitString(Scanner * pScanner, const char * name,
    const char * Text)
{
    Scanner_InitCore(pScanner);

    BasicScanner * pNewScanner;
    bool result =
        BasicScanner_Create(&pNewScanner, name, Text, BasicScannerType_Macro);
    BasicScannerStack_Push(&pScanner->stack, pNewScanner);
    return result;
}

bool PushExpandedMacro(Scanner * pScanner,

    const char * callString,
    const char * defineContent)
{
    if (pScanner->bError)
    {
        return false;
    }

    BasicScanner * pNewScanner;
    bool result = BasicScanner_Create(&pNewScanner, callString,  
        defineContent, BasicScannerType_Macro);

    if (result == true)
    {
        pNewScanner->bMacroExpanded = true;
        BasicScanner_Match(pNewScanner); 
        BasicScannerStack_Push(&pScanner->stack, pNewScanner);
    }

    return result;
}

bool Scanner_GetFullPath(Scanner * pScanner, const char * fileName,
    bool bQuotedForm, String * /*@auto*/ *fullPathOut)
{
    if (pScanner->bError)
    {
        return false;
    }

    bool bFullPathFound = false;

    
     
    if (bQuotedForm)
    {
        
        
        
        if (IsFullPath(fileName))
        {
            
            
            bFullPathFound = true;
            PTR_STRING_REPLACE(*fullPathOut, fileName);
        }
        else
        {
            if (pScanner->stack != NULL)
            {
                
                StrBuilder path = STRBUILDER_INIT;

                
                ForEachBasicScanner(p, pScanner->stack)
                {
                    
                    StrBuilder_Set(&path, p->stream.FullDir2);
                    StrBuilder_Append(&path, fileName);
                    bool bFileExists = FileExists(path.c_str);

                    if (bFileExists)
                    {
                        GetFullPath(path.c_str, fullPathOut);
                        
                        bFullPathFound = true;
                        break;
                    }
                }

                StrBuilder_Destroy(&path);
            }
            else
            {
                
                String * /*@auto*/ fullPath = NULL;

                GetFullPath(fileName, &fullPath);
                bool bFileExists = FileExists(fullPath);

                if (bFileExists)
                {
                    PTR_SWAP(fullPath, *fullPathOut);
                    bFullPathFound = true;
                }

                Free(fullPath);
            }
        }
    }

     
    if (!bFullPathFound)
    {
        StrBuilder path = STRBUILDER_INIT;


        for (int i = 0; i < pScanner->IncludeDir.size; i++)
        {
            const char * pItem = pScanner->IncludeDir.pItems[i];
            StrBuilder_Set(&path, pItem);

            
            
            StrBuilder_Append(&path, "/");

            StrBuilder_Append(&path, fileName);
            bool bFileExists = FileExists(path.c_str);

            if (bFileExists)
            {
                PTR_STRING_REPLACE(*fullPathOut, path.c_str);
                bFullPathFound = true;
                break;
            }
        }

        StrBuilder_Destroy(&path);
    }

    return bFullPathFound;
}

bool Scanner_IsAlreadyIncluded(Scanner * pScanner,
    const char * includeFileName,
    FileIncludeType fileIncludeType)
{
    bool bResult = false;
    String * /*@auto*/ fullPath = NULL;
    bool bHasFullPath = false;

    switch (fileIncludeType)
    {
        case FileIncludeTypeQuoted:
        case FileIncludeTypeIncludes:
        bHasFullPath = Scanner_GetFullPath(pScanner, includeFileName,
            fileIncludeType == FileIncludeTypeQuoted,
            &fullPath);
        break;

        case FileIncludeTypeFullPath:
        PTR_STRING_REPLACE(fullPath, includeFileName);
        bHasFullPath = true;
        break;
    };

    if (bHasFullPath)
    {
        TFile * pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

        if (pFile != NULL)
        {
            bResult = true;
        }
    }
    Free(fullPath);
    return bResult;
}

void Scanner_IncludeFile(Scanner * pScanner,
    const char * includeFileName,
    FileIncludeType fileIncludeType,
    bool bSkipBof)
{
    if (pScanner->bError)
    {
        return;
    }

    bool bDirectInclude = false;

    String * /*@auto*/ fullPath = NULL;

    
    
    
    bool bHasFullPath = false;

    switch (fileIncludeType)
    {
        case FileIncludeTypeQuoted:
        case FileIncludeTypeIncludes:
        bHasFullPath = Scanner_GetFullPath(pScanner, includeFileName,
            fileIncludeType == FileIncludeTypeQuoted,
            &fullPath);
        break;

        case FileIncludeTypeFullPath:
        PTR_STRING_REPLACE(fullPath, includeFileName);
        bHasFullPath = true;
        break;
    };

    if (bHasFullPath)
    {
        TFile * pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

        if (pFile != NULL && pFile->PragmaOnce)
        {
            
            
            if (pScanner->pOptions->bAmalgamate)
            {
                
                assert(false);
            }

            Scanner_PushToken(pScanner, TK_FILE_EOF, "pragma once file", true);
        }
        else
        {
            if (pFile == NULL)
            {
                pFile = TFile_Create();
                pFile->bDirectInclude = bDirectInclude;
                pFile->bSystemLikeInclude =
                    (fileIncludeType == FileIncludeTypeIncludes);
                PTR_STRING_REPLACE(pFile->IncludePath, includeFileName);
                TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile); 
            }

            BasicScanner * pNewScanner = NULL;
            bool result = BasicScanner_CreateFile(fullPath, &pNewScanner);

            if (result == true)
            {
                if (pFile)
                {
                    pNewScanner->FileIndex = pFile->FileIndex;

                    if (bSkipBof)
                    {
                        BasicScanner_Match(pNewScanner);
                    }

                    BasicScannerStack_Push(&pScanner->stack, pNewScanner);
                }
                else
                {
                    Scanner_SetError(pScanner, "mem");
                }
            }
            else
            {
                Scanner_SetError(pScanner, "Cannot open source file: '%s': No such file or directory", fullPath);
            }
        }
    }
    else
    {
        Scanner_SetError(pScanner, "Cannot open include file: '%s': No such file or directory", includeFileName);
    }

    Free(fullPath);
}

const char * Scanner_GetStreamName(Scanner * pScanner)
{
    const char * streamName = NULL;

    BasicScanner * p = Scanner_Top(pScanner);
    streamName = p ? p->stream.NameOrFullPath : NULL;

    return streamName;
}

bool Scanner_Init(Scanner * pScanner)
{
    return Scanner_InitCore(pScanner);
}

void Scanner_Destroy(Scanner * pScanner) /*@default*/
{
    BasicScannerStack_Destroy(&pScanner->stack);
    MacroMap_Destroy(&pScanner->Defines2);
    StackInts_Destroy(&pScanner->StackIfDef);
    TFileMap_Destroy(&pScanner->FilesIncluded);
    StrArray_Destroy(&pScanner->IncludeDir);
    FileNodeList_Destroy(&pScanner->Sources);
    StrBuilder_Destroy(&pScanner->DebugString);
    StrBuilder_Destroy(&pScanner->ErrorString);
    TScannerItemList_Destroy(&pScanner->AcumulatedTokens);
}

void Scanner_Reset(Scanner * pScanner)
{
    
    
    
    
    
    
    

    BasicScannerStack_Destroy(&pScanner->stack);
    BasicScannerStack_Init(&pScanner->stack);

    
    

    StackInts_Destroy(&pScanner->StackIfDef);
    StackInts_Init(&pScanner->StackIfDef);

    
    

    
    

    
    

    StrBuilder_Destroy(&pScanner->DebugString);
    StrBuilder_Init(&pScanner->DebugString);

    StrBuilder_Destroy(&pScanner->ErrorString);
    StrBuilder_Init(&pScanner->ErrorString);

    TScannerItemList_Destroy(&pScanner->AcumulatedTokens);
    TScannerItemList_Init(&pScanner->AcumulatedTokens);

    pScanner->bError = false;
}

 

int Scanner_GetFileIndex(Scanner * pScanner)
{
    if (pScanner->bError)
    {
        return -1;
    }

    int fileIndex = -1;

    ForEachBasicScanner(pBasicScanner, pScanner->stack)
    {
        fileIndex = pBasicScanner->FileIndex;

        if (fileIndex >= 0)
        {
            break;
        }
    }

    
    return fileIndex;
}

 

BasicScanner * Scanner_Top(Scanner * pScanner)
{
    return pScanner->stack;
}













void IgnorePreProcessorv2(BasicScanner * pBasicScanner, StrBuilder * strBuilder)
{

    while (pBasicScanner->currentItem.token != TK_EOF &&
        pBasicScanner->currentItem.token != TK_FILE_EOF)
    {
        if (pBasicScanner->currentItem.token == TK_BREAKLINE)
        {
            
            BasicScanner_Match(pBasicScanner);
            break;
        }
        StrBuilder_Append(strBuilder, pBasicScanner->currentItem.lexeme.c_str);
        BasicScanner_Match(pBasicScanner);
    }
}

void GetDefineString(Scanner * pScanner, StrBuilder * strBuilder)
{
    for (;;)
    {
        Tokens token = Scanner_Top(pScanner)->currentItem.token;

        if (token == TK_EOF)
        {
            break;
        }

        if (token == TK_BREAKLINE)
        {
            
            
            break;
        }

        if (token == TK_OPEN_COMMENT ||
            token == TK_CLOSE_COMMENT ||
            token == TK_COMMENT ||
            token == TK_LINE_COMMENT)
        {
            
            StrBuilder_Append(strBuilder, " ");
        }
        else
        {
            StrBuilder_Append(strBuilder, BasicScanner_Lexeme(Scanner_Top(pScanner)));
        }

        BasicScanner_Match(Scanner_Top(pScanner));
    }
}

struct Macro * Scanner_FindPreprocessorItem2(Scanner * pScanner, const char * key)
{
    struct Macro * pMacro = MacroMap_Find(&pScanner->Defines2, key);
    return pMacro;
}

bool Scanner_IsLexeme(Scanner * pScanner, const char * psz)
{
    return BasicScanner_IsLexeme(Scanner_Top(pScanner), psz);
}

int PreprocessorExpression(Parser * parser)
{
    
    TExpression * pExpression = NULL;
    ConstantExpression(parser, &pExpression);
    
    
    
    int r;
    if (!EvaluateConstantExpression(pExpression, &r))
    {
        Scanner_SetError(&parser->Scanner, "error evaluating expression");
    }

    TExpression_Delete(pExpression);
    return r;
}

int EvalExpression(const char * s, Scanner * pScanner)
{
    struct MacroMap * pDefines = &pScanner->Defines2;
    
    
    
    Parser parser;
    Parser_InitString(&parser, "eval expression", s);
    parser.bPreprocessorEvalFlag = true;

    if (pDefines)
    {
        
        MacroMap_Swap(&parser.Scanner.Defines2, pDefines);
    }

    
    int iRes = PreprocessorExpression(&parser);

    
    if (pDefines)
    {
        MacroMap_Swap(&parser.Scanner.Defines2, pDefines);
    }

    if (parser.bError)
    {
        Scanner_SetError(pScanner, parser.ErrorMessage.c_str);
    }

    if (parser.Scanner.bError)
    {
        Scanner_SetError(pScanner, parser.Scanner.ErrorString.c_str);
    }

    Parser_Destroy(&parser);
    return iRes;
}

static void GetMacroArguments(Scanner * pScanner, BasicScanner * pBasicScanner,
    struct Macro * pMacro, struct TokenArray * ppTokenArray,
    StrBuilder * strBuilder)
{
    
    
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;
    Tokens token = pBasicScanner->currentItem.token;

    
    int nArgsExpected = pMacro->FormalArguments.Size; 
    int nArgsFound = 0;

    

    if (token == TK_LEFT_PARENTHESIS)
    {
        
        struct PPToken * ppTokenName = PPToken_Create(pMacro->Name, PPTokenType_Identifier);
        TokenArray_PushBack(ppTokenArray, ppTokenName);

        
        struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
        TokenArray_PushBack(ppTokenArray, ppToken);

        StrBuilder_Append(strBuilder, lexeme);
        BasicScanner_Match(pBasicScanner);

        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;

        
        nArgsFound = 1;
        int iInsideParentesis = 1;

        for (;;)
        {
            if (token == TK_LEFT_PARENTHESIS)
            {

                struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));

                TokenArray_PushBack(ppTokenArray, ppToken);

                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);

                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;

                iInsideParentesis++;
            }
            else if (token == TK_RIGHT_PARENTHESIS)
            {
                if (iInsideParentesis == 1)
                {
                    struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
                    TokenArray_PushBack(ppTokenArray, ppToken);

                    StrBuilder_Append(strBuilder, lexeme);
                    BasicScanner_Match(pBasicScanner);

                    token = pBasicScanner->currentItem.token;
                    lexeme = pBasicScanner->currentItem.lexeme.c_str;

                    break;
                }

                iInsideParentesis--;

                struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
                TokenArray_PushBack(ppTokenArray, ppToken);

                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);

                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;
            }
            else if (token == TK_COMMA)
            {
                if (iInsideParentesis == 1)
                {
                    nArgsFound++;
                }
                else
                {
                    
                }

                
                struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
                TokenArray_PushBack(ppTokenArray, ppToken);

                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;
            }
            else
            {
                
                struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
                TokenArray_PushBack(ppTokenArray, ppToken);

                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;
            }
        }
    }

    if (nArgsExpected != nArgsFound)
    {
        if (nArgsFound == 0 && nArgsExpected > 0)
        {
            
        }
        else
        {
            if (nArgsExpected > nArgsFound)
            {
                
                
            }
            else
            {
                
                
            }
            
            
            
        }
    }

    
    
    

    
}

Tokens FindPreToken(const char * lexeme)
{
    Tokens token = TK_NONE;
    if (strcmp(lexeme, "include") == 0)
    {
        token = TK_PRE_INCLUDE;
    }
    else if (strcmp(lexeme, "pragma") == 0)
    {
        token = TK_PRE_PRAGMA;
    }
    else if (strcmp(lexeme, "if") == 0)
    {
        token = TK_PRE_IF;
    }
    else if (strcmp(lexeme, "elif") == 0)
    {
        token = TK_PRE_ELIF;
    }
    else if (strcmp(lexeme, "ifndef") == 0)
    {
        token = TK_PRE_IFNDEF;
    }
    else if (strcmp(lexeme, "ifdef") == 0)
    {
        token = TK_PRE_IFDEF;
    }
    else if (strcmp(lexeme, "endif") == 0)
    {
        token = TK_PRE_ENDIF;
    }
    else if (strcmp(lexeme, "else") == 0)
    {
        token = TK_PRE_ELSE;
    }
    else if (strcmp(lexeme, "error") == 0)
    {
        token = TK_PRE_ERROR;
    }
    else if (strcmp(lexeme, "line") == 0)
    {
        token = TK_PRE_LINE;
    }
    else if (strcmp(lexeme, "undef") == 0)
    {
        token = TK_PRE_UNDEF;
    }
    else if (strcmp(lexeme, "define") == 0)
    {
        token = TK_PRE_DEFINE;
    }
    return token;
}

void GetPPTokens(BasicScanner * pBasicScanner, struct TokenArray * pptokens,
    StrBuilder * strBuilder)
{
    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;

    
    while (token != TK_BREAKLINE && token != TK_EOF && token != TK_FILE_EOF)
    {
        StrBuilder_Append(strBuilder, lexeme);

        if (token != TK_BACKSLASHBREAKLINE)
        {
            
            struct       PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
            TokenArray_PushBack(pptokens, ppToken);
        }
        BasicScanner_Match(pBasicScanner);
        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;
    }

    
    while (pptokens->Size > 0 &&
        pptokens->pItems[pptokens->Size - 1]->Token == PPTokenType_Spaces)
    {
        TokenArray_Pop(pptokens);
    }
}

static void Scanner_MatchAllPreprocessorSpaces(BasicScanner * pBasicScanner,
    StrBuilder * strBuilder)
{
    Tokens token = pBasicScanner->currentItem.token;
    while (token == TK_SPACES || token == TK_BACKSLASHBREAKLINE ||
        token == TK_COMMENT ||
        token == TK_OPEN_COMMENT ||
        token == TK_CLOSE_COMMENT)
    {
        StrBuilder_Append(strBuilder, pBasicScanner->currentItem.lexeme.c_str);

        BasicScanner_Match(pBasicScanner);
        token = pBasicScanner->currentItem.token;
    }
}

void ParsePreDefinev2(Scanner * pScanner, StrBuilder * strBuilder)
{
    BasicScanner * pBasicScanner = Scanner_Top(pScanner);

    
    struct Macro * pNewMacro = Macro_Create();

    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;

    PTR_STRING_REPLACE(pNewMacro->Name, lexeme);
    StrBuilder_Append(strBuilder, lexeme);

    
    BasicScanner_Match(pBasicScanner);

    token = pBasicScanner->currentItem.token;
    lexeme = pBasicScanner->currentItem.lexeme.c_str;

    
    if (token == TK_LEFT_PARENTHESIS)
    {
        pNewMacro->bIsFunction = true;

        StrBuilder_Append(strBuilder, lexeme);

        
        BasicScanner_Match(pBasicScanner);

        for (;;)
        {
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, strBuilder);

            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;

            if (token == TK_RIGHT_PARENTHESIS)
            {
                
                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                break;
            }

            if (token == TK_BREAKLINE || token == TK_EOF)
            {
                
                break;
            }

            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;

            struct       PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
            TokenArray_PushBack(&pNewMacro->FormalArguments, ppToken);

            StrBuilder_Append(strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, strBuilder);

            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;

            if (token == TK_COMMA)
            {
                
                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                
            }
        }
    }
    else
    {
        Scanner_MatchAllPreprocessorSpaces(pBasicScanner, strBuilder);
    }

    Scanner_MatchAllPreprocessorSpaces(pBasicScanner, strBuilder);

    GetPPTokens(pBasicScanner, &pNewMacro->TokenSequence, strBuilder);

    MacroMap_SetAt(&pScanner->Defines2, pNewMacro->Name, pNewMacro);

    
}

int EvalPre(Scanner * pScanner, StrBuilder * sb)
{
    if (pScanner->bError)
    {
        return 0;
    }

    
    
    
    BasicScanner * pBasicScanner = Scanner_Top(pScanner);

    struct TokenArray pptokens = TOKENARRAY_INIT;
    GetPPTokens(pBasicScanner, &pptokens, sb);


    StrBuilder strBuilder = STRBUILDER_INIT;
    ExpandMacroToText(&pptokens, &pScanner->Defines2, false, true, true, NULL,
        &strBuilder);

    int iRes = EvalExpression(strBuilder.c_str, pScanner);

    if (pScanner->bError)
    {
        
    }

     
    StrBuilder_Destroy(&strBuilder);
    TokenArray_Destroy(&pptokens);
    return iRes;
}

static void Scanner_PushToken(Scanner * pScanner, Tokens token,
    const char * lexeme, bool bActive)
{
    if (pScanner->bError)
    {
        return;
    }

    struct ScannerItem * pNew = ScannerItem_Create();
    LocalStrBuilder_Set(&pNew->lexeme, lexeme);
    pNew->token = token;
    pNew->bActive = bActive; 
    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);
}








void Scanner_BuyIdentifierThatCanExpandAndCollapse(Scanner * pScanner)
{
    enum PPState state = StateTop(pScanner);
    BasicScanner * pBasicScanner = Scanner_Top(pScanner);
    

    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;
    

    if (!IsIncludeState(state))
    {
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = false;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        
        BasicScanner_Match(pBasicScanner);
        return;
    }

    struct Macro * pMacro2 = Scanner_FindPreprocessorItem2(pScanner, lexeme);
    if (pMacro2 == NULL)
    {
        
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        
        BasicScanner_Match(pBasicScanner);
        return;
    }

    if (pBasicScanner->bMacroExpanded &&
        strcmp(pMacro2->Name, pBasicScanner->stream.NameOrFullPath) == 0)
    {
        
        
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        
        BasicScanner_Match(pBasicScanner);
        return;
    }

    struct Macro * pFirstMacro = pMacro2;

    
    BasicScanner_Match(pBasicScanner);

    bool bExitLoop = false;

    do
    {
        if (!pMacro2->bIsFunction)
        {
            struct TokenArray ppTokenArray = TOKENARRAY_INIT;
            
            struct       PPToken * ppTokenName =
                PPToken_Create(pMacro2->Name, TokenToPPToken(TK_IDENTIFIER));
            TokenArray_PushBack(&ppTokenArray, ppTokenName);

            StrBuilder strExpanded = STRBUILDER_INIT;

            ExpandMacroToText(&ppTokenArray, &pScanner->Defines2, false, false, false, NULL,
                &strExpanded);

            
            
            struct Macro * pMacro3 = NULL;

            if (strExpanded.size > 0)
            {
                pMacro3 = Scanner_FindPreprocessorItem2(pScanner, strExpanded.c_str);
            }

            if (pMacro3)
            {
                if (pMacro3->bIsFunction)
                {
                    
                    pMacro2 = pMacro3;
                }
                else
                {
                    

                    PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                    Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                    bExitLoop = true;

                }
            }
            else
            {
                

                PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                bExitLoop = true;
            }

            TokenArray_Destroy(&ppTokenArray);
            StrBuilder_Destroy(&strExpanded);
        }
        else
        {
            

            

            TScannerItemList LocalAcumulatedTokens = { 0 };
            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;
            while (token == TK_SPACES ||
                token == TK_COMMENT ||
                token == TK_OPEN_COMMENT ||
                token == TK_CLOSE_COMMENT)
            {
                

                
                struct ScannerItem * pNew = ScannerItem_Create();
                LocalStrBuilder_Set(&pNew->lexeme, lexeme);
                pNew->token = token;
                pNew->bActive = true;
                TScannerItemList_PushBack(&LocalAcumulatedTokens, pNew);
                

                BasicScanner_Match(pBasicScanner);
                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;
            }

            if (token == TK_LEFT_PARENTHESIS)
            {
                StrBuilder strCallString = STRBUILDER_INIT;
                StrBuilder strExpanded = STRBUILDER_INIT;
                struct TokenArray ppTokenArray = TOKENARRAY_INIT;

                StrBuilder_Set(&strCallString, pFirstMacro->Name);
                
                
                GetMacroArguments(pScanner,
                    pBasicScanner,
                    pMacro2,
                    &ppTokenArray,
                    &strCallString);

                ExpandMacroToText(&ppTokenArray,
                    &pScanner->Defines2,
                    false,
                    false,
                    false,
                    NULL,
                    &strExpanded);

                
                
                
                struct Macro * pMacro3 = NULL;
                if (strExpanded.size > 0)
                {
                    pMacro3 = Scanner_FindPreprocessorItem2(pScanner, strExpanded.c_str);
                }

                if (pMacro3)
                {
                    if (pMacro3->bIsFunction)
                    {
                        
                        pMacro2 = pMacro3;
                    }
                    else
                    {
                        

                        PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                        Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                    }
                }
                else
                {
                    

                    PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                    Scanner_PushToken(pScanner, TK_MACRO_CALL, strCallString.c_str, true);
                    bExitLoop = true;
                }
                
                TokenArray_Destroy(&ppTokenArray);
                StrBuilder_Destroy(&strExpanded);
                StrBuilder_Destroy(&strCallString);
            }
            else
            {
                
                
                
                
                if (pFirstMacro != pMacro2)
                {
                    
                    struct ScannerItem * pNew = ScannerItem_Create();
                    LocalStrBuilder_Append(&pNew->lexeme, pFirstMacro->Name);
                    pNew->token = TK_MACRO_CALL;
                    pNew->bActive = true;
                    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);
                }

                struct ScannerItem * pNew0 = ScannerItem_Create();
                LocalStrBuilder_Append(&pNew0->lexeme, pMacro2->Name);
                pNew0->token = TK_IDENTIFIER;
                pNew0->bActive = true;
                TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew0);

                if (pFirstMacro != pMacro2)
                {
                    struct ScannerItem * pNew2 = ScannerItem_Create();
                    pNew2->token = TK_MACRO_EOF;
                    pNew2->bActive = true;
                    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew2);
                }

                if (LocalAcumulatedTokens.pHead != NULL)
                {
                    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, LocalAcumulatedTokens.pHead);
                    LocalAcumulatedTokens.pHead = NULL;
                    LocalAcumulatedTokens.pTail = NULL;
                }
                

                
                
                bExitLoop = true;
            }


            TScannerItemList_Destroy(&LocalAcumulatedTokens);
        }
        if (bExitLoop)
            break;
    }
    while (!bExitLoop);
}

void Scanner_BuyTokens(Scanner * pScanner)
{
    
    
    
    
    

    if (pScanner->bError)
    {
        return;
    }

    BasicScanner * pBasicScanner = Scanner_Top(pScanner);
    if (pBasicScanner == NULL)
    {
        
        return;
    }

    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;

    if (token == TK_BOF)
    {
        BasicScanner_Match(pBasicScanner);
        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;
    }

    while (token == TK_EOF)
    {
        
        BasicScannerStack_Pop(&pScanner->stack);

        
        pBasicScanner = Scanner_Top(pScanner);

        if (pBasicScanner != NULL)
        {
            
            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;
        }
        else
        {
            break;
        }
    }

    if (token == TK_FILE_EOF)
    {
        if (pScanner->stack->pPrevious == NULL)
        {
            
            token = TK_EOF;
        }
    }

    if (token == TK_EOF)
    {
        
        struct ScannerItem * pNew = ScannerItem_Create();
        pNew->token = TK_EOF;
        pNew->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        return;
    }

    StrBuilder strBuilder = STRBUILDER_INIT;

    enum PPState state = StateTop(pScanner);
    bool bActive0 = IsIncludeState(state);

    if (token == TK_PREPROCESSOR)
    {
        
        StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
        BasicScanner_Match(pBasicScanner);

        
        Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

        lexeme = pBasicScanner->currentItem.lexeme.c_str;
        token = pBasicScanner->currentItem.token;

        Tokens preToken = FindPreToken(lexeme);

        if (preToken == TK_PRE_INCLUDE)
        {
            
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            lexeme = pBasicScanner->currentItem.lexeme.c_str;
            token = pBasicScanner->currentItem.token;

            if (IsIncludeState(state))
            {
                
                Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

                lexeme = pBasicScanner->currentItem.lexeme.c_str;
                token = pBasicScanner->currentItem.token;

                if (token == TK_STRING_LITERAL)
                {
                    String * /*@auto*/ fileName;
                    fileName = StrDup(lexeme + 1);

                    StrBuilder_Append(&strBuilder, lexeme);
                    BasicScanner_Match(pBasicScanner);

                    fileName[strlen(fileName) - 1] = 0;

                    
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    if (pScanner->pOptions->bAmalgamate)
                    {
                        if (!Scanner_IsAlreadyIncluded(pScanner, fileName, FileIncludeTypeQuoted))
                        {
                            Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
                            Scanner_IncludeFile(pScanner, fileName, FileIncludeTypeQuoted, true);
                        }
                        else
                        {
                            Scanner_PushToken(pScanner, TK_BREAKLINE, "\n", true);
                        }
                    }
                    else
                    {
                        Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
                        Scanner_IncludeFile(pScanner, fileName, FileIncludeTypeQuoted, true);
                    }
                    Free(fileName);
                    
                }
                else if (token == TK_LESS_THAN_SIGN)
                {
                    StrBuilder_Append(&strBuilder, lexeme);

                    BasicScanner_Match(pBasicScanner);
                    lexeme = pBasicScanner->currentItem.lexeme.c_str;
                    token = pBasicScanner->currentItem.token;
                    StrBuilder path = STRBUILDER_INIT;


                    for (;;)
                    {
                        StrBuilder_Append(&strBuilder, lexeme);

                        if (token == TK_GREATER_THAN_SIGN)
                        {
                            BasicScanner_Match(pBasicScanner);
                            lexeme = pBasicScanner->currentItem.lexeme.c_str;
                            token = pBasicScanner->currentItem.token;
                            break;
                        }

                        if (token == TK_BREAKLINE)
                        {
                            
                            break;
                        }

                        StrBuilder_Append(&path, lexeme);
                        BasicScanner_Match(pBasicScanner);
                        lexeme = pBasicScanner->currentItem.lexeme.c_str;
                        token = pBasicScanner->currentItem.token;
                    }

                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    if (pScanner->pOptions->bAmalgamate)
                    {
                        if (!Scanner_IsAlreadyIncluded(pScanner, path.c_str, FileIncludeTypeIncludes))
                        {
                            Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
                            Scanner_IncludeFile(pScanner, path.c_str, FileIncludeTypeIncludes,
                                true);
                        }
                        else
                        {
                            Scanner_PushToken(pScanner, TK_BREAKLINE, "\n", true);
                        }
                    }
                    else
                    {
                        Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
                        Scanner_IncludeFile(pScanner, path.c_str, FileIncludeTypeIncludes,
                            true);
                    }

                    StrBuilder_Destroy(&path);
                }

            }
            else
            {
                
                Scanner_PushToken(pScanner, TK_SPACES, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_PRAGMA)
        {
            
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            if (IsIncludeState(state))
            {
                Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

                if (BasicScanner_IsLexeme(pBasicScanner, "once"))
                {
                    const char * fullPath = Scanner_Top(pScanner)->stream.NameOrFullPath;
                    TFile * pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

                    if (pFile == NULL)
                    {
                        pFile = TFile_Create();
                        pFile->PragmaOnce = true;
                        TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile);
                    }
                    else
                    {
                        pFile->PragmaOnce = true;
                    }
                    
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                }
                else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "message"))
                {
                    
                    StrBuilder_Append(&strBuilder, lexeme);
                    BasicScanner_Match(pBasicScanner);

                    if (IsIncludeState(state))
                    {
                        GetDefineString(pScanner, &strBuilder);
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                        Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                    }
                    else
                    {
                        Scanner_PushToken(pScanner, preToken, strBuilder.c_str, false);
                    }
                }
                else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "dir"))
                {
                    StrBuilder_Append(&strBuilder, lexeme);

                    BasicScanner_Match(pBasicScanner);
                    Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);
                    lexeme = pBasicScanner->currentItem.lexeme.c_str;

                    String * /*@auto*/ fileName;
                    fileName = StrDup(lexeme + 1);

                    Scanner_Match(pScanner);
                    fileName[strlen(fileName) - 1] = 0;
                    StrArray_Push(&pScanner->IncludeDir, fileName);
                    Free(fileName);
                    
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                }
                else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "source"))
                {
                    StrBuilder_Append(&strBuilder, lexeme);

                    BasicScanner_Match(pBasicScanner);
                    Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

                    String * /*@auto*/ fileName = NULL;

                    if (pBasicScanner->currentItem.token == TK_STRING_LITERAL)
                    {
                        lexeme = pBasicScanner->currentItem.lexeme.c_str;
                        fileName = StrDup(lexeme + 1);
                        fileName[strlen(fileName) - 1] = 0;

                        bool bHasFullPath = false;
                        String * fullPath = 0;
                        bHasFullPath = Scanner_GetFullPath(pScanner, fileName, true, &fullPath);
                        Free(fileName);
                        fileName = fullPath;
                        BasicScanner_Match(pBasicScanner);
                    }
                    else
                    {
                        fileName = StrDup(pScanner->stack->stream.NameOrFullPath);
                        fileName[strlen(pScanner->stack->stream.NameOrFullPath) - 1] = 'c';
                    }




                    FileNodeList_PushBack(&pScanner->Sources, fileName);

                    Free(fileName);
                    
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                }
                else if (BasicScanner_IsLexeme(pBasicScanner, "region"))
                {
                    StrBuilder_Append(&strBuilder, "region");
                    BasicScanner_Match(pBasicScanner);
                    Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);
                    if (BasicScanner_IsLexeme(pBasicScanner, "cprime"))
                    {
                        BasicScanner_Match(pBasicScanner);
                        Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

                        Scanner_PushToken(pScanner, TK_DEFAULT, "default", true);
                        Scanner_PushToken(pScanner, TK_SPACES, " ", true);

                        lexeme = pBasicScanner->currentItem.lexeme.c_str;
                        Scanner_PushToken(pScanner, TK_IDENTIFIER, lexeme, true);

                        BasicScanner_Match(pBasicScanner);
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);

                        Scanner_PushToken(pScanner, TK_LEFT_CURLY_BRACKET, "{", true);
                    }
                    else
                    {
                        
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                        Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                    }
                }
                else if (BasicScanner_IsLexeme(pBasicScanner, "endregion"))
                {
                    StrBuilder_Append(&strBuilder, "endregion");
                    BasicScanner_Match(pBasicScanner);
                    Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

                    if (BasicScanner_IsLexeme(pBasicScanner, "cprime"))
                    {
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                        Scanner_PushToken(pScanner, TK_RIGHT_CURLY_BRACKET, "}", true);
                    }
                    else
                    {
                        
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                        Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                    }
                }
                else
                {
                    
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                }

            }
            else
            {
                IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                Scanner_PushToken(pScanner, preToken, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_IF || preToken == TK_PRE_IFDEF ||
            preToken == TK_PRE_IFNDEF)
        {
            StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);

            BasicScanner_Match(pBasicScanner);
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

            lexeme = pBasicScanner->currentItem.lexeme.c_str;

            switch (state)
            {
                case PPState_NONE:
                case PPState_I1:
                case PPState_E1:
                {
                    int iRes = 0;

                    if (preToken == TK_PRE_IF)
                    {
                        iRes = EvalPre(pScanner, &strBuilder);
                    }
                    else
                    {
                        bool bFound = Scanner_FindPreprocessorItem2(pScanner, lexeme) != NULL;

                        if (preToken == TK_PRE_IFDEF)
                        {
                            iRes = bFound ? 1 : 0;
                        }
                        else 
                        {
                            iRes = !bFound ? 1 : 0;
                        }
                    }

                    if (iRes != 0)
                    {
                        StatePush(pScanner, PPState_I1);
                    }
                    else
                    {
                        StatePush(pScanner, PPState_I0);
                    }
                }
                break;

                case PPState_I0:
                StatePush(pScanner, PPState_I0);
                break;

                case PPState_E0:
                StatePush(pScanner, PPState_E0);
                break;
            }

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, preToken, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ELIF)
        {
            
            StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);

            BasicScanner_Match(pBasicScanner);
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

            switch (state)
            {
                case PPState_NONE:
                case PPState_I1:
                pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_E0;
                break;

                case PPState_I0:
                {
                    int iRes = EvalPre(pScanner, &strBuilder);

                    if (pScanner->StackIfDef.Size >= 2)
                    {
                        if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
                            PPState_I1 ||
                            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
                            PPState_E1))
                        {
                            if (iRes)
                            {
                                pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_I1;
                            }
                        }
                    }
                    else
                    {
                        if (iRes)
                        {
                            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_I1;
                        }
                    }
                }
                break;

                case PPState_E0:
                break;

                case PPState_E1:
                
                break;
            }

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_ELIF, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ENDIF)
        {
            
            StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);

            BasicScanner_Match(pBasicScanner);
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            StatePop(pScanner);

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            Scanner_PushToken(pScanner, TK_PRE_ENDIF, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ELSE)
        {

            
            StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
            BasicScanner_Match(pBasicScanner);

            switch (state)
            {
                case PPState_NONE:
                
                break;

                case PPState_I1:
                pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_E0;
                break;

                case PPState_I0:
                if (pScanner->StackIfDef.Size >= 2)
                {
                    if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
                        PPState_I1 ||
                        pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
                        PPState_E1))
                    {
                        pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_E1;
                    }
                }
                else
                {
                    pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = PPState_E1;
                }

                break;

                case PPState_E0:
                break;

                case PPState_E1:
                
                break;
            }

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_ELSE, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ERROR)
        {
            
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            if (IsIncludeState(state))
            {
                StrBuilder str = STRBUILDER_INIT;
                StrBuilder_Append(&str, ": #error : ");
                GetDefineString(pScanner, &str);
                Scanner_SetError(pScanner, str.c_str);
                StrBuilder_Destroy(&str);

                IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                Scanner_PushToken(pScanner, TK_PRE_ERROR, strBuilder.c_str, true);
            }
            else
            {
                Scanner_PushToken(pScanner, preToken, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_LINE)
        {
            if (IsIncludeState(state))
            {
                
                StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
                BasicScanner_Match(pBasicScanner);

                IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                Scanner_PushToken(pScanner, TK_PRE_LINE, strBuilder.c_str, true);
            }
            else
            {
                Scanner_PushToken(pScanner, preToken, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_UNDEF)
        {
            if (IsIncludeState(state))
            {
                
                StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
                BasicScanner_Match(pBasicScanner);

                lexeme = BasicScanner_Lexeme(Scanner_Top(pScanner));

                MacroMap_RemoveKey(&pScanner->Defines2, lexeme);

                IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                Scanner_PushToken(pScanner, TK_PRE_UNDEF, strBuilder.c_str, true);
            }
            else
            {
                Scanner_PushToken(pScanner, preToken, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_DEFINE)
        {
            
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);
            bool bActive = IsIncludeState(state);
            if (bActive)
            {
                ParsePreDefinev2(pScanner, &strBuilder);
            }

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_DEFINE, strBuilder.c_str, bActive);
        }

        
    } 
    else if (token == TK_IDENTIFIER)
    {
        
        Scanner_BuyIdentifierThatCanExpandAndCollapse(pScanner);
    }
    else
    {
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = bActive0;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        BasicScanner_Match(pBasicScanner);
    }
    StrBuilder_Destroy(&strBuilder);
    

    
    
}

void PrintPreprocessedToFileCore(FILE * fp, Scanner * scanner)
{
    while (Scanner_TokenAt(scanner, 0) != TK_EOF)
    {
        Tokens token = Scanner_TokenAt(scanner, 0);
        const char * lexeme = Scanner_LexemeAt(scanner, 0);
        if (Scanner_IsActiveAt(scanner, 0))
        {
            switch (token)
            {
                
                case TK_PRE_INCLUDE:
                case TK_PRE_PRAGMA:
                case TK_PRE_IF:
                case TK_PRE_ELIF:
                case TK_PRE_IFNDEF:
                case TK_PRE_IFDEF:
                case TK_PRE_ENDIF:
                case TK_PRE_ELSE:
                case TK_PRE_ERROR:
                case TK_PRE_LINE:
                case TK_PRE_UNDEF:
                case TK_PRE_DEFINE:
                fprintf(fp, "\n");
                break;

                
                case TK_LINE_COMMENT:
                case TK_COMMENT:
                case TK_OPEN_COMMENT:
                case TK_CLOSE_COMMENT:
                fprintf(fp, " ");
                break;

                case TK_BOF:
                break;

                case TK_MACRO_CALL:
                case TK_MACRO_EOF:
                case TK_FILE_EOF:
                break;

                default:
                fprintf(fp, "%s", lexeme);
                break;
            }
        }

        Scanner_Match(scanner);
    }
}

void PrintPreprocessedToFile(const char * fileIn, const char * configFileName)
{
    String * /*@auto*/ fullFileNamePath = NULL;
    GetFullPath(fileIn, &fullFileNamePath);

    Scanner scanner;
    Scanner_Init(&scanner);

    Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath,
        false);

    if (configFileName != NULL)
    {
        String * /*@auto*/ configFullPath = NULL;
        GetFullPath(configFileName, &configFullPath);

        Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath,
            true);
        Scanner_Match(&scanner);

        Free(configFullPath);
    }

    
    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(fullFileNamePath, drive, dir, fname, ext); 

    char fileNameOut[CPRIME_MAX_DRIVE + CPRIME_MAX_DIR + CPRIME_MAX_FNAME + CPRIME_MAX_EXT + 1];
    strcat(fname, "_pre");
    MakePath(fileNameOut, drive, dir, fname, ".c");

    FILE * fp = fopen(fileNameOut, "w");
    PrintPreprocessedToFileCore(fp, &scanner);

    fclose(fp);
    Scanner_Destroy(&scanner);
    Free(fullFileNamePath);
}

void PrintPreprocessedToStringCore2(StrBuilder * fp, Scanner * scanner)
{
    while (Scanner_TokenAt(scanner, 0) != TK_EOF)
    {
        Tokens token = Scanner_TokenAt(scanner, 0);
        const char * lexeme = Scanner_LexemeAt(scanner, 0);
        if (Scanner_IsActiveAt(scanner, 0))
        {
            switch (token)
            {
                
                case TK_PRE_INCLUDE:
                case TK_PRE_PRAGMA:
                case TK_PRE_IF:
                case TK_PRE_ELIF:
                case TK_PRE_IFNDEF:
                case TK_PRE_IFDEF:
                case TK_PRE_ENDIF:
                case TK_PRE_ELSE:
                case TK_PRE_ERROR:
                case TK_PRE_LINE:
                case TK_PRE_UNDEF:
                case TK_PRE_DEFINE:
                StrBuilder_Append(fp, "\n");
                break;

                
                case TK_LINE_COMMENT:
                case TK_COMMENT:

                case TK_OPEN_COMMENT:
                case TK_CLOSE_COMMENT:

                StrBuilder_Append(fp, " ");
                break;

                case TK_BOF:
                break;

                case TK_MACRO_CALL:
                case TK_MACRO_EOF:
                case TK_FILE_EOF:
                break;

                default:
                StrBuilder_Append(fp, lexeme);
                break;
            }
        }

        Scanner_Match(scanner);
    }
}

void PrintPreprocessedToString2(StrBuilder * fp, const char * input, const char * configFileName)
{

    Scanner scanner;
    Scanner_InitString(&scanner, "name", input);


    if (configFileName != NULL)
    {
        String * /*@auto*/ configFullPath = NULL;
        GetFullPath(configFileName, &configFullPath);

        Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath,
            true);
        Scanner_Match(&scanner);

        Free(configFullPath);
    }


    PrintPreprocessedToStringCore2(fp, &scanner);

    Scanner_Destroy(&scanner);
}



void GetSources(const char * configFile,
    const char * fileIn,
    bool bRecursiveSearch,
    struct FileNodeList * pFileNodeList)
{

    String * /*@auto*/ fullFileNamePath = NULL;
    GetFullPath(fileIn, &fullFileNamePath);
    Scanner scanner;

    Scanner_Init(&scanner);
    struct Options options = OPTIONS_INIT;
    options.bAmalgamate = true;
    scanner.pOptions = &options;

    Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath,
        false);

    if (configFile != NULL)
    {
        Scanner_IncludeFile(&scanner, configFile, FileIncludeTypeFullPath,
            false);
        TFileMap_DeleteItem(&scanner.FilesIncluded, configFile);
    }


    while (Scanner_TokenAt(&scanner, 0) != TK_EOF)
    {
        Scanner_Match(&scanner);
    }


    Scanner_Reset(&scanner);


    struct FileNodeMap map = { 0 };
    if (bRecursiveSearch)
    {
        for (;;)
        {
            struct FileNode * pSources = scanner.Sources.pHead;
            scanner.Sources.pHead = NULL;
            scanner.Sources.pTail = NULL;
            struct FileNode * pCurrent = pSources;
            while (pCurrent)
            {
                struct FileNode * pNext = pCurrent->pNext;
                if (FileNodeMap_Lookup(&map, pCurrent->Key) == 0)
                {
                    FileNodeMap_Insert(&map, pCurrent);
                    Scanner_IncludeFile(&scanner,
                        pCurrent->Key,
                        FileIncludeTypeFullPath,
                        false);
                }
                else
                {
                    FileNode_Delete(pCurrent);
                }

                pCurrent = pNext;
            }

            while (Scanner_TokenAt(&scanner, 0) != TK_EOF)
            {
                Scanner_Match(&scanner);
            }

            Scanner_Reset(&scanner);

            if (scanner.Sources.pHead == NULL)
                break;
        }


        for (int j = 0; j < scanner.FilesIncluded.buckets.size; j++)
        {
            Bucket * pBucket = scanner.FilesIncluded.buckets.data[j];
            if (pBucket)
            {
                for (int i = 0; i < pBucket->size; i++)
                {
                    TFile * pFile = (TFile *)pBucket->data[i];

                    bool bIncludeDir = false;
                    for (int k = 0; k < scanner.IncludeDir.size; k++)
                    {
                        if (strstr(pFile->FullPath, scanner.IncludeDir.pItems[k]) != 0)
                        {
                            bIncludeDir = true;
                            break;
                        }
                    }

                    if (!bIncludeDir)
                    {

                        FileNodeList_PushBack(pFileNodeList, pFile->FullPath);
                    }
                }
            }
        }
    }
    else
    {
        FileNodeList_Swap(pFileNodeList, &scanner.Sources);
    }




    FileNodeMap_Destroy(&map);
    Scanner_Destroy(&scanner);
    Free(fullFileNamePath);
}

void PrintPreprocessedToConsole(const char * fileIn,
    const char * configFileName)
{
    String * /*@auto*/ fullFileNamePath = NULL;
    GetFullPath(fileIn, &fullFileNamePath);

    Scanner scanner;
    Scanner_Init(&scanner);

    Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath,
        false);

    if (configFileName != NULL)
    {
        String * /*@auto*/ configFullPath = NULL;
        GetFullPath(configFileName, &configFullPath);

        Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath,
            true);
        Scanner_Match(&scanner);

        Free(configFullPath);
    }

    PrintPreprocessedToFileCore(stdout, &scanner);

    Scanner_Destroy(&scanner);
    Free(fullFileNamePath);
}

int Scanner_GetNumberOfScannerItems(Scanner * pScanner)
{
    int nCount = 1; 
    ForEachListItem(struct ScannerItem, pItem, &pScanner->AcumulatedTokens)
    {
        nCount++;
    }
    return nCount;
}

struct ScannerItem * Scanner_ScannerItemAt(Scanner * pScanner, int index)
{

    
    
    

    struct ScannerItem * pScannerItem = NULL;

    if (!pScanner->bError)
    {
        
        int nCount = 0;
        ForEachListItem(struct ScannerItem, pItem, &pScanner->AcumulatedTokens)
        {
            nCount++;
        }

        
        if (index >= nCount)
        {
            for (int i = nCount; i <= index; i++)
            {
                
                Scanner_BuyTokens(pScanner);
            }
            pScannerItem = pScanner->AcumulatedTokens.pTail;
        }
        else
        {
            
            int n = 0;
            ForEachListItem(struct ScannerItem, pItem, &pScanner->AcumulatedTokens)
            {
                if (n == index)
                {
                    pScannerItem = pItem;
                    break;
                }
                n++;
            }
        }
    }


    return pScannerItem;
}

void Scanner_PrintItems(Scanner * pScanner)
{
    printf("-----\n");
    int n = Scanner_GetNumberOfScannerItems(pScanner);
    for (int i = 0; i < n; i++)
    {
        struct ScannerItem * pItem = Scanner_ScannerItemAt(pScanner, i);
        printf("%d : %s %s\n", i, pItem->lexeme.c_str, TokenToString(pItem->token));
    }
    printf("-----\n");
}

int Scanner_FileIndexAt(Scanner * pScanner, int index)
{
    struct ScannerItem * pScannerItem = Scanner_ScannerItemAt(pScanner, index);
    if (pScannerItem)
    {
        return pScannerItem->FileIndex;
    }
    return 0;
}

int Scanner_LineAt(Scanner * pScanner, int index)
{
    struct ScannerItem * pScannerItem = Scanner_ScannerItemAt(pScanner, index);
    if (pScannerItem)
    {
        return pScannerItem->Line;
    }
    return 0;
}

bool Scanner_IsActiveAt(Scanner * pScanner, int index)
{
    struct ScannerItem * pScannerItem = Scanner_ScannerItemAt(pScanner, index);
    if (pScannerItem)
    {
        return pScannerItem->bActive;
    }
    return false;
}

Tokens Scanner_TokenAt(Scanner * pScanner, int index)
{
    struct ScannerItem * pScannerItem = Scanner_ScannerItemAt(pScanner, index);
    if (pScannerItem)
    {
        return pScannerItem->token;
    }

    return TK_EOF;
}

const char * Scanner_LexemeAt(Scanner * pScanner, int index)
{
    struct ScannerItem * pScannerItem = Scanner_ScannerItemAt(pScanner, index);
    if (pScannerItem)
    {
        return pScannerItem->lexeme.c_str;
    }
    return "";
}



void Scanner_MatchDontExpand(Scanner * pScanner)
{
    if (!pScanner->bError)
    {
        if (pScanner->AcumulatedTokens.pHead != NULL)
        {
            TScannerItemList_PopFront(&pScanner->AcumulatedTokens);
        }
        else
        {
            BasicScanner * pTopScanner = Scanner_Top(pScanner);
            if (pTopScanner == NULL)
            {
                return;
            }

            BasicScanner_Match(pTopScanner);

            Tokens token = pTopScanner->currentItem.token;

            while (token == TK_EOF && pScanner->stack->pPrevious != NULL)
            {
                
                BasicScannerStack_PopIfNotLast(&pScanner->stack);
                pTopScanner = Scanner_Top(pScanner);
                token = pTopScanner->currentItem.token;
            }
        }
    }
}
void Scanner_Match(Scanner * pScanner)
{
    if (pScanner->AcumulatedTokens.pHead != NULL)
    {
        TScannerItemList_PopFront(&pScanner->AcumulatedTokens);
        if (pScanner->AcumulatedTokens.pHead == NULL)
        {
            Scanner_BuyTokens(pScanner);
        }
    }
}

bool Scanner_MatchToken(Scanner * pScanner, Tokens token, bool bActive)
{
    if (pScanner->bError)
    {
        return false;
    }

    bool b = Scanner_TokenAt(pScanner, 0) == token;
    Scanner_Match(pScanner);
    return b;
}


void TScannerItemList_Destroy(TScannerItemList * p)
{
    struct ScannerItem * pCurrent = p->pHead;
    while (pCurrent)
    {
        struct ScannerItem * pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        ScannerItem_Delete(pItem);
    }
}

void TScannerItemList_Clear(TScannerItemList * p)
{
    TScannerItemList_Destroy(p);
    TScannerItemList_Init(p);
}

void TScannerItemList_Init(TScannerItemList * p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}


void TScannerItemList_Swap(TScannerItemList * a, TScannerItemList * b)
{
    TScannerItemList t = *a;
    *a = *b;
    *b = t;
}

void TScannerItemList_PopFront(TScannerItemList * pList)
{
    struct ScannerItem * p = pList->pHead;
    pList->pHead = pList->pHead->pNext;
    ScannerItem_Delete(p);
}

void TScannerItemList_PushBack(TScannerItemList * pList, struct ScannerItem * pItem)
{
    if ((pList)->pHead == NULL)
    {
        (pList)->pHead = (pItem);
        (pList)->pTail = (pItem);
    }
    else
    {
        (pList)->pTail->pNext = (pItem);
        (pList)->pTail = (pItem);
    }

}










wchar_t BasicScanner_MatchChar(BasicScanner * scanner);

const char * TokenToString(Tokens tk)
{
    switch (tk)
    {
        case TK_NONE:
            return "None";

        case TK_BOF:
            return "Bof";
        case TK_EOF:
            return "Eof";
        case TK_LINE_COMMENT:
            return "LINE_COMMENT";
        case TK_COMMENT:
            return "COMMENT";
        case TK_CLOSE_COMMENT:
            return "CLOSE_COMMENT";
        case TK_OPEN_COMMENT:
            return "OPEN_COMMENT";
        case TK_STRING_LITERAL:
            return "LITERALSTR";
        case TK_IDENTIFIER:
            return "IDENTIFIER";
        case TK_SPACES:
            return "SPACES";
        case TK_DECIMAL_INTEGER:
            return "TK_DECIMAL_INTEGER";
        case TK_HEX_INTEGER:
            return "TK_HEX_INTEGER";
        case TK_FLOAT_NUMBER:
            return "TK_FLOAT_NUMBER";
        case TK_BREAKLINE:
            return "BREAKLINE";
        case TK_BACKSLASHBREAKLINE:
            return "TK_BACKSLASHBREAKLINE";
        case TK_PREPROCESSOR:
            return "PREPROCESSOR";
        case CHARACTER_TABULATION:
            return "CHARACTER_TABULATION";
        case TK_EXCLAMATION_MARK:
            return "!";
        case TK_QUOTATION_MARK:
            return "\"";
        case TK_NUMBER_SIGN:
            return "#";
        case TK_DOLLAR_SIGN:
            return "$";
        case TK_PERCENT_SIGN:
            return "%";
        case TK_AMPERSAND:
            return "&";
        case TK_APOSTROPHE:
            return "'";
        case TK_LEFT_PARENTHESIS:
            return "(";
        case TK_RIGHT_PARENTHESIS:
            return ")";
        case TK_ASTERISK:
            return "*";
        case TK_PLUS_SIGN:
            return "+";
        case TK_COMMA:
            return ",";
        case TK_HYPHEN_MINUS:
            return "-";
        case TK_FULL_STOP:
            return ".";
        case TK_SOLIDUS:
            return "/";
        case TK_COLON:
            return ":";
        case TK_SEMICOLON:
            return ";";
        case TK_LESS_THAN_SIGN:
            return "<";
        case TK_EQUALS_SIGN:
            return "=";
        case TK_GREATER_THAN_SIGN:
            return ">";
        case TK_QUESTION_MARK:
            return "?";
        case TK_COMMERCIAL_AT:
            return "@";
        case TK_LEFT_SQUARE_BRACKET:
            return "[";
        case REVERSE_SOLIDUS:
            return "\\";
        case TK_RIGHT_SQUARE_BRACKET:
            return "]";
        case TK_CIRCUMFLEX_ACCENT:
            return "^";
        case TK_LOW_LINE:
            return "_";
        case TK_GRAVE_ACCENT:
            return "`";
        case TK_LEFT_CURLY_BRACKET:
            return "{";
        case TK_VERTICAL_LINE:
            return "|";
        case TK_RIGHT_CURLY_BRACKET:
            return "}";

        case TK_TILDE:
            return "~";
            break;
        case TK_AUTO:
            return "auto";

        case TK_BREAK:
            return "break";
        case TK_CASE:
            return "case";
        case TK_CHAR:
            return "char";
        case TK_CONST:
            return "const";
        case TK_CONTINUE:
            return "continue";
        case TK_DEFAULT:
            return "default";

        case TK_DO:
            return "do";
        case TK_DOUBLE:
            return "double";
        case TK_ELSE:
            return "else";
        case TK_ENUM:
            return "enum";
        case TK_EXTERN:
            return "extern";
        case TK_FLOAT:
            return "float";
        case TK_FOR:
            return "for";
        case TK_GOTO:
            return "goto";
        case TK_IF:
            return "if";
        case TK_INT:
            return "int";
        case TK_LONG:
            return "long";
        case TK__INT8:
            return "__int8";
        case TK__INT16:
            return "__int16";
        case TK__INT32:
            return "__int32";
        case TK__INT64:
            return "__int64";
        case TK__WCHAR_T:
            return "__wchar_t";

        case TK_REGISTER:
            return "register";
        case TK_RETURN:
            return "return";
        case TK_SHORT:
            return "short";
        case TK_SIGNED:
            return "signed";
        case TK_SIZEOF:
            return "sizeof";
        case TK_STATIC:
            return "static";
        case TK_STRUCT:
            return "struct";
        case TK_SWITCH:
            return "switch";
        case TK_TYPEDEF:
            return "typedef";
        case TK_UNION:
            return "union";

        case TK_UNSIGNED:
            return "unsigned";
        case TK_VOID:
            return "void";
        case TK__BOOL:
            return "_Bool";
            break;
        case TK_VOLATILE:
            return "volatile";
        case TK_WHILE:
            return "while";
        case TK_ARROW:
            return "->";

        case TK_PLUSPLUS:
            return "++";

        case TK_MINUSMINUS:
            return "--";

        case TK_EQUALEQUAL:
            return "==";
        case TK_NOTEQUAL:
            return "!=";

        case TK_LESSLESS:
            return "<<";

        case TK_GREATERGREATER:
            return ">>";


        case TK_LESSEQUAL:
            return "<=";
        case TK_GREATEREQUAL:
            return ">=";

        case TK_ANDAND:
            return "&&";
        case TK_OROR:
            return "||";
        case TK_MULTIEQUAL:
            return "*=";
        case TK_DIVEQUAL:
            return "/=";
        case TK_PERCENT_EQUAL:
            return "/%=";
        case TK_PLUSEQUAL:
            return "+=";
        case TK_MINUS_EQUAL:
            return "-=";
        case TK_ANDEQUAL:
            return "!=";
        case TK_CARETEQUAL:
            return "^=";
        case TK_OREQUAL:
            return "|=";
        case TK_NUMBERNUMBER:
            return "##";
        case TK_LESSCOLON:
            return "<:";
        case TK_COLONGREATER:
            return ":>";
        case TK_LESSPERCENT:
            return "<%";
        case TK_PERCENTGREATER:
            return "%>";
        case TK_PERCENTCOLON:
            return "%:";
        case TK_DOTDOTDOT:
            return "...";
        case TK_GREATERGREATEREQUAL:
            return ">>=";
        case TK_LESSLESSEQUAL:
            return "<<=";
        case TK_PERCENTCOLONPERCENTCOLON:
            return "/%:/%:";

        case TK_PRE_INCLUDE:
            return "TK_PRE_INCLUDE";

        case TK_PRE_DEFINE:
            return "TK_PRE_DEFINE";
            
        case TK_MACRO_CALL:
            return "TK_MACRO_CALL";

        case TK_MACRO_EOF:
            return "TK_MACRO_EOF";

        case TK_FILE_EOF:
            return "TK_FILE_EOF";
        default:
            
            break;
    }
    return "???";
}

struct ScannerItem * ScannerItem_Create(void) /*@default*/
{
    struct ScannerItem *p = (struct ScannerItem *) Malloc(sizeof * p);
    if (p != NULL)
    {
        ScannerItem_Init(p);
    }
    return p;
}

void ScannerItem_Delete(struct ScannerItem * pScannerItem) /*@default*/
{
    if (pScannerItem != NULL)
    {
        ScannerItem_Destroy(pScannerItem);
        Free((void*)pScannerItem);
    }
}

void ScannerItem_Init(struct ScannerItem * scannerItem) /*@default*/
{
    LocalStrBuilder_Init(&scannerItem->lexeme);
    scannerItem->token = TK_NONE;
    scannerItem->Line =  -1;
    scannerItem->FileIndex =  -1;
    scannerItem->bActive =  1;
    scannerItem->pNext = NULL;
}

void ScannerItem_Reset(struct ScannerItem * scannerItem)
{
    LocalStrBuilder_Clear(&scannerItem->lexeme);
    scannerItem->token = TK_ERROR;
}

void ScannerItem_Copy(struct ScannerItem * scannerItem,
                      struct ScannerItem * other)
{
    scannerItem->token = other->token;
    LocalStrBuilder_Set(&scannerItem->lexeme, other->lexeme.c_str);
}

void ScannerItem_Swap(struct ScannerItem * scannerItem,
                      struct ScannerItem * other)
{
    Tokens tk = other->token;
    other->token = scannerItem->token;
    scannerItem->token = tk;
    LocalStrBuilder_Swap(&scannerItem->lexeme, &other->lexeme);
}

void ScannerItem_Destroy(struct ScannerItem * scannerItem) /*@default*/
{
    LocalStrBuilder_Destroy(&scannerItem->lexeme);
}

void BasicScanner_InitCore(BasicScanner * pBasicScanner,
                           BasicScannerType Type)
{
    pBasicScanner->m_Token = TK_BOF;
    pBasicScanner->Type = Type;
    pBasicScanner->pPrevious = NULL;
    pBasicScanner->FileIndex = -1;
    pBasicScanner->bLineStart = true;
    pBasicScanner->bMacroExpanded = false;
    ScannerItem_Init(&pBasicScanner->currentItem);
    pBasicScanner->currentItem.token = TK_BOF;
}

bool BasicScanner_Init(BasicScanner * pBasicScanner,
                       const char * name,
                       const char * Text,
                       BasicScannerType type)
{
    BasicScanner_InitCore(pBasicScanner, type);
    bool b = Stream_Init(&pBasicScanner->stream, name, Text);
    return b ? true : false;
}

bool BasicScanner_InitFile(BasicScanner * pBasicScanner,
                           const char * fileName)
{
    BasicScanner_InitCore(pBasicScanner, BasicScannerType_File);

    bool b = Stream_InitFile(&pBasicScanner->stream, fileName);
    return b ? true : false;
}

bool BasicScanner_Create(BasicScanner ** pp,
                         const char * name,
                         const char * Text,
                         BasicScannerType Type)
{
    bool result = false  ;
    BasicScanner * p = (BasicScanner *)Malloc(sizeof(BasicScanner));
    if (p)
    {
        result = BasicScanner_Init(p, name, Text, Type);
        if (result == true)
        {
            *pp = p;
        }
        else
        {
            Free(p);
        }
    }
    return result;
}

bool BasicScanner_CreateFile(const char * fileName, BasicScanner ** pp)
{
    bool result = false  ;
    BasicScanner * p = (BasicScanner *)Malloc(sizeof(BasicScanner));
    if (p)
    {
        result = BasicScanner_InitFile(p, fileName);
        if (result == true)
        {
            *pp = p;
        }
        else
        {
            Free(p);
        }
    }
    return result;
}


void BasicScanner_Destroy(BasicScanner * pBasicScanner) /*@default*/
{
    Stream_Destroy(&pBasicScanner->stream);
    ScannerItem_Destroy(&pBasicScanner->currentItem);
}

void BasicScanner_Delete(BasicScanner * pBasicScanner) /*@default*/
{
    if (pBasicScanner != NULL)
    {
        BasicScanner_Destroy(pBasicScanner);
        Free((void*)pBasicScanner);
    }
}

struct TkPair
{
    const char * lexeme;
    Tokens token;
};

static struct TkPair singleoperators[] =
{
    

    {"[", TK_LEFT_SQUARE_BRACKET }, 
    {"]",  TK_RIGHT_SQUARE_BRACKET},
    {"(", TK_LEFT_PARENTHESIS},
    {")", TK_RIGHT_PARENTHESIS},
    {"{", TK_LEFT_CURLY_BRACKET},
    {"}", TK_RIGHT_CURLY_BRACKET},
    {".", TK_FULL_STOP},
    {"&", TK_AMPERSAND},
    {"*", TK_ASTERISK},
    {"+", TK_PLUS_SIGN},
    {"-",  TK_HYPHEN_MINUS},
    {"~", TK_TILDE},
    {"!", TK_EXCLAMATION_MARK},
    {"%", TK_PERCENT_SIGN},
    {"<", TK_LESS_THAN_SIGN},
    {">", TK_GREATER_THAN_SIGN },
    {"^", TK_CIRCUMFLEX_ACCENT },
    {"|", TK_VERTICAL_LINE },
    {"?", TK_QUESTION_MARK},
    {":", TK_COLON },
    {";", TK_SEMICOLON },
    {"=", TK_EQUALS_SIGN},
    {",", TK_COMMA},
    { "$", TK_DOLLAR_SIGN},
    { "@", TK_COMMERCIAL_AT } 
    
    
    
    
};

static struct TkPair doubleoperators[] =
{
    { "->", TK_ARROW },
    { "++", TK_PLUSPLUS },
    { "--", TK_MINUSMINUS },
    { "<<", TK_LESSLESS },
    { ">>", TK_GREATERGREATER },
    { "<=", TK_LESSEQUAL },
    { ">=", TK_GREATEREQUAL },
    { "==", TK_EQUALEQUAL },
    { "!=", TK_NOTEQUAL },
    { "&&", TK_ANDAND },
    { "||", TK_OROR },
    { "*=", TK_MULTIEQUAL },
    { "/=", TK_DIVEQUAL },
    { "%=", TK_PERCENT_EQUAL },
    { "+=", TK_PLUSEQUAL },
    { "-=", TK_MINUS_EQUAL },
    { "&=", TK_ANDEQUAL },
    { "^=", TK_CARETEQUAL },
    { "|=", TK_OREQUAL },
    { "##", TK_NUMBERNUMBER },
    { "<:", TK_LESSCOLON },
    { ":>", TK_COLONGREATER },
    { "<%", TK_LESSPERCENT },
    { "%>", TK_PERCENTGREATER },
    { "%:", TK_PERCENTCOLON },

    { "...", TK_DOTDOTDOT },
    { "%:%:", TK_PERCENTCOLONPERCENTCOLON },
    { "<<=", TK_LESSLESSEQUAL },
    { ">>=", TK_GREATERGREATEREQUAL }
};

static struct TkPair keywords[] =
{
    
    { "auto", TK_AUTO },
    { "break", TK_BREAK },
    { "case", TK_CASE },
    { "char", TK_CHAR },
    { "const", TK_CONST },
    { "continue", TK_CONTINUE },
    { "default", TK_DEFAULT },
    { "do", TK_DO },
    { "double", TK_DOUBLE },
    { "else", TK_ELSE },
    { "enum", TK_ENUM },
    { "extern", TK_EXTERN },
    { "float", TK_FLOAT },
    { "for", TK_FOR },
    { "goto", TK_GOTO },
    { "if", TK_IF },
    { "inline", TK_INLINE },
    { "__inline", TK__INLINE },
    {"__forceinline", TK__FORCEINLINE },
    { "int", TK_INT },
    { "long", TK_LONG },
    
    { "__int8", TK__INT8},
    { "__int16", TK__INT16 },
    { "__int32", TK__INT32 },
    { "__int64", TK__INT64 },
    { "__wchar_t", TK__WCHAR_T},
    
    { "register", TK_REGISTER },
    { "restrict", TK_RESTRICT },
    { "return", TK_RETURN },
    { "short", TK_SHORT },
    { "signed", TK_SIGNED },
    { "sizeof", TK_SIZEOF },
    { "static", TK_STATIC },
    { "struct", TK_STRUCT },
    { "switch", TK_SWITCH },
    { "typedef", TK_TYPEDEF },
    { "union", TK_UNION },

    { "unsigned", TK_UNSIGNED },
    { "void", TK_VOID },
    { "volatile", TK_VOLATILE },
    { "while", TK_WHILE },
    { "_Alignas", TK__ALIGNAS },
    { "_Alignof", TK__ALINGOF },
    { "_Atomic", TK__ATOMIC },

    { "_Bool", TK__BOOL },
    { "_Complex", TK__COMPLEX },
    { "_Generic", TK__GENERIC },
    { "_Imaginary", TK__IMAGINARY },
    { "_Noreturn", TK__NORETURN },
    { "_Static_assert", TK__STATIC_ASSERT },
    { "_Thread_local", TK__THREAD_LOCAL },
    
    { "__asm", TK__ASM } 

};
void BasicScanner_Next(BasicScanner * scanner);
void BasicScanner_Match(BasicScanner * scanner)
{
    BasicScanner_Next(scanner);
}

bool BasicScanner_MatchToken(BasicScanner * scanner, Tokens token)
{
    bool b = false;
    if (scanner->currentItem.token == token)
    {
        b = true;
        BasicScanner_Match(scanner);
    }
    return b;
}


void BasicScanner_Next(BasicScanner * scanner)
{
    if (scanner->Type == BasicScannerType_Token)
    {
        if (scanner->bLineStart)
        {
            ScannerItem_Reset(&scanner->currentItem);
            scanner->currentItem.token = scanner->m_Token;
            LocalStrBuilder_Set(&scanner->currentItem.lexeme,
                                scanner->stream.Text);
            scanner->bLineStart = false;
        }
        else
        {
            scanner->currentItem.token = TK_EOF;
        }
        return;
    }

    if (scanner->currentItem.token == TK_MACRO_EOF ||
        scanner->currentItem.token == TK_FILE_EOF)
    {
        scanner->currentItem.token = TK_EOF;
        return;
    }


    scanner->currentItem.Line = scanner->stream.Line;
    scanner->currentItem.FileIndex = scanner->FileIndex;

    
    
    wchar_t ch = '\0';
    ScannerItem_Reset(&scanner->currentItem);
    ch = scanner->stream.Character;
    wchar_t ch1 = Stream_LookAhead(&scanner->stream);
    if (ch == '.' && ch1 == '.')
    {
        BasicScanner_MatchChar(scanner);
        ch = BasicScanner_MatchChar(scanner);
        if (ch != '.')
        {
            scanner->currentItem.token = TK_ERROR;
        }
        BasicScanner_MatchChar(scanner);
        scanner->currentItem.token = TK_DOTDOTDOT;
        return;
    }
    
    for (int i = 0; i < sizeof(doubleoperators) / sizeof(doubleoperators[0]); i++)
    {
        if (doubleoperators[i].lexeme[0] == ch &&
            doubleoperators[i].lexeme[1] == ch1)
        {
            scanner->currentItem.token = doubleoperators[i].token;
            BasicScanner_MatchChar(scanner);
            BasicScanner_MatchChar(scanner);
            scanner->bLineStart = false;
            return;
        }
    }

    if (ch == '*' && ch1 == '/')
    {
        scanner->currentItem.token = TK_CLOSE_COMMENT;
        ch = BasicScanner_MatchChar(scanner);
        ch = BasicScanner_MatchChar(scanner);

        return;
    }

    
    for (int i = 0; i < sizeof(singleoperators) / sizeof(singleoperators[0]); i++)
    {
        if (singleoperators[i].lexeme[0] == ch)
        {
            scanner->currentItem.token = singleoperators[i].token;
            BasicScanner_MatchChar(scanner);
            scanner->bLineStart = false;
            return;
        }
    }
    
    
    
    
    
    if (ch == L'"' ||
        (ch == L'L' && ch1 == L'"'))
    {
        if (ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner); 
        }
        scanner->currentItem.token = TK_STRING_LITERAL;
        ch = BasicScanner_MatchChar(scanner);
        for (;;)
        {
            if (ch == '\"')
            {
                ch = BasicScanner_MatchChar(scanner);
                break;
            }
            else if (ch == '\\')
            {
                
                ch = BasicScanner_MatchChar(scanner);
                ch = BasicScanner_MatchChar(scanner);
            }
            else if (ch == '\0')
            {
                
                scanner->currentItem.token = TK_EOF;
                break;
            }
            else
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }
        scanner->bLineStart = false;
        return;
    }
    
    
    if (ch == L'\'' ||
        (ch == L'L' && ch1 == L'\''))
    {
        if (ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner); 
        }
        scanner->currentItem.token = TK_CHAR_LITERAL;
        ch = BasicScanner_MatchChar(scanner); 
        if (ch == '\\')
        {
            
            ch = BasicScanner_MatchChar(scanner); 
            ch = BasicScanner_MatchChar(scanner); 
        }
        else
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        ch = BasicScanner_MatchChar(scanner);
        scanner->bLineStart = false;
        return;
    }
    
    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z') ||
        ch == '_')
    {
        scanner->currentItem.token = TK_IDENTIFIER;
        ch = BasicScanner_MatchChar(scanner);
        while ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
               (ch >= '0' && ch <= '9') ||
               ch == '_')
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        
        for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        {
            if (BasicScanner_IsLexeme(scanner, keywords[i].lexeme))
            {
                scanner->currentItem.token = keywords[i].token;
                
                
                break;
            }
        }
        scanner->bLineStart = false;
        return;
    }

    

    if (ch == '0' &&
        (
        (ch1 == 'x' || ch1 == 'X') || 
        (ch1 >= '0' && ch1 <= '9')) 
        )
    {
        ch = BasicScanner_MatchChar(scanner);
        if (ch == 'x' || ch == 'X')
        {
            scanner->currentItem.token = TK_HEX_INTEGER;
        }
        else if (ch1 >= '0' && ch1 <= '9')
        {
            scanner->currentItem.token = TK_OCTAL_INTEGER;
        }
        else
        {
            assert(false);
        }
        ch = BasicScanner_MatchChar(scanner);


        while ((ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'F') ||
               (ch >= 'a' && ch <= 'f'))
        {
            ch = BasicScanner_MatchChar(scanner);
        }

        
        if (ch == 'u' || ch == 'U')
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        if (ch == 'l' || ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner);
            if (ch == 'l' || ch == 'L')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
            else if (ch == 'u' || ch == 'U')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
            else
            {
                
            }
        }
        else if (ch == 'i' || ch == 'I')
        {
            ch = BasicScanner_MatchChar(scanner);
            if (ch == '3')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '2')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '1')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '6')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '6')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '4')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '8')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }

        return;
    }
    
    if (ch >= '0' && ch <= '9')
    {
        scanner->currentItem.token = TK_DECIMAL_INTEGER;
        ch = BasicScanner_MatchChar(scanner);
        while ((ch >= '0' && ch <= '9'))
        {
            ch = BasicScanner_MatchChar(scanner);
        }

        
        if (ch == 'u' || ch == 'U')
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        if (ch == 'l' || ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner);
            if (ch == 'l' || ch == 'L')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
            else if (ch == 'u' || ch == 'U')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
            else
            {
                
            }
        }
        else if (ch == 'i' || ch == 'I')
        {
            ch = BasicScanner_MatchChar(scanner);
            if (ch == '3')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '2')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '1')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '6')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '6')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '4')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                else
                {
                    
                }
            }
            else if (ch == '8')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }
        else
        {
            if (ch == '.')
            {
                ch = BasicScanner_MatchChar(scanner);
                scanner->currentItem.token = TK_FLOAT_NUMBER;
                while ((ch >= '0' && ch <= '9'))
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
            }

            if (scanner->stream.Character == 'e' ||
                scanner->stream.Character == 'E')
            {
                ch = BasicScanner_MatchChar(scanner);
                if (ch == '-' ||
                    ch == '+')
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
                while ((ch >= '0' && ch <= '9'))
                {
                    ch = BasicScanner_MatchChar(scanner);
                }
            }

            if (ch == 'L' || ch == 'l' || ch == 'F' || ch == 'f')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }

        scanner->bLineStart = false;
        return;
    }
    
    if (ch == '\n' || ch == L'\r')
    {
        scanner->currentItem.token = TK_BREAKLINE;
        if (ch == L'\r' && ch1 == L'\n')
        {
            
            Stream_Match(&scanner->stream);
            ch = scanner->stream.Character;
            ch = BasicScanner_MatchChar(scanner);
        }
        else
        {
            ch = BasicScanner_MatchChar(scanner);
            LocalStrBuilder_Clear(&scanner->currentItem.lexeme);
            
            LocalStrBuilder_Append(&scanner->currentItem.lexeme, "\r\n");
        }
        scanner->bLineStart = true;
        return;
    }
    if (ch == '\0')
    {
        if (scanner->bMacroExpanded)
        {
            scanner->currentItem.token = TK_MACRO_EOF;
        }
        else
        {
            scanner->currentItem.token = TK_FILE_EOF;
        }

        scanner->bLineStart = false;
        return;
    }
    if (ch == '\f')
    {
        scanner->currentItem.token = TK_SPACES;
        BasicScanner_MatchChar(scanner);
        return;
    }
    
    if (ch == ' ' || ch == '\t')
    {
        scanner->currentItem.token = TK_SPACES;
        ch = BasicScanner_MatchChar(scanner);
        while (ch == ' ' || ch == '\t')
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        
        return;
    }
    if (ch < 32)
    {
        scanner->currentItem.token = TK_SPACES;
    }
    
    if (scanner->stream.Character == '#')
    {
        ch = BasicScanner_MatchChar(scanner);
        if (scanner->bLineStart)
        {
            scanner->currentItem.token = TK_PREPROCESSOR;
        }
        else
        {
            scanner->currentItem.token = TK_NUMBER_SIGN;
        }
        return;
    }



    
    if (ch == '/')
    {
        if (ch1 == '/')
        {
            scanner->currentItem.token = TK_LINE_COMMENT;
            ch = BasicScanner_MatchChar(scanner);
            ch = BasicScanner_MatchChar(scanner);
            while (ch != '\r' &&
                   ch != '\n' &&
                   ch != '\0')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }
        else if (ch1 == '*')
        {
            scanner->currentItem.token = TK_COMMENT;
            ch = BasicScanner_MatchChar(scanner);
            ch = BasicScanner_MatchChar(scanner);
            if (ch == '@')
            {
                scanner->currentItem.token = TK_OPEN_COMMENT;
                ch = BasicScanner_MatchChar(scanner);
            }
            else
            {
                for (;;)
                {
                    if (ch == '*')
                    {
                        ch = BasicScanner_MatchChar(scanner);
                        if (ch == '/')
                        {
                            ch = BasicScanner_MatchChar(scanner);
                            break;
                        }
                    }
                    else if (ch == L'\r')
                    {
                        
                        Stream_Match(&scanner->stream);
                        ch = scanner->stream.Character;
                        if (ch == L'\n')
                        {
                            ch = BasicScanner_MatchChar(scanner);
                        }
                        else
                        {
                        }
                    }
                    else if (ch == L'\n')
                    {
                        ch = BasicScanner_MatchChar(scanner);
                    }
                    else
                    {
                        ch = BasicScanner_MatchChar(scanner);
                    }
                }
            }



            return;
        }
        else
        {
            scanner->currentItem.token = TK_SOLIDUS;
            ch = BasicScanner_MatchChar(scanner);
        }
        return;
    }
    
    if (ch == L'\\' &&
        (ch1 == L'\n' || ch1 == L'\r'))
    {
        
        
        
        
        
        
        
        
        

        ch = BasicScanner_MatchChar(scanner);

        if (ch == L'\r')
        {
            ch = BasicScanner_MatchChar(scanner);

            if (ch == L'\n')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }
        else if (ch == L'\n')
        {
            BasicScanner_MatchChar(scanner);
        }

        
        LocalStrBuilder_Set(&scanner->currentItem.lexeme, "\\\n");

        scanner->currentItem.token = TK_BACKSLASHBREAKLINE;
        scanner->bLineStart = false;
        

        return;
    }
    if (ch == 2)  
    {
        ch = BasicScanner_MatchChar(scanner);
        scanner->currentItem.token = TK_MACROPLACEHOLDER;
        scanner->bLineStart = false;
        return;
    }
    if (ch == '\\')
    {
        ch = BasicScanner_MatchChar(scanner);
        scanner->currentItem.token = REVERSE_SOLIDUS;
        return;
    }

    if (scanner->currentItem.token == TK_ERROR)
    {
        printf("invalid char, scanner");
    }
    
}


Tokens BasicScanner_Token(BasicScanner * scanner)
{
    return scanner->currentItem.token;
}

const char * BasicScanner_Lexeme(BasicScanner * scanner)
{
    return scanner->currentItem.lexeme.c_str;
}

bool BasicScanner_IsLexeme(BasicScanner * scanner, const char * psz)
{
    return strcmp(BasicScanner_Lexeme(scanner), psz) == 0;
}

wchar_t BasicScanner_MatchChar(BasicScanner * scanner)
{
    LocalStrBuilder_AppendChar(&scanner->currentItem.lexeme,
        (char)scanner->stream.Character);
    Stream_Match(&scanner->stream);
    return scanner->stream.Character;
}





void BasicScannerStack_Init(BasicScannerStack * stack)
{
    *stack = NULL;
}

void BasicScannerStack_Push(BasicScannerStack * stack, BasicScanner * pItem)
{
    if (*stack == NULL)
    {
        *stack = pItem;
    }
    else
    {
        pItem->pPrevious = *stack;
        *stack = pItem;
    }
}

BasicScanner * BasicScannerStack_PopGet(BasicScannerStack * stack)
{
    BasicScanner * pItem = NULL;
    if (*stack != NULL)
    {
        pItem = *stack;
        *stack = pItem->pPrevious;
    }
    return pItem;
}

void BasicScannerStack_PopIfNotLast(BasicScannerStack * stack)
{
    
    if ((*stack)->pPrevious != NULL)
    {
        BasicScanner_Delete(BasicScannerStack_PopGet(stack));
    }
}

void BasicScannerStack_Pop(BasicScannerStack * stack)
{
    BasicScanner_Delete(BasicScannerStack_PopGet(stack));
}

void BasicScannerStack_Destroy(BasicScannerStack * stack)
{
    BasicScanner * pItem = *stack;
    while (pItem)
    {
        BasicScanner * p = pItem;
        pItem = pItem->pPrevious;
        BasicScanner_Delete(p);
    }
}















#ifdef USE_UTF8
#include  "Utf8.h"
#endif




void StrBuilder_Init(StrBuilder * p) /*@default*/
{
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
}

void StrBuilder_Swap(StrBuilder * str1,
    StrBuilder * str2)
{
    StrBuilder temp_Moved = *str1;
    *str1 = *str2;
    *str2 = temp_Moved;
}

void StrBuilder_Destroy(StrBuilder * p)
{
    if (p)
    {
        Free(p->c_str);
        p->c_str = NULL;
        p->size = 0;
        p->capacity = 0;
    }
}

bool StrBuilder_Reserve(StrBuilder * p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        char * pnew = (char *)Realloc(p->c_str,
            (nelements + 1) * sizeof(p->c_str[0]));

        if (pnew)
        {
            if (p->c_str == NULL)
            {
                pnew[0] = '\0';
            }

            p->c_str = pnew;
            p->capacity = nelements;
        }

        else
        {
            r = false  ;
        }
    }

    return r;
}

static bool StrBuilder_Grow(StrBuilder * p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        r = StrBuilder_Reserve(p, new_nelements);
    }

    return r;
}

bool StrBuilder_SetN(StrBuilder * p,
    const char * source,
    int nelements)
{
    bool r = StrBuilder_Grow(p, nelements);

    if (r)
    {
        strncpy(p->c_str,   source, nelements);
        p->c_str[nelements] = '\0';
        p->size = nelements;
    }

    return r;
}

bool StrBuilder_Set(StrBuilder * p,
    const char * source)
{
    bool r = true;
    if (source == NULL)
    {
        StrBuilder_Clear(p);
    }
    else
    {
        int n = strlen(source);
        StrBuilder_Clear(p);

        if (n > 0)
        {
            r = StrBuilder_SetN(p, source, strlen(source));
        }
    }
    return r;
}

bool StrBuilder_AppendN(StrBuilder * p,
    const char * source,
    int nelements)
{
    if (source == NULL || source[0] == '\0')
    {
        return true;
    }

    bool r = StrBuilder_Grow(p, p->size + nelements);

    if (r == true)
    {
        strncpy(p->c_str + p->size,
             
            source,
            nelements);
        p->c_str[p->size + nelements] = '\0';
        p->size += nelements;
    }

    return r;
}

bool StrBuilder_AppendIdent(StrBuilder * p,
    int nspaces,
    const char * source)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }
    return StrBuilder_Append(p, source);
}

bool StrBuilder_Append(StrBuilder * p,
    const char * source)
{
    if (source == NULL || source[0] == '\0')
    {
        return true;
    }

    return StrBuilder_AppendN(p, source, strlen(source));
}

void StrBuilder_Clear(StrBuilder * p)
{
    if (p->c_str != NULL)
    {
        p->c_str[0] = '\0';
        p->size = 0;
    }
}

char * StrBuilder_Release(StrBuilder * p)
{
    char * pResult = p->c_str;

    if (pResult != NULL)
    {
        p->c_str = NULL;
        p->size = 0;
        p->capacity = 0;
    }

    return pResult;
}


void StrBuilder_Attach(StrBuilder * pStrBuilder,
    char * psz,
    int nBytes)
{
    if (psz != NULL)
    {
        
        StrBuilder_Destroy(pStrBuilder);
        pStrBuilder->c_str = psz;
        pStrBuilder->capacity = nBytes - 1;
        pStrBuilder->size = 0;
        pStrBuilder->c_str[0] = '\0';
    }
}

bool StrBuilder_AppendWChar(StrBuilder * p, wchar_t wch)
{
#ifdef USE_UTF8
    char buffer[5] = { 0 };
    int nbytes = EncodeCharToUTF8Bytes(wch, buffer);
    return StrBuilder_AppendN(p, buffer, nbytes);
#else
    char ch = (char)wch;
    return StrBuilder_AppendN(p, &ch, 1);
#endif
}


bool StrBuilder_AppendChar(StrBuilder * p, char ch)
{
    return StrBuilder_AppendN(p, &ch, 1);
}

bool StrBuilder_AppendW(StrBuilder * p, const wchar_t * psz)
{
    bool result = false;

    while (*psz)
    {
        result = StrBuilder_AppendWChar(p, *psz);

        if (result != true)
        {
            break;
        }

        psz++;
    }

    return result;
}


void StrBuilder_Trim(StrBuilder * p)
{
    StrBuilder temp;
    StrBuilder_Init(&temp);

    StrBuilder_Reserve(&temp, p->size);

    bool bCopy = false;

    for (int i = 0; i < p->size; i++)
    {
        char ch = p->c_str[i];

        if (!bCopy && ch != ' ')
        {
            
            bCopy = true;
        }

        if (bCopy)
            StrBuilder_AppendChar(&temp, ch);
    }

    
    int k = ((int)(temp.size)) - 1;

    for (; k >= 0; k--)
    {
        char ch = temp.c_str[k];

        if (ch != ' ')
        {
            break;
        }
    }

    temp.c_str[k + 1] = '\0';
    temp.size = k + 1;
    StrBuilder_Swap(&temp, p);
    StrBuilder_Destroy(&temp);
}



bool StrBuilder_AppendUpper(StrBuilder * p, const char * s)
{
    if (s != NULL)
    {
        while (*s)
        {
            StrBuilder_AppendChar(p, toupper(*s));
            s++;
        }
    }

    return true;
}


void StrBuilder_AppendFmtV(StrBuilder * p, const char * fmt, va_list va)
{
    char buffer[500];
    vsnprintf(buffer, 500, fmt, va);
    StrBuilder_Append(p, buffer);
}

void StrBuilder_AppendFmt(StrBuilder * p, const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

}

void StrBuilder_AppendFmtIdent(StrBuilder * p, int nspaces, const char * fmt, ...)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }

    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

}

void StrBuilder_AppendFmtLn(StrBuilder * p,
    int nspaces,
    const char * fmt,
    ...)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }

    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

    StrBuilder_Append(p, "\n");
}















bool LoadFile(const char * filename, const char ** out, int * szOut)
{
    bool result = false;
    int lSize = 0;
    FILE * fp = (FILE *)fopen(filename, "rb");

    if (fp)
    {
        fseek(fp, 0L, SEEK_END);
        lSize = ftell(fp);
        rewind(fp);
        char * buffer = (char *)Malloc(lSize + 1);

        if (buffer)
        {
              fread(buffer, 1, lSize, fp);

            if (feof(fp))
            {
                
            }

            if (!ferror(fp))
            {
                
                buffer[lSize] = '\0';
                *out = buffer;
                buffer = NULL;
                result = true;
                *szOut = lSize;
            }

            Free(buffer);
        }

        fclose(fp);
    }

    return result;
}


bool Stream_InitFile(struct Stream * pStream,
                     const char * fullPath)
{
    
    pStream->NameOrFullPath = StrDup(fullPath);
    pStream->FullDir2 = NULL;
    pStream->Line = 1;
    pStream->Column = 1;
    pStream->Position = 0;
    bool result = LoadFile(fullPath, (const char **)& pStream->Text,
                           &pStream->TextLen);

    if (result)
    {
        
        GetFullDir(fullPath, &pStream->FullDir2);

        if (pStream->Text != NULL &&
            pStream->Text[0] != '\0')
        {
            
            pStream->Character = pStream->Text[0];
        }

        else
        {
            pStream->Character = '\0';
        }
    }

    return result;
}

bool Stream_Init(struct Stream * pStream, const char * name, const char * Text)
{
    pStream->Line = 1;
    pStream->Column = 1;
    pStream->Position = 0;
    pStream->Text = StrDup(Text);
    pStream->NameOrFullPath = StrDup(name);
    pStream->FullDir2 = StrDup("");

    if (Text != NULL)
    {
        pStream->TextLen = strlen(Text);
    }

    else
    {
        pStream->TextLen = 0;
    }

    if (pStream->Text != NULL &&
        pStream->Text[0] != '\0')
    {
        
        pStream->Character = pStream->Text[0];
    }

    else
    {
        pStream->Character = '\0';
    }

    return true;
}


void Stream_Destroy(struct Stream * pStream) /*@default*/
{
    Free((void*)pStream->NameOrFullPath);
    Free((void*)pStream->FullDir2);
    Free((void*)pStream->Text);
}


wchar_t Stream_LookAhead(struct Stream * pStream)
{
    if (pStream->Position + 1 >= pStream->TextLen)
    {
        return '\0';
    }

    return pStream->Text[pStream->Position + 1];
}

bool Stream_MatchChar(struct Stream * pStream, wchar_t ch)
{
    bool b = pStream->Character == ch;
    Stream_Match(pStream);
    return b;
}

void Stream_Match(struct Stream * pStream)
{
    if (pStream->Position >= pStream->TextLen)
    {
        pStream->Character = L'\0';
        return;
    }

    pStream->Column++;
    pStream->Position++;

    if (pStream->Position == pStream->TextLen)
    {
        pStream->Character = '\0';
    }

    else
    {
        pStream->Character = pStream->Text[pStream->Position];
    }

    if (pStream->Character == '\n')
    {
        pStream->Line++;
        pStream->Column = 0;
    }
}









void LocalStrBuilder_Init(struct LocalStrBuilder * p)
{
    p->capacity = LOCALSTRBUILDER_NCHARS;
    p->size = 0;
    p->c_str = p->chars;
}

void LocalStrBuilder_Swap(struct LocalStrBuilder * pA, struct LocalStrBuilder * pB)
{
    int bA = (pA->c_str == pA->chars);
    int bB = (pB->c_str == pB->chars);

    struct LocalStrBuilder temp = *pA;
    *pA = *pB;
    *pB = temp;

    if (bA)
    {
        pB->c_str = pB->chars;
    }
    if (bB)
    {
        pA->c_str = pA->chars;
    }
}

void LocalStrBuilder_Destroy(struct LocalStrBuilder * p)
{
    if (p->c_str != p->chars)
    {
        Free(p->c_str);
    }
}

void LocalStrBuilder_Reserve(struct LocalStrBuilder * p, int nelements)
{
    if (nelements > p->capacity)
    {
        char * pnew = NULL;
        if (nelements <= LOCALSTRBUILDER_NCHARS)
        {
            pnew = p->chars;
            p->capacity = LOCALSTRBUILDER_NCHARS;
            p->c_str = pnew;
        }
        else
        {
            if (p->capacity <= LOCALSTRBUILDER_NCHARS)
            {
                pnew = (char *)Malloc((nelements + 1) * sizeof(char));
                memcpy(pnew, p->chars, LOCALSTRBUILDER_NCHARS);
            }
            else
            {
                pnew = (char *)Realloc(p->c_str, (nelements + 1) * sizeof(char));
            }

            p->c_str = pnew;

            if (p->size == 0)
            {
                pnew[0] = '\0';
            }
            p->capacity = nelements;
        }
    }
}

void LocalStrBuilder_Print(struct LocalStrBuilder * p)
{
    printf("size = %d, capacity = %d, c_str = '%s', internal buffer = %s \n",
        (int)p->size,
           (int)p->capacity,
           p->c_str,
           (p->c_str == p->chars ? "yes" : "no"));
}

void LocalStrBuilder_Clear(struct LocalStrBuilder * p)
{
    if (p->c_str)
    {
        p->c_str[0] = 0;
    }
    p->size = 0;
}

void LocalStrBuilder_Grow(struct LocalStrBuilder * p, int nelements)
{
    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        LocalStrBuilder_Reserve(p, new_nelements);
    }
}

void LocalStrBuilder_Append(struct LocalStrBuilder * p, const char * source)
{
    while (*source)
    {
        LocalStrBuilder_AppendChar(p, *source);
        source++;
    }
}


void LocalStrBuilder_Set(struct LocalStrBuilder * p, const char * source)
{
    LocalStrBuilder_Clear(p);
    while (*source)
    {
        LocalStrBuilder_AppendChar(p, *source);
        source++;
    }
}



void LocalStrBuilder_AppendChar(struct LocalStrBuilder * p, char ch)
{
    LocalStrBuilder_Grow(p, p->size + 1);

    p->c_str[p->size] = ch;
    p->c_str[p->size + 1] = 0;
    p->size++;
}










 
static uint32_t HashFunc(const char * a)
{
    
    int len = strlen(a);
    const char * key = a;
    uint32_t hash = 0;


    for (int i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

bool Bucket_Reserve(Bucket * p, int nelements);

bool BucketItem_InitMoveKey(struct BucketItem * node,
                            int hash,
                            String * *key  ,
                            void * data)
{
    node->data = data;
    node->hash = hash;

    node->key = *key;
    *key = NULL;

    return true;
}


bool BucketItem_Init(struct BucketItem * node,
                     int hash,
                     const char * key,
                     void * data)
{
    node->key = StrDup(key);
    node->data = data;
    node->hash = hash;
    return true;
}

bool BucketItem_CreateMoveKey(struct BucketItem ** pp,
                              int hash,
                              String * *key,
                              void * data)
{
    bool result = false  ;
    struct BucketItem * node = (struct BucketItem *)Malloc(sizeof(struct BucketItem) * 1);
    if (node)
    {
        BucketItem_InitMoveKey(node,
                               hash,
                               key,
                               data);
        *pp = node;
        result = true;
    }
    return result;
}

bool BucketItem_Change(struct BucketItem * p,
                       void * data)
{
    p->data = data;
    return true;
}

void BucketItem_Destroy(struct BucketItem * node, void(*pfDestroyData)(void *))
{
    Free(node->key);
    if (pfDestroyData)
    {
        pfDestroyData(node->data);
    }
}

void BucketItem_Delete(struct BucketItem * p, void(*pfDestroyData)(void *))
{
    if (p)
    {
        BucketItem_Destroy(p, pfDestroyData);
        Free(p);
    }
}

bool Bucket_Init(Bucket * p, int capacity)
{
    bool result = true;
    p->data = NULL;
    p->size = 0;
    p->capacity = 0;

    if (capacity > 0)
    {
        result = Bucket_Reserve(p, capacity);
    }

    return result;
}

bool Bucket_Create(Bucket * *pp)
{
    bool result = false  ;
    Bucket * p = (Bucket *)Malloc(sizeof(Bucket) * 1);
    if (p)
    {
        result = Bucket_Init(p, 0);
        if (result == true)
        {
            *pp = p;
            p = NULL;
        }
        Free(p);
    }
    return result;
}


void Bucket_Destroy(Bucket * p, void(*pfDestroyData)(void *))
{
    for (int i = 0; i < p->size; i++)
    {
        BucketItem_Delete(p->data[i], pfDestroyData);
    }
    Free(p->data);
}


void Bucket_Delete(Bucket * p, void(*pfDestroyData)(void *))
{
    if (p)
    {
        Bucket_Destroy(p, pfDestroyData);
        Free(p);
    }
}


bool Bucket_Reserve(Bucket * p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        struct BucketItem ** pnew = (struct BucketItem **)Realloc(p->data,
            (nelements + 1) * sizeof(p->data[0]));

        if (pnew)
        {
            if (p->data == NULL)
            {
                pnew[0] = NULL;
            }

            p->data = pnew;
            p->capacity = nelements;
        }
        else
        {
            
            r = false  ;
        }
    }

    return r;
}
static bool Grow(Bucket * p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        r = Bucket_Reserve(p, new_nelements);
    }

    return r;
}

bool Bucket_Append(Bucket * p, struct BucketItem * pItem)
{
    bool result = Grow(p, p->size + 1);

    if (result == true)
    {
        p->data[p->size] = pItem;
        p->size++;
    }

    return result;
}

static int FindNodeIndex(Bucket * bucket, uint32_t hash, const char * key)
{
    
    for (int i = 0; i < bucket->size; i++)
    {
        struct BucketItem * node = bucket->data[i];
        if (node->hash == hash &&
            strcmp(node->key, key) == 0)
        {
            return (int)i;
        }
    }

    return -1;
}

bool RemoveBucketItem(Bucket * bucket,
                      uint32_t hash,
                      const char * key,
                      void ** ppData)
{
    
    *ppData = NULL; 

    int index = FindNodeIndex(bucket, hash, key);
    bool result = index != -1 ? true : false;

    if (result == true)
    {
        
        *ppData = bucket->data[index]->data;

        if (index != (int)(bucket->size) - 1)
        {
            
            struct BucketItem * pTemp = bucket->data[bucket->size - 1];
            bucket->data[bucket->size - 1] = bucket->data[index];
            bucket->data[index] = pTemp;
        }

        BucketItem_Delete(bucket->data[bucket->size - 1], NULL);
        bucket->size--;
    }


    return result;
}


bool Buckets_Init(Buckets * p,
                  int size)
{
    bool result = false  ;
    p->data = NULL;
    p->size = size;

    p->data = (Bucket * *)Malloc(sizeof(Bucket *) * size);
    if (p->data)
    {
        for (int i = 0; i < size; i++)
        {
            p->data[i] = NULL;
        }
        result = true;
    }

    return result;
}

void Buckets_Destroy(Buckets * p, void(*pfDestroyData)(void *))
{
    for (int i = 0; i < p->size; i++)
    {
        Bucket_Delete(p->data[i],
                      pfDestroyData);
    }
    Free(p->data);
}


bool Map_Init(Map * map, int nBuckets)
{
    map->Size = 0;
    bool result = Buckets_Init(&map->buckets, nBuckets);
    if (result == true)
    {
    }
    return result;
}

bool Map_Create(Map * *pp, int nBuckets)
{
    bool result = false  ;
    Map * p = (Map *)Malloc(sizeof(Map));
    if (p)
    {
        result = Map_Init(p, nBuckets);
        if (result == true)
        {
            *pp = p;
        }
        else
        {
            Free(p);
        }
    }
    return result;
}

void Map_Destroy(Map * map, void(*pfDestroyData)(void *))
{
    Buckets_Destroy(&map->buckets, pfDestroyData);
}

void Map_Delete(Map * p, void(*pfDestroyData)(void *))
{
    Map_Destroy(p, pfDestroyData);
    Free((void *)p);
}

struct BucketItem * Map_FindNode(Map * map, const char * key)
{
    if (map->buckets.data == NULL)
    {
        return NULL;
    }

    
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket * pBucket = map->buckets.data[bucket_n];

    if (pBucket == NULL)
    {
        return NULL;
    }

    int i = FindNodeIndex(pBucket, hash, key);
    if (i == -1)
    {
        return NULL;
    }

    return pBucket->data[i];
}


bool Map_SetMoveKey(Map * map, String * *key, void * data)
{
    
    bool result;

    struct BucketItem * pNode = Map_FindNode(map, *key);
    if (pNode)
    {
        return BucketItem_Change(pNode, data);
    }

    if (map->buckets.size == 0)
    {
        Buckets_Init(&map->buckets, 100);
    }

    uint32_t hash = HashFunc(*key);
    int bucket_n = hash % map->buckets.size;
    Bucket * bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        result = Bucket_Create(&bucket);
        if (result == true)
        {
            map->buckets.data[bucket_n] = bucket;
        }
    }
    else
    {
        result = true;
    }

    if (result == true)
    {
        struct BucketItem * node;
        result = BucketItem_CreateMoveKey(&node,
                                          hash,
                                          key,
                                          data);
        if (result == true)
        {
            result = Bucket_Append(bucket, node  );
        }
    }

    if (result == true)
    {
        map->Size++;
    }

    return result;
}

bool Map_Set(Map * map, const char * key, void * data)
{
    
    void * pv;
    bool result = Map_Find(map, key, &pv);
    if (result == true)
    {
        return false;
        
    }


    
    String * /*@auto*/ localkey = StrDup(key);
    result = Map_SetMoveKey(map, &localkey, data);
    Free(localkey);
    return result;
}


bool Map_Find(Map * map, const char * key, void ** pp)
{
    
    struct BucketItem * pNode = Map_FindNode(map, key);
    bool result = pNode ? true : false;

    if (result == true)
    {
        *pp = pNode->data;
    }

    return result;
}

void * Map_Find2(Map * map, const char * key)
{
    void * pv;
    bool result = Map_Find(map, key, &pv);

    return result == true ? pv : NULL;
}

bool Map_DeleteEx(Map * map, const char * key, void ** pp)
{
    
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket * bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        return false;
    }

    bool result = RemoveBucketItem(bucket, hash, key, pp);

    if (result == true)
    {
        map->Size--;
    }
    return result;
}

bool Map_DeleteItemOpt(Map * map, const char * key, void(*pfDestroyData)(void *))
{
    
    void * p;
    bool result = Map_DeleteEx(map, key, &p);
    if (result == true)
    {
        if (pfDestroyData != NULL)
        {
            pfDestroyData(p);
        }
    }
    return result;
}

bool Map_DeleteItem(Map * map, const char * key, void(*pfDestroyData)(void *))
{
    bool result = Map_DeleteItemOpt(map, key, pfDestroyData);
    void * p;
    
    if (Map_Find(map, key, &p) == true)
    {
        
        Map_DeleteItemOpt(map, key, pfDestroyData);
    }
    return result;
}


void Map_Print(Map * map)
{
    for (int i = 0; i < map->buckets.size; i++)
    {
        Bucket * data = map->buckets.data[i];
        if (data != NULL)
        {
            for (int k = 0; k < data->size; k++)
            {
                struct BucketItem * node = data->data[k];
                printf("%s", node->key);
            }
        }
    }
}


void Buckets_Swap(Buckets * b1, Buckets * b2)
{
    Bucket ** data2 = b2->data;
    int size2 = b2->size;

    b2->data = b1->data;
    b2->size = b1->size;

    b1->data = data2;
    b1->size = size2;

}

void Map_Swap(Map * map, Map * map2)
{
    Map temp = *map2;
    *map2 = *map;
    *map = temp;
    
}




bool MultiMap_Init(MultiMap * map, int nBuckets)
{
    map->Size = 0;
    bool result = Buckets_Init(&map->buckets, nBuckets);
    if (result == true)
    {
    }
    return result;
}

void MultiMap_Destroy(MultiMap * map, void(*pfDestroyData)(void *))
{
    Buckets_Destroy(&map->buckets, pfDestroyData);
}

bool MultiMap_Add(MultiMap * map, const char * key, void * data)
{
    
    bool result;

    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;
    Bucket * bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        
        result = Bucket_Create(&bucket);
        if (result == true)
        {
            map->buckets.data[bucket_n] = bucket;
        }
    }
    else
    {
        result = true;
    }

    if (result == true)
    {
        
        String * /*@auto*/stemp = StrDup(key);

        struct BucketItem * node;
        result = BucketItem_CreateMoveKey(&node,
                                          hash,
                                          &stemp,
                                          data);

        Free(stemp);

        if (result == true)
        {
            result = Bucket_Append(bucket, node  );
        }
    }

    if (result == true)
    {
        map->Size++;
    }

    return result;
}


Bucket * MultiMap_FindBucket(MultiMap * map, const char * key)
{
    if (map->buckets.data == NULL)
    {
        return NULL;
    }

    
    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;

    Bucket * pBucket = map->buckets.data[bucket_n];

    if (pBucket == NULL)
    {
        return NULL;
    }

    return pBucket;
}

void MultiMap_Swap(MultiMap * map, MultiMap * map2)
{
    MultiMap temp = *map2;
    *map2 = *map;
    *map = temp;
}
 













struct Macro * Macro_Create(void) /*@default*/
{
    struct Macro* p = (struct Macro*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Name = NULL;
        p->bIsFunction = false;
        TokenArray_Init(&p->TokenSequence);
        TokenArray_Init(&p->FormalArguments);
        p->FileIndex = 0;
    }
    return p;
}

void Macro_Destroy(struct Macro * p) /*@default*/
{
    Free((void*)p->Name);
    TokenArray_Destroy(&p->TokenSequence);
    TokenArray_Destroy(&p->FormalArguments);
}

void Macro_Delete(struct Macro * p) /*@default*/
{
    if (p != NULL)
    {
        Macro_Destroy(p);
        Free((void*)p);
    }
}


bool FillIn(struct TokenArray * ts,
            bool get_more,
            struct TokenArray * removed);

void Glue(const struct TokenArray * lsI,
          const struct TokenArray * rsI,
          struct TokenArray * out);


void HidenSetAdd(const TokenSet * hs,
                 const struct TokenArray * ts,
                 struct TokenArray * pOut)
{
    TokenArray_Clear(pOut);


    for (int i = 0; i < ts->Size; i++)
    {
        struct PPToken * t = ts->pItems[i];

        for (int k = 0; k < hs->Size; k++)
        {
            TokenSet_PushBack(&t->HiddenSet, PPToken_Clone(hs->pItems[k]));
        }

        TokenArray_PushBack(pOut, PPToken_Clone(t));
    }

    
    TokenArray_Print(pOut);
    
}

void ExpandMacro(const struct TokenArray * pTokenSequence,
                 const struct MacroMap * macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro * caller,
                 struct TokenArray * pOutputSequence);

 
int FindNoSpaceIndex(const struct TokenArray * pArray, int start)
{
    int result = -1;

    for (int i = start; i < pArray->Size; i++)
    {
        if (!PPToken_IsSpace(pArray->pItems[i]))
        {
            result = i;
            break;
        }
    }

    return result;
}


void AppendEscaped(StrBuilder * strBuilder,
                   const char * source)
{
    while (*source)
    {
        switch (*source)
        {
            case '\\':
            case '"':
                StrBuilder_AppendChar(strBuilder, '\\');

                
            default:
                StrBuilder_AppendChar(strBuilder, *source);
        }

        source++;
    }
}

 
void AppendStringize(StrBuilder * strBuilder, const struct TokenArray * ts)
{
     

     

    StrBuilder_Append(strBuilder, "\"");

    bool seen_space = true;   

    for (int i = 0; i < ts->Size; i++)
    {
        struct PPToken * pToken = ts->pItems[i];

        if (PPToken_IsSpace(pToken))
        {
            if (seen_space)
                continue;

            else
                seen_space = true;

            StrBuilder_Append(strBuilder, " ");
        }

        else if (PPToken_IsStringLit(pToken))
        {
            seen_space = false;
            StrBuilder_Append(strBuilder, "\\\"");
            AppendEscaped(strBuilder, pToken->Lexeme);
            StrBuilder_Append(strBuilder, "\\\"");
        }

        else if (PPToken_IsCharLit(pToken))
        {
            seen_space = false;
            StrBuilder_AppendChar(strBuilder, '\'');
            AppendEscaped(strBuilder, pToken->Lexeme);
            StrBuilder_AppendChar(strBuilder, '\'');
        }

        else
        {
            seen_space = false;
            StrBuilder_Append(strBuilder, pToken->Lexeme);
        }
    }

    StrBuilder_Append(strBuilder, "\"");

    
    StrBuilder_Trim(strBuilder);
}


 
void SubstituteArgs(struct Macro * pMacro,
                    const struct MacroMap * macros,
                    const struct TokenArray * isOriginal,   
                    const TokenArrayMap * args,
                    TokenSet * hs,
                    bool skip_defined,
                    bool evalmode,
                    struct Macro * pCaller,
                    struct TokenArray * pOutputSequence)
{
    TokenArray_Clear(pOutputSequence);

    
    struct TokenArray is = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&is, isOriginal);

    struct TokenArray os = TOKENARRAY_INIT;

    struct PPToken * head = NULL;
    while (is.Size > 0)
    {

        
        TokenArray_Print(&is);
        
        TokenArray_Print(&os);
        

        
        head = TokenArray_PopFront(&is);

        if (PPToken_IsStringizingOp(head))
        {
             

            
            int idx = FindNoSpaceIndex(&is, 0);
            struct TokenArray * aseq;

            if (idx != -1 &&
                args != NULL &&
                TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
            {
                 
                StrBuilder strBuilder = STRBUILDER_INIT;
                AppendStringize(&strBuilder, aseq);
                TokenArray_Erase(&is, 0, idx + 1);

                
                TokenArray_PushBack(&os, PPToken_Create(strBuilder.c_str, PPTokenType_Other));
                StrBuilder_Destroy(&strBuilder);

                PPToken_Delete(head);
                head = NULL;
                continue;
            }

        }

        else if (PPToken_IsConcatOp(head))
        {

             
            int idx = FindNoSpaceIndex(&is, 0);

            if (idx != -1)
            {
                struct TokenArray * aseq;

                if (TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
                {
                    TokenArray_Erase(&is, 0, idx + 1);

                    
                    if (aseq->Size > 0)
                    {
                        struct TokenArray os2 = TOKENARRAY_INIT;
                        Glue(&os, aseq, &os2);
                        TokenArray_Swap(&os2, &os);
                        TokenArray_Destroy(&os2);
                    }
                }

                else
                {
                    struct TokenArray t = TOKENARRAY_INIT;
                    TokenArray_PushBack(&t, PPToken_Clone(is.pItems[idx]));
                    TokenArray_Erase(&is, 0, idx + 1);

                    struct TokenArray os2 = TOKENARRAY_INIT;
                    Glue(&os, &t, &os2);
                    TokenArray_Swap(&os2, &os);
                    TokenArray_Destroy(&os2);
                    TokenArray_Destroy(&t);
                }

                PPToken_Delete(head);
                head = NULL;

                continue;
            }
        }

        else
        {
            int idx = FindNoSpaceIndex(&is, 0);

            if (idx != -1 &&
                PPToken_IsConcatOp(is.pItems[idx]))
            {
                 
                struct TokenArray * aseq;

                if (!TokenArrayMap_Lookup(args, head->Lexeme, &aseq))
                {
                     
                    
                    TokenArray_PushBack(&os, head);
                    head = NULL; 
                }
                else
                {
                    

                    
                    if (aseq->Size == 0)
                    {
                        
                        TokenArray_Erase(&is, 0, idx + 1);

                        int idx2 = FindNoSpaceIndex(&is, 0);

                        if (idx2 != -1)
                        {
                            struct TokenArray * aseq2;

                            if (!TokenArrayMap_Lookup(args, is.pItems[idx2]->Lexeme, &aseq2))
                            {
                                
                                TokenArray_Erase(&is, 0, idx + 1);
                                TokenArray_AppendCopy(&os, aseq);
                            }
                        }
                    }

                    else
                    {
                        
                        TokenArray_Print(&is);
                        
                        TokenArray_Erase(&is, 0, idx);
                        TokenArray_Print(&is);
                        
                        TokenArray_AppendCopy(&os, aseq);
                    }
                }

                PPToken_Delete(head);
                head = NULL;

                continue;
            }

            struct TokenArray * argseq = NULL;

            if (args != NULL &&
                TokenArrayMap_Lookup(args, head->Lexeme, &argseq))
            {
                
                struct TokenArray expanded = TOKENARRAY_INIT;
                ExpandMacro(argseq, macros, false, skip_defined, evalmode, pCaller, &expanded);
                TokenArray_AppendMove(&os, &expanded);
                TokenArray_Destroy(&expanded);

                PPToken_Delete(head);
                head = NULL;

                continue;
            }
        }

        TokenArray_PushBack(&os, head);
        head = NULL; 
    }
    
    struct TokenArray os2 = TOKENARRAY_INIT;
    HidenSetAdd(hs, &os, &os2);

    TokenArray_Swap(pOutputSequence, &os2);

    TokenArray_Destroy(&os);
    TokenArray_Destroy(&os2);
    TokenArray_Destroy(&is);
}

 
void ArgToken(struct TokenArray * tokens,
              bool get_more,
              bool want_space,
              struct PPToken * token)
{
    struct PPToken * pToken = TokenArray_PopFront(tokens);
    PPToken_Swap(pToken, token);
    PPToken_Delete(pToken);
    pToken = NULL;

     
}

 
bool GatherArgs(const char * name,
                struct TokenArray * tokens,
                const struct TokenArray * formal_args,
                TokenArrayMap * args,
                bool get_more,
                bool is_vararg,
                struct PPToken * close)
{
    struct PPToken t = TOKEN_INIT;

    for (int i = 0; i < formal_args->Size; i++)
    {
        struct TokenArray * pV = TokenArray_Create();

        TokenArrayMap_SetAt(args,
                            formal_args->pItems[i]->Lexeme,
                            pV);

        char terminate;

        if (i + 1 == formal_args->Size)
        {
            terminate = ')';
        }

        else if (is_vararg && i + 2 == formal_args->Size)
        {
            
            terminate = '.';
        }

        else
        {
            terminate = ',';
        }

        int bracket = 0;

        
        for (;;)
        {
            ArgToken(tokens, get_more, true, &t);
            
            TokenArray_Print(tokens);
            

            if (bracket == 0 && (
                (terminate == '.' && (PPToken_IsChar(&t, ',') || PPToken_IsChar(&t, ')'))) ||
                (terminate != '.' && PPToken_IsChar(&t, terminate))))
            {
                break;
            }

            if (PPToken_IsChar(&t, '('))
            {
                bracket++;
            }

            else if (PPToken_IsChar(&t, ')'))
            {
                bracket--;
            }

            else if (PPToken_IsChar(&t, '\0')) 
            {
                 
                
                return (false);
            }

            else
            {
            }


            TokenArray_PushBack(pV, PPToken_Clone(&t));
        }

        
        TokenArray_Print(pV);
        

        
        if (terminate == '.' && PPToken_IsChar(&t, ')'))
        {
            i++;
            struct TokenArray * pV2 = TokenArray_Create();

            TokenArrayMap_SetAt(args,
                                formal_args->pItems[i]->Lexeme,
                                pV2);

            
            
            break;
        }

        Free(close->Lexeme);
        close->Lexeme = StrDup(t.Lexeme);
    }

    if (formal_args->Size == 0)
    {
        ArgToken(tokens, get_more, false, &t);

        if (PPToken_IsChar(&t, ')'))
        {
             
            
            return (false);
        }
    }


    PPToken_Destroy(&t);

    return (true);
}

 
void GatherDefinedOperator(struct TokenArray * tokens,
                           const struct MacroMap * macros,
                           struct TokenArray * result)
{
    
    

    
    while (PPToken_IsSpace(tokens->pItems[0]))
    {
        struct PPToken * pp = TokenArray_PopFront(tokens);
        TokenArray_PushBack(result, pp);
    }

    if ((PPToken_IsIdentifier(tokens->pItems[0])))
    {
        
        if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
        {
            struct PPToken * pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("1");


            TokenArray_PushBack(result, pp0);
        }

        else
        {
            struct PPToken * pp0 = TokenArray_PopFront(tokens);
            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("0");

            TokenArray_PushBack(result, pp0);
        }

        return;
    }

    else if ((PPToken_IsChar(tokens->pItems[0], '(')))
    {
        


        PPToken_Delete(TokenArray_PopFront(tokens));




        
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken * pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsIdentifier(tokens->pItems[0]))
        {
            
        }

        if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
        {
            struct PPToken * pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("1");

            TokenArray_PushBack(result, pp0);
        }

        else
        {
            struct PPToken * pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("0");

            TokenArray_PushBack(result, pp0);
        }

        
        

        
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken * pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsChar(tokens->pItems[0], ')'))
        {
            
        }

        PPToken_Delete(TokenArray_PopFront(tokens));
        

        return;
    }

    else
    {
    }
}


void ExpandMacro(const struct TokenArray * tsOriginal,
                 const struct MacroMap * macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro * caller,
                 struct TokenArray * pOutputSequence2)
{
    TokenArray_Clear(pOutputSequence2);

    struct TokenArray r = TOKENARRAY_INIT;

    struct TokenArray ts = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&ts, tsOriginal);

    
    TokenArray_Print(&ts);
    

    struct PPToken * pHead = NULL; 
    while (ts.Size > 0)
    {
        
        TokenArray_Print(&r);
        

        
        pHead =
            TokenArray_PopFront(&ts);

        if (!PPToken_IsIdentifier(pHead))
        {
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; 
            continue;
        }

        if (skip_defined &&
            PPToken_IsIdentifier(pHead) &&
            PPToken_IsLexeme(pHead, "defined"))
        {
            struct TokenArray result = TOKENARRAY_INIT;
            GatherDefinedOperator(&ts, macros, &result);
            TokenArray_AppendMove(&r, &result);

            PPToken_Delete(pHead);
            pHead = NULL;

            TokenArray_Destroy(&result);
            continue;
        }

        struct Macro * pMacro = MacroMap_Find(macros, pHead->Lexeme);

        if (pMacro == NULL)
        {
            
            
            if (evalmode)
            {
                Free(pHead->Lexeme);
                pHead->Lexeme = StrDup("0");
                pHead->Token = PPTokenType_Number;
            }
            
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; 
            continue;
        }

        struct PPToken * pFound =
            TokenSet_Find(&pHead->HiddenSet, pMacro->Name);

        if (pFound)
        {
            
            
            TokenArray_PushBack(&r, pHead);
            pHead = NULL;
            continue;
        }

        struct TokenArray removed_spaces = TOKENARRAY_INIT;

        
        TokenArray_Print(&ts);
        

        if (!pMacro->bIsFunction)
        {
            
            

            TokenSet hiddenSet = TOKENSET_INIT;
            TokenSetAppendCopy(&hiddenSet, &pHead->HiddenSet);
            TokenSet_PushBack(&hiddenSet, PPToken_Create(pHead->Lexeme, pHead->Token));

            PPToken_Delete(pHead);
            pHead = NULL; 

            struct TokenArray s = TOKENARRAY_INIT;

            SubstituteArgs(pMacro,
                           macros,
                           &pMacro->TokenSequence,
                           NULL, 
                           &hiddenSet,
                           skip_defined,
                           evalmode,
                           caller,
                           &s);

            TokenArray_AppendMove(&s, &ts);
            TokenArray_Swap(&s, &ts);

            TokenArray_Destroy(&s);
            TokenSet_Destroy(&hiddenSet);

            caller = pMacro;
        }

        else if (FillIn(&ts, get_more, &removed_spaces) &&
                 PPToken_IsOpenPar(ts.pItems[0]))
        {
            

            
            TokenArrayMap args = TOKENARRAYMAP_INIT;

            PPToken_Delete(TokenArray_PopFront(&ts));

            struct PPToken close = TOKEN_INIT;

            if (!GatherArgs(pHead->Lexeme,
                &ts,
                &pMacro->FormalArguments,
                &args,
                get_more,
                false,  
                &close))
            {
                PPToken_Destroy(&close);
                PPToken_Delete(pHead);
                pHead = NULL;
                continue; 
            }


             

            TokenSet hs = TOKENSET_INIT;

            
            SetIntersection(&pHead->HiddenSet,
                            &close.HiddenSet,
                            &hs);
            TokenSet_PushBack(&hs, PPToken_Create(pMacro->Name, PPTokenType_Identifier));

            PPToken_Delete(pHead);
            pHead = NULL;

            struct TokenArray s = TOKENARRAY_INIT;

            SubstituteArgs(pMacro,
                           macros,
                           &pMacro->TokenSequence,
                           &args,
                           &hs,
                           skip_defined,
                           evalmode,
                           caller,
                           &s);

            TokenArray_AppendMove(&s, &ts);
            TokenArray_Swap(&s, &ts);
            caller = pMacro;

            TokenSet_Destroy(&hs);
            TokenArray_Destroy(&s);

            TokenArrayMap_Destroy(&args);
            PPToken_Destroy(&close);
        }

        else
        {
            
            
            TokenArray_Print(&removed_spaces);
            
            TokenArray_AppendMove(&removed_spaces, &ts);
            TokenArray_Swap(&removed_spaces, &ts);
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; 
        }

        
        TokenArray_Destroy(&removed_spaces);
    }

    

    TokenArray_Swap(&r, pOutputSequence2);

    TokenArray_Destroy(&r);
    TokenArray_Destroy(&ts);
}


 
bool FillIn(struct TokenArray * ts, bool get_more, struct TokenArray * removed)
{
    while (ts->Size > 0 &&
           PPToken_IsSpace(ts->pItems[0]))
    {
        TokenArray_PushBack(removed, TokenArray_PopFront(ts));
    }

    if (ts->Size > 0)
    {
        return true;
    }

     

    return (false);
}






void Glue(const struct TokenArray * lsI,
          const struct TokenArray * rsI,
          struct TokenArray * out)
{
    struct TokenArray ls = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&ls, lsI);

    struct TokenArray rs = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&rs, rsI);

    TokenArray_Clear(out);

    if (ls.Size == 0)
    {
        TokenArray_Swap(out, &rs);
    }

    else
    {

        while (ls.Size > 0 &&
               PPToken_IsSpace(ls.pItems[ls.Size - 1]))
        {
            TokenArray_Pop(&ls);
        }

        while (rs.Size > 0 && PPToken_IsSpace(rs.pItems[0]))
        {
            struct PPToken * tk = TokenArray_PopFront(&rs);
            PPToken_Delete(tk);
            tk = NULL;
        }

        if (ls.Size == 0 &&
            rs.Size == 0)
        {
            TokenArray_Swap(out, &ls);
        }

        else
        {
            
            

            StrBuilder strNewLexeme = STRBUILDER_INIT;

            if (ls.Size > 0)
            {
                
                
                

                StrBuilder_Append(&strNewLexeme, ls.pItems[ls.Size - 1]->Lexeme);
                TokenArray_Pop(&ls);
            }

            if (rs.Size > 0)
            {
                
                
                
                StrBuilder_Append(&strNewLexeme, rs.pItems[0]->Lexeme);
                TokenArray_Pop(&rs);
            }

            
            TokenArray_PushBack(&ls, PPToken_Create(strNewLexeme.c_str, PPTokenType_Other));
            StrBuilder_Destroy(&strNewLexeme);

            TokenArray_AppendMove(&ls, &rs);
            TokenArray_Swap(out, &ls);
        }
    }

    
    TokenArray_Print(out);
    

    TokenArray_Destroy(&ls);
    TokenArray_Destroy(&rs);
}

void ExpandMacroToText(const struct TokenArray * pTokenSequence,
                       const struct MacroMap * macros,
                       bool get_more,
                       bool skip_defined,
                       bool evalmode,
                       struct Macro * caller,
                       StrBuilder * strBuilder)
{
    StrBuilder_Clear(strBuilder);
    struct TokenArray tks = TOKENARRAY_INIT;
    ExpandMacro(pTokenSequence,
                macros,
                get_more,
                skip_defined,
                evalmode,
                caller,

                &tks);

    for (int i = 0; i < tks.Size; i++)
    {
        if (tks.pItems[i]->Token == PPTokenType_Spaces)
        {
            StrBuilder_Append(strBuilder, " ");
        }
        else
        {
            StrBuilder_Append(strBuilder, tks.pItems[i]->Lexeme);
        }

    }

    TokenArray_Destroy(&tks);
}




int MacroMap_SetAt(struct MacroMap * pMap,
                   const char * Key,
                   struct Macro * newValue)
{
    void * pPrevious;
    int r = Map2_SetAt((Map2 *)pMap, Key, newValue, &pPrevious);
    Macro_Delete((struct Macro *)pPrevious);
    return r;
}

bool MacroMap_Lookup(const struct MacroMap * pMap,
                     const char * Key,
                     struct Macro ** rValue)
{
    return Map2_Lookup((Map2 *)pMap,
                       Key,
                       (void **)rValue);
}

struct Macro * MacroMap_Find(const struct MacroMap * pMap, const char * Key)
{
    void * p = NULL;
    Map2_Lookup((Map2 *)pMap,
                Key,
                &p);
    return (struct Macro *)p;
}


bool MacroMap_RemoveKey(struct MacroMap * pMap, const char * Key)
{
    struct Macro * pItem;
    bool r = Map2_RemoveKey((Map2 *)pMap, Key, (void **)& pItem);

    if (r)
    {
        Macro_Delete(pItem);
    }

    return r;
}

void MacroMap_Init(struct MacroMap * p)
{
    struct MacroMap t = MACROMAP_INIT;
    *p = t;
}

static void Macro_DeleteVoid(void * p)
{
    Macro_Delete((struct Macro *)p);
}

void MacroMap_Destroy(struct MacroMap * p)
{
    Map2_Destroy((Map2 *)p, Macro_DeleteVoid);
}


void MacroMap_Swap(struct MacroMap * pA, struct MacroMap * pB)
{
    struct MacroMap t = *pA;
    *pA = *pB;
    *pB = t;
}








void PPToken_Destroy(struct  PPToken * p) /*@default*/
{
    Free((void*)p->Lexeme);
    TokenSet_Destroy(&p->HiddenSet);
}

void PPToken_Swap(struct  PPToken * pA, struct  PPToken * pB)
{
    struct  PPToken temp = *pA;
    *pA = *pB;
    *pB = temp;
}

struct  PPToken * PPToken_Clone(struct  PPToken * p)
{
    struct PPToken * pNew = PPToken_Create(p->Lexeme, p->Token);
    TokenSetAppendCopy(&pNew->HiddenSet, &p->HiddenSet);
    return pNew;
}

struct PPToken * PPToken_Create(const char * s, enum PPTokenType token)
{
    struct PPToken * p = (struct PPToken *)Malloc(sizeof(struct PPToken));

    if (p != 0)
    {
        struct PPToken t = TOKEN_INIT;
        *p = t;
        p->Lexeme = StrDup(s);
        p->Token = token;
    }
    else
    {
        
    }

    return p;
}

void PPToken_Delete(struct PPToken * p) /*@default*/
{
    if (p != NULL)
    {
        PPToken_Destroy(p);
        Free((void*)p);
    }
}

void PPToken_DeleteVoid(void * pv)
{
    PPToken_Delete((struct PPToken *)pv);
}

bool PPToken_IsIdentifier(struct PPToken * pHead)
{
    return pHead->Token == PPTokenType_Identifier;
}

bool PPToken_IsSpace(struct PPToken * pHead)
{
    if (pHead->Token == PPTokenType_Spaces)
    {
        return true;
    }
    return false;
}

bool PPToken_IsStringizingOp(struct PPToken * pHead)
{
    return pHead->Lexeme[0] == '#' &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsConcatOp(struct PPToken * pHead)
{
    return pHead->Lexeme[0] == '#' &&
        pHead->Lexeme[1] == '#' &&
        pHead->Lexeme[2] == '\0';
}

bool PPToken_IsStringLit(struct PPToken * pHead)
{
    return pHead->Token == PPTokenType_StringLiteral;
}

bool PPToken_IsCharLit(struct PPToken * pHead)
{
    return pHead->Token == PPTokenType_CharConstant;
}

bool PPToken_IsOpenPar(struct PPToken * pHead)
{
    return pHead->Lexeme[0] == '(' &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsChar(struct PPToken * pHead, char ch)
{
    return pHead->Lexeme[0] == ch &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsLexeme(struct PPToken * pHead, const char * lexeme)
{
    return strcmp(pHead->Lexeme, lexeme) == 0;
}









void TokenArray_Reserve(struct TokenArray * p, int nelements) /*@default*/
{
    if (nelements > p->Capacity)
    {
        struct PPToken** pnew = p->pItems;
        pnew = (struct PPToken**)Realloc(pnew, nelements * sizeof(struct PPToken*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = nelements;
        }
    }
}

int TokenArray_Grow(struct TokenArray * p, int nelements)
{
    return Array_Grow((Array *)p, nelements);
}

struct PPToken * TokenArray_PopFront(struct TokenArray * p)
{
    void * pItem = Array_PopFront((Array *)p);
    return (struct PPToken *)pItem;
}

void TokenArray_Pop(struct TokenArray * p)
{
    Array_Pop((Array *)p, PPToken_DeleteVoid);
}

struct PPToken * TokenArray_Top(struct TokenArray * p)
{
    return (struct PPToken *)Array_Top((Array *)p);
}

void TokenArray_PushBack(struct TokenArray * p, struct PPToken * pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TokenArray_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

void TokenArray_Clear(struct TokenArray * p)
{
    Array_Clear((Array *)p, PPToken_DeleteVoid);
}


void TokenArray_Init(struct TokenArray * p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

struct TokenArray * TokenArray_Create() /*@default*/
{
    struct TokenArray *p = (struct TokenArray *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TokenArray_Init(p);
    }
    return p;
}

void TokenArray_Destroy(struct TokenArray * st) /*@default*/
{
    for (int i = 0; i < st->Size; i++)
    {
        PPToken_Delete(st->pItems[i]);
    }
    Free((void*)st->pItems);
}

void TokenArray_Swap(struct TokenArray * p1, struct TokenArray * p2)
{
    struct TokenArray temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void TokenArray_Delete(struct TokenArray * st) /*@default*/
{
    if (st != NULL)
    {
        TokenArray_Destroy(st);
        Free((void*)st);
    }
}




void TokenArray_AppendTokensCopy(struct TokenArray * pArray, struct PPToken ** pToken, int len)
{
    for (int i = 0; i < len; i++)
    {
        TokenArray_PushBack(pArray, PPToken_Clone(pToken[i]));
    }
}
void TokenArray_AppendTokensMove(struct TokenArray * pArray, struct PPToken ** pToken, int len)
{
    for (int i = 0; i < len; i++)
    {
        TokenArray_PushBack(pArray, pToken[i]);
        pToken[i] = NULL;
    }
}

void TokenArray_AppendCopy(struct TokenArray * pArrayTo, const struct TokenArray * pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenArray_PushBack(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
    }
}

void TokenArray_AppendMove(struct TokenArray * pArrayTo, struct TokenArray * pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenArray_PushBack(pArrayTo, pArrayFrom->pItems[i]);
        pArrayFrom->pItems[i] = NULL;
    }
}

struct PPToken * TokenArray_Find(const struct TokenArray * pArray, const char * lexeme)
{
    struct PPToken * pFound = NULL;

    for (int i = 0; i < pArray->Size; i++)
    {
        if (strcmp(lexeme, pArray->pItems[i]->Lexeme) == 0)
        {
            pFound = pArray->pItems[i];
            break;
        }
    }

    return pFound;
}

void TokenArray_ToStrBuilder(const struct TokenArray * tokens,
                             StrBuilder * strBuidler)
{
    StrBuilder_Clear(strBuidler);
    for (int i = 0; i < tokens->Size; i++)
    {
        StrBuilder_Append(strBuidler, tokens->pItems[i]->Lexeme);
    }
}

void TokenArray_Print(const struct TokenArray * tokens)
{
    if (tokens->Size == 0)
    {
        
    }

    
    

      

    
    

}


void TokenArray_Erase(struct TokenArray * pArray, int begin, int end)
{
    for (int i = begin; i < end; i++)
    {
        PPToken_Delete(pArray->pItems[i]);
    }


    if (pArray->Size > 1)
    {
        memmove(pArray->pItems + begin,
                pArray->pItems + end,
                sizeof(void *) * (pArray->Size - end));
    }

    pArray->Size = pArray->Size - end;
}


int TokenArrayMap_SetAt(TokenArrayMap * pMap,
                        const char * Key,
                        struct TokenArray * newValue)
{
    void * pPrevious;
    int r = Map2_SetAt((Map2 *)pMap, Key, newValue, &pPrevious);
    TokenArray_Delete((struct TokenArray *)pPrevious);
    return r;
}

bool TokenArrayMap_Lookup(const TokenArrayMap * pMap,
                          const char * Key,
                          struct TokenArray ** rValue)
{
    if (pMap == NULL)
    {
        return false;
    }

    return Map2_Lookup((Map2 *)pMap,
                       Key,
                       (void **)rValue);
}

bool TokenArrayMap_RemoveKey(TokenArrayMap * pMap, const char * Key)
{
    struct TokenArray * pItem;
    bool r = Map2_RemoveKey((Map2 *)pMap, Key, (void **)& pItem);

    if (r)
    {
        TokenArray_Delete(pItem);
    }

    return r;
}

void TokenArrayMap_Init(TokenArrayMap * p)
{
    TokenArrayMap t = TOKENARRAY_INIT;
    *p = t;
}


static void TokenArray_DeleteVoid(void * p)
{
    TokenArray_Delete((struct TokenArray *)p);
}

void TokenArrayMap_Destroy(TokenArrayMap * p)
{
    Map2_Destroy((Map2 *)p, &TokenArray_DeleteVoid);
}



void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB)
{
    TokenArrayMap t = TOKENARRAYMAP_INIT;
    *pA = *pB;
    *pB = t;
}

void TokenSet_PushBack(TokenSet * p, struct PPToken * pItem)  
{
    int r = 0;
    struct PPToken * pTk = TokenSet_Find(p, pItem->Lexeme);

    if (pTk == NULL)
    {
        r = Array_Push((Array *)p, pItem);

        if (r == -1)
        {
            PPToken_Delete(pItem);
        }
    }

    else
    {
        r = 0;
        PPToken_Delete(pItem);
    }


}


void TokenSetAppendCopy(TokenSet * pArrayTo, const TokenSet * pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenSet_PushBack(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
    }
}


struct PPToken * TokenSet_Find(const TokenSet * pArray, const char * lexeme)
{
    struct PPToken * pFound = NULL;

    for (int i = 0; i < pArray->Size; i++)
    {
        if (strcmp(lexeme, pArray->pItems[i]->Lexeme) == 0)
        {
            pFound = pArray->pItems[i];
            break;
        }
    }

    return pFound;
}

void TokenSet_Clear(TokenSet * p)
{
    Array_Clear((Array *)p, PPToken_DeleteVoid);
}


void TokenSet_Destroy(TokenSet * pArray) /*@default*/
{
    for (int i = 0; i < pArray->Size; i++)
    {
        PPToken_Delete(pArray->pItems[i]);
    }
    Free((void*)pArray->pItems);
}

void SetIntersection(const TokenSet * p1,
                     const TokenSet * p2,
                     TokenSet * pResult)
{
    if (p1->Size != 0 && p2->Size != 0)
    {
        struct PPToken * first1 = p1->pItems[0];
        struct PPToken * last1 = p1->pItems[p1->Size];

        struct PPToken * first2 = p2->pItems[0];
        struct PPToken * last2 = p2->pItems[p2->Size];

        while (first1 != last1 && first2 != last2)
        {
            
            if (strcmp(first1->Lexeme, first2->Lexeme) == 0)
            {
                ++first1;
            }

            else
            {
                
                if (strcmp(first2->Lexeme, first1->Lexeme) != 0)
                {
                    
                    TokenSet_PushBack(pResult, PPToken_Clone(first1));
                    first1++;
                    
                    
                }

                ++first2;
            }
        }
    }

    else if (p1->Size == 0)
    {
        TokenSetAppendCopy(pResult, p1);
    }

    else if (p2->Size == 0)
    {
        TokenSetAppendCopy(pResult, p2);
    }


}

 










void KeyValue_Delete(MapItem2 * p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Key);
        Free((void*)p);
    }
}

static MapItem2 * Map2_GetAssocAt(
    Map2 * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue);


unsigned int String2_HashKey(const char * Key)
{
    
    
    unsigned int uHashVal = 2166136261U;
    unsigned int uFirst = 0;
    unsigned int uLast = (unsigned int)strlen(Key);
    unsigned int uStride = 1 + uLast / 10;

    for (; uFirst < uLast; uFirst += uStride)
    {
        uHashVal = 16777619U * uHashVal ^ (unsigned int)Key[uFirst];
    }

    return (uHashVal);
}


void Map2_RemoveAll(Map2 * pMap, void(*DeleteFunc)(void *))
{
    if (pMap->pHashTable != NULL)
    {
        for (unsigned int nHash = 0;
             nHash < pMap->nHashTableSize;
             nHash++)
        {
            MapItem2 * pKeyValue =
                pMap->pHashTable[nHash];

            while (pKeyValue != NULL)
            {
                MapItem2 * pKeyValueCurrent = pKeyValue;

                if (DeleteFunc)
                    DeleteFunc(pKeyValueCurrent->pValue);

                pKeyValue = pKeyValue->pNext;
                KeyValue_Delete(pKeyValueCurrent);


            }
        }

        Free(pMap->pHashTable);
        pMap->pHashTable = NULL;
        pMap->nCount = 0;
    }
}

void Map2_Destroy(Map2 * pMap, void(*DeleteFunc)(void *))
{
    Map2_RemoveAll(pMap, DeleteFunc);
}

static MapItem2 * Map2_GetAssocAt(
    Map2 * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue)
{
    if (pMap->pHashTable == NULL)
    {
        *HashValue = 0;
        *nHashBucket = 0;
        return NULL;
    }

    *HashValue = String2_HashKey(Key);
    *nHashBucket = *HashValue % pMap->nHashTableSize;

    MapItem2 * pResult = NULL;

    MapItem2 * pKeyValue =
        pMap->pHashTable[*nHashBucket];

    for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
    {
        if (pKeyValue->HashValue == *HashValue &&
            strcmp(pKeyValue->Key, Key) == 0)
        {
            pResult = pKeyValue;
            break;
        }
    }

    return pResult;
}

bool Map2_Lookup(Map2 * pMap,
                 const char * Key,
                 void ** rValue)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    MapItem2 * pKeyValue = Map2_GetAssocAt(pMap,
                                           Key,
                                           &nHashBucket,
                                           &HashValue);

    if (pKeyValue != NULL)
    {
        *rValue = pKeyValue->pValue;
        bResult = true;
    }

    return bResult;
}

bool Map2_LookupKey(Map2 * pMap,
                    const char * Key,
                    const char ** rKey)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    MapItem2 * pKeyValue = Map2_GetAssocAt(pMap,
                                           Key,
                                           &nHashBucket,
                                           &HashValue);

    if (pKeyValue != NULL)
    {
        *rKey = pKeyValue->Key;
        bResult = true;
    }

    return bResult;
}

bool Map2_RemoveKey(Map2 * pMap,
                    const char * Key,
                    void ** ppValue)
{
    *ppValue = 0;
    bool bResult = false;

    if (pMap->pHashTable != NULL)
    {
        unsigned int HashValue =
            String2_HashKey(Key);

        MapItem2 ** ppKeyValuePrev =
            &pMap->pHashTable[HashValue % pMap->nHashTableSize];

        MapItem2 * pKeyValue = *ppKeyValuePrev;

        for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
        {
            if ((pKeyValue->HashValue == HashValue) &&
                (strcmp(pKeyValue->Key, Key) == 0))
            {
                
                *ppKeyValuePrev = pKeyValue->pNext;
                *ppValue = pKeyValue->pValue;
                KeyValue_Delete(pKeyValue);
                bResult = true;

                break;
            }

            ppKeyValuePrev = &pKeyValue->pNext;
        }
    }

    return bResult;
}

int Map2_SetAt(Map2 * pMap,
               const char * Key,
               void * newValue,
               void ** ppPreviousValue)
{
    int result = 0;
    *ppPreviousValue = NULL;

    if (pMap->pHashTable == NULL)
    {
        if (pMap->nHashTableSize < 1)
        {
            pMap->nHashTableSize = 1000;
        }

        MapItem2 ** pHashTable =
            (MapItem2 * *)Malloc(sizeof(MapItem2 *) * pMap->nHashTableSize);

        if (pHashTable != NULL)
        {
            memset(pHashTable, 0, sizeof(MapItem2 *) * pMap->nHashTableSize);
            pMap->pHashTable = pHashTable;
        }
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        MapItem2 * pKeyValue =
            Map2_GetAssocAt(pMap,
                            Key,
                            &nHashBucket,
                            &HashValue);

        if (pKeyValue == NULL)
        {
            pKeyValue = (MapItem2 *)Malloc(sizeof(MapItem2) * 1);
            pKeyValue->HashValue = HashValue;
            pKeyValue->pValue = newValue;
            pKeyValue->Key = StrDup(Key);
            pKeyValue->pNext = pMap->pHashTable[nHashBucket];
            pMap->pHashTable[nHashBucket] = pKeyValue;
            pMap->nCount++;
            result = 0;
        }

        else
        {
            result = 1;
            *ppPreviousValue = pKeyValue->pValue;
            pKeyValue->pValue = newValue;

            Free(pKeyValue->Key);
            pKeyValue->Key = StrDup(Key);

        }
    }

    return result;
}

void Map2_Init(Map2 * p) /*@default*/
{
    p->pHashTable = NULL;
    p->nHashTableSize = 0;
    p->nCount = 0;
}

void Map2_Swap(Map2 * pA, Map2 * pB)
{
    Map2 temp = *pA;
    *pA = *pB;
    *pB = temp;
}

Map2 * Map2_Create(void) /*@default*/
{
    Map2 *p = (Map2*) Malloc(sizeof * p);
    if (p != NULL)
    {
        Map2_Init(p);
    }
    return p;
}

void Map2_Delete(Map2 * p, void(*DeleteFunc)(void *))
{
    if (p != NULL)
    {
        Map2_Destroy(p, DeleteFunc);
        Free((void *)p);
    }
}



void Options_Destroy(struct Options * options)  
{
}












static void SymbolMap_KeyValue_Delete(struct SymbolMapItem * p)
{
    if (p)
    {
        Free(p->Key);
        Free(p);
    }
}

struct SymbolMapItem * SymbolMap_GetAssocAt(
    struct SymbolMap * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue);


static unsigned int SymbolMap_String2_HashKey(const char * Key)
{
    
    
    unsigned int uHashVal = 2166136261U;
    unsigned int uFirst = 0;
    unsigned int uLast = (unsigned int)strlen(Key);
    unsigned int uStride = 1 + uLast / 10;

    for (; uFirst < uLast; uFirst += uStride)
    {
        uHashVal = 16777619U * uHashVal ^ (unsigned int)Key[uFirst];
    }

    return (uHashVal);
}


void SymbolMap_RemoveAll(struct SymbolMap * pMap)
{
    if (pMap->pHashTable != NULL)
    {
        for (int nHash = 0;
            nHash < pMap->nHashTableSize;
            nHash++)
        {
            struct SymbolMapItem * pKeyValue =
                pMap->pHashTable[nHash];

            while (pKeyValue != NULL)
            {
                struct SymbolMapItem * pKeyValueCurrent = pKeyValue;
                pKeyValue = pKeyValue->pNext;
                SymbolMap_KeyValue_Delete(pKeyValueCurrent);
            }
        }

        Free(pMap->pHashTable);
        pMap->pHashTable = NULL;
        pMap->nCount = 0;
    }
}

void SymbolMap_Destroy(struct SymbolMap * pMap)
{
    SymbolMap_RemoveAll(pMap);
}

struct SymbolMapItem * SymbolMap_FindBucket(struct SymbolMap * pMap, const char * Key)
{
    if (pMap->pHashTable == NULL)
    {
        return NULL;
    }

    unsigned int HashValue = SymbolMap_String2_HashKey(Key);
    unsigned int nHashBucket = HashValue % pMap->nHashTableSize;


    struct SymbolMapItem * pKeyValue =
        pMap->pHashTable[nHashBucket];

    return pKeyValue;
}

struct SymbolMapItem * SymbolMap_GetAssocAt(
    struct SymbolMap * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue)
{
    if (pMap->pHashTable == NULL)
    {
        *HashValue = 0;
        *nHashBucket = 0;
        return NULL;
    }

    *HashValue = SymbolMap_String2_HashKey(Key);
    *nHashBucket = *HashValue % pMap->nHashTableSize;

    struct SymbolMapItem * pResult = NULL;

    struct SymbolMapItem * pKeyValue =
        pMap->pHashTable[*nHashBucket];

    for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
    {
        if (pKeyValue->HashValue == *HashValue &&
            strcmp(pKeyValue->Key, Key) == 0)
        {
            pResult = pKeyValue;
            break;
        }
    }

    return pResult;
}

TTypePointer * SymbolMap_Find(struct SymbolMap * pMap,
    const char * Key)
{
    TTypePointer * pTypePointer = NULL;
    unsigned int nHashBucket, HashValue;
    struct SymbolMapItem * pKeyValue = SymbolMap_GetAssocAt(pMap,
        Key,
        &nHashBucket,
        &HashValue);

    if (pKeyValue != NULL)
    {
        pTypePointer = pKeyValue->pValue;
    }


    if (pTypePointer == NULL && pMap->pPrevious != NULL)
    {
        pTypePointer = SymbolMap_Find(pMap->pPrevious, Key);
    }

    return pTypePointer;
}

bool SymbolMap_LookupKey(struct SymbolMap * pMap,
    const char * Key,
    const char ** rKey)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    struct SymbolMapItem * pKeyValue = SymbolMap_GetAssocAt(pMap,
        Key,
        &nHashBucket,
        &HashValue);

    if (pKeyValue != NULL)
    {
        *rKey = pKeyValue->Key;
        bResult = true;
    }

    return bResult;
}

bool SymbolMap_RemoveKey(struct SymbolMap * pMap,
    const char * Key,
    TTypePointer ** ppValue)
{
    *ppValue = 0;
    bool bResult = false;

    if (pMap->pHashTable != NULL)
    {
        unsigned int HashValue =
            SymbolMap_String2_HashKey(Key);

        struct SymbolMapItem ** ppKeyValuePrev =
            &pMap->pHashTable[HashValue % pMap->nHashTableSize];

        struct SymbolMapItem * pKeyValue = *ppKeyValuePrev;

        for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
        {
            if ((pKeyValue->HashValue == HashValue) &&
                (strcmp(pKeyValue->Key, Key) == 0))
            {
                
                *ppKeyValuePrev = pKeyValue->pNext;
                *ppValue = pKeyValue->pValue;
                SymbolMap_KeyValue_Delete(pKeyValue);
                bResult = true;
                break;
            }

            ppKeyValuePrev = &pKeyValue->pNext;
        }
    }

    return bResult;
}

int SymbolMap_SetAt(struct SymbolMap * pMap,
    const char * Key,
    TTypePointer * newValue)
{
    int result = 0;


    if (pMap->pHashTable == NULL)
    {
        if (pMap->nHashTableSize < 1)
        {
            pMap->nHashTableSize = 1000;
        }

        struct SymbolMapItem ** pHashTable =
            (struct SymbolMapItem **)Malloc(sizeof(struct SymbolMapItem *) * pMap->nHashTableSize);

        if (pHashTable != NULL)
        {
            memset(pHashTable, 0, sizeof(struct SymbolMapItem *) * pMap->nHashTableSize);
            pMap->pHashTable = pHashTable;
        }
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                Key,
                &nHashBucket,
                &HashValue);

        
        {
            pKeyValue = (struct SymbolMapItem *)Malloc(sizeof(struct SymbolMapItem) * 1);
            pKeyValue->HashValue = HashValue;
            pKeyValue->pValue = newValue;
            pKeyValue->Key = StrDup(Key);
            pKeyValue->pNext = pMap->pHashTable[nHashBucket];
            pMap->pHashTable[nHashBucket] = pKeyValue;
            pMap->nCount++;
            result = 0;
        }

        
        
        
        
        
        
    }

    return result;
}

void SymbolMap_Init(struct SymbolMap * p)
{
    struct SymbolMap temp = SYMBOLMAP_INIT;
    *p = temp;
}

void SymbolMap_Swap(struct SymbolMap * pA, struct SymbolMap * pB)
{
    struct SymbolMap temp = *pA;
    *pA = *pB;
    *pB = temp;
}

struct SymbolMap * SymbolMap_Create()
{
    struct SymbolMap * p = (struct SymbolMap *)Malloc(sizeof(struct SymbolMap));

    if (p != 0)
    {
        struct SymbolMap t = SYMBOLMAP_INIT;
        *p = t;
    }

    return p;
}

void SymbolMap_Delete(struct SymbolMap * p)
{
    if (p != 0)
    {
        SymbolMap_Destroy(p);
        Free(p);
    }
}

const char * PrintType(EType type)
{

    switch (type)
    {
    case TypeNull:
    case TDeclaration_ID:
        return "TDeclaration_ID";
    case TStaticAssertDeclaration_ID:
    case TEofDeclaration_ID:

    case TSingleTypeSpecifier_ID:
        return "TSingleTypeSpecifier_ID";
    case TEnumSpecifier_ID:
        return "TEnumSpecifier_ID";
    case TStructUnionSpecifier_ID:
        return "TStructUnionSpecifier_ID";

    case TStorageSpecifier_ID:
    case TAtomicTypeSpecifier_ID:
    case TTemplateTypeSpecifier_ID:
    case TStructDeclaration_ID:
    case TAlignmentSpecifier_ID:
    case TTypeQualifier_ID:
    case TFunctionSpecifier_ID:
    case TCompoundStatement_ID:
    case TExpressionStatement_ID:
    case TSwitchStatement_ID:
    case TLabeledStatement_ID:
    case TForStatement_ID:
    case TJumpStatement_ID:
    case TAsmStatement_ID:
    case TWhileStatement_ID:
    case TDoStatement_ID:
    case TIfStatement_ID:
    case TypeName_ID:

    case TInitializerListType_ID:

    case TPrimaryExpression_ID:
    case TUnaryExpressionOperator_ID:
    case TCastExpressionType_ID:
    case TPrimaryExpressionValue_ID:
    case TPrimaryExpressionLiteral_ID:
    case TPostfixExpressionCore_ID:
    case TBinaryExpression_ID:
    case TTernaryExpression_ID:
    case TEnumerator_ID:
        break;
    default:
        break;
    }
    return "";
}

static void SymbolMap_PrintCore(struct SymbolMap * pMap, int * n)
{
    if (pMap->pPrevious)
    {
        SymbolMap_PrintCore(pMap->pPrevious, n);
        (*n)++;
    }

    for (int k = 0; k < *n; k++)
    {
        printf(" ");
    }

    if (pMap->pHashTable != NULL)
    {
        for (int i = 0; i < pMap->nHashTableSize; i++)
        {
            struct SymbolMapItem * pSymbolMapItem = pMap->pHashTable[i];
            while (pSymbolMapItem != NULL)
            {
                printf("%s = %s\n", pSymbolMapItem->Key, PrintType(pSymbolMapItem->pValue->Type));
                pSymbolMapItem = pSymbolMapItem->pNext;
            }
        }
    }
}


void SymbolMap_Print(struct SymbolMap * pMap)
{
    int n = 0;
    SymbolMap_PrintCore(pMap, &n);
}



bool SymbolMap_IsTypeName(struct SymbolMap * pMap, const char * identifierName)
{
    bool bIsTypeName = false;
    bool foundResult = false;

    while (pMap)
    {
        struct SymbolMapItem * pBucket =
            SymbolMap_FindBucket(pMap, identifierName);

        while (pBucket)
        {
            if (pBucket->pValue->Type == TDeclaration_ID &&
                strcmp(pBucket->Key, identifierName) == 0)
            {
                foundResult = true;

                TDeclaration * pDeclaration =
                    (TDeclaration *)pBucket->pValue;

                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];

                    if (pItem->Type == TStorageSpecifier_ID)
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypeName = true;
                            break;
                        }
                    }
                }
            }

            if (foundResult)
                break;

            pBucket = pBucket->pNext;
        }

        if (foundResult)
            break;

        pMap = pMap->pPrevious;
    }

    return bIsTypeName;
}


TDeclaration * SymbolMap_FindFunction(struct SymbolMap * pMap, const char * funcName)
{
    TDeclaration * pDeclaration = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                funcName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            
            if (pKeyValue->pValue->Type == TDeclaration_ID)
            {
                if (strcmp(pKeyValue->Key, funcName) == 0)
                {
                    pDeclaration =
                        (TDeclaration *)pKeyValue->pValue;

                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pDeclaration;
}




TDeclaration * SymbolMap_FindObjFunction2(struct SymbolMap * pMap,
    const char * objName,
    const char * funcName)
{
    if (objName == NULL || funcName == NULL)
    {
        return NULL;
    }

    char buffer[500] = { 0 };
    strcat(buffer, objName);
    strcat(buffer, "_");
    strcat(buffer, funcName);
    TDeclaration * p = SymbolMap_FindFunction(pMap, buffer);
    return p;
}

TStructUnionSpecifier * SymbolMap_FindStructUnion(struct SymbolMap * pMap, const char * structTagName)
{
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                structTagName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            
            if (pKeyValue->pValue->Type == TStructUnionSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, structTagName) == 0)
                {
                    pStructUnionSpecifier =
                        (TStructUnionSpecifier *)pKeyValue->pValue;
                    if (pStructUnionSpecifier->StructDeclarationList.Size > 0 ||
                        pStructUnionSpecifier->UnionSet.pHead != NULL)
                    {
                        
                        
                        
                        break;
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pStructUnionSpecifier;
}


TEnumSpecifier * SymbolMap_FindEnum(struct SymbolMap * pMap, const char * enumTagName)
{
    TEnumSpecifier * pEnumSpecifier = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                enumTagName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            
            if (pKeyValue->pValue->Type == TEnumSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, enumTagName) == 0)
                {
                    pEnumSpecifier =
                        (TEnumSpecifier *)pKeyValue->pValue;
                    if (pEnumSpecifier->EnumeratorList.pHead != NULL)
                    {
                        
                        break;
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pEnumSpecifier;
}


TDeclaration * SymbolMap_FindTypedefDeclarationTarget(struct SymbolMap * pMap,
    const char * typedefName)
{
    TDeclaration * pDeclarationResult = NULL;


    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;
                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        
                        pDeclarationResult =
                            SymbolMap_FindTypedefDeclarationTarget(pMap, indirectTypedef);
                    }
                    else
                    {
                        
                        pDeclarationResult = pDeclaration;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pDeclarationResult;
}





TDeclarationSpecifiers * SymbolMap_FindTypedefTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    
    TDeclarationSpecifiers * pSpecifiersResult = NULL;



    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;
                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];

                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        
                        break;

                    }
                }
                if (!bIsTypedef)
                {
                    
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);
                        if (pDeclarator)
                        {
                            
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            
                            pSpecifiersResult =
                                SymbolMap_FindTypedefTarget(pMap, indirectTypedef, declarator);
                        }
                        else
                        {
                            
                        }
                    }
                    else
                    {
                        
                        pSpecifiersResult = &pDeclaration->Specifiers;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pSpecifiersResult;
}





TDeclarationSpecifiers * SymbolMap_FindTypedefFirstTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    
    TDeclarationSpecifiers * pSpecifiersResult = NULL;



    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;

                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);
                        if (pDeclarator)
                        {
                            
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            
                            pSpecifiersResult = &pDeclaration->Specifiers;
                            
                                
                        }
                        else
                        {
                            
                        }
                    }
                    else
                    {
                        
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);

                        
                        ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                        {
                            TPointer * pNew = TPointer_Create();
                            TPointer_Copy(pNew, pItem);
                            TPointerList_PushBack(&declarator->PointerList, pNew);
                        }

                        pSpecifiersResult = &pDeclaration->Specifiers;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pSpecifiersResult;

}
TTypeSpecifier * SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap * pMap,
    const char * typedefName)
{
     

    TTypeSpecifier * pSpecifierTarget = NULL;

    TDeclaration * pDeclaration =
        SymbolMap_FindTypedefDeclarationTarget(pMap, typedefName);
    if (pDeclaration)
    {
        for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
        {
            TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


            switch (pItem->Type)
            {
            case TSingleTypeSpecifier_ID:
                pSpecifierTarget = (TTypeSpecifier *)pItem;
                break;

            case TStructUnionSpecifier_ID:
            {
                TStructUnionSpecifier * pStructUnionSpecifier =
                    (TStructUnionSpecifier *)pItem;
                if (pStructUnionSpecifier->StructDeclarationList.Size == 0)
                {
                    if (pStructUnionSpecifier->TagName != NULL)
                    {
                        pSpecifierTarget = (TTypeSpecifier *)SymbolMap_FindStructUnion(pMap, pStructUnionSpecifier->TagName);
                    }
                    else
                    {
                        
                    }
                }
                else
                {
                    pSpecifierTarget = (TTypeSpecifier *)pStructUnionSpecifier;
                }
            }
            break;
            case TEnumSpecifier_ID:
            {
                TEnumSpecifier * pEnumSpecifier =
                    (TEnumSpecifier *)pItem;
                if (pEnumSpecifier->EnumeratorList.pHead == NULL)
                {
                    if (pEnumSpecifier->Name != NULL)
                    {
                        pEnumSpecifier = SymbolMap_FindEnum(pMap, pEnumSpecifier->Name);
                    }
                    else
                    {
                        
                    }
                }
                else
                {
                    pSpecifierTarget = (TTypeSpecifier *)pEnumSpecifier;
                }
            }
            break;

            default:
                break;
            }

            if (pSpecifierTarget != NULL)
            {
                
                break;
            }
        }
    }
    return pSpecifierTarget;
}












#define List_Add(pList, pItem) \
if ((pList)->pHead == NULL) {\
    (pList)->pHead = (pItem); \
    (pList)->pTail = (pItem); \
}\
else {\
      (pList)->pTail->pNext = (pItem); \
      (pList)->pTail = (pItem); \
  }

void Declarator(Parser * ctx, bool bAbstract, TDeclarator ** ppTDeclarator2);


Tokens Parser_Match(Parser * parser, TScannerItemList * listOpt);
Tokens Parser_MatchToken(Parser * parser,
    Tokens tk,
    TScannerItemList * listOpt);
bool TTypeSpecifier_IsFirst(Parser * ctx, Tokens token, const char * lexeme);

void Specifier_Qualifier_List(Parser * ctx, TSpecifierQualifierList * pSpecifierQualifierList);
static bool TTypeQualifier_IsFirst(Tokens token);


static bool IsPreprocessorTokenPhase(Tokens token)
{
    return
        token == TK_SPACES ||
        token == TK_COMMENT ||
        token == TK_OPEN_COMMENT ||
        token == TK_CLOSE_COMMENT ||
        token == TK_LINE_COMMENT ||
        token == TK_BREAKLINE ||
        token == TK_BACKSLASHBREAKLINE ||
        
        token == TK_PRE_INCLUDE ||
        token == TK_PRE_PRAGMA ||
        token == TK_PRE_IF ||
        token == TK_PRE_ELIF ||
        token == TK_PRE_IFNDEF ||
        token == TK_PRE_IFDEF ||
        token == TK_PRE_ENDIF ||
        token == TK_PRE_ELSE ||
        token == TK_PRE_ERROR ||
        token == TK_PRE_LINE ||
        token == TK_PRE_UNDEF ||
        token == TK_PRE_DEFINE ||
        
        token == TK_MACRO_CALL ||
        token == TK_MACRO_EOF ||
        token == TK_FILE_EOF;
}




bool Declaration(Parser * ctx, TAnyDeclaration ** ppDeclaration);

int IsTypeName(Parser * ctx, Tokens token, const char * lexeme);



bool Parser_InitString(Parser * parser,
    const char * name,
    const char * Text)
{
    parser->ParserOptions.bNoImplicitTag = false;
    TScannerItemList_Init(&parser->ClueList);
    parser->IncludeLevel = 0;
    
    SymbolMap_Init(&parser->GlobalScope);
    parser->pCurrentScope = &parser->GlobalScope;
    parser->bPreprocessorEvalFlag = false;
    

    
    parser->bError = false;

    StrBuilder_Init(&parser->ErrorMessage);


    
    Scanner_InitString(&parser->Scanner, name, Text);

    
    TScannerItemList clueList0 = { 0 };
    Parser_Match(parser, &clueList0);
    TScannerItemList_Destroy(&clueList0);

    return true;
}

bool Parser_InitFile(Parser * parser, const char * fileName)
{

    parser->ParserOptions.bNoImplicitTag = false;
    parser->IncludeLevel = 0;
    parser->bPreprocessorEvalFlag = false;
    TScannerItemList_Init(&parser->ClueList);

    
    SymbolMap_Init(&parser->GlobalScope);
    parser->pCurrentScope = &parser->GlobalScope;

    
    
    parser->bError = false;


    StrBuilder_Init(&parser->ErrorMessage);
    Scanner_Init(&parser->Scanner);


    
    Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);

    
    
    TScannerItemList clueList0 = { 0 };
    Parser_Match(parser, &clueList0);
    TScannerItemList_Destroy(&clueList0);

    return true;
}

void Parser_PushFile(Parser * parser, const char * fileName)
{
    Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);


    TScannerItemList clueList0 = { 0 };
    Parser_Match(parser, &clueList0);
    
    TScannerItemList_Destroy(&clueList0);

}





void Parser_Destroy(Parser * parser)
{
    TScannerItemList_Destroy(&parser->ClueList);

    SymbolMap_Destroy(&parser->GlobalScope);

    
    StrBuilder_Destroy(&parser->ErrorMessage);
    Scanner_Destroy(&parser->Scanner);
}

static const char * GetName()
{
    static char buffer[2];
    buffer[0] = '\0';
    
    
    
    
    
    
    return buffer;
}

bool Parser_HasError(Parser * pParser)
{
    return pParser->bError || pParser->Scanner.bError;
}

void SetWarning(Parser * parser, const char * fmt, ...)
{
    StrBuilder warningMessage = STRBUILDER_INIT;
    Scanner_GetFilePositionString(&parser->Scanner, &warningMessage);
    va_list args;
    va_start(args, fmt);
    StrBuilder_AppendFmtV(&warningMessage, fmt, args);
    va_end(args);

    printf("%s\n", warningMessage.c_str);

    StrBuilder_Destroy(&warningMessage);
}

void SetError(Parser * parser, const char * fmt, ...)
{
    
    if (!Parser_HasError(parser))
    {
        Scanner_GetFilePositionString(&parser->Scanner, &parser->ErrorMessage);
        parser->bError = true;
        va_list args;
        va_start(args, fmt);
        StrBuilder_AppendFmtV(&parser->ErrorMessage, fmt, args);
        va_end(args);
    }

    else
    {
        
        parser->bError = true;
    }
}


int GetCurrentLine(Parser * parser)
{
    if (Parser_HasError(parser))
    {
        return -1;
    }

    return Scanner_LineAt(&parser->Scanner, 0);
}

int GetFileIndex(Parser * parser)
{
    if (Parser_HasError(parser))
    {
        return -1;
    }

    return Scanner_FileIndexAt(&parser->Scanner, 0);
}

static void GetPosition(Parser * ctx, TPosition * pPosition)
{
    pPosition->Line = GetCurrentLine(ctx);
    pPosition->FileIndex = GetFileIndex(ctx);
    
}

Tokens Parser_LookAheadToken(Parser * parser)
{
    Tokens token = TK_ERROR;

    if (!Parser_HasError(parser))
    {
        for (int i = 1; i < 10; i++)
        {
            token = Scanner_TokenAt(&parser->Scanner, i);
            bool bActive = Scanner_IsActiveAt(&parser->Scanner, i);
            if (bActive && !IsPreprocessorTokenPhase(token))
            {
                break;
            }
        }
    }

    return token;
}


const char * Parser_LookAheadLexeme(Parser * parser)
{
    if (Parser_HasError(parser))
    {
        return "";
    }

    const char * lexeme = NULL;

    if (!Parser_HasError(parser))
    {
        for (int i = 1; i < 10; i++)
        {
            Tokens token = Scanner_TokenAt(&parser->Scanner, i);
            bool bActive = Scanner_IsActiveAt(&parser->Scanner, i);
            if (bActive && !IsPreprocessorTokenPhase(token))
            {
                lexeme = Scanner_LexemeAt(&parser->Scanner, i);
                break;
            }
        }
    }

    return lexeme;
}


Tokens Parser_CurrentToken(Parser * parser)
{
    if (Parser_HasError(parser))
    {
        return TK_ERROR;
    }

    Tokens token = Scanner_TokenAt(&parser->Scanner, 0);

    if (IsPreprocessorTokenPhase(token))
    {
        SetError(parser, "!IsPreprocessorTokenPhase");
    }
    return token;
}

Tokens Parser_MatchEx(Parser * parser, TScannerItemList * listOpt, bool bKeepComment)
{
    
    Tokens token = TK_EOF;
    if (!Parser_HasError(parser))
    {

        if (listOpt)
        {
            TScannerItemList_Swap(listOpt, &parser->ClueList);
        }

        Scanner_Match(&parser->Scanner);

        token = Scanner_TokenAt(&parser->Scanner, 0);
        while (token != TK_EOF &&
            token != TK_NONE &&
            (!Scanner_IsActiveAt(&parser->Scanner, 0) ||
                IsPreprocessorTokenPhase(token)))
        {
            
            struct ScannerItem * pNew = ScannerItem_Create();
            LocalStrBuilder_Set(&pNew->lexeme, Scanner_LexemeAt(&parser->Scanner, 0));
            pNew->token = Scanner_TokenAt(&parser->Scanner, 0);
            TScannerItemList_PushBack(&parser->ClueList, pNew);


            Scanner_Match(&parser->Scanner);
            token = Scanner_TokenAt(&parser->Scanner, 0);
        }
    }

    return token;
}
Tokens Parser_Match(Parser * parser, TScannerItemList * listOpt)
{
    return Parser_MatchEx(parser, listOpt, true);
}

Tokens Parser_MatchToken(Parser * parser,
    Tokens tk,
    TScannerItemList * listOpt)
{
    if (Parser_HasError(parser))
    {
        return TK_EOF;
    }

    Tokens currentToken = Parser_CurrentToken(parser);

    if (tk != currentToken)
    {
        SetError(parser, "Unexpected token - %s", TokenToString(tk));
        return TK_EOF;
    }

    Parser_Match(parser, listOpt);
    return Parser_CurrentToken(parser);
}

const char * GetCompletationMessage(Parser * parser)
{
    const char * pMessage = "ok";

    if (Parser_HasError(parser))
    {
        if (parser->Scanner.bError)
        {
            pMessage = parser->Scanner.ErrorString.c_str;
        }

        else
        {
            pMessage = parser->ErrorMessage.c_str;
        }
    }

    return pMessage;
}

const char * Lexeme(Parser * parser)
{
    if (Parser_HasError(parser))
    {
        
        return "";
    }

    return Scanner_LexemeAt(&parser->Scanner, 0);
}

bool ErrorOrEof(Parser * parser)
{
    return Parser_HasError(parser) ||
        Parser_CurrentToken(parser) == TK_EOF;
}





void Expression0(Parser * ctx, TExpression **);
void CastExpression(Parser * ctx, TExpression **);
void GenericSelection(Parser * ctx);
void ArgumentExpressionList(Parser * ctx, TExpression **);
void AssignmentExpression(Parser * ctx, TExpression **);
void Initializer_List(Parser * ctx, TInitializerList * pInitializerList);



bool IsFirstOfPrimaryExpression(Tokens token)
{
    bool bResult = false;

    switch (token)
    {
    case TK_IDENTIFIER:
    case TK_STRING_LITERAL:
    case TK_CHAR_LITERAL:
    case TK_DECIMAL_INTEGER:
    case TK_HEX_INTEGER:
    case TK_FLOAT_NUMBER:
    case TK_LEFT_PARENTHESIS:

        
        
    case TK_LEFT_SQUARE_BRACKET: 
                                 

                                 
    case TK__GENERIC:
        bResult = true;
        break;

    default:
        break;
    }

    return bResult;
}

void PrimaryExpressionLiteral(Parser * ctx, TExpression ** ppPrimaryExpression)
{
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);

    TPrimaryExpressionLiteral * pPrimaryExpressionLiteral
        = TPrimaryExpressionLiteral_Create();

    *ppPrimaryExpression = (TExpression *)pPrimaryExpressionLiteral;

    while (token == TK_STRING_LITERAL)
    {
        TPrimaryExpressionLiteralItem * pPrimaryExpressionLiteralItem
            = TPrimaryExpressionLiteralItem_Create();
        const char * lexeme2 = Lexeme(ctx);
        PTR_STRING_REPLACE(pPrimaryExpressionLiteralItem->lexeme, lexeme2);

        token = Parser_Match(ctx,
            &pPrimaryExpressionLiteralItem->ClueList0);

        TPrimaryExpressionLiteralItemList_Add(&pPrimaryExpressionLiteral->List, pPrimaryExpressionLiteralItem);
    }
}

void Compound_Statement(Parser * ctx, TStatement ** ppStatement);

void Parameter_Type_List(Parser * ctx, TParameterTypeList * pParameterList);

void LambdaExpression(Parser * ctx, TExpression ** ppPrimaryExpression)
{
    
     

     
    TPrimaryExpressionLambda * pPrimaryExpressionLambda = TPrimaryExpressionLambda_Create();

    *ppPrimaryExpression = (TExpression *)pPrimaryExpressionLambda; 

    Parser_MatchToken(ctx,
        TK_LEFT_SQUARE_BRACKET,
        &pPrimaryExpressionLambda->ClueList0);

    Parser_MatchToken(ctx,
        TK_RIGHT_SQUARE_BRACKET,
        &pPrimaryExpressionLambda->ClueList1);

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_PARENTHESIS)
    {
        token = Parser_MatchToken(ctx,
            TK_LEFT_PARENTHESIS,
            &pPrimaryExpressionLambda->ClueList2);

        pPrimaryExpressionLambda->pParameterTypeListOpt =
            TParameterTypeList_Create();

        if (token != TK_RIGHT_PARENTHESIS)
        {
            Parameter_Type_List(ctx, pPrimaryExpressionLambda->pParameterTypeListOpt);
        }

        Parser_MatchToken(ctx,
            TK_RIGHT_PARENTHESIS,
            &pPrimaryExpressionLambda->ClueList3);
    }

    Compound_Statement(ctx, (TStatement * *)& pPrimaryExpressionLambda->pCompoundStatement);
}

void PrimaryExpression(Parser * ctx, TExpression ** ppPrimaryExpression)
{
    *ppPrimaryExpression = NULL;



     
    * ppPrimaryExpression = NULL; 

    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);
    
    
    
    


    if (!IsFirstOfPrimaryExpression(token))
    {
        SetError(ctx, "unexpected error IsFirstOfPrimaryExpression");
    }

    switch (token)
    {

    case TK_LEFT_SQUARE_BRACKET:
        LambdaExpression(ctx, ppPrimaryExpression);
        break;

    case TK_STRING_LITERAL:
        PrimaryExpressionLiteral(ctx, ppPrimaryExpression);
        break;

    case TK_IDENTIFIER:
    {
        if (SymbolMap_Find(ctx->pCurrentScope, lexeme) == NULL)
        {
            if (!ctx->bPreprocessorEvalFlag)
            {
                if (strcmp(lexeme, "__FUNCTION__") == 0)
                {
                    
                }
                else
                {
                    SetWarning(ctx, "Warning: '%s': undeclared identifier\n", lexeme);
                }
            }
        }

        TPrimaryExpressionValue * pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        pPrimaryExpressionValue->token = token;
        PTR_STRING_REPLACE(pPrimaryExpressionValue->lexeme, lexeme);


        Parser_Match(ctx,
            &pPrimaryExpressionValue->ClueList0);
        *ppPrimaryExpression = (TExpression *)pPrimaryExpressionValue;
    }
    break;

    case TK_CHAR_LITERAL:
    case TK_DECIMAL_INTEGER:
    case TK_HEX_INTEGER:
    case TK_FLOAT_NUMBER:
    {
        TPrimaryExpressionValue * pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        pPrimaryExpressionValue->token = token;
        PTR_STRING_REPLACE(pPrimaryExpressionValue->lexeme, Lexeme(ctx));


        Parser_Match(ctx,
            &pPrimaryExpressionValue->ClueList0);
        *ppPrimaryExpression = (TExpression *)pPrimaryExpressionValue;
    }
    break;

    case TK_LEFT_PARENTHESIS:
    {
        TPrimaryExpressionValue * pPrimaryExpressionValue
            = TPrimaryExpressionValue_Create();

        Parser_Match(ctx,
            &pPrimaryExpressionValue->ClueList0);

        TExpression * pExpression;
        Expression0(ctx, &pExpression);

        
        Parser_MatchToken(ctx,
            TK_RIGHT_PARENTHESIS,
            &pPrimaryExpressionValue->ClueList1);


        pPrimaryExpressionValue->token = token;
        PTR_STRING_REPLACE(pPrimaryExpressionValue->lexeme, Lexeme(ctx));
        pPrimaryExpressionValue->pExpressionOpt = pExpression;


        *ppPrimaryExpression = (TExpression *)pPrimaryExpressionValue;
    }
    break;

    case TK__GENERIC:
        GenericSelection(ctx);
        break;

    default:
        SetError(ctx, "unexpected error");
    }

    if (*ppPrimaryExpression == NULL)
    {
        SetError(ctx, "unexpected error NULL");
    }

}

void GenericSelection(Parser * ctx)
{
    

     
}

void GenericAssocList(Parser * ctx)
{

    

     
}

void GenericAssociation(Parser * ctx)
{
    

     
}

void TTypeName_Swap(TTypeName * a, TTypeName * b)
{
    TTypeName temp = *a;
    *a = *b;
    *b = temp;
}

void TTypeName_Init(TTypeName * p) /*@default*/
{
    p->Type = TypeName_ID;
    p->SpecifierQualifierList.pData = NULL;
    p->SpecifierQualifierList.Size = 0;
    p->SpecifierQualifierList.Capacity = 0;
    TDeclarator_Init(&p->Declarator);
}



void TypeName(Parser * ctx, TTypeName * pTypeName)
{
     

    Specifier_Qualifier_List(ctx, &pTypeName->SpecifierQualifierList);

    TDeclarator * pDeclarator = NULL;
    Declarator(ctx, true, &pDeclarator);
    if (pDeclarator)
    {
        TDeclarator_Swap(&pTypeName->Declarator, pDeclarator);
        TDeclarator_Delete(pDeclarator);
    }
}


static void PostfixExpressionCore(Parser * ctx, TPostfixExpressionCore * pPostfixExpressionCore)
{
    
     

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        

        pPostfixExpressionCore->token = token;


        
        token = Parser_Match(ctx,
            &pPostfixExpressionCore->ClueList0);

        if (token != TK_RIGHT_PARENTHESIS)
        {
            ArgumentExpressionList(ctx, &pPostfixExpressionCore->pExpressionRight);
        }

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS,
            &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_LEFT_SQUARE_BRACKET:
    {
        pPostfixExpressionCore->token = token;
        

        Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET,
            &pPostfixExpressionCore->ClueList0);

        Expression0(ctx, &pPostfixExpressionCore->pExpressionRight);

        Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_FULL_STOP:
    {
        
        pPostfixExpressionCore->token = token;

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);

        PTR_STRING_REPLACE(pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER,
            &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_ARROW:
    {
        
        pPostfixExpressionCore->token = token;

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);

        PTR_STRING_REPLACE(pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER, &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_PLUSPLUS:
    {
        pPostfixExpressionCore->token = token;
        

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);
    }
    break;

    case TK_MINUSMINUS:
    {
        
        pPostfixExpressionCore->token = token;
        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);
    }
    break;

    default:
        
        break;
    }


    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    case TK_LEFT_SQUARE_BRACKET:
    case TK_FULL_STOP:
    case TK_ARROW:
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:
    {
        TPostfixExpressionCore * pPostfixExpressionCoreNext =
            TPostfixExpressionCore_Create();
        PostfixExpressionCore(ctx, pPostfixExpressionCoreNext);

        if (pPostfixExpressionCore->pNext != NULL)
        {
            SetError(ctx, "unexpected error");
        }
        pPostfixExpressionCore->pNext = pPostfixExpressionCoreNext;
    }
    break;
    default:
        
        break;
    }


}

void PostfixExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL;

                          

    Tokens token = Parser_CurrentToken(ctx);



    if (token == TK_LEFT_PARENTHESIS)
    {
        const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);
        Tokens lookAheadToken = Parser_LookAheadToken(ctx);

        if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
        {
            

            TPostfixExpressionCore * pTPostfixExpressionCore =
                TPostfixExpressionCore_Create();

            Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pTPostfixExpressionCore->ClueList0);

            TTypeName typeName;
            TTypeName_Init(&typeName);

            TypeName(ctx, &typeName);
            TTypeName_Destroy(&typeName);

            Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pTPostfixExpressionCore->ClueList1);

            Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &pTPostfixExpressionCore->ClueList2);

            Initializer_List(ctx, &pTPostfixExpressionCore->InitializerList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, &pTPostfixExpressionCore->ClueList3);

            if (Parser_CurrentToken(ctx) == TK_COMMA)
            {
                Parser_Match(ctx, &pTPostfixExpressionCore->ClueList4);
            }

            *ppExpression = (TExpression *)pTPostfixExpressionCore;
        }

        else
        {
            
            TExpression * pPrimaryExpression;
            PrimaryExpression(ctx, &pPrimaryExpression);
            *ppExpression = pPrimaryExpression;
        }
    }
    else
    {
        
        

        
        TExpression * pPrimaryExpression;
        PrimaryExpression(ctx, &pPrimaryExpression);
        *ppExpression = pPrimaryExpression;
    }

    token = Parser_CurrentToken(ctx);
    if (IsFirstOfPrimaryExpression(token))
    {

        

        TPostfixExpressionCore * pPostfixExpressionCore =
            TPostfixExpressionCore_Create();
        pPostfixExpressionCore->pExpressionLeft = *ppExpression;
        PostfixExpressionCore(ctx, pPostfixExpressionCore);
        *ppExpression = (TExpression *)pPostfixExpressionCore;
    }
    else
    {
        switch (token)
        {
        case TK_LEFT_PARENTHESIS:
        {
            TPostfixExpressionCore * pPostfixExpressionCore =
                TPostfixExpressionCore_Create();
            pPostfixExpressionCore->pExpressionLeft = *ppExpression;

            String * /*@auto*/ lexemeCopy = NULL;

            TPrimaryExpressionValue * ppri =
                TExpression_As_TPrimaryExpressionValue(*ppExpression);
            if (ppri)
            {
                PTR_STRING_REPLACE(lexemeCopy, ppri->lexeme);
            }
            PostfixExpressionCore(ctx, pPostfixExpressionCore);
            *ppExpression = (TExpression *)pPostfixExpressionCore;



            Free(lexemeCopy);
        }
        break;
        case TK_LEFT_SQUARE_BRACKET:
        case TK_FULL_STOP:
        case TK_ARROW:
        case TK_PLUSPLUS:
        case TK_MINUSMINUS:
        {
            TPostfixExpressionCore * pPostfixExpressionCore =
                TPostfixExpressionCore_Create();
            pPostfixExpressionCore->pExpressionLeft = *ppExpression;
            PostfixExpressionCore(ctx, pPostfixExpressionCore);
            *ppExpression = (TExpression *)pPostfixExpressionCore;
        }
        break;
        default:
            
            break;
        }

    }

}

void ArgumentExpressionList(Parser * ctx, TExpression ** ppExpression)
{
     
    TExpression * pAssignmentExpression;
    AssignmentExpression(ctx, &pAssignmentExpression);
    *ppExpression = pAssignmentExpression;

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        TBinaryExpression * pExpr =
            TBinaryExpression_Create();

        Parser_Match(ctx, &pExpr->ClueList0);

        TExpression * pAssignmentExpressionRight;
        AssignmentExpression(ctx, &pAssignmentExpressionRight);


        GetPosition(ctx, &pExpr->Position);
        pExpr->token = TK_COMMA;
        pExpr->pExpressionLeft = pAssignmentExpression;
        pExpr->pExpressionRight = pAssignmentExpressionRight;



        *ppExpression = (TExpression *)pExpr;
    }

    token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        TBinaryExpression * pExpr =
            TBinaryExpression_Create();

        Parser_Match(ctx, &pExpr->ClueList0);

        GetPosition(ctx, &pExpr->Position);
        pExpr->token = TK_COMMA;
        pExpr->pExpressionLeft = *ppExpression;

        TExpression * pExpressionRight;
        ArgumentExpressionList(ctx, &pExpressionRight);
        pExpr->pExpressionRight = pExpressionRight;

        *ppExpression = (TExpression *)pExpr;
    }
}



static bool IsTypeQualifierToken(Tokens token)
{
    bool bResult = false;
    switch (token)
    {
        
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:
        
        bResult = true;
        break;
#ifdef LANGUAGE_EXTENSIONS

        


    case TK_AUTO:
    case TK_LEFT_SQUARE_BRACKET:


        bResult = true;
        break;
#endif
    default:
        
        break;
    }
    return bResult;
}

int IsTypeName(Parser * ctx, Tokens token, const char * lexeme)
{

    int bResult = false;

    if (lexeme == NULL)
    {
        return false;
    }

    switch (token)
    {

    case TK_IDENTIFIER:
        bResult = SymbolMap_IsTypeName(ctx->pCurrentScope, lexeme);
        
        break;

        
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:

#ifdef LANGUAGE_EXTENSIONS

    case TK_AUTO:


#endif

        
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:
    case TK_STRUCT:
    case TK_UNION:
    case TK_ENUM:
        bResult = true;
        break;
    default:
        
        break;
    }

    return bResult;
}

void UnaryExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; 

                           

    Tokens token0 = Parser_CurrentToken(ctx);
    Tokens tokenAhead = Parser_LookAheadToken(ctx);
    const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);

    if (IsTypeName(ctx, tokenAhead, lookAheadlexeme))
    {
        
        TExpression * pPostfixExpression;
        PostfixExpression(ctx, &pPostfixExpression);
        *ppExpression = (TExpression *)(pPostfixExpression);
        return;
    }

    else if (IsFirstOfPrimaryExpression(token0))
    {
        

        TExpression * pPostfixExpression;
        PostfixExpression(ctx, &pPostfixExpression);
        *ppExpression = (TExpression *)(pPostfixExpression);
        return;
    }

    switch (token0)
    {
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:
    {
        TUnaryExpressionOperator * pUnaryExpressionOperator =
            TUnaryExpressionOperator_Create();

        Parser_Match(ctx, &pUnaryExpressionOperator->ClueList0);

        TExpression * pUnaryExpression;
        UnaryExpression(ctx, &pUnaryExpression);


        pUnaryExpressionOperator->token = token0;
        pUnaryExpressionOperator->pExpressionRight = pUnaryExpression;
        *ppExpression = (TExpression *)pUnaryExpressionOperator;
    }
    break;

    
    case TK_AMPERSAND:
    case TK_ASTERISK:
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    case TK_TILDE:
    case TK_EXCLAMATION_MARK:
    {
        TUnaryExpressionOperator * pUnaryExpressionOperator =
            TUnaryExpressionOperator_Create();

        Parser_Match(ctx, &pUnaryExpressionOperator->ClueList0);
        TExpression * pCastExpression;
        CastExpression(ctx, &pCastExpression);

        pUnaryExpressionOperator->token = token0;
        pUnaryExpressionOperator->pExpressionRight = pCastExpression;
        *ppExpression = (TExpression *)pUnaryExpressionOperator;

    }
    break;

    

    case TK_SIZEOF:
    {
        TUnaryExpressionOperator * pUnaryExpressionOperator =
            TUnaryExpressionOperator_Create();
        *ppExpression = (TExpression *)pUnaryExpressionOperator;

        pUnaryExpressionOperator->token = token0;

        Parser_MatchToken(ctx, TK_SIZEOF, &pUnaryExpressionOperator->ClueList0);

        if (Parser_CurrentToken(ctx) == TK_LEFT_PARENTHESIS)
        {
            const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);
            Tokens lookAheadToken = Parser_LookAheadToken(ctx);

            if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
            {
                
                Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pUnaryExpressionOperator->ClueList1);
                TypeName(ctx, &pUnaryExpressionOperator->TypeName);
                Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pUnaryExpressionOperator->ClueList2);
            }
            else
            {
                
                TExpression * pTUnaryExpression;
                UnaryExpression(ctx, &pTUnaryExpression);
                pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
            }
        }
        else
        {
            
            TExpression * pTUnaryExpression;
            UnaryExpression(ctx, &pTUnaryExpression);
            pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
        }
    }
    break;

    case TK__ALINGOF:
        
        
        break;
    case TK_EOF:
        break;
        
    default:
        
        
        
        break;
    }

}

void CastExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; 

                           

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_PARENTHESIS)
    {
        const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);
        Tokens lookAheadToken = Parser_LookAheadToken(ctx);

        if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
        {
            TScannerItemList tempList0 = { 0, 0 };
            Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &tempList0);

            TTypeName typeName;
            TTypeName_Init(&typeName);
            TypeName(ctx, &typeName);

            TScannerItemList tempList1 = { 0, 0 };
            token = Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &tempList1);

            if (token == TK_LEFT_CURLY_BRACKET)
            {
                
                
                
                 

                Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, NULL);

                TPostfixExpressionCore * pTPostfixExpressionCore =
                    TPostfixExpressionCore_Create();
                pTPostfixExpressionCore->pTypeName = TTypeName_Create();
                TTypeName_Swap(pTPostfixExpressionCore->pTypeName, &typeName);

                
                Initializer_List(ctx, &pTPostfixExpressionCore->InitializerList);

                


                if (Parser_CurrentToken(ctx) == TK_COMMA)
                {
                    Parser_Match(ctx, NULL);
                }
                Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, NULL);
                *ppExpression = (TExpression *)pTPostfixExpressionCore;
                
            }
            else
            {
                TCastExpressionType * pCastExpressionType =
                    TCastExpressionType_Create();

                TScannerItemList_Swap(&tempList0, &pCastExpressionType->ClueList0);
                TScannerItemList_Swap(&tempList1, &pCastExpressionType->ClueList1);

                TExpression * pCastExpression;
                CastExpression(ctx, &pCastExpression);

                TTypeName_Swap(&pCastExpressionType->TypeName, &typeName);
                pCastExpressionType->pExpression = pCastExpression;
                *ppExpression = (TExpression *)pCastExpressionType;

            }

            TTypeName_Destroy(&typeName);
            TScannerItemList_Destroy(&tempList0);
            TScannerItemList_Destroy(&tempList1);
        }
        else
        {
            TExpression * pUnaryExpression;
            UnaryExpression(ctx, &pUnaryExpression);
            *ppExpression = pUnaryExpression;
        }
    }
    else
    {
        TExpression * pUnaryExpression;
        UnaryExpression(ctx, &pUnaryExpression);

        *ppExpression = pUnaryExpression;
    }
}


void MultiplicativeExpression(Parser * ctx, TExpression ** ppExpression)
{


     

    TExpression * pExpressionLeft;
    CastExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_PERCENT_SIGN:
    case TK_SOLIDUS:
    case TK_ASTERISK:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();

        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;

        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        CastExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_PERCENT_SIGN:
    case TK_SOLIDUS:
    case TK_ASTERISK:
    {
        TBinaryExpression * pBinaryExpression =
            TBinaryExpression_Create();

        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        MultiplicativeExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void AdditiveExpression(Parser * ctx, TExpression ** ppExpression)
{

     

    TExpression * pExpressionLeft;
    MultiplicativeExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    {
        TBinaryExpression * pBinaryExpression =
            TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        MultiplicativeExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        AdditiveExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

}

void ShiftExpression(Parser * ctx, TExpression ** ppExpression)
{

     


    TExpression * pExpressionLeft;
    AdditiveExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_GREATERGREATER:
    case TK_LESSLESS:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        AdditiveExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_GREATERGREATER:
    case TK_LESSLESS:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        ShiftExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void RelationalExpression(Parser * ctx, TExpression ** ppExpression)
{
     

    TExpression * pExpressionLeft;
    ShiftExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_LESS_THAN_SIGN:
    case TK_GREATER_THAN_SIGN:
    case TK_GREATEREQUAL:
    case TK_LESSEQUAL:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        ShiftExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LESS_THAN_SIGN:
    case TK_GREATER_THAN_SIGN:
    case TK_GREATEREQUAL:
    case TK_LESSEQUAL:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        RelationalExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

}

void EqualityExpression(Parser * ctx, TExpression ** ppExpression)
{
     

    TExpression * pExpressionLeft;
    RelationalExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_EQUALEQUAL:
    case TK_NOTEQUAL:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        RelationalExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_EQUALEQUAL:
    case TK_NOTEQUAL:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        EqualityExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void AndExpression(Parser * ctx, TExpression ** ppExpression)
{
     

    TExpression * pExpressionLeft;
    EqualityExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_AMPERSAND:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        EqualityExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_AMPERSAND:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        AndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void ExclusiveOrExpression(Parser * ctx, TExpression ** ppExpression)
{
     

    TExpression * pExpressionLeft;
    AndExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_CIRCUMFLEX_ACCENT:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        AndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_CIRCUMFLEX_ACCENT:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);


        TExpression * pExpressionRight;
        ExclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

}

void InclusiveOrExpression(Parser * ctx, TExpression ** ppExpression)
{

     

    TExpression * pExpressionLeft;
    ExclusiveOrExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_VERTICAL_LINE:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        ExclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_VERTICAL_LINE:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        InclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void LogicalAndExpression(Parser * ctx, TExpression ** ppExpression)
{

     

    TExpression * pExpressionLeft;
    InclusiveOrExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_ANDAND:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;
        GetPosition(ctx, &pBinaryExpression->Position);


        Parser_Match(ctx, &pBinaryExpression->ClueList0);


        TExpression * pExpressionRight;
        InclusiveOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_ANDAND:
    {
        TBinaryExpression * pBinaryExpression =
            TBinaryExpression_Create();

        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        LogicalAndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}

void LogicalOrExpression(Parser * ctx, TExpression ** ppExpression)
{
     


    TExpression * pExpressionLeft;
    LogicalAndExpression(ctx, &pExpressionLeft);
    *ppExpression = pExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_OROR:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        LogicalAndExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }

    token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_OROR:
    {
        TBinaryExpression * pBinaryExpression = TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->token = token;
        pBinaryExpression->pExpressionLeft = *ppExpression;


        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        TExpression * pExpressionRight;
        LogicalOrExpression(ctx, &pExpressionRight);
        pBinaryExpression->pExpressionRight = pExpressionRight;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;
    default:
        
        break;
    }
}


void ConditionalExpression(Parser * ctx, TExpression ** ppExpression)
{
     
    TExpression * pLogicalOrExpressionLeft;
    LogicalOrExpression(ctx, &pLogicalOrExpressionLeft);
    *ppExpression = pLogicalOrExpressionLeft;

    if (Parser_CurrentToken(ctx) == TK_QUESTION_MARK)
    {
        TTernaryExpression * pTernaryExpression =
            TTernaryExpression_Create();

        Parser_Match(ctx, &pTernaryExpression->ClueList0);

        TExpression * pTExpression;
        Expression0(ctx, &pTExpression);

        Parser_MatchToken(ctx, TK_COLON, &pTernaryExpression->ClueList1);

        TExpression * pConditionalExpressionRight;
        ConditionalExpression(ctx, &pConditionalExpressionRight);


        pTernaryExpression->token = TK_QUESTION_MARK;
        pTernaryExpression->pExpressionLeft = pLogicalOrExpressionLeft;
        pTernaryExpression->pExpressionMiddle = pTExpression;
        pTernaryExpression->pExpressionRight = pConditionalExpressionRight;
        *ppExpression = (TExpression *)pTernaryExpression;
    }


}

void AssignmentExpression(Parser * ctx, TExpression ** ppExpression)
{
     


    
    
    
    
    TExpression * pConditionalExpressionLeft;
    ConditionalExpression(ctx, &pConditionalExpressionLeft);
    *ppExpression = pConditionalExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {

    case TK_EQUALS_SIGN:
    case TK_MULTIEQUAL:
    case TK_DIVEQUAL:
    case TK_PERCENT_EQUAL:
    case TK_PLUSEQUAL:
    case TK_MINUS_EQUAL:
    case TK_LESSLESSEQUAL:
    case TK_GREATERGREATEREQUAL:
    case TK_ANDEQUAL:
    case TK_CARETEQUAL:
    case TK_OREQUAL:
    {
        TBinaryExpression * pBinaryExpression =
            TBinaryExpression_Create();

        Parser_Match(ctx, &pBinaryExpression->ClueList0);

        
        
        
        TExpression * pAssignmentExpressionRight;
        AssignmentExpression(ctx, &pAssignmentExpressionRight);

        GetPosition(ctx, &pBinaryExpression->Position);

        pBinaryExpression->pExpressionLeft = *ppExpression;
        pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
        pBinaryExpression->token = token;
        *ppExpression = (TExpression *)pBinaryExpression;
    }
    break;

    default:
        
        break;
    }
}

void Expression0(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; 
                           
    TExpression * pAssignmentExpressionLeft;
    AssignmentExpression(ctx, &pAssignmentExpressionLeft);
    *ppExpression = pAssignmentExpressionLeft;

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        TExpression * pAssignmentExpressionRight;
        Parser_Match(ctx, NULL);
        Expression0(ctx, &pAssignmentExpressionRight);

        TBinaryExpression * pBinaryExpression =
            TBinaryExpression_Create();
        GetPosition(ctx, &pBinaryExpression->Position);
        pBinaryExpression->pExpressionLeft = *ppExpression;
        pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
        pBinaryExpression->token = TK_COMMA;

        *ppExpression = (TExpression *)pBinaryExpression;
    }
}

void ConstantExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; 

                           
    ConditionalExpression(ctx, ppExpression);
}





void Designator(Parser * ctx, TDesignator * pDesignator);
void Designator_List(Parser * ctx, TDesignatorList * pDesignatorList);
void Designation(Parser * ctx, TDesignatorList * pDesignatorList);
void Initializer_List(Parser * ctx, TInitializerList * pInitializerList);

bool Statement(Parser * ctx, TStatement ** ppStatement);

void Compound_Statement(Parser * ctx, TStatement ** ppStatement);

void Parameter_Declaration(Parser * ctx, TParameter * pParameterDeclaration);
bool Declaration(Parser * ctx, TAnyDeclaration ** ppDeclaration);
void Type_Qualifier_List(Parser * ctx, TTypeQualifierList * pQualifiers);
void Declaration_Specifiers(Parser * ctx, TDeclarationSpecifiers * pDeclarationSpecifiers);

void Type_Specifier(Parser * ctx, TTypeSpecifier ** ppTypeSpecifier);
bool Type_Qualifier(Parser * ctx, TTypeQualifier * pQualifier);
void Initializer(Parser * ctx,
    TInitializer ** ppInitializer,
    Tokens endToken1,
    Tokens endToken2);


void Expression_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    TExpressionStatement * pExpression = TExpressionStatement_Create();
    *ppStatement = (TStatement *)pExpression;
    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK_SEMICOLON)
    {
        Expression0(ctx, &pExpression->pExpression);
    }

    Parser_MatchToken(ctx, TK_SEMICOLON, &pExpression->ClueList0);
}

void Selection_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_IF:
    {
        TIfStatement * pIfStatement = TIfStatement_Create();
        *ppStatement = (TStatement *)pIfStatement;

        Parser_Match(ctx, &pIfStatement->ClueList0);

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pIfStatement->ClueList1);


        Expression0(ctx, &pIfStatement->pConditionExpression);

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pIfStatement->ClueList2);

        Statement(ctx, &pIfStatement->pStatement);
        token = Parser_CurrentToken(ctx);

        if (token == TK_ELSE)
        {
            Parser_Match(ctx, &pIfStatement->ClueList3);
            Statement(ctx, &pIfStatement->pElseStatement);
        }
    }
    break;

    case TK_SWITCH:
    {
        TSwitchStatement * pSelectionStatement = TSwitchStatement_Create();
        *ppStatement = (TStatement *)pSelectionStatement;


        Parser_Match(ctx, &pSelectionStatement->ClueList0);


        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pSelectionStatement->ClueList1);

        Expression0(ctx, &pSelectionStatement->pConditionExpression);


        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pSelectionStatement->ClueList2);

        Statement(ctx, &pSelectionStatement->pExpression);
    }
    break;

    default:
        
        break;
    }
}

void Jump_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_GOTO:
    {
        TJumpStatement * pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement *)pJumpStatement;

        Parser_Match(ctx, &pJumpStatement->ClueList0);
        PTR_STRING_REPLACE(pJumpStatement->Identifier, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_IDENTIFIER, &pJumpStatement->ClueList1);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
    }
    break;

    case TK_CONTINUE:
    {
        TJumpStatement * pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement *)pJumpStatement;
        Parser_Match(ctx, &pJumpStatement->ClueList0);

        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
    }
    break;

    case TK_BREAK:
    {
        TJumpStatement * pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement *)pJumpStatement;

        Parser_Match(ctx, &pJumpStatement->ClueList0);
        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
    }
    break;

    case TK_RETURN:
    {
        TJumpStatement * pJumpStatement = TJumpStatement_Create();
        pJumpStatement->token = token;
        *ppStatement = (TStatement *)pJumpStatement;

        token = Parser_Match(ctx, &pJumpStatement->ClueList0);

        if (token != TK_SEMICOLON)
        {
            Expression0(ctx, &pJumpStatement->pExpression);
        }

        Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
    }
    break;

    default:
        
        break;
    }
}

void Iteration_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_WHILE:
    {
        TWhileStatement * pWhileStatement = TWhileStatement_Create();
        *ppStatement = (TStatement *)pWhileStatement;

        Parser_Match(ctx, &pWhileStatement->ClueList0);

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pWhileStatement->ClueList1);

        Expression0(ctx, &pWhileStatement->pExpression);

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pWhileStatement->ClueList2);

        Statement(ctx, &pWhileStatement->pStatement);
    }
    break;

    case TK_DO:
    {
        TDoStatement * pDoStatement = TDoStatement_Create();
        *ppStatement = (TStatement *)pDoStatement;

        Parser_Match(ctx, &pDoStatement->ClueList0); 

        Statement(ctx, &pDoStatement->pStatement);

        Parser_MatchToken(ctx, TK_WHILE, &pDoStatement->ClueList1); 

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDoStatement->ClueList2); 

        Expression0(ctx, &pDoStatement->pExpression);

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDoStatement->ClueList3); 

        Parser_MatchToken(ctx, TK_SEMICOLON, &pDoStatement->ClueList4); 
    }
    break;

    case TK_FOR:
    {
        TForStatement * pIterationStatement = TForStatement_Create();
        *ppStatement = (TStatement *)pIterationStatement;

        Parser_Match(ctx, &pIterationStatement->ClueList0);

        token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pIterationStatement->ClueList1);

        
        if (token != TK_SEMICOLON)
        {
            
            
            

            bool bHasDeclaration = Declaration(ctx, &pIterationStatement->pInitDeclarationOpt);

            if (bHasDeclaration)
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }
                else
                {
                    
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }
            }

            else
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    
                    Expression0(ctx, &pIterationStatement->pExpression1);


                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }

                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
                }

                else
                {
                    
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
                }

            }
        }

        else
        {
            

            Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);

            token = Parser_CurrentToken(ctx);

            if (token != TK_SEMICOLON)
            {
                
                Expression0(ctx, &pIterationStatement->pExpression2);


                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
            }

            else
            {
                
                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
            }
        }

        token = Parser_CurrentToken(ctx);

        
        if (token != TK_RIGHT_PARENTHESIS)
        {
            Expression0(ctx, &pIterationStatement->pExpression3);
        }

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pIterationStatement->ClueList4);

        Statement(ctx, &pIterationStatement->pStatement);
    }
    break;

    default:
        
        break;
    }
}


void Labeled_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    TLabeledStatement * pLabeledStatement = TLabeledStatement_Create();
    *ppStatement = (TStatement *)pLabeledStatement;
    Tokens token = Parser_CurrentToken(ctx);
    pLabeledStatement->token = token;

    if (token == TK_IDENTIFIER)
    {
        
        PTR_STRING_REPLACE(pLabeledStatement->Identifier, Lexeme(ctx));

        Parser_Match(ctx, &pLabeledStatement->ClueList0);

        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList1);

        Statement(ctx, &pLabeledStatement->pStatementOpt);
    }

    else if (token == TK_CASE)
    {

        Parser_Match(ctx, &pLabeledStatement->ClueList0);

        ConstantExpression(ctx, &pLabeledStatement->pExpression);


        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList1);

        Statement(ctx, &pLabeledStatement->pStatementOpt);
    }

    else if (token == TK_DEFAULT)
    {

        Parser_Match(ctx, &pLabeledStatement->ClueList0);

        Parser_MatchToken(ctx, TK_COLON, &pLabeledStatement->ClueList1);

        Statement(ctx, &pLabeledStatement->pStatementOpt);
    }
}

void Asm_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    TAsmStatement * pAsmStatement = TAsmStatement_Create();
    *ppStatement = (TStatement *)pAsmStatement;
    Parser_MatchToken(ctx, TK__ASM, NULL);
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_CURLY_BRACKET)
    {
        Parser_Match(ctx, NULL);

        for (; ;)
        {
            if (ErrorOrEof(ctx))
            {
                break;
            }

            token = Parser_CurrentToken(ctx);

            if (token == TK_RIGHT_CURLY_BRACKET)
            {
                Parser_Match(ctx, NULL);
                break;
            }

            Parser_Match(ctx, NULL);
        }
    }

    else
    {
        
        
        
        token = Parser_CurrentToken(ctx);

        for (; ;)
        {
            if (ErrorOrEof(ctx))
            {
                break;
            }

            token = Parser_CurrentToken(ctx);

            if (token == TK_RIGHT_CURLY_BRACKET)
            {
                
                
                
                
                break;
            }

            if (token == TK_SEMICOLON)
            {
                break;
            }

            Parser_Match(ctx, NULL);
        }
    }

    
    token = Parser_CurrentToken(ctx);

    if (token == TK_SEMICOLON)
    {
        Parser_Match(ctx, NULL);
    }
}

bool Statement(Parser * ctx, TStatement ** ppStatement)
{
    

    if (Parser_HasError(ctx))
    {
        return false;
    }

    bool bResult = false;
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);

    switch (token)
    {
    case TK__ASM:
        bResult = true;
        Asm_Statement(ctx, ppStatement);
        break;

    case TK_LEFT_CURLY_BRACKET:
    {
        bResult = true;
        Compound_Statement(ctx, ppStatement);
    }
    break;

    case TK_CASE:
    case TK_DEFAULT:
        bResult = true;
        Labeled_Statement(ctx, ppStatement);
        break;

    case TK_SWITCH:
        bResult = true;
        Selection_Statement(ctx, ppStatement);
        break;

    case TK_IF:
        bResult = true;
        Selection_Statement(ctx, ppStatement);
        break;

        
        
        
        
        
        
        
        

        
    case TK_WHILE:
    case TK_FOR:
    case TK_DO:
        bResult = true;
        Iteration_Statement(ctx, ppStatement);
        break;

        
    case TK_GOTO:
    case TK_CONTINUE:
    case TK_BREAK:
    case TK_RETURN:
        bResult = true;
        Jump_Statement(ctx, ppStatement);
        break;

        
        
    case TK_LEFT_SQUARE_BRACKET:
    case TK_LEFT_PARENTHESIS:
    case TK_SEMICOLON:

    case TK_DECIMAL_INTEGER:
    case TK_FLOAT_NUMBER:
    case TK_STRING_LITERAL:


        
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:

    case TK_SIZEOF:

        
    case TK_AMPERSAND:
    case TK_ASTERISK:
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    case TK_TILDE:
    case TK_EXCLAMATION_MARK:
#ifdef LANGUAGE_EXTENSIONS
        
    case TK_ANDAND: 
#endif
        bResult = true;
        Expression_Statement(ctx, ppStatement);
        break;

    case TK_IDENTIFIER:

        if (IsTypeName(ctx, TK_IDENTIFIER, lexeme))
        {
            
        }
        else
        {
            if (Parser_LookAheadToken(ctx) == TK_COLON)
            {
                
                Labeled_Statement(ctx, ppStatement);
            }

            else
            {
                Expression_Statement(ctx, ppStatement);
            }

            bResult = true;
        }

        break;

    case TK_INLINE:
    case TK__INLINE: 
    case TK__NORETURN:
    case TK__ALIGNAS:

        
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:


    case TK_TYPEDEF:
    case TK_EXTERN:
    case TK_STATIC:
    case TK__THREAD_LOCAL:
    case TK_AUTO:
    case TK_REGISTER:
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:

    case TK_STRUCT:
    case TK_UNION:
    case TK_ENUM:
        bResult = false;
        break;

    default:

        SetError(ctx, "unexpected error");
        
        
        
        break;
    }

    return bResult;
}

void Block_Item(Parser * ctx, TBlockItem ** ppBlockItem)
{
     
    *ppBlockItem = NULL;
    TStatement * pStatement = NULL;

    if (Statement(ctx, &pStatement))
    {
        *ppBlockItem = (TBlockItem *)pStatement;
        
    }

    else
    {


        TAnyDeclaration * pDeclaration;
        Declaration(ctx, &pDeclaration);
        *ppBlockItem = (TBlockItem *)pDeclaration;
        
    }
}

void Block_Item_List(Parser * ctx, TBlockItemList * pBlockItemList)
{
    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        TBlockItem * pBlockItem = NULL;
        Block_Item(ctx, &pBlockItem);
        TBlockItemList_PushBack(pBlockItemList, pBlockItem);
        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_RIGHT_CURLY_BRACKET)
        {
            
            break;
        }

        if (ErrorOrEof(ctx))
            break;
    }
}

void Compound_Statement(Parser * ctx, TStatement ** ppStatement)
{
     
    TCompoundStatement * pCompoundStatement = TCompoundStatement_Create();
    *ppStatement = (TStatement *)pCompoundStatement;

    struct SymbolMap BlockScope = SYMBOLMAP_INIT;

    BlockScope.pPrevious = ctx->pCurrentScope;
    ctx->pCurrentScope = &BlockScope;

    Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &pCompoundStatement->ClueList0);

    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        Block_Item_List(ctx, &pCompoundStatement->BlockItemList);
    }

    Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, &pCompoundStatement->ClueList1);

    

    ctx->pCurrentScope = BlockScope.pPrevious;
    SymbolMap_Destroy(&BlockScope);
}

void Struct_Or_Union(Parser * ctx,
    TStructUnionSpecifier * pStructUnionSpecifier)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_STRUCT:
        pStructUnionSpecifier->Token = token;
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList0);
        break;

    case TK_UNION:
        pStructUnionSpecifier->Token = token;
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList0);
        break;

    default:
        
        break;
    }
}

void Static_Assert_Declaration(Parser * ctx, TStaticAssertDeclaration * pStaticAssertDeclaration)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__STATIC_ASSERT)
    {
        Parser_Match(ctx, &pStaticAssertDeclaration->ClueList0);

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pStaticAssertDeclaration->ClueList1);

        ConstantExpression(ctx,
            &pStaticAssertDeclaration->pConstantExpression);

        Parser_MatchToken(ctx, TK_COMMA, &pStaticAssertDeclaration->ClueList2);

        PTR_STRING_REPLACE(pStaticAssertDeclaration->Text, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_STRING_LITERAL, &pStaticAssertDeclaration->ClueList3);

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pStaticAssertDeclaration->ClueList4);

        Parser_MatchToken(ctx, TK_SEMICOLON, &pStaticAssertDeclaration->ClueList5);
    }
}

void Specifier_Qualifier_List(Parser * ctx, TSpecifierQualifierList * pSpecifierQualifierList)
{
     
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);
    if (TTypeSpecifier_IsFirst(ctx, token, lexeme))
    {
        if (TSpecifierQualifierList_CanAdd(pSpecifierQualifierList, token, lexeme))
        {
            TTypeSpecifier * pTypeSpecifier = NULL;
            Type_Specifier(ctx, &pTypeSpecifier);
            if (pTypeSpecifier != NULL)
            {
                
                TSpecifierQualifierList_PushBack(pSpecifierQualifierList, (TSpecifierQualifier *)pTypeSpecifier);
            }
        }
        else
        {
            SetError(ctx, "invalid specifier-qualifier-list");
        }

    }
    else if (TTypeQualifier_IsFirst(token))
    {
        TTypeQualifier * pTypeQualifier = TTypeQualifier_Create();
        Type_Qualifier(ctx, pTypeQualifier);
        TSpecifierQualifierList_PushBack(pSpecifierQualifierList, TTypeQualifier_As_TSpecifierQualifier(pTypeQualifier));
    }
    else
    {
        SetError(ctx, "internal error 01 %s", TokenToString(token));
    }


    token = Parser_CurrentToken(ctx);
    lexeme = Lexeme(ctx);
    if (TTypeQualifier_IsFirst(token))
    {
        Specifier_Qualifier_List(ctx, pSpecifierQualifierList);
    }
    else if (TTypeSpecifier_IsFirst(ctx, token, lexeme))
    {
        if (TSpecifierQualifierList_CanAdd(pSpecifierQualifierList, token, lexeme))
        {
             

            Specifier_Qualifier_List(ctx, pSpecifierQualifierList);
        }
    }

}


void Struct_Declarator(Parser * ctx,

    TStructDeclarator ** ppTDeclarator2)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COLON)
    {
        
        

        Parser_Match(ctx, NULL);
        TExpression * p = NULL;
        ConstantExpression(ctx, &p);
        TExpression_Delete(p);
    }

    else
    {
        TInitDeclarator * pInitDeclarator =
            TInitDeclarator_Create();

        *ppTDeclarator2 = pInitDeclarator;

        Declarator(ctx, false, &pInitDeclarator->pDeclarator);

        token = Parser_CurrentToken(ctx);



        if (token == TK_COLON)
        {
            Parser_Match(ctx, &pInitDeclarator->ClueList0);

            TExpression * p = NULL;
            ConstantExpression(ctx, &p);
            TExpression_Delete(p);
        }
#ifdef LANGUAGE_EXTENSIONS


        if (token == TK_EQUALS_SIGN)
        {
            Parser_Match(ctx, &pInitDeclarator->ClueList1); 
            Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);

            token = Parser_CurrentToken(ctx);

        }

#endif
    }
}

void Struct_Declarator_List(Parser * ctx,

    TStructDeclaratorList * pStructDeclarationList)
{
     
    TStructDeclarator * pTDeclarator2 = NULL;

    Struct_Declarator(ctx, &pTDeclarator2);
    TStructDeclaratorList_Add(pStructDeclarationList, pTDeclarator2);

    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            
            Parser_Match(ctx, &pTDeclarator2->ClueList0);
            

            Struct_Declarator_List(ctx, pStructDeclarationList);
        }
        else if (token == TK_SEMICOLON)
        {
            
            
            break;
        }
        else
        {
            if (token == TK_RIGHT_CURLY_BRACKET)
            {
                SetError(ctx, "syntax error: missing ';' before '}'");
            }
            else
            {
                SetError(ctx, "syntax error: expected ',' or ';'");
            }

            break;
        }
    }
}

void Struct_Declaration(Parser * ctx,
    TAnyStructDeclaration ** ppStructDeclaration)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token != TK__STATIC_ASSERT)
    {
        TStructDeclaration * pStructDeclarationBase = TStructDeclaration_Create();
        *ppStructDeclaration = (TAnyStructDeclaration *)pStructDeclarationBase;
        Specifier_Qualifier_List(ctx,
            &pStructDeclarationBase->SpecifierQualifierList);
        token = Parser_CurrentToken(ctx);

        if (token != TK_SEMICOLON)
        {
            Struct_Declarator_List(ctx,
                &pStructDeclarationBase->DeclaratorList);

            Parser_MatchToken(ctx, TK_SEMICOLON, &pStructDeclarationBase->ClueList1);
            
        }
        else
        {
            Parser_MatchToken(ctx, TK_SEMICOLON, &pStructDeclarationBase->ClueList1);
        }
    }

    else
    {
        TStaticAssertDeclaration * pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
        *ppStructDeclaration = (TAnyStructDeclaration *)pStaticAssertDeclaration;
        Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
    }
}

void Struct_Declaration_List(Parser * ctx,
    TStructDeclarationList * pStructDeclarationList)
{
     
    if (ErrorOrEof(ctx))
    {
        return;
    }

    TAnyStructDeclaration * pStructDeclaration = NULL;
    Struct_Declaration(ctx, &pStructDeclaration);
    TStructDeclarationList_PushBack(pStructDeclarationList, pStructDeclaration);


    Tokens token = Parser_CurrentToken(ctx);
    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        
        Struct_Declaration_List(ctx, pStructDeclarationList);
    }
}

void UnionSetItem(Parser * ctx, TUnionSet * p)
{
     
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);

    TUnionSetItem * pItem = TUnionSetItem_Create();

    if (token == TK_IDENTIFIER)
    {
        PTR_STRING_REPLACE(pItem->Name, lexeme);
        Parser_Match(ctx, &pItem->ClueList1);
        TUnionSet_PushBack(p, pItem);
    }
    else if (token == TK_STRUCT ||
        token == TK_UNION)
    {
        Parser_Match(ctx, &pItem->ClueList0);

        PTR_STRING_REPLACE(pItem->Name, lexeme);
        Parser_MatchToken(ctx, TK_IDENTIFIER, &pItem->ClueList1);
        TUnionSet_PushBack(p, pItem);
    }
    else
    {
        SetError(ctx, "invalid token for union set");
    }
}

void UnionSetList(Parser * ctx, TUnionSet * p)
{
     
    Tokens token = Parser_CurrentToken(ctx);
    UnionSetItem(ctx, p);

    token = Parser_CurrentToken(ctx);
    if (token == TK_VERTICAL_LINE)
    {
        p->pTail->TokenFollow = token;
        Parser_Match(ctx, &p->pTail->ClueList2);
        UnionSetList(ctx, p);
    }
}

void UnionSet(Parser * ctx, TUnionSet * pUnionSet)
{
     

    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);


    if (token == TK_LESS_THAN_SIGN)
    {
        Parser_Match(ctx, &pUnionSet->ClueList0);


        UnionSetList(ctx, pUnionSet);

        Parser_MatchToken(ctx, TK_GREATER_THAN_SIGN,
            &pUnionSet->ClueList1);
    }


}

void Struct_Or_Union_Specifier(Parser * ctx,
    TStructUnionSpecifier * pStructUnionSpecifier)
{
     

     

    
    Struct_Or_Union(ctx, pStructUnionSpecifier);


    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);




    if (token == TK_LESS_THAN_SIGN)
    {
        UnionSet(ctx, &pStructUnionSpecifier->UnionSet);
        token = Parser_CurrentToken(ctx);
    }


    token = Parser_CurrentToken(ctx);
    lexeme = Lexeme(ctx);

    if (token == TK_IDENTIFIER)
    {
        
        PTR_STRING_REPLACE(pStructUnionSpecifier->TagName, lexeme);
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList1);
    }

    if (pStructUnionSpecifier->TagName != NULL)
    {
        SymbolMap_SetAt(ctx->pCurrentScope, pStructUnionSpecifier->TagName, (TTypePointer *)pStructUnionSpecifier);
    }

    token = Parser_CurrentToken(ctx);
    if (token == TK_LEFT_CURLY_BRACKET)
    {
        
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList2);

        Struct_Declaration_List(ctx,
            &pStructUnionSpecifier->StructDeclarationList);

        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pStructUnionSpecifier->ClueList3);
    }
    else
    {
        
        
    }
}

void Enumeration_Constant(Parser * ctx,
    TEnumerator * pEnumerator2)
{
    const char * lexeme = Lexeme(ctx);
    PTR_STRING_REPLACE(pEnumerator2->Name, lexeme);
    Parser_MatchToken(ctx, TK_IDENTIFIER, &pEnumerator2->ClueList0);
}

bool EnumeratorC(Parser * ctx, TEnumerator * pEnumerator2)
{
     
    bool bValueAssigned = false;
    Enumeration_Constant(ctx, pEnumerator2);


    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_EQUALS_SIGN)
    {
        Parser_Match(ctx, &pEnumerator2->ClueList1);
        ConstantExpression(ctx, &pEnumerator2->pExpression);
        bValueAssigned = true;
    }

    return bValueAssigned;
}

void Enumerator_List(Parser * ctx,
    TEnumeratorList * pEnumeratorList2)
{
    if (ErrorOrEof(ctx))
    {
        return;
    }

     

    TEnumerator * pEnumerator2 = TEnumerator_Create();
    List_Add(pEnumeratorList2, pEnumerator2);

    EnumeratorC(ctx, pEnumerator2);
    SymbolMap_SetAt(ctx->pCurrentScope, pEnumerator2->Name, (TTypePointer *)pEnumerator2);

    Tokens token = Parser_CurrentToken(ctx);

    
    if (token == TK_COMMA)
    {
        Parser_Match(ctx, &pEnumerator2->ClueList2);
        token = Parser_CurrentToken(ctx);
        pEnumerator2->bHasComma = true;

        if (token != TK_RIGHT_CURLY_BRACKET)
        {
            Enumerator_List(ctx, pEnumeratorList2);
        }
    }
}

void Enum_Specifier(Parser * ctx, TEnumSpecifier * pEnumSpecifier2)
{
     

    Parser_MatchToken(ctx, TK_ENUM, &pEnumSpecifier2->ClueList0);

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_IDENTIFIER)
    {
        const char * lexeme = Lexeme(ctx);
        PTR_STRING_REPLACE(pEnumSpecifier2->Name, lexeme);
        Parser_Match(ctx, &pEnumSpecifier2->ClueList1);


        SymbolMap_SetAt(ctx->pCurrentScope, pEnumSpecifier2->Name, (TTypePointer *)pEnumSpecifier2);
    }

    else
    {
        const char * name = GetName();
        PTR_STRING_REPLACE(pEnumSpecifier2->Name, name);
        Parser_Match(ctx, &pEnumSpecifier2->ClueList2);
    }


    if (token == TK_IDENTIFIER)
    {
        
        token = Parser_CurrentToken(ctx);

        if (token == TK_LEFT_CURLY_BRACKET)
        {
            Parser_Match(ctx, &pEnumSpecifier2->ClueList2);

            Enumerator_List(ctx, &pEnumSpecifier2->EnumeratorList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
                &pEnumSpecifier2->ClueList3);
        }

        else
        {
            
            
        }
    }
    else if (token == TK_LEFT_CURLY_BRACKET)
    {
        
        Enumerator_List(ctx, &pEnumSpecifier2->EnumeratorList);

        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pEnumSpecifier2->ClueList3);
    }

    else
    {
        SetError(ctx, "expected enum name or {");
    }
}

bool TFunctionSpecifier_IsFirst(Tokens token)
{
     
    bool bResult = false;

    switch (token)
    {
    case TK_INLINE:
    case TK__INLINE:
    case TK__FORCEINLINE:
    case TK__NORETURN:
        bResult = true;
        break;

    default:
        break;
    }

    return bResult;
}

void Function_Specifier(Parser * ctx,
    TFunctionSpecifier * pFunctionSpecifier)
{
     

    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK__INLINE:
    case TK__FORCEINLINE:
    case TK_INLINE:
    case TK__NORETURN:
        pFunctionSpecifier->Token = token;
        Parser_Match(ctx, &pFunctionSpecifier->ClueList0);
        break;

    default:
        break;
    }
}

bool TStorageSpecifier_IsFirst(Tokens token)
{
    bool bResult = false;
     
    switch (token)
    {
    case TK_TYPEDEF:
    case TK_EXTERN:
    case TK_STATIC:
    case TK__THREAD_LOCAL:
    case TK_AUTO:
    case TK_REGISTER:
        bResult = true;
        break;
    default:
        break;
    }

    return bResult;
}

void Storage_Class_Specifier(Parser * ctx,

    TStorageSpecifier * pStorageSpecifier)
{
     

    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_TYPEDEF:
    case TK_EXTERN:
    case TK_STATIC:
    case TK__THREAD_LOCAL:
    case TK_AUTO:
    case TK_REGISTER:
        pStorageSpecifier->Token = token;
        Parser_Match(ctx, &pStorageSpecifier->ClueList0);
        break;

    default:
        break;
    }
}

void Parameter_List(Parser * ctx,
    TParameterList * pParameterList)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    TParameter * pParameter = TParameter_Create();
    List_Add(pParameterList, pParameter);
    Parameter_Declaration(ctx, pParameter);

    
    token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {
        
        pParameter->bHasComma = true;
        Parser_Match(ctx, &pParameter->ClueList0);

        token = Parser_CurrentToken(ctx);
        if (token != TK_DOTDOTDOT)
        {
            Parameter_List(ctx, pParameterList);
        }
    }
}

void Parameter_Declaration(Parser * ctx,
    TParameter * pParameterDeclaration)
{

    

     
    Declaration_Specifiers(ctx,
        &pParameterDeclaration->Specifiers);

    TDeclarator * pDeclarator = NULL;
    Declarator(ctx, true, &pDeclarator);
    if (pDeclarator)
    {
        TDeclarator_Swap(&pParameterDeclaration->Declarator, pDeclarator);
        TDeclarator_Delete(pDeclarator);
    }
}

void Parameter_Type_List(Parser * ctx,
    TParameterTypeList * pParameterList)
{
     

    Parameter_List(ctx, &pParameterList->ParameterList);

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_DOTDOTDOT)
    {
        pParameterList->bVariadicArgs = true;
        
        Parser_Match(ctx, &pParameterList->ClueList1);
    }
}


void Direct_Declarator(Parser * ctx, bool bAbstract, TDirectDeclarator ** ppDeclarator2)
{
    *ppDeclarator2 = NULL; 

                            
    TDirectDeclarator * pDirectDeclarator = NULL;

    if (ErrorOrEof(ctx))
        return;


    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        
        pDirectDeclarator = TDirectDeclarator_Create();

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList0);

        Declarator(ctx, bAbstract, &pDirectDeclarator->pDeclarator);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList1);

        
        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeDeclarator;
        
    }
    break;

    case TK_IDENTIFIER:
    {
        
        pDirectDeclarator = TDirectDeclarator_Create();

        

        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeIdentifier;

        const char * lexeme = Lexeme(ctx);
        PTR_STRING_REPLACE(pDirectDeclarator->Identifier, lexeme);
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);
        Parser_Match(ctx, &pDirectDeclarator->ClueList0);
    }
    break;

    default:
        
        break;
    }



    if (pDirectDeclarator == NULL)
    {
        
        
        
        pDirectDeclarator = TDirectDeclarator_Create();
        PTR_STRING_REPLACE(pDirectDeclarator->Identifier, "");
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);

        

        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeIdentifier;

        
        
    }

    *ppDeclarator2 = pDirectDeclarator;

    for (;;)
    {
        

        token = Parser_CurrentToken(ctx);
        switch (token)
        {
        case TK_LEFT_PARENTHESIS:

             
            
            
            
            token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList2);

            

            pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeFunction;

            if (token != TK_RIGHT_PARENTHESIS)
            {
                
                Parameter_Type_List(ctx, &pDirectDeclarator->Parameters);
            }
            Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList3);
            break;

        case TK_LEFT_SQUARE_BRACKET:
             

            
            

            

            pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeArray;

            token = Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET, &pDirectDeclarator->ClueList2);
            if (token == TK_STATIC)
            {
            }
            else
            {
                if (token != TK_RIGHT_SQUARE_BRACKET)
                {
                    
                    AssignmentExpression(ctx, &pDirectDeclarator->pExpression);
                }
                else
                {
                    
                    
                }
            }

            Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, &pDirectDeclarator->ClueList3);

            break;
        default:
            
            break;
        }

        token = Parser_CurrentToken(ctx);
        if (token != TK_LEFT_PARENTHESIS && token != TK_LEFT_SQUARE_BRACKET)
        {
            break;
        }
        else
        {
            TDirectDeclarator * pDirectDeclaratorNext = TDirectDeclarator_Create();
            pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
            pDirectDeclarator = pDirectDeclaratorNext;
        }
    }

    token = Parser_CurrentToken(ctx);
    if (token == TK_LEFT_PARENTHESIS)
    {
        
        TDirectDeclarator * pDirectDeclaratorNext = NULL;
        Direct_Declarator(ctx, bAbstract, &pDirectDeclaratorNext);
        pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
    }
    else if (!bAbstract && token == TK_IDENTIFIER)
    {
        
        TDirectDeclarator * pDirectDeclaratorNext = NULL;
        Direct_Declarator(ctx, bAbstract, &pDirectDeclaratorNext);
        pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
    }


}

static bool TTypeQualifier_IsFirst(Tokens token)
{
    bool bResult = false;

    switch (token)
    {

    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:
        bResult = true;
        break;

#ifdef LANGUAGE_EXTENSIONS
        
    case TK_LEFT_SQUARE_BRACKET:
    case TK_AUTO:

        bResult = true;
        break;
#endif
    default:
        break;
    }

    return bResult;
}

#ifdef LANGUAGE_EXTENSIONS
void Size_Qualifier(Parser * ctx, TTypeQualifier * pQualifier)
{
    Tokens token = Parser_CurrentToken(ctx);
    pQualifier->Token = token;
    

    token = Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET, &pQualifier->ClueList0);

    switch (token)
    {
    case TK_IDENTIFIER:
        PTR_STRING_REPLACE(pQualifier->SizeIdentifier, Lexeme(ctx));
        token = Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
        break;
    default:
        break;
    }


    token = Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, NULL);

}
#endif


bool Type_Qualifier(Parser * ctx, TTypeQualifier * pQualifier)
{
     

    
     

    bool bResult = false;
    Tokens token = Parser_CurrentToken(ctx);

    
    switch (token)
    {

    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:
        pQualifier->Token = token;
        Parser_Match(ctx, &pQualifier->ClueList0);
        bResult = true;
        break;

#ifdef LANGUAGE_EXTENSIONS

    case TK_LEFT_SQUARE_BRACKET:

        Size_Qualifier(ctx, pQualifier);
        bResult = true;
        break;

    case TK_AUTO:


        pQualifier->Token = token;
        Parser_Match(ctx, &pQualifier->ClueList0);
        bResult = true;
        break;
#endif
    default:
        break;
    }

    return bResult;
}

void Type_Qualifier_List(Parser * ctx,
    TTypeQualifierList * pQualifiers)
{
     

    TTypeQualifier * pTypeQualifier = TTypeQualifier_Create();
    Type_Qualifier(ctx, pTypeQualifier);
    TTypeQualifierList_PushBack(pQualifiers, pTypeQualifier);

    if (IsTypeQualifierToken(Parser_CurrentToken(ctx)))
    {
        Type_Qualifier_List(ctx, pQualifiers);
    }

}


void Pointer(Parser * ctx, TPointerList * pPointerList)
{
     

    TPointer * pPointer = TPointer_Create();

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_ASTERISK)
    {
        
        TPointerList_PushBack(pPointerList, pPointer);
        Parser_Match(ctx, &pPointer->ClueList0);
    }
    else
    {
        
        SetError(ctx, "pointer error");
    }

    token = Parser_CurrentToken(ctx);


    
    if (IsTypeQualifierToken(token))
    {
        Type_Qualifier_List(ctx, &pPointer->Qualifier);
    }

    token = Parser_CurrentToken(ctx);

    
    if (token == TK_ASTERISK)
    {
        Pointer(ctx, pPointerList);
    }
}


void Declarator(Parser * ctx, bool bAbstract, TDeclarator ** ppTDeclarator2)
{
    
    *ppTDeclarator2 = NULL; 

    TDeclarator * pDeclarator = TDeclarator_Create();
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_ASTERISK)
    {
        Pointer(ctx, &pDeclarator->PointerList);
    }

    
    Direct_Declarator(ctx, bAbstract, &pDeclarator->pDirectDeclarator);

    *ppTDeclarator2 = pDeclarator;
}


bool TAlignmentSpecifier_IsFirst(Tokens token)
{
     
    return (token == TK__ALIGNAS);
}

bool Alignment_Specifier(Parser * ctx,
    TAlignmentSpecifier * pAlignmentSpecifier)
{
    bool bResult = false;
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__ALIGNAS)
    {
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);
        
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);
        bResult = true;
    }

    return bResult;
}


bool TTypeSpecifier_IsFirst(Parser * ctx, Tokens token, const char * lexeme)
{
     

    bool bResult = false;

    switch (token)
    {
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:
    case TK__ATOMIC:

    case TK_STRUCT:
    case TK_UNION:
    case TK_ENUM:
        bResult = true;
        break;

    case TK_IDENTIFIER:
        bResult = IsTypeName(ctx, TK_IDENTIFIER, lexeme);
        break;

    default:
        break;
    }

    return bResult;
}


void AtomicTypeSpecifier(Parser * ctx,
    TTypeSpecifier * *ppTypeSpecifier)
{
    
                    
    TAtomicTypeSpecifier * pAtomicTypeSpecifier =
        TAtomicTypeSpecifier_Create();

    *ppTypeSpecifier = TAtomicTypeSpecifier_As_TTypeSpecifier(pAtomicTypeSpecifier);

    Parser_MatchToken(ctx, TK__ATOMIC, &pAtomicTypeSpecifier->ClueList0);

    Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pAtomicTypeSpecifier->ClueList1);

    TypeName(ctx, &pAtomicTypeSpecifier->TypeName);

    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pAtomicTypeSpecifier->ClueList2);
}

void Type_Specifier(Parser * ctx, TTypeSpecifier * *ppTypeSpecifier)
{
     


    bool bResult = false;

    const char * lexeme = Lexeme(ctx);
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
        
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        
    case TK_FLOAT:
    case TK_DOUBLE:
    case TK_SIGNED:
    case TK_UNSIGNED:
    case TK__BOOL:
    case TK__COMPLEX:
    {
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            TSingleTypeSpecifier_Create();

        pSingleTypeSpecifier->Token2 = token;
        bResult = true;

        Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

        *ppTypeSpecifier = (TTypeSpecifier *)pSingleTypeSpecifier;
    }
    break;

    
    case TK__ATOMIC:
        bResult = true;
        AtomicTypeSpecifier(ctx, ppTypeSpecifier);
        break;

    case TK_STRUCT:
    case TK_UNION:
    {
        
        bResult = true;
        TStructUnionSpecifier * pStructUnionSpecifier = TStructUnionSpecifier_Create();

        *ppTypeSpecifier = (TTypeSpecifier *)pStructUnionSpecifier;
        Struct_Or_Union_Specifier(ctx, pStructUnionSpecifier);
    }
    break;

    case TK_ENUM:
    {
        
        bResult = true;
        TEnumSpecifier * pEnumSpecifier2 = TEnumSpecifier_Create();
        *ppTypeSpecifier = (TTypeSpecifier *)pEnumSpecifier2;
        Enum_Specifier(ctx, pEnumSpecifier2);
    }
    break;

    case TK_IDENTIFIER:
    {
        int bIsTypedef = IsTypeName(ctx, TK_IDENTIFIER, lexeme);
        if (bIsTypedef)
        {
            TSingleTypeSpecifier * pSingleTypeSpecifier = TSingleTypeSpecifier_Create();

            if (bIsTypedef == 2  )
                pSingleTypeSpecifier->Token2 = TK_STRUCT;
            else if (bIsTypedef == 3  )
                pSingleTypeSpecifier->Token2 = TK_UNION;
            else if (bIsTypedef == 4  )
                pSingleTypeSpecifier->Token2 = TK_ENUM;

            else
                pSingleTypeSpecifier->Token2 = token;

            PTR_STRING_REPLACE(pSingleTypeSpecifier->TypedefName, lexeme);
            bResult = true;

            Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);
            *ppTypeSpecifier = (TTypeSpecifier *)pSingleTypeSpecifier;

        }
        else
        {
            
            SetError(ctx, "internal error 2");
        }
    }
    break;

    default:
        break;
    }

    
    
    
    
    
}

bool Declaration_Specifiers_IsFirst(Parser * ctx, Tokens token, const char * lexeme)
{
     
    bool bResult =
        TStorageSpecifier_IsFirst(token) ||
        TTypeSpecifier_IsFirst(ctx, token, lexeme) ||
        TTypeQualifier_IsFirst(token) ||
        TFunctionSpecifier_IsFirst(token) ||
        TFunctionSpecifier_IsFirst(token);

    return bResult;
}

void Declaration_Specifiers(Parser * ctx,
    TDeclarationSpecifiers * pDeclarationSpecifiers)
{
     
    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);

    if (TStorageSpecifier_IsFirst(token))
    {
        TStorageSpecifier * pStorageSpecifier = TStorageSpecifier_Create();

        Storage_Class_Specifier(ctx, pStorageSpecifier);

        TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, TStorageSpecifier_As_TDeclarationSpecifier(pStorageSpecifier));
    }
    else if (TTypeSpecifier_IsFirst(ctx, token, lexeme))
    {
        if (TDeclarationSpecifiers_CanAddSpeficier(pDeclarationSpecifiers,
            token,
            lexeme))
        {
            TTypeSpecifier * pTypeSpecifier = NULL;
            Type_Specifier(ctx, &pTypeSpecifier);
            
            TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, (TDeclarationSpecifier *)pTypeSpecifier);
        }
        else
        {
            SetError(ctx, "double typedef");
        }

    }
    else if (TTypeQualifier_IsFirst(token))
    {
        TTypeQualifier * pTypeQualifier = TTypeQualifier_Create();
        Type_Qualifier(ctx, pTypeQualifier);
        
        TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, (TDeclarationSpecifier *)TTypeQualifier_As_TSpecifierQualifier(pTypeQualifier));
    }
    else if (TFunctionSpecifier_IsFirst(token))
    {
        TFunctionSpecifier * pFunctionSpecifier = TFunctionSpecifier_Create();
        Function_Specifier(ctx, pFunctionSpecifier);
        TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, TFunctionSpecifier_As_TDeclarationSpecifier(pFunctionSpecifier));
    }
    else if (TAlignmentSpecifier_IsFirst(token))
    {
        
        
        
    }
    else
    {
        SetError(ctx, "internal error 3");
    }

    token = Parser_CurrentToken(ctx);
    lexeme = Lexeme(ctx);

    
    if (Declaration_Specifiers_IsFirst(ctx, token, lexeme))
    {
        if (TDeclarationSpecifiers_CanAddSpeficier(pDeclarationSpecifiers,
            token,
            lexeme))
        {
            Declaration_Specifiers(ctx, pDeclarationSpecifiers);
        }

    }

}



void Initializer(Parser * ctx,
    TInitializer * *ppInitializer,
    Tokens endToken1,
    Tokens endToken2)
{
    
     

     

    Tokens token = Parser_CurrentToken(ctx);
    if (
        token == TK_DEFAULT)
    {
        TInitializerListType * pTInitializerList =
            TInitializerListType_Create();

        pTInitializerList->bDefault = true;

        *ppInitializer = (TInitializer *)pTInitializerList;

        Parser_Match(ctx, &pTInitializerList->ClueList0);
        token = Parser_CurrentToken(ctx);


        if (token == TK_LEFT_CURLY_BRACKET)
        {
            Parser_Match(ctx, &pTInitializerList->ClueList1);

            Initializer_List(ctx, &pTInitializerList->InitializerList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
                &pTInitializerList->ClueList2);
        }
    }
    else
    {
        if (token == TK_LEFT_CURLY_BRACKET)
        {

            TInitializerListType * pTInitializerList =
                TInitializerListType_Create();


            *ppInitializer = (TInitializer *)pTInitializerList;

            Parser_Match(ctx, &pTInitializerList->ClueList1);
            

            Initializer_List(ctx, &pTInitializerList->InitializerList);

            Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
                &pTInitializerList->ClueList2);
        }

        else
        {
            TExpression * pExpression = NULL;
            AssignmentExpression(ctx, &pExpression);
            *ppInitializer = (TInitializer *)pExpression;
        }
    }
}

void Initializer_List(Parser * ctx, TInitializerList * pInitializerList)
{
     
    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);
        if (token == TK_RIGHT_CURLY_BRACKET)
        {
            
            break;
        }

        TInitializerListItem * pTInitializerListItem = TInitializerListItem_Create();
        List_Add(pInitializerList, pTInitializerListItem);

#ifdef LANGUAGE_EXTENSIONS

#endif
        if (token == TK_LEFT_SQUARE_BRACKET ||
            token == TK_FULL_STOP)
        {
            Designation(ctx, &pTInitializerListItem->DesignatorList);
        }

        Initializer(ctx, &pTInitializerListItem->pInitializer, TK_COMMA, TK_RIGHT_CURLY_BRACKET);
        
        token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            
            Parser_Match(ctx, &pTInitializerListItem->ClueList);
            
        }

        else
        {
            break;
        }
    }
}

void Designation(Parser * ctx, TDesignatorList * pDesignatorList)
{
     
    Designator_List(ctx, pDesignatorList);
    Parser_MatchToken(ctx, TK_EQUALS_SIGN, NULL);
}

void Designator_List(Parser * ctx, TDesignatorList * pDesignatorList)
{
    
     
    TDesignator * pDesignator = TDesignator_Create();
    Designator(ctx, pDesignator);
    TDesignatorList_PushBack(pDesignatorList, pDesignator);

    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_LEFT_SQUARE_BRACKET ||
            token == TK_FULL_STOP)
        {
            TDesignator * pDesignatorNew = TDesignator_Create();
            Designator(ctx, pDesignatorNew);
            List_Add(pDesignatorList, pDesignatorNew);
        }

        else
        {
            break;
        }
    }
}

void Designator(Parser * ctx, TDesignator * p)
{
     
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_LEFT_SQUARE_BRACKET)
    {
        Parser_Match(ctx, &p->ClueList0);

        ConstantExpression(ctx, &p->pExpression);

        Parser_Match(ctx, &p->ClueList1);
        Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, NULL);
    }

    else if (token == TK_FULL_STOP)
    {
        
        Parser_Match(ctx, &p->ClueList0);

        PTR_STRING_REPLACE(p->Name, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
    }
}

void Init_Declarator(Parser * ctx,
    TInitDeclarator * *ppDeclarator2)
{
     
    TInitDeclarator * pInitDeclarator =
        TInitDeclarator_Create();

    Declarator(ctx, false, &pInitDeclarator->pDeclarator);
    Tokens token = Parser_CurrentToken(ctx);

    const char * declaratorName = TInitDeclarator_FindName(pInitDeclarator);
    if (declaratorName)
    {
        
        

        SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer *)pInitDeclarator);
    }

    
    *ppDeclarator2 = pInitDeclarator;

    if (token == TK_EQUALS_SIGN)
    {
        

        Parser_Match(ctx, &pInitDeclarator->ClueList0);

        Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
        
    }
}

void Init_Declarator_List(Parser * ctx,
    TInitDeclaratorList * pInitDeclaratorList)
{
     

    TInitDeclarator * pInitDeclarator = NULL;
    Init_Declarator(ctx, &pInitDeclarator);
    List_Add(pInitDeclaratorList, pInitDeclarator);

    
    Tokens token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {
        Parser_Match(ctx, &pInitDeclarator->ClueList0);

        Init_Declarator_List(ctx, pInitDeclaratorList);
    }

}

void Parse_Declarations(Parser * ctx, TDeclarations * declarations);

void GroupDeclaration(Parser * ctx,
    TGroupDeclaration * *ppGroupDeclaration)
{
     

    TGroupDeclaration * p = TGroupDeclaration_Create();
    *ppGroupDeclaration = p;

    Parser_Match(ctx, &p->ClueList0);


    PTR_STRING_REPLACE(p->Identifier, Lexeme(ctx));
    Parser_MatchToken(ctx, TK_IDENTIFIER, &p->ClueList1);

    Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &p->ClueList2);

    Tokens token = Parser_CurrentToken(ctx);
    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        Parse_Declarations(ctx, &p->Declarations);
    }
    else
    {
        
    }
    Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, NULL);
}

void PopBack(TScannerItemList * clueList)
{
    if (clueList->pHead &&
        clueList->pHead->pNext == clueList->pTail)
    {
        ScannerItem_Delete(clueList->pTail);
        clueList->pTail = clueList->pHead;
        clueList->pHead->pNext = 0;
    }
}
bool HasCommentedKeyword(TScannerItemList * clueList, const char * keyword)
{
    bool bResult = false;
    struct ScannerItem * pCurrent = clueList->pTail;
    if (pCurrent &&
        pCurrent->token == TK_COMMENT)
    {
        bResult = strncmp(pCurrent->lexeme.c_str + 2, keyword, strlen(keyword)) == 0;
    }
    return bResult;
}

static bool IsDefaultFunctionTag(const char * functionTag)
{
    if (functionTag)
    {
        if (strcmp(functionTag, "init") == 0 ||
            strcmp(functionTag, "delete") == 0 ||
            strcmp(functionTag, "destroy") == 0 ||
            strcmp(functionTag, "create") == 0)
        {
            return true;
        }
    }
    return false;    
}

bool  Declaration(Parser * ctx,
    TAnyDeclaration * *ppDeclaration)
{
     



    bool bHasDeclaration = false;
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__STATIC_ASSERT)
    {
        TStaticAssertDeclaration * pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
        *ppDeclaration = (TAnyDeclaration *)pStaticAssertDeclaration;
        Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
        bHasDeclaration = true;

    }
    else if (token == TK_DEFAULT)
    {
        TGroupDeclaration * p = NULL;
        GroupDeclaration(ctx, &p);
        *ppDeclaration = (TAnyDeclaration *)p;
        bHasDeclaration = true;
    }
    else
    {
        TDeclaration * pFuncVarDeclaration = TDeclaration_Create();

        if (token == TK_SEMICOLON)
        {
            
            bHasDeclaration = true;
            
        }
        else
        {
            if (Declaration_Specifiers_IsFirst(ctx, Parser_CurrentToken(ctx), Lexeme(ctx)))
            {
                Declaration_Specifiers(ctx, &pFuncVarDeclaration->Specifiers);
                bHasDeclaration = true;
            }
        }

        if (bHasDeclaration)
        {
            *ppDeclaration = (TAnyDeclaration *)pFuncVarDeclaration;
            pFuncVarDeclaration->FileIndex = GetFileIndex(ctx);
            pFuncVarDeclaration->Line = GetCurrentLine(ctx);
            

            token = Parser_CurrentToken(ctx);

            if (token == TK_SEMICOLON)
            {
                Parser_Match(ctx, &pFuncVarDeclaration->ClueList1);
            }

            else
            {
                
                


                
                
                
                
                
                

                struct SymbolMap BlockScope = SYMBOLMAP_INIT;

                BlockScope.pPrevious = ctx->pCurrentScope;
                ctx->pCurrentScope = &BlockScope;


                
                Init_Declarator_List(ctx, &pFuncVarDeclaration->InitDeclaratorList);


                ctx->pCurrentScope = BlockScope.pPrevious;
                SymbolMap_Destroy(&BlockScope);

                

                token = Parser_CurrentToken(ctx);

                
                
                ForEachListItem(TInitDeclarator, pInitDeclarator, &pFuncVarDeclaration->InitDeclaratorList)
                {
                    const char * declaratorName = TInitDeclarator_FindName(pInitDeclarator);



                    if (declaratorName != NULL)
                    {
                        SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer *)pFuncVarDeclaration);
                    }

                    
                }

                if (token == TK_COLON)
                {
                    Parser_Match(ctx, &pFuncVarDeclaration->ClueList00);
                    token = Parser_CurrentToken(ctx);

                    assert(pFuncVarDeclaration->FunctionTag == NULL);
                    pFuncVarDeclaration->FunctionTag = StrDup(Lexeme(ctx));

                    if (!IsDefaultFunctionTag(pFuncVarDeclaration->FunctionTag))
                    {
                        SetWarning(ctx, "Unknown tag '%s'", pFuncVarDeclaration->FunctionTag);
                    }

                    Parser_Match(ctx, &pFuncVarDeclaration->ClueList001);
                    token = Parser_CurrentToken(ctx);

                    SymbolMap_SetAt(ctx->pCurrentScope,
                        pFuncVarDeclaration->FunctionTag,
                        (TTypePointer *)pFuncVarDeclaration);
                }
                else if (!ctx->ParserOptions.bNoImplicitTag)
                {
                    const char * funcName = TDeclaration_GetFunctionName(pFuncVarDeclaration);
                    const char * functionTag = NULL;

                    
                    if (funcName && IsSuffix(funcName, "init"))
                    {
                        
                        functionTag = "init";
                    }
                    else if (funcName && IsSuffix(funcName, "destroy"))
                    {
                        
                        functionTag = "destroy";
                    }
                    else if (funcName && IsSuffix(funcName, "delete"))
                    {
                        
                        functionTag = "delete";
                    }
                    else if (funcName && IsSuffix(funcName, "create"))
                    {
                        
                        functionTag = "create";
                    }
                    else
                    {
                        
                    }
                    if (functionTag)
                    {
                        assert(pFuncVarDeclaration->FunctionTag == NULL);
                        pFuncVarDeclaration->FunctionTag = StrDup(functionTag);
                        pFuncVarDeclaration->bAutoTag = true;
                        SymbolMap_SetAt(ctx->pCurrentScope,
                            functionTag,
                            (TTypePointer *)pFuncVarDeclaration);
                    }
                  
                }

                
                if (token == TK_DEFAULT)
                {
                     

                    pFuncVarDeclaration->bDefault = true;
                    Parser_Match(ctx, &pFuncVarDeclaration->ClueList0);
                    token = Parser_CurrentToken(ctx);
                }

                if (token == TK_LEFT_CURLY_BRACKET)
                {

                    

                    
                    
                    struct SymbolMap BlockScope2 = SYMBOLMAP_INIT;

                    TInitDeclarator * pDeclarator3 =
                        pFuncVarDeclaration->InitDeclaratorList.pHead;

                    ForEachListItem(TParameter, pParameter, &pDeclarator3->pDeclarator->pDirectDeclarator->Parameters.ParameterList)
                    {
                        const char * parameterName = TDeclarator_GetName(&pParameter->Declarator);
                        if (parameterName != NULL)
                        {
                            SymbolMap_SetAt(&BlockScope2, parameterName, (TTypePointer *)pParameter);
                        }
                        else
                        {
                            
                        }
                    }

                    BlockScope2.pPrevious = ctx->pCurrentScope;
                    ctx->pCurrentScope = &BlockScope2;


                    
                     
                    TStatement * pStatement;
                    Compound_Statement(ctx, &pStatement);
                    

                    ctx->pCurrentScope = BlockScope2.pPrevious;
                    SymbolMap_Destroy(&BlockScope2);


                    pFuncVarDeclaration->pCompoundStatementOpt = (TCompoundStatement *)pStatement;
                }

                else
                {

                    
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pFuncVarDeclaration->ClueList1);
                }


            }

            
            


        }
        else
        {
            TDeclaration_Delete(pFuncVarDeclaration);
        }
    }


    return bHasDeclaration;
}


void Parse_Declarations(Parser * ctx, TDeclarations * declarations)
{
    int declarationIndex = 0;

    while (!ErrorOrEof(ctx))
    {

        TAnyDeclaration * pDeclarationOut = NULL;

        bool bHasDecl = Declaration(ctx, &pDeclarationOut);
        if (bHasDecl)
        {


            
            

            
            

            
            
            
            TDeclarations_PushBack(declarations, pDeclarationOut);


            declarationIndex++;
        }
        else
        {
            if (Parser_CurrentToken(ctx) == TK_EOF)
            {
                
                Parser_Match(ctx, NULL);
            }
            else
            {
                
                
            }
            break;
        }

        if (Parser_CurrentToken(ctx) == TK_EOF)
        {
            break;
        }

        if (Parser_HasError(ctx))
            break;
    }

    if (Parser_CurrentToken(ctx) == TK_EOF)
    {
        TEofDeclaration * pEofDeclaration =
            TEofDeclaration_Create();
        
        Parser_Match(ctx, &pEofDeclaration->ClueList0);
        TDeclarations_PushBack(declarations, (TAnyDeclaration *)pEofDeclaration);
    }


}

void Parser_Main(Parser * ctx, TDeclarations * declarations)
{
    Parse_Declarations(ctx, declarations);
}

static void TFileMapToStrArray(TFileMap * map, TFileArray * arr)
{
    TFileArray_Reserve(arr, map->Size);
    arr->Size = map->Size;

    for (int i = 0; i < map->buckets.size; i++)
    {
        Bucket * data = map->buckets.data[i];

        if (data != NULL)
        {
            for (int k = 0; k < data->size; k++)
            {
                struct BucketItem * node = data->data[k];
                TFile * pFile = (TFile *)node->data;

                if (pFile->FileIndex >= 0 &&
                    pFile->FileIndex < (int)arr->Size)
                {
                    arr->pItems[pFile->FileIndex] = pFile;
                    node->data = NULL; 
                }
            }
        }
    }
}

bool GetAST(const char * filename,
    const char * configFileName  ,
    struct Options * options,
    TProgram * pProgram)
{
    bool bResult = false;

    Parser parser;


    if (configFileName != NULL)
    {
        
        String * /*@auto*/ fullConfigFilePath = NULL;
        GetFullPath(configFileName, &fullConfigFilePath);

        Parser_InitFile(&parser, fullConfigFilePath);
        Parser_Main(&parser, &pProgram->Declarations);

        
        TDeclarations_Destroy(&pProgram->Declarations);
        TDeclarations_Init(&pProgram->Declarations);

        
        TScannerItemList_Clear(&parser.ClueList);
        BasicScannerStack_Pop(&parser.Scanner.stack);
        
        Free(fullConfigFilePath);
    }

    String * /*@auto*/ fullFileNamePath = NULL;
    GetFullPath(filename, &fullFileNamePath);

    parser.Scanner.pOptions = options; 

    
    parser.ParserOptions.bNoImplicitTag = options->bNoImplicitTag;

    if (filename != NULL)
    {
        if (configFileName == NULL)
        {
            Parser_InitFile(&parser, fullFileNamePath);
        }
        else
        {
            Parser_PushFile(&parser, fullFileNamePath);
        }
        Parser_Main(&parser, &pProgram->Declarations);
    }


    
    if (options->bAmalgamate)
    {
        struct FileNodeMap map = { 0 };

        
        FileNodeMap_Insert(&map, FileNode_Create(fullFileNamePath));


        for (;;)
        {


            struct FileNode * pSources = parser.Scanner.Sources.pHead;
            parser.Scanner.Sources.pHead = NULL;
            parser.Scanner.Sources.pTail = NULL;

            struct FileNode * pCurrent = pSources;
            while (pCurrent)
            {
                struct FileNode * pNext = pCurrent->pNext;
                if (FileNodeMap_Lookup(&map, pCurrent->Key) == 0)
                {
                    

                    
                    FileNodeMap_Insert(&map, pCurrent);

                    TScannerItemList_Destroy(&parser.ClueList);
                    TScannerItemList_Init(&parser.ClueList);

                    struct ScannerItem * pNew = ScannerItem_Create();
                    pNew->token = TK_PRE_INCLUDE;
                    LocalStrBuilder_Append(&pNew->lexeme, "source");
                    TScannerItemList_PushBack(&parser.ClueList, pNew);


                    Parser_PushFile(&parser, pCurrent->Key);

                    printf("source %s\n", pCurrent->Key);


                    Parser_Main(&parser, &pProgram->Declarations);
                }
                else
                {
                    FileNode_Free(pCurrent); 
                }

                pCurrent = pNext;
            }
            if (parser.Scanner.Sources.pHead == NULL)
                break;
        }
        FileNodeMap_Destroy(&map);
    }


    TFileMapToStrArray(&parser.Scanner.FilesIncluded, &pProgram->Files2);
    printf("%s\n", GetCompletationMessage(&parser));
    SymbolMap_Swap(&parser.GlobalScope, &pProgram->GlobalScope);

    if (Parser_HasError(&parser))
    {
        Scanner_PrintDebug(&parser.Scanner);
    }

    MacroMap_Swap(&parser.Scanner.Defines2, &pProgram->Defines);

    bResult = !Parser_HasError(&parser);

    Parser_Destroy(&parser);
    Free(fullFileNamePath);

    return bResult;
}



bool GetASTFromString(const char * sourceCode,
    struct Options * options,
    TProgram * pProgram)
{
    bool bResult = false;

    Parser parser;

    Parser_InitString(&parser, "source", sourceCode);

    parser.ParserOptions.bNoImplicitTag = options->bNoImplicitTag;

    Parser_Main(&parser, &pProgram->Declarations);


    TFileMapToStrArray(&parser.Scanner.FilesIncluded, &pProgram->Files2);
    printf("%s\n", GetCompletationMessage(&parser));
    SymbolMap_Swap(&parser.GlobalScope, &pProgram->GlobalScope);

    if (Parser_HasError(&parser))
    {
        Scanner_PrintDebug(&parser.Scanner);
    }

    MacroMap_Swap(&parser.Scanner.Defines2, &pProgram->Defines);

    bResult = !Parser_HasError(&parser);

    Parser_Destroy(&parser);

    return bResult;
}













void IntegerStack_Init(struct IntegerStack * pItems) /*@default*/
{
    pItems->pData = NULL;
    pItems->Size = 0;
    pItems->Capacity = 0;
}

void IntegerStack_PushBack(struct IntegerStack * pItems, int i) /*@default*/
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        int* pnew = pItems->pData;
        pnew = (int*)Realloc(pnew, n * sizeof(int));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
    pItems->pData[pItems->Size] = i;
    pItems->Size++;
}

void IntegerStack_Pop(struct IntegerStack * pItems)
{
    if (pItems->Size > 0)
        pItems->Size--;
    
      
}



void IntegerStack_Destroy(struct IntegerStack * pItems) /*@default*/
{
    Free((void*)pItems->pData);
}

static int global_lambda_counter = 0;
static const char * GetReallocStr(TProgram * program);

void PrintCodeOptions_Destroy(PrintCodeOptions * options) /*@default*/
{
    Options_Destroy(&options->Options);
    IntegerStack_Destroy(&options->Stack);
}


void TSpecifierQualifierList_CodePrint(TProgram * program, PrintCodeOptions * options, TSpecifierQualifierList * pDeclarationSpecifiers, StrBuilder * fp);

void TTypeName_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeName * p, StrBuilder * fp);

static void TInitializer_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitializer * pTInitializer,

    StrBuilder * fp);

static void TInitializerList_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TDeclarator * pDeclarator,
    TInitializerList * p,

    StrBuilder * fp);


static void TInitializerListItem_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitializerListItem * p,

    StrBuilder * fp);


static void TTypeQualifierList_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeQualifierList * p, StrBuilder * fp);

static void TAnyDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TAnyDeclaration * pDeclaration, StrBuilder * fp);

static void TAnyStructDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TAnyStructDeclaration * p, StrBuilder * fp);
static void TTypeQualifier_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeQualifier * p, StrBuilder * fp);
static void TDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclaration * p, StrBuilder * fp);
static void TExpression_CodePrint(TProgram * program, PrintCodeOptions * options, TExpression * p, const char * name, StrBuilder * fp);
static void TStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TStatement * p, StrBuilder * fp);
static void TBlockItem_CodePrint(TProgram * program, PrintCodeOptions * options, TBlockItem * p, StrBuilder * fp);

static void TPointer_CodePrint(TProgram * program, PrintCodeOptions * options, TPointer * pPointer, StrBuilder * fp);
static void TParameter_CodePrint(TProgram * program, PrintCodeOptions * options, TParameter * p, StrBuilder * fp);

void Output_Append(StrBuilder * p,
    PrintCodeOptions * options,
    const char * source)
{
    if (options->bInclude)
    {
        if (options->Stack.Size == 0 ||
            options->Stack.pData[options->Stack.Size - 1] == 1)
        {
            StrBuilder_Append(p, source);
        }
    }
    else
    {
        
    }
}

static void TNodeClueList_CodePrint(PrintCodeOptions * options, TScannerItemList * list,
    StrBuilder * fp)
{
    if (options->Options.bCannonical)
    {
        
        
        
        return;
    };

    ForEachListItem(struct ScannerItem, pNodeClue, list)
    {
        switch (pNodeClue->token)
        {
        case TK_PRE_INCLUDE:
        {
            bool bIncludeFile = true;

            if (options->Stack.Size > 0 &&
                options->Stack.pData[options->Stack.Size - 1] == 0)
            {
                bIncludeFile = false;
            }
            else
            {
                if (options->Options.bAmalgamate)
                {
                    if (strstr(pNodeClue->lexeme.c_str, "<") != NULL)
                    {
                        bIncludeFile = false;
                    }
                }
                else
                {
                    bIncludeFile = false;
                }
            }


            if (bIncludeFile)
            {
                IntegerStack_PushBack(&options->Stack, bIncludeFile);
            }
            else
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                Output_Append(fp, options, "\n");
                IntegerStack_PushBack(&options->Stack, bIncludeFile);
            }

        }
        break;

        case TK_FILE_EOF:
            IntegerStack_Pop(&options->Stack);
            
            
            
            if (options->Options.bAmalgamate)
            {
                Output_Append(fp, options, "\n");
            }

            break;
        case TK_PRE_DEFINE:
            
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            break;

        case TK_PRE_PRAGMA:
            if (options->Options.bAmalgamate)
            {
                
            }
            else
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                Output_Append(fp, options, "\n");
            }

            break;
        case TK_PRE_UNDEF:

        case TK_PRE_IF:
        case TK_PRE_ENDIF:
        case TK_PRE_ELSE:
        case TK_PRE_IFDEF:
        case TK_PRE_IFNDEF:
        case TK_PRE_ELIF:
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            break;

        case TK_OPEN_COMMENT:
        case TK_CLOSE_COMMENT:
            
            break;

        case TK_COMMENT:
            if (options->Options.bIncludeComments)
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
            }
            else
            {
                Output_Append(fp, options, " ");
            }

            break;

        case TK_LINE_COMMENT:
            if (options->Options.bIncludeComments)
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
            }
            else
            {
                
            }
            break;

        case TK_BREAKLINE:
            Output_Append(fp, options, "\n");

            break;

        case TK_MACRO_CALL:
            if (options->Options.bExpandMacros)
            {

            }
            else
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                options->bInclude = false;
            }
            break;


        case TK_MACRO_EOF:
            if (options->Options.bExpandMacros)
            {

            }
            else
            {
                options->bInclude = true;
            }


            break;

        case TK_SPACES:
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            break;

            
        default:
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            break;
        }
    }

}

static void TCompoundStatement_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TCompoundStatement * p,

    StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "{");

    for (int j = 0; j < p->BlockItemList.Size; j++)
    {
        TBlockItem * pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_CodePrint(program, options, pBlockItem, fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "}");

}


static void TLabeledStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TLabeledStatement * p, StrBuilder * fp)
{


    if (p->token == TK_CASE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "case");
        if (p->pExpression)
        {
            TExpression_CodePrint(program, options, p->pExpression, "", fp);
        }
        else
        {
            
        }
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");

        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }
    else if (p->token == TK_DEFAULT)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "default");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");
        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }
    else if (p->token == TK_IDENTIFIER)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, p->Identifier);

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");

        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }



}

static void TForStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TForStatement * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "for");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");

    if (p->pInitDeclarationOpt)
    {
        TAnyDeclaration_CodePrint(program, options, p->pInitDeclarationOpt, fp);
        if (p->pExpression2)
        {
            TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
        }
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
    }
    else
    {
        TExpression_CodePrint(program, options, p->pExpression1, "expr1", fp);
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ")");

    TStatement_CodePrint(program, options, p->pStatement, fp);


}


static void TWhileStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TWhileStatement * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "while");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");
    TStatement_CodePrint(program, options, p->pStatement, fp);

}



static void TDoStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TDoStatement * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "do");

    TStatement_CodePrint(program, options, p->pStatement, fp);

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "while");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, options, ")");
    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ";");


}


static void TExpressionStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TExpressionStatement * p, StrBuilder * fp)
{
    TExpression_CodePrint(program, options, p->pExpression, "", fp);

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, ";");


}


static void TJumpStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TJumpStatement * p, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    switch (p->token)
    {
    case TK_GOTO:
        Output_Append(fp, options, "goto");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, p->Identifier);
        break;
    case  TK_CONTINUE:
        Output_Append(fp, options, "continue");
        break;
    case TK_BREAK:
        Output_Append(fp, options, "break");
        break;
    case TK_RETURN:
        Output_Append(fp, options, "return");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        TExpression_CodePrint(program, options, p->pExpression, "", fp);
        break;

    default:
        
        break;
    }


    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ";");


}

static void TAsmStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TAsmStatement * p, StrBuilder * fp)
{
    Output_Append(fp, options, "\"type\":\"asm-statement\"");

}

static void TSwitchStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TSwitchStatement * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "switch");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");

    TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");

    TStatement_CodePrint(program, options, p->pExpression, fp);

}


static void TIfStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TIfStatement * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "if");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");


    TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");

    if (p->pStatement->Type != TCompoundStatement_ID)
        Output_Append(fp, options, "");

    if (p->pStatement)
    {
        TStatement_CodePrint(program, options, p->pStatement, fp);
    }

    if (p->pElseStatement)
    {
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "else");
        TStatement_CodePrint(program, options, p->pElseStatement, fp);
    }


}

static void TStatement_CodePrint(TProgram * program, PrintCodeOptions * options, TStatement * p, StrBuilder * fp)
{
    if (p == NULL)
    {
        return;
    }

    switch (p->Type)
    {
    case TExpressionStatement_ID:
        TExpressionStatement_CodePrint(program, options, (TExpressionStatement *)p, fp);
        break;

    case TSwitchStatement_ID:
        TSwitchStatement_CodePrint(program, options, (TSwitchStatement *)p, fp);
        break;

    case TLabeledStatement_ID:
        TLabeledStatement_CodePrint(program, options, (TLabeledStatement *)p, fp);
        break;

    case TForStatement_ID:
        TForStatement_CodePrint(program, options, (TForStatement *)p, fp);
        break;

    case TJumpStatement_ID:
        TJumpStatement_CodePrint(program, options, (TJumpStatement *)p, fp);
        break;

    case TAsmStatement_ID:
        TAsmStatement_CodePrint(program, options, (TAsmStatement *)p, fp);
        break;

    case TCompoundStatement_ID:
        TCompoundStatement_CodePrint(program, options, (TCompoundStatement *)p, fp);
        break;

    case TIfStatement_ID:
        TIfStatement_CodePrint(program, options, (TIfStatement *)p, fp);
        break;

    case TDoStatement_ID:
        TDoStatement_CodePrint(program, options, (TDoStatement *)p, fp);
        break;

    default:
        
        break;
    }


}

static void TBlockItem_CodePrint(TProgram * program, PrintCodeOptions * options, TBlockItem * p, StrBuilder * fp)
{
    if (p == NULL)
    {
        
        return;
    }


    switch (p->Type)
    {
    case TEofDeclaration_ID:
        break;

    case TStaticAssertDeclaration_ID:
        break;

    case TSwitchStatement_ID:

        TSwitchStatement_CodePrint(program, options, (TSwitchStatement *)p, fp);

        break;

    case TJumpStatement_ID:

        TJumpStatement_CodePrint(program, options, (TJumpStatement *)p, fp);

        break;

    case TForStatement_ID:

        TForStatement_CodePrint(program, options, (TForStatement *)p, fp);

        break;

    case TIfStatement_ID:

        TIfStatement_CodePrint(program, options, (TIfStatement *)p, fp);

        break;

    case TWhileStatement_ID:

        TWhileStatement_CodePrint(program, options, (TWhileStatement *)p, fp);

        break;

    case TDoStatement_ID:

        TDoStatement_CodePrint(program, options, (TDoStatement *)p, fp);

        break;

    case TDeclaration_ID:
        TDeclaration_CodePrint(program, options, (TDeclaration *)p, fp);
        
        break;

    case TLabeledStatement_ID:

        TLabeledStatement_CodePrint(program, options, (TLabeledStatement *)p, fp);

        break;

    case TCompoundStatement_ID:
        TCompoundStatement_CodePrint(program, options, (TCompoundStatement *)p, fp);
        break;

    case TExpressionStatement_ID:

        TExpressionStatement_CodePrint(program, options, (TExpressionStatement *)p, fp);

        break;


    case TAsmStatement_ID:

        TAsmStatement_CodePrint(program, options, (TAsmStatement *)p, fp);

        break;

    default:
        
        break;
    }


}



bool GetType(const char * source,
    StrBuilder * strBuilderType)
{

    while (*source &&
        *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        source++;
    }


    return *source == '_';
}


bool GetTypeAndFunction(const char * source,
    StrBuilder * strBuilderType,
    StrBuilder * strBuilderFunc)
{

    while (*source &&
        *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        source++;
    }

    while (*source)
    {
        StrBuilder_AppendChar(strBuilderFunc, *source);
        source++;
    }

    return *source == '_';
}

static void TParameterTypeList_CodePrint(TProgram * program, PrintCodeOptions * options, TParameterTypeList * p, StrBuilder * fp);


static void TPrimaryExpressionLambda_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TPrimaryExpressionLambda * p,
    StrBuilder * fp)
{

    
    StrBuilder_AppendFmt(fp, "_lambda_%d", global_lambda_counter);

    StrBuilder sb = STRBUILDER_INIT;

    if (p->pParameterTypeListOpt)
    {
        


        Output_Append(&sb, options, "\n");
        StrBuilder_AppendFmt(&sb, "static void _lambda_%d(", global_lambda_counter);
        

        TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, &sb);

        
        Output_Append(&sb, options, ")");

    }
    global_lambda_counter++;
    TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, &sb);

    Output_Append(&program->sbPreDeclaration, options, "\n");

    StrBuilder_Append(&program->sbPreDeclaration, sb.c_str);




    StrBuilder_Destroy(&sb);

#if NORMAL 
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "[");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "]");

    if (p->pParameterTypeListOpt)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "(");

        TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, fp);

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, ")");

    }

    TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, fp);
#endif

}

static void TPostfixExpressionCore_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TPostfixExpressionCore * p,

    StrBuilder * fp)
{


    bool bIsPointer = false;

    if (p->pExpressionLeft)
    {
        TExpression_CodePrint(program, options, p->pExpressionLeft, "l", fp);
    }


    {
        if (p->pTypeName)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "(");
            TTypeName_CodePrint(program, options, p->pTypeName, fp);
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, ")");

            
            bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

            
            
            TInitializerList_CodePrint(program,
                options,
                (TDeclarationSpecifiers *)& p->pTypeName->SpecifierQualifierList,
                NULL,
                &p->InitializerList,

                fp);
        }

    }

    switch (p->token)
    {
    case TK_FULL_STOP:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ".");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, p->Identifier);

        break;
    case TK_ARROW:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "->");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, p->Identifier);

        break;

    case TK_LEFT_SQUARE_BRACKET:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "[");
        TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "]");
        break;

    case TK_LEFT_PARENTHESIS:
        
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "(");
        TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ")");
        break;

    case TK_PLUSPLUS:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "++");

        break;
    case TK_MINUSMINUS:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "--");

        break;


    default:
        
        break;
    }



    if (p->pNext)
    {
        TPostfixExpressionCore_CodePrint(program, options, p->pNext, fp);
    }



}

static void TExpression_CodePrint(TProgram * program, PrintCodeOptions * options, TExpression * p,
    const char * name,

    StrBuilder * fp)
{
    if (p == NULL)
    {
        
        return;
    }



    switch (p->Type)
    {
        CASE(TBinaryExpression) :
        {
            TBinaryExpression * pBinaryExpression = (TBinaryExpression *)p;

            TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList0, fp);
            Output_Append(fp, options, TokenToString(pBinaryExpression->token));

            TExpression_CodePrint(program, options, ((TBinaryExpression *)p)->pExpressionRight, "r-expr", fp);
        }
        break;

        CASE(TTernaryExpression) :
        {
            TTernaryExpression * pTernaryExpression =
                (TTernaryExpression *)p;


            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList0, fp);
            Output_Append(fp, options, "?");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionMiddle, "m-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList1, fp);
            Output_Append(fp, options, ":");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionRight, "r-expr", fp);
        }
        break;

        CASE(TPrimaryExpressionLiteral) :
        {
            TPrimaryExpressionLiteral * pPrimaryExpressionLiteral
                = (TPrimaryExpressionLiteral *)p;

            ForEachListItem(TPrimaryExpressionLiteralItem, pItem, &pPrimaryExpressionLiteral->List)
            {
                TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
                Output_Append(fp, options, pItem->lexeme);
            }
        }
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue * pPrimaryExpressionValue =
                (TPrimaryExpressionValue *)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, options, "(");
                TExpression_CodePrint(program, options, pPrimaryExpressionValue->pExpressionOpt, "expr", fp);

                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList1, fp);
                Output_Append(fp, options, ")");
            }
            else
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, options, pPrimaryExpressionValue->lexeme);
            }
        }
        

        break;

        CASE(TPrimaryExpressionLambda) :
        {
            TPrimaryExpressionLambda * pPostfixExpressionCore =
                (TPrimaryExpressionLambda *)p;
            TPrimaryExpressionLambda_CodePrint(program, options, pPostfixExpressionCore, fp);
        }
        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore * pPostfixExpressionCore =
                (TPostfixExpressionCore *)p;
            TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator * pTUnaryExpressionOperator =
                (TUnaryExpressionOperator *)p;

            TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList0, fp);

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
                {
                    Output_Append(fp, options, "sizeof");
                    TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList1, fp);

                    Output_Append(fp, options, "(");
                    TTypeName_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName, fp);

                    TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList2, fp);
                    Output_Append(fp, options, ")");
                }
                else
                {
                    Output_Append(fp, options, "sizeof");
                    TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
                    Output_Append(fp, options, "");
                }
            }
            else
            {
                Output_Append(fp, options, TokenToString(((TBinaryExpression *)p)->token));
                TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
            }
        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType *)p;
            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
            Output_Append(fp, options, "(");

            TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, fp);


            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
            Output_Append(fp, options, ")");

            TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", fp);
        }
        break;

    default:

        
        break;
    }



}



static   void TEnumerator_CodePrint(TProgram * program, PrintCodeOptions * options, TEnumerator * pTEnumerator, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &pTEnumerator->ClueList0, fp);
    Output_Append(fp, options, pTEnumerator->Name);

    if (pTEnumerator->pExpression)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList1, fp);
        Output_Append(fp, options, "=");

        TExpression_CodePrint(program, options, pTEnumerator->pExpression, "expr", fp);


    }
    else
    {
        
    }

    if (pTEnumerator->bHasComma)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList2, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEnumSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TEnumSpecifier * p, StrBuilder * fp)
{
    

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "enum");

    if (options->Options.bCannonical)
    {
        Output_Append(fp, options, " ");
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Name);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    if (p->EnumeratorList.pHead != NULL)
    {
        Output_Append(fp, options, "{");

        ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
        {
            TEnumerator_CodePrint(program, options, pTEnumerator, fp);
        }

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "}");
    }


}

static void TUnionSetItem_CodePrint(TProgram * program, PrintCodeOptions * options, TUnionSetItem * p, StrBuilder * fp)
{
    if (p->Token == TK_STRUCT)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "struct");
    }
    else if (p->Token == TK_UNION)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "union");
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Name);

    if (p->TokenFollow == TK_VERTICAL_LINE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "|");
    }
}

static void TUnionSet_CodePrint(TProgram * program, PrintCodeOptions * options, TUnionSet * p, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (options->Options.Target == CompilerTarget_Annotated)
    {
        Output_Append(fp, options, "/*@");
    }

    Output_Append(fp, options, "<");

    TUnionSetItem * pCurrent = p->pHead;
    while (pCurrent)
    {
        TUnionSetItem_CodePrint(program, options, pCurrent, fp);
        pCurrent = pCurrent->pNext;
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, ">");

    if (options->Options.Target == CompilerTarget_Annotated)
    {
        Output_Append(fp, options, "*/");
    }

}

static void TStructUnionSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TStructUnionSpecifier * p, StrBuilder * fp)
{
    if (options->Options.bCannonical)
    {
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    }

    

    if (p->StructDeclarationList.Size > 0)
    {
        if (p->Token == TK_STRUCT)
        {
            Output_Append(fp, options, "struct");
        }
        else if (p->Token == TK_UNION)
        {
            Output_Append(fp, options, "union");
        }

        if (options->Options.bCannonical)
        {
            Output_Append(fp, options, " ");
        }

        if (p->UnionSet.pHead != NULL)
        {
            TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
        }

        

    }
    else
    {
        if (p->Token == TK_STRUCT)
        {
            Output_Append(fp, options, "struct");
        }
        else if (p->Token == TK_UNION)
        {
            Output_Append(fp, options, "union");
        }

        if (options->Options.bCannonical)
        {
            Output_Append(fp, options, " ");
        }

        if (p->UnionSet.pHead != NULL)
        {
            TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
        }
    }

    if (options->Options.bCannonical)
    {
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    }

    Output_Append(fp, options, p->TagName);


    if (p->StructDeclarationList.Size > 0)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);

        Output_Append(fp, options, "{");

        for (int i = 0; i < p->StructDeclarationList.Size; i++)
        {
            TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
            TAnyStructDeclaration_CodePrint(program, options, pStructDeclaration, fp);
        }

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "}");
    }

}

static void TSingleTypeSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TSingleTypeSpecifier * p, StrBuilder * fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    

     
    if (p->Token2 == TK_IDENTIFIER)
    {
        Output_Append(fp, options, p->TypedefName);
    }
    else
    {
        Output_Append(fp, options,
            TokenToString(p->Token2));
    }



}

static void TDesignator_CodePrint(TProgram * program, PrintCodeOptions * options, TDesignator * p, StrBuilder * fp)
{
    
    


    
    if (p->Name)
    {
        
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ".");
        Output_Append(fp, options, p->Name);
        Output_Append(fp, options, "=");
        TExpression_CodePrint(program, options, p->pExpression, "index", fp);
    }
    else
    {
        
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        TExpression_CodePrint(program, options, p->pExpression, "index", fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    }



}

#define List_HasOneItem(pList) \
 ((pList)->pHead != NULL && (pList)->pHead == (pList)->pTail)

#define List_Back(pList) \
  ((pList)->pTail)

static void TInitializerList_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarationSpecifiers * pDeclarationSpecifiers, 
    TDeclarator * pDeclatator,                        
    TInitializerList * p,

    StrBuilder * fp)
{
    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL )
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            
        }
        
        StrBuilder sb = STRBUILDER_INIT;
        bool bHasInitializers = false;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(pDeclarationSpecifiers),
            pDeclatator,                        
            NULL,
            NULL, 
            "",
            NULL  ,
            ActionStaticInit,
            SearchNone,
            &bHasInitializers,
            &sb);
        if (bHasInitializers)
        {
            Output_Append(fp, options, sb.c_str);
        }
        else
        {
            Output_Append(fp, options, "{0}");
        }

        StrBuilder_Destroy(&sb);
    }
    else
    {

        ForEachListItem(TInitializerListItem, pItem, p)
        {
            if (!List_IsFirstItem(p, pItem))
                Output_Append(fp, options, ",");

            TInitializerListItem_CodePrint(program,
                options,
                pDeclatator,
                pDeclarationSpecifiers,
                pItem,
                fp);
        }

    }
}

static void TInitializerListType_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitializerListType * p,
    StrBuilder * fp)
{

     
    if (p->bDefault || p->InitializerList.pHead == NULL)
    {
        
        TInitializer * pInitializer = NULL;
        
        


        if (options->Options.Target == CompilerTarget_CXX)
        {
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, "{");

            TNodeClueList_CodePrint(options, &p->ClueList2, fp);
            Output_Append(fp, options, "}");
        }
        else  if (options->Options.Target == CompilerTarget_Annotated)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                Output_Append(fp, options, "/*@");
            }


            Output_Append(fp, options, "default");


            if (options->Options.Target == CompilerTarget_Annotated)
            {
                Output_Append(fp, options, "*/");
            }

            TNodeClueList_CodePrint(options, &p->ClueList1, fp);

            if (p->InitializerList.pHead)
                TNodeClueList_CodePrint(options, &p->InitializerList.pHead->ClueList, fp);

            StrBuilder sb = STRBUILDER_INIT;
            bool bHasInitializers = false;
            InstanciateDestroy2(program,
                options,
                (TSpecifierQualifierList *)(pDeclarationSpecifiers),
                pDeclarator,                        
                pInitializer,
                NULL, 
                "",
                NULL  ,
                ActionStaticInit,
                SearchNone,
                &bHasInitializers,
                &sb);

            if (bHasInitializers)
            {
                Output_Append(fp, options, sb.c_str);
            }
            else
            {
                Output_Append(fp, options, "{0}");
            }

            StrBuilder_Destroy(&sb);
        }

    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "{");

        TInitializerList_CodePrint(program,
            options,
            pDeclarationSpecifiers,
            pDeclarator,
            &p->InitializerList,

            fp);

        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "}");
    }


}


static void TInitializer_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitializer * pTInitializer,

    StrBuilder * fp)
{
    if (pTInitializer == NULL)
    {
        return;
    }
    if (pTInitializer->Type == TInitializerListType_ID)
    {
        TInitializerListType_CodePrint(program,
            options,
            pDeclarator,
            pDeclarationSpecifiers,
            (TInitializerListType *)pTInitializer, fp);
    }
    else
    {
        TExpression_CodePrint(program, options, (TExpression *)pTInitializer, "", fp);
    }


}



static void TPointerList_CodePrint(TProgram * program, PrintCodeOptions * options, TPointerList * p, StrBuilder * fp)
{
    ForEachListItem(TPointer, pItem, p)
    {
        TPointer_CodePrint(program, options, pItem, fp);
    }
}

static void TParameterList_CodePrint(TProgram * program, PrintCodeOptions * options, TParameterList * p, StrBuilder * fp)
{



    ForEachListItem(TParameter, pItem, p)
    {
        
        
        
        
        
        
        TParameter_CodePrint(program, options, pItem, fp);
    }



}

static void TParameterTypeList_CodePrint(TProgram * program, PrintCodeOptions * options, TParameterTypeList * p, StrBuilder * fp)
{
    
    TParameterList_CodePrint(program, options, &p->ParameterList, fp);

    if (p->bVariadicArgs)
    {
        
        

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "...");
    }
    

}
static void TDeclarator_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarator * p, bool bPrintName, StrBuilder * fp);

static void TDirectDeclarator_CodePrint(TProgram * program, PrintCodeOptions * options, TDirectDeclarator * pDirectDeclarator,

    bool bPrintName,
    StrBuilder * fp)
{
    if (pDirectDeclarator == NULL)
    {
        return;
    }
    


    if (pDirectDeclarator->Identifier)
    {
        
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        if (bPrintName)
        {
            Output_Append(fp, options, pDirectDeclarator->Identifier);
        }
        
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        Output_Append(fp, options, "(");

        TDeclarator_CodePrint(program, options, pDirectDeclarator->pDeclarator, bPrintName, fp);

        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList1, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeArray)
    {
         
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, options, "[");
        if (pDirectDeclarator->pExpression)
        {
            TExpression_CodePrint(program, options, pDirectDeclarator->pExpression, "assignment-expression", fp);
        }
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, options, "]");
    }


    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, options, "(");
        TParameterTypeList_CodePrint(program, options, &pDirectDeclarator->Parameters, fp);
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        
        TDirectDeclarator_CodePrint(program, options, pDirectDeclarator->pDirectDeclarator, bPrintName, fp);
    }


    

}

static void TDeclarator_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarator * p, bool bPrintName, StrBuilder * fp)
{
    TPointerList_CodePrint(program, options, &p->PointerList, fp);
    TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}








void TStructDeclarator_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TStructDeclarator * p,
    StrBuilder * fp)
{

    TDeclarator_CodePrint(program, options, p->pDeclarator, true , fp);
    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }

        Output_Append(fp, options, "=");

        PrintCodeOptions options2 = *options;
        options2.Options.bExpandMacros = true;
        options2.Options.bIncludeComments = false;


        TInitializer_CodePrint(program,
            &options2,
            p->pDeclarator,
            (TDeclarationSpecifiers *)pSpecifierQualifierList,
            p->pInitializer,
            fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }

    }

}

static void TStructDeclaratorList_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TStructDeclaratorList * p,
    StrBuilder * fp)
{




    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
            Output_Append(fp, options, ",");
        }
        TStructDeclarator_CodePrint(program, options, pSpecifierQualifierList, pItem, fp);
    }



}

static void TStructDeclaration_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TStructDeclaration * p,
    StrBuilder * fp)
{
    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);
    TStructDeclaratorList_CodePrint(program,
        options,
        &p->SpecifierQualifierList,
        &p->DeclaratorList, fp);


    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, ";");


}

static void TAnyStructDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TAnyStructDeclaration * p, StrBuilder * fp)
{
    switch (p->Type)
    {
    case TStructDeclaration_ID:
        TStructDeclaration_CodePrint(program, options, (TStructDeclaration *)p, fp);
        break;

    default:
        
        break;
    }


}

static void StorageSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TStorageSpecifier * p, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, TokenToString(p->Token));
}

static void TFunctionSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TFunctionSpecifier * p, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, TokenToString(p->Token));
}


static void TTypeQualifier_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeQualifier * p, StrBuilder * fp)
{
    

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (p->Token == TK_AUTO)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }

        Output_Append(fp, options, "auto");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }
    }
    else if (p->Token == TK_LEFT_SQUARE_BRACKET)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }
        
        Output_Append(fp, options, "[");
        Output_Append(fp, options, p->SizeIdentifier);
        Output_Append(fp, options, "]");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }

    }
    else
    {

        Output_Append(fp, options, TokenToString(p->Token));
    }

#ifdef LANGUAGE_EXTENSIONS
    if (p->Token == TK_SIZEOF)
    {
        
        
        
        

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            
        }
    }
#endif
}

static void TTypeQualifierList_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeQualifierList * p, StrBuilder * fp)
{
    for (int i = 0; i < p->Size; i++)
    {
        TTypeQualifier * pItem = p->Data[i];
        TTypeQualifier_CodePrint(program, options, pItem, fp);
    }

}
static void TPointer_CodePrint(TProgram * program, PrintCodeOptions * options, TPointer * pPointer, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
    Output_Append(fp, options, "*");
    TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, fp);
}

void TSpecifierQualifierList_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pDeclarationSpecifiers,
    StrBuilder * fp)
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        if (i > 0 && options->Options.bCannonical)
        {
            
            Output_Append(fp, options, " ");
        }

        TSpecifierQualifier * pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier *)pItem, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier *)pItem, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier *)pItem, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier *)pItem, fp);
            break;
            
            
            

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier *)pItem, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier *)pItem, fp);
            break;

        default:
            
            break;
        }
    }


}

void TDeclarationSpecifiers_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarationSpecifiers * pDeclarationSpecifiers, StrBuilder * fp)
{

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier * pItem = pDeclarationSpecifiers->pData[i];

        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier *)pItem, fp);
            break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier *)pItem, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier *)pItem, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier *)pItem, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier *)pItem, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier *)pItem, fp);
            break;

            
            
            

        default:
            
            break;
        }
    }





}

void TInitDeclarator_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitDeclarator * p,
    StrBuilder * fp)
{
    TDeclarator_CodePrint(program, options, p->pDeclarator, true , fp);

    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "=");
        TInitializer_CodePrint(program,
            options,
            pDeclarator,
            pDeclarationSpecifiers,
            p->pInitializer,

            fp);
    }

}



void TInitDeclaratorList_CodePrint(TProgram * program,
    PrintCodeOptions * options,

    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitDeclaratorList * p,

    StrBuilder * fp)
{

    
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            Output_Append(fp, options, ",");


        TInitDeclarator_CodePrint(program,
            options,
            pInitDeclarator->pDeclarator,
            pDeclarationSpecifiers,
            pInitDeclarator,
            fp);
    }

    

}



TStructUnionSpecifier * GetStructSpecifier(TProgram * program, TDeclarationSpecifiers * specifiers);


static bool FindListStructPattern(TProgram * program,
    TParameter * pParameter,
    bool * pbItemIsPointer,
    bool * pbItemIsAutoPointer,
    StrBuilder * itemTypeName,
    StrBuilder * arrayName)
{
    
    

    bool bHasHead = false;
    bool bHasTail = false;

    
    TStructUnionSpecifier * pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        
        
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            TAnyStructDeclaration * pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            TStructDeclaration * pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator * pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);


                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    bool bIsPointer2 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);
                    if (bIsPointer1)

                    {
                        if (strcmp(structDeclaratorName, "pHead") == 0)
                        {
                            bHasHead = true;
                        }
                        if (strcmp(structDeclaratorName, "pTail") == 0)
                        {
                            bHasTail = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasHead && bHasTail;
}

static bool FindVectorStructPattern(TProgram * program,
    TParameter * pParameter,
    bool * pbItemIsPointer,
    bool * pbItemIsAutoPointer,
    StrBuilder * itemTypeName,
    StrBuilder * arrayName)
{
    
    
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    
    TStructUnionSpecifier * pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        
        
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            TAnyStructDeclaration * pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            TStructDeclaration * pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator * pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);


                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    bool bIsPointer2 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);

                    if (bIsPointer1 || bIsPointer2)
                    {
                        bHasVector = true;
                        StrBuilder_Set(arrayName, structDeclaratorName);

                        
                        bool bItemIsPointer =
                            TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsPointer = bIsPointer2;

                        
                        bool bItemIsAutoPointer =
                            TPointerList_IsAutoPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsAutoPointer = bItemIsPointer;

                        
                        
                        
                        
                        TTypeName * pTypeName = NULL;
                        PrintCodeOptions  options = CODE_PRINT_OPTIONS_INIT;
                        options.Options.bCannonical = true;
                        TSpecifierQualifierList_CodePrint(program, &options, &pStructDeclaration->SpecifierQualifierList, itemTypeName);
                        
                    }
                    else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        if (strcmp(structDeclaratorName, "Size") == 0)
                        {
                            bHasSize = true;
                        }
                        else if (strcmp(structDeclaratorName, "Capacity") == 0)
                        {
                            bHasCapacity = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasSize && bHasCapacity && bHasVector;
}


struct TemplateVar
{
    const char * Name;
    const char * Value;
};

const char * FindValue(const char * name, int namesize, struct TemplateVar * args, int argssize)
{
    for (int i = 0; i < argssize; i++)
    {
        if (namesize == strlen(args[i].Name) &&
            strncmp(name, args[i].Name, namesize) == 0)
        {
            return args[i].Value;
        }
    }
    return "?";
}

void StrBuilder_Template(StrBuilder * p,
    const char * tmpt,
    struct TemplateVar * vars,
    int size,
    int identationLevel)
{


    const char * pch = tmpt;

    
    for (int i = 0; i < identationLevel * 4; i++)
    {
        StrBuilder_AppendChar(p, ' ');
    }

    
    while (*pch == ' ')
    {
        for (int j = 0; j < 4; j++)
        {
            StrBuilder_AppendChar(p, ' ');
        }

        pch++;
    }

    while (*pch)
    {
        if (*pch == '$')
        {

            pch++;
            const char * name = pch;
            int namesize = 0;
            if (*pch &&
                (*pch >= 'a' && *pch <= 'z') ||
                (*pch >= 'A' && *pch <= 'Z') ||
                (*pch >= '_'))
            {
                pch++;
                namesize++;

                while (*pch &&
                    (*pch >= 'a' && *pch <= 'z') ||
                    (*pch >= 'A' && *pch <= 'Z') ||
                    (*pch >= '0' && *pch <= '9') ||
                    (*pch >= '_')) 
                {
                    pch++;
                    namesize++;
                }
            }

            const char * val =
                FindValue(name, namesize, vars, size);
            StrBuilder_Append(p, val);
        }
        else
        {
            
            
            
            

            if (*pch == '\n')
            {
                StrBuilder_AppendChar(p, *pch);
                pch++;


                if (*pch != '\0') 
                {
                    for (int i = 0; i < identationLevel * 4; i++)
                    {
                        StrBuilder_AppendChar(p, ' ');
                    }

                    
                    while (*pch == ' ')
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            StrBuilder_AppendChar(p, ' ');
                        }
                        pch++;
                    }
                }
            }
            else
            {
                if (*pch != '\b')
                {
                    StrBuilder_AppendChar(p, *pch);
                }
                pch++;
            }
        }
    }
}

void GetPrefixSuffix(const char * psz, StrBuilder * prefix, StrBuilder * suffix)
{
    while (*psz && *psz != '_')
    {
        StrBuilder_AppendChar(prefix, *psz);
        psz++;
    }

    if (*psz == '_')
        psz++;

    while (*psz)
    {
        StrBuilder_AppendChar(suffix, *psz);
        psz++;
    }
}

static int FindRuntimeID(TProgram * program,
    const char * structOrTypeName,
    StrBuilder * idname)
{
    
    TDeclaration * pFinalDecl =
        TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; 
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; 
        pStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
    }
    

    if (pStructUnionSpecifier &&
        pStructUnionSpecifier->UnionSet.pHead != NULL)
    {
        if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
        {
            TStructDeclaration * pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
            if (pStructDeclaration)
            {
                TStructDeclarator * pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                
                if (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    
                    {
                        StrBuilder_Set(idname, structDeclaratorName);
                    }
                }
            }
        }
    }
    return typeInt;
}


static int FindIDValue(TProgram * program,
    const char * structOrTypeName,
    StrBuilder * idname)
{
    
    TDeclaration * pFinalDecl =
        TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; 
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; 
        pStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
    }
    

    if (pStructUnionSpecifier)
    {
        if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
        {
            TStructDeclaration * pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
            if (pStructDeclaration)
            {
                TStructDeclarator * pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                
                if (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    
                    {
                        PrintCodeOptions options2 = CODE_PRINT_OPTIONS_INIT;
                        TInitializer_CodePrint(program, &options2, pStructDeclarator->pDeclarator,
                            (TDeclarationSpecifiers *)& pStructDeclaration->SpecifierQualifierList,
                            pStructDeclarator->pInitializer, idname);

                        
                    }
                }
            }
        }
    }
    return typeInt;
}


void FindUnionSetOf(TProgram * program,
    const char * structOrTypeName,
    Map2 * map)
{
    TDeclaration * pFinalDecl =
        TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; 
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; 
        pStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
    }

    if (pStructUnionSpecifier &&
        pStructUnionSpecifier->UnionSet.pHead != NULL)
    {
        TUnionSetItem * pCurrent =
            pStructUnionSpecifier->UnionSet.pHead;
        while (pCurrent)
        {
            FindUnionSetOf(program, pCurrent->Name, map);
            pCurrent = pCurrent->pNext;
        }
    }
    else
    {
        void * pp;
        Map2_SetAt(map, structOrTypeName, (void *)typeInt, &pp);
    }
}

void UnionTypeDefault(TProgram * program,
    PrintCodeOptions * options,
    const char * structName,
    TParameterTypeList * pArgsOpt, 
    const char * parameterName,
    const char * functionSuffix,
    StrBuilder * fp);
static const char * GetNullStr(TProgram * program);



static void DefaultFunctionDefinition_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclaration * p,
    StrBuilder * fp)
{

    
    TDeclarationSpecifiers * pSpecifiers =
        &p->Specifiers;

    const char * funcName =
        TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

    StrBuilder functionPrefix = STRBUILDER_INIT;
    StrBuilder functionSuffix = STRBUILDER_INIT;

    GetPrefixSuffix(funcName, &functionPrefix, &functionSuffix);

    


    TParameterTypeList * pArgs =
        TDeclaration_GetFunctionArguments(p);

    TParameter * pFirstParameter =
        TParameterTypeList_GetParameterByIndex(pArgs, 0);


    const char * functionTagName = TDeclaration_FindFunctionTagName(p, &program->GlobalScope);


    TParameter * pSecondParameter =
        TParameterTypeList_GetParameterByIndex(pArgs, 1);


    if (functionTagName && strcmp(functionTagName, "create") == 0)
    {
        options->IdentationLevel++;

        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(pSpecifiers),
            p->InitDeclaratorList.pHead->pDeclarator,
            NULL,
            pArgs,
            "p",
            NULL  ,
            ActionCreate,
            SearchInit,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "init") == 0 && pFirstParameter != NULL)
    {
        options->IdentationLevel++;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            pArgs, 
            TParameter_GetName(pFirstParameter),
            NULL  ,
            ActionInitContent,
            SearchNone,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "destroy") == 0 && pFirstParameter != NULL)
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            NULL, 
            TParameter_GetName(pFirstParameter),
            NULL  ,
            ActionDestroyContent,
            SearchNone,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "delete") == 0 && pFirstParameter != NULL)
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            NULL, 
            TParameter_GetName(pFirstParameter),
            NULL  ,
            ActionDelete,
            SearchDestroy,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else
    {
        
        const char * functionTag =
            TDeclaration_FindFunctionTagName(p, &program->GlobalScope);

        if (functionTag == NULL && !options->Options.bNoImplicitTag)
        {
            

            if (pFirstParameter != NULL &&
                pSecondParameter != NULL &&
                IsSuffix(funcName, "_Reserve"))
            {
                functionTag = "reserve";
            }
            else if (pFirstParameter != NULL &&
                pSecondParameter != NULL &&
                IsSuffix(funcName, "_PushBack"))
            {
                functionTag = "push";
            }
        }

        if (functionTag && strcmp(functionTag, "reserve") == 0)
        {
            bool bItemIsPointer;
            bool bItemIsAutoPointer;
            StrBuilder itemType = STRBUILDER_INIT;
            StrBuilder arrayName = STRBUILDER_INIT;

            
            if (FindVectorStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                const char * pszTemplatePointer =
                    "if ($nelements > $p->Capacity)\n"
                    "{\n"
                    " $type** pnew = $p->$data;\n"
                    " pnew = ($type**)$realloc(pnew, $nelements * sizeof($type*));\n"
                    " if (pnew)\n"
                    " {\n"
                    "  $p->$data = pnew;\n"
                    "  $p->Capacity = $nelements;\n"
                    " }\n"
                    "}\n";

                const char * pszTemplateNotPointer =
                    "if ($nelements > $p->Capacity)\n"
                    "{\n"
                    " $type* pnew = $p->$data;\n"
                    " pnew = ($type*)$realloc(pnew, $nelements * sizeof($type));\n"
                    " if (pnew)\n"
                    " {\n"
                    "  $p->$data = pnew;\n"
                    "  $p->Capacity = $nelements;\n"
                    " }\n"
                    "}\n";

                const char * pszTemplate =
                    bItemIsPointer ? pszTemplatePointer : pszTemplateNotPointer;

                struct TemplateVar vars[] = {
                  { "p", TParameter_GetName(pFirstParameter) },
                { "nelements", TParameter_GetName(pSecondParameter) },
                { "type", itemType.c_str },
                { "data", arrayName.c_str },
                { "realloc", GetReallocStr(program) }
                };

                StrBuilder_Template(fp,
                    pszTemplate,
                    vars,
                    sizeof(vars) / sizeof(vars[0]),
                    1  );
            }

            StrBuilder_Destroy(&itemType);
            StrBuilder_Destroy(&arrayName);
        }
        else if (functionTag && strcmp(functionTag, "push") == 0)
        {
            bool bItemIsPointer;
            bool bItemIsAutoPointer;
            StrBuilder itemType = STRBUILDER_INIT;
            StrBuilder arrayName = STRBUILDER_INIT;

            
            if (FindVectorStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                
                bool bHasReserve =
                    SymbolMap_FindObjFunction2(&program->GlobalScope, functionPrefix.c_str, "Reserve") != 0;
                const char * pszTemplate = "";

                if (bHasReserve)
                {
                    pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                        "{\n"
                        " int n = $p->Capacity * 2;\n"
                        " if (n == 0)\n"
                        " {\n"
                        "  n = 1;\n"
                        " }\n"
                        " $prefix\b_Reserve($p, n);\n"
                        "}\n"
                        "$p->$data[$p->Size] = $nelements;\n"
                        "$p->Size++;\n";
                }
                else
                {
                    if (bItemIsPointer)
                    {
                        pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                            "{\n"
                            " int n = $p->Capacity * 2;\n"
                            " if (n == 0)\n"
                            " {\n"
                            "  n = 1;\n"
                            " }\n"
                            " $type** pnew = $p->$data;\n"
                            " pnew = ($type**)$realloc(pnew, n * sizeof($type*));\n"
                            " if (pnew)\n"
                            " {\n"
                            "  $p->$data = pnew;\n"
                            "  $p->Capacity = n;\n"
                            " }\n"
                            "}\n"
                            "$p->$data[$p->Size] = $nelements;\n"
                            "$p->Size++;\n";
                    }
                    else
                    {
                        pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                            "{\n"
                            " int n = $p->Capacity * 2;\n"
                            " if (n == 0)\n"
                            " {\n"
                            "  n = 1;\n"
                            " }\n"
                            " $type* pnew = $p->$data;\n"
                            " pnew = ($type*)$realloc(pnew, n * sizeof($type));\n"
                            " if (pnew)\n"
                            " {\n"
                            "  $p->$data = pnew;\n"
                            "  $p->Capacity = n;\n"
                            " }\n"
                            "}\n"
                            "$p->$data[$p->Size] = $nelements;\n"
                            "$p->Size++;\n";
                    }


                }

                struct TemplateVar vars[] = {
                  { "p", TParameter_GetName(pFirstParameter)},
                { "nelements", TParameter_GetName(pSecondParameter) },
                { "type", itemType.c_str },
                { "data", arrayName.c_str },
                { "prefix", functionPrefix.c_str },
                { "realloc", GetReallocStr(program)}
                };

                StrBuilder_Template(fp,
                    pszTemplate,
                    vars,
                    sizeof(vars) / sizeof(vars[0]),
                    1 );
            }
            else if (FindListStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                struct TemplateVar vars[] = {
                  { "pList", TParameter_GetName(pFirstParameter) },
                { "pItem", TParameter_GetName(pSecondParameter) },
                { "type", itemType.c_str },
                { "data", arrayName.c_str },
                { "prefix", functionPrefix.c_str },
                { "null", GetNullStr(program)}
                };
                
                
                const char * pszTemplate =
                    "if ($pList->pHead == $null)\n"
                    "{\n"
                    " $pList->pHead = $pItem;\n"
                    "}\n"
                    "else\n"
                    "{\n"
                    " $pList->pTail->pNext = $pItem;\n"
                    "}\n"
                    "$pList->pTail = $pItem; \n";

                StrBuilder_Template(fp,
                    pszTemplate,
                    vars,
                    sizeof(vars) / sizeof(vars[0]),
                    1 );
            }

            StrBuilder_Destroy(&itemType);
            StrBuilder_Destroy(&arrayName);
        }
        else
        {
            if (pFirstParameter != NULL)
            {
                TStructUnionSpecifier * pStructUnionSpecifier =
                    GetStructSpecifier(program, &pFirstParameter->Specifiers);
                if (pStructUnionSpecifier &&
                    pStructUnionSpecifier->UnionSet.pHead != NULL)
                {
                    options->IdentationLevel++;
                    UnionTypeDefault(program,
                        options,
                        pStructUnionSpecifier->TagName,
                        pArgs,
                        TParameter_GetName(pFirstParameter),
                        functionSuffix.c_str,
                        fp);
                    options->IdentationLevel--;
                }
            }
        }
    }

    StrBuilder_Destroy(&functionPrefix);
    StrBuilder_Destroy(&functionSuffix);

}

static void TDeclaration_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclaration * p,

    StrBuilder * fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);

    TInitDeclaratorList_CodePrint(program,
        options,
        &p->Specifiers,
        &p->InitDeclaratorList, fp);

    if (p->FunctionTag && !p->bAutoTag)
    {
        TNodeClueList_CodePrint(options, &p->ClueList00, fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            StrBuilder_Append(fp, "/*@");
        }

        StrBuilder_Append(fp, ":");
        TNodeClueList_CodePrint(options, &p->ClueList001, fp);
        StrBuilder_Append(fp, p->FunctionTag);


        if (options->Options.Target == CompilerTarget_Annotated)
        {
            StrBuilder_Append(fp, "*/");
        }
    }

    if (p->pCompoundStatementOpt != NULL)
    {
         

        if (p->bDefault)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    StrBuilder_Append(fp, "/*@");
                }

                StrBuilder_Append(fp, "default");

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    StrBuilder_Append(fp, "*/");
                }


                TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
                Output_Append(fp, options, "{\n");

                DefaultFunctionDefinition_CodePrint(program,
                    options,
                    p,

                    fp);

                Output_Append(fp, options, "}");
            }
            else if (options->Options.Target == CompilerTarget_CXX)
            {
                StrBuilder_Append(fp, "default;");
            }


            return;
        }
        else
        {
            if (p->pCompoundStatementOpt != NULL)
            {
                
                TCompoundStatement_CodePrint(program,
                    options,
                    p->pCompoundStatementOpt,

                    fp);
            }
        }
    }
    else
    {


        if (p->bDefault)
        {

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                TNodeClueList_CodePrint(options, &p->ClueList0, fp);

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    StrBuilder_Append(fp, "/*@");
                }
                StrBuilder_Append(fp, "default");

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    StrBuilder_Append(fp, "*/");
                }

                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                Output_Append(fp, options, "\n{\n");

                DefaultFunctionDefinition_CodePrint(program,
                    options,
                    p,

                    fp);

                Output_Append(fp, options, "}");
            }
            else if (options->Options.Target == CompilerTarget_CXX)
            {
                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                StrBuilder_Append(fp, " default");
                Output_Append(fp, options, ";");
            }


            return;
        }
        else
        {
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, ";");
        }
    }


    return;
}

void TTypeName_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeName * p, StrBuilder * fp)
{

    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);

    TDeclarator_CodePrint(program, options, &p->Declarator, true , fp);


}

static void TParameter_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TParameter * p,

    StrBuilder * fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
    TDeclarator_CodePrint(program, options, &p->Declarator, true , fp);

    if (p->bHasComma)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEofDeclaration_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TEofDeclaration * p,

    StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
}

static void TStaticAssertDeclaration_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TStaticAssertDeclaration * p,

    StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "_StaticAssert");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pConstantExpression, "", fp);
    Output_Append(fp, options, ",");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, options, p->Text);


    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ")");
    TNodeClueList_CodePrint(options, &p->ClueList5, fp);
    Output_Append(fp, options, ";");

}

static void TGroupDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TGroupDeclaration * p, StrBuilder * fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "#pragma region cprime");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Identifier);
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, "\n");

    TDeclaration * pFunction =
        SymbolMap_FindFunction(&program->GlobalScope, p->Identifier);
    if (pFunction)
    {
        TDeclaration_CodePrint(program, options, pFunction, fp);
    }
    else
    {
        Map2 map = MAPSTRINGTOPTR_INIT;
        FindUnionSetOf(program, p->Identifier, &map);

        StrBuilder idname = STRBUILDER_INIT;

        int ir = FindRuntimeID(program,
            p->Identifier,
            &idname);

        for (int i = 0; i < (int)map.nHashTableSize; i++)
        {
            if (map.pHashTable[i])
            {
                const char * derivedName = (const char *)map.pHashTable[i]->Key;
                const char * baseName = p->Identifier;

                StrBuilder idnamelocal = STRBUILDER_INIT;

                int ir2 = FindIDValue(program,
                    derivedName,
                    &idnamelocal);

                struct TemplateVar vars0[] = {
                  { "base", baseName },
                { "derived", derivedName },
                { "id", idname.c_str },
                { "idvalue", idnamelocal.c_str }
                };

                if ((int)map.pHashTable[i]->pValue == 2)
                {




                    if (ir == 2)
                    {
                        StrBuilder_Template(fp,
                            "inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                            "inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
                            vars0,
                            sizeof(vars0) / sizeof(vars0[0]),
                            options->IdentationLevel);
                    }
                    else
                    {
                        if (ir == 2)
                        {
                            StrBuilder_Template(fp,
                                "inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                                "inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
                                vars0,
                                sizeof(vars0) / sizeof(vars0[0]),
                                options->IdentationLevel);
                        }
                        else
                        {
                            StrBuilder_Template(fp,
                                "inline struct $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                                "inline $base* $derived\b_As_$base(struct $derived* p) { return ($base*) p; }\n",
                                vars0,
                                sizeof(vars0) / sizeof(vars0[0]),
                                options->IdentationLevel);
                        }
                    }

                }
                else
                {
                    StrBuilder_Template(fp,
                        "inline $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? ($derived*) p : 0;}\n"
                        "inline $base* $derived\b_As_$base($derived* p) { return ($base*) p; }\n",
                        vars0,
                        sizeof(vars0) / sizeof(vars0[0]),
                        options->IdentationLevel);
                }

                StrBuilder_Destroy(&idnamelocal);
            }
        }

        Map2_Destroy(&map, NULL);
        StrBuilder_Destroy(&idname);

    }

    
    
      
    
    
    Output_Append(fp, options, "#pragma endregion cprime\n");
}

static void TAnyDeclaration_CodePrint(TProgram * program, PrintCodeOptions * options, TAnyDeclaration * pDeclaration, StrBuilder * fp)
{
    switch (pDeclaration->Type)
    {
    case TGroupDeclaration_ID:
        TGroupDeclaration_CodePrint(program, options, (TGroupDeclaration *)pDeclaration, fp);
        break;

    case TEofDeclaration_ID:
        TEofDeclaration_CodePrint(program, options, (TEofDeclaration *)pDeclaration, fp);
        break;

    case TStaticAssertDeclaration_ID:
        TStaticAssertDeclaration_CodePrint(program, options, (TStaticAssertDeclaration *)pDeclaration, fp);
        break;

    case TDeclaration_ID:
        TDeclaration_CodePrint(program, options, (TDeclaration *)pDeclaration, fp);
        break;

    default:
        
        break;
    }


}

static void TDesignatorList_CodePrint(TProgram * program, PrintCodeOptions * options, TDesignatorList * p, StrBuilder * fp)
{



    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            Output_Append(fp, options, ",");
        }
        TDesignator_CodePrint(program, options, pItem, fp);
    }



}


static void TInitializerListItem_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclarator * pDeclarator,
    TDeclarationSpecifiers * pDeclarationSpecifiers,
    TInitializerListItem * p,

    StrBuilder * fp)
{
    if (p->DesignatorList.pHead != NULL)
    {
        TDesignatorList_CodePrint(program, options, &p->DesignatorList, fp);
    }

    TInitializer_CodePrint(program,
        options,
        pDeclarator,
        pDeclarationSpecifiers,
        p->pInitializer,
        fp);

    TNodeClueList_CodePrint(options, &p->ClueList, fp);
}



void TProgram_PrintCodeToFile(TProgram * pProgram,
    struct Options * options0,
    const char * outFileName,
    const char * inputFileName)
{
    PrintCodeOptions options = CODE_PRINT_OPTIONS_INIT;
    options.Options = *options0;

    global_lambda_counter = 0;

    FILE * fp = fopen(outFileName, "w");

    if (fp == NULL)
    {
        printf("cannot open output file %s", outFileName);
        return;
    }



    int k = 0;

    
    
    
    
    

    StrBuilder sb = STRBUILDER_INIT;
    StrBuilder_Reserve(&sb, 80 * 5000);

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        TAnyDeclaration * pItem = pProgram->Declarations.pItems[i];

        StrBuilder_Clear(&pProgram->sbPreDeclaration);

        StrBuilder sbDeclaration = STRBUILDER_INIT;
        TAnyDeclaration_CodePrint(pProgram, &options, pItem, &sbDeclaration);

        StrBuilder_Append(&sb, pProgram->sbPreDeclaration.c_str);
        StrBuilder_Append(&sb, sbDeclaration.c_str);

        StrBuilder_Destroy(&sbDeclaration);


        fprintf(fp, "%s", sb.c_str);


        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);
    fclose(fp);
}

void TProgram_PrintCodeToString(TProgram * pProgram,
    struct Options * options0,
    StrBuilder * output)
{
    PrintCodeOptions options = CODE_PRINT_OPTIONS_INIT;
    options.Options = *options0;
    global_lambda_counter = 0;
    int k = 0;


    StrBuilder sb = STRBUILDER_INIT;
    StrBuilder_Reserve(&sb, 80 * 5000);

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        TAnyDeclaration * pItem = pProgram->Declarations.pItems[i];

        StrBuilder_Clear(&pProgram->sbPreDeclaration);

        StrBuilder sbDeclaration = STRBUILDER_INIT;
        TAnyDeclaration_CodePrint(pProgram, &options, pItem, &sbDeclaration);

        StrBuilder_Append(&sb, pProgram->sbPreDeclaration.c_str);
        StrBuilder_Append(&sb, sbDeclaration.c_str);

        StrBuilder_Destroy(&sbDeclaration);

        StrBuilder_Append(output, sb.c_str);


        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);

}


static const char * GetFreeStr(TProgram * program)
{
    bool bCustomFree =
        SymbolMap_FindFunction(&program->GlobalScope, "Free") != NULL ||
        MacroMap_Find(&program->Defines, "Free") != NULL;

    return bCustomFree ? "Free" : "free";
}

static const char * GetMallocStr(TProgram * program)
{
    bool bCustomMalloc =
        SymbolMap_FindFunction(&program->GlobalScope, "Malloc") != NULL ||
        MacroMap_Find(&program->Defines, "Malloc") != NULL;

    return bCustomMalloc ? "Malloc" : "malloc";
}

static const char * GetReallocStr(TProgram * program)
{
    bool bCustomMalloc =
        SymbolMap_FindFunction(&program->GlobalScope, "Realloc") != NULL ||
        MacroMap_Find(&program->Defines, "Realloc") != NULL;

    return bCustomMalloc ? "Realloc" : "realloc";
}


static const char * GetFalseStr(TProgram * program)
{
    bool bHasFalse =
        MacroMap_Find(&program->Defines, "false") != NULL;

    return bHasFalse ? "false" : "0";
}

static const char * GetNullStr(TProgram * program)
{
    bool bHasFalse =
        MacroMap_Find(&program->Defines, "NULL") != NULL;

    return bHasFalse ? "NULL" : "0";
}



static void PrintIfNotNullLn(TProgram * program,
    PrintCodeOptions * options,
    const char * pInitExpressionText, 
    StrBuilder * fp)
{
    bool bHasNULL =
        MacroMap_Find(&program->Defines, "NULL") != NULL;

    if (bHasNULL)
    {
        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "if (%s != NULL)",
            pInitExpressionText);
    }
    else
    {
        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "if (%s)",
            pInitExpressionText);
    }
}

static TDeclaration * FindHighLevelFunctionCore(struct SymbolMap * pMap,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TDeclarator * pDeclatator,                        
    const char * functionTagName)
{
    TDeclaration * pResult = NULL;

    if (functionTagName == NULL)
    {
        return NULL;
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                functionTagName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            
            if (pKeyValue->pValue->Type == TDeclaration_ID)
            {
                if (strcmp(pKeyValue->Key, functionTagName) == 0)
                {
                    
                    TDeclaration * pDeclaration =
                        (TDeclaration *)pKeyValue->pValue;

                    if (pDeclaration->FunctionTag &&
                        strcmp(pDeclaration->FunctionTag, functionTagName) == 0)
                    {
                        TDeclarationSpecifiers * pDeclarationSpecifiersOfArg1 =
                            TDeclaration_GetArgTypeSpecifier(pDeclaration, 0);

                        if (pDeclarationSpecifiersOfArg1)
                        {
                            if (TSpecifierQualifierList_Compare(pDeclarationSpecifiersOfArg1, pSpecifierQualifierList))
                            {
                                pResult = pDeclaration;
                                break;
                            }
                            else
                            {
                                
                                
                                const char * typedefName = TDeclarationSpecifiers_GetTypedefName(pDeclarationSpecifiersOfArg1);
                                if (typedefName)
                                {
                                    TTypeSpecifier * p = SymbolMap_FindTypedefSpecifierTarget(pMap, typedefName);
                                    if (TTypeSpecifier_Compare(p, pSpecifierQualifierList->pData[0]))
                                    {
                                        pResult = pDeclaration;
                                        break;
                                    }
                                }
                                else
                                {
                                    const char * typedefName = TDeclarationSpecifiers_GetTypedefName(pSpecifierQualifierList);
                                    if (typedefName)
                                    {
                                        TTypeSpecifier * p = SymbolMap_FindTypedefSpecifierTarget(pMap, typedefName);
                                        if (TTypeSpecifier_Compare(p, pDeclarationSpecifiersOfArg1->pData[0]))
                                        {
                                            pResult = pDeclaration;
                                            break;
                                        }
                                    }
                                }
                                
                                pResult = 0;
                            }
                        }
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }



    return pResult;
}

static bool FindHighLevelFunction(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TDeclarator * pDeclatator,                        
    TParameterTypeList * pArgsOpt, 
    TInitializer * pInitializerOpt,
    const char * pInitExpressionText, 
    const char * pszAutoPointerLenExpressionOpt,
    const Action action,
    Search search,
    const char * nameToFind,
    StrBuilder * fp)
{
    if (nameToFind == NULL)
    {
        
        return false;
    }




    bool bComplete = false;

    

    
    bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
    bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerSizeToObject = TPointerList_IsAutoPointerSizeToObject(&pDeclatator->PointerList);

    if (action == ActionDestroy || action == ActionDestroyContent)
    {
        if (bIsPointer)
        {
            if (bIsAutoPointerSizeToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
            {
                
                
                if (search == SearchAll ||
                    search == SearchDelete)
                {
                    
                    TDeclaration * pDeclarationDestroy =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                            pSpecifierQualifierList,
                            pDeclatator,
                            "delete");
                    if (pDeclarationDestroy)
                    {
                        const char * funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);
                        if (bIsAutoPointerToObject)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                "%s(%s);",
                                funcName,
                                pInitExpressionText);
                            bComplete = true;
                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {

                            if (pszAutoPointerLenExpressionOpt)
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                options->IdentationLevel++;

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "%s(%s[i]);",
                                    funcName,
                                    pInitExpressionText);

                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "%s((void*)%s);",
                                    GetFreeStr(program),
                                    pInitExpressionText);
                            }
                            else
                            {
                                
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "%s(%s[0]);",
                                    funcName,
                                    pInitExpressionText);

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "%s((void*)%s);",
                                    GetFreeStr(program),
                                    pInitExpressionText);
                            }

                            bComplete = true;
                        }
                    }
                    else
                    {
                        if (search == SearchAll ||
                            search == SearchDestroy)
                        {
                            
                            
                            TDeclaration * pDeclarationDestroy2 =
                                FindHighLevelFunctionCore(&program->GlobalScope,
                                    pSpecifierQualifierList,
                                    pDeclatator,
                                    "destroy");
                            if (pDeclarationDestroy2)
                            {
                                const char * funcName = TDeclaration_GetFunctionName(pDeclarationDestroy2);

                                if (bIsAutoPointerToObject)
                                {
                                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        "%s(%s);",
                                        funcName,
                                        pInitExpressionText);

                                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        "%s((void*)%s);",
                                        GetFreeStr(program),
                                        pInitExpressionText);
                                }
                                else if (bIsAutoPointerToAutoPointer)
                                {
                                    if (pszAutoPointerLenExpressionOpt)
                                    {
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                        options->IdentationLevel++;

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s(%s[i]);",
                                            funcName,
                                            pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s[i]);",
                                            GetFreeStr(program),
                                            pInitExpressionText);

                                        options->IdentationLevel--;
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s);",
                                            GetFreeStr(program),
                                            pInitExpressionText);
                                    }
                                    else
                                    {
                                        

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s(%s[0]);",
                                            funcName,
                                            pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s[0]);",
                                            GetFreeStr(program),
                                            pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s);",
                                            GetFreeStr(program),
                                            pInitExpressionText);
                                    }

                                }
                                else if (bIsAutoPointerSizeToObject)
                                {
                                    if (pszAutoPointerLenExpressionOpt)
                                    {
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                        options->IdentationLevel++;

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s(%s[i]);",
                                            funcName,
                                            pInitExpressionText);

                                        
                                        
                                        

                                        options->IdentationLevel--;
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s);",
                                            GetFreeStr(program),
                                            pInitExpressionText);
                                    }
                                    else
                                    {
                                        

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s(%s[0]);",
                                            funcName,
                                            pInitExpressionText);

                                        
                                        
                                        

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s);",
                                            GetFreeStr(program),
                                            pInitExpressionText);
                                    }
                                }

                                bComplete = true;
                            }
                        }
                    }
                }
            }
            else if (bIsAutoPointerToPointer)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "%s((void*)%s);",
                    GetFreeStr(program),
                    pInitExpressionText);

                
                bComplete = true;
            }
            else
            {
                if (action != ActionDestroyContent)
                {
                    
                    bComplete = true;
                }
            }

        }
        else
        {
            
            if (!bIsAutoPointerToPointer)
            {
                if (search == SearchAll ||
                    search == SearchDestroy)
                {
                    TDeclaration * pDeclarationDestroy =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                            pSpecifierQualifierList,
                            pDeclatator,
                            "destroy"
                        );

                    
                    
                      
                        
                          
                    if (pDeclarationDestroy)
                    {
                        const char * destroyFuncName =
                            TDeclaration_GetFunctionName(pDeclarationDestroy);
                        if (destroyFuncName)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                "%s(&%s);",
                                destroyFuncName,
                                pInitExpressionText);
                        }
                        else
                        {
                            assert(false);
                        }

                        
                          
                            
                            
                        bComplete = true;
                    }
                }
            }

        }
    }
    else if (action == ActionDelete)
    {
        
        if (search == SearchAll ||
            search == SearchDelete)
        {
            
            TDeclaration * pDeclarationDestroy =
                FindHighLevelFunctionCore(&program->GlobalScope,
                    pSpecifierQualifierList,
                    pDeclatator,
                    "delete");
            if (pDeclarationDestroy)
            {
                const char * funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "%s(%s);",
                    funcName,
                    pInitExpressionText);
                bComplete = true;
            }
            else
            {
                if (search == SearchAll ||
                    search == SearchDestroy)
                {
                    
                    
                    TDeclaration * pDeclarationDestroy2 =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                            pSpecifierQualifierList,
                            pDeclatator,
                            "destroy");
                    if (pDeclarationDestroy2)
                    {
                        const char * funcName = TDeclaration_GetFunctionName(pDeclarationDestroy2);
                        StrBuilder_AppendFmtLn(fp, 4 * 1,
                            "%s(%s);",
                            funcName,
                            pInitExpressionText);

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "%s((void*)%s);",
                            GetFreeStr(program),
                            pInitExpressionText);
                        bComplete = true;
                    }
                }

            }
        }
        else
        {
            
            
            
            
            if (search == SearchAll ||
                search == SearchDestroy)
            {
                TDeclaration * pDeclarationDestroy =
                    FindHighLevelFunctionCore(&program->GlobalScope,
                        pSpecifierQualifierList,
                        pDeclatator,
                        "destroy");
                if (pDeclarationDestroy)
                {
                    const char * funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);

                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);



                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");

                    options->IdentationLevel++;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s(%s);",
                        funcName,
                        pInitExpressionText);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s((void*)%s);",
                        GetFreeStr(program),
                        pInitExpressionText);
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "}",
                        pInitExpressionText);

                    bComplete = true;
                }
            }

        }
    }
    else if (action == ActionInit)
    {
        if (bIsPointer)
        {
            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                "%s = %s;",
                pInitExpressionText,
                GetNullStr(program));
            bComplete = true;
        }
        else
        {
            if (search == SearchAll ||
                search == SearchInit)
            {
                
                


                TDeclaration * pDeclarationInit =
                    FindHighLevelFunctionCore(&program->GlobalScope,
                        pSpecifierQualifierList,
                        pDeclatator,
                        "init");
                if (pDeclarationInit)
                {
                    const char * funcName = TDeclaration_GetFunctionName(pDeclarationInit);

                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                        "%s(&%s",
                        funcName,
                        pInitExpressionText);

                    TParameterTypeList_GetArgsString(pArgsOpt, fp);

                    StrBuilder_Append(fp, ");\n");

                    bComplete = true;
                }
            }

        }
    }
    else if (action == ActionInitContent)
    {
        if (search == SearchAll ||
            search == SearchInit)
        {
            TDeclaration * pDeclarationInit =
                FindHighLevelFunctionCore(&program->GlobalScope,
                    pSpecifierQualifierList,
                    pDeclatator,
                    "init");
            if (pDeclarationInit)
            {
                const char * funcName = TDeclaration_GetFunctionName(pDeclarationInit);

                if (bIsPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s(%s);",
                        funcName,
                        pInitExpressionText);
                }
                else
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s(&%s);",
                        funcName,
                        pInitExpressionText);
                }
                bComplete = true;
            }

        }
    }
    else if (action == ActionCreate)
    {
        if (search == SearchAll ||
            search == SearchInit)
        {
            TDeclaration * pDeclarationInit =
                FindHighLevelFunctionCore(&program->GlobalScope,
                    pSpecifierQualifierList,
                    pDeclatator,
                    "init");
            if (pDeclarationInit)
            {
                const char * funcName = TDeclaration_GetFunctionName(pDeclarationInit);


                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "struct %s *p = (struct %s *) %s(sizeof * p);",
                    nameToFind,
                    nameToFind,
                    GetMallocStr(program));


                PrintIfNotNullLn(program, options, "p", fp);


                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "{");
                options->IdentationLevel++;

                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                    "%s(p",
                    funcName);

                if (TParameterTypeList_HasNamedArgs(pArgsOpt))
                {
                    StrBuilder_Append(fp, ", ");
                    TParameterTypeList_GetArgsString(pArgsOpt, fp);
                }

                StrBuilder_Append(fp, ");\n");


                options->IdentationLevel--;

                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "}");

                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "return p;");

                bComplete = true;
            }

        }
    }
    else if (action == ActionStaticInit)
    {
        if (pInitializerOpt)
        {
            StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
            PrintCodeOptions options2 = *options;
            TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
            bComplete = true;
        }
        else if (bIsPointer)
        {
            StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
            bComplete = true;
        }


    }
    return bComplete;
}



static bool IsVector(TStructUnionSpecifier * pStructUnionSpecifier)
{
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    if (pStructUnionSpecifier)
    {
        
        
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            TAnyStructDeclaration * pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            TStructDeclaration * pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator * pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);

                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    if (bIsPointer1)
                    {
                        bHasVector = true;
                    }
                    else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        if (strcmp(structDeclaratorName, "Size") == 0)
                        {
                            bHasSize = true;
                        }
                        else if (strcmp(structDeclaratorName, "Capacity") == 0)
                        {
                            bHasCapacity = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasSize && bHasCapacity && bHasVector;
}

void UnionTypeDefault(TProgram * program,
    PrintCodeOptions * options,
    const char * structName,
    TParameterTypeList * pArgsOpt, 
    const char * parameterName0,
    const char * functionSuffix,
    StrBuilder * fp)
{
    Map2 map = MAPSTRINGTOPTR_INIT;
    FindUnionSetOf(program, structName, &map);

    StrBuilder strid = STRBUILDER_INIT;
    FindRuntimeID(program, structName, &strid);

    StrBuilder args = STRBUILDER_INIT;

    if (pArgsOpt != NULL)
    {
        
        TParameterTypeList_GetArgsString(pArgsOpt, &args);
    }
    else
    {
        StrBuilder_Append(&args, parameterName0);
    }

    struct TemplateVar vars0[] = {
      { "p", parameterName0 },
    { "id", strid.c_str }
    };

    StrBuilder_Template(fp,
        "switch ($p->$id)\n"
        "{\n",
        vars0,
        sizeof(vars0) / sizeof(vars0[0]),
        options->IdentationLevel);

    StrBuilder_Destroy(&strid);

    for (int i = 0; i < (int)map.nHashTableSize; i++)
    {
        if (map.pHashTable[i])
        {
            StrBuilder idvalue = STRBUILDER_INIT;

            FindIDValue(program,
                (const char *)map.pHashTable[i]->Key,
                &idvalue);

            struct TemplateVar vars[] = {
            { "type", (const char *)map.pHashTable[i]->Key },
            { "suffix", functionSuffix },
            { "value", idvalue.c_str },
            { "args", args.c_str }
            };
            if ((int)map.pHashTable[i]->pValue == 2)
            {
                
                StrBuilder_Template(fp,
                    " case $value:\n"
                    "  $type\b_$suffix((struct $type*)$args);\n"
                    " break;\n",
                    vars,
                    sizeof(vars) / sizeof(vars[0]),
                    options->IdentationLevel);
            }
            else
            {
                
                StrBuilder_Template(fp,
                    " case $value:\n"
                    "  $type\b_$suffix(($type*)$args);\n"
                    " break;\n",
                    vars,
                    sizeof(vars) / sizeof(vars[0]),
                    options->IdentationLevel);
            }
            StrBuilder_Destroy(&idvalue);
        }
    }

    StrBuilder_Template(fp,
        " default:\n"
        " break;\n"
        "}\n",
        NULL,
        0,
        options->IdentationLevel);

    StrBuilder_Destroy(&args);

    Map2_Destroy(&map, NULL); 
}

void InstanciateDestroy2(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TDeclarator * pDeclatator,                        
    TInitializer * pInitializerOpt, 
    TParameterTypeList * pArgsOpt, 
    const char * pInitExpressionText, 
    const char * pszAutoPointerLenExpressionOpt, 
                
    const Action action,
    Search search,
    bool * pbHasInitializers,
    StrBuilder * fp)
{
    if (pInitializerOpt && pbHasInitializers)
    {
        *pbHasInitializers = true;
    }


    bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
    bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);

    TDeclarationSpecifier * pMainSpecifier =
        TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

    if (pMainSpecifier == NULL)
    {
        
        return;
    }

    if (pMainSpecifier->Type == TSingleTypeSpecifier_ID)
    {
        TSingleTypeSpecifier * pSingleTypeSpecifier =
            (TSingleTypeSpecifier *)pMainSpecifier;

        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            bool bComplete = false;
            TDeclarator declarator;
            TDeclarator_Init(&declarator);
            
            
            
            
            
            TDeclarationSpecifiers * pDeclarationSpecifiers =
                SymbolMap_FindTypedefFirstTarget(&program->GlobalScope,
                    pSingleTypeSpecifier->TypedefName,
                    &declarator);
            if (pDeclarationSpecifiers)
            {
                ForEachListItem(TPointer, pItem, &pDeclatator->PointerList)
                {
                    TPointer * pNew = TPointer_Create();
                    TPointer_Copy(pNew, pItem);
                    TPointerList_PushBack(&declarator.PointerList, pNew);
                }

                

                if (action == ActionCreate)
                {
                    
                    

                    
                    
                    
                    
                    
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s *p = (%s*) %s(sizeof * p);",
                        pSingleTypeSpecifier->TypedefName,
                        pSingleTypeSpecifier->TypedefName,
                        GetMallocStr(program));

                    PrintIfNotNullLn(program, options, "p", fp);

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");

                    options->IdentationLevel++;

                    
                    

                    TDeclaration * pDeclarationInit =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                            pSpecifierQualifierList,
                            pDeclatator,
                            "init");

                    
                      
                        
                          

                    if (pDeclarationInit)
                    {
                        const char * funcName = TDeclaration_GetFunctionName(pDeclarationInit);


                        StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                            "%s(p",
                            funcName);

                        
                            
                            

                        if (TParameterTypeList_HasNamedArgs(pArgsOpt))
                        {
                            StrBuilder_Append(fp, ", ");
                            TParameterTypeList_GetArgsString(pArgsOpt, fp);
                        }

                        StrBuilder_Append(fp, ");\n");

                        bComplete = true;
                    }
                    


                    if (!bComplete)
                    {

                        
                        InstanciateDestroy2(program,
                            options,
                            (TSpecifierQualifierList *)pDeclarationSpecifiers,
                            &declarator,
                            NULL,
                            pArgsOpt,
                            "p",
                            NULL  ,
                            ActionInitContent,
                            SearchNone, 
                            pbHasInitializers,
                            fp);
                    }

                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "}");

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "return p;");

                }
                else
                {
                    bComplete = FindHighLevelFunction(program,
                        options,
                        pSpecifierQualifierList,
                        pDeclatator,                        
                        pArgsOpt, 
                        pInitializerOpt,
                        pInitExpressionText, 
                        pszAutoPointerLenExpressionOpt,
                        action,
                        search,
                        pSingleTypeSpecifier->TypedefName,
                        fp);


                    if (!bComplete)
                    {
                        Action action2 = action;

                        
                        InstanciateDestroy2(program,
                            options,
                            (TSpecifierQualifierList *)pDeclarationSpecifiers,
                            &declarator,
                            pInitializerOpt,
                            pArgsOpt,
                            pInitExpressionText,
                            pszAutoPointerLenExpressionOpt,
                            action2,
                            search,
                            pbHasInitializers,
                            fp);
                    }
                }

                TDeclarator_Destroy(&declarator);
            }
            else
            {
                
                
            }

        }
        else if (pSingleTypeSpecifier->Token2 == TK_STRUCT ||
            pSingleTypeSpecifier->Token2 == TK_UNION)
        {
            TStructUnionSpecifier * pStructUnionSpecifier = NULL;

            
            bool bComplete = false;

            bComplete = FindHighLevelFunction(program,
                options,
                pSpecifierQualifierList,
                pDeclatator,                        
                pArgsOpt,
                pInitializerOpt,
                pInitExpressionText, 
                pszAutoPointerLenExpressionOpt,
                action,
                search,
                pSingleTypeSpecifier->TypedefName,
                fp);

            
            
            
            
            
            if (!bComplete) 
            {
                if (pSingleTypeSpecifier &&
                    pSingleTypeSpecifier->TypedefName != NULL)
                {
                    
                    
                    pStructUnionSpecifier =
                        SymbolMap_FindStructUnion(&program->GlobalScope, pSingleTypeSpecifier->TypedefName);
                }

                
                
                
                bool bIsUnionTypes = pStructUnionSpecifier &&
                    pStructUnionSpecifier->UnionSet.pHead != NULL;

                if (pStructUnionSpecifier &&
                    pStructUnionSpecifier->StructDeclarationList.Size > 0)
                {
                    if (action == ActionDelete)
                    {
                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
                        options->IdentationLevel++;
                    }
                    else if (action == ActionDestroy)
                    {
                        if (bIsAutoPointerToObject)
                        {
                            PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;
                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {

                            PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;

                            if (pszAutoPointerLenExpressionOpt)
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                                options->IdentationLevel++;
                            }
                            else
                            {
                                
                            }

                        }

                    }
                    else if (action == ActionCreate)
                    {
                        
                        
                        

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "struct %s* p = (struct %s*) %s(sizeof * p);",
                            pStructUnionSpecifier->TagName,
                            pStructUnionSpecifier->TagName,
                            GetMallocStr(program));

                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "{");
                        options->IdentationLevel++;
                    }
                    else if (action == ActionStaticInit)
                    {
                        StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "{");
                    }

                    if (bIsUnionTypes)
                    {
                        if (action == ActionDelete)
                        {
                            options->IdentationLevel++;
                            UnionTypeDefault(program,
                                options,
                                pStructUnionSpecifier->TagName,
                                NULL,  
                                pInitExpressionText,
                                "Delete",
                                fp);
                            options->IdentationLevel--;
                        }
                        else if (action == ActionDestroyContent ||
                            action == ActionDestroy)
                        {
                            options->IdentationLevel++;
                            UnionTypeDefault(program,
                                options,
                                pStructUnionSpecifier->TagName,
                                NULL,  
                                pInitExpressionText,
                                "Destroy",
                                fp);
                            options->IdentationLevel--;
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        int variableCount = 0;
                        
                        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
                        {




                            TAnyStructDeclaration * pAnyStructDeclaration =
                                pStructUnionSpecifier->StructDeclarationList.pItems[i];

                            TStructDeclaration * pStructDeclaration =
                                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                            if (pStructDeclaration != NULL)
                            {
                                TStructDeclarator * pStructDeclarator =
                                    pStructDeclaration->DeclaratorList.pHead;

                                StrBuilder strVariableName = STRBUILDER_INIT;
                                StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


                                while (pStructDeclarator)
                                {

                                    if (action == ActionStaticInit && variableCount > 0)
                                    {
                                        StrBuilder_Append(fp, ", ");
                                    }

                                    variableCount++;
                                    
                                    TInitializer * pStructMemberInitializer =
                                        pStructDeclarator->pInitializer;

                                    TPrimaryExpressionValue initializerExpression;
                                    TPrimaryExpressionValue_Init(&initializerExpression);


                                    StrBuilder_Clear(&strVariableName);
                                    StrBuilder_Clear(&strPonterSizeExpr);

                                    const char * structDeclaratorName =
                                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                                    if (action != ActionStaticInit)
                                    {
                                        if (pInitExpressionText)
                                            StrBuilder_Set(&strVariableName, pInitExpressionText);


                                        if (bIsAutoPointerToAutoPointer)
                                        {
                                            if (pszAutoPointerLenExpressionOpt)
                                            {
                                                StrBuilder_Append(&strVariableName, "[i]");
                                            }
                                            else
                                            {
                                                StrBuilder_Append(&strVariableName, "[0]");
                                            }
                                        }

                                        if (bIsPointer)
                                        {
                                            StrBuilder_Append(&strVariableName, "->");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strVariableName, ".");
                                        }
                                    }
                                    else
                                    {
                                        StrBuilder_Append(&strVariableName, ".");
                                    }

                                    StrBuilder_Append(&strVariableName, structDeclaratorName);


                                    Action action2 = action;
                                    if (action == ActionDestroyContent ||
                                        action == ActionDelete)
                                    {
                                        
                                        action2 = ActionDestroy;
                                    }
                                    else if (action == ActionInitContent)
                                    {

                                        TParameter * pParameter = NULL;
                                        if (pArgsOpt)
                                        {
                                            pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                            if (pParameter != NULL)
                                            {
                                                pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                                initializerExpression.token = TK_IDENTIFIER;
                                                PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                            }
                                        }

                                        action2 = ActionInit;
                                    }
                                    else if (action == ActionCreate)
                                    {
                                        TParameter * pParameter = NULL;
                                        if (pArgsOpt)
                                        {
                                            pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                            if (pParameter != NULL)
                                            {
                                                pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                                initializerExpression.token = TK_IDENTIFIER;
                                                PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                            }
                                        }

                                        action2 = ActionInit;
                                    }

                                    if (action2 == ActionDestroy)
                                    {

                                        
                                        
                                        
                                        
                                        
                                        


                                        const char * pszSize =
                                            TPointerList_GetSize(&pStructDeclarator->pDeclarator->PointerList);
                                        if (pszSize)
                                        {
                                            if (pInitExpressionText)
                                                StrBuilder_Set(&strPonterSizeExpr, pInitExpressionText);

                                            if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                                            {
                                                StrBuilder_Append(&strPonterSizeExpr, "->");
                                            }
                                            else
                                            {
                                                StrBuilder_Append(&strPonterSizeExpr, ".");
                                            }
                                            StrBuilder_Append(&strPonterSizeExpr, pszSize);
                                        }
                                        else
                                        {
                                            
                                        }
                                    }

                                    
                                    InstanciateDestroy2(program,
                                        options,
                                        &pStructDeclaration->SpecifierQualifierList,
                                        pStructDeclarator->pDeclarator,
                                        pStructMemberInitializer,
                                        NULL, 
                                        strVariableName.c_str,
                                        strPonterSizeExpr.c_str,
                                        action2,
                                        SearchAll,
                                        pbHasInitializers,
                                        fp);



                                    
                                    TPrimaryExpressionValue_Destroy(&initializerExpression);

                                    pStructDeclarator = (pStructDeclarator)->pNext;
                                }

                                StrBuilder_Destroy(&strVariableName);
                                StrBuilder_Destroy(&strPonterSizeExpr);

                            }
                        }
                    }

                    if (action == ActionDestroy)
                    {
                        if (bIsAutoPointerToObject)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {
                            if (pszAutoPointerLenExpressionOpt)
                            {
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); 
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                            }
                            else
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                            }


                            
                        }
                    }
                    else if (action == ActionDestroyContent)
                    {
                        if (bIsAutoPointerToAutoPointer)
                        {
                            
                            
                            
                            
                        }
                    }
                    else if (action == ActionDelete)
                    {
                        if (bIsUnionTypes)
                        {

                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                        }
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                    }
                    else if (action == ActionCreate)
                    {
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "}");

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "return p;");
                    }
                    else if (action == ActionStaticInit)
                    {

                        StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "}");


                    }
                }
                else
                {
                    
                    StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
                }
                
            }


        }
        else if (pSingleTypeSpecifier->Token2 == TK_ENUM)
        {
            
            
        }
        else
        {
            
            if (action == ActionDestroy)
            {
                if (bIsAutoPointerToObject)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                }
                else if (bIsAutoPointerToAutoPointer)
                {
                    if (pszAutoPointerLenExpressionOpt)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                        options->IdentationLevel++;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[i]);", GetFreeStr(program), pInitExpressionText);
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }
                    else
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[0]);", GetFreeStr(program), pInitExpressionText);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }

                    
                }
                else
                {
                    
                }
            }
            else if (action == ActionInit)
            {
                if (pInitializerOpt)
                {
                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                    PrintCodeOptions options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
                    StrBuilder_Append(fp, ";\n");
                }
                else
                {


                    if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
                    }
                    else
                    {
                        if (TSpecifierQualifierList_IsBool(pSpecifierQualifierList))
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetFalseStr(program));
                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0;", pInitExpressionText);
                        }

                    }
                }
            }
            else if (action == ActionStaticInit)
            {
                if (pInitializerOpt)
                {
                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
                    PrintCodeOptions options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
                }
                else
                {
                    if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                    {
                        StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
                    }
                    else
                    {
                        StrBuilder_AppendFmt(fp, "/*%s=*/0", pInitExpressionText);
                    }
                }
            }
        }
    }
    else if (pMainSpecifier->Type == TStructUnionSpecifier_ID)
    {
        TStructUnionSpecifier * pStructUnionSpecifier =
            (TStructUnionSpecifier *)pMainSpecifier;

        
        bool bComplete = false;


        bComplete = FindHighLevelFunction(program,
            options,
            pSpecifierQualifierList,
            pDeclatator,                        
            pArgsOpt,
            pInitializerOpt,
            pInitExpressionText, 
            pszAutoPointerLenExpressionOpt,
            action,
            search,
            pStructUnionSpecifier->TagName,
            fp);

        
        
        
        
        
        if (!bComplete) 
        {
            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->TagName != NULL)
            {
                
                
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }

            bool bIsUnionTypes = pStructUnionSpecifier &&
                pStructUnionSpecifier->UnionSet.pHead != NULL;


            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->StructDeclarationList.Size > 0)
            {
                if (action == ActionDelete)
                {
                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
                    options->IdentationLevel++;
                }
                else if (action == ActionDestroy)
                {
                    if (bIsAutoPointerToObject)
                    {
                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                        options->IdentationLevel++;
                    }
                    else if (bIsAutoPointerToAutoPointer)
                    {

                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                        options->IdentationLevel++;

                        if (pszAutoPointerLenExpressionOpt)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;
                        }
                        else
                        {
                            
                        }

                    }

                }
                else if (action == ActionCreate)
                {
                    
                    
                    

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "struct %s* p = (struct %s*) %s(sizeof * p);",
                        pStructUnionSpecifier->TagName,
                        pStructUnionSpecifier->TagName,
                        GetMallocStr(program));

                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");
                    options->IdentationLevel++;
                }
                else if (action == ActionStaticInit)
                {
                    StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "{");

                    
                    
                    

                    
                    
                }

                if (bIsUnionTypes)
                {
                    if (action == ActionDelete)
                    {
                        options->IdentationLevel++;
                        UnionTypeDefault(program,
                            options,
                            pStructUnionSpecifier->TagName,
                            NULL,  
                            pInitExpressionText,
                            "Delete",
                            fp);
                        options->IdentationLevel--;
                    }
                    else if (action == ActionDestroyContent ||
                        action == ActionDestroy)
                    {
                        options->IdentationLevel++;
                        UnionTypeDefault(program,
                            options,
                            pStructUnionSpecifier->TagName,
                            NULL,  
                            pInitExpressionText,
                            "Destroy",
                            fp);
                        options->IdentationLevel--;
                    }
                    else
                    {

                    }
                }
                else
                {
                    int variableCount = 0;
                    
                    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
                    {




                        TAnyStructDeclaration * pAnyStructDeclaration =
                            pStructUnionSpecifier->StructDeclarationList.pItems[i];

                        TStructDeclaration * pStructDeclaration =
                            TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                        if (pStructDeclaration != NULL)
                        {
                            TStructDeclarator * pStructDeclarator =
                                pStructDeclaration->DeclaratorList.pHead;

                            StrBuilder strVariableName = STRBUILDER_INIT;
                            StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


                            while (pStructDeclarator)
                            {

                                if (action == ActionStaticInit && variableCount > 0)
                                {
                                    StrBuilder_Append(fp, ", ");
                                }
                                variableCount++;

                                
                                TInitializer * pStructMemberInitializer =
                                    pStructDeclarator->pInitializer;

                                TPrimaryExpressionValue initializerExpression;
                                TPrimaryExpressionValue_Init(&initializerExpression);


                                StrBuilder_Clear(&strVariableName);
                                StrBuilder_Clear(&strPonterSizeExpr);

                                const char * structDeclaratorName =
                                    TDeclarator_GetName(pStructDeclarator->pDeclarator);
                                if (action != ActionStaticInit)
                                {
                                    if (pInitExpressionText)
                                        StrBuilder_Set(&strVariableName, pInitExpressionText);


                                    if (bIsAutoPointerToAutoPointer)
                                    {
                                        if (pszAutoPointerLenExpressionOpt)
                                        {
                                            StrBuilder_Append(&strVariableName, "[i]");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strVariableName, "[0]");
                                        }
                                    }

                                    if (bIsPointer)
                                    {
                                        StrBuilder_Append(&strVariableName, "->");
                                    }
                                    else
                                    {
                                        StrBuilder_Append(&strVariableName, ".");
                                    }
                                }
                                else
                                {
                                    StrBuilder_Append(&strVariableName, ".");
                                }

                                StrBuilder_Append(&strVariableName, structDeclaratorName);


                                Action action2 = action;
                                if (action == ActionDestroyContent ||
                                    action == ActionDelete)
                                {
                                    
                                    action2 = ActionDestroy;
                                }
                                else if (action == ActionInitContent)
                                {

                                    TParameter * pParameter = NULL;
                                    if (pArgsOpt)
                                    {
                                        pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                        if (pParameter != NULL)
                                        {
                                            pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                            initializerExpression.token = TK_IDENTIFIER;
                                            PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                        }
                                    }

                                    action2 = ActionInit;
                                }
                                else if (action == ActionCreate)
                                {
                                    TParameter * pParameter = NULL;
                                    if (pArgsOpt)
                                    {
                                        pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                        if (pParameter != NULL)
                                        {
                                            pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                            initializerExpression.token = TK_IDENTIFIER;
                                            PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                        }
                                    }

                                    action2 = ActionInit;
                                }

                                if (action2 == ActionDestroy)
                                {

                                    
                                    
                                    
                                    
                                    
                                    


                                    const char * pszSize =
                                        TPointerList_GetSize(&pStructDeclarator->pDeclarator->PointerList);
                                    if (pszSize)
                                    {
                                        if (pInitExpressionText)
                                            StrBuilder_Set(&strPonterSizeExpr, pInitExpressionText);

                                        if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                                        {
                                            StrBuilder_Append(&strPonterSizeExpr, "->");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strPonterSizeExpr, ".");
                                        }
                                        StrBuilder_Append(&strPonterSizeExpr, pszSize);
                                    }
                                    else
                                    {
                                        
                                    }
                                }

                                
                                InstanciateDestroy2(program,
                                    options,
                                    &pStructDeclaration->SpecifierQualifierList,
                                    pStructDeclarator->pDeclarator,
                                    pStructMemberInitializer,
                                    NULL, 
                                    strVariableName.c_str,
                                    strPonterSizeExpr.c_str,
                                    action2,
                                    SearchAll,
                                    pbHasInitializers,
                                    fp);



                                
                                TPrimaryExpressionValue_Destroy(&initializerExpression);

                                pStructDeclarator = (pStructDeclarator)->pNext;
                            }

                            StrBuilder_Destroy(&strVariableName);
                            StrBuilder_Destroy(&strPonterSizeExpr);

                        }
                    }
                }

                if (action == ActionDestroy)
                {
                    if (bIsAutoPointerToObject)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                    }
                    else if (bIsAutoPointerToAutoPointer)
                    {
                        if (pszAutoPointerLenExpressionOpt)
                        {
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); 
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        }


                        
                    }
                }
                else if (action == ActionDestroyContent)
                {
                    if (bIsAutoPointerToAutoPointer)
                    {
                        
                        
                        
                        
                    }
                }
                else if (action == ActionDelete)
                {
                    if (bIsUnionTypes)
                    {

                    }
                    else
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                }
                else if (action == ActionCreate)
                {
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "}");

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "return p;");
                }
                else if (action == ActionStaticInit)
                {
                    StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "}");

                    
                    
                    
                    
                    
                }
            }
            else
            {
                
                StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
            }
        }

    }
    else if (pMainSpecifier->Type == TEnumSpecifier_ID)
    {
        TEnumSpecifier * pEnumSpecifier =
            TDeclarationSpecifier_As_TEnumSpecifier(pMainSpecifier);


        
        if (action == ActionDestroy)
        {
            if (bIsAutoPointerToObject)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else if (bIsAutoPointerToAutoPointer)
            {
                
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else
            {
                
            }
        }
        else if (action == ActionInit)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";\n");
            }
            else
            {
                
                const char * firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
                }
                else
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
                }
            }

        }
        else if (action == ActionInitContent)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";");
            }
            else
            {
                
                const char * firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "*%s = %s;", pInitExpressionText, GetNullStr(program));
                }
                else
                {

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
                }
            }
        }
        else if (action == ActionStaticInit)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers *)pSpecifierQualifierList, pInitializerOpt, fp);
            }
            else
            {
                
                const char * firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
                }
                else
                {
                    StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, firstValue);
                }
            }
        }
    }
    else
    {
        
    }

}


TStructUnionSpecifier * GetStructSpecifier(TProgram * program, TDeclarationSpecifiers * specifiers)
{
    if (specifiers == NULL)
        return NULL;

    TStructUnionSpecifier * pTStructUnionSpecifier =
        TDeclarationSpecifier_As_TStructUnionSpecifier(specifiers->pData[0]);

    TSingleTypeSpecifier * pSingleTypeSpecifier =
        TDeclarationSpecifier_As_TSingleTypeSpecifier(specifiers->pData[0]);

    if (pTStructUnionSpecifier == NULL)
    {
        if (pSingleTypeSpecifier != NULL &&
            pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            const char * typedefName = pSingleTypeSpecifier->TypedefName;

            TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
            if (pDeclaration)
            {
                if (pDeclaration->Specifiers.Size > 1)
                {
                    pTStructUnionSpecifier =
                        TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pData[1]);
                }
            }
        }
    }

    
    if (pTStructUnionSpecifier &&
        pTStructUnionSpecifier->TagName != NULL)
    {
        pTStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, pTStructUnionSpecifier->TagName);
    }
    else  if (pSingleTypeSpecifier != NULL &&
        pSingleTypeSpecifier->Token2 == TK_STRUCT)
    {
        
        pTStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, pSingleTypeSpecifier->TypedefName);
    }

    return pTStructUnionSpecifier;
}













#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#include <direct.h>

#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext)
{
    const char* end;  
    const char* p;       
    const char* s;       

                         
    if (path[0] && path[1] == ':')
    {
        if (drv)
        {
            *drv++ = *path++;
            *drv++ = *path++;
            *drv = '\0';
        }
    }
    else if (drv)
        *drv = '\0';

     
    for (end = path; *end && *end != ':'; )
        end++;

     
    for (p = end; p > path && *--p != '\\' && *p != '/'; )
        if (*p == '.')
        {
            end = p;
            break;
        }

    if (ext)
        for (s = end; (*ext = *s++); )
            ext++;

     
    for (p = end; p > path; )
        if (*--p == '\\' || *p == '/')
        {
            p++;
            break;
        }

    if (name)
    {
        for (s = p; s < end; )
            *name++ = *s++;

        *name = '\0';
    }

    if (dir)
    {
        for (s = path; s < p; )
            *dir++ = *s++;

        *dir = '\0';
    }
}

void MkDir(char* path)
{
#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
    _mkdir(path);
#else
    mkdir(path, 0777);
#endif
}

void MakePath(char* path, char* drv, char* dir, char* name, char* ext)
{
    if (drv && drv[0] != '\0')
    {
        while (*drv)
        {
            *path = *drv;
            path++;
            drv++;
        }
        
        
       
       
    }

    if (dir && dir[0] != '\0')
    {
        while (*dir)
        {
            *path = *dir;
            path++;
            dir++;
        }
        
         
    }

    while (*name)
    {
        *path = *name;
        path++;
        name++;
    }

    
    

    while (*ext)
    {
        *path = *ext;
        path++;
        ext++;
    }
    *path = '\0';
}

bool IsInPath(const char * filePath, const char* path)
{
    while (*path)
    {
        if (toupper(*path) != toupper(*filePath))
        {
            return false;
        }

        if (*path == '\0')
            break;

        path++;
        filePath++;
    }

    return true;
}

bool IsFullPath(const char*  path)
{
    if (path != NULL)
    {
        if ((path[0] >= 'a' && path[0] <= 'z') ||
            (path[0] >= 'A' && path[0] <= 'Z'))
        {
            if (path[1] == ':')
            {
                if (path[2] == '\\')
                {
                    
                    const char* p = &path[2];

                    while (*p)
                    {
                        if (*p == '.' && *(p - 1) == '\\')
                        {
                            return false;
                        }

                        p++;
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

bool FileExists(const char* fullPath)
{
    bool bFileExists = false;
    FILE* fp = fopen(fullPath, "rb");

    if (fp)
    {
        bFileExists = true;
        fclose(fp);
    }

    return bFileExists;
}

void GetFullDirS(const char* fileName, char* out, int len)
{
    char buffer[CPRIME_MAX_PATH];

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

    _fullpath(
        buffer,
        fileName,
        CPRIME_MAX_PATH);


#else
    realpath(fileName, buffer);
#endif

    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(buffer, drive, dir, fname, ext); 
    
    
    strcpy(out, drive);
    strcat(out, dir);
}


void GetFullDir(const char* fileName, char** out)
{
    char buffer[CPRIME_MAX_PATH];

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

    _fullpath(
        buffer,
        fileName,
        CPRIME_MAX_PATH);


#else
    realpath(fileName, buffer);
#endif

    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(buffer, drive, dir, fname, ext); 
    StrBuilder s;
    StrBuilder_Init(&s);
    StrBuilder_Append(&s, drive);
    StrBuilder_Append(&s, dir);
    *out = StrBuilder_Release(&s);
    
    StrBuilder_Destroy(&s);
}


void GetFullPath(const char* fileName, char** out)
{
    char buffer[CPRIME_MAX_PATH];

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)


    _fullpath(
        buffer,
        fileName,
        CPRIME_MAX_PATH);

#else
    realpath(fileName, buffer);
#endif

    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(buffer, drive, dir, fname, ext); 
    StrBuilder s = STRBUILDER_INIT;

    StrBuilder_Append(&s, drive);
    StrBuilder_Append(&s, dir);
    StrBuilder_Append(&s, fname);
    StrBuilder_Append(&s, ext);
    *out = StrBuilder_Release(&s);
    StrBuilder_Destroy(&s);
}

void GetFullPathS(const char* fileName, char* out)
{
    char buffer[CPRIME_MAX_PATH];

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)


    _fullpath(
        buffer,
        fileName,
        CPRIME_MAX_PATH);

#else
    realpath(fileName, buffer);
#endif

    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(buffer, drive, dir, fname, ext); 

    strcpy(out, drive);
    strcat(out, dir);
    strcat(out, fname);
    strcat(out, ext);
    
}





struct PrintXMLContext
{
    FILE * fp;
};


void PrintText(struct PrintXMLContext * ctx, const char * text)
{
    while (*text)
    {
        switch (*text)
        {
            case '&':
                fprintf(ctx->fp, "&amp;");
                break;
            case '<':
                fprintf(ctx->fp, "&lt;");
                break;
            case '>':
                fprintf(ctx->fp, "&gt;");
                break;
            case '\'':
                fprintf(ctx->fp, "&apos;");
                break;
            case '"':
                fprintf(ctx->fp, "&quot;");
                break;
            default:
                fprintf(ctx->fp, "%c", *text);
                break;
        }
        text++;
    }

}

void Print(struct PrintXMLContext * ctx, const char * format, ...)
{
    va_list argList;

    va_start(argList, format);
    vfprintf(ctx->fp, format, argList);
    va_end(argList);
}

void PrintLn(struct PrintXMLContext * ctx, const char * format, ...)
{
    va_list argList;

    va_start(argList, format);
    vfprintf(ctx->fp, format, argList);
    va_end(argList);


    fprintf(ctx->fp, "\n");
}
void TDeclarator_PrintXML(TDeclarator * p,
                          struct PrintXMLContext * ctx);

void TDeclarationSpecifiers_PrintXML(TDeclarationSpecifiers * p,
                                     struct PrintXMLContext * ctx);

void TStructDeclaration_PrintXML(TStructDeclaration * p, struct PrintXMLContext * ctx);

void TAnyStructDeclaration_PrintXML(TAnyStructDeclaration * p, struct PrintXMLContext * ctx);
void TTypeQualifier_PrintXML(TTypeQualifier * p, struct PrintXMLContext * ctx);


int HasItemsToPrint(TScannerItemList * list)
{
     
    return 0;
}

void TScannerItemList_PrintXML(TScannerItemList * list,
                               struct PrintXMLContext * ctx)
{

    if (HasItemsToPrint(list))
    {
        PrintLn(ctx, "<pr>");
        struct ScannerItem * pCurrent = list->pHead;
        while (pCurrent)
        {
            const char * name = TokenToString(pCurrent->token);
            switch (pCurrent->token)
            {
                case TK_PRE_INCLUDE:
                    PrintLn(ctx, "<%s>", name);
                    PrintText(ctx, pCurrent->lexeme.c_str);
                    PrintLn(ctx, "</%s>", name);
                    break;
                case TK_MACRO_CALL:
                    PrintLn(ctx, "<%s>", name);
                    PrintText(ctx, pCurrent->lexeme.c_str);
                    PrintLn(ctx, "</%s>", name);
                    break;
                case TK_FILE_EOF:
                    PrintLn(ctx, "<TK_FILE_EOF/>");
                    break;
                case TK_MACRO_EOF:
                    PrintLn(ctx, "<TK_MACRO_EOF/>");
                    break;
                    
                      
                        
                default:
                    
                    break;
            }
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</pr>");
    }
}

void TBinaryExpression_PrintXML(TBinaryExpression * p, struct PrintXMLContext * ctx)
{
}

void TPrimaryExpressionLambda_PrintXML(TPrimaryExpressionLambda * p, struct PrintXMLContext * ctx)
{
}
void TUnaryExpressionOperator_PrintXML(TUnaryExpressionOperator * p, struct PrintXMLContext * ctx)
{
}
void TCastExpressionType_PrintXML(TCastExpressionType * p, struct PrintXMLContext * ctx)
{
}
void TPrimaryExpressionValue_PrintXML(TPrimaryExpressionValue * p, struct PrintXMLContext * ctx)
{
}

void TPostfixExpressionCore_PrintXML(TPostfixExpressionCore * p, struct PrintXMLContext * ctx)
{
}

void TPrimaryExpressionLiteral_PrintXML(TPrimaryExpressionLiteral * p, struct PrintXMLContext * ctx)
{
}

void TTernaryExpression_PrintXML(TTernaryExpression * p, struct PrintXMLContext * ctx)
{
}

void TExpression_PrintXML(TExpression * p, struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TBinaryExpression_ID:
            TBinaryExpression_PrintXML((TBinaryExpression*)p, ctx);
        break;
        case TPrimaryExpressionLambda_ID:
            TPrimaryExpressionLambda_PrintXML((TPrimaryExpressionLambda*)p, ctx);
        break;
        case TUnaryExpressionOperator_ID:
            TUnaryExpressionOperator_PrintXML((TUnaryExpressionOperator*)p, ctx);
        break;
        case TCastExpressionType_ID:
            TCastExpressionType_PrintXML((TCastExpressionType*)p, ctx);
        break;
        case TPrimaryExpressionValue_ID:
            TPrimaryExpressionValue_PrintXML((TPrimaryExpressionValue*)p, ctx);
        break;
        case TPostfixExpressionCore_ID:
            TPostfixExpressionCore_PrintXML((TPostfixExpressionCore*)p, ctx);
        break;
        case TPrimaryExpressionLiteral_ID:
            TPrimaryExpressionLiteral_PrintXML((TPrimaryExpressionLiteral*)p, ctx);
        break;
        case TTernaryExpression_ID:
            TTernaryExpression_PrintXML((TTernaryExpression*)p, ctx);
        break;
        default:
        break;
    }
}

void TForStatement_PrintXML(TForStatement * p, struct PrintXMLContext * ctx)
{
}

void TJumpStatement_PrintXML(TJumpStatement * p, struct PrintXMLContext * ctx)
{
}


void TExpressionStatement_PrintXML(TExpressionStatement * p, struct PrintXMLContext * ctx)
{
}


void TIfStatement_PrintXML(TIfStatement * p, struct PrintXMLContext * ctx)
{
}


void TWhileStatement_PrintXML(TWhileStatement * p, struct PrintXMLContext * ctx)
{
}


void TSwitchStatement_PrintXML(TSwitchStatement * p, struct PrintXMLContext * ctx)
{
}


void TAsmStatement_PrintXML(TAsmStatement * p, struct PrintXMLContext * ctx)
{
}


void TDoStatement_PrintXML(TDoStatement * p, struct PrintXMLContext * ctx)
{
}


void TLabeledStatement_PrintXML(TLabeledStatement * p, struct PrintXMLContext * ctx)
{
}

void TCompoundStatement_PrintXML(TCompoundStatement * p, struct PrintXMLContext * ctx)
{
}

void TStatement_PrintXML(TStatement * p, struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TForStatement_ID:
            TForStatement_PrintXML((TForStatement*)p, ctx);
        break;
        case TJumpStatement_ID:
            TJumpStatement_PrintXML((TJumpStatement*)p, ctx);
        break;
        case TExpressionStatement_ID:
            TExpressionStatement_PrintXML((TExpressionStatement*)p, ctx);
        break;
        case TIfStatement_ID:
            TIfStatement_PrintXML((TIfStatement*)p, ctx);
        break;
        case TWhileStatement_ID:
            TWhileStatement_PrintXML((TWhileStatement*)p, ctx);
        break;
        case TSwitchStatement_ID:
            TSwitchStatement_PrintXML((TSwitchStatement*)p, ctx);
        break;
        case TAsmStatement_ID:
            TAsmStatement_PrintXML((TAsmStatement*)p, ctx);
        break;
        case TDoStatement_ID:
            TDoStatement_PrintXML((TDoStatement*)p, ctx);
        break;
        case TLabeledStatement_ID:
            TLabeledStatement_PrintXML((TLabeledStatement*)p, ctx);
        break;
        case TCompoundStatement_ID:
            TCompoundStatement_PrintXML((TCompoundStatement*)p, ctx);
        break;
        default:
        break;
    }
}

void TGroupDeclaration_PrintXML(TGroupDeclaration * p,
                                struct PrintXMLContext * ctx)
{
}

void TStaticAssertDeclaration_PrintXML(TStaticAssertDeclaration * p,
                                       struct PrintXMLContext * ctx)
{
}
void TParameter_PrintXML(TParameter * p, struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<parameter>");
    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TDeclarator_PrintXML(&p->Declarator, ctx);
    PrintLn(ctx, "</parameter>");
}


void TParameterList_PrintXML(TParameterList * p, struct PrintXMLContext * ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<parameter-list>");
        TParameter * pCurrent = p->pHead;
        while (pCurrent)
        {
            TParameter_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</parameter-list>");
    }
}

void TParameterTypeList_PrintXML(TParameterTypeList * p,
                                 struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<parameter-type-list>");
    TParameterList_PrintXML(&p->ParameterList, ctx);
    PrintLn(ctx, "</parameter-type-list>");
}

void TDirectDeclarator_PrintXML(TDirectDeclarator * p,
                                struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<direct-declarator>");
    if (p->Identifier)
    {
        PrintLn(ctx, "<id>");
        PrintText(ctx, p->Identifier);
        PrintLn(ctx, "</id>");
    }
    else  if (p->pDeclarator)
    {
        TDeclarator_PrintXML(p->pDeclarator, ctx);
    }


    if (p->DeclaratorType == TDirectDeclaratorTypeArray)
    {
    }
    else  if (p->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        TParameterTypeList_PrintXML(&p->Parameters, ctx);
    }

    if (p->pDirectDeclarator)
    {
        TDirectDeclarator_PrintXML(p->pDirectDeclarator, ctx);
    }
    
    PrintLn(ctx, "</direct-declarator>");
}



void TTypeQualifierList_PrintXML(TTypeQualifierList * p,
                                 struct PrintXMLContext * ctx)
{
    if (p->Size)
    {
        PrintLn(ctx, "<qualifiers>");
        for (int i = 0; i < p->Size; i++)
        {
            TTypeQualifier_PrintXML(p->Data[i], ctx);
        }
        PrintLn(ctx, "</qualifiers>");
    }
}

void TPointer_PrintXML(TPointer * p,
                       struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<pointer>");

    TTypeQualifierList_PrintXML(&p->Qualifier, ctx);

    PrintLn(ctx, "</pointer>");
}
void TPointerList_PrintXML(TPointerList * p,
                           struct PrintXMLContext * ctx)
{
    TPointer * pCurrent = p->pHead;
    if (pCurrent)
    {
        PrintLn(ctx, "<pointer-list>");
        while (pCurrent)
        {
            TPointer_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</pointer-list>");
    }
}

void TDeclarator_PrintXML(TDeclarator * p,
                          struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<declarator>");
    TDirectDeclarator_PrintXML(p->pDirectDeclarator, ctx);
    TPointerList_PrintXML(&p->PointerList, ctx);
    PrintLn(ctx, "</declarator>");
}

void TInitDeclarator_PrintXML(TInitDeclarator * p,
                              struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<init-declarator>");
    TDeclarator_PrintXML(p->pDeclarator, ctx);
    PrintLn(ctx, "</init-declarator>");
}

void TInitDeclaratorList_PrintXML(TInitDeclaratorList * p,
                                  struct PrintXMLContext * ctx)
{
    TInitDeclarator * pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitDeclarator_PrintXML(pCurrent, ctx);
        pCurrent = pCurrent->pNext;
    }
}

void TDeclaration_PrintXML(TDeclaration * p, struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<declaration>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);

    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TInitDeclaratorList_PrintXML(&p->InitDeclaratorList, ctx);
    TScannerItemList_PrintXML(&p->ClueList1, ctx);
    PrintLn(ctx, "</declaration>");
}


void TSingleTypeSpecifier_PrintXML(TSingleTypeSpecifier * p,
                                   struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<single-type-specifier>");

    TScannerItemList_PrintXML(&p->ClueList0, ctx);

    if (p->TypedefName)
    {
        PrintText(ctx, p->TypedefName);
    }
    else
    {
        PrintText(ctx, TokenToString(p->Token2));
    }

    PrintLn(ctx, "</single-type-specifier>");
}

void TTypeQualifier_PrintXML(TTypeQualifier * p, struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<type-qualifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintLn(ctx, "</type-qualifier>");
}

void TStructDeclarationList_PrintXML(TStructDeclarationList * p, struct PrintXMLContext * ctx)
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration * pCurrent = p->pItems[i];
        TAnyStructDeclaration_PrintXML(pCurrent, ctx);
    }
}

void TStructUnionSpecifier_PrintXML(TStructUnionSpecifier * p, struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<struct-union-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    TStructDeclarationList_PrintXML(&p->StructDeclarationList, ctx);
    PrintLn(ctx, "</struct-union-specifier>");


}

void TStorageSpecifier_PrintXML(TStorageSpecifier * p,
                                struct PrintXMLContext * ctx)
{
    Print(ctx, "<storage-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</storage-specifier>");
}


void TAtomicTypeSpecifier_PrintXML(TAtomicTypeSpecifier * p,
                                   struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<atomic-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    
    PrintLn(ctx, "</atomic-specifier>");


}


void TAlignmentSpecifier_PrintXML(TAlignmentSpecifier * p,
                                  struct PrintXMLContext * ctx)
{
    
}



void TFunctionSpecifier_PrintXML(TFunctionSpecifier * p,
                                 struct PrintXMLContext * ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
}

void TEnumSpecifier_PrintXML(TEnumSpecifier * p, struct PrintXMLContext * ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
}


void TStructDeclaratorList_PrintXML(TStructDeclaratorList * p, struct PrintXMLContext * ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<struct-declarator-list>");
        TInitDeclarator * pCurrent = p->pHead;
        while (pCurrent)
        {
            TInitDeclarator_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</struct-declarator-list>");
    }
}

void TStructDeclaration_PrintXML(TStructDeclaration * p, struct PrintXMLContext * ctx)
{
    PrintLn(ctx, "<struct-declaration>");
    TStructDeclaratorList_PrintXML(&p->DeclaratorList, ctx);
    PrintLn(ctx, "</struct-declaration>");
}

void TAnyStructDeclaration_PrintXML(TAnyStructDeclaration * p, struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TStaticAssertDeclaration_ID:
            TStaticAssertDeclaration_PrintXML((TStaticAssertDeclaration*)p, ctx);
        break;
        case TStructDeclaration_ID:
            TStructDeclaration_PrintXML((TStructDeclaration*)p, ctx);
        break;
        default:
        break;
    }
}
void TTypeSpecifier_PrintXML(TTypeSpecifier * p, struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TStructUnionSpecifier_ID:
            TStructUnionSpecifier_PrintXML((TStructUnionSpecifier*)p, ctx);
        break;
        case TAtomicTypeSpecifier_ID:
            TAtomicTypeSpecifier_PrintXML((TAtomicTypeSpecifier*)p, ctx);
        break;
        case TSingleTypeSpecifier_ID:
            TSingleTypeSpecifier_PrintXML((TSingleTypeSpecifier*)p, ctx);
        break;
        case TEnumSpecifier_ID:
            TEnumSpecifier_PrintXML((TEnumSpecifier*)p, ctx);
        break;
        default:
        break;
    }
}

void TDeclarationSpecifier_PrintXML(TDeclarationSpecifier * p, struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TTypeQualifier_ID:
            TTypeQualifier_PrintXML((TTypeQualifier*)p, ctx);
        break;
        case TStructUnionSpecifier_ID:
            TStructUnionSpecifier_PrintXML((TStructUnionSpecifier*)p, ctx);
        break;
        case TStorageSpecifier_ID:
            TStorageSpecifier_PrintXML((TStorageSpecifier*)p, ctx);
        break;
        case TAtomicTypeSpecifier_ID:
            TAtomicTypeSpecifier_PrintXML((TAtomicTypeSpecifier*)p, ctx);
        break;
        case TSingleTypeSpecifier_ID:
            TSingleTypeSpecifier_PrintXML((TSingleTypeSpecifier*)p, ctx);
        break;
        case TAlignmentSpecifier_ID:
            TAlignmentSpecifier_PrintXML((TAlignmentSpecifier*)p, ctx);
        break;
        case TFunctionSpecifier_ID:
            TFunctionSpecifier_PrintXML((TFunctionSpecifier*)p, ctx);
        break;
        case TEnumSpecifier_ID:
            TEnumSpecifier_PrintXML((TEnumSpecifier*)p, ctx);
        break;
        default:
        break;
    }
}

void TDeclarationSpecifiers_PrintXML(TDeclarationSpecifiers * p,
                                     struct PrintXMLContext * ctx)
{
    if (p->Size > 0)
    {
        PrintLn(ctx, "<especifiers>");
        for (int i = 0; i < p->Size; i++)
        {
            TDeclarationSpecifier_PrintXML(p->pData[i], ctx);
        }
        PrintLn(ctx, "</especifiers>");
    }


}



void TEofDeclaration_PrintXML(TEofDeclaration * p,
                              struct PrintXMLContext * ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintLn(ctx, "<eof-declaration/>");
}

void TAnyDeclaration_PrintXML(TAnyDeclaration * p,
                              struct PrintXMLContext * ctx) /*@default*/
{
    switch (p->Type)
    {
        case TGroupDeclaration_ID:
            TGroupDeclaration_PrintXML((TGroupDeclaration*)p, ctx);
        break;
        case TStaticAssertDeclaration_ID:
            TStaticAssertDeclaration_PrintXML((TStaticAssertDeclaration*)p, ctx);
        break;
        case TDeclaration_ID:
            TDeclaration_PrintXML((TDeclaration*)p, ctx);
        break;
        case TEofDeclaration_ID:
            TEofDeclaration_PrintXML((TEofDeclaration*)p, ctx);
        break;
        default:
        break;
    }
}


void TProgram_PrintAstToXML(TProgram * pProgram,
                            const char * fileName,
                            const char * inputFileName)
{
    FILE * fp = fopen(fileName, "w");
    

    struct PrintXMLContext ctx = { 0 };
    ctx.fp = fp;
    bool b = false;
    fprintf(fp, "<AST>\n");

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        TAnyDeclaration * pItem = pProgram->Declarations.pItems[i];
        TAnyDeclaration_PrintXML(pItem, &ctx);
    }

    fprintf(fp, "</AST>");

    fclose(fp);
}



