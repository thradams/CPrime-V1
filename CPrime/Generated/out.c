


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

//#define List_IsLastItem(pList, pItem) ((pList)->pTail == (pItem))






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
    //name to identify this stream
    String* /*@auto*/ NameOrFullPath;
    String* /*@auto*/ FullDir2;
     
    //stream content and length
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
//


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
    CHAR1, // '/' ,
    CHARACTER_TABULATION,// = '\t';
    TK_PREPROCESSOR,
    TK_ERROR, //reservado para erro


    //
    TK_EXCLAMATION_MARK,// = '!';
    TK_QUOTATION_MARK,// = '\"';
    TK_NUMBER_SIGN,// = '#';

    TK_DOLLAR_SIGN,// = '$';
    TK_PERCENT_SIGN,// = '%';
    TK_AMPERSAND,// = '&';
    TK_APOSTROPHE,// = '\'';
    TK_LEFT_PARENTHESIS,// = '(';
    TK_RIGHT_PARENTHESIS,// = ')';
    TK_ASTERISK,// = '*';
    TK_PLUS_SIGN,// = '+';
    TK_COMMA,// = ',';
    TK_HYPHEN_MINUS,// = '-';
    TK_HYPHEN_MINUS_NEG,// = '-'; //nao retorna no basic string mas eh usado para saber se eh - unario
    TK_FULL_STOP,// = '.';
    TK_SOLIDUS,// = '/';

    TK_COLON,// = ':';
    TK_SEMICOLON,// = ';';
    TK_LESS_THAN_SIGN,// = '<';
    TK_EQUALS_SIGN,// = '=';
    TK_GREATER_THAN_SIGN,// = '>';
    TK_QUESTION_MARK,// = '\?';
    TK_COMMERCIAL_AT,// = '@';

    TK_LEFT_SQUARE_BRACKET,// = '[';
    REVERSE_SOLIDUS,// = '\\';
    TK_RIGHT_SQUARE_BRACKET,// = ']';
    TK_CIRCUMFLEX_ACCENT,// = '^';
    TK_LOW_LINE,// = '_';
    TK_GRAVE_ACCENT,// = '`';

    TK_LEFT_CURLY_BRACKET,// = '{';
    TK_VERTICAL_LINE,// = '|';
    TK_RIGHT_CURLY_BRACKET,// = '}';
    TK_TILDE, // ~

    ////////////////////////////////////////
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
    ////////////////
    //Microsoft - specific
    TK__INT8,
    TK__INT16,
    TK__INT32,
    TK__INT64,
    TK__WCHAR_T,
    ////////////////
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
    TK__INLINE,//ms
    TK__FORCEINLINE, //ms
    TK__NORETURN,
    TK__ALIGNAS,
    TK__GENERIC,
    TK__IMAGINARY,
    TK__ALINGOF,

    ///
    TK__ASM, //visual c++    

    //Tokens para linhas do pre processador
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
    //fim tokens preprocessador
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

    //true antes do 1 token de cada linha
    bool bLineStart;
    bool bMacroExpanded;
    int FileIndex;
    Tokens m_Token;
    struct BasicScanner * pPrevious;

} BasicScanner;


const char * BasicScanner_Lexeme(BasicScanner * scanner);
bool        BasicScanner_IsLexeme(BasicScanner * scanner, const char * psz);
//void        BasicScanner_Match(BasicScanner* scanner);
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





//////////////
typedef struct
{
    Buckets buckets;
    int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

bool MultiMap_Init(MultiMap * map, int nBuckets);
void MultiMap_Destroy(MultiMap * map, void(*pfDestroyData)(void *));

//Adiciona outro item no mapa sem testar se ja existe
bool MultiMap_Add(MultiMap * map, const char * key, void * data);

//Retorna todo bucket que tem o mesm hash
//Ainda � preciso percorrer para saber se sao da mesma key
//Varias entradas para mesma key
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


///////////////////////////////


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

    //imprime na forma para declarar um tipo, remove o resto
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
    PPState_NONE, // inclui
    PPState_I1,   // inclui
    PPState_I0,
    PPState_E0,
    PPState_E1, // inclui
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
    //Stack de basicscanner
    BasicScannerStack stack;

    //Mapa dos defines
    struct MacroMap  Defines2;

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

    struct Options * pOptions;
    ///////////////////////////////////////////////////
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


//NOVA INTERFACE

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


/*
AST data structures
*/

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
    /*
    static_assert-declaration:
    _Static_assert ( constant-expression , string-literal ) ;
    */
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
    /*
    Marca fim de um arquivo
    */
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
    /*
    block-item-list:
    block-item
    block-item-list block-item
    */
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
    /*
    type-qualifier:
    const
    restrict
    volatile
    _Atomic
    */

    /*
    auto
    _size ( SizeIdentifier )
    */

    EType Type /*@=TTypeQualifier_ID*/;
    String * /*@auto*/ SizeIdentifier;
    Tokens Token;
    TScannerItemList ClueList0;

} TTypeQualifier;

void TTypeQualifier_Copy(TTypeQualifier * dest, TTypeQualifier * src);
bool TTypeQualifier_Compare(TTypeQualifier * p1, TTypeQualifier * p2);

typedef struct {
    /*
    type-qualifier-list:
    type-qualifier
    type-qualifier-list type-qualifier
    */

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
    TScannerItemList ClueList0; //do
    TScannerItemList ClueList1; //while
    TScannerItemList ClueList2; //(
    TScannerItemList ClueList3; //)
    TScannerItemList ClueList4; // ;

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
    TScannerItemList ClueList0; //if 
    TScannerItemList ClueList1; //(
    TScannerItemList ClueList2; //)
    TScannerItemList ClueList3; //else
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

/*block-item:
declaration
statement
*/
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
    /*
    pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
    */
    TTypeQualifierList Qualifier;
    struct TPointer * pNext;
    TScannerItemList ClueList0;
} TPointer;

TPointer * TPointer_Create(void);
void TPointer_Delete(TPointer * p);
void TPointer_Copy(TPointer * dest, TPointer * src);


typedef struct TPointerList
{
    /*
    pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
    */
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
    /*
    function-specifier:
    inline
    _Noreturn
    */
    EType Type  /*@=TFunctionSpecifier_ID*/;
    Tokens Token;
    TScannerItemList ClueList0;
} TFunctionSpecifier;


TFunctionSpecifier * TFunctionSpecifier_Create(void);
void TFunctionSpecifier_Delete(TFunctionSpecifier * p);
bool TFunctionSpecifier_Compare(TFunctionSpecifier * p1, TFunctionSpecifier * p2);

typedef struct
{
    /*
    storage-class-specifier:
    typedef
    extern
    static
    _Thread_local
    auto
    register
    */
    EType Type  /*@=TStorageSpecifier_ID*/;
    Tokens Token;
    TScannerItemList ClueList0;
} TStorageSpecifier;

TStorageSpecifier * TStorageSpecifier_Create(void);
void TStorageSpecifier_Delete(TStorageSpecifier * p);
bool TStorageSpecifier_Compare(TStorageSpecifier *p1, TStorageSpecifier *p2);

typedef struct
{
    /*
    alignment-specifier:
    _Alignas ( type-name )
    _Alignas ( constant-expression )
    */
    EType Type  /*@=TAlignmentSpecifier_ID*/;
    String * /*@auto*/ TypeName;
} TAlignmentSpecifier;

TAlignmentSpecifier * TAlignmentSpecifier_Create(void);
void TAlignmentSpecifier_Delete(TAlignmentSpecifier * p);


typedef struct TEnumerator
{
    /*
    enumerator:
    enumeration-constant
    enumeration-constant = constant-expression
    */
    struct TEnumerator * pNext;
    String * /*@auto*/ Name;
    TExpression * /*@auto*/   pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; // =
    TScannerItemList ClueList2; // ,
    bool bHasComma;
} TEnumerator;

TEnumerator * TEnumerator_Create(void);
void TEnumerator_Delete(TEnumerator * p);


typedef struct
{
    /*
    enumerator-list:
    enumerator
    enumerator-list, enumerator
    */
    TEnumerator * pHead, * pTail;
} TEnumeratorList;
void TEnumeratorList_Destroy(TEnumeratorList * p);
void TEnumeratorList_Init(TEnumeratorList * p);

typedef struct TEnumSpecifier
{
    /*
    enum-specifier:
    enum identifieropt { enumerator-list }
    enum identifieropt { enumerator-list , }
    enum identifier
    */

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
    /*
    void
    char
    short
    int
    long
    float
    double
    signed
    unsigned
    _Bool
    _Complex
    typedef-name
    */
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


/*
declaration-specifiers:
storage-class-specifier declaration-specifiersopt
type-specifier declaration-specifiersopt
type-qualifier declaration-specifiersopt
function-specifier declaration-specifiersopt
alignment-specifier declaration-specifiersopt
*/

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

/*
specifier-qualifier-list:
type-specifier specifier-qualifier-listopt
type-qualifier specifier-qualifier-listopt
*/
struct /*@<TTypeSpecifier | TTypeQualifier>*/ TSpecifierQualifier
{
    EType Type;
};


/*
specifier-qualifier-list:
type-specifier specifier-qualifier-listopt
type-qualifier specifier-qualifier-listopt
*/
typedef struct TSpecifierQualifier TSpecifierQualifier;
void TSpecifierQualifier_Delete(TSpecifierQualifier * p);

CAST(TSpecifierQualifier, TStorageSpecifier)
CAST(TSpecifierQualifier, TAlignmentSpecifier)
CAST(TSpecifierQualifier, TSingleTypeSpecifier)

CAST(TSpecifierQualifier, TTypeQualifier)
CAST(TSpecifierQualifier, TEnumSpecifier)


typedef struct {
    /*
    specifier-qualifier-list:
    type-specifier specifier-qualifier-listopt
    type-qualifier specifier-qualifier-listopt
    */
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
    /*
    declaration-specifiers:
    storage-class-specifier declaration-specifiersopt
    type-specifier declaration-specifiersopt
    type-qualifier declaration-specifiersopt
    function-specifier declaration-specifiersopt
    alignment-specifier declaration-specifiersopt
    */
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

//struct TStructUnionSpecifier;
typedef struct TStructUnionSpecifier TStructUnionSpecifier;

TStructUnionSpecifier* TDeclarationSpecifiers_GetCompleteStructUnionSpecifier(struct SymbolMap* pSymbolMap,
    TDeclarationSpecifiers* pDeclarationSpecifiers);

struct TParameter;
typedef struct TParameter TParameter;

typedef struct
{
    /*
    parameter-list:
    parameter-declaration
    parameter-list , parameter-declaration
    */

    TParameter * pHead, * pTail;
} TParameterList;

void TParameterList_Destroy(TParameterList * p);
void TParameterList_Init(TParameterList * p);
const char * TParameter_GetName(TParameter * p);
bool TParameter_IsDirectPointer(TParameter * p);

typedef struct TParameterTypeList
{
    /*
    parameter-type-list:
    parameter-list
    parameter-list , ...
    */
    TParameterList ParameterList;
    TScannerItemList ClueList0; //,
    TScannerItemList ClueList1; //...
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
    /*
    designator:
    [ constant-expression ]
    . identifier
    */
    String * /*@auto*/ Name;
    TExpression * /*@auto*/  pExpression;
    struct TDesignator * pNext;
    TScannerItemList ClueList0; //. ou [
    TScannerItemList ClueList1; //]
} TDesignator;


TDesignator * TDesignator_Create(void);
void TDesignator_Delete(TDesignator * p);


typedef struct
{
    /*
    designator-list:
    designator
    designator-list designator
    */
    TDesignator * /*@auto*/ pHead, * pTail;
} TDesignatorList;
void TDesignatorList_Destroy(TDesignatorList * p);
void TDesignatorList_Init(TDesignatorList * p);
void TDesignatorList_PushBack(TDesignatorList * p, TDesignator * pItem);

typedef struct TDesignation
{
    /*
    designation:
    designator-list =
    */
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
    /*
    initializer-list:
    designationopt initializer
    initializer-list , designationopt initializer
    */
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
    /*
    initializer-list:
    designationopt initializer
    initializer-list , designationopt initializer
    */

    TInitializerListItem * /*@auto*/ pHead, * pTail;
} TInitializerList;

void TInitializerList_Init(TInitializerList * p);
void TInitializerList_Destroy(TInitializerList * p);


typedef struct
{
    /*
    initializer:
    assignment-expression

    { initializer-list }    <-----representa esta parte
    { initializer-list ,}
    */
    /*
      {}
      default {}
      default { initializer-list }
      default { initializer-list ,}
    */

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
    /*
    initializer:
    assignment-expression

    { initializer-list }
    { initializer-list ,}
    */
    EType Type;
};
typedef struct TInitializer TInitializer;

CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;
typedef struct TDirectDeclarator TDirectDeclarator;

typedef struct TDeclarator
{
    /*
    declarator:
    pointeropt direct-declarator
    */

    /*
    abstract-declarator:
    pointer
    pointeropt direct-abstract-declarator
    */

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
    /*
    direct-declarator:
    identifier
    ( declarator )
    direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
    direct-declarator [ static type-qualifier-listopt assignment-expression ]
    direct-declarator [ type-qualifier-list static assignment-expression ]
    direct-declarator [ type-qualifier-listopt * ]
    direct-declarator ( parameter-type-list )
    direct-declarator ( identifier-listopt )
    */

    String * /*@auto*/ Identifier;
    TDeclarator * /*@auto*/ pDeclarator;
    struct TDirectDeclarator * /*@auto*/  pDirectDeclarator;
    TPosition Position;
    TParameterTypeList  Parameters;
    TExpression * /*@auto*/  pExpression;
    TDirectDeclaratorType DeclaratorType; //para diferenciar pois null nao basta []
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
} TDirectDeclarator;


TDirectDeclarator * TDirectDeclarator_Create();
void TDirectDeclarator_Delete(TDirectDeclarator * p);

typedef struct TInitDeclarator
{
    /*
    init-declarator:
    declarator
    declarator = initializer
    */
    TDeclarator * /*@auto*/  pDeclarator;
    TInitializer * /*@auto*/   pInitializer;
    struct TInitDeclarator * pNext;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; //defval
} TInitDeclarator;


TInitDeclarator * TInitDeclarator_Create();
void TInitDeclarator_Delete(TInitDeclarator * p);

typedef TInitDeclarator TStructDeclarator;


typedef struct TInitDeclaratorList
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */
    TInitDeclarator * pHead, * pTail;
} TInitDeclaratorList;

void TInitDeclaratorList_Destroy(TInitDeclaratorList * p);
void TInitDeclaratorList_Init(TInitDeclaratorList * p);
const char * TDeclarator_GetName(TDeclarator * p);
const char * TInitDeclarator_FindName(TInitDeclarator * p);


typedef struct TStructDeclaratorList
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */
    TInitDeclarator * /*@auto*/ pHead, * pTail;
} TStructDeclaratorList;


void TStructDeclaratorList_Destroy(TStructDeclaratorList * p);
void TStructDeclaratorList_Init(TStructDeclaratorList * p);
void TStructDeclaratorList_Add(TStructDeclaratorList * p, TInitDeclarator * pItem);


typedef struct TStructDeclaration
{
    /*
    struct-declaration:
    specifier-qualifier-list struct-declarator-listopt ;
    static_assert-declaration
    */

    EType Type  /*@=TStructDeclaration_ID*/;

    TSpecifierQualifierList SpecifierQualifierList;
    TStructDeclaratorList DeclaratorList;
    TScannerItemList ClueList1;
} TStructDeclaration;


TStructDeclaration * TStructDeclaration_Create();
void TStructDeclaration_Delete(TStructDeclaration * p);


/*
struct-declaration:
specifier-qualifier-list struct-declarator-listopt ;
static_assert-declaration
*/
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

    TScannerItemList ClueList0; // <
    TScannerItemList ClueList1; // > 
    //TScannerItemList ClueList2; //>

} TUnionSet;
void TUnionSet_Init(TUnionSet * p);
void TUnionSet_Destroy(TUnionSet * p);
void TUnionSet_PushBack(TUnionSet * p, TUnionSetItem * pItem);

typedef struct TStructUnionSpecifier
{
    /*
    struct-or-union-specifier:
    struct-or-union identifieropt { struct-declaration-list }
    struct-or-union identifier
    */

    /*
    struct-or-union-specifier:
    struct-or-union identifieropt { struct-declaration-list }
    struct-or-union union-set-opt identifier
    */

    EType Type  /*@=TStructUnionSpecifier_ID*/;
    TStructDeclarationList StructDeclarationList;
    String * /*@auto*/ TagName;

    Tokens Token;


    TUnionSet UnionSet;
    TScannerItemList ClueList0; //struct-or-union
    TScannerItemList ClueList1; //identifieropt
    TScannerItemList ClueList2; //{
    TScannerItemList ClueList3; //}


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
    /*
    declaration:
    declaration-specifiers init-declarator-listopt ;
    static_assert-declaration
    */

    /*
    declaration:
    declaration-specifiers init-declarator-listopt : identifier defaultopt;
    
    */

    EType Type  /*@=TDeclaration_ID*/;
    TDeclarationSpecifiers Specifiers;
    TInitDeclaratorList InitDeclaratorList;

    //se for funcao
    TCompoundStatement * /*@auto*/  pCompoundStatementOpt;

    int FileIndex;
    int Line;

    TScannerItemList ClueList0; //default FunctionTag
    TScannerItemList ClueList00; //:
    TScannerItemList ClueList001; //identifier

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
    /*
    parameter-declaration:
    declaration-specifiers declarator
    declaration-specifiers abstract-declaratoropt
    */

    struct TParameter * pNext;
    TDeclarationSpecifiers Specifiers;
    TDeclarator Declarator;
    TScannerItemList ClueList0; //, do parametro
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
    /*
    default identifier
    {
    }
    */
    EType Type  /*@=TGroupDeclaration_ID*/;
    TDeclarations Declarations;
    String * /*@auto*/ Identifier;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TGroupDeclaration;

TGroupDeclaration * TGroupDeclaration_Create();
void TGroupDeclaration_Delete(TGroupDeclaration * p);

//Coleta o resultado do parser
typedef struct
{
    //declaracoes
    TDeclarations Declarations;

    //arquivos na qual declaracao tem indice
    TFileArray Files2;

    //multimap dos simbolos
    //DeclarationsMap Symbols;
    struct SymbolMap GlobalScope;


    //Defines
    struct MacroMap Defines;

    StrBuilder sbPreDeclaration;

} TProgram;


void TProgram_Init(TProgram * p);
void TProgram_Destroy(TProgram * p);
TDeclaration * TProgram_GetFinalTypeDeclaration(TProgram * p, const char * typeName);
TDeclaration * TProgram_FindDeclaration(TProgram * p, const char * name);



typedef struct TTypeName
{
    /*
    type-name:
    specifier-qualifier-list abstract-declaratoropt
    */
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
    /*
    atomic-type-specifier:
    _Atomic ( type-name )
    */
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
    /*
    (6.5.1) primary-expression:
    identifier
    constant
    string-literal
    ( expression )
    generic-selection
    */

    EType Type /*@=TPrimaryExpressionValue_ID*/;
    Tokens token;
    String * /*@auto*/ lexeme;
    TExpression * /*@auto*/   pExpressionOpt; //( expression )
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
    TTypeName * /*@auto*/  pTypeName; /*typename*/

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
    TScannerItemList ClueList1; //sizeof (
    TScannerItemList ClueList2; //sizeof ( )
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
    TScannerItemList ClueList0; //[
    TScannerItemList ClueList1; //]
    TScannerItemList ClueList2; //(
    TScannerItemList ClueList3; //)
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

    ///////////
    //controle interno
    struct IntegerStack Stack;// = 0;
    bool bInclude;// = true;
    int IdentationLevel;
    //

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
                         TSpecifierQualifierList * pSpecifierQualifierList,//<-dupla para entender o tipo
                         TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
                         TInitializer * pInitializer,
                         TParameterTypeList * pArgsOpt,
                         const char * pInitExpressionText, //(x->p->i = 0)    
                         const char * pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                                                     //se passar null eh pq nao interessa
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
  // indica presenca de erro no parser
  bool bError;

  // mensagem de erro
  StrBuilder ErrorMessage;

  // scanner ja pr�-processado
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
#define EXECUTABLE_NAME "cprime"

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
        SplitPath(inputFileName, drive, dir, fname, ext); // C4996


        printf("Generating code for %s...\n", inputFileName);
        if (outputFileName[0] != '\0')
        {
            if (bPrintASTFile)
            {
                //TProgram_PrintAstToFile(&program, outputFileName, inputFileName);
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
                //faz um  arquivo com extensao json
                //MakePath(outc, drive, dir, fname, ".json");
                //TProgram_PrintAstToFile(&program, outc, inputFileName);
                MakePath(outc, drive, dir, fname, ".xml");
                TProgram_PrintAstToXML(&program, outc, inputFileName);
            }
            else
            {
                //gera em cima do proprio arquivo
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
    printf("-a                                    Output almagamation of input file\n");
    printf("-cx                                   Generate CX.\n");
    printf("-ca                                   Generated C annotated\n");
    printf("-removeComments                      Remove comments from output\n");
    printf("-build                                Compile all sources defined in inputfile\n");
    printf("-rbuild                               Build of all sources of input\n");
    printf("-sources                              Prints all sources used\n");
    printf("-noImplicitTag                       Prints all sources used\n");

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
    //AllTests();
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
        // configFileName = cxconfigFileFullPath;
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
    bool bBuild = false;
    bool bRecursiveBuild = false;
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
        else if (strcmp(option, "-build") == 0)
        {
            bBuild = true;
        }
        else if (strcmp(option, "-rbuild") == 0)
        {
            bRecursiveBuild = true;
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

    if (bBuild || bRecursiveBuild)
    {
        printf("Output dir : %s\n", outputDirFullPath);
        if (bBuild)
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

            //Cria o diretorio de ouput
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
        //fprintf(fp, "}");
        b = true;
    }

    b = TExpression_Print(p->pExpression1, "expr1", true, fp);
    //fprintf(fp, ",");
    b = TExpression_Print(p->pExpression2, "expr2", b, fp);
    //fprintf(fp, ",");
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
    //fprintf(fp, ",");
    //TExpression_Print(&p->Expression, false, fp);
    //fprintf(fp, "}");
    return true;
}


bool TJumpStatement_Print(TJumpStatement * p, bool b, FILE * fp)
{
    fprintf(fp, "\"type\":\"jump-statement\"");
    //fprintf(fp, ",");
    //fprintf(fp, "\"statement\": {");
    b = TExpression_Print(p->pExpression, "statement", false, fp);
    //fprintf(fp, "}");
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
            //assert(false);
            break;
    }

    return b;
}

bool TBlockItem_Print(TBlockItem * p, bool b, FILE * fp)
{
    if (p == NULL)
    {
        //assert(false);
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
            //assert(false);
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
            //assert(false);
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
    //b = TTypeQualifierList_Print(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
    //b = TTypeSpecifier_Print(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

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
        ////assert(false);
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

        //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
        break;

        CASE(TTernaryExpression) :
            b = TExpression_Print(((TTernaryExpression *)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression *)p)->pExpressionMiddle, "m-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression *)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"ternary\":\"%s\"", TokenToString(((TTernaryExpression *)p)->token));

        //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
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
                //ttypename_print pTUnaryExpressionOperator->TypeName


                //tem algo?
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
                {
                    TTypeName_Print(&pTUnaryExpressionOperator->TypeName, "", b, fp);
                    //fprintf(fp, "\"type\":{");
                    //b = TTypeQualifierList_Print(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
                    //b/ = TTypeSpecifier_Print(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

                    //if (b)
                    //{
                      //fprintf(fp, ",");
                    //}

                    //fprintf(fp, "\"declarator\":");
                    //b = TDeclarator_Print(&pTUnaryExpressionOperator->TypeName.Declarator, b, fp);

                    //fprintf(fp, "}");
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


            //fprintf(fp, ",\"cast\":{");
            TTypeName_Print(&pCastExpressionType->TypeName, "cast", b, fp);
            //b = TTypeQualifierList_Print(&pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
            //b = TTypeSpecifier_Print(pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

            //if (b)
            //{
              //fprintf(fp, ",");
            //}

            //fprintf(fp, "\"declarator\":");
            //b = TDeclarator_Print(&pCastExpressionType->TypeName.Declarator, b, fp);

            //fprintf(fp, "}");

        }
        break;

        default:

            //assert(false);
            break;
    }

    fprintf(fp, "}");
    return b;
}


bool TEnumerator_Print(TEnumerator * pTEnumerator, bool b, FILE * fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"name\":\"%s\"", pTEnumerator->Name);
    //fprintf(fp, ",");
    if (pTEnumerator->pExpression)
    {
        TExpression_Print(pTEnumerator->pExpression, "expr", true, fp);
    }
    else
    {
        //vou criar uma expressionp enum?
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

    //for (int i = 0; i < p->EnumeratorList.size; i++)
    int i = 0;
    ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
    {
        //TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

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
        //declaracao vazia: ;
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
            //TStructDeclaration_Print();
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

    //
    if (p->Name)
    {
        //.identifier
        fprintf(fp, "\"member-name\":\"%s\"", p->Name);
    }

    else
    {
        //[constant-expression]
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

            //fprintf(fp, "{");
            b = TExpression_Print((TExpression *)p, "initializer-expression", false, fp);
            //fprintf(fp, "}");
            break;

        case TInitializerListType_ID:
            fprintf(fp, "\"initializer\":");
            b = TInitializerList_Print(&((TInitializerListType *)p)->InitializerList, b, fp);
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}


bool TPointerList_Print(TPointerList * p, bool b, FILE * fp)
{
    b = false;


    fprintf(fp, "[");
    int i = 0;
    //for (int i = 0; i < p->size; i++)
    ForEachListItem(TPointer, pItem, p)
    {
        if (i > 0)
            fprintf(fp, ",");

        //TPointer * pItem = p->pItems[i];
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
        //fprintf(fp, "\"initializer\":");
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
        //fprintf(fp, "\"initializer\":");
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
        //identifier
        fprintf(fp, "\"identifier\":");
        fprintf(fp, "\"%s\"", pDirectDeclarator->Identifier);
        b = true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        fprintf(fp, "\"declarator\":");
        b = TDeclarator_Print(pDirectDeclarator->pDeclarator, b, fp);
    }

    if (pDirectDeclarator->pExpression)
    {
        /*
         direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
         direct-declarator [ static type-qualifier-listopt assignment-expression ]
         direct-declarator [ type-qualifier-list static assignment-expression ]
        */
        b = TExpression_Print(pDirectDeclarator->pExpression, "assignment-expression", b, fp);
    }

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        //( parameter-type-list )
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

        //CASE(TAlignmentSpecifier) :
        //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
        //break;
        default:
            //assert(false);
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
    //b = TTypeQualifierList_Print(&p->Qualifier, false, fp);
    //b = TTypeSpecifier_Print(p->pSpecifier, b, fp);

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
            //assert(false);
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
            //assert(false);
            break;
            //CASE(TAlignmentSpecifier) :
            //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
            //break;

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
    //b = TFunctionSpecifier_Print(&pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
    //b = StorageSpecifier_Print(&pDeclarationSpecifiers->StorageSpecifiers, b, fp);
    //b = TTypeQualifierList_Print(&pDeclarationSpecifiers->TypeQualifiers, b, fp);
    //b/ = TTypeSpecifier_Print(pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
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
            //assert(false);
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
    //TDeclarations_Print(&pProgram->Declarations, false, fp);


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
    // [Size]
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
    //TUnionSetItem_Delete(p->pHead);
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
        //A funcao TParameterTypeList_GetParameterByIndex deve retornar
        //null caso o primeiro parametro seja void. void Function(void)
        //
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
            //F(void) neste caso nao tem nome
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
            //ATENCAO
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
                //assert(false);
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
    //assert(p->pDeclarator != NULL);
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

        //ForEachListItem(TPointer, pItem, pPointerlist)
        TPointer * pItem = pPointerlist->pHead;
        //for (T * var = (list)->pHead; var != NULL; var = var->pNext)
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
    //Esta definicao esta estranha..tem que pegar o size de 1 cara so

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
    //retorna true se tem 1 ponteiro qualificado auto
    bool bResult = false;
    TPointer * pPointer = pPointerlist->pHead;
    if (pPointer != NULL && pPointer->pNext == NULL)
    {
        //so tem 1 ponteiro
        //procura se tem algum qualificador auto
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
                    //auto _size()
                    // _size() auto
                    bResult = IsAutoToken(pPointer->Qualifier.Data[0]->Token) ||
                        IsAutoToken(pPointer->Qualifier.Data[1]->Token);
                }
            }
        }
    }

    return bResult;
}



void TTypeQualifierList_Destroy(TTypeQualifierList * p)  /*custom*/
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
        //nao eh p acontecer!

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
    //dest->ClueList0 nao vamos copiar
    //dest->Type nao precisa copiar
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
    //bool result = false;
    //if (p1->TypeName && p2->TypeName &&
      //  strcmp(p1->TypeName, p2->TypeName) == 0)
    //{
      //  result = true;
    //}
    //so eh usado em 1 context que nao faz diferenca hj
    assert(false);
    return true;// result;
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
                //assert(false);
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
            //assert(false);
            break;
        }
    }


    if (token == TK_IDENTIFIER)
    {
        if (!bTypeDef && !bInt)
        {
            //Exemplo que se quer evitar
            //typedef int X;
            //void F(int X)
            //nao pode ter nada antes
            bResult = true;
        }
    }
    else
    {
        //verificar combinacoes unsigned float etc.
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
            //ATENCAO
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
                //case TK_INT:				
                //case TK_DOUBLE:
                    //..etc...
                    //bOther = true;
                    //break; 

            case TK_IDENTIFIER:
                bTypeDef = true;
                break;
            default:
                bOther = true;
                break;
                ////assert(false);
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
            //assert(false);
            break;
        }
    }


    if (token == TK_IDENTIFIER)
    {
        if (pTStructUnionSpecifier)
        {
            //ja tem uma struct
            if (pTStructUnionSpecifier->TagName &&
                strcmp(pTStructUnionSpecifier->TagName, lexeme) == 0)
            {
                //typedef struct X X;
            }
            else
            {
                bResult = true;
            }
        }
        else if (pEnumSpecifier)
        {
            //ja tem uma struct
            if (pEnumSpecifier->Name &&
                strcmp(pEnumSpecifier->Name, lexeme) == 0)
            {
                //typedef enum X X;
            }
            else
            {
                bResult = true;
            }
        }
        else if (!bTypeDef && !bOther)
        {
            //Exemplo que se quer evitar
            //typedef int X;
            //void F(int X)
            //nao pode ter nada antes
            bResult = true;
        }
    }
    else
    {
        //verificar combinacoes unsigned float etc.
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
            //procura declaracao completa
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
    //F(void) neste caso nao tem nome
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
            //assert(false);
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
            //assert(false);
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
        //assert(false);
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
        //assert(false);
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
    //return DeclarationsMap_FindDeclaration(&p->Symbols, name);
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



//Retorna a declaracao final do tipo entrando em cada typedef. 
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



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
    int * pResult)
{

    int result = *pResult;

    if (p->pExpressionLeft)
    {
        int left;
        EvaluateConstantExpression(p->pExpressionLeft, &left);
    }

    //if (p->pInitializerList)
    {
        //falta imprimeir typename
        //TTypeName_Print*
        //b = TInitializerList_CodePrint(p->pInitializerList, b, fp);
    }

    switch (p->token)
    {
    case TK_FULL_STOP:
        //fprintf(fp, ".%s", p->Identifier);
        //assert(false);
        break;
    case TK_ARROW:
        //fprintf(fp, "->%s", p->Identifier);
        //b = true;
        //assert(false);
        break;

    case TK_LEFT_SQUARE_BRACKET:
    {
        int index;
        //fprintf(fp, "[");
        EvaluateConstantExpression(p->pExpressionRight, &index);
        //fprintf(fp, "]");
        //assert(false);
    }
    break;

    case TK_LEFT_PARENTHESIS:
    {
        EvaluateConstantExpression(p->pExpressionRight, &result);
    }
    break;

    case TK_PLUSPLUS:
        //assert(false);
        break;
    case TK_MINUSMINUS:
        //assert(false);
        break;
    default:
        //assert(false);
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

//Criado para avaliacao do #if
//Tem que arrumar para fazer os casts do enum
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
                    //SetError
                }
                break;


            default:
                //TODO ADD THE OPERADOR?
                //assert(false);
                b = false;
                break;
            }

            //if (pBinaryExpression->)
        }
        break;

        CASE(TTernaryExpression) :
        {
            int e1, e2, e3;
            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionLeft, &e1);

            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionMiddle, &e2);

            b = EvaluateConstantExpression(((TTernaryExpression *)p)->pExpressionRight, &e3);
            //assert(false);
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
                    result = 0; //para macro
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
                        //vem com 'A'
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
                    //assert(0);
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
            //assert(false);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {

            TUnaryExpressionOperator * pTUnaryExpressionOperator =
                (TUnaryExpressionOperator *)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {

                //if (TDeclarationSpecifiers_IsTypedef(pTUnaryExpressionOperator->TypeName.SpecifierQualifierList))
                {

                    //b = TTypeQualifier_CodePrint2(&pTUnaryExpressionOperator->TypeName.qualifiers, fp);
                    //b = TTypeSpecifier_CodePrint2(pTUnaryExpressionOperator->TypeName.pTypeSpecifier, b, fp);
                    // b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.declarator, b, fp);


                }
                //else
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
                    //assert(false);
                    break;
                }
            }


        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType *)p;


            //b = TTypeQualifier_CodePrint2(&pCastExpressionType->TypeName.qualifiers, fp);
            //b = TTypeSpecifier_CodePrint2(pCastExpressionType->TypeName.pTypeSpecifier, b, fp);
            //b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.declarator, b, fp);

            b = EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
            //assert(false);

        }
        break;

    default:
        //assert(false);
        break;
    }

    //assert(result != -987654321);
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
            result = false /*nomem*/;
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
        //assert(false);
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
    //assert(p->size > 0);
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
    //String_Destroy((char**)(&p));
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
    //assert(p->size > 0);
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
        if (StrIComp(pEndPart, suffix) == 0) //case insensitive
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
    //so delete esta item e nao todos os proximos
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
    // hash key to unsigned int value by pseudorandomizing transform
    // (algorithm copied from STL string hash in xfunctional)
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
            //out of mem
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
        ////////////////
        //Microsoft - specific
        case TK__INT8:
        case TK__INT16:
        case TK__INT32:
        case TK__INT64:
        case TK__WCHAR_T:
        ////////////////
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
        case TK__INLINE://ms
        case TK__FORCEINLINE: //ms
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

        case     TK_EXCLAMATION_MARK:// = '!';
        case    TK_QUOTATION_MARK:// = '\"';
        case    TK_NUMBER_SIGN:// = '#';

        case    TK_DOLLAR_SIGN:// = '$';
        case     TK_PERCENT_SIGN:// = '%';
        case    TK_AMPERSAND:// = '&';
        case     TK_APOSTROPHE:// = '\'';
        case    TK_LEFT_PARENTHESIS:// = '(';
        case    TK_RIGHT_PARENTHESIS:// = ')';
        case    TK_ASTERISK:// = '*';
        case    TK_PLUS_SIGN:// = '+';
        case    TK_COMMA:// = ':';
        case    TK_HYPHEN_MINUS:// = '-';
        case    TK_HYPHEN_MINUS_NEG:// = '-'; //nao retorna no basic string mas eh usado para saber se eh - unario
        case    TK_FULL_STOP:// = '.';
        case    TK_SOLIDUS:// = '/';

        case    TK_COLON:// = ':';
        case    TK_SEMICOLON:// = ';';
        case    TK_LESS_THAN_SIGN:// = '<';
        case    TK_EQUALS_SIGN:// = '=';
        case    TK_GREATER_THAN_SIGN:// = '>';
        case    TK_QUESTION_MARK:// = '\?';
        case    TK_COMMERCIAL_AT:// = '@';

        case     TK_LEFT_SQUARE_BRACKET:// = '[';
        case    REVERSE_SOLIDUS:// = '\\';
        case     TK_RIGHT_SQUARE_BRACKET:// = ']';
        case    TK_CIRCUMFLEX_ACCENT:// = '^';
        case    TK_LOW_LINE:// = '_';
        case    TK_GRAVE_ACCENT:// = '`';

        case    TK_LEFT_CURLY_BRACKET:// = '{';
        case    TK_VERTICAL_LINE:// = '|';
        case    TK_RIGHT_CURLY_BRACKET:// = '}';
        case    TK_TILDE: // ~

        result = PPTokenType_Punctuator;
        break;
        default:
        //assert(false);
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
    // tem que ser case insensitive!
    //assert(IsFullPath(key));
    // converter
    // Ajusta o file index de acordo com a entrada dele no mapa
    pFile->FileIndex = map->Size;
    bool result = Map_Set(map, key, pFile);
    PTR_STRING_REPLACE(pFile->FullPath, key);
    return result;
}

TFile * TFileMap_Find(TFileMap * map, const char * key)
{
    // tem que ser case insensitive!
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
    // TODO tipo do token
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
    // TFileMap_init
    // pScanner->IncludeDir
    Map_Init(&pScanner->FilesIncluded, 100);
    MacroMap_Init(&pScanner->Defines2);
    StrBuilder_Init(&pScanner->DebugString);

    StrBuilder_Init(&pScanner->ErrorString);

    pScanner->bError = false;
    StackInts_Init(&pScanner->StackIfDef);

    BasicScannerStack_Init(&pScanner->stack);

    StrArray_Init(&pScanner->IncludeDir);
    FileNodeList_Init(&pScanner->Sources);

    // Indica que foi feita uma leitura especulativa
    // pScanner->bHasLookAhead = false;
    //  pScanner->pLookAheadPreviousScanner = NULL;

    // Valor lido na leitura especulativa
    // ScannerItem_Init(&pScanner->LookAhead);
    //__FILE__ __LINE__ __DATE__ __STDC__  __STD_HOSTED__  __TIME__
    //__STD_VERSION__
    //
    AddStandardMacro(pScanner, "__LINE__", "0");
    AddStandardMacro(pScanner, "__FILE__", "\"__FILE__\"");
    AddStandardMacro(pScanner, "__DATE__", "\"__DATE__\"");
    AddStandardMacro(pScanner, "__TIME__", "\"__TIME__\"");
    AddStandardMacro(pScanner, "__STDC__", "1");
    AddStandardMacro(pScanner, "__COUNTER__", "0");
    // AddStandardMacro(pScanner, "__STD_HOSTED__", "1");

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
    bool result = BasicScanner_Create(&pNewScanner, callString, /*defineName*/
        defineContent, BasicScannerType_Macro);

    if (result == true)
    {
        pNewScanner->bMacroExpanded = true;
        BasicScanner_Match(pNewScanner); // inicia
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

    // https://msdn.microsoft.com/en-us/library/36k2cdd4.aspx
    /*
    bQuotedForm
    The preprocessor searches for include files in this order:
    1) In the same directory as the file that contains the #include statement.
    2) In the directories of the currently opened include files, in the reverse
    order in which they were opened. The search begins in the directory of the
    parent include file and continues upward through the directories of any
    grandparent include files. 3) Along the path that's specified by each /I
    compiler option. 4) Along the paths that are specified by the INCLUDE
    environment variable.
    */
    if (bQuotedForm)
    {
        // String s = NULL;
        // GetFullPath(fileName, &s);
        // Free(s);
        if (IsFullPath(fileName))
        {
            // Se ja vier com fullpath?? este caso esta cobrindo
            // mas deve ter uma maneira melhor de verificar se eh um fullpath ja
            bFullPathFound = true;
            PTR_STRING_REPLACE(*fullPathOut, fileName);
        }
        else
        {
            if (pScanner->stack != NULL)
            {
                // tenta nos diretorios ja abertos
                StrBuilder path = STRBUILDER_INIT;

                // for (int i = (int)pScanner->stack.size - 1; i >= 0; i--)
                ForEachBasicScanner(p, pScanner->stack)
                {
                    // BasicScanner* p = (BasicScanner*)pScanner->stack.pItems[i];
                    StrBuilder_Set(&path, p->stream.FullDir2);
                    StrBuilder_Append(&path, fileName);
                    bool bFileExists = FileExists(path.c_str);

                    if (bFileExists)
                    {
                        GetFullPath(path.c_str, fullPathOut);
                        // String_Set(fullPathOut, StrBuilder_Release(&path));
                        bFullPathFound = true;
                        break;
                    }
                }

                StrBuilder_Destroy(&path);
            }
            else
            {
                // nao abriu nenhum, faz o full path do nome do arquivo
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

    /*
    Angle-bracket form
    The preprocessor searches for include files in this order:
    1) Along the path that's specified by each /I compiler option.
    2) When compiling occurs on the command line, along the paths that are
    specified by the INCLUDE environment variable.
    */
    if (!bFullPathFound)
    {
        StrBuilder path = STRBUILDER_INIT;


        for (int i = 0; i < pScanner->IncludeDir.size; i++)
        {
            const char * pItem = pScanner->IncludeDir.pItems[i];
            StrBuilder_Set(&path, pItem);

            //barra para o outro lado funciona
            //windows e linux
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

    // Faz a procura nos diretorios como se tivesse adicinando o include
    // seguindo as mesmas regras. Caso o include seja possivel ele retorna o path
    // completo  este path completo que eh usado para efeitos do pragma once.
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
            // foi marcado como pragma once.. nao faz nada
            // tenho q enviar um comando
            if (pScanner->pOptions->bAmalgamate)
            {
                //no mondo amalgamation nao eh p cair aqui
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
                TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile); // pfile Moved
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
    //Basically this function was created to allow
    //inclusion of new file Scanner_IncludeFile
    //after scanner reach EOF  (See GetSources)
    //After eof we need to Reset. The reset
    //is not general.
    //A better aprouch would be just make this work
    //correclty without reset.

    BasicScannerStack_Destroy(&pScanner->stack);
    BasicScannerStack_Init(&pScanner->stack);

    //mantem
    //MacroMap_Destroy(&pScanner->Defines2);

    StackInts_Destroy(&pScanner->StackIfDef);
    StackInts_Init(&pScanner->StackIfDef);

    //mantem
    //TFileMap_Destroy(&pScanner->FilesIncluded);

    //mantem
    //StrArray_Destroy(&pScanner->IncludeDir);

    //FileNodeList_Destroy(&pScanner->Sources);
    //FileNodeList_Init(&pScanner->Sources);

    StrBuilder_Destroy(&pScanner->DebugString);
    StrBuilder_Init(&pScanner->DebugString);

    StrBuilder_Destroy(&pScanner->ErrorString);
    StrBuilder_Init(&pScanner->ErrorString);

    TScannerItemList_Destroy(&pScanner->AcumulatedTokens);
    TScannerItemList_Init(&pScanner->AcumulatedTokens);

    pScanner->bError = false;
}

/*int Scanner_GetCurrentLine(Scanner* pScanner)
{
    //assert(!pScanner->bHasLookAhead);

    if (pScanner->bError)
    {
        return -1;
    }


    int currentLine = -1;
    int fileIndex = -1;


    ForEachBasicScanner(pBasicScanner, pScanner->stack)
    {
        fileIndex = pBasicScanner->FileIndex;

        if (fileIndex >= 0) //macro eh -1
        {
            currentLine = pBasicScanner->stream.currentLine;
            break;
        }
    }

    return currentLine;
}
*/

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

    // //assert(fileIndex >= 0);
    return fileIndex;
}

/*const char* Scanner_LexemeAt(Scanner* pScanner)
{
    if (pScanner->bHasLookAhead)
    {
        return pScanner->LookAhead.lexeme.c_str;
    }
    else
    {
        BasicScanner* pBasicScanner = pScanner->stack;

        return pBasicScanner ?
            pBasicScanner->currentItem.lexeme.c_str :
            "";
    }
}*/

BasicScanner * Scanner_Top(Scanner * pScanner)
{
    return pScanner->stack;
}

// int Scanner_Line(Scanner* pScanner)
//{
//  //assert(!pScanner->bHasLookAhead);
// return Scanner_Top(pScanner)->stream.currentLine;
//}

// int Scanner_Col(Scanner* pScanner)
//{
//  //assert(!pScanner->bHasLookAhead);
//    return Scanner_Top(pScanner)->stream.currentCol;
//}

void IgnorePreProcessorv2(BasicScanner * pBasicScanner, StrBuilder * strBuilder)
{

    while (pBasicScanner->currentItem.token != TK_EOF &&
        pBasicScanner->currentItem.token != TK_FILE_EOF)
    {
        if (pBasicScanner->currentItem.token == TK_BREAKLINE)
        {
            // StrBuilder_Append(strBuilder, pTop->currentItem.lexeme.c_str);
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
            // deixa o break line
            // BasicScanner_Match(Scanner_Top(pScanner));
            break;
        }

        if (token == TK_OPEN_COMMENT ||
            token == TK_CLOSE_COMMENT ||
            token == TK_COMMENT ||
            token == TK_LINE_COMMENT)
        {
            // transforma em espaços
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
    // Faz o parser da expressão
    TExpression * pExpression = NULL;
    ConstantExpression(parser, &pExpression);
    //..a partir da arvore da expressão
    // calcula o valor
    // TODO pegar error
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
    // printf("%s = ", s);
    // TODO avaliador de expressoes para pre processador
    // https://gcc.gnu.org/onlinedocs/gcc-3.0.2/cpp_4.html#SEC38
    Parser parser;
    Parser_InitString(&parser, "eval expression", s);
    parser.bPreprocessorEvalFlag = true;

    if (pDefines)
    {
        // usa o mapa de macros para o pre-processador
        MacroMap_Swap(&parser.Scanner.Defines2, pDefines);
    }

    //    Scanner_Match(&parser.Scanner);
    int iRes = PreprocessorExpression(&parser);

    // printf(" %d\n", iRes);
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
    // StrBuilder_Append(strBuilderResult, Scanner_LexemeAt(pScanner));
    // TODO aqui nao pode ser o current
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;
    Tokens token = pBasicScanner->currentItem.token;

    // verificar se tem parametros
    int nArgsExpected = pMacro->FormalArguments.Size; // pMacro->bIsFunction;
    int nArgsFound = 0;

    // fazer uma lista com os parametros

    if (token == TK_LEFT_PARENTHESIS)
    {
        // Adiciona o nome da macro
        struct PPToken * ppTokenName = PPToken_Create(pMacro->Name, PPTokenType_Identifier);
        TokenArray_PushBack(ppTokenArray, ppTokenName);

        // Match do (
        struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
        TokenArray_PushBack(ppTokenArray, ppToken);

        StrBuilder_Append(strBuilder, lexeme);
        BasicScanner_Match(pBasicScanner);

        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;

        // comeca com 1
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
                    // continuar...
                }

                // StrBuilder_Append(strBuilderResult, Scanner_LexemeAt(pScanner));
                struct PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
                TokenArray_PushBack(ppTokenArray, ppToken);

                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                token = pBasicScanner->currentItem.token;
                lexeme = pBasicScanner->currentItem.lexeme.c_str;
            }
            else
            {
                // StrBuilder_Append(strBuilderResult, Scanner_LexemeAt(pScanner));
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
            // erro
        }
        else
        {
            if (nArgsExpected > nArgsFound)
            {
                // Scanner_SetError(pScanner, "Illegal macro call. Too few arguments
                // error");
            }
            else
            {
                // Scanner_SetError(pScanner, "Illegal macro call. Too many arguments
                // error.");
            }
            //assert(false);
            // JObj_PrintDebug(pMacro);
            // Scanner_PrintDebug(pScanner);
        }
    }

    // tODO se nao for macro tem que pegar todo
    // o match feito e devolver.
    // nome da macro e espacos..

    // return false;
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

    // Corpo da macro
    while (token != TK_BREAKLINE && token != TK_EOF && token != TK_FILE_EOF)
    {
        StrBuilder_Append(strBuilder, lexeme);

        if (token != TK_BACKSLASHBREAKLINE)
        {
            // TODO comentarios entram como espaco
            struct       PPToken * ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
            TokenArray_PushBack(pptokens, ppToken);
        }
        BasicScanner_Match(pBasicScanner);
        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;
    }

    // Remove os espaços do fim
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

    // objetivo eh montar a macro e colocar no mapa
    struct Macro * pNewMacro = Macro_Create();

    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;

    PTR_STRING_REPLACE(pNewMacro->Name, lexeme);
    StrBuilder_Append(strBuilder, lexeme);

    // Match nome da macro
    BasicScanner_Match(pBasicScanner);

    token = pBasicScanner->currentItem.token;
    lexeme = pBasicScanner->currentItem.lexeme.c_str;

    // Se vier ( é macro com parâmetros
    if (token == TK_LEFT_PARENTHESIS)
    {
        pNewMacro->bIsFunction = true;

        StrBuilder_Append(strBuilder, lexeme);

        // Match (
        BasicScanner_Match(pBasicScanner);

        for (;;)
        {
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, strBuilder);

            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;

            if (token == TK_RIGHT_PARENTHESIS)
            {
                // Match )
                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                break;
            }

            if (token == TK_BREAKLINE || token == TK_EOF)
            {
                // oopss
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
                // Match ,
                StrBuilder_Append(strBuilder, lexeme);
                BasicScanner_Match(pBasicScanner);
                // tem mais
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

    // breakline ficou...
}

int EvalPre(Scanner * pScanner, StrBuilder * sb)
{
    if (pScanner->bError)
    {
        return 0;
    }

    // pega todos os tokens ate o final da linha expande e
    // avalia
    // usado no #if #elif etc.
    BasicScanner * pBasicScanner = Scanner_Top(pScanner);

    struct TokenArray pptokens = TOKENARRAY_INIT;
    GetPPTokens(pBasicScanner, &pptokens, sb);


    StrBuilder strBuilder = STRBUILDER_INIT;
    ExpandMacroToText(&pptokens, &pScanner->Defines2, false, true, true, NULL,
        &strBuilder);

    int iRes = EvalExpression(strBuilder.c_str, pScanner);

    if (pScanner->bError)
    {
        //assert(false);
    }

    /*StrBuilder sb1 = STRBUILDER_INIT;
    Scanner_GetFilePositionString(pScanner, &sb1);
    printf("%s \n", sb1.c_str);
    printf("#if ");
    for (int i = 0; i < pptokens.Size; i++)
    {
      printf("%s", pptokens.pItems[i]->Lexeme);
    }
    printf(" == %d \n\n",iRes);
    StrBuilder_Destroy(&sb1);
    */
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
    pNew->bActive = bActive; //;
    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);
}

// Atencao
// Esta funcao eh complicada.
//
// Ela faz uma parte da expansao da macro que pode virar um "tetris"
// aonde o colapso de uma expansao vira outra expansao
// a unica garantia sao os testes.
//
void Scanner_BuyIdentifierThatCanExpandAndCollapse(Scanner * pScanner)
{
    enum PPState state = StateTop(pScanner);
    BasicScanner * pBasicScanner = Scanner_Top(pScanner);
    //assert(pBasicScanner != NULL);

    Tokens token = pBasicScanner->currentItem.token;
    const char * lexeme = pBasicScanner->currentItem.lexeme.c_str;
    //assert(token == TK_IDENTIFIER);

    if (!IsIncludeState(state))
    {
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = false;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        // Match do identificador
        BasicScanner_Match(pBasicScanner);
        return;
    }

    struct Macro * pMacro2 = Scanner_FindPreprocessorItem2(pScanner, lexeme);
    if (pMacro2 == NULL)
    {
        // nao eh macro
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        // Match do identificador
        BasicScanner_Match(pBasicScanner);
        return;
    }

    if (pBasicScanner->bMacroExpanded &&
        strcmp(pMacro2->Name, pBasicScanner->stream.NameOrFullPath) == 0)
    {
        // ja estou expandindo esta mesma macro
        // nao eh macro
        struct ScannerItem * pNew = ScannerItem_Create();
        LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
        pNew->token = pBasicScanner->currentItem.token;
        pNew->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

        // Match do identificador
        BasicScanner_Match(pBasicScanner);
        return;
    }

    struct Macro * pFirstMacro = pMacro2;

    // Match do identificador do nome da macro funcao
    BasicScanner_Match(pBasicScanner);

    bool bExitLoop = false;

    do
    {
        if (!pMacro2->bIsFunction)
        {
            struct TokenArray ppTokenArray = TOKENARRAY_INIT;
            // o nome eh a propria expansao
            struct       PPToken * ppTokenName =
                PPToken_Create(pMacro2->Name, TokenToPPToken(TK_IDENTIFIER));
            TokenArray_PushBack(&ppTokenArray, ppTokenName);

            StrBuilder strExpanded = STRBUILDER_INIT;

            ExpandMacroToText(&ppTokenArray, &pScanner->Defines2, false, false, false, NULL,
                &strExpanded);

            // se expandir para identificador e ele for uma macro do tipo funcao
            // pode ser tetris
            struct Macro * pMacro3 = NULL;

            if (strExpanded.size > 0)
            {
                pMacro3 = Scanner_FindPreprocessorItem2(pScanner, strExpanded.c_str);
            }

            if (pMacro3)
            {
                if (pMacro3->bIsFunction)
                {
                    // Expandiu para uma identificador que é macro funcao
                    pMacro2 = pMacro3;
                }
                else
                {
                    // ok expandiu

                    PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                    Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                    bExitLoop = true;

                }
            }
            else
            {
                // ok expandiu

                PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                bExitLoop = true;
            }

            TokenArray_Destroy(&ppTokenArray);
            StrBuilder_Destroy(&strExpanded);
        }
        else
        {
            //é uma função

            // Procurar pelo (

            TScannerItemList LocalAcumulatedTokens = { 0 };
            token = pBasicScanner->currentItem.token;
            lexeme = pBasicScanner->currentItem.lexeme.c_str;
            while (token == TK_SPACES ||
                token == TK_COMMENT ||
                token == TK_OPEN_COMMENT ||
                token == TK_CLOSE_COMMENT)
            {
                // StrBuilder_Append(strBuilder, lexeme);

                /////////////
                struct ScannerItem * pNew = ScannerItem_Create();
                LocalStrBuilder_Set(&pNew->lexeme, lexeme);
                pNew->token = token;
                pNew->bActive = true;
                TScannerItemList_PushBack(&LocalAcumulatedTokens, pNew);
                ////////////

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
                // eh uma chamada da macro funcao
                // coletar argumentos e expandir
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

                /////////////////////////////////
                // se expandir para identificador e ele for uma macro do tipo funcao
                // pode ser tetris
                struct Macro * pMacro3 = NULL;
                if (strExpanded.size > 0)
                {
                    pMacro3 = Scanner_FindPreprocessorItem2(pScanner, strExpanded.c_str);
                }

                if (pMacro3)
                {
                    if (pMacro3->bIsFunction)
                    {
                        // Expandiu para uma identificador que é macro funcao
                        pMacro2 = pMacro3;
                    }
                    else
                    {
                        // ok expandiu

                        PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                        Scanner_PushToken(pScanner, TK_MACRO_CALL, pMacro2->Name, true);
                    }
                }
                else
                {
                    // ok expandiu

                    PushExpandedMacro(pScanner, pMacro2->Name, strExpanded.c_str);

                    Scanner_PushToken(pScanner, TK_MACRO_CALL, strCallString.c_str, true);
                    bExitLoop = true;
                }
                ///////////////////////
                TokenArray_Destroy(&ppTokenArray);
                StrBuilder_Destroy(&strExpanded);
                StrBuilder_Destroy(&strCallString);
            }
            else
            {
                // macro call
                // B
                // endcall
                // espacos
                if (pFirstMacro != pMacro2)
                {
                    // nao era uma chamada da macro funcao
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
                // tODO espacos

                // a macro eh uma funcao mas isso nao eh a chamada da macro
                // pq nao foi encontrado (
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
    // Sempre compra uma carta nova do monte do baralho.
    // se a carta servir ele coloca na mesa.
    // se comprar uma carta macro expande e coloca em cima
    // do baralho novas cartas sou coloca na mesa
    //(sim eh complicado)

    if (pScanner->bError)
    {
        return;
    }

    BasicScanner * pBasicScanner = Scanner_Top(pScanner);
    if (pBasicScanner == NULL)
    {
        // acabaram todos os montes de tokens (cartas do baralho)
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
        // ok remove este baralho vazio
        BasicScannerStack_Pop(&pScanner->stack);

        // proximo baralho
        pBasicScanner = Scanner_Top(pScanner);

        if (pBasicScanner != NULL)
        {
            // vai removendo enquanto sao baralhos vazios
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
            // se eh o unico arquivo TK_FILE_EOF vira eof
            token = TK_EOF;
        }
    }

    if (token == TK_EOF)
    {
        // não sobrou nenhum baralho nao tem o que comprar
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
        // Match #
        StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
        BasicScanner_Match(pBasicScanner);

        // Match ' '
        Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);

        lexeme = pBasicScanner->currentItem.lexeme.c_str;
        token = pBasicScanner->currentItem.token;

        Tokens preToken = FindPreToken(lexeme);

        if (preToken == TK_PRE_INCLUDE)
        {
            // Match include
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            lexeme = pBasicScanner->currentItem.lexeme.c_str;
            token = pBasicScanner->currentItem.token;

            if (IsIncludeState(state))
            {
                // Match espacos
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

                    // tem que ser antes de colocar o outro na pilha
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
                    // break;
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
                            // oopps
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
                // TODO active
                Scanner_PushToken(pScanner, TK_SPACES, strBuilder.c_str, false);
            }
        }
        else if (preToken == TK_PRE_PRAGMA)
        {
            // Match pragma
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
                    //
                    IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                    Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                }
                else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "message"))
                {
                    // Match message
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
                    //
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
                        fileName = fullPath;//moved
                        BasicScanner_Match(pBasicScanner);
                    }
                    else
                    {
                        fileName = StrDup(pScanner->stack->stream.NameOrFullPath);
                        fileName[strlen(pScanner->stack->stream.NameOrFullPath) - 1] = 'c';
                    }




                    FileNodeList_PushBack(&pScanner->Sources, fileName);

                    Free(fileName);
                    //
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
                        //
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
                        //
                        IgnorePreProcessorv2(pBasicScanner, &strBuilder);
                        Scanner_PushToken(pScanner, TK_PRE_PRAGMA, strBuilder.c_str, true);
                    }
                }
                else
                {
                    //
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
                        else // if (preToken == TK_PRE_IFNDEF)
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
            // Match elif
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
                //assert(0);
                break;
            }

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_ELIF, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ENDIF)
        {
            // Match elif
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

            // Match else
            StrBuilder_Append(&strBuilder, pBasicScanner->currentItem.lexeme.c_str);
            BasicScanner_Match(pBasicScanner);

            switch (state)
            {
                case PPState_NONE:
                //assert(0);
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
                //assert(false);
                break;
            }

            state = StateTop(pScanner);
            bool bActive = IsIncludeState(state);

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_ELSE, strBuilder.c_str, bActive);
        }
        else if (preToken == TK_PRE_ERROR)
        {
            // Match error
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
                // Match line
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
                // Match undef
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
            // Match define
            StrBuilder_Append(&strBuilder, lexeme);
            BasicScanner_Match(pBasicScanner);

            // Match all ' '
            Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);
            bool bActive = IsIncludeState(state);
            if (bActive)
            {
                ParsePreDefinev2(pScanner, &strBuilder);
            }

            IgnorePreProcessorv2(pBasicScanner, &strBuilder);
            Scanner_PushToken(pScanner, TK_PRE_DEFINE, strBuilder.c_str, bActive);
        }

        // break;
    } //#
    else if (token == TK_IDENTIFIER)
    {
        // codigo complicado tetris
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
    //}//for

    // state = StateTop(pScanner);
    // pTopScanner->currentItem.bActive = IsIncludeState(state);
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
                // Tokens para linhas do pre processador
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

                // fim tokens preprocessador
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

    ///
    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(fullFileNamePath, drive, dir, fname, ext); // C4996

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
                // Tokens para linhas do pre processador
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

                // fim tokens preprocessador
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
    int nCount = 1; // contando com o "normal"
    ForEachListItem(struct ScannerItem, pItem, &pScanner->AcumulatedTokens)
    {
        nCount++;
    }
    return nCount;
}

struct ScannerItem * Scanner_ScannerItemAt(Scanner * pScanner, int index)
{

    // item0 item1 ..itemN
    //^
    // posicao atual

    struct ScannerItem * pScannerItem = NULL;

    if (!pScanner->bError)
    {
        // conta o numero de itens empilhados
        int nCount = 0;
        ForEachListItem(struct ScannerItem, pItem, &pScanner->AcumulatedTokens)
        {
            nCount++;
        }

        // precisa comprar tokens?
        if (index >= nCount)
        {
            for (int i = nCount; i <= index; i++)
            {
                // comprar mais tokens
                Scanner_BuyTokens(pScanner);
            }
            pScannerItem = pScanner->AcumulatedTokens.pTail;
        }
        else
        {
            // nao precisa comprar eh so pegar
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
                //assert(pScanner->AcumulatedTokens.pHead == NULL);
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
            return "!";// = '!';
        case TK_QUOTATION_MARK:
            return "\"";//,// = '\"';
        case TK_NUMBER_SIGN:
            return "#";//,// = '#';
        case TK_DOLLAR_SIGN:
            return "$";//,// = '$';
        case TK_PERCENT_SIGN:
            return "%";//,// = '%';
        case TK_AMPERSAND:
            return "&";//,// = '&';
        case TK_APOSTROPHE:
            return "'";//,// = '\'';
        case TK_LEFT_PARENTHESIS:
            return "(";//,// = '(';
        case TK_RIGHT_PARENTHESIS:
            return ")";//,// = ')';
        case TK_ASTERISK:
            return "*";//,// = '*';
        case TK_PLUS_SIGN:
            return "+";//,// = '+';
        case TK_COMMA:
            return ",";//,// = ',';
        case TK_HYPHEN_MINUS:
            return "-";//,// = '-';
        case TK_FULL_STOP:
            return ".";//,// = '.';
        case TK_SOLIDUS:
            return "/";//,// = '/';
        case TK_COLON:
            return ":";//,// = ':';
        case TK_SEMICOLON:
            return ";";//,// = ';';
        case TK_LESS_THAN_SIGN:
            return "<";//,// = '<';
        case TK_EQUALS_SIGN:
            return "=";//,// = '=';
        case TK_GREATER_THAN_SIGN:
            return ">";//,// = '>';
        case TK_QUESTION_MARK:
            return "?";//,// = '\?';
        case TK_COMMERCIAL_AT:
            return "@";//,// = '@';
        case TK_LEFT_SQUARE_BRACKET:
            return "[";//,// = '[';
        case REVERSE_SOLIDUS:
            return "\\";//,// = '\\';
        case TK_RIGHT_SQUARE_BRACKET:
            return "]";//,// = ']';
        case TK_CIRCUMFLEX_ACCENT:
            return "^";// = '^';
        case TK_LOW_LINE:
            return "_";//,// = '_';
        case TK_GRAVE_ACCENT:
            return "`";//,// = '`';
        case TK_LEFT_CURLY_BRACKET:
            return "{";//,// = '{';
        case TK_VERTICAL_LINE:
            return "|";//,// = '|';
        case TK_RIGHT_CURLY_BRACKET:
            return "}";//,// = '}';

        case TK_TILDE:
            return "~";//,// = '~';
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
            //
        case TK_MACRO_CALL:
            return "TK_MACRO_CALL";

        case TK_MACRO_EOF:
            return "TK_MACRO_EOF";

        case TK_FILE_EOF:
            return "TK_FILE_EOF";
        default:
            //assert(false);
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
    bool result = false /*nomem*/;
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
    bool result = false /*nomem*/;
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
    //punctuator: one of

    {"[", TK_LEFT_SQUARE_BRACKET }, //0
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
    { "@", TK_COMMERCIAL_AT } //pode ser usado em macros pp-tokens
    //  {"...", TK_DOTDOTDOT},//50
    //  {"%:%:", TK_PERCENTCOLONPERCENTCOLON},
    //  {"<<=", TK_LESSLESSEQUAL},
    //{">>=", TK_GREATERGREATEREQUAL},
};

static struct TkPair doubleoperators[] =
{
    { "->", TK_ARROW },//25
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

    { "...", TK_DOTDOTDOT },//50
    { "%:%:", TK_PERCENTCOLONPERCENTCOLON },
    { "<<=", TK_LESSLESSEQUAL },
    { ">>=", TK_GREATERGREATEREQUAL }
};

static struct TkPair keywords[] =
{
    //keywords
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
    //
    { "__int8", TK__INT8},
    { "__int16", TK__INT16 },
    { "__int32", TK__INT32 },
    { "__int64", TK__INT64 },
    { "__wchar_t", TK__WCHAR_T},
    //
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
    //
    { "__asm", TK__ASM } //visual studio

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

    //bool bLineStart = scanner->bLineStart;
    //scanner->bLineStart = false;
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
    //procura por puncturares com 2 caracteres
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

    //procura por puncturtorscom 1 caracteres
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
    //U'
    //u
    //L
    //Devido ao L' tem que vir antes do identificador
    //literal string
    if (ch == L'"' ||
        (ch == L'L' && ch1 == L'"'))
    {
        if (ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner); //L
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
                //escape
                ch = BasicScanner_MatchChar(scanner);
                ch = BasicScanner_MatchChar(scanner);
            }
            else if (ch == '\0')
            {
                //oops
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
    //Devido ao L' tem que vir antes do identificador
    //literal
    if (ch == L'\'' ||
        (ch == L'L' && ch1 == L'\''))
    {
        if (ch == 'L')
        {
            ch = BasicScanner_MatchChar(scanner); //L
        }
        scanner->currentItem.token = TK_CHAR_LITERAL;
        ch = BasicScanner_MatchChar(scanner); //'
        if (ch == '\\')
        {
            //escape
            ch = BasicScanner_MatchChar(scanner); //
            ch = BasicScanner_MatchChar(scanner); //caractere
        }
        else
        {
            ch = BasicScanner_MatchChar(scanner);//caractere
        }
        ch = BasicScanner_MatchChar(scanner);//'
        scanner->bLineStart = false;
        return;
    }
    //Identificador
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
        //v� se � keywords e corrige o token
        for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        {
            if (BasicScanner_IsLexeme(scanner, keywords[i].lexeme))
            {
                scanner->currentItem.token = keywords[i].token;
                //StrBuilder_Append(&scanner->currentItem.lexeme, keywords[i].lexeme);
                //Stream_Next(&scanner->stream);
                break;
            }
        }
        scanner->bLineStart = false;
        return;
    }

    //TODO binarios

    if (ch == '0' &&
        (
        (ch1 == 'x' || ch1 == 'X') || //hex 
        (ch1 >= '0' && ch1 <= '9')) //octal
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

        //integer suffix
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
                //error
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
                    //error 
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
                    //error 
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
                    //error 
                }
            }
            else if (ch == '8')
            {
                ch = BasicScanner_MatchChar(scanner);
            }
        }

        return;
    }
    //numero
    if (ch >= '0' && ch <= '9')
    {
        scanner->currentItem.token = TK_DECIMAL_INTEGER;
        ch = BasicScanner_MatchChar(scanner);
        while ((ch >= '0' && ch <= '9'))
        {
            ch = BasicScanner_MatchChar(scanner);
        }

        //integer suffix
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
                //error
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
                    //error 
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
                    //error 
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
                    //error 
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
    //quebra de linha
    if (ch == '\n' || ch == L'\r')
    {
        scanner->currentItem.token = TK_BREAKLINE;
        if (ch == L'\r' && ch1 == L'\n')
        {
            //so coloca \n
            Stream_Match(&scanner->stream);
            ch = scanner->stream.Character;
            ch = BasicScanner_MatchChar(scanner);
        }
        else
        {
            ch = BasicScanner_MatchChar(scanner);
            LocalStrBuilder_Clear(&scanner->currentItem.lexeme);
            //normaliza para windows?
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
    //espacos
    if (ch == ' ' || ch == '\t')
    {
        scanner->currentItem.token = TK_SPACES;
        ch = BasicScanner_MatchChar(scanner);
        while (ch == ' ' || ch == '\t')
        {
            ch = BasicScanner_MatchChar(scanner);
        }
        //continua com scanner->bLineStart
        return;
    }
    if (ch < 32)
    {
        scanner->currentItem.token = TK_SPACES;
    }
    //
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



    //comentario de linha
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
                        //so coloca \n
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
    //junta linha
    if (ch == L'\\' &&
        (ch1 == L'\n' || ch1 == L'\r'))
    {
        //1) Whenever backslash appears at the end of 
        //a line(immediately followed by the newline character), both 
        //backslash and newline are deleted,
        //combining two physical source lines into one logical 
        //source line.This is a single - pass operation; 
        //a line ending in two backslashes followed by an empty 
        //line does not combine three lines into one.
        //If a universal character name(\uXXX) is formed in this 
        //phase, the behavior is undefined.

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

        //homogeiniza \r\n para \n
        LocalStrBuilder_Set(&scanner->currentItem.lexeme, "\\\n");

        scanner->currentItem.token = TK_BACKSLASHBREAKLINE;
        scanner->bLineStart = false;
        //BasicScanner_Match(scanner);

        return;
    }
    if (ch == 2)  //peguei um
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
    //assert(false);
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

//////////////////////////////////////////////



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
    //assert(*stack != NULL);
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
            r = false /*nomem*/;
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
        strncpy(p->c_str, /*p->capacity + 1,*/ source, nelements);
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
            /*(p->capacity + 1) - p->size,*/
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
        //assert(nBytes > 0);
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
            //a partir de agora copia
            bCopy = true;
        }

        if (bCopy)
            StrBuilder_AppendChar(&temp, ch);
    }

    //indice do ultimo que nao eh espaco
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
            /*int fr =*/ fread(buffer, 1, lSize, fp);

            if (feof(fp))
            {
                //ok leu tudo
            }

            if (!ferror(fp))
            {
                //ok
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
    //assert(IsFullPath(fullPath));
    pStream->NameOrFullPath = StrDup(fullPath);
    pStream->FullDir2 = NULL;
    pStream->Line = 1;
    pStream->Column = 1;
    pStream->Position = 0;
    bool result = LoadFile(fullPath, (const char **)& pStream->Text,
                           &pStream->TextLen);

    if (result)
    {
        //O objetivo aqui eh pegar o diretorio
        GetFullDir(fullPath, &pStream->FullDir2);

        if (pStream->Text != NULL &&
            pStream->Text[0] != '\0')
        {
            //unicode?
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
        //unicode?
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










/**
* Simple Bob Jenkins's hash algorithm taken from the
* wikipedia description.
*/
static uint32_t HashFunc(const char * a)
{
    //assert(a != NULL);
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
                            String * *key /*in out*/,
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
    bool result = false /*nomem*/;
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
    bool result = false /*nomem*/;
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
            //assert(false);
            r = false /*nomem*/;
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
    //assert(key != NULL);
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
    //assert(key != NULL);
    *ppData = NULL; //out

    int index = FindNodeIndex(bucket, hash, key);
    bool result = index != -1 ? true : false;

    if (result == true)
    {
        //ponteiro de item que vai ser removido (out)
        *ppData = bucket->data[index]->data;

        if (index != (int)(bucket->size) - 1)
        {
            //swap  dos ponteiros de [index] e [size - 1]
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
    bool result = false /*nomem*/;
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
    bool result = false /*nomem*/;
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

    //assert(key != NULL);
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
    //assert(key != NULL);
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
            result = Bucket_Append(bucket, node /*moved*/);
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
    //assert(key != NULL);
    void * pv;
    bool result = Map_Find(map, key, &pv);
    if (result == true)
    {
        return false;
        ////assert(false);
    }


    //assert(key != NULL);
    String * /*@auto*/ localkey = StrDup(key);
    result = Map_SetMoveKey(map, &localkey, data);
    Free(localkey);
    return result;
}


bool Map_Find(Map * map, const char * key, void ** pp)
{
    //assert(key != NULL);
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
    //assert(key != NULL);
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
    //assert(key != NULL);
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
    ////assert(Map_Find(map, key, &p) != true);
    if (Map_Find(map, key, &p) == true)
    {
        //assert(false);
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
    //Buckets_Swap(&map->buckets, &map2->buckets);
}


////

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
    //assert(key != NULL);
    bool result;

    uint32_t hash = HashFunc(key);
    int bucket_n = hash % map->buckets.size;
    Bucket * bucket = map->buckets.data[bucket_n];

    if (bucket == NULL)
    {
        //N�o existia..criar
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
        //Adiciona no fim - n�o verifica se ja existe
        String * /*@auto*/stemp = StrDup(key);

        struct BucketItem * node;
        result = BucketItem_CreateMoveKey(&node,
                                          hash,
                                          &stemp,
                                          data);

        Free(stemp);

        if (result == true)
        {
            result = Bucket_Append(bucket, node /*moved*/);
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

    //assert(key != NULL);
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
/*
  based on
  https://github.com/dspinellis/cscout/blob/084d64dc7a0c5466dc2d505c1ca16fb303eb2bf1/src/macro.cpp
*/













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

// Return a new token sequence with hs added to the hide set of every element of ts
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

    //printf("hsadd returns: ");
    TokenArray_Print(pOut);
    //printf("\n");
}

void ExpandMacro(const struct TokenArray * pTokenSequence,
                 const struct MacroMap * macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro * caller,
                 struct TokenArray * pOutputSequence);

/*
Retorna o indice do primeiro token que não for espaço
a partir e incluindo o indice start.
Return -1 se não achar.
*/
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

// Return s with all \ and " characters \ escaped
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

                // FALTHROUGH
            default:
                StrBuilder_AppendChar(strBuilder, *source);
        }

        source++;
    }
}

/*
* Convert a list of tokens into a string as specified by the # operator
* Multiple spaces are converted to a single space, \ and " are
* escaped
*/
void AppendStringize(StrBuilder * strBuilder, const struct TokenArray * ts)
{
    /*
    Each occurrence of white space between the arguments
    preprocessing tokens becomes a single space character in
    the character string literal.
    */

    /*
    White space before the first preprocessing token and after the
    last preprocessing token composing the argument is deleted.
    */

    StrBuilder_Append(strBuilder, "\"");

    bool seen_space = true;   // To delete leading spaces

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

    // Remove trailing spaces
    StrBuilder_Trim(strBuilder);
}


/*
* Substitute the arguments args appearing in the input sequence is
* Result is created in the output sequence os and finally has the specified
* hide set added to it, before getting returned.
*/
void SubstituteArgs(struct Macro * pMacro,
                    const struct MacroMap * macros,
                    const struct TokenArray * isOriginal,   //macro
                    const TokenArrayMap * args,
                    TokenSet * hs,
                    bool skip_defined,
                    bool evalmode,
                    struct Macro * pCaller,
                    struct TokenArray * pOutputSequence)
{
    TokenArray_Clear(pOutputSequence);

    //Trabalha com uma copia
    struct TokenArray is = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&is, isOriginal);

    struct TokenArray os = TOKENARRAY_INIT;

    struct PPToken * head = NULL;
    while (is.Size > 0)
    {

        //printf("subst: is=");
        TokenArray_Print(&is);
        //printf(" os=");
        TokenArray_Print(&os);
        //printf("\n");

        //assert(head == NULL);
        head = TokenArray_PopFront(&is);

        if (PPToken_IsStringizingOp(head))
        {
            /*
            Each # preprocessing token in the replacement list for
            a function-like macro shall be followed by a parameter
            as the next preprocessing token in the replacement list.
            */

            // Stringizing operator
            int idx = FindNoSpaceIndex(&is, 0);
            struct TokenArray * aseq;

            if (idx != -1 &&
                args != NULL &&
                TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
            {
                /*
                If, in the replacement list, a parameter is immediately
                preceded by a # preprocessing token, both are replaced
                by a single character string literal preprocessing token that
                contains the spelling of the preprocessing token sequence
                for the corresponding argument.
                */
                StrBuilder strBuilder = STRBUILDER_INIT;
                AppendStringize(&strBuilder, aseq);
                TokenArray_Erase(&is, 0, idx + 1);

                //TODO token tipo?
                TokenArray_PushBack(&os, PPToken_Create(strBuilder.c_str, PPTokenType_Other));
                StrBuilder_Destroy(&strBuilder);

                PPToken_Delete(head);
                head = NULL;
                continue;
            }

        }

        else if (PPToken_IsConcatOp(head))
        {

            /*
            If, in the replacement list of a function-like macro,
            a parameter is immediately preceded or followed by
            a ## preprocessing token, the parameter is replaced by
            the corresponding arguments preprocessing token sequence;
            */
            int idx = FindNoSpaceIndex(&is, 0);

            if (idx != -1)
            {
                struct TokenArray * aseq;

                if (TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
                {
                    TokenArray_Erase(&is, 0, idx + 1);

                    // Only if actuals can be empty
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
                /*
                * Implement the following gcc extension:
                *  "`##' before a
                *   rest argument that is empty discards the preceding sequence of
                *   non-whitespace characters from the macro definition.  (If another macro
                *   argument precedes, none of it is discarded.)"
                * Otherwise, break to process a non-formal argument in the default way
                */
                struct TokenArray * aseq;

                if (!TokenArrayMap_Lookup(args, head->Lexeme, &aseq))
                {
                    /*
                    if (m.get_is_vararg())
                    {
                    ti2 = find_nonspace(ti + 1, is.end());

                    if (ti2 != is.end() && (ai = find_formal_argument(args, *ti2)) != args.end() && ai->second.size() == 0)
                    {
                    // All conditions satisfied; discard elements:
                    // <non-formal> <##> <empty-formal>
                    is.erase(is.begin(), ++ti2);
                    continue;
                    }
                    }
                    */
                    // Non-formal arguments don't deserve special treatment
                    TokenArray_PushBack(&os, head);
                    head = NULL; //moved
                }
                else
                {
                    // Paste but not expand LHS, RHS

                    // Only if actuals can be empty
                    if (aseq->Size == 0)
                    {
                        // Erase including ##
                        TokenArray_Erase(&is, 0, idx + 1);

                        int idx2 = FindNoSpaceIndex(&is, 0);

                        if (idx2 != -1)
                        {
                            struct TokenArray * aseq2;

                            if (!TokenArrayMap_Lookup(args, is.pItems[idx2]->Lexeme, &aseq2))
                            {
                                // Erase the ## RHS
                                TokenArray_Erase(&is, 0, idx + 1);
                                TokenArray_AppendCopy(&os, aseq);
                            }
                        }
                    }

                    else
                    {
                        // Erase up to ##
                        TokenArray_Print(&is);
                        //printf("-\n");
                        TokenArray_Erase(&is, 0, idx);
                        TokenArray_Print(&is);
                        //printf("-\n");
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
                //expand head
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
        head = NULL; //moved
    }
    //assert(head == NULL);
    struct TokenArray os2 = TOKENARRAY_INIT;
    HidenSetAdd(hs, &os, &os2);

    TokenArray_Swap(pOutputSequence, &os2);

    TokenArray_Destroy(&os);
    TokenArray_Destroy(&os2);
    TokenArray_Destroy(&is);
}

/*
* Return a macro argument token from tokens
* Used by gather_args.
* If get_more is true when tokens is exhausted read using pdtoken::getnext_noexpand
* (see explanation on that method's comment for why we use pdtoken, rather than pltoken)
* Leave in tokens the first token not gathered.
* If want_space is true return spaces, otherwise discard them
*/
void ArgToken(struct TokenArray * tokens,
              bool get_more,
              bool want_space,
              struct PPToken * token)
{
    struct PPToken * pToken = TokenArray_PopFront(tokens);
    PPToken_Swap(pToken, token);
    PPToken_Delete(pToken);
    pToken = NULL;

    /*  if (want_space)
      {
        if (tokens->Size > 0)
        {
        Token *pToken = TokenArray_PopFront(tokens);
        PPToken_Swap(pToken, token);
        PPToken_Destroy(pToken);
          return;
        }

        else if (get_more)
        {
          //Pdtoken t;
          //t.getnext_noexpand();
          //return (t);
        }

      else
      {
        String2_Set(&token->Lexeme, NULL);
        //return Ptoken(EOF, "");
      }
      }

      else
      {
        while (tokens->Size > 0 && PPToken_IsSpace(tokens->pItems[0]))
        {
        Token* p = TokenArray_PopFront(tokens);
        PPToken_Delete(p);
        }

        if (tokens->Size > 0)
        {
        Token* p = TokenArray_PopFront(tokens);
        PPToken_Swap(p, token);
        PPToken_Delete(p);

          return;
        }

        else if (get_more)
        {
          //Pdtoken t;

          //do
          //{
            //t.getnext_noexpand_nospc();
          //}
          //while (t.get_code() != EOF && t.is_space());

          //return (t);
        }

      else
      {
        String2_Set(&token->Lexeme, NULL);
        //return Ptoken(EOF, "");
      }
      }  */
}

/*
* Get the macro arguments specified in formal_args, initiallly by
* removing them from tokens, then, if get_more is true,
from pdtoken.getnext_noexpand.
* The opening bracket has already been gathered.
* Build the map from formal name to argument value args.
* Return in close the closing bracket token (used for its hideset)
* Return true if ok, false on error.
*/
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
            // Vararg last argument is optional; terminate with ) or ,
            terminate = '.';
        }

        else
        {
            terminate = ',';
        }

        int bracket = 0;

        // Get a single argument
        for (;;)
        {
            ArgToken(tokens, get_more, true, &t);
            //printf("tokens=");
            TokenArray_Print(tokens);
            //printf("\n");

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

            else if (PPToken_IsChar(&t, '\0')) //EOF
            {
                /*
                * @error
                * The end of file was reached while
                * gathering a macro's arguments
                */
                //printf("macro [%s] EOF while reading function macro arguments", name);
                return (false);
            }

            else
            {
            }


            TokenArray_PushBack(pV, PPToken_Clone(&t));
        }

        //printf("Gather args returns: ");
        TokenArray_Print(pV);
        //printf("\n");

        // Check if varargs last optional argument was not supplied
        if (terminate == '.' && PPToken_IsChar(&t, ')'))
        {
            i++;
            struct TokenArray * pV2 = TokenArray_Create();

            TokenArrayMap_SetAt(args,
                                formal_args->pItems[i]->Lexeme,
                                pV2);

            // Instantiate argument with an empty value list
            //args[(*i).get_val()];
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
            /*
            * @error
            * The arguments to a function-like macro did
            * not terminate with a closing bracket
            */
            //printf("macro [%s] close bracket expected for function-like macro", name);
            return (false);
        }
    }


    PPToken_Destroy(&t);

    return (true);
}

/*
* Remove from tokens and return the elements comprising the arguments to the defined
* operator, * such as "defined X" or "defined(X)"
* This is the rule when processing #if #elif expressions
*/
void GatherDefinedOperator(struct TokenArray * tokens,
                           const struct MacroMap * macros,
                           struct TokenArray * result)
{
    //struct TokenArray tokens = TOKENARRAY_INIT;
    //TokenArray_AppendCopy(&tokens, tokensIn);

    // Skip leading space
    while (PPToken_IsSpace(tokens->pItems[0]))
    {
        struct PPToken * pp = TokenArray_PopFront(tokens);
        TokenArray_PushBack(result, pp);
    }

    if ((PPToken_IsIdentifier(tokens->pItems[0])))
    {
        // defined X form
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
        // defined (X) form


        PPToken_Delete(TokenArray_PopFront(tokens));




        // Skip spaces
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken * pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsIdentifier(tokens->pItems[0]))
        {
            //goto error;
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

        //PPToken* pp = TokenArray_PopFront(&tokens);
        //TokenArray_PushBack(result, pp);

        // Skip spaces
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken * pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsChar(tokens->pItems[0], ')'))
        {
            //goto error;
        }

        PPToken_Delete(TokenArray_PopFront(tokens));
        //TokenArray_PushBack(result, pp);

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

    //printf("Expanding: ");
    TokenArray_Print(&ts);
    //printf("\n");

    struct PPToken * pHead = NULL; //muito facil ter leaks
    while (ts.Size > 0)
    {
        //printf("r = ");
        TokenArray_Print(&r);
        //printf("\n");

        //assert(pHead == NULL);
        pHead =
            TokenArray_PopFront(&ts);

        if (!PPToken_IsIdentifier(pHead))
        {
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
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
            //if eval mode se nao achar a macro
            //ela vira zero
            if (evalmode)
            {
                Free(pHead->Lexeme);
                pHead->Lexeme = StrDup("0");
                pHead->Token = PPTokenType_Number;
            }
            // Nothing to do if the identifier is not a macro
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
            continue;
        }

        struct PPToken * pFound =
            TokenSet_Find(&pHead->HiddenSet, pMacro->Name);

        if (pFound)
        {
            // Skip the head token if it is in the hideset
            //printf("Skipping (head is in HS)\n");
            TokenArray_PushBack(&r, pHead);
            pHead = NULL;//moved
            continue;
        }

        struct TokenArray removed_spaces = TOKENARRAY_INIT;

        //printf("replacing for %s tokens=", pMacro->Name);
        TokenArray_Print(&ts);
        //printf("\n");

        if (!pMacro->bIsFunction)
        {
            // Object-like macro
            //printf("Object-like macro\n");

            TokenSet hiddenSet = TOKENSET_INIT;
            TokenSetAppendCopy(&hiddenSet, &pHead->HiddenSet);
            TokenSet_PushBack(&hiddenSet, PPToken_Create(pHead->Lexeme, pHead->Token));

            PPToken_Delete(pHead);
            pHead = NULL; //usado deletado

            struct TokenArray s = TOKENARRAY_INIT;

            SubstituteArgs(pMacro,
                           macros,
                           &pMacro->TokenSequence,
                           NULL, //empty args
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
            //printf("Application of a function-like macro\n");

            // Map from formal name to value
            TokenArrayMap args = TOKENARRAYMAP_INIT;

            PPToken_Delete(TokenArray_PopFront(&ts));

            struct PPToken close = TOKEN_INIT;

            if (!GatherArgs(pHead->Lexeme,
                &ts,
                &pMacro->FormalArguments,
                &args,
                get_more,
                false, /*m.is_vararg,*/
                &close))
            {
                PPToken_Destroy(&close);
                PPToken_Delete(pHead);
                pHead = NULL;//deletado
                continue; // Attempt to bail-out on error
            }


            /*
            After the arguments for the invocation of a function-like
            macro have been identified, argument substitution takes place.
            */

            TokenSet hs = TOKENSET_INIT;

            //merge head and close
            SetIntersection(&pHead->HiddenSet,
                            &close.HiddenSet,
                            &hs);
            TokenSet_PushBack(&hs, PPToken_Create(pMacro->Name, PPTokenType_Identifier));

            PPToken_Delete(pHead);
            pHead = NULL;//deletado

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
            // Function-like macro name lacking a (
            //printf("splicing: [");
            TokenArray_Print(&removed_spaces);
            //printf("]\n");
            TokenArray_AppendMove(&removed_spaces, &ts);
            TokenArray_Swap(&removed_spaces, &ts);
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
        }

        //TokenArray_Contains(pHead->HiddenSet, pMacro->Name);
        TokenArray_Destroy(&removed_spaces);
    }

    //assert(pHead == NULL);

    TokenArray_Swap(&r, pOutputSequence2);

    TokenArray_Destroy(&r);
    TokenArray_Destroy(&ts);
}


/*
* Try to ensure that ts has at least one non-space token
* Return true if this is the case
* Return any discarded space tokens in removed
*/
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

    /*if (get_more)
    {
    Pdtoken t;

    for (;;)
    {
    t.getnext_noexpand();

    if (t.get_code() == EOF)
    return (false);

    else if (t.is_space())
    removed.push_back(t);

    else
    break;
    }

    ts.push_back(t);
    return (true);
    }*/

    return (false);
}




// Paste last of left side with first of right side

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
            //Junta o ultimo token do lado esquerdo
            //com o primeiro do lado direito

            StrBuilder strNewLexeme = STRBUILDER_INIT;

            if (ls.Size > 0)
            {
                //printf("glue LS: ");
                //printf("%s", ls.pItems[ls.Size - 1]->Lexeme);
                //printf("\n");

                StrBuilder_Append(&strNewLexeme, ls.pItems[ls.Size - 1]->Lexeme);
                TokenArray_Pop(&ls);
            }

            if (rs.Size > 0)
            {
                //printf("glue RS: ");
                //printf("%s", rs.pItems[0]->Lexeme);
                //printf("\n");
                StrBuilder_Append(&strNewLexeme, rs.pItems[0]->Lexeme);
                TokenArray_Pop(&rs);
            }

            //tipo?
            TokenArray_PushBack(&ls, PPToken_Create(strNewLexeme.c_str, PPTokenType_Other));
            StrBuilder_Destroy(&strNewLexeme);

            TokenArray_AppendMove(&ls, &rs);
            TokenArray_Swap(out, &ls);
        }
    }

    //printf("glue returns: ");
    TokenArray_Print(out);
    //printf("\n");

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
        //assert(false);
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
        //printf("(empty)");
    }

    //for (int i = 0; i < tokens->Size; i++)
    //{

      //printf(" '%s' ", tokens->pItems[i]->Lexeme);

    //}
    //printf("\n");

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

void TokenSet_PushBack(TokenSet * p, struct PPToken * pItem) /*custom*/
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
            //if (comp(*first1, *first2))
            if (strcmp(first1->Lexeme, first2->Lexeme) == 0)
            {
                ++first1;
            }

            else
            {
                //if (!comp(*first2, *first1))
                if (strcmp(first2->Lexeme, first1->Lexeme) != 0)
                {
                    //*d_first++ = *first1++;
                    TokenSet_PushBack(pResult, PPToken_Clone(first1));
                    first1++;
                    //*d_first++ = *first1++;
                    //d_first
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

/*
http://en.cppreference.com/w/cpp/algorithm/set_intersection
template<class InputIt1, class InputIt2,
class OutputIt, class Compare>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
InputIt2 first2, InputIt2 last2,
OutputIt d_first, Compare comp)
{
while (first1 != last1 && first2 != last2) {
if (comp(*first1, *first2)) {
++first1;
} else {
if (!comp(*first2, *first1)) {
*d_first++ = *first1++;
}
++first2;
}
}
return d_first;
}
*/
//#include "Map.h"


//#include "stdafx.h"






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
    // hash key to unsigned int value by pseudorandomizing transform
    // (algorithm copied from STL string hash in xfunctional)
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
                // remove from list
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



void Options_Destroy(struct Options * options) /*default*/
{
}
//#include "Map.h"


//#include "stdafx.h"








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
    // hash key to unsigned int value by pseudorandomizing transform
    // (algorithm copied from STL string hash in xfunctional)
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
                // remove from list
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

        //if (pKeyValue == NULL)
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

        //else
        //{
        //    result = 1;
        //    pKeyValue->pValue = newValue;
        //    strset(pKeyValue->Key, Key);
        //}
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
            //Obs enum struct e union compartilham um mapa unico
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
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TStructUnionSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, structTagName) == 0)
                {
                    pStructUnionSpecifier =
                        (TStructUnionSpecifier *)pKeyValue->pValue;
                    if (pStructUnionSpecifier->StructDeclarationList.Size > 0 ||
                        pStructUnionSpecifier->UnionSet.pHead != NULL)
                    {
                        //Se achou definicao completa pode sair
                        //se achou um _union pode sair tb
                        //pois nao tem definicao completa de union
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
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TEnumSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, enumTagName) == 0)
                {
                    pEnumSpecifier =
                        (TEnumSpecifier *)pKeyValue->pValue;
                    if (pEnumSpecifier->EnumeratorList.pHead != NULL)
                    {
                        //Se achou definicao completa pode sair
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

                //typedef X Y;
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
                        //assert(false);
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        //eh um typedef indireto
                        pDeclarationResult =
                            SymbolMap_FindTypedefDeclarationTarget(pMap, indirectTypedef);
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
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

//Acha o tipo final de um typedef
//e vai somando as partes dos declaratos
//por exemplo no meio do caminho dos typedefs
//pode ter ponteiros e depois const etc.
TDeclarationSpecifiers * SymbolMap_FindTypedefTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    //TDeclaration* pDeclarationResult = NULL;
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

                //typedef X Y;
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
                        //assert(false);
                        break;

                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
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
                            //copiar o pointer list deste typedef para o outro
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            //eh um typedef indireto
                            pSpecifiersResult =
                                SymbolMap_FindTypedefTarget(pMap, indirectTypedef, declarator);
                        }
                        else
                        {
                            //assert(false);
                        }
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
                        pSpecifiersResult = &pDeclaration->Specifiers;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pSpecifiersResult;// &pDeclarationResult->Specifiers;
}



//Acha o primeiro typedef
//somas as partes do declarator
TDeclarationSpecifiers * SymbolMap_FindTypedefFirstTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    //TDeclaration* pDeclarationResult = NULL;
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

                //typedef X Y;
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
                        //assert(false);
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
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
                            //copiar o pointer list deste typedef para o outro
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            //eh um typedef indireto
                            pSpecifiersResult = &pDeclaration->Specifiers;
                            //pSpecifiersResult =
                                //SymbolMap_FindTypedefTarget(pMap, indirectTypedef, declarator);
                        }
                        else
                        {
                            //assert(false);
                        }
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);

                        //copiar o pointer list deste typedef para o outro
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

    return pSpecifiersResult;// &pDeclarationResult->Specifiers;

}
TTypeSpecifier * SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap * pMap,
    const char * typedefName)
{
    /*Sample:
    struct X;
    typedef struct X X;
    struct X { int i;  };
    typedef X Y;
    */

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
                        //assert(false);
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
                        //assert(false);
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
                //ja achou
                break;
            }
        }
    }
    return pSpecifierTarget;
}







//Define to include modications




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
//static bool Is_Type_QualifierFirst(Tokens token);
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
        //Tokens para linhas do pre processador
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
        //fim tokens preprocessador
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
    ///////
    SymbolMap_Init(&parser->GlobalScope);
    parser->pCurrentScope = &parser->GlobalScope;
    parser->bPreprocessorEvalFlag = false;
    /////////

    //Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
    parser->bError = false;

    StrBuilder_Init(&parser->ErrorMessage);


    /////////
    Scanner_InitString(&parser->Scanner, name, Text);

    //sair do BOF
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

    /////
    SymbolMap_Init(&parser->GlobalScope);
    parser->pCurrentScope = &parser->GlobalScope;

    //////
    //Map_Init(&parser->TypeDefNames, SYMBOL_BUCKETS_SIZE);
    parser->bError = false;


    StrBuilder_Init(&parser->ErrorMessage);
    Scanner_Init(&parser->Scanner);


    ////////
    Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);

    //Scanner_Match(&parser->Scanner);
    //sair do BOF
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
    //assert(clueList0.pHead == NULL);
    TScannerItemList_Destroy(&clueList0);

}





void Parser_Destroy(Parser * parser)
{
    TScannerItemList_Destroy(&parser->ClueList);

    SymbolMap_Destroy(&parser->GlobalScope);

    //Map_Destroy(&parser->TypeDefNames, NULL);
    StrBuilder_Destroy(&parser->ErrorMessage);
    Scanner_Destroy(&parser->Scanner);
}

static const char * GetName()
{
    static char buffer[2];
    buffer[0] = '\0';
    //static int i = 0;
    //strcat(buffer, "__noname");
    //char bn[20];
    //_itoa(i, bn, 10);
    //strcat(buffer, bn);
    //i++;
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
    //    //assert(false);
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
        //ja esta com erro entao eh ruido...
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
    ////assert(pPosition->FileIndex >= 0);
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
    ////assert(listOpt != NULL);
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
            //so adiciona os espacos no cara atual
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
        //assert(false);
        return "";
    }

    return Scanner_LexemeAt(&parser->Scanner, 0);
}

bool ErrorOrEof(Parser * parser)
{
    return Parser_HasError(parser) ||
        Parser_CurrentToken(parser) == TK_EOF;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


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

        //////////
        //extensions
    case TK_LEFT_SQUARE_BRACKET: //lambda-expression
                                 /////////

                                 //desde que nao seja cast
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
    //c++
    /*
    lambda-expression:
    lambda-introducer lambda-declaratoropt compound-statement

    lambda-introducer:
    [ lambda-captureopt]

    lambda-capture:
    capture-default
    capture-list
    capture-default , capture-list

    capture-default:
    &=

    capture-list:
    capture ...opt
    capture-list , capture ...opt

    capture:
    simple-capture
    init-capture

    simple-capture:
    identifier
    & identifier
    this

    init-capture:
    identifier initializer
    & identifier initializer

    lambda-declarator:
    ( parameter-declaration-clause ) mutableopt
    exception-specificationopt attribute-specifier-seqopt trailing-return-typeopt
    */

    /*
    lambda-expression:
    [] ( parameters opt ) compound-statement
    [] compound-statement
    */
    TPrimaryExpressionLambda * pPrimaryExpressionLambda = TPrimaryExpressionLambda_Create();

    *ppPrimaryExpression = (TExpression *)pPrimaryExpressionLambda; //out

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



    /*
    (6.5.1) primary-expression:
    identifier
    constant
    string-literal
    ( expression )
    generic-selection
    */
    * ppPrimaryExpression = NULL; //out

    Tokens token = Parser_CurrentToken(ctx);
    const char * lexeme = Lexeme(ctx);
    //PreprocessorTokenIndex(ctx);
    //-2 nem eh macro
    //-1 inicio de macro
    //-3 fim de macro


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
                    //identificador magico
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

        //    //TNodeClueList_MoveToEnd(&pPrimaryExpressionValue->ClueList, &ctx->Scanner.ClueList);
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
    //_Generic

    /*
    (6.5.1.1) generic-selection:
    _Generic ( assignment-expression , generic-assoc-list )
    */
}

void GenericAssocList(Parser * ctx)
{

    //type-name default

    /*
    (6.5.1.1) generic-assoc-list:
    generic-association
    generic-assoc-list , generic-association
    */
}

void GenericAssociation(Parser * ctx)
{
    //type-name default

    /*
    (6.5.1.1) generic-association:
    type-name : assignment-expression
    default : assignment-expression
    */
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
    /*
    type-name:
    specifier-qualifier-list abstract-declaratoropt
    */

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
    //ja entra aqui sendo uma  postfix-expression antes
    /*
    (6.5.2) postfix-expression:

    postfix-expression [ expression ]
    postfix-expression ( argument-expression-listopt )
    postfix-expression . identifier
    postfix-expression -> identifier
    postfix-expression ++
    postfix-expression --

    */

    Tokens token = Parser_CurrentToken(ctx);


    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        //aqui eu posso marcar a funcao como usada.

        pPostfixExpressionCore->token = token;


        //  postfix-expression ( argument-expression-listopt )    
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
        // postfix-expression [ expression ]

        Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET,
            &pPostfixExpressionCore->ClueList0);

        Expression0(ctx, &pPostfixExpressionCore->pExpressionRight);

        Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_FULL_STOP:
    {
        // postfix-expression . identifier
        pPostfixExpressionCore->token = token;

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);

        PTR_STRING_REPLACE(pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER,
            &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_ARROW:
    {
        // postfix-expression -> identifier
        pPostfixExpressionCore->token = token;

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);

        PTR_STRING_REPLACE(pPostfixExpressionCore->Identifier, Lexeme(ctx));

        Parser_MatchToken(ctx, TK_IDENTIFIER, &pPostfixExpressionCore->ClueList1);
    }
    break;

    case TK_PLUSPLUS:
    {
        pPostfixExpressionCore->token = token;
        //postfix-expression ++

        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);
    }
    break;

    case TK_MINUSMINUS:
    {
        //  postfix-expression --
        pPostfixExpressionCore->token = token;
        Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);
    }
    break;

    default:
        // //assert(false);
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
        //assert(false);
        break;
    }


}

void PostfixExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL;//out

                         /*
                         (6.5.2) postfix-expression:
                         postfix-expression ( argument-expression-listopt )
                         ( type-name ) { initializer-list }
                         ( type-name ) { initializer-list , }

                         primary-expression
                         postfix-expression [ expression ]
                         postfix-expression . identifier
                         postfix-expression -> identifier
                         postfix-expression ++
                         postfix-expression --

                         */

    Tokens token = Parser_CurrentToken(ctx);



    if (token == TK_LEFT_PARENTHESIS)
    {
        const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);
        Tokens lookAheadToken = Parser_LookAheadToken(ctx);

        if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
        {
            // ( type-name ) { initializer-list }

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
            //primary-expression
            TExpression * pPrimaryExpression;
            PrimaryExpression(ctx, &pPrimaryExpression);
            *ppExpression = pPrimaryExpression;
        }
    }
    else
    {
        //tem que ser?
        //assert(IsFirstOfPrimaryExpression(token));

        //primary-expression
        TExpression * pPrimaryExpression;
        PrimaryExpression(ctx, &pPrimaryExpression);
        *ppExpression = pPrimaryExpression;
    }

    token = Parser_CurrentToken(ctx);
    if (IsFirstOfPrimaryExpression(token))
    {

        // //assert(false); //pergunta deve continuar? ta certo?

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
            //assert(false);
            break;
        }

    }

}

void ArgumentExpressionList(Parser * ctx, TExpression ** ppExpression)
{
    /*(6.5.2) argument-expression-list:
    assignment-expression
    argument-expression-list , assignment-expression
    */
    TExpression * pAssignmentExpression;
    AssignmentExpression(ctx, &pAssignmentExpression);
    *ppExpression = pAssignmentExpression;

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COMMA)
    {
        TBinaryExpression * pExpr =
            TBinaryExpression_Create();

        Parser_Match(ctx, &pExpr->ClueList0);// &pAssignmentExpression->ClueList);

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
        //type-qualifier
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:
        //
        bResult = true;
        break;
#ifdef LANGUAGE_EXTENSIONS

        //type-qualifier-extensions 


    case TK_AUTO:
    case TK_LEFT_SQUARE_BRACKET:


        bResult = true;
        break;
#endif
    default:
        //assert(false);
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
        //        bResult = DeclarationsMap_IsTypeDef(&ctx->Symbols, lexeme);
        break;

        //type-qualifier
    case TK_CONST:
    case TK_RESTRICT:
    case TK_VOLATILE:
    case TK__ATOMIC:

#ifdef LANGUAGE_EXTENSIONS

    case TK_AUTO:


#endif

        //type-specifier
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        //microsoft
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        //
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
        //assert(false);
        break;
    }

    return bResult;
}

void UnaryExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; //out

                          /*(6.5.3) unary-expression:
                          postfix-expression
                          ++ unary-expression
                          -- unary-expression
                          unary-operator cast-expression
                          sizeof unary-expression
                          sizeof ( type-name )
                          alignof ( type-name )

                          unary-operator: one of
                          & * + - ~ !
                          */

    Tokens token0 = Parser_CurrentToken(ctx);
    Tokens tokenAhead = Parser_LookAheadToken(ctx);
    const char * lookAheadlexeme = Parser_LookAheadLexeme(ctx);

    if (IsTypeName(ctx, tokenAhead, lookAheadlexeme))
    {
        //first para postfix-expression
        TExpression * pPostfixExpression;
        PostfixExpression(ctx, &pPostfixExpression);
        *ppExpression = (TExpression *)(pPostfixExpression);
        return;
    }

    else if (IsFirstOfPrimaryExpression(token0))
    {
        //primary-expression é first para postfix-expression

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

    //unary-operator cast-expression
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

    //////////////

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
                //sizeof(type-name)
                Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pUnaryExpressionOperator->ClueList1);
                TypeName(ctx, &pUnaryExpressionOperator->TypeName);
                Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pUnaryExpressionOperator->ClueList2);
            }
            else
            {
                //sizeof unary-expression
                TExpression * pTUnaryExpression;
                UnaryExpression(ctx, &pTUnaryExpression);
                pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
            }
        }
        else
        {
            //sizeof do tipo desta expressao
            TExpression * pTUnaryExpression;
            UnaryExpression(ctx, &pTUnaryExpression);
            pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
        }
    }
    break;

    case TK__ALINGOF:
        //Match
        //assert(false);
        break;
    case TK_EOF:
        break;
        //TODO ver tudo que pode ser follow
    default:
        ////assert(false);
        //        SetUnexpectedError(ctx, "Assert", "");
        //aqui nao eh erro necessariamente
        break;
    }

}

void CastExpression(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; //out

                          /*
                          cast-expression:
                          unary-expression
                          ( type-name ) cast-expression
                          */

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
                //se isso acontecer, quer dizer que eh uma postfix-expression
                //entao deveria ter sido expandido com
                //unary-expression -> postfix-expression ->
                /*
                (6.5.2) postfix-expression:
                ...
                ( type-name ) { initializer-list }
                ( type-name ) { initializer-list , }
                */

                Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, NULL);

                TPostfixExpressionCore * pTPostfixExpressionCore =
                    TPostfixExpressionCore_Create();
                pTPostfixExpressionCore->pTypeName = TTypeName_Create();
                TTypeName_Swap(pTPostfixExpressionCore->pTypeName, &typeName);

                //pTPostfixExpressionCore->pInitializerList = TInitializerList_Create();
                Initializer_List(ctx, &pTPostfixExpressionCore->InitializerList);

                //Initializer_List(ctx, pTPostfixExpressionCore->pInitializerList);


                if (Parser_CurrentToken(ctx) == TK_COMMA)
                {
                    Parser_Match(ctx, NULL);
                }
                Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET, NULL);
                *ppExpression = (TExpression *)pTPostfixExpressionCore;
                //PostfixExpressionCore(ctx, pTPostfixExpressionCore);
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


    /*
    (6.5.5) multiplicative-expression:
    cast-expression                                // identifier  constant  string-literal  (  _Generic ++	  -- 	 & * + - ~ ! 		 sizeof 		 sizeof		 alignof
    multiplicative-expression * cast-expression
    multiplicative-expression / cast-expression
    multiplicative-expression % cast-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void AdditiveExpression(Parser * ctx, TExpression ** ppExpression)
{

    /*
    (6.5.6) additive-expression:
    multiplicative-expression
    additive-expression + multiplicative-expression
    additive-expression - multiplicative-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }

}

void ShiftExpression(Parser * ctx, TExpression ** ppExpression)
{

    /*(6.5.7) shift-expression:
    additive-expression
    shift-expression << additive-expression
    shift-expression >> additive-expression
    */


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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void RelationalExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*
    (6.5.8) relational-expression:
    shift-expression
    relational-expression < shift-expression
    relational-expression > shift-expression
    relational-expression <= shift-expression
    relational-expression >= shift-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }

}

void EqualityExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*(6.5.9) equality-expression:
    relational-expression
    equality-expression == relational-expression
    equality-expression != relational-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void AndExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*(6.5.10) AND-expression:
    equality-expression
    AND-expression & equality-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void ExclusiveOrExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*
    (6.5.11) exclusive-OR-expression:
    AND-expression
    exclusive-OR-expression ^ AND-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }

}

void InclusiveOrExpression(Parser * ctx, TExpression ** ppExpression)
{

    /*
    (6.5.12) inclusive-OR-expression:
    exclusive-OR-expression
    inclusive-OR-expression | exclusive-OR-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void LogicalAndExpression(Parser * ctx, TExpression ** ppExpression)
{

    /*
    (6.5.13) logical-AND-expression:
    inclusive-OR-expression
    logical-AND-expression && inclusive-OR-expression
    */

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
        //assert(false);
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
        //assert(false);
        break;
    }
}

void LogicalOrExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*(6.5.14) logical-OR-expression:
    logical-AND-expression
    logical-OR-expression || logical-AND-expression
    */


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
        //assert(false);
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
        //assert(false);
        break;
    }
}


void ConditionalExpression(Parser * ctx, TExpression ** ppExpression)
{
    /*(6.5.15) conditional-expression:
    logical-OR-expression
    logical-OR-expression ? expression : conditional-expression
    */
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
    /*(6.5.16) assignment-expression:
    conditional-expression
    unary-expression assignment-operator assignment-expression

    (6.5.16) assignment-operator: one of
    = *= /= %= += -= <<= >>= &= ^= |=
    */


    //Não sei se eh  conditional-expression ou
    //unary-expression
    //Mas a conditional-expression faz tambem a
    //unary-expression
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

        //Significa que o anterior deve ser do tipo  unary-expression
        //embora tenhamos feito o parser de conditional-expression
        //se nao for é erro.
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
        //É apenas conditional-expression
        break;
    }
}

void Expression0(Parser * ctx, TExpression ** ppExpression)
{
    *ppExpression = NULL; //out
                          /*
                          (6.5.17) expression:
                          assignment-expression
                          expression , assignment-expression
                          */
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
    *ppExpression = NULL; //out

                          /*
                          (6.6) constant-expression:
                          conditional-expression
                          */
    ConditionalExpression(ctx, ppExpression);
}


///////////////////////////////////////////////////////////////////////////////


void Designator(Parser * ctx, TDesignator * pDesignator);
void Designator_List(Parser * ctx, TDesignatorList * pDesignatorList);
void Designation(Parser * ctx, TDesignatorList * pDesignatorList);
void Initializer_List(Parser * ctx, TInitializerList * pInitializerList);
//void Assignment_Expression(Parser* ctx, TExpressionStatement* pExpressionStatement, Tokens endToken1, Tokens endToken2);
bool Statement(Parser * ctx, TStatement ** ppStatement);
//void Constant_Expression(Parser* ctx, Tokens endToken1, Tokens endToken2, ScannerItemStack* outStack);
void Compound_Statement(Parser * ctx, TStatement ** ppStatement);
//void Expression(Parser* ctx, TExpression** pExpression, Tokens endToken1, Tokens endToken2);
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
    /*
    expression-statement:
    expressionopt;
    */
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
    /*
    selection-statement:
    if ( expression ) statement
    if ( expression ) statement else statement
    switch ( expression ) statement
    */
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
        //assert(false);
        break;
    }
}

void Jump_Statement(Parser * ctx, TStatement ** ppStatement)
{
    /*
    jump-statement:
    goto identifier ;
    continue ;
    break ;
    return expressionopt ;
    */
    //jump-statement
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
        //assert(false);
        break;
    }
}

void Iteration_Statement(Parser * ctx, TStatement ** ppStatement)
{
    /*
    iteration-statement:
    while ( expression ) statement
    do statement while ( expression ) ;
    for ( expressionopt ; expressionopt ; expressionopt ) statement
    for ( declaration expressionopt ; expressionopt ) statement
    */
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

        Parser_Match(ctx, &pDoStatement->ClueList0); //do

        Statement(ctx, &pDoStatement->pStatement);

        Parser_MatchToken(ctx, TK_WHILE, &pDoStatement->ClueList1); //while

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDoStatement->ClueList2); //(

        Expression0(ctx, &pDoStatement->pExpression);

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDoStatement->ClueList3); //)

        Parser_MatchToken(ctx, TK_SEMICOLON, &pDoStatement->ClueList4); //;
    }
    break;

    case TK_FOR:
    {
        TForStatement * pIterationStatement = TForStatement_Create();
        *ppStatement = (TStatement *)pIterationStatement;

        Parser_Match(ctx, &pIterationStatement->ClueList0);

        token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pIterationStatement->ClueList1);

        //primeira expressao do for
        if (token != TK_SEMICOLON)
        {
            //
            //for (expressionopt; expressionopt; expressionopt) statement
            //for (declaration expressionopt; expressionopt) statement

            bool bHasDeclaration = Declaration(ctx, &pIterationStatement->pInitDeclarationOpt);

            if (bHasDeclaration)
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //Esta eh a 2 expressao do for, a declaracao ja comeu 1
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }
                else
                {
                    //segunda expressao vazia                        
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }
            }

            else
            {
                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //primeira expressao do for
                    Expression0(ctx, &pIterationStatement->pExpression1);


                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);
                }

                token = Parser_CurrentToken(ctx);

                if (token != TK_SEMICOLON)
                {
                    //segunda expressao do for
                    Expression0(ctx, &pIterationStatement->pExpression2);

                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
                }

                else
                {
                    //segunda expressao vazia                        
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
                }

            }
        }

        else
        {
            //primeira expressao do for vazia

            Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList2);

            token = Parser_CurrentToken(ctx);

            if (token != TK_SEMICOLON)
            {
                //Esta eh a 2 expressao do for, a declaracao ja comeu 1
                Expression0(ctx, &pIterationStatement->pExpression2);


                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
            }

            else
            {
                //segunda expressao do for vazia tb
                Parser_MatchToken(ctx, TK_SEMICOLON, &pIterationStatement->ClueList3);
            }
        }

        token = Parser_CurrentToken(ctx);

        //terceira expressao do for
        if (token != TK_RIGHT_PARENTHESIS)
        {
            Expression0(ctx, &pIterationStatement->pExpression3);
        }

        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pIterationStatement->ClueList4);

        Statement(ctx, &pIterationStatement->pStatement);
    }
    break;

    default:
        //assert(false);
        break;
    }
}


void Labeled_Statement(Parser * ctx, TStatement ** ppStatement)
{
    /*
    labeled-statement:
    identifier : statement (ver Labeled_StatementLabel)
    case constant-expression : statement
    default : statement
    */
    TLabeledStatement * pLabeledStatement = TLabeledStatement_Create();
    *ppStatement = (TStatement *)pLabeledStatement;
    Tokens token = Parser_CurrentToken(ctx);
    pLabeledStatement->token = token;

    if (token == TK_IDENTIFIER)
    {
        //aqui nao eh um tipo
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
    /*
    __asm assembly-instruction ;opt
    __asm { assembly-instruction-list };opt
    */
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
        //sem ;
        //    __asm int 0x2c
        //chato
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
                //__asm mov al, 2   __asm mov dx, 0xD007   __asm out dx, al
                //chute na verdade..
                //dificil saber aonde termina
                //https://msdn.microsoft.com/en-us/library/45yd4tzz.aspx
                break;
            }

            if (token == TK_SEMICOLON)
            {
                break;
            }

            Parser_Match(ctx, NULL);
        }
    }

    //opcional
    token = Parser_CurrentToken(ctx);

    if (token == TK_SEMICOLON)
    {
        Parser_Match(ctx, NULL);
    }
}

bool Statement(Parser * ctx, TStatement ** ppStatement)
{
    //assert(*ppStatement == NULL);

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

        //case TK_ELSE:
        ////assert(false);
        //Ele tem que estar fazendo os statement do IF!
        //bResult = true;
        //Parser_Match(ctx, NULL); //else
        //poderia retornar uma coisa so  p dizer q eh else
        //Statement(ctx, obj);
        //break;

        //iteration-statement
    case TK_WHILE:
    case TK_FOR:
    case TK_DO:
        bResult = true;
        Iteration_Statement(ctx, ppStatement);
        break;

        //jump-statement
    case TK_GOTO:
    case TK_CONTINUE:
    case TK_BREAK:
    case TK_RETURN:
        bResult = true;
        Jump_Statement(ctx, ppStatement);
        break;

        //lista de first para expressões
        //expression-statement
    case TK_LEFT_SQUARE_BRACKET://lamda todo isprimeiryfirst
    case TK_LEFT_PARENTHESIS:
    case TK_SEMICOLON:

    case TK_DECIMAL_INTEGER:
    case TK_FLOAT_NUMBER:
    case TK_STRING_LITERAL:


        //unary
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:

    case TK_SIZEOF:

        //unary-operator
    case TK_AMPERSAND:
    case TK_ASTERISK:
    case TK_PLUS_SIGN:
    case TK_HYPHEN_MINUS:
    case TK_TILDE:
    case TK_EXCLAMATION_MARK:
#ifdef LANGUAGE_EXTENSIONS
        //unary-operator-extension
    case TK_ANDAND: //&&
#endif
        bResult = true;
        Expression_Statement(ctx, ppStatement);
        break;

    case TK_IDENTIFIER:

        if (IsTypeName(ctx, TK_IDENTIFIER, lexeme))
        {
            //É uma declaracao
        }
        else
        {
            if (Parser_LookAheadToken(ctx) == TK_COLON)
            {
                //era um label..
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
    case TK__INLINE: //microscoft
    case TK__NORETURN:
    case TK__ALIGNAS:

        //type-qualifier
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
        //microsoft
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        /////////
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
        //bResult = true;
        //SetType(pStatement, "expression-statement");
        //Expression_Statement(ctx, pStatement);
        break;
    }

    return bResult;
}

void Block_Item(Parser * ctx, TBlockItem ** ppBlockItem)
{
    /*
    block-item:
    declaration
    statement
    */
    *ppBlockItem = NULL;
    TStatement * pStatement = NULL;

    if (Statement(ctx, &pStatement))
    {
        *ppBlockItem = (TBlockItem *)pStatement;
        //assert(*ppBlockItem != NULL);
    }

    else
    {


        TAnyDeclaration * pDeclaration;
        Declaration(ctx, &pDeclaration);
        *ppBlockItem = (TBlockItem *)pDeclaration;
        //assert(*ppBlockItem != NULL);
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
            //terminou
            break;
        }

        if (ErrorOrEof(ctx))
            break;
    }
}

void Compound_Statement(Parser * ctx, TStatement ** ppStatement)
{
    /*
    compound-statement:
    { block-item-listopt }
    */
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

    //SymbolMap_Print(ctx->pCurrentScope);

    ctx->pCurrentScope = BlockScope.pPrevious;
    SymbolMap_Destroy(&BlockScope);
}

void Struct_Or_Union(Parser * ctx,
    TStructUnionSpecifier * pStructUnionSpecifier)
{
    /*
    struct-or-union:
    struct
    union
    */
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
        //assert(false);
        break;
    }
}

void Static_Assert_Declaration(Parser * ctx, TStaticAssertDeclaration * pStaticAssertDeclaration)
{
    /*
    static_assert-declaration:
    _Static_assert ( constant-expression , string-literal ) ;
    */
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
    /*specifier-qualifier-list:
    type-specifier specifier-qualifier-listopt
    type-qualifier specifier-qualifier-listopt
    */
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
                //ATENCAO
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
            /*
            typedef int X;
            void F(int X ); //X vai ser variavel e nao tipo
            */

            Specifier_Qualifier_List(ctx, pSpecifierQualifierList);
        }
    }

}


void Struct_Declarator(Parser * ctx,

    TStructDeclarator ** ppTDeclarator2)
{
    /**
    struct-declarator:
    declarator
    declaratoropt : constant-expression
    */
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_COLON)
    {
        //AST TODO
        ////TNodeClueList_MoveToEnd(&ppTDeclarator2->ClueList, &ctx->Scanner.ClueList);

        Parser_Match(ctx, NULL);// &ppTDeclarator2->ClueList);
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
            Parser_Match(ctx, &pInitDeclarator->ClueList1); //_defval ou =
            Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);

            token = Parser_CurrentToken(ctx);

        }

#endif
    }
}

void Struct_Declarator_List(Parser * ctx,

    TStructDeclaratorList * pStructDeclarationList)
{
    /*
    struct-declarator-list:
    struct-declarator
    struct-declarator-list , struct-declarator
    */
    TStructDeclarator * pTDeclarator2 = NULL;// TDeclarator_Create();

    Struct_Declarator(ctx, &pTDeclarator2);
    TStructDeclaratorList_Add(pStructDeclarationList, pTDeclarator2);

    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            //Tem mais
            Parser_Match(ctx, &pTDeclarator2->ClueList0);
            //ANNOTATED AQUI TEM O COMENTARIO /*@= 1*/

            Struct_Declarator_List(ctx, pStructDeclarationList);
        }
        else if (token == TK_SEMICOLON)
        {
            //em ctx cluelist
            //ANNOTATED AQUI TEM O COMENTARIO /*@= 1*/
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
    /**
    struct-declaration:
    specifier-qualifier-list struct-declarator-listopt ;
    static_assert-declaration
    */
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
            //TODO AQUI TEM O COMENTARIO /*@= 1*/
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
    /*
    struct-declaration-list:
    struct-declaration
    struct-declaration-list struct-declaration
    */
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
        //Tem mais?
        Struct_Declaration_List(ctx, pStructDeclarationList);
    }
}

void UnionSetItem(Parser * ctx, TUnionSet * p)
{
    /*
    _union-set-item:
    struct Identifier
    union Identifier
    Identifier
    */
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
    /*
    _union-set-list:
    _union-set-item
    _union-set-item | _union-set-list
    */
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
    /*
    _union-set:
    < _union-set-list >
    */

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
    /*
    struct-or-union-specifier:
    struct-or-union identifieropt { struct-declaration-list }
    struct-or-union identifier
    */

    /*
    struct-or-union-specifier:
    struct-or-union )opt identifieropt { struct-declaration-list }
    struct-or-union )opt identifier
    */

    //aqui teria que ativar o flag
    Struct_Or_Union(ctx, pStructUnionSpecifier);//TODO


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
        //ANNOTATED AQUI TEM O COMENTARIO /*Box | Circle*/ antes nome da struct
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
        //ANNOTATED AQUI TEM O COMENTARIO /*Box | Circle*/ antes do {
        Parser_Match(ctx, &pStructUnionSpecifier->ClueList2);

        Struct_Declaration_List(ctx,
            &pStructUnionSpecifier->StructDeclarationList);

        Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
            &pStructUnionSpecifier->ClueList3);
    }
    else
    {
        //struct X *
        // SetError2(ctx, "expected name or {", "");
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
    /*
    enumerator:
    enumeration-constant
    enumeration-constant = constant-expression
    */
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

    /*
    enumerator-list:
    enumerator
    enumerator-list , enumerator
    */

    TEnumerator * pEnumerator2 = TEnumerator_Create();
    List_Add(pEnumeratorList2, pEnumerator2);

    EnumeratorC(ctx, pEnumerator2);
    SymbolMap_SetAt(ctx->pCurrentScope, pEnumerator2->Name, (TTypePointer *)pEnumerator2);

    Tokens token = Parser_CurrentToken(ctx);

    //tem mais?
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
    /*
    enum-specifier:
    enum identifieropt { enumerator-list }
    enum identifieropt { enumerator-list, }
    enum identifier
    */

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
        //Ja fez Match do identifier
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
            //enum identifier
            //                  ^
        }
    }
    else if (token == TK_LEFT_CURLY_BRACKET)
    {
        //ja foi feito o Match do {
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
    /*
    function-specifier:
    inline
    _Noreturn
    */
    bool bResult = false;

    switch (token)
    {
    case TK_INLINE:
    case TK__INLINE://microsoft
    case TK__FORCEINLINE://microsoft
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
    /*
    function-specifier:
    inline
    _Noreturn
    */

    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK__INLINE://microsoft
    case TK__FORCEINLINE://microsoft
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
    /*
    storage-class-specifier:
    typedef
    extern
    static
    _Thread_local
    auto
    register
    */
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
    /*
    storage-class-specifier:
    typedef
    extern
    static
    _Thread_local
    auto
    register
    */

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
    /*
    parameter-list:
    parameter-declaration
    parameter-list, parameter-declaration
    */
    Tokens token = Parser_CurrentToken(ctx);

    TParameter * pParameter = TParameter_Create();
    List_Add(pParameterList, pParameter);
    Parameter_Declaration(ctx, pParameter);

    //Tem mais?
    token = Parser_CurrentToken(ctx);
    if (token == TK_COMMA)
    {
        //a virgula fica no anterior
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

    //ctx->pCurrentParameterScope

    /*
    parameter-declaration:
    declaration-specifiers declarator
    declaration-specifiers abstract-declaratoropt
    */
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
    /*
    parameter-type-list:
    parameter-list
    parameter-list , ...
    */

    Parameter_List(ctx, &pParameterList->ParameterList);

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_DOTDOTDOT)
    {
        pParameterList->bVariadicArgs = true;
        //TODO ADD this parameter
        Parser_Match(ctx, &pParameterList->ClueList1);
    }
}


void Direct_Declarator(Parser * ctx, bool bAbstract, TDirectDeclarator ** ppDeclarator2)
{
    *ppDeclarator2 = NULL; //out

                           /*
                           direct-declarator:
                           identifier
                           ( declarator )
                           direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
                           direct-declarator [ static type-qualifier-listopt assignment-expression ]
                           direct-declarator [ type-qualifier-list static assignment-expression ]
                           direct-declarator [ type-qualifier-listopt * ]
                           direct-declarator ( parameter-type-list )
                           direct-declarator ( identifier-listopt )
                           */
    TDirectDeclarator * pDirectDeclarator = NULL;

    if (ErrorOrEof(ctx))
        return;


    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
        //assert(pDirectDeclarator == NULL);
        pDirectDeclarator = TDirectDeclarator_Create();

        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList0);

        Declarator(ctx, bAbstract, &pDirectDeclarator->pDeclarator);
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList1);

        //Para indicar que eh uma ( declarator )
        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeDeclarator;
        // ) para nao confundir com funcao (
    }
    break;

    case TK_IDENTIFIER:
    {
        //identifier
        pDirectDeclarator = TDirectDeclarator_Create();

        //Para indicar que eh uma identificador

        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeIdentifier;

        const char * lexeme = Lexeme(ctx);
        PTR_STRING_REPLACE(pDirectDeclarator->Identifier, lexeme);
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);
        Parser_Match(ctx, &pDirectDeclarator->ClueList0);
    }
    break;

    default:
        ////assert(false);
        break;
    }



    if (pDirectDeclarator == NULL)
    {
        //Por enquanto esta funcao esta sendo usada para
        //abstract declarator que nao tem nome.
        //vou criar aqui por enquanto um cara vazio
        pDirectDeclarator = TDirectDeclarator_Create();
        PTR_STRING_REPLACE(pDirectDeclarator->Identifier, "");
        pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
        pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);

        //Para indicar que eh uma identificador

        pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeIdentifier;

        //Quando tiver abstract declarator vai ser 
        //bug cair aqui
    }

    *ppDeclarator2 = pDirectDeclarator;

    for (;;)
    {
        //assert(pDirectDeclarator != NULL);

        token = Parser_CurrentToken(ctx);
        switch (token)
        {
        case TK_LEFT_PARENTHESIS:

            /*
            direct-declarator ( parameter-type-list )
            direct-declarator ( identifier-listopt )
            */
            //      pDirectDeclarator->token = token;
            //      //assert(pDirectDeclarator->pParametersOpt == NULL);
            //      pDirectDeclarator->pParametersOpt = TParameterList_Create();
            token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pDirectDeclarator->ClueList2);

            //Para indicar que eh uma funcao

            pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeFunction;

            if (token != TK_RIGHT_PARENTHESIS)
            {
                //opt
                Parameter_Type_List(ctx, &pDirectDeclarator->Parameters);
            }
            Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pDirectDeclarator->ClueList3);
            break;

        case TK_LEFT_SQUARE_BRACKET:
            /*
            direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
            direct-declarator [ static type-qualifier-listopt assignment-expression ]
            direct-declarator [ type-qualifier-list static assignment-expression ]
            direct-declarator [ type-qualifier-listopt * ]
            */

            ////assert(pDirectDeclarator->pParametersOpt == NULL);
            //pDirectDeclarator->pParametersOpt = TParameterList_Create();

            //Para indicar que eh um array

            pDirectDeclarator->DeclaratorType = TDirectDeclaratorTypeArray;

            token = Parser_MatchToken(ctx, TK_LEFT_SQUARE_BRACKET, &pDirectDeclarator->ClueList2);
            if (token == TK_STATIC)
            {
            }
            else
            {
                if (token != TK_RIGHT_SQUARE_BRACKET)
                {
                    //assert(pDirectDeclarator->pExpression == NULL);
                    AssignmentExpression(ctx, &pDirectDeclarator->pExpression);
                }
                else
                {
                    //array vazio é permitido se for o ultimo cara da struct          
                    //struct X { int ElementCount;  int Elements[]; };           
                }
            }

            Parser_MatchToken(ctx, TK_RIGHT_SQUARE_BRACKET, &pDirectDeclarator->ClueList3);

            break;
        default:
            //assert(false);
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
        //tem mais
        TDirectDeclarator * pDirectDeclaratorNext = NULL;
        Direct_Declarator(ctx, bAbstract, &pDirectDeclaratorNext);
        pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
    }
    else if (!bAbstract && token == TK_IDENTIFIER)
    {
        //tem mais
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
        //type-qualifier-extensions 
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
    //token = Parser_Match(ctx, );

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
    /*
    type-qualifier:
    const
    restrict
    volatile
    _Atomic
    */

    //extensions
    /*
    auto
    _size(identifier)
    _size(int)
    */

    bool bResult = false;
    Tokens token = Parser_CurrentToken(ctx);

    //const char* lexeme = Lexeme(ctx);
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
    /*
    type-qualifier-list:
    type-qualifier
    type-qualifier-list type-qualifier
    */

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
    /*
    pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
    */

    TPointer * pPointer = TPointer_Create();

    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_ASTERISK)
    {
        //ANNOTATED AQUI VAI TER AUTO SIZEOF
        TPointerList_PushBack(pPointerList, pPointer);
        Parser_Match(ctx, &pPointer->ClueList0);
    }
    else
    {
        //Erro
        SetError(ctx, "pointer error");
    }

    token = Parser_CurrentToken(ctx);


    //Opcional
    if (IsTypeQualifierToken(token))
    {
        Type_Qualifier_List(ctx, &pPointer->Qualifier);
    }

    token = Parser_CurrentToken(ctx);

    //Tem mais?
    if (token == TK_ASTERISK)
    {
        Pointer(ctx, pPointerList);
    }
}

//pag 123 C
void Declarator(Parser * ctx, bool bAbstract, TDeclarator ** ppTDeclarator2)
{
    //assert(*ppTDeclarator2 == NULL);
    *ppTDeclarator2 = NULL; //out

    TDeclarator * pDeclarator = TDeclarator_Create();
    /*
    declarator:
    pointeropt direct-declarator
    */
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK_ASTERISK)
    {
        Pointer(ctx, &pDeclarator->PointerList);
    }

    //assert(pDeclarator->pDirectDeclarator == NULL);
    Direct_Declarator(ctx, bAbstract, &pDeclarator->pDirectDeclarator);

    *ppTDeclarator2 = pDeclarator;
}


bool TAlignmentSpecifier_IsFirst(Tokens token)
{
    /*
    alignment - specifier:
    _Alignas(type - name)
    _Alignas(constant - expression)
    */
    return (token == TK__ALIGNAS);
}

bool Alignment_Specifier(Parser * ctx,
    TAlignmentSpecifier * pAlignmentSpecifier)
{
    bool bResult = false;
    /*
    alignment - specifier:
    _Alignas(type - name)
    _Alignas(constant - expression)
    */
    Tokens token = Parser_CurrentToken(ctx);

    if (token == TK__ALIGNAS)
    {
        Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);
        //assert(false);//TODO
        Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);
        bResult = true;
    }

    return bResult;
}


bool TTypeSpecifier_IsFirst(Parser * ctx, Tokens token, const char * lexeme)
{
    /*
    type-specifier:
    void
    char
    short
    int
    long
    float
    double
    signed
    unsigned
    _Bool
    _Complex
    atomic-type-specifier
    struct-or-union-specifier
    enum-specifier
    typedef-name
    */

    bool bResult = false;

    switch (token)
    {
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        //microsoft
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        /////
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
    //assert(false); //tODO criar TAtomicTypeSpecifier
                   /*
                   atomic-type-specifier:
                   _Atomic ( type-name )
                   */
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
    /*
    type-specifier:
    void
    char
    short
    int
    long
    float
    double
    signed
    unsigned
    _Bool
    _Complex
    atomic-type-specifier
    struct-or-union-specifier
    enum-specifier
    typedef-name
    */


    bool bResult = false;

    const char * lexeme = Lexeme(ctx);
    Tokens token = Parser_CurrentToken(ctx);

    switch (token)
    {
        //type - specifier
    case TK_VOID:
    case TK_CHAR:
    case TK_SHORT:
    case TK_INT:
    case TK_LONG:
        //microsoft
    case TK__INT8:
    case TK__INT16:
    case TK__INT32:
    case TK__INT64:
    case TK__WCHAR_T:
        /////////
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

    //atomic-type-specifier
    case TK__ATOMIC:
        bResult = true;
        AtomicTypeSpecifier(ctx, ppTypeSpecifier);
        break;

    case TK_STRUCT:
    case TK_UNION:
    {
        //assert(*ppTypeSpecifier == NULL);
        bResult = true;
        TStructUnionSpecifier * pStructUnionSpecifier = TStructUnionSpecifier_Create();

        *ppTypeSpecifier = (TTypeSpecifier *)pStructUnionSpecifier;
        Struct_Or_Union_Specifier(ctx, pStructUnionSpecifier);
    }
    break;

    case TK_ENUM:
    {
        //assert(*ppTypeSpecifier == NULL);
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

            if (bIsTypedef == 2 /*struct*/)
                pSingleTypeSpecifier->Token2 = TK_STRUCT;
            else if (bIsTypedef == 3 /*union*/)
                pSingleTypeSpecifier->Token2 = TK_UNION;
            else if (bIsTypedef == 4 /*enum*/)
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
            //assert(false); //temque chegar aqui limpo ja
            SetError(ctx, "internal error 2");
        }
    }
    break;

    default:
        break;
    }

    //token = Parser_CurrentToken(ctx);
    //if (token == TK_VERTICAL_LINE)
    //{
    //criar uma lista
    //}
}

bool Declaration_Specifiers_IsFirst(Parser * ctx, Tokens token, const char * lexeme)
{
    /*
    declaration-specifiers:
    storage-class-specifier declaration-specifiersopt
    type-specifier          declaration-specifiersopt
    type-qualifier          declaration-specifiersopt
    function-specifier      declaration-specifiersopt
    alignment-specifier     declaration-specifiersopt
    */
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
    /*
    declaration-specifiers:
    storage-class-specifier declaration-specifiersopt
    type-specifier          declaration-specifiersopt
    type-qualifier          declaration-specifiersopt
    function-specifier      declaration-specifiersopt
    alignment-specifier     declaration-specifiersopt
    */
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
            //ATENCAO
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
        //ATENCAO
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
        //assert(false);
        //TAlignmentSpecifier* pAlignmentSpecifier = TAlignmentSpecifier_Create();
        //List_Add(pDeclarationSpecifiers, TAlignmentSpecifier_As_TDeclarationSpecifier(pAlignmentSpecifier));
    }
    else
    {
        SetError(ctx, "internal error 3");
    }

    token = Parser_CurrentToken(ctx);
    lexeme = Lexeme(ctx);

    //Tem mais?
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
    //assert(*ppInitializer == NULL);
    /*
    initializer:
    assignment-expression
    { initializer-list }
    { initializer-list , }
    */

    /*
    initializer:
    default
    assignment-expression
    _defaultopt { initializer-list }
    _defaultopt { initializer-list , }
    */

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
            //ANNOTATED AQUI DIZ DEFAULT 

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
    /*
    initializer-list:
    designationopt initializer
    initializer-list , designationopt initializer
    */
    for (; ;)
    {
        if (ErrorOrEof(ctx))
            break;

        Tokens token = Parser_CurrentToken(ctx);
        if (token == TK_RIGHT_CURLY_BRACKET)
        {
            //Empty initializer
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
        //push
        token = Parser_CurrentToken(ctx);

        if (token == TK_COMMA)
        {
            //TNodeClueList_MoveToEnd(&pTInitializerListItem->ClueList, &ctx->Scanner.ClueList);
            Parser_Match(ctx, &pTInitializerListItem->ClueList);
            //tem mais
        }

        else
        {
            break;
        }
    }
}

void Designation(Parser * ctx, TDesignatorList * pDesignatorList)
{
    /*
    designation:
    designator-list =
    */
    Designator_List(ctx, pDesignatorList);
    Parser_MatchToken(ctx, TK_EQUALS_SIGN, NULL);//tODO
}

void Designator_List(Parser * ctx, TDesignatorList * pDesignatorList)
{
    // http://www.drdobbs.com/the-new-c-declarations-initializations/184401377
    /*
    designator-list:
    designator
    designator-list designator
    */
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
    /*
    designator:
    [ constant-expression ]
    . identifier
    */
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
        //TNodeClueList_MoveToEnd(&p->ClueList, &ctx->Scanner.ClueList);
        Parser_Match(ctx, &p->ClueList0);

        PTR_STRING_REPLACE(p->Name, Lexeme(ctx));
        Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
    }
}

void Init_Declarator(Parser * ctx,
    TInitDeclarator * *ppDeclarator2)
{
    /*
    init-declarator:
    declarator
    declarator = initializer
    */
    TInitDeclarator * pInitDeclarator =
        TInitDeclarator_Create();

    Declarator(ctx, false, &pInitDeclarator->pDeclarator);
    Tokens token = Parser_CurrentToken(ctx);

    const char * declaratorName = TInitDeclarator_FindName(pInitDeclarator);
    if (declaratorName)
    {
        //Fica em um contexto que vive so durante a declaracao
        //depois eh substituido

        SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer *)pInitDeclarator);
    }

    //Antes do =
    *ppDeclarator2 = pInitDeclarator;

    if (token == TK_EQUALS_SIGN)
    {
        //assert(*ppDeclarator2 != NULL);

        Parser_Match(ctx, &pInitDeclarator->ClueList0);

        Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
        ////TNodeClueList_MoveToEnd(&pInitDeclarator->ClueList, &ctx->Scanner.ClueList);
    }
}

void Init_Declarator_List(Parser * ctx,
    TInitDeclaratorList * pInitDeclaratorList)
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */

    TInitDeclarator * pInitDeclarator = NULL;
    Init_Declarator(ctx, &pInitDeclarator);
    List_Add(pInitDeclaratorList, pInitDeclarator);

    //Tem mais?
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
    /*
    CPRIME
    group-declaration:
    default identifier { declarations opt }
    */

    TGroupDeclaration * p = TGroupDeclaration_Create();
    *ppGroupDeclaration = p;

    Parser_Match(ctx, &p->ClueList0);//default


    PTR_STRING_REPLACE(p->Identifier, Lexeme(ctx));
    Parser_MatchToken(ctx, TK_IDENTIFIER, &p->ClueList1);//identifier

    Parser_MatchToken(ctx, TK_LEFT_CURLY_BRACKET, &p->ClueList2);

    Tokens token = Parser_CurrentToken(ctx);
    if (token != TK_RIGHT_CURLY_BRACKET)
    {
        Parse_Declarations(ctx, &p->Declarations);
    }
    else
    {
        //vazio
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
    /*
    declaration:
    declaration-specifiers;
    declaration-specifiers init-declarator-list ;
    static_assert-declaration
    */



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
        *ppDeclaration = (TAnyDeclaration *)p;//moved
        bHasDeclaration = true;
    }
    else
    {
        TDeclaration * pFuncVarDeclaration = TDeclaration_Create();

        if (token == TK_SEMICOLON)
        {
            //declaracao vazia como ;
            bHasDeclaration = true;
            //Match(ctx);
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
            ////assert(pFuncVarDeclaration->FileIndex >= 0);

            token = Parser_CurrentToken(ctx);

            if (token == TK_SEMICOLON)
            {
                Parser_Match(ctx, &pFuncVarDeclaration->ClueList1);
            }

            else
            {
                //Pega os parametros das funcoes mas nao usa
                //se nao for uma definicao de funcao


                //////////////////////
                /////vou criar um escopo para declarators
                // int* p = malloc(sizeof p);
                //                        ^
                //                       p esta no contexto
                // mas nao tem toda declaracao

                struct SymbolMap BlockScope = SYMBOLMAP_INIT;

                BlockScope.pPrevious = ctx->pCurrentScope;
                ctx->pCurrentScope = &BlockScope;


                //Agora vem os declaradores que possuem os ponteiros
                Init_Declarator_List(ctx, &pFuncVarDeclaration->InitDeclaratorList);


                ctx->pCurrentScope = BlockScope.pPrevious;
                SymbolMap_Destroy(&BlockScope);

                ////////////////////////

                token = Parser_CurrentToken(ctx);

                //colocar os declaradores nos simbolos
                //agora ele monta a tabela com a declaracao toda
                ForEachListItem(TInitDeclarator, pInitDeclarator, &pFuncVarDeclaration->InitDeclaratorList)
                {
                    const char * declaratorName = TInitDeclarator_FindName(pInitDeclarator);



                    if (declaratorName != NULL)
                    {
                        SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer *)pFuncVarDeclaration);
                    }

                    //ctx->
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

                    //auto tag
                    if (funcName && IsSuffix(funcName, "init"))
                    {
                        //tem que ter 1 argumento
                        functionTag = "init";
                    }
                    else if (funcName && IsSuffix(funcName, "destroy"))
                    {
                        //tem que ter 1 argumento
                        functionTag = "destroy";
                    }
                    else if (funcName && IsSuffix(funcName, "delete"))
                    {
                        //tem que ter 1 argumento
                        functionTag = "delete";
                    }
                    else if (funcName && IsSuffix(funcName, "create"))
                    {
                        //tem que ter 0 argumentos
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

                //
                if (token == TK_DEFAULT)
                {
                    /*
                    6.9.1) function-definition:
                    declaration-specifiers declarator declaration-listopt defaultopt compound-statement
                    */

                    pFuncVarDeclaration->bDefault = true;
                    Parser_Match(ctx, &pFuncVarDeclaration->ClueList0);
                    token = Parser_CurrentToken(ctx);
                }

                if (token == TK_LEFT_CURLY_BRACKET)
                {

                    //ANNOTATED AQUI TEM O COMENTARIO /*@default*/ antes do {

                    //Ativa o escopo dos parametros
                    //Adiconar os parametros em um escopo um pouco a cima.
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
                            //parametro sem nome
                        }
                    }

                    BlockScope2.pPrevious = ctx->pCurrentScope;
                    ctx->pCurrentScope = &BlockScope2;


                    //SymbolMap_Print(ctx->pCurrentScope);
                    /*
                    6.9.1) function-definition:
                    declaration-specifiers declarator declaration-listopt compound-statement
                    */
                    TStatement * pStatement;
                    Compound_Statement(ctx, &pStatement);
                    //TODO cast

                    ctx->pCurrentScope = BlockScope2.pPrevious;
                    SymbolMap_Destroy(&BlockScope2);


                    pFuncVarDeclaration->pCompoundStatementOpt = (TCompoundStatement *)pStatement;
                }

                else
                {

                    //ANNOTATED AQUI TEM O COMENTARIO /*@default*/ antes do ;
                    Parser_MatchToken(ctx, TK_SEMICOLON, &pFuncVarDeclaration->ClueList1);
                }


            }

            // StrBuilder_Swap(&pFuncVarDeclaration->PreprocessorAndCommentsString,
            // &ctx->Scanner.PreprocessorAndCommentsString);


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


            //TDeclarations_Destroy(&ctx->Templates);
            //TDeclarations_Init(&ctx->Templates);

            //printf("%s", ctx->Scanner.PreprocessorAndCommentsString);
            // StrBuilder_Clear(&ctx->Scanner.PreprocessorAndCommentsString);

            //Cada Declaration poderia ter out uma lista TDeclarations
            //publica que vai ser inserida aqui.
            //
            TDeclarations_PushBack(declarations, pDeclarationOut);


            declarationIndex++;
        }
        else
        {
            if (Parser_CurrentToken(ctx) == TK_EOF)
            {
                //ok
                Parser_Match(ctx, NULL);
            }
            else
            {
                //nao ter mais declaracao nao eh erro
                //SetError(ctx, "declaration expected");
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
        //ok
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
                    node->data = NULL; //movido para array
                }
            }
        }
    }
}

bool GetAST(const char * filename,
    const char * configFileName /*optional*/,
    struct Options * options,
    TProgram * pProgram)
{
    bool bResult = false;

    Parser parser;


    if (configFileName != NULL)
    {
        //opcional   
        String * /*@auto*/ fullConfigFilePath = NULL;
        GetFullPath(configFileName, &fullConfigFilePath);

        Parser_InitFile(&parser, fullConfigFilePath);
        Parser_Main(&parser, &pProgram->Declarations);

        //apaga declaracoes eof por ex
        TDeclarations_Destroy(&pProgram->Declarations);
        TDeclarations_Init(&pProgram->Declarations);

        //Some com o arquivo de configclea
        TScannerItemList_Clear(&parser.ClueList);
        BasicScannerStack_Pop(&parser.Scanner.stack);
        //Some com o arquivo de config
        Free(fullConfigFilePath);
    }

    String * /*@auto*/ fullFileNamePath = NULL;
    GetFullPath(filename, &fullFileNamePath);

    parser.Scanner.pOptions = options; //TODO

    //Copy parser options
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


    //all sources...
    if (options->bAmalgamate)
    {
        struct FileNodeMap map = { 0 };

        //Inserts the initial file
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
                    //processar

                    //inserar na lista ja processados          
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
                    FileNode_Free(pCurrent); //nao pode deletar os proximos
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
    //else
      //assert(false);
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
        //nao eh p include
    }
}

static void TNodeClueList_CodePrint(PrintCodeOptions * options, TScannerItemList * list,
    StrBuilder * fp)
{
    if (options->Options.bCannonical)
    {
        // no modo cannonical quem coloca os espacos
        //eh a funcao especializada
        //para que o tipo seja somente ele 
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
            //options->IncludeLevel--;
            ////assert(IncludeLevel > 0);
            //bInclude = true;
            if (options->Options.bAmalgamate)
            {
                Output_Append(fp, options, "\n");
            }

            break;
        case TK_PRE_DEFINE:
            //TODO gerar macros como init
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            break;

        case TK_PRE_PRAGMA:
            if (options->Options.bAmalgamate)
            {
                //pragma once nao eh p incluir
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
            //Output_Append(fp, options, pNodeClue->lexeme.c_str);
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
                Output_Append(fp, options, "\n");
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

            //case NodeClueTypeNone:      
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
            //assert(false);
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
        //assert(false);
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
        //assert(false);
        break;
    }


}

static void TBlockItem_CodePrint(TProgram * program, PrintCodeOptions * options, TBlockItem * p, StrBuilder * fp)
{
    if (p == NULL)
    {
        //assert(false);
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
        //Output_Append(fp, options,  "\n");
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
        //assert(false);
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

    //Output_Append(fp, options, "l1");
    StrBuilder_AppendFmt(fp, "_lambda_%d", global_lambda_counter);

    StrBuilder sb = STRBUILDER_INIT;

    if (p->pParameterTypeListOpt)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList2, &sb);


        Output_Append(&sb, options, "\n");
        StrBuilder_AppendFmt(&sb, "static void _lambda_%d(", global_lambda_counter);
        //Output_Append(&sb, options, "static void func_l1(");

        TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, &sb);

        //TNodeClueList_CodePrint(options, &p->ClueList3, &sb);
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

            //pSpecifierQualifierList = &p->pTypeName->SpecifierQualifierList;
            bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

            //falta imprimeir typename
            //TTypeName_Print*
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
        //Do lado esquerdo vem o nome da funcao p->pExpressionLeft
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
        //assert(false);
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
        ////assert(false);
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
        ///true;

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

        //assert(false);
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
        //vou criar uma expressionp enum?
    }

    if (pTEnumerator->bHasComma)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList2, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEnumSpecifier_CodePrint(TProgram * program, PrintCodeOptions * options, TEnumSpecifier * p, StrBuilder * fp)
{
    //true;

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

    //true;

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

        //TNodeClueList_CodePrint(options, &p->ClueList1, fp);

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

    //true;

    /*if (p->Token2 == TK_STRUCT)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "struct ");
      }
      Output_Append(fp, options, p->TypedefName);
    }
    else if (p->Token2 == TK_UNION)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "union ");
      }
      Output_Append(fp, options, p->TypedefName);

    }
    else if (p->Token2 == TK_ENUM)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "enum ");
      }
      Output_Append(fp, options, p->TypedefName);

    }
    else
    */
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
    //    if (b)
    //      Output_Append(fp, options,  ",");


    //
    if (p->Name)
    {
        //.identifier
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ".");
        Output_Append(fp, options, p->Name);
        Output_Append(fp, options, "=");
        TExpression_CodePrint(program, options, p->pExpression, "index", fp);
    }
    else
    {
        //[constant-expression]
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
    TDeclarationSpecifiers * pDeclarationSpecifiers, //<- usadao para construir {}
    TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
    TInitializerList * p,

    StrBuilder * fp)
{
    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL/* &&
                  pSpecifierQualifierList != NULL*/)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            //Output_Append(fp, options, COMMENT_KEYWORD_DEFAULT);
        }
        //a partir de {} e um tipo consegue gerar o final  
        StrBuilder sb = STRBUILDER_INIT;
        bool bHasInitializers = false;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList *)(pDeclarationSpecifiers),
            pDeclatator,                        //<-dupla para entender o tipo
            NULL,
            NULL,/*args*/
            "",
            NULL /*not used*/,
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

    /*
    default { ... }
    {}
    */
    if (p->bDefault || p->InitializerList.pHead == NULL)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        TInitializer * pInitializer = NULL;
        //p->InitializerList.pHead ?
        //p->InitializerList.pHead->pInitializer : NULL;


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
                pDeclarator,                        //<-dupla para entender o tipo
                pInitializer,
                NULL,/*args*/
                "",
                NULL /*not used*/,
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
        //if (!List_IsFirstItem(p, pItem))
        //{
        //  TNodeClueList_CodePrint(options, &pItem->ClueList, fp);
        //            Output_Append(fp, options,  ",");
        //}
        //TParameterDeclaration * pItem = p->pItems[i];
        TParameter_CodePrint(program, options, pItem, fp);
    }



}

static void TParameterTypeList_CodePrint(TProgram * program, PrintCodeOptions * options, TParameterTypeList * p, StrBuilder * fp)
{
    //Output_Append(fp, options,  "(");
    TParameterList_CodePrint(program, options, &p->ParameterList, fp);

    if (p->bVariadicArgs)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        //Output_Append(fp, options,  ",");

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "...");
    }
    //Output_Append(fp, options,  ")");

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
    //fprintf(fp, "{");


    if (pDirectDeclarator->Identifier)
    {
        //identifier
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        if (bPrintName)
        {
            Output_Append(fp, options, pDirectDeclarator->Identifier);
        }
        //true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        Output_Append(fp, options, "(");

        TDeclarator_CodePrint(program, options, pDirectDeclarator->pDeclarator, bPrintName, fp);

        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList1, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeArray)
    {
        /*
        direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
        direct-declarator [ static type-qualifier-listopt assignment-expression ]
        direct-declarator [ type-qualifier-list static assignment-expression ]
        */
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
        //( parameter-type-list )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, options, "(");
        TParameterTypeList_CodePrint(program, options, &pDirectDeclarator->Parameters, fp);
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        //fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_CodePrint(program, options, pDirectDeclarator->pDirectDeclarator, bPrintName, fp);
    }


    //fprintf(fp, "}");

}

static void TDeclarator_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarator * p, bool bPrintName, StrBuilder * fp)
{
    TPointerList_CodePrint(program, options, &p->PointerList, fp);
    TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}

//void TInitDeclarator_CodePrint(TProgram* program, 
//PrintCodeOptions * options, 
//TI/nitDeclarator* p,    
//StrBuilder* fp);



void TStructDeclarator_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,
    TStructDeclarator * p,
    StrBuilder * fp)
{

    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);
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
        //assert(false);
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
    //TODO nao pode colocr isso se veio de comentario

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
        //TODO espacos
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
        //tODO ja esta nos comentarios
        //Output_Append(fp, options, "(");
        //Output_Append(fp, options, p->SizeIdentifier);
        //Output_Append(fp, options, ")");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            //Output_Append(fp, options, "@*/");
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
            //gerar espaco entre eles para nao grudar no modo cannonico
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
            //CASE(TAlignmentSpecifier) : 
            ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
            //break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier *)pItem, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier *)pItem, fp);
            break;

        default:
            //assert(false);
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

            //CASE(TAlignmentSpecifier) : 
            ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
            //break;

        default:
            //assert(false);
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
    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);

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

    //fprintf(fp, "[");
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

    //  fprintf(fp, "]");

}



TStructUnionSpecifier * GetStructSpecifier(TProgram * program, TDeclarationSpecifiers * specifiers);


static bool FindListStructPattern(TProgram * program,
    TParameter * pParameter,
    bool * pbItemIsPointer,
    bool * pbItemIsAutoPointer,
    StrBuilder * itemTypeName,
    StrBuilder * arrayName)
{
    //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
    //ter size, capacity e um vector de items

    bool bHasHead = false;
    bool bHasTail = false;

    //O primeiro parametro tem que ser struct or typedef para struct
    TStructUnionSpecifier * pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
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
    //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
    //ter size, capacity e um vector de items
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    //O primeiro parametro tem que ser struct or typedef para struct
    TStructUnionSpecifier * pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
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

                        //se eh um array de ponteiros 
                        bool bItemIsPointer =
                            TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsPointer = bIsPointer2;

                        //se eh um array de ponteiros  donos
                        bool bItemIsAutoPointer =
                            TPointerList_IsAutoPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsAutoPointer = bItemIsPointer;

                        //este eh array
                        //vamos ver o tipo do item e se ele eh auto
                        //pStructDeclaration->SpecifierQualifierList
                        // StrBuilder itemTypeStr = STRBUILDER_INIT;
                        TTypeName * pTypeName = NULL;
                        PrintCodeOptions  options = CODE_PRINT_OPTIONS_INIT;
                        options.Options.bCannonical = true;
                        TSpecifierQualifierList_CodePrint(program, &options, &pStructDeclaration->SpecifierQualifierList, itemTypeName);
                        //StrBuilder_Destroy(&itemTypeStr);
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

    //Move tudo para o lado de acordo com a identacao
    for (int i = 0; i < identationLevel * 4; i++)
    {
        StrBuilder_AppendChar(p, ' ');
    }

    //agora nove de acordo com os espacos
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
                    (*pch >= '_')) //$X_X
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
            //Este \b eh usado para juntar identificador
            //$part1_part2
            //$part1\b_part2
            //

            if (*pch == '\n')
            {
                StrBuilder_AppendChar(p, *pch);
                pch++;


                if (*pch != '\0') //se for o ultimo nao move
                {//Move tudo para o lado de acordo com a identacao
                    for (int i = 0; i < identationLevel * 4; i++)
                    {
                        StrBuilder_AppendChar(p, ' ');
                    }

                    //agora nove de acordo com os espacos
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
    ////////////
    TDeclaration * pFinalDecl =
        TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
        pStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
    }
    //////////////

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

                //o primeiro item tem que ser o ID
                if (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    //if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
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
    ////////////
    TDeclaration * pFinalDecl =
        TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
        pStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
    }
    //////////////

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

                //o primeiro item tem que ser o ID
                if (pStructDeclarator)
                {
                    const char * structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    //if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        PrintCodeOptions options2 = CODE_PRINT_OPTIONS_INIT;
                        TInitializer_CodePrint(program, &options2, pStructDeclarator->pDeclarator,
                            (TDeclarationSpecifiers *)& pStructDeclaration->SpecifierQualifierList,
                            pStructDeclarator->pInitializer, idname);

                        //StrBuilder_Set(idname, structDeclaratorName);
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
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->TagName)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->TagName);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
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
    TParameterTypeList * pArgsOpt, //parametros
    const char * parameterName,
    const char * functionSuffix,
    StrBuilder * fp);
static const char * GetNullStr(TProgram * program);



static void DefaultFunctionDefinition_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TDeclaration * p,
    StrBuilder * fp)
{

    //Retorno da funcao
    TDeclarationSpecifiers * pSpecifiers =
        &p->Specifiers;

    const char * funcName =
        TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

    StrBuilder functionPrefix = STRBUILDER_INIT;
    StrBuilder functionSuffix = STRBUILDER_INIT;

    GetPrefixSuffix(funcName, &functionPrefix, &functionSuffix);

    //parametros


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
            NULL /*not used*/,
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
            pArgs,/*args fazer inicializacao conforme parametro*/
            TParameter_GetName(pFirstParameter),
            NULL /*not used*/,
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
            NULL,/*args*/
            TParameter_GetName(pFirstParameter),
            NULL /*not used*/,
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
            NULL,/*args*/
            TParameter_GetName(pFirstParameter),
            NULL /*not used*/,
            ActionDelete,
            SearchDestroy,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else
    {
        //Agora entre no auto tag.
        const char * functionTag =
            TDeclaration_FindFunctionTagName(p, &program->GlobalScope);

        if (functionTag == NULL && !options->Options.bNoImplicitTag)
        {
            //implicity function tag

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

            //Implemetancao para vector
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
                    1 /*options->IdentationLevel*/);
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

            //Implemetancao para vector
            if (FindVectorStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                //TODO procurar pelas funcoes com tag
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
                    1/*options->IdentationLevel*/);
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
                //o item apontado tem que ter pNext verificar isso
                //e colocar erro se nao tiver
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
                    1/*options->IdentationLevel*/);
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
        /*
        typedef struct Array { int data; ... } Items;
        void Items_Add(Items* p,int i) {...}
        void Items_Delete(Items* p,int i) {...}
        */

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
                //normal
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

    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);


}

static void TParameter_CodePrint(TProgram * program,
    PrintCodeOptions * options,
    TParameter * p,

    StrBuilder * fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);

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

    //for (int i = 0; i < p->Declarations.Size; i++)
    //{
      //TAnyDeclaration_CodePrint(program, options, p->Declarations.pItems[i], fp);
    //}
    //TNodeClueList_CodePrint(options, &p->ClueList1, fp);
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
        //assert(false);
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

    //for (int i = 0; i < pProgram->Files2.size; i++)
    //{
    //  TFile *pFile = pProgram->Files2.pItems[i];
    //  printf("\"%s\"\n", pFile->FullPath);
    //}

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
    const char * pInitExpressionText, //(x->p->i = 0)    
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
    TSpecifierQualifierList * pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
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
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TDeclaration_ID)
            {
                if (strcmp(pKeyValue->Key, functionTagName) == 0)
                {
                    //agora tem que verificar o tipo.
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
                                //pode ser que pDeclarationSpecifiersOfArg1 seja typedef para pSpecifierQualifierList
                                //ou vice versa
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
                                //nao eh igual 
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
    TSpecifierQualifierList * pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
    TParameterTypeList * pArgsOpt, //parametros do create /init
    TInitializer * pInitializerOpt,
    const char * pInitExpressionText, //(x->p->i = 0)    
    const char * pszAutoPointerLenExpressionOpt,
    const Action action,
    Search search,
    const char * nameToFind,
    StrBuilder * fp)
{
    if (nameToFind == NULL)
    {
        //pode ser null struct sem nome
        return false;
    }




    bool bComplete = false;

    //TPointerList_Printf(&pDeclatator->PointerList);

    //TODO FAZER FLAGS e OLHAR P TIPO E DECLARATOR AMBOS
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
                //nao procurar delete bIsAutoPointerSizeToObject
                //nao eh ponteiro
                if (search == SearchAll ||
                    search == SearchDelete)
                {
                    //vamos procurar pela funcao conceito _Delete
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
                                //1 auto pointer para 1 autopointer
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
                            //se nao achou delete procura a destroy 
                            //e depois chama free
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
                                        //1 auto pointer para 1 auto pointer

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

                                        // StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        //   "free((void*)%s[i]);",
                                        // pInitExpressionText);

                                        options->IdentationLevel--;
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s((void*)%s);",
                                            GetFreeStr(program),
                                            pInitExpressionText);
                                    }
                                    else
                                    {
                                        //1 auto pointer para 1 auto pointer

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                            "%s(%s[0]);",
                                            funcName,
                                            pInitExpressionText);

                                        // StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        //   "free((void*)%s[0]);",
                                        //   pInitExpressionText);

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

                //nada
                bComplete = true;
            }
            else
            {
                if (action != ActionDestroyContent)
                {
                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = NULL;", pInitExpressionText);
                    bComplete = true;
                }
            }

        }
        else
        {
            //nao eh ponteiro
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

                    //vamos procurar pela funcao conceito _Destroy
                    //TDeclaration* pDeclarationDestroy =
                      //  SymbolMap_FindObjFunction(&program->GlobalScope,
                        //    nameToFind,
                          //  "Destroy");
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

                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                          //  "%s_Destroy(&%s);",
                            //nameToFind,
                            //pInitExpressionText);
                        bComplete = true;
                    }
                }
            }

        }
    }
    else if (action == ActionDelete)
    {
        //nao eh ponteiro
        if (search == SearchAll ||
            search == SearchDelete)
        {
            //vamos procurar pela funcao conceito _Delete
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
                    //se nao achou delete procura a destroy 
                    //e depois chama free
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
            //nao procurar pela delete mas procurar pela destroy
            //posso procurar pela destroy
            //se nao achou delete procura a destroy 
            //e depois chama free
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
                //pega o nome
                //const char * TStructUnionSpecifier_GetSpecialMemberName(TStructUnionSpecifier * p, enum DefaultFunctionTags type)


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


//Verifica se tem "cara" de ser o vector
static bool IsVector(TStructUnionSpecifier * pStructUnionSpecifier)
{
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
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
    TParameterTypeList * pArgsOpt, //parametros
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
        //lista argumentos separados por virgula
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
                //2 is struct
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
                //1 is typedef
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

    Map2_Destroy(&map, NULL); //LEAK?
}

void InstanciateDestroy2(TProgram * program,
    PrintCodeOptions * options,
    TSpecifierQualifierList * pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
    TInitializer * pInitializerOpt, //usado para inicializacao estatica
    TParameterTypeList * pArgsOpt, //parametros do create /init
    const char * pInitExpressionText, //(x->p->i = 0)    
    const char * pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                //se passar null eh pq nao interessa
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
        //error
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
            //Pode ter uma cadeia de typdefs
            //ele vai entrandando em cada uma ...
            //ate que chega no fim recursivamente
            //enquanto ele vai andando ele vai tentando
            //algo com o nome do typedef
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

                //TPointerList_Printf(&declarator.PointerList);

                if (action == ActionCreate)
                {
                    //create do typedef eh um pouco difernet
                    //das outras

                    //vou deixar o malloc aqui fora
                    //existe typedef p struct sem nome
                    //entao queremos usar o nome do typedef
                    //typedef struct { int i; } X; X* X_Create();
                    //para poder fazer 
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s *p = (%s*) %s(sizeof * p);",
                        pSingleTypeSpecifier->TypedefName,
                        pSingleTypeSpecifier->TypedefName,
                        GetMallocStr(program));

                    PrintIfNotNullLn(program, options, "p", fp);

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");

                    options->IdentationLevel++;

                    /////////////////
                    //vou ver se tem init para typedef

                    TDeclaration * pDeclarationInit =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                            pSpecifierQualifierList,
                            pDeclatator,
                            "init");

                    //TDeclaration * pDeclarationInit =
                      //  SymbolMap_FindObjFunctionByType(&program->GlobalScope,
                        //    pSingleTypeSpecifier->TypedefName,
                          //  "init");

                    if (pDeclarationInit)
                    {
                        const char * funcName = TDeclaration_GetFunctionName(pDeclarationInit);


                        StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                            "%s(p",
                            funcName);

                        //StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                            //"%s_Init(p",
                            //pSingleTypeSpecifier->TypedefName);

                        if (TParameterTypeList_HasNamedArgs(pArgsOpt))
                        {
                            StrBuilder_Append(fp, ", ");
                            TParameterTypeList_GetArgsString(pArgsOpt, fp);
                        }

                        StrBuilder_Append(fp, ");\n");

                        bComplete = true;
                    }
                    ////////////////


                    if (!bComplete)
                    {

                        //passa a informacao do tipo correto agora
                        InstanciateDestroy2(program,
                            options,
                            (TSpecifierQualifierList *)pDeclarationSpecifiers,
                            &declarator,
                            NULL,
                            pArgsOpt,
                            "p",
                            NULL /*not used*/,
                            ActionInitContent,
                            SearchNone, //se tivesse init ja tinha achado
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
                        pSpecifierQualifierList,//<-dupla para entender o tipo
                        pDeclatator,                        //<-dupla para entender o tipo
                        pArgsOpt, //parametros do create /init
                        pInitializerOpt,
                        pInitExpressionText, //(x->p->i = 0)    
                        pszAutoPointerLenExpressionOpt,
                        action,
                        search,
                        pSingleTypeSpecifier->TypedefName,
                        fp);


                    if (!bComplete)
                    {
                        Action action2 = action;

                        //passa a informacao do tipo correto agora
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
                //nao achou a declaracao
                //assert(false);
            }

        }
        else if (pSingleTypeSpecifier->Token2 == TK_STRUCT ||
            pSingleTypeSpecifier->Token2 == TK_UNION)
        {
            TStructUnionSpecifier * pStructUnionSpecifier = NULL;

            //Indica se consegui fazer sem entrar na struct
            bool bComplete = false;

            bComplete = FindHighLevelFunction(program,
                options,
                pSpecifierQualifierList,//<-dupla para entender o tipo
                pDeclatator,                        //<-dupla para entender o tipo
                pArgsOpt,
                pInitializerOpt,
                pInitExpressionText, //(x->p->i = 0)    
                pszAutoPointerLenExpressionOpt,
                action,
                search,
                pSingleTypeSpecifier->TypedefName,
                fp);

            //Exemplos
            //struct Y *pY e � para destruir o conteudo
            //struct Y *pY e NAO � para destruir o conteudo
            //struct Y * auto pY; e � para destruir o conteudo ou nao
            //struct Y y; //eh para destruir o conteudo
            if (!bComplete) //se for para entrar na struct
            {
                if (pSingleTypeSpecifier &&
                    pSingleTypeSpecifier->TypedefName != NULL)
                {
                    //se nao eh completa tenta achar
                    //vou procurar a definicao completa da struct
                    pStructUnionSpecifier =
                        SymbolMap_FindStructUnion(&program->GlobalScope, pSingleTypeSpecifier->TypedefName);
                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                //DAQUI para baixo o codigo eh todo igual ao da struct
                //COMPARTILHAR        
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
                                ////assert(false);
                            }

                        }

                    }
                    else if (action == ActionCreate)
                    {
                        //struct sem nome tem que ser criada
                        //com typedef que chama outro codigo
                        //assert(pStructUnionSpecifier->Name != NULL);

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
                                NULL, /*args*/
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
                                NULL, /*args*/
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
                        //ok tem a definicao completa da struct
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
                                    //O padrao eh ser o inicializador do tipo
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
                                        //destroy normal
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

                                        //Tem que detectar isso aqui!
                                        // String * /*@auto*/ pItems;
                                        // X * /*@auto*/ * /*@auto*/ pItems;
                                        //sef or ele vai precisar da informacao do _size
                                        // X * /*@auto*/ * /*@auto*/ _size(Size) pItems;
                                        //e dai ele passa a string para  funcao gerar


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
                                            //nao tem size
                                        }
                                    }

                                    //Se for destroy e sor 
                                    InstanciateDestroy2(program,
                                        options,
                                        &pStructDeclaration->SpecifierQualifierList,
                                        pStructDeclarator->pDeclarator,
                                        pStructMemberInitializer,
                                        NULL, //nao passa os args
                                        strVariableName.c_str,
                                        strPonterSizeExpr.c_str,
                                        action2,
                                        SearchAll,
                                        pbHasInitializers,
                                        fp);



                                    //Variavel local
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
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); //fecha  for
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                            }
                            else
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                            }


                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                        }
                    }
                    else if (action == ActionDestroyContent)
                    {
                        if (bIsAutoPointerToAutoPointer)
                        {
                            //    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                            //  options->IdentationLevel--;
                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
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
                    //error nao tem a definicao completa da struct
                    StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////
            }//complete


        }
        else if (pSingleTypeSpecifier->Token2 == TK_ENUM)
        {
            //sample
            //enum E {A}; E* E_Create();
        }
        else
        {
            //nao eh typedef, deve ser int, double etc..
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

                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                }
                else
                {
                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
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

        //Indica se consegui fazer sem entrar na struct
        bool bComplete = false;


        bComplete = FindHighLevelFunction(program,
            options,
            pSpecifierQualifierList,//<-dupla para entender o tipo
            pDeclatator,                        //<-dupla para entender o tipo
            pArgsOpt,
            pInitializerOpt,
            pInitExpressionText, //(x->p->i = 0)    
            pszAutoPointerLenExpressionOpt,
            action,
            search,
            pStructUnionSpecifier->TagName,
            fp);

        //Exemplos
        //struct Y *pY e � para destruir o conteudo
        //struct Y *pY e NAO � para destruir o conteudo
        //struct Y * auto pY; e � para destruir o conteudo ou nao
        //struct Y y; //eh para destruir o conteudo
        if (!bComplete) //se for para entrar na struct
        {
            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->TagName != NULL)
            {
                //se nao eh completa tenta achar
                //vou procurar a definicao completa da struct
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
                            ////assert(false);
                        }

                    }

                }
                else if (action == ActionCreate)
                {
                    //struct sem nome tem que ser criada
                    //com typedef que chama outro codigo
                    //assert(pStructUnionSpecifier->Name != NULL);

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

                    //if (bCanApplyFunction)
                    //{
                    //o primeiro nao precisa do {

                    //  StrBuilder_AppendFmt(fp, "/*%s=*/{", pInitExpressionText);
                    //}
                }

                if (bIsUnionTypes)
                {
                    if (action == ActionDelete)
                    {
                        options->IdentationLevel++;
                        UnionTypeDefault(program,
                            options,
                            pStructUnionSpecifier->TagName,
                            NULL, /*args*/
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
                            NULL, /*args*/
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
                    //ok tem a definicao completa da struct
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

                                //O padrao eh ser o inicializador do tipo
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
                                    //destroy normal
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

                                    //Tem que detectar isso aqui!
                                    // String * /*@auto*/ pItems;
                                    // X * /*@auto*/ * /*@auto*/ pItems;
                                    //sef or ele vai precisar da informacao do _size
                                    // X * /*@auto*/ * /*@auto*/ _size(Size) pItems;
                                    //e dai ele passa a string para  funcao gerar


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
                                        //nao tem size
                                    }
                                }

                                //Se for destroy e sor 
                                InstanciateDestroy2(program,
                                    options,
                                    &pStructDeclaration->SpecifierQualifierList,
                                    pStructDeclarator->pDeclarator,
                                    pStructMemberInitializer,
                                    NULL, //nao passa os args
                                    strVariableName.c_str,
                                    strPonterSizeExpr.c_str,
                                    action2,
                                    SearchAll,
                                    pbHasInitializers,
                                    fp);



                                //Variavel local
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
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); //fecha  for
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                        }


                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                    }
                }
                else if (action == ActionDestroyContent)
                {
                    if (bIsAutoPointerToAutoPointer)
                    {
                        //    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                        //  options->IdentationLevel--;
                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
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

                    //if (bCanApplyFunction)
                    //{
                    //  //o primeiro nao tem 
                    //StrBuilder_Append(fp, "}");
                    //}
                }
            }
            else
            {
                //error nao tem a definicao completa da struct
                StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
            }
        }//complete

    }
    else if (pMainSpecifier->Type == TEnumSpecifier_ID)
    {
        TEnumSpecifier * pEnumSpecifier =
            TDeclarationSpecifier_As_TEnumSpecifier(pMainSpecifier);


        //nao eh typedef, deve ser int, double etc..
        if (action == ActionDestroy)
        {
            if (bIsAutoPointerToObject)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else if (bIsAutoPointerToAutoPointer)
            {
                //assert(false);
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else
            {
                //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
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
                //TODO achar a definicao completa do enum
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
                //TODO achar a definicao completa do enum
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
                //TODO achar a definicao completa do enum
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
        //assert(false);
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

    //Procura pela definicao completa da struct
    if (pTStructUnionSpecifier &&
        pTStructUnionSpecifier->TagName != NULL)
    {
        pTStructUnionSpecifier =
            SymbolMap_FindStructUnion(&program->GlobalScope, pTStructUnionSpecifier->TagName);
    }
    else  if (pSingleTypeSpecifier != NULL &&
        pSingleTypeSpecifier->Token2 == TK_STRUCT)
    {
        //Modelo C++ que o nome da struct ja eh suficiente
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
    const char* end; /* end of processed string */
    const char* p;      /* search pointer */
    const char* s;      /* copy pointer */

                        /* extract drive name */
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

    /* search for end of string or stream separator */
    for (end = path; *end && *end != ':'; )
        end++;

    /* search for begin of file extension */
    for (p = end; p > path && *--p != '\\' && *p != '/'; )
        if (*p == '.')
        {
            end = p;
            break;
        }

    if (ext)
        for (s = end; (*ext = *s++); )
            ext++;

    /* search for end of directory name */
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
        //*path = ':';
        //path++;
       // *path = '\\';
       // path++;
    }

    if (dir && dir[0] != '\0')
    {
        while (*dir)
        {
            *path = *dir;
            path++;
            dir++;
        }
        //  *path = '\\';
         // path++;
    }

    while (*name)
    {
        *path = *name;
        path++;
        name++;
    }

    //*path = '.';
    //path++;

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
                    //Ve se tem pontos ..
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
    SplitPath(buffer, drive, dir, fname, ext); // C4996
    
    
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
    SplitPath(buffer, drive, dir, fname, ext); // C4996
    StrBuilder s;// = STRBUILDER_INIT;
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
    SplitPath(buffer, drive, dir, fname, ext); // C4996
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
    SplitPath(buffer, drive, dir, fname, ext); // C4996

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
    /* ScannerItem* pCurrent = list->pHead;
     while (pCurrent)
     {
         switch (pCurrent->token)
         {
         case TK_PRE_INCLUDE:
         case TK_MACRO_CALL:
         case TK_FILE_EOF:
         case TK_MACRO_EOF:
             return 1;
         default:
             break;
         }
         pCurrent = pCurrent->pNext;
     }*/
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
                    //case TK_BREAKLINE:
                      //  PrintLn(ctx, "<BR/>");
                        //break;
                default:
                    //PrintLn(ctx, "<TK>%s</TK>", pCurrent->lexeme.c_str);
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
    //p->
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
    //PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</atomic-specifier>");


}


void TAlignmentSpecifier_PrintXML(TAlignmentSpecifier * p,
                                  struct PrintXMLContext * ctx)
{
    //TScannerItemList_PrintXML(&p->ClueList0, ctx);
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
    //TDeclarations_Print(&pProgram->Declarations, false, fp);

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



