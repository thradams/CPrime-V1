#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten/emscripten.h>



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif







typedef enum
{
  RESULT_OK = 0,
  RESULT_OUT_OF_MEM,
  RESULT_FAIL
} Result;


#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
  void** pItems;
  int size;
  int capacity;

} Array;

#define ARRAY_INIT { NULL , 0 , 0 }

Result Array_Reserve(Array* p, int nelements);
Result Array_Grow(Array* p, int nelements);
void Array_Pop(Array* p, void(*pfDestroyData)(void*));
void* Array_PopGet(Array* p);
void* Array_Top(Array* p);
Result Array_Push(Array* p, void* pItem);
void Array_Clear(Array* p, void(*pfDestroyData)(void*));
void Array_Init(Array* p);

void Array_Destroy(Array* st, void(*pfDestroyData)(void*));

void Array_Swap(Array* p1, Array* p2);
void* Array_PopFront(Array* p);
void* Array_RemoveAt(Array* p, int index);
//////


typedef struct
{
  const char** pItems;
  int size;
  int capacity;

} StrArray;

#define STRARRAY_INIT { NULL , 0 , 0 }

Result StrArray_Reserve(StrArray* p, int nelements);
Result StrArray_Push(StrArray* p, const char* pItem);
void StrArray_Clear(StrArray* p);
void StrArray_Init(StrArray* p);
void StrArray_Destroy(StrArray* st);
void StrArray_Swap(StrArray* p1, StrArray* p2);
#include <string.h>



#include <stdio.h>
//#include <crtdbg.h>
#include <assert.h>
//#define ASSERT(x) _ASSERTE(x)

#define ASSERT(x) 
//assert(x)

#define _auto
#define _default
#define _defval(x)
#define _size(x)
#define _union(x)

/*
inline void Free(void *p)
{
free(p);
}

inline void *Malloc(size_t s)
{
return malloc(s);
}
*/




typedef char * String;
#define STRING_INIT NULL

void String_Init(String* s);

Result String_InitWith(String* pString, const char* source);
void   String_Destroy(String* pString);
void   String_Reset(String* pString);
void   String_Attach(String* pString, char* psz);
void   String_Swap(String* pA, String* pB);

Result String_Set(String *pS1, const char* psz1);

int IsEmptyStr(const char*  psz);




Result Array_Reserve(Array* p, int nelements)
{
  Result result = RESULT_OK;
  if (nelements > p->capacity)
  {
    void** pnew = p->pItems;
    pnew = (void**)realloc(pnew, nelements * sizeof(void*));
    if (pnew)
    {
      p->pItems = pnew;
      p->capacity = nelements;
    }
    else
    {
      result = RESULT_OUT_OF_MEM;
    }
  }
  return result;
}


Result Array_Grow(Array* p, int nelements)
{
  Result result = RESULT_OK;
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


void* Array_PopGet(Array* p)
{
  void* pItem = 0;
  if (p->size > 0)
  {
    pItem = p->pItems[p->size - 1];
    p->pItems[p->size - 1] = NULL;
    p->size--;
  }
  else
  {
    ASSERT(false);
  }
  return pItem;
}

void Array_Pop(Array* p, void(*pfDestroyData)(void*))
{
  void* pItem = Array_PopGet(p);
  if (pfDestroyData)
  {
    pfDestroyData(pItem);
  }
}

void* Array_Top(Array* p)
{
  ASSERT(p->size > 0);
  return p->pItems[p->size - 1];
}

Result Array_Push(Array* p, void* pItem)
{
  Result result = Array_Grow(p, p->size + 1);
  if (result == RESULT_OK)
  {
    p->pItems[p->size] = pItem;
    p->size++;
  }
  return result;
}

void Array_Clear(Array* p, void(*pfDestroyData)(void*))
{
  for (int i = 0; i < p->size; i++)
  {
    if (pfDestroyData)
      pfDestroyData(p->pItems[i]);
  }
  free(p->pItems);
  p->pItems = NULL;
  p->size = 0;
  p->capacity = 0;
}


void Array_Init(Array* p)
{
  p->capacity = 0;
  p->size = 0;
  p->pItems = NULL;
}

void Array_Destroy(Array* st, void(*pfDestroyData)(void*))
{
  Array_Clear(st, pfDestroyData);
}

void Array_Swap(Array* p1, Array* p2)
{
  int c = p1->capacity;
  int s = p1->size;
  void** pp = p1->pItems;
  p1->capacity = p2->capacity;
  p1->size = p2->size;
  p1->pItems = p2->pItems;
  p2->capacity = c;
  p2->size = s;
  p2->pItems = pp;
}


Result StrArray_Reserve(StrArray* p, int nelements)
{
  return Array_Reserve((Array*)p, nelements);
}

Result StrArray_Push(StrArray* p, const char* pItem)
{
  String s;
  Result result = String_InitWith(&s, pItem);
  if (result == RESULT_OK)
  {
    result = Array_Push((Array*)p, s);
    if (result != RESULT_OK)
    {
      String_Destroy(&s);
    }
  }
  return result;
}

static void Array_DeleteStrVoid(void* p)
{
  String_Destroy((String*)(&p));
}

void StrArray_Clear(StrArray* p)
{
  Array_Clear((Array*)p, Array_DeleteStrVoid);
}

void StrArray_Init(StrArray* p)
{
  Array_Init((Array*)p);
}

void StrArray_Destroy(StrArray* p)
{
  Array_Destroy((Array*)p, &Array_DeleteStrVoid);
}

void StrArray_Swap(StrArray* p1, StrArray* p2)
{
  StrArray temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}



void* Array_PopFront(Array* p)
{
  void* pItem = NULL;
  ASSERT(p->size > 0);
  if (p->size > 0)
  {
    pItem = p->pItems[0];
    if (p->size > 1)
    {
      memmove(p->pItems, p->pItems + 1, sizeof(void*) * (p->size - 1));
    }
    p->size--;
  }
  return pItem;
}







#define ForEachListItem(T, var, list)\
  for (T * var = (list)->pHead ; var != NULL; var =  var->pNext)

#define List_IsFirstItem(pList, pItem) ((pList)->pHead == (pItem))
#define List_IsLastItem(pList, pItem) ((pList)->pTail == (pItem))





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

Result StrBuilder_Reserve(StrBuilder* p, int nelements);

void StrBuilder_Attach(StrBuilder* wstr,
  char* psz,
  int nBytes);

void StrBuilder_Destroy(StrBuilder* wstr);
void StrBuilder_Swap(StrBuilder* str1, StrBuilder* str2);


void StrBuilder_Clear(StrBuilder* wstr);

Result StrBuilder_SetN(StrBuilder* p,
  const char* source,
  int nelements);

Result StrBuilder_Set(StrBuilder* p,
  const char* source);

Result StrBuilder_AppendN(StrBuilder* p,
  const char* source,
  int nelements);

Result StrBuilder_Append(StrBuilder* p,
  const char* source);

char* StrBuilder_Release(StrBuilder* p);


void StrBuilder_AppendFmt(StrBuilder * p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(StrBuilder * p, int nspaces, const char* fmt, ...);

Result StrBuilder_AppendWChar(StrBuilder * p, wchar_t wch);
Result StrBuilder_AppendW(StrBuilder * p, const wchar_t* psz);
Result StrBuilder_AppendChar(StrBuilder * p, char wch);
void StrBuilder_Trim(StrBuilder* p);
Result StrBuilder_AppendUpper(StrBuilder *p, const char* s);

Result StrBuilder_AppendIdent(StrBuilder* p,
  int nspaces,
  const char* source);


void StrBuilder_AppendFmtLn(StrBuilder * p,
  int nspaces,
  const char* fmt,
  ...);
void StrBuilder_AppendFmtV(StrBuilder * p, const char* fmt, va_list va);

typedef struct
{
  //name to identify this stream
  String NameOrFullPath;
  String FullDir2;

  //stream content and length
  String text;
  int text_length;

  int position;
  wchar_t currentChar;

  int currentLine;
  int currentCol;

} SStream;



Result SStream_Init(SStream* pfStream,
  const char* name,
  const char* psz);

Result SStream_InitFile(SStream* pfStream,
  const char* fileName);

void SStream_Destroy(SStream* pfStream);

wchar_t SStream_LookAhead(SStream* pStream);

void SStream_Match(SStream* pStream);
bool SStream_MatchChar(SStream* pStream, wchar_t ch);


#define LOCALSTRBUILDER_NCHARS 7

typedef struct
{
  char* c_str;
  int size;
  int capacity;
  char chars[LOCALSTRBUILDER_NCHARS + 1];

} LocalStrBuilder;


void LocalStrBuilder_Init(LocalStrBuilder* p);

void LocalStrBuilder_Swap(LocalStrBuilder* pA, LocalStrBuilder* pB);

void LocalStrBuilder_Destroy(LocalStrBuilder* p);

void LocalStrBuilder_Reserve(LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Print(LocalStrBuilder* p);

void LocalStrBuilder_Clear(LocalStrBuilder* p);

void LocalStrBuilder_Grow(LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Append(LocalStrBuilder* p, const char* source);
void LocalStrBuilder_AppendChar(LocalStrBuilder* p, char ch);
void LocalStrBuilder_Set(LocalStrBuilder* p, const char* source);

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
  TK_STRING_LITERAL,
  TK_IDENTIFIER,
  TK_SPACES,
  TK_DECIMAL_INTEGER,
  TK_HEX_INTEGER,
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

#ifdef LANGUAGE_EXTENSIONS
                      TK__AUTO,
                      TK__SIZE,
                      TK__DEFAULT,
                      TK__DEFVAL,
#endif

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
#ifdef LANGUAGE_EXTENSIONS
                      TK__UNION, //extension
#endif
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
                      TK_CLASS,

                      //

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

//APELIDOS PARA TOKENS
//type-qualifier-extensions
#define TK_OPT_QUALIFIER   TK_QUESTION_MARK
#define TK_OWN_QUALIFIER   TK_CIRCUMFLEX_ACCENT
#define TK_DTOR_QUALIFIER  TK_PERCENT_SIGN
#define TK_MDTOR_QUALIFIER TK_VERTICAL_LINE

//
#define TK_MOVE TK_ANDAND

typedef struct ScannerItem
{
  LocalStrBuilder lexeme;
  Tokens token;
  int Line _defval(-1);
  int FileIndex _defval(-1);
  bool bActive _defval(1);
  struct ScannerItem* pNext;
} ScannerItem;


const char* TokenToString(Tokens tk);

void ScannerItem_Init(ScannerItem* scannerItem);
void ScannerItem_Reset(ScannerItem* scannerItem);
void ScannerItem_Swap(ScannerItem* scannerItem, ScannerItem* other);
void ScannerItem_Destroy(ScannerItem* scannerItem);
void ScannerItem_Copy(ScannerItem* scannerItem, ScannerItem* other);
ScannerItem* ScannerItem_Create(void);
void ScannerItem_Delete(ScannerItem* scannerItem);

typedef enum
{
  BasicScannerType_Macro,
  BasicScannerType_Token,
  BasicScannerType_File,
} BasicScannerType;

typedef struct BasicScanner
{
  BasicScannerType Type;
  SStream stream;
  ScannerItem currentItem;

  //true antes do 1 token de cada linha
  bool bLineStart;
  bool bMacroExpanded;
  int FileIndex;
  Tokens m_Token;
  struct BasicScanner* pPrevious;

} BasicScanner;


const char* BasicScanner_Lexeme(BasicScanner* scanner);
bool        BasicScanner_IsLexeme(BasicScanner* scanner, const char* psz);
//void        BasicScanner_Match(BasicScanner* scanner);
void        BasicScanner_Match(BasicScanner* scanner);
bool         BasicScanner_MatchToken(BasicScanner* scanner, Tokens token);
Result      BasicScanner_InitFile(BasicScanner* pScanner, const char* fileName);
Result      BasicScanner_CreateFile(const char* fileName, BasicScanner** pp);
void        BasicScanner_Delete(BasicScanner* pScanner);

Result BasicScanner_Init(BasicScanner* pScanner,
  const char* name,
  const char* text,
  BasicScannerType Type);

Result BasicScanner_Create(BasicScanner** pp,
  const char* name,
  const char* text,
  BasicScannerType Type);

void BasicScanner_Destroy(BasicScanner* pScanner);



typedef BasicScanner* BasicScannerStack;
#define ITEM_STACK_INIT NULL
void BasicScannerStack_Init(BasicScannerStack* stack);
void BasicScannerStack_Push(BasicScannerStack* stack, BasicScanner* pItem);
BasicScanner* BasicScannerStack_PopGet(BasicScannerStack* stack);
void BasicScannerStack_Pop(BasicScannerStack* stack);
void BasicScannerStack_PopIfNotLast(BasicScannerStack* stack);
void BasicScannerStack_Destroy(BasicScannerStack* stack);

#define ForEachBasicScanner(pItem, stack)\
    for (BasicScanner* pItem = stack;\
      pItem;\
      pItem = pItem->pPrevious)



#include <inttypes.h>

typedef struct
{
  String key;
  void *data;
  uint32_t hash;
} BucketItem;
#define BUCKET_ITEM_INIT { STRING_INIT, NULL, 0 }

typedef struct
{
  BucketItem** data;
  int size;
  int capacity;

} Bucket;
#define BUCKET_INIT {NULL , 0,0 }

typedef struct
{
  Bucket** data;
  int size;
} Buckets;
#define BUCKETS_INIT { NULL, 0}

typedef struct
{
  Buckets buckets;
  int Size;
} Map;

#define MAP_INIT {BUCKETS_INIT, 0}

Result Map_Init(Map* map, int nBuckets);

void Map_Swap(Map* map, Map* map2);

void Map_Destroy(Map *map, void(*pfDestroyData)(void*));

void Map_Delete(Map *map, void(*pfDestroyData)(void*));
Result Map_Create(Map **map, int nBuckets);

Result Map_Set(Map *map, const char*key, void *data);
Result Map_SetMoveKey(Map* map, String* key, void* data);

Result Map_Find(Map* map, const char* key, void** pp);
void* Map_Find2(Map* map, const char* key);
Result Map_DeleteItem(Map *map, const char* key, void(*pfDestroyData)(void*));
Result Map_DeleteItemOpt(Map* map, const char* key, void(*pfDestroyData)(void*));

void Map_Print(Map *map);





//////////////
typedef struct
{
  Buckets buckets;
  int Size;
} MultiMap;

#define MULTIMAP_INIT {BUCKETS_INIT, 0}

Result MultiMap_Init(MultiMap* map, int nBuckets);
void MultiMap_Destroy(MultiMap *map, void(*pfDestroyData)(void*));

//Adiciona outro item no mapa sem testar se ja existe
Result MultiMap_Add(MultiMap *map, const char*key, void *data);

//Retorna todo bucket que tem o mesm hash
//Ainda � preciso percorrer para saber se sao da mesma key
//Varias entradas para mesma key
Bucket* MultiMap_FindBucket(MultiMap* map, const char* key);
void MultiMap_Swap(MultiMap* map, MultiMap* map2);




typedef struct PPToken PPToken;

typedef struct
{
  PPToken* _auto * _auto _size(Size) pItems;
  int Size;
  int Capacity;
} TokenArray;

#define TOKENARRAY_INIT {0, 0, 0}

void      TokenArray_Reserve(TokenArray* p, int nelements);
int      TokenArray_Grow(TokenArray* p, int nelements);
void     TokenArray_Pop(TokenArray* p);

PPToken* TokenArray_PopFront(TokenArray* p);

PPToken*      TokenArray_Top(TokenArray* p);
void      TokenArray_PushBack(TokenArray* p, PPToken* pItem);
void     TokenArray_Clear(TokenArray* p);
void     TokenArray_Init(TokenArray* p);
TokenArray* TokenArray_Create();
void     TokenArray_Destroy(TokenArray* st);
void     TokenArray_Delete(TokenArray* st);
void     TokenArray_Swap(TokenArray* p1, TokenArray* p2);

//


bool TokenArray_Contain(TokenArray *pArray, PPToken* pToken);

void TokenArray_AppendCopy(TokenArray *pArrayTo, const TokenArray *pArrayFrom);
void TokenArray_AppendMove(TokenArray *pArrayTo, TokenArray *pArrayFrom);
void TokenArray_Print(const TokenArray* tokens);
void TokenArray_ToStrBuilder(const TokenArray* tokens, StrBuilder* strBuidler);

PPToken* TokenArray_Find(const TokenArray *pArray, const char * lexeme);
void TokenArray_Erase(TokenArray *pArray, int begin, int end);


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
  const char*  Key,
  TokenArray** rValue);

bool TokenArrayMap_RemoveKey(TokenArrayMap* pMap,
  const char*  Key);

void TokenArrayMap_Init(TokenArrayMap* p);
void TokenArrayMap_Destroy(TokenArrayMap* p);



void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB);


typedef struct
{
  PPToken* _auto * _auto _size(Size) pItems;
  int Size;
  int Capacity;
} TokenSet;
#define TOKENSET_INIT { NULL, 0, 0 }

void TokenSet_PushBack(TokenSet* p, PPToken* pItem);
void TokenSetAppendCopy(TokenSet *pArrayTo, const TokenSet *pArrayFrom);
PPToken* TokenSet_Find(const TokenSet *pArray, const char * lexeme);
void TokenSet_Destroy(TokenSet *pArray);

void SetIntersection(const TokenSet *p1,
  const TokenSet *p2,
  TokenSet *pResult);
typedef enum
{
  PPTokenType_Identifier,
  PPTokenType_Number,
  PPTokenType_CharConstant,
  PPTokenType_StringLiteral,
  PPTokenType_Punctuator,
  PPTokenType_Spaces,
  PPTokenType_Other,
} PPTokenType;

typedef struct PPToken
{
  PPTokenType Token;
  String Lexeme;
  TokenSet HiddenSet;
} PPToken;

#define TOKEN_INIT { PPTokenType_Other, STRING_INIT, TOKENSET_INIT }


void PPToken_Destroy(PPToken* p);

PPToken*  PPToken_Create(const char* s, PPTokenType token);
PPToken*  PPToken_Clone(PPToken* p);
void PPToken_Delete(PPToken * p);
void PPToken_DeleteVoid(void* pv);
void PPToken_Swap(PPToken * pA, PPToken * pB);


bool PPToken_IsIdentifier(PPToken* pHead);
bool PPToken_IsSpace(PPToken* pHead);
bool PPToken_IsStringizingOp(PPToken* pHead);
bool PPToken_IsConcatOp(PPToken* pHead);
bool PPToken_IsStringLit(PPToken* pHead);
bool PPToken_IsCharLit(PPToken* pHead);
bool PPToken_IsOpenPar(PPToken* pHead);
bool PPToken_IsChar(PPToken* pHead, char ch);
bool PPToken_IsLexeme(PPToken* pHead, const char* ch);

typedef struct MapItem2
{
  struct MapItem2* pNext;
  unsigned int HashValue;
  String Key;
  void* pValue;
} MapItem2;

typedef struct
{
  MapItem2** pHashTable;
  unsigned int nHashTableSize;
  int  nCount;
} Map2;


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map2_SetAt(Map2* pMap,
  const char* Key,
  void* newValue,
  void** ppPreviousValue);


bool Map2_Lookup(Map2* pMap,
  const char*  Key,
  void** rValue);

bool Map2_RemoveKey(Map2* pMap,
  const char*  Key,
  void** ppValue);

void Map2_Init(Map2* p);
void Map2_Destroy(Map2* p);

Map2*  Map2_Create(void);
void Map2_Delete(Map2 * p);

void Map2_Swap(Map2 * pA, Map2 * pB);

typedef struct
{
  String Name;
  bool bIsFunction;
  TokenArray TokenSequence;
  TokenArray FormalArguments;
  int FileIndex;
} Macro;

Macro* Macro_Create(void);


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
  int  nCount;
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
  bool evalmode,
  Macro* caller,
  TokenArray* pOutputSequence);

void ExpandMacroToText(const TokenArray* pTokenSequence,
  const MacroMap* macros,
  bool get_more,
  bool skip_defined,
  bool evalmode,
  Macro* caller,
  StrBuilder* strBuilder);



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
  ScannerItem* _auto pHead, *pTail;
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



struct TTypePointer;
typedef struct TTypePointer TTypePointer;

typedef struct SymbolMapItem
{
  struct SymbolMapItem* pNext;
  unsigned int HashValue;
  String Key;
  TTypePointer* pValue;
} SymbolMapItem;

typedef struct SymbolMap
{
  SymbolMapItem** pHashTable;
  int nHashTableSize;
  int  nCount;
  struct SymbolMap* pPrevious;
} SymbolMap;


#define SYMBOLMAP_INIT { NULL, 100, 0 , NULL}

int SymbolMap_SetAt(SymbolMap* pMap,
  const char* Key,
  TTypePointer* newValue);


TTypePointer* SymbolMap_Find(SymbolMap* pMap,
  const char*  Key);

bool SymbolMap_RemoveKey(SymbolMap* pMap,
  const char*  Key,
  TTypePointer** ppValue);

void SymbolMap_Init(SymbolMap* p);
void SymbolMap_Destroy(SymbolMap* p);

SymbolMap*  SymbolMap_Create();
void SymbolMap_Delete(SymbolMap * p);

SymbolMapItem* SymbolMap_FindBucket(SymbolMap* pMap, const char*  Key);

void SymbolMap_Swap(SymbolMap * pA, SymbolMap * pB);

void SymbolMap_Print(SymbolMap* pMap);
bool SymbolMap_IsTypeName(SymbolMap* pMap, const char* identifierName);

struct TStructUnionSpecifier* SymbolMap_FindStructUnion(SymbolMap* pMap, const char* structTagName);
struct TEnumSpecifier* SymbolMap_FindEnum(SymbolMap* pMap, const char* enumTagName);

struct TTypePointer;
typedef struct TTypePointer TTypePointer;

struct TTypeSpecifier;
typedef struct TTypeSpecifier TTypeSpecifier;

TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(SymbolMap* pMap,
  const char* typedefName);

struct TDeclaration* SymbolMap_FindTypedefDeclarationTarget(SymbolMap* pMap,
  const char* typedefName);
struct TDeclaration* SymbolMap_FindFunction(SymbolMap* pMap, const char* funcName);
struct TDeclaration* SymbolMap_FindObjFunction(SymbolMap* pMap,
  const char* objName,
  const char* funcName);

struct TDeclarator;

struct TDeclarationSpecifiers* SymbolMap_FindTypedefTarget(SymbolMap* pMap,
  const char* typedefName,
  struct TDeclarator* declarator);

struct TDeclarationSpecifiers* SymbolMap_FindTypedefFirstTarget(SymbolMap* pMap,
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
  EType Type _defval(TStaticAssertDeclaration_ID);

  TExpression*_auto  pConstantExpression;
  String Text;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;
  TScannerItemList ClueList4;
  TScannerItemList ClueList5;

} TStaticAssertDeclaration;

TStaticAssertDeclaration* TStaticAssertDeclaration_Create();
void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration* p);


typedef struct
{
  /*
  Marca fim de um arquivo
  */
  EType Type _defval(TEofDeclaration_ID);
  TScannerItemList ClueList0;
} TEofDeclaration;

TEofDeclaration* TEofDeclaration_Create();
void TEofDeclaration_Delete(TEofDeclaration* p);

struct TStatement;
typedef struct TStatement TStatement;

struct TGroupDeclaration;
typedef struct TGroupDeclaration TGroupDeclaration;

struct _union(TStaticAssertDeclaration |
  TDeclaration |
  TGroupDeclaration |
  TEofDeclaration) TAnyDeclaration
{
  EType Type;
};

typedef struct TAnyDeclaration TAnyDeclaration;
void TAnyDeclaration_Delete(TAnyDeclaration* p);


struct TBlockItem;
typedef struct TBlockItem TBlockItem;

typedef struct {
  /*
  block-item-list:
  block-item
  block-item-list block-item
  */
  TBlockItem * _auto * _auto _size(Size) pItems;
  int Size;
  int Capacity;
} TBlockItemList;

void TBlockItemList_Destroy(TBlockItemList* p);
void TBlockItemList_Init(TBlockItemList* p);
void TBlockItemList_PushBack(TBlockItemList* p, TBlockItem* pItem);


typedef struct
{
  EType Type  _defval(TCompoundStatement_ID);
  TBlockItemList BlockItemList;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;

} TCompoundStatement;

TCompoundStatement* TCompoundStatement_Create();
void TCompoundStatement_Delete(TCompoundStatement* p);


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

  EType Type _defval(TTypeQualifier_ID);
  String SizeIdentifier;
  Tokens Token;
  TScannerItemList ClueList0;

} TTypeQualifier;

void TTypeQualifier_Copy(TTypeQualifier* dest, TTypeQualifier* src);

typedef struct {
  /*
  type-qualifier-list:
  type-qualifier
  type-qualifier-list type-qualifier
  */

  TTypeQualifier * _auto Data[4];
  int Size;

} TTypeQualifierList;

void TTypeQualifierList_Init(TTypeQualifierList* p);
void TTypeQualifierList_Destroy(TTypeQualifierList* p);
void TTypeQualifierList_PushBack(TTypeQualifierList* p, TTypeQualifier* pItem);
void TTypeQualifierList_Copy(TTypeQualifierList* dest, TTypeQualifierList* src);

TTypeQualifier* TTypeQualifier_Create(void);
void TTypeQualifier_Delete(TTypeQualifier* p);


typedef struct
{
  EType Type _defval(TExpressionStatement_ID);
  TExpression *_auto    pExpression;
  TScannerItemList ClueList0;
} TExpressionStatement;

TExpressionStatement* TExpressionStatement_Create(void);
void TExpressionStatement_Delete(TExpressionStatement* p);

typedef struct
{
  EType Type _defval(TJumpStatement_ID);
  Tokens token;
  String Identifier;
  TExpression *_auto   pExpression;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TJumpStatement;

TJumpStatement* TJumpStatement_Create(void);
void TJumpStatement_Delete(TJumpStatement* p);


typedef struct
{
  EType Type  _defval(TAsmStatement_ID);
  TScannerItemList ClueList;
} TAsmStatement;

TAsmStatement* TAsmStatement_Create(void);
void TAsmStatement_Delete(TAsmStatement* p);

typedef struct
{
  EType Type  _defval(TForStatement_ID);
  TAnyDeclaration*_auto   pInitDeclarationOpt;
  TExpression*_auto   pExpression1;
  TExpression*_auto  pExpression2;
  TExpression*_auto   pExpression3;
  TStatement*_auto   pStatement;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;
  TScannerItemList ClueList4;
} TForStatement;

TForStatement* TForStatement_Create(void);
void TForStatement_Delete(TForStatement* p);

typedef struct
{
  EType Type  _defval(TWhileStatement_ID);
  TExpression*_auto   pExpression;
  TStatement*_auto   pStatement;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TWhileStatement;

TWhileStatement* TWhileStatement_Create(void);
void TWhileStatement_Delete(TWhileStatement* p);

typedef struct
{
  EType Type  _defval(TDoStatement_ID);
  TExpression *_auto    pExpression;
  TStatement*_auto    pStatement;
  TScannerItemList ClueList0; //do
  TScannerItemList ClueList1; //while
  TScannerItemList ClueList2; //(
  TScannerItemList ClueList3; //)
  TScannerItemList ClueList4; // ;

} TDoStatement;

TDoStatement* TDoStatement_Create(void);
void TDoStatement_Delete(TDoStatement* p);

typedef struct
{
  EType Type  _defval(TLabeledStatement_ID);

  TStatement *_auto   pStatementOpt;
  TExpression *_auto   pExpression;
  String Identifier;
  Tokens token;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
} TLabeledStatement;

TLabeledStatement* TLabeledStatement_Create(void);
void TLabeledStatement_Delete(TLabeledStatement* p);


typedef struct
{
  EType Type  _defval(TSwitchStatement_ID);
  TExpression *_auto   pConditionExpression;
  TStatement*_auto    pExpression;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TSwitchStatement;

TSwitchStatement* TSwitchStatement_Create(void);
void TSwitchStatement_Delete(TSwitchStatement* p);


typedef struct
{
  EType Type  _defval(TIfStatement_ID);
  TExpression*_auto    pConditionExpression;
  TStatement*_auto   pStatement;
  TStatement*_auto   pElseStatement;
  TScannerItemList ClueList0; //if 
  TScannerItemList ClueList1; //(
  TScannerItemList ClueList2; //)
  TScannerItemList ClueList3; //else
} TIfStatement;

TIfStatement* TIfStatement_Create(void);
void TIfStatement_Delete(TIfStatement* p);


struct _union(TCompoundStatement |
  TExpressionStatement |
  TLabeledStatement |
  TJumpStatement |
  TIfStatement |
  TDoStatement |
  TForStatement |
  TAsmStatement |
  TWhileStatement |
  TSwitchStatement) TStatement
{
  EType Type;
};

typedef struct TStatement TStatement;
void TStatement_Delete(TStatement* p);

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
struct _union(TDeclaration | TStatement) TBlockItem
{
  EType Type;
};

typedef struct TBlockItem TBlockItem;
void TBlockItem_Delete(TBlockItem* p);

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
  struct TPointer* _auto pNext;
  TScannerItemList ClueList0;
} TPointer;

TPointer* TPointer_Create(void);
void TPointer_Delete(TPointer* p);
void TPointer_Copy(TPointer* dest, TPointer* src);


typedef struct TPointerList
{
  /*
  pointer:
  * type-qualifier-listopt
  * type-qualifier-listopt pointer
  */
  TPointer* _auto pHead, *pTail;
} TPointerList;

void TPointerList_PushBack(TPointerList* pList, TPointer* pItem);

void TPointerList_Printf(TPointerList* p);
void TPointerList_Destroy(TPointerList* p);
bool TPointerList_IsPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerN(TPointerList* pPointerlist, int n);
bool TPointerList_IsAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointer(TPointerList* pPointerlist);
void TPointerList_Swap(TPointerList* a, TPointerList* b);
bool TPointerList_IsAutoPointerSizeToObject(TPointerList* pPointerlist);

const char * TPointerList_GetSize(TPointerList* pPointerlist);

typedef struct
{
  /*
  function-specifier:
  inline
  _Noreturn
  */
  EType Type  _defval(TFunctionSpecifier_ID);
  Tokens Token;
  TScannerItemList ClueList0;
} TFunctionSpecifier;


TFunctionSpecifier* TFunctionSpecifier_Create(void);
void TFunctionSpecifier_Delete(TFunctionSpecifier* p);

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
  EType Type  _defval(TStorageSpecifier_ID);
  Tokens Token;
  TScannerItemList ClueList0;
} TStorageSpecifier;

TStorageSpecifier* TStorageSpecifier_Create(void);
void TStorageSpecifier_Delete(TStorageSpecifier* p);


typedef struct
{
  /*
  alignment-specifier:
  _Alignas ( type-name )
  _Alignas ( constant-expression )
  */
  EType Type  _defval(TAlignmentSpecifier_ID);
  String TypeName;
} TAlignmentSpecifier;

TAlignmentSpecifier* TAlignmentSpecifier_Create(void);
void TAlignmentSpecifier_Delete(TAlignmentSpecifier* p);


typedef struct TEnumerator
{
  /*
  enumerator:
  enumeration-constant
  enumeration-constant = constant-expression
  */
  struct TEnumerator* _auto pNext;
  String Name;
  TExpression*_auto   pExpression;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1; // =
  TScannerItemList ClueList2; // ,
  bool bHasComma;
} TEnumerator;

TEnumerator* TEnumerator_Create(void);
void TEnumerator_Delete(TEnumerator* p);


typedef struct
{
  /*
  enumerator-list:
  enumerator
  enumerator-list, enumerator
  */
  TEnumerator * _auto pHead, *pTail;
} TEnumeratorList;
void TEnumeratorList_Destroy(TEnumeratorList* p);
void TEnumeratorList_Init(TEnumeratorList* p);

typedef struct TEnumSpecifier
{
  /*
  enum-specifier:
  enum identifieropt { enumerator-list }
  enum identifieropt { enumerator-list , }
  enum identifier
  */

  EType Type  _defval(TEnumSpecifier_ID);
  String Name;
  TEnumeratorList EnumeratorList;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;
} TEnumSpecifier;

TEnumSpecifier* TEnumSpecifier_Create(void);
void TEnumSpecifier_Delete(TEnumSpecifier* p);

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
  EType Type  _defval(TSingleTypeSpecifier_ID);
  Tokens Token;
  String TypedefName;
  TScannerItemList ClueList0;
} TSingleTypeSpecifier;

TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void);
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier* p);

const char* TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier* p);

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

struct _union(TStorageSpecifier |
  TTypeSpecifier |
  TTypeQualifier |
  TFunctionSpecifier |
  TAlignmentSpecifier) TDeclarationSpecifier
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
struct _union(TTypeSpecifier |
  TTypeQualifier) TSpecifierQualifier
{
  EType Type;
};


/*
specifier-qualifier-list:
type-specifier specifier-qualifier-listopt
type-qualifier specifier-qualifier-listopt
*/
typedef struct TSpecifierQualifier TSpecifierQualifier;
void TSpecifierQualifier_Delete(TSpecifierQualifier* p);

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
  TSpecifierQualifier *_auto *_auto _size(Size) pData;
  int Size;
  int Capacity;
} TSpecifierQualifierList;

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers);
void TSpecifierQualifierList_PushBack(TSpecifierQualifierList* p, TSpecifierQualifier* pItem);
bool TSpecifierQualifierList_IsTypedef(TSpecifierQualifierList* p);
const char* TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList* p);
TDeclarationSpecifier* TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAutoPointer(TSpecifierQualifierList *pSpecifierQualifierList);

bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList* p, Tokens token, const char* lexeme);
bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList* p);


typedef struct TDeclarationSpecifiers {
  /*
  declaration-specifiers:
  storage-class-specifier declaration-specifiersopt
  type-specifier declaration-specifiersopt
  type-qualifier declaration-specifiersopt
  function-specifier declaration-specifiersopt
  alignment-specifier declaration-specifiersopt
  */
  TDeclarationSpecifier *_auto *_auto _size(Size) pData;
  int Size;
  int Capacity;
} TDeclarationSpecifiers;

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers* p, TDeclarationSpecifier* pItem);

const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers);
bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers* pDeclarationSpecifiers, Tokens token, const char* lexeme);


struct TParameter;
typedef struct TParameter TParameter;

typedef struct
{
  /*
  parameter-list:
  parameter-declaration
  parameter-list , parameter-declaration
  */

  TParameter* _auto pHead, *pTail;
} TParameterList;

void TParameterList_Destroy(TParameterList* p);
void TParameterList_Init(TParameterList* p);
const char* TParameter_GetName(TParameter* p);
bool TParameter_IsDirectPointer(TParameter* p);

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

void TParameterTypeList_Init(TParameterTypeList* p);
void TParameterTypeList_Destroy(TParameterTypeList* p);
TParameterTypeList* TParameterTypeList_Create();
void TParameterTypeList_Delete(TParameterTypeList* p);

const char* TParameterTypeList_GetFirstParameterName(TParameterTypeList* p);
const char* TParameterTypeList_GetSecondParameterName(TParameterTypeList* p);
TParameter* TParameterTypeList_FindParameterByName(TParameterTypeList* p, const char* name);
TParameter* TParameterTypeList_GetParameterByIndex(TParameterTypeList* p, int index);
void TParameterTypeList_GetArgsString(TParameterTypeList* p, StrBuilder* sb);
bool TParameterTypeList_HasNamedArgs(TParameterTypeList* p);

typedef struct TDesignator
{
  /*
  designator:
  [ constant-expression ]
  . identifier
  */
  String Name;
  TExpression *_auto  pExpression;
  struct TDesignator * _auto pNext;
  TScannerItemList ClueList0; //. ou [
  TScannerItemList ClueList1; //]
} TDesignator;


TDesignator* TDesignator_Create(void);
void TDesignator_Delete(TDesignator* p);


typedef struct
{
  /*
  designator-list:
  designator
  designator-list designator
  */
  TDesignator* _auto pHead, *pTail;
} TDesignatorList;
void TDesignatorList_Destroy(TDesignatorList* p);
void TDesignatorList_Init(TDesignatorList* p);
void TDesignatorList_PushBack(TDesignatorList* p, TDesignator* pItem);

typedef struct TDesignation
{
  /*
  designation:
  designator-list =
  */
  TDesignatorList DesignatorList;
  TScannerItemList ClueList0;
} TDesignation;

TDesignation* TDesignation_Create(void);
void TDesignation_Delete(TDesignation* p);

struct TInitializer;
typedef struct TInitializer TInitializer;
void TInitializer_Delete(TInitializer* p);

typedef struct TInitializerListItem
{
  /*
  initializer-list:
  designationopt initializer
  initializer-list , designationopt initializer
  */
  TDesignatorList  DesignatorList;
  TInitializer*_auto  pInitializer;
  struct TInitializerListItem* _auto pNext;
  TScannerItemList ClueList;
  bool bDefault;
} TInitializerListItem;

TInitializerListItem* TInitializerListItem_Create();
void TInitializerListItem_Delete(TInitializerListItem* p);



typedef struct TInitializerList
{
  /*
  initializer-list:
  designationopt initializer
  initializer-list , designationopt initializer
  */

  TInitializerListItem * _auto pHead, *pTail;
} TInitializerList;

void TInitializerList_Init(TInitializerList* p);
void TInitializerList_Destroy(TInitializerList* p);
void TInitializerList_Delete(TInitializerList* p);

typedef struct
{
  EType Type  _defval(TInitializerListType_ID);
  TInitializerList InitializerList;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  bool bDefault;
} TInitializerListType;

TInitializerListType* TInitializerListType_Create(void);
void TInitializerListType_Delete(TInitializerListType* p);



struct _union(TInitializerListType | TExpression) TInitializer
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
  TDirectDeclarator* _auto  pDirectDeclarator;
  TScannerItemList ClueList;
} TDeclarator;

TDeclarator* TDeclarator_Create();
void TDeclarator_Init(TDeclarator* p);
void TDeclarator_Destroy(TDeclarator* p);
const char* TDeclarator_GetName(TDeclarator* p);


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

  String Identifier;
  TDeclarator* _auto pDeclarator;
  struct TDirectDeclarator* _auto  pDirectDeclarator;
  TPosition Position;
  TParameterTypeList  Parameters;
  TExpression*   pExpression;
  TDirectDeclaratorType DeclaratorType; //para diferenciar pois null nao basta []
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;
} TDirectDeclarator;


TDirectDeclarator* TDirectDeclarator_Create();
void TDirectDeclarator_Delete(TDirectDeclarator* p);

typedef struct TInitDeclarator
{
  /*
  init-declarator:
  declarator
  declarator = initializer
  */
  TDeclarator*_auto  pDeclarator;
  TInitializer*_auto   pInitializer;
  struct TInitDeclarator * _auto pNext;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1; //defval
} TInitDeclarator;


TInitDeclarator* TInitDeclarator_Create();
void TInitDeclarator_Delete(TInitDeclarator* p);

typedef TInitDeclarator TStructDeclarator;


typedef struct TInitDeclaratorList
{
  /*
  init-declarator-list:
  init-declarator
  init-declarator-list , init-declarator
  */
  TInitDeclarator* _auto pHead, *pTail;
} TInitDeclaratorList;

void TInitDeclaratorList_Destroy(TInitDeclaratorList* p);
void TInitDeclaratorList_Init(TInitDeclaratorList* p);
const char* TDeclarator_GetName(TDeclarator* p);
const char* TInitDeclarator_FindName(TInitDeclarator* p);


typedef struct TStructDeclaratorList
{
  /*
  init-declarator-list:
  init-declarator
  init-declarator-list , init-declarator
  */
  TInitDeclarator* _auto pHead, *pTail;
} TStructDeclaratorList;


void TStructDeclaratorList_Destroy(TStructDeclaratorList* p);
void TStructDeclaratorList_Init(TStructDeclaratorList* p);
void TStructDeclaratorList_Add(TStructDeclaratorList* p, TInitDeclarator* pItem);


typedef struct TStructDeclaration
{
  /*
  struct-declaration:
  specifier-qualifier-list struct-declarator-listopt ;
  static_assert-declaration
  */

  EType Type  _defval(TStructDeclaration_ID);

  TSpecifierQualifierList SpecifierQualifierList;
  TStructDeclaratorList DeclaratorList;
  TScannerItemList ClueList1;
} TStructDeclaration;


TStructDeclaration* TStructDeclaration_Create();
void TStructDeclaration_Delete(TStructDeclaration* p);


/*
struct-declaration:
specifier-qualifier-list struct-declarator-listopt ;
static_assert-declaration
*/
struct _union(TStructDeclaration |
  TStaticAssertDeclaration) TAnyStructDeclaration
{
  EType Type;
};

typedef struct TAnyStructDeclaration TAnyStructDeclaration;
void TAnyStructDeclaration_Delete(TAnyStructDeclaration* p);

CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)
CAST(TAnyStructDeclaration, TEofDeclaration)

typedef struct
{
  TAnyStructDeclaration* _auto * _auto _size(Size) pItems;
  int Size;
  int Capacity;
} TStructDeclarationList;

void TStructDeclarationList_Destroy(TStructDeclarationList* p);
void TStructDeclarationList_Init(TStructDeclarationList* p);
void TStructDeclarationList_PushBack(TStructDeclarationList* p, TAnyStructDeclaration* pItem);


typedef struct TUnionSetItem
{
  struct TUnionSetItem* _auto  pNext;
  Tokens Token;
  Tokens TokenFollow;
  String Name;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TUnionSetItem;

TUnionSetItem* TUnionSetItem_Create();
void TUnionSetItem_Delete(TUnionSetItem*);

typedef struct TUnionSet
{
  TUnionSetItem * _auto pHead, *pTail;

  TScannerItemList ClueList0; // _union
  TScannerItemList ClueList1; //(
  TScannerItemList ClueList2; //)

} TUnionSet;
void TUnionSet_Init(TUnionSet* p);
void TUnionSet_Destroy(TUnionSet* p);
void TUnionSet_PushBack(TUnionSet* p, TUnionSetItem* pItem);

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

  EType Type  _defval(TStructUnionSpecifier_ID);
  TStructDeclarationList StructDeclarationList;
  String Name;

  Tokens Token;
  Tokens Token2;

  TUnionSet UnionSet;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;

} TStructUnionSpecifier;

TStructUnionSpecifier* TStructUnionSpecifier_Create();
void TStructUnionSpecifier_Delete(TStructUnionSpecifier* p);


struct TAtomicTypeSpecifier;
typedef struct TAtomicTypeSpecifier TAtomicTypeSpecifier;


struct _union(TSingleTypeSpecifier |
  TAtomicTypeSpecifier |
  TEnumSpecifier |
  TStructUnionSpecifier) TTypeSpecifier
{
  EType Type;
};

typedef struct TTypeSpecifier TTypeSpecifier;

CAST(TTypeSpecifier, TSingleTypeSpecifier)
CAST(TTypeSpecifier, TEnumSpecifier)
CAST(TTypeSpecifier, TStructUnionSpecifier)
CAST(TDeclarationSpecifier, TStructUnionSpecifier)
CAST(TSpecifierQualifier, TStructUnionSpecifier)
CAST(TTypeSpecifier, TAtomicTypeSpecifier)

typedef struct TDeclaration
{
  /*
  declaration:
  declaration-specifiers init-declarator-listopt ;
  static_assert-declaration
  */

  EType Type  _defval(TDeclaration_ID);
  TDeclarationSpecifiers Specifiers;
  TInitDeclaratorList InitDeclaratorList;

  //se for funcao
  TCompoundStatement* _auto  pCompoundStatementOpt;

  int FileIndex;
  int Line;

  TScannerItemList ClueList0; //default

  bool bDefault;
  TScannerItemList ClueList1;


} TDeclaration;


TDeclaration* TDeclaration_Create();
void TDeclaration_Delete(TDeclaration* p);

TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(TDeclaration* p, int index);

const char* TDeclaration_GetArgName(TDeclaration* p, int index);
int TDeclaration_GetNumberFuncArgs(TDeclaration* p);

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p);

TCompoundStatement* TDeclaration_Is_FunctionDefinition(TDeclaration* p);
const char* TDeclaration_GetFunctionThis(TDeclaration* p);
bool TDeclaration_Is_EnumDeclaration(TDeclaration* p);
TDeclarator* TDeclaration_FindDeclarator(TDeclaration* p, const char* name);
const char* TDeclaration_GetFunctionName(TDeclaration* p);


CAST(TAnyDeclaration, TStaticAssertDeclaration)
CAST(TAnyDeclaration, TDeclaration)
CAST(TAnyDeclaration, TEofDeclaration)

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration);
bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pDeclaration);
int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration);


typedef struct TParameter
{
  /*
  parameter-declaration:
  declaration-specifiers declarator
  declaration-specifiers abstract-declaratoropt
  */

  struct TParameter* _auto pNext;
  TDeclarationSpecifiers Specifiers;
  TDeclarator Declarator;
  TScannerItemList ClueList0; //, do parametro
  bool bHasComma;
} TParameter;

TParameter* TParameter_Create();
void TParameter_Delete(TParameter* p);

void TParameter_Swap(TParameter* a, TParameter* b);
const char* TParameter_GetName(TParameter* p);
const char* TParameter_GetTypedefName(TParameter* p);


typedef struct
{
  TAnyDeclaration * _auto * _auto _size(Size) pItems;
  int Size;
  int Capacity;
} TDeclarations;

void TDeclarations_Destroy(TDeclarations* p);
void TDeclarations_Init(TDeclarations* p);
void TDeclarations_PushBack(TDeclarations* p, TDeclaration* pItem);

typedef struct TGroupDeclaration
{
  /*
  default identifier
  {
  }
  */
  EType Type  _defval(TGroupDeclaration_ID);
  TDeclarations Declarations;
  String Identifier;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TGroupDeclaration;

TGroupDeclaration* TGroupDeclaration_Create();
void TGroupDeclaration_Delete(TGroupDeclaration* p);

//Coleta o resultado do parser
typedef struct
{
  //declaracoes
  TDeclarations Declarations;

  //arquivos na qual declaracao tem indice
  TFileArray Files2;

  //multimap dos simbolos
  //DeclarationsMap Symbols;
  SymbolMap GlobalScope;


  //Defines
  MacroMap Defines;

  StrBuilder sbPreDeclaration;

} TProgram;


void TProgram_Init(TProgram* p);
void TProgram_Destroy(TProgram* p);
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName);
TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name);



typedef struct TTypeName
{
  /*
  type-name:
  specifier-qualifier-list abstract-declaratoropt
  */
  EType Type  _defval(TypeName_ID);
  TSpecifierQualifierList SpecifierQualifierList;
  TDeclarator Declarator;
} TTypeName;

TTypeName* TTypeName_Create();
void TTypeName_Destroy(TTypeName* p);
void TTypeName_Delete(TTypeName* p);
void TTypeName_Init(TTypeName* p);

typedef struct TAtomicTypeSpecifier
{
  /*
  atomic-type-specifier:
  _Atomic ( type-name )
  */
  EType Type  _defval(TAtomicTypeSpecifier_ID);
  TTypeName TypeName;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
} TAtomicTypeSpecifier;


TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create();
void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier* p);


bool EvaluateConstantExpression(TExpression * p, int *pResult);

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration * p);

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name);

bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers);



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

  EType Type _defval(TPrimaryExpressionValue_ID);
  Tokens token;
  String lexeme;
  TExpression*_auto   pExpressionOpt; //( expression )
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
} TPrimaryExpressionValue;

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue* p);
void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p);
TPrimaryExpressionValue* TPrimaryExpressionValue_Create();
void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue* p);

typedef struct TPrimaryExpressionLiteralItem
{
  struct TPrimaryExpressionLiteralItem* _auto pNext;
  String lexeme;
  TScannerItemList ClueList0;
} TPrimaryExpressionLiteralItem;

TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create();
void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem *p);

typedef struct
{
  TPrimaryExpressionLiteralItem * _auto pHead, *pTail;
} TPrimaryExpressionLiteralItemList;

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList* p);
void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList* p);
void TPrimaryExpressionLiteralItemList_Add(TPrimaryExpressionLiteralItemList* p, TPrimaryExpressionLiteralItem *pItem);


typedef struct
{
  EType Type _defval(TPrimaryExpressionLiteral_ID);
  TPrimaryExpressionLiteralItemList List;
} TPrimaryExpressionLiteral;


TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create();
void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral* p);


typedef struct
{
  EType Type _defval(TBinaryExpression_ID);
  Tokens token;
  TExpression*_auto   pExpressionLeft;
  TExpression*_auto    pExpressionRight;
  TPosition Position;

  TScannerItemList ClueList0;

} TBinaryExpression;

TBinaryExpression* TBinaryExpression_Create(void);
void TBinaryExpression_Delete(TBinaryExpression* p);

typedef struct
{
  EType Type _defval(TTernaryExpression_ID);
  Tokens token;
  TExpression*_auto   pExpressionLeft;
  TExpression*_auto    pExpressionMiddle;
  TExpression*_auto    pExpressionRight;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
} TTernaryExpression;

TTernaryExpression* TTernaryExpression_Create(void);
void TTernaryExpression_Delete(TTernaryExpression* p);


struct TTypeName;
typedef struct TTypeName TTypeName;

typedef struct TPostfixExpressionCore
{
  EType Type  _defval(TPostfixExpressionCore_ID);
  Tokens token;
  String lexeme;
  TExpression*_auto   pExpressionLeft;
  TExpression*_auto   pExpressionRight;

  struct TPostfixExpressionCore* _auto  pNext;
  TInitializerList InitializerList;
  String Identifier;
  TTypeName*_auto  pTypeName; /*typename*/

  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
  TScannerItemList ClueList2;
  TScannerItemList ClueList3;
  TScannerItemList ClueList4;

} TPostfixExpressionCore;

TPostfixExpressionCore* TPostfixExpressionCore_Create();
void TPostfixExpressionCore_Delete(TPostfixExpressionCore* p);


typedef struct
{
  EType Type  _defval(TCastExpressionType_ID);
  TExpression*_auto    pExpression;
  TTypeName TypeName;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1;
} TCastExpressionType;

TCastExpressionType* TCastExpressionType_Create();
void TCastExpressionType_Delete(TCastExpressionType* p);


typedef struct
{
  EType Type  _defval(TUnaryExpressionOperator_ID);
  Tokens token;
  TExpression*_auto   pExpressionRight;
  TTypeName TypeName;
  TScannerItemList ClueList0;
  TScannerItemList ClueList1; //sizeof (
  TScannerItemList ClueList2; //sizeof ( )
} TUnaryExpressionOperator;


TUnaryExpressionOperator* TUnaryExpressionOperator_Create();
void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator* p);

struct _union(TPrimaryExpressionLiteral |
  TPrimaryExpressionValue |
  TBinaryExpression |
  TUnaryExpressionOperator |
  TPostfixExpressionCore |
  TPostfixExpressionCore |
  TCastExpressionType |
  TPrimaryExpressionLambda) TExpression
{
  EType Type;
};

typedef struct TExpression TExpression;
void TExpression_Delete(TExpression* p);


CAST(TExpression, TPrimaryExpressionLiteral)
CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)


typedef struct TPrimaryExpressionLambda
{
  EType Type _defval(TPrimaryExpressionLambda_ID);

  TCompoundStatement* pCompoundStatement;
  TParameterTypeList * _auto pParameterTypeListOpt;
  TScannerItemList ClueList0; //[
  TScannerItemList ClueList1; //]
  TScannerItemList ClueList2; //(
  TScannerItemList ClueList3; //)
} TPrimaryExpressionLambda;

TPrimaryExpressionLambda* TPrimaryExpressionLambda_Create();
void TPrimaryExpressionLambda_Delete(TPrimaryExpressionLambda* p);


void TDeclarations_Destroy(TDeclarations* p) _default
{
  for (int i = 0; i < p->Size; i++)
  {
    TAnyDeclaration_Delete(p->pItems[i]);
  }
  free((void*)p->pItems);
}
void TDeclarations_Init(TDeclarations* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}
void TDeclarations_Reserve(TDeclarations* p, int n) _default
{
  if (n > p->Capacity)
  {
    TAnyDeclaration** pnew = p->pItems;
    pnew = (TAnyDeclaration**)realloc(pnew, n * sizeof(TAnyDeclaration*));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = n;
    }
  }
}
void TDeclarations_PushBack(TDeclarations* p, TDeclaration* pItem) _default
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

TGroupDeclaration* TGroupDeclaration_Create() _default
{
  TGroupDeclaration *p = (TGroupDeclaration*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TGroupDeclaration_ID;
    TDeclarations_Init(&p->Declarations);
    String_Init(&p->Identifier);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
  }
  return p;
}
void TGroupDeclaration_Delete(TGroupDeclaration* p) _default
{
  if (p != NULL)
  {
    TDeclarations_Destroy(&p->Declarations);
    String_Destroy(&p->Identifier);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}

void TStructDeclarationList_Destroy(TStructDeclarationList* p) _default
{
  for (int i = 0; i < p->Size; i++)
  {
    TAnyStructDeclaration_Delete(p->pItems[i]);
  }
  free((void*)p->pItems);
}
void TStructDeclarationList_Init(TStructDeclarationList* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}

void TStructDeclarationList_Reserve(TStructDeclarationList* p, int n) _default
{
  if (n > p->Capacity)
  {
    TAnyStructDeclaration** pnew = p->pItems;
    pnew = (TAnyStructDeclaration**)realloc(pnew, n * sizeof(TAnyStructDeclaration*));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = n;
    }
  }
}


void TStructDeclarationList_PushBack(TStructDeclarationList* p, TAnyStructDeclaration* pItem) _default
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

void TBlockItemList_Init(TBlockItemList* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}

void TBlockItemList_Destroy(TBlockItemList* p) _default
{
  for (int i = 0; i < p->Size; i++)
  {
    TBlockItem_Delete(p->pItems[i]);
  }
  free((void*)p->pItems);
}
void TBlockItemList_Reserve(TBlockItemList* p, int n) _default
{
  if (n > p->Capacity)
  {
    TBlockItem** pnew = p->pItems;
    pnew = (TBlockItem**)realloc(pnew, n * sizeof(TBlockItem*));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = n;
    }
  }
}
void TBlockItemList_PushBack(TBlockItemList* p, TBlockItem* pItem)_default
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

TCompoundStatement* TCompoundStatement_Create() _default
{
  TCompoundStatement *p = (TCompoundStatement*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TCompoundStatement_ID;
    TBlockItemList_Init(&p->BlockItemList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
  }
  return p;
}


void TCompoundStatement_Delete(TCompoundStatement* p) _default
{
  if (p != NULL)
  {
    TBlockItemList_Destroy(&p->BlockItemList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    free((void*)p);
  }
}

TLabeledStatement* TLabeledStatement_Create(void) _default
{
  TLabeledStatement *p = (TLabeledStatement*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TLabeledStatement_ID;
    p->pStatementOpt = NULL;
    p->pExpression = NULL;
    String_Init(&p->Identifier);
    p->token = TK_NONE;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
  }
  return p;
}

void TLabeledStatement_Delete(TLabeledStatement* p)_default
{
  if (p != NULL)
  {
    TStatement_Delete(p->pStatementOpt);
    TExpression_Delete(p->pExpression);
    String_Destroy(&p->Identifier);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    free((void*)p);
  }
}
TForStatement* TForStatement_Create(void)_default
{
  TForStatement *p = (TForStatement*)malloc(sizeof * p);
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

void TForStatement_Delete(TForStatement* p)_default
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
    free((void*)p);
  }
}

TWhileStatement* TWhileStatement_Create(void) _default
{
  TWhileStatement *p = (TWhileStatement*)malloc(sizeof * p);
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

void TWhileStatement_Delete(TWhileStatement* p)_default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpression);
    TStatement_Delete(p->pStatement);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}

TDoStatement* TDoStatement_Create(void) _default
{
  TDoStatement *p = (TDoStatement*)malloc(sizeof * p);
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

void TDoStatement_Delete(TDoStatement* p) _default
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
    free((void*)p);
  }
}


TExpressionStatement* TExpressionStatement_Create(void) _default
{
  TExpressionStatement *p = (TExpressionStatement*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TExpressionStatement_ID;
    p->pExpression = NULL;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}

void TExpressionStatement_Delete(TExpressionStatement* p)_default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    free((void*)p);
  }
}

TJumpStatement* TJumpStatement_Create(void) _default
{
  TJumpStatement *p = (TJumpStatement*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TJumpStatement_ID;
    p->token = TK_NONE;
    String_Init(&p->Identifier);
    p->pExpression = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
  }
  return p;
}

void TJumpStatement_Delete(TJumpStatement* p) _default
{
  if (p != NULL)
  {
    String_Destroy(&p->Identifier);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}




TAsmStatement* TAsmStatement_Create(void) _default
{
  TAsmStatement *p = (TAsmStatement*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TAsmStatement_ID;
    TScannerItemList_Init(&p->ClueList);
  }
  return p;
}

void TAsmStatement_Delete(TAsmStatement* p) _default
{
  if (p != NULL)
  {
    TScannerItemList_Destroy(&p->ClueList);
    free((void*)p);
  }
}

TSwitchStatement* TSwitchStatement_Create(void) _default
{
  TSwitchStatement *p = (TSwitchStatement*)malloc(sizeof * p);
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

void TSwitchStatement_Delete(TSwitchStatement* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pConditionExpression);
    TStatement_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}


TIfStatement* TIfStatement_Create(void) _default
{
  TIfStatement *p = (TIfStatement*)malloc(sizeof * p);
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

void TIfStatement_Delete(TIfStatement* p) _default
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
    free((void*)p);
  }
}

void TStatement_Delete(TStatement* p) _default
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



void TBlockItem_Delete(TBlockItem* p) _default
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

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue* p) _default
{
  p->Type = TPrimaryExpressionValue_ID;
  p->token = TK_NONE;
  String_Init(&p->lexeme);
  p->pExpressionOpt = NULL;
  TScannerItemList_Init(&p->ClueList0);
  TScannerItemList_Init(&p->ClueList1);
}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p) _default
{
  String_Destroy(&p->lexeme);
  TExpression_Delete(p->pExpressionOpt);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

TPrimaryExpressionValue* TPrimaryExpressionValue_Create() _default
{
  TPrimaryExpressionValue *p = (TPrimaryExpressionValue*)malloc(sizeof * p);
  if (p != NULL)
  {
    TPrimaryExpressionValue_Init(p);
  }
  return p;
}

void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue* p) _default
{
  if (p != NULL)
  {
    TPrimaryExpressionValue_Destroy(p);
    free((void*)p);
  }
}

TPrimaryExpressionLambda* TPrimaryExpressionLambda_Create() _default
{
  TPrimaryExpressionLambda *p = (TPrimaryExpressionLambda*)malloc(sizeof * p);
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

void TPrimaryExpressionLambda_Delete(TPrimaryExpressionLambda* p) _default
{
  if (p != NULL)
  {
    TParameterTypeList_Delete(p->pParameterTypeListOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
    free((void*)p);
  }
}

void TPostfixExpressionCore_Delete(TPostfixExpressionCore* p) _default
{
  if (p != NULL)
  {
    String_Destroy(&p->lexeme);
    TExpression_Delete(p->pExpressionLeft);
    TExpression_Delete(p->pExpressionRight);
    TPostfixExpressionCore_Delete(p->pNext);
    TInitializerList_Destroy(&p->InitializerList);
    String_Destroy(&p->Identifier);
    TTypeName_Delete(p->pTypeName);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
    TScannerItemList_Destroy(&p->ClueList4);
    free((void*)p);
  }
}

TBinaryExpression* TBinaryExpression_Create(void) _default
{
  TBinaryExpression *p = (TBinaryExpression*)malloc(sizeof * p);
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

void TBinaryExpression_Delete(TBinaryExpression* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpressionLeft);
    TExpression_Delete(p->pExpressionRight);
    TScannerItemList_Destroy(&p->ClueList0);
    free((void*)p);
  }
}


void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpressionRight);
    TTypeName_Destroy(&p->TypeName);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}


void TCastExpressionType_Delete(TCastExpressionType* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpression);
    TTypeName_Destroy(&p->TypeName);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    free((void*)p);
  }
}

TTernaryExpression* TTernaryExpression_Create(void) _default
{
  TTernaryExpression *p = (TTernaryExpression*)malloc(sizeof * p);
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

void TTernaryExpression_Delete(TTernaryExpression* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pExpressionLeft);
    TExpression_Delete(p->pExpressionMiddle);
    TExpression_Delete(p->pExpressionRight);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    free((void*)p);
  }
}

void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem *p) _default
{
  if (p != NULL)
  {
    TPrimaryExpressionLiteralItem_Delete(p->pNext);
    String_Destroy(&p->lexeme);
    TScannerItemList_Destroy(&p->ClueList0);
    free((void*)p);
  }
}
TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create() _default
{
  TPrimaryExpressionLiteralItem *p = (TPrimaryExpressionLiteralItem*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->pNext = NULL;
    String_Init(&p->lexeme);
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}

TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create() _default
{
  TPrimaryExpressionLiteral *p = (TPrimaryExpressionLiteral*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TPrimaryExpressionLiteral_ID;
    TPrimaryExpressionLiteralItemList_Init(&p->List);
  }
  return p;
}


void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral* p) _default
{
  if (p != NULL)
  {
    TPrimaryExpressionLiteralItemList_Destroy(&p->List);
    free((void*)p);
  }
}

void TExpression_Delete(TExpression* p) _default
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
    default:
      break;
    }
  }
}


TEofDeclaration* TEofDeclaration_Create() _default
{
  TEofDeclaration *p = (TEofDeclaration*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TEofDeclaration_ID;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}


void TEofDeclaration_Delete(TEofDeclaration* p) _default
{
  if (p != NULL)
  {
    TScannerItemList_Destroy(&p->ClueList0);
    free((void*)p);
  }
}



TStaticAssertDeclaration* TStaticAssertDeclaration_Create() _default
{
  TStaticAssertDeclaration *p = (TStaticAssertDeclaration*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TStaticAssertDeclaration_ID;
    p->pConstantExpression = NULL;
    String_Init(&p->Text);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
    TScannerItemList_Init(&p->ClueList3);
    TScannerItemList_Init(&p->ClueList4);
    TScannerItemList_Init(&p->ClueList5);
  }
  return p;
}

void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration* p) _default
{
  if (p != NULL)
  {
    TExpression_Delete(p->pConstantExpression);
    String_Destroy(&p->Text);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
    TScannerItemList_Destroy(&p->ClueList4);
    TScannerItemList_Destroy(&p->ClueList5);
    free((void*)p);
  }
}

TEnumerator* TEnumerator_Create(void) _default
{
  TEnumerator *p = (TEnumerator*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->pNext = NULL;
    String_Init(&p->Name);
    p->pExpression = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
    p->bHasComma = false;
  }
  return p;
}

void TEnumerator_Delete(TEnumerator* p) _default
{
  if (p != NULL)
  {
    TEnumerator_Delete(p->pNext);
    String_Destroy(&p->Name);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}

void TEnumeratorList_Init(TEnumeratorList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TEnumeratorList_Destroy(TEnumeratorList* p) _default
{
  TEnumerator_Delete(p->pHead);
}

TEnumSpecifier* TEnumSpecifier_Create(void) _default
{
  TEnumSpecifier *p = (TEnumSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TEnumSpecifier_ID;
    String_Init(&p->Name);
    TEnumeratorList_Init(&p->EnumeratorList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
    TScannerItemList_Init(&p->ClueList3);
  }
  return p;
}

void TEnumSpecifier_Delete(TEnumSpecifier* p) _default
{
  if (p != NULL)
  {
    String_Destroy(&p->Name);
    TEnumeratorList_Destroy(&p->EnumeratorList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
    free((void*)p);
  }
}



TUnionSetItem* TUnionSetItem_Create() _default
{
  TUnionSetItem *p = (TUnionSetItem*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->pNext = NULL;
    p->Token = TK_NONE;
    p->TokenFollow = TK_NONE;
    String_Init(&p->Name);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
  }
  return p;
}
void TUnionSetItem_Delete(TUnionSetItem* p) _default
{
  if (p != NULL)
  {
    TUnionSetItem_Delete(p->pNext);
    String_Destroy(&p->Name);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}

void TUnionSet_Init(TUnionSet* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
  TScannerItemList_Init(&p->ClueList0);
  TScannerItemList_Init(&p->ClueList1);
  TScannerItemList_Init(&p->ClueList2);
}

void TUnionSet_Destroy(TUnionSet* p) _default
{
  TUnionSetItem_Delete(p->pHead);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
}


void TUnionSet_PushBack(TUnionSet* pList, TUnionSetItem* pItem)
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




TStructUnionSpecifier* TStructUnionSpecifier_Create() _default
{
  TStructUnionSpecifier *p = (TStructUnionSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TStructUnionSpecifier_ID;
    TStructDeclarationList_Init(&p->StructDeclarationList);
    String_Init(&p->Name);
    p->Token = TK_NONE;
    p->Token2 = TK_NONE;
    TUnionSet_Init(&p->UnionSet);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
    TScannerItemList_Init(&p->ClueList3);
  }
  return p;
}
void TStructUnionSpecifier_Delete(TStructUnionSpecifier* p) _default
{
  if (p != NULL)
  {
    TStructDeclarationList_Destroy(&p->StructDeclarationList);
    String_Destroy(&p->Name);
    TUnionSet_Destroy(&p->UnionSet);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
    free((void*)p);
  }
}


TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void) _default
{
  TSingleTypeSpecifier *p = (TSingleTypeSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TSingleTypeSpecifier_ID;
    p->Token = TK_NONE;
    String_Init(&p->TypedefName);
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}
void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier* p) _default
{
  String_Destroy(&p->TypedefName);
  TScannerItemList_Destroy(&p->ClueList0);
}
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier* p) _default
{
  if (p != NULL)
  {
    TSingleTypeSpecifier_Destroy(p);
    free((void*)p);
  }
}


const char* TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier* p)
{
  const char* result = NULL;
  if (p->Token == TK_IDENTIFIER)
  {
    result = p->TypedefName;
  }
  return result;
}

void TTypeSpecifier_Delete(TTypeSpecifier* p) _default
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


void TDeclarator_Init(TDeclarator* p) _default
{
  p->PointerList.pHead = NULL;
  p->PointerList.pTail = NULL;
  p->pDirectDeclarator = NULL;
  TScannerItemList_Init(&p->ClueList);
}

TDeclarator* TDeclarator_Create() _default
{
  TDeclarator *p = (TDeclarator*)malloc(sizeof * p);
  if (p != NULL)
  {
    TDeclarator_Init(p);
  }
  return p;
}

void TDeclarator_Destroy(TDeclarator* p) _default
{
  TPointerList_Destroy(&p->PointerList);
  TDirectDeclarator_Delete(p->pDirectDeclarator);
  TScannerItemList_Destroy(&p->ClueList);
}

void TDeclarator_Delete(TDeclarator* p) _default
{
  if (p != NULL)
  {
    TDeclarator_Destroy(p);
    free((void*)p);
  }
}

TInitDeclarator* TInitDeclarator_Create() _default
{
  TInitDeclarator *p = (TInitDeclarator*)malloc(sizeof * p);
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

void TInitDeclarator_Destroy(TInitDeclarator* p) _default
{
  TDeclarator_Delete(p->pDeclarator);
  TInitializer_Delete(p->pInitializer);
  TInitDeclarator_Delete(p->pNext);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TInitDeclarator_Delete(TInitDeclarator* p) _default
{
  if (p != NULL)
  {
    TInitDeclarator_Destroy(p);
    free((void*)p);
  }
}

void TParameterTypeList_Init(TParameterTypeList* p) _default
{
  TParameterList_Init(&p->ParameterList);
  TScannerItemList_Init(&p->ClueList0);
  TScannerItemList_Init(&p->ClueList1);
  p->bVariadicArgs = false;
}
void TParameterTypeList_Destroy(TParameterTypeList* p) _default
{
  TParameterList_Destroy(&p->ParameterList);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

TParameterTypeList* TParameterTypeList_Create() _default
{
  TParameterTypeList *p = (TParameterTypeList*)malloc(sizeof * p);
  if (p != NULL)
  {
    TParameterTypeList_Init(p);
  }
  return p;
}
void TParameterTypeList_Delete(TParameterTypeList* p) _default
{
  if (p != NULL)
  {
    TParameterTypeList_Destroy(p);
    free((void*)p);
  }
}

const char* TParameterTypeList_GetFirstParameterName(TParameterTypeList* p)
{
  const char* name = "";
  if (p->ParameterList.pHead)
  {
    name = TDeclarator_GetName(&p->ParameterList.pHead->Declarator);
  }
  return name;
}

bool TParameterTypeList_HasNamedArgs(TParameterTypeList* p)
{
  bool result = false;
  if (p != NULL)
  {
    ForEachListItem(TParameter, pParameter, &p->ParameterList)
    {
      const char* parameterName = TParameter_GetName(pParameter);
      if (parameterName != NULL)
      {
        result = true;
        break;
      }
    }
  }
  return result;
}



void TParameterTypeList_GetArgsString(TParameterTypeList* p, StrBuilder* sb)
{
  if (p != NULL)
  {
    int index = 0;
    ForEachListItem(TParameter, pParameter, &p->ParameterList)
    {
      const char* parameterName = TParameter_GetName(pParameter);
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

TParameter* TParameterTypeList_GetParameterByIndex(TParameterTypeList* p, int index)
{
  TParameter* pParameterResult = NULL;
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

TParameter* TParameterTypeList_FindParameterByName(TParameterTypeList* p, const char* name)
{
  TParameter* pParameterResult = NULL;
  bool bFound = false;
  if (name)
  {
    ForEachListItem(TParameter, pParameter, &p->ParameterList)
    {
      //F(void) neste caso nao tem nome
      const char* parameterName = TParameter_GetName(pParameter);
      if (parameterName && strcmp(parameterName, name) == 0)
      {
        pParameterResult = pParameter;
        break;
      }
    }
  }
  return pParameterResult;
}

const char* TParameterTypeList_GetSecondParameterName(TParameterTypeList* p)
{
  const char* name = "";
  if (p->ParameterList.pHead &&
    p->ParameterList.pHead->pNext)
  {
    name = TDeclarator_GetName(&p->ParameterList.pHead->pNext->Declarator);
  }
  return name;
}

void TDirectDeclarator_Destroy(TDirectDeclarator* p) _default
{
  String_Destroy(&p->Identifier);
  TDeclarator_Delete(p->pDeclarator);
  TDirectDeclarator_Delete(p->pDirectDeclarator);
  TParameterTypeList_Destroy(&p->Parameters);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
}

void TDirectDeclarator_Delete(TDirectDeclarator* p) _default
{
  if (p != NULL)
  {
    TDirectDeclarator_Destroy(p);
    free((void*)p);
  }
}

TDeclarationSpecifier* TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList* p)
{
  TDeclarationSpecifier* pSpecifier = NULL;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
    if (pSpecifierQualifier->Type == TSingleTypeSpecifier_ID ||
      pSpecifierQualifier->Type == TStructUnionSpecifier_ID ||
      pSpecifierQualifier->Type == TEnumSpecifier_ID)
    {
      pSpecifier = pSpecifierQualifier;
      break;
    }
  }
  return pSpecifier;
}

const char* TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList* p)
{
  const char* typedefName = NULL;

  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];


    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
    if (pSingleTypeSpecifier &&
      pSingleTypeSpecifier->Token == TK_IDENTIFIER)
    {
      typedefName = pSingleTypeSpecifier->TypedefName;
      break;
    }
  }
  return typedefName;
}

bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList* p)
{
  bool bResult = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
    TStorageSpecifier* pStorageSpecifier =
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

bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList* p)
{
  bool bResult = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];

    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
    if (pSingleTypeSpecifier &&
      pSingleTypeSpecifier->Token == TK_CHAR)
    {
      bResult = true;
      break;
    }
  }
  return bResult;
}


bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList* p)
{
  bool bResult = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
    if (pSingleTypeSpecifier &&
      (pSingleTypeSpecifier->Token == TK_INT ||
        pSingleTypeSpecifier->Token == TK_SHORT ||
        pSingleTypeSpecifier->Token == TK_SIGNED ||
        pSingleTypeSpecifier->Token == TK_UNSIGNED ||
        pSingleTypeSpecifier->Token == TK__INT8 ||
        pSingleTypeSpecifier->Token == TK__INT16 ||
        pSingleTypeSpecifier->Token == TK__INT32 ||
        pSingleTypeSpecifier->Token == TK__INT64 ||
        pSingleTypeSpecifier->Token == TK__WCHAR_T)
      )
    {
      bResult = true;
      break;
    }
  }
  return bResult;
}


bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList* p)
{
  bool bResult = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
    if (pSingleTypeSpecifier &&
      (pSingleTypeSpecifier->Token == TK_DOUBLE ||
        pSingleTypeSpecifier->Token == TK_FLOAT))
    {
      bResult = true;
      break;
    }
  }
  return bResult;
}

bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList* p)
{
  bool bResult = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);

    if (pSingleTypeSpecifier &&
      pSingleTypeSpecifier->Token == TK__BOOL)
    {
      bResult = true;
      break;
    }
  }
  return bResult;
}

const char* TDeclarator_GetName(TDeclarator*   p)
{
  if (p == NULL)
  {
    return NULL;
  }
  TDirectDeclarator* pDirectDeclarator = p->pDirectDeclarator;
  while (pDirectDeclarator != NULL)
  {
    if (pDirectDeclarator->Identifier != NULL &&
      pDirectDeclarator->Identifier[0] != 0)
    {
      return pDirectDeclarator->Identifier;
    }

    if (pDirectDeclarator->pDeclarator)
    {
      const char* name =
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

const char* TInitDeclarator_FindName(TInitDeclarator* p)
{
  ASSERT(p->pDeclarator != NULL);
  return TDeclarator_GetName(p->pDeclarator);
}



TAlignmentSpecifier* TAlignmentSpecifier_Create(void) _default
{
  TAlignmentSpecifier *p = (TAlignmentSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TAlignmentSpecifier_ID;
    String_Init(&p->TypeName);
  }
  return p;
}
void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p) _default
{
  String_Destroy(&p->TypeName);
}

void TAlignmentSpecifier_Delete(TAlignmentSpecifier* p) _default
{
  if (p != NULL)
  {
    TAlignmentSpecifier_Destroy(p);
    free((void*)p);
  }
}


TStructDeclaration* TStructDeclaration_Create() _default
{
  TStructDeclaration *p = (TStructDeclaration*)malloc(sizeof * p);
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


void TStructDeclaratorList_Destroy(TStructDeclaratorList* p) _default
{
  TInitDeclarator_Delete(p->pHead);
}

void TStructDeclaratorList_Init(TStructDeclaratorList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TStructDeclaratorList_Add(TStructDeclaratorList* pList, TInitDeclarator* pItem)
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

void TStructDeclaration_Destroy(TStructDeclaration* p) _default
{
  TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
  TStructDeclaratorList_Destroy(&p->DeclaratorList);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TStructDeclaration_Delete(TStructDeclaration* p) _default
{
  if (p != NULL)
  {
    TStructDeclaration_Destroy(p);
    free((void*)p);
  }
}


void TAnyStructDeclaration_Delete(TAnyStructDeclaration* p) _default
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

bool TPointerList_IsAutoPointer(TPointerList* pPointerlist)
{
  bool bIsPointer = false;
  bool bIsAuto = false;
  if (pPointerlist)
  {
    bIsPointer = (pPointerlist->pHead != NULL);

    //ForEachListItem(TPointer, pItem, pPointerlist)
    TPointer* pItem = pPointerlist->pHead;
    //for (T * var = (list)->pHead; var != NULL; var = var->pNext)
    while (pItem)
    {
      for (int i = 0; i < pItem->Qualifier.Size; i++)
      {
        TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
        if (pQualifier->Token == TK__AUTO ||
          pQualifier->Token == TK_OWN_QUALIFIER)
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

void TPointerList_Destroy(TPointerList* p) _default
{
  TPointer_Delete(p->pHead);
}

TPointer* TPointer_Create(void) _default
{
  TPointer *p = (TPointer*)malloc(sizeof * p);
  if (p != NULL)
  {
    TTypeQualifierList_Init(&p->Qualifier);
    p->pNext = NULL;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}
void TPointer_Destroy(TPointer* p) _default
{
  TTypeQualifierList_Destroy(&p->Qualifier);
  TPointer_Delete(p->pNext);
  TScannerItemList_Destroy(&p->ClueList0);
}

void TPointerList_PushBack(TPointerList* pList, TPointer* pItem)
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

void TPointer_Delete(TPointer* p) _default
{
  if (p != NULL)
  {
    TPointer_Destroy(p);
    free((void*)p);
  }
}

void TPointerList_Printf(TPointerList* p)
{
  ForEachListItem(TPointer, pItem, p)
  {
    printf("*");

    for (int i = 0; i < pItem->Qualifier.Size; i++)
    {
      if (i > 0)
        printf(" ");
      TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
      printf("%s", TokenToString(pQualifier->Token));

      if (pQualifier->Token == TK__SIZE)
      {
        printf("(%s)", pQualifier->SizeIdentifier);
      }
    }
  }
  printf("\n");
}

void TPointerList_Swap(TPointerList* a, TPointerList* b)
{
  TPointerList t = *a;
  *a = *b;
  *b = t;
}

void TPointer_Copy(TPointer* dest, TPointer* src)
{
  TTypeQualifierList_Copy(&dest->Qualifier, &src->Qualifier);
}

bool TPointerList_IsPointer(TPointerList* pPointerlist)
{
  return pPointerlist->pHead != NULL;
}


const char * TPointerList_GetSize(TPointerList* pPointerlist)
{
  //Esta definicao esta estranha..tem que pegar o size de 1 cara so

  const char* pszResult = NULL;

  if (pPointerlist)
  {
    ForEachListItem(TPointer, pItem, pPointerlist)
    {
      for (int i = 0; i < pItem->Qualifier.Size; i++)
      {
        TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];

        if (pQualifier->Token == TK__SIZE)
        {
          pszResult = pQualifier->SizeIdentifier;
          break;
        }
      }
    }
  }
  return pszResult;
}

bool TPointerList_IsPointerN(TPointerList* pPointerlist, int n)
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

bool TPointerList_IsPointerToObject(TPointerList* pPointerlist)
{
  bool bResult = false;
  TPointer* pPointer = pPointerlist->pHead;
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


bool TPointerList_IsAutoPointerToObject(TPointerList* pPointerlist)
{
  bool bResult = false;
  TPointer* pPointer = pPointerlist->pHead;
  if (pPointer != NULL)
  {
    if (pPointer->Qualifier.Size == 1 &&
      pPointer->Qualifier.Data[0]->Token == TK__AUTO)
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


bool TPointerList_IsAutoPointerSizeToObject(TPointerList* pPointerlist)
{
  bool bResult = false;
  TPointer* pPointer = pPointerlist->pHead;
  if (pPointer != NULL)
  {
    if (pPointer->Qualifier.Size == 2 &&
      pPointer->pNext == NULL)
    {
      bResult = (pPointer->Qualifier.Data[0]->Token == TK__AUTO &&
        pPointer->Qualifier.Data[1]->Token == TK__SIZE) ||
        (pPointer->Qualifier.Data[0]->Token == TK__SIZE &&
          pPointer->Qualifier.Data[0]->Token == TK__AUTO);
    }
  }


  return bResult;
}

bool TPointerList_IsAutoPointerToPointer(TPointerList* pPointerlist)
{
  bool bResult = false;
  TPointer* pPointer = pPointerlist->pHead;
  if (pPointer != NULL)
  {
    if (pPointer->Qualifier.Size == 1 &&
      pPointer->Qualifier.Data[0]->Token == TK__AUTO)
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


bool TPointerList_IsAutoPointerToAutoPointer(TPointerList* pPointerlist)
{
  bool bResult = false;
  TPointer* pPointer = pPointerlist->pHead;
  if (pPointer != NULL)
  {
    if (pPointer->Qualifier.Size == 1 &&
      pPointer->Qualifier.Data[0]->Token == TK__AUTO)
    {
      pPointer = pPointer->pNext;
      if (pPointer != NULL)
      {
        if (pPointer->Qualifier.Size == 1 &&
          pPointer->Qualifier.Data[0]->Token == TK__AUTO)
        {
          bResult = true;
        }
        else if (pPointer->Qualifier.Size == 2)
        {
          //auto _size()
          // _size() auto
          bResult = pPointer->Qualifier.Data[0]->Token == TK__AUTO ||
            pPointer->Qualifier.Data[1]->Token == TK__AUTO;
        }
      }
    }
  }

  return bResult;
}



void TTypeQualifierList_Destroy(TTypeQualifierList* p)  /*custom*/
{
  for (int i = 0; i < p->Size; i++)
  {
    TTypeQualifier_Delete(p->Data[i]);
  }
}


void TTypeQualifierList_Init(TTypeQualifierList* p)
{
  p->Data[0] = NULL;
  p->Size = 0;
}

void TTypeQualifierList_Copy(TTypeQualifierList* dest, TTypeQualifierList* src)
{
  TTypeQualifierList_Destroy(dest);
  TTypeQualifierList_Init(dest);

  for (int i = 0; i < src->Size; i++)
  {
    TTypeQualifier* pItem = TTypeQualifier_Create();
    TTypeQualifier_Copy(pItem, src->Data[i]);
    TTypeQualifierList_PushBack(dest, pItem);
  }
}

void TTypeQualifierList_PushBack(TTypeQualifierList* p, TTypeQualifier* pItem)
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

TTypeQualifier* TTypeQualifier_Create(void) _default
{
  TTypeQualifier *p = (TTypeQualifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TTypeQualifier_ID;
    String_Init(&p->SizeIdentifier);
    p->Token = TK_NONE;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}
void TTypeQualifier_Destroy(TTypeQualifier* p) _default
{
  String_Destroy(&p->SizeIdentifier);
  TScannerItemList_Destroy(&p->ClueList0);
}
void TTypeQualifier_Delete(TTypeQualifier* p) _default
{
  if (p != NULL)
  {
    TTypeQualifier_Destroy(p);
    free((void*)p);
  }
}

void TTypeQualifier_Copy(TTypeQualifier* dest, TTypeQualifier* src)
{
  String_Set(&dest->SizeIdentifier, src->SizeIdentifier);
  dest->Token = src->Token;
  //dest->ClueList0 nao vamos copiar
  //dest->Type nao precisa copiar
}


TStorageSpecifier* TStorageSpecifier_Create(void) _default
{
  TStorageSpecifier *p = (TStorageSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TStorageSpecifier_ID;
    p->Token = TK_NONE;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}
void TStorageSpecifier_Destroy(TStorageSpecifier* p) _default
{
  TScannerItemList_Destroy(&p->ClueList0);
}
void TStorageSpecifier_Delete(TStorageSpecifier* p) _default
{
  if (p != NULL)
  {
    TStorageSpecifier_Destroy(p);
    free((void*)p);
  }
}


void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier* p) _default
{
  if (p != NULL)
  {
    TTypeName_Destroy(&p->TypeName);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    free((void*)p);
  }
}

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers) _default
{
  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TSpecifierQualifier_Delete(pDeclarationSpecifiers->pData[i]);
  }
  free((void*)pDeclarationSpecifiers->pData);
}


void TSpecifierQualifierList_Reserve(TSpecifierQualifierList* p, int n) _default
{
  if (n > p->Capacity)
  {
    TSpecifierQualifier** pnew = p->pData;
    pnew = (TSpecifierQualifier**)realloc(pnew, n * sizeof(TSpecifierQualifier*));
    if (pnew)
    {
      p->pData = pnew;
      p->Capacity = n;
    }
  }
}

void TSpecifierQualifierList_PushBack(TSpecifierQualifierList* p, TSpecifierQualifier* pItem) _default
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




bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList* p, Tokens token, const char* lexeme)
{
  bool bResult = false;

  bool bStruct = false;
  bool bEnum = false;

  bool bTypeDef = false;
  bool bInt = false;
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pSpecifier = p->pData[i];
    switch (pSpecifier->Type)
    {
      CASE(TSingleTypeSpecifier) :
      {     TSingleTypeSpecifier* pTSingleTypeSpecifier =
        (TSingleTypeSpecifier*)pSpecifier;
      switch (pTSingleTypeSpecifier->Token)
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
        ASSERT(false);
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
      ASSERT(false);
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

bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers* pDeclarationSpecifiers,
  Tokens token,
  const char* lexeme)
{
  bool bResult = false;
  bool bStruct = false;
  bool bEnum = false;


  bool bTypeDef = false;
  bool bInt = false;

  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier* pSpecifier = pDeclarationSpecifiers->pData[i];

    switch (pSpecifier->Type)
    {
      CASE(TSingleTypeSpecifier) :
      {     TSingleTypeSpecifier* pTSingleTypeSpecifier =
        (TSingleTypeSpecifier*)pSpecifier;
      switch (pTSingleTypeSpecifier->Token)
      {
      case TK_INT:
        bInt = true;
        break;
      case TK_DOUBLE:
      case TK_IDENTIFIER:
        bTypeDef = true;
        break;
      default:
        ASSERT(false);
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
      ASSERT(false);
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

const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
  if (pDeclarationSpecifiers == NULL)
  {
    return NULL;
  }
  const char* typeName = NULL;


  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

    TSingleTypeSpecifier* pSingleTypeSpecifier =
      TDeclarationSpecifier_As_TSingleTypeSpecifier(pItem);
    if (pSingleTypeSpecifier != NULL)
    {
      if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
      {
        typeName = pSingleTypeSpecifier->TypedefName;
        break;
      }
    }
  }
  return typeName;
}

void TSpecifierQualifier_Delete(TSpecifierQualifier* pItem) _default
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

void TDeclarationSpecifier_Delete(TDeclarationSpecifier* pItem) _default
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

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers* pDeclarationSpecifiers) _default
{
  pDeclarationSpecifiers->pData = NULL;
  pDeclarationSpecifiers->Size = 0;
  pDeclarationSpecifiers->Capacity = 0;
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers) _default
{
  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier_Delete(pDeclarationSpecifiers->pData[i]);
  }
  free((void*)pDeclarationSpecifiers->pData);
}


void TDeclarationSpecifiers_Reserve(TDeclarationSpecifiers* p, int n) _default
{
  if (n > p->Capacity)
  {
    TDeclarationSpecifier** pnew = p->pData;
    pnew = (TDeclarationSpecifier**)realloc(pnew, n * sizeof(TDeclarationSpecifier*));
    if (pnew)
    {
      p->pData = pnew;
      p->Capacity = n;
    }
  }
}

void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers* p, TDeclarationSpecifier* pItem) _default
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


TDeclarator* TDeclaration_FindDeclarator(TDeclaration*  p, const char* name)
{
  if (p == NULL)
  {
    return NULL;
  }
  TDeclarator*  pResult = NULL;

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

TFunctionSpecifier* TFunctionSpecifier_Create(void) _default
{
  TFunctionSpecifier *p = (TFunctionSpecifier*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TFunctionSpecifier_ID;
    p->Token = TK_NONE;
    TScannerItemList_Init(&p->ClueList0);
  }
  return p;
}
void TFunctionSpecifier_Destroy(TFunctionSpecifier* p) _default
{
  TScannerItemList_Destroy(&p->ClueList0);
}
void TFunctionSpecifier_Delete(TFunctionSpecifier* p) _default
{
  if (p != NULL)
  {
    TFunctionSpecifier_Destroy(p);
    free((void*)p);
  }
}



bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p)
{
  bool bIsStructOrUnion = false;
  for (int i = 0; i < p->Specifiers.Size; i++)
  {
    TDeclarationSpecifier* pItem = p->Specifiers.pData[i];
    if (TDeclarationSpecifier_As_TStructUnionSpecifier(pItem))
    {
      bIsStructOrUnion = true;
      break;
    }

  }
  return bIsStructOrUnion;
}

void TInitDeclaratorList_Init(TInitDeclaratorList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TInitDeclaratorList_Destroy(TInitDeclaratorList* p) _default
{
  TInitDeclarator_Delete(p->pHead);
}



void TDeclaration_Delete(TDeclaration* p) _default
{
  if (p != NULL)
  {
    TDeclarationSpecifiers_Destroy(&p->Specifiers);
    TInitDeclaratorList_Destroy(&p->InitDeclaratorList);
    TCompoundStatement_Delete(p->pCompoundStatementOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    free((void*)p);
  }
}
TDeclaration* TDeclaration_Create() _default
{
  TDeclaration *p = (TDeclaration*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TDeclaration_ID;
    TDeclarationSpecifiers_Init(&p->Specifiers);
    TInitDeclaratorList_Init(&p->InitDeclaratorList);
    p->pCompoundStatementOpt = NULL;
    p->FileIndex = 0;
    p->Line = 0;
    TScannerItemList_Init(&p->ClueList0);
    p->bDefault = false;
    TScannerItemList_Init(&p->ClueList1);
  }
  return p;
}


void TParameter_Swap(TParameter* a, TParameter* b)
{
  TParameter temp = *a;
  *a = *b;
  *b = temp;
}

const char* TDeclarationSpecifier_GetTypedefName(TDeclarationSpecifiers* p)
{
  const char* typedefName = NULL;
  for (int i = 0; i < p->Size; i++)
  {
    TDeclarationSpecifier* pSpecifier = p->pData[i];
    TSingleTypeSpecifier *pSingleTypeSpecifier =
      TDeclarationSpecifier_As_TSingleTypeSpecifier(pSpecifier);
    if (pSingleTypeSpecifier &&
      pSingleTypeSpecifier->Token == TK_IDENTIFIER)
    {
      typedefName = pSingleTypeSpecifier->TypedefName;
    }
  }
  return typedefName;
}

const char* TParameter_GetName(TParameter* p)
{
  //F(void) neste caso nao tem nome
  return TDeclarator_GetName(&p->Declarator);
}

const char* TParameter_GetTypedefName(TParameter* p)
{
  return TDeclarationSpecifier_GetTypedefName(&p->Specifiers);
}

bool TDeclarator_IsDirectPointer(TDeclarator* p)
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

bool TParameter_IsDirectPointer(TParameter* p)
{
  return TDeclarator_IsDirectPointer(&p->Declarator);
}


TParameter* TParameter_Create() _default
{
  TParameter *p = (TParameter*)malloc(sizeof * p);
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

void TParameter_Delete(TParameter* p) _default
{
  if (p != NULL)
  {
    TParameter_Delete(p->pNext);
    TDeclarationSpecifiers_Destroy(&p->Specifiers);
    TDeclarator_Destroy(&p->Declarator);
    TScannerItemList_Destroy(&p->ClueList0);
    free((void*)p);
  }
}

void TParameterList_Init(TParameterList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TParameterList_Destroy(TParameterList* p) _default
{
  TParameter_Delete(p->pHead);
}


bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pAnyDeclaration)
{
  TDeclaration *  pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
  if (pDeclaration != NULL)
  {
    return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
  }

  return false;
}


bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
  bool bResult = false;
  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];
    switch (pItem->Type)
    {
      CASE(TStorageSpecifier) :
      {
        TStorageSpecifier* pStorageSpecifier =
          (TStorageSpecifier*)pItem;

        if (pStorageSpecifier->Token == TK_TYPEDEF)
        {
          bResult = true;
        }
      }

      break;
    default:
      ASSERT(false);
      break;
    }

    if (bResult)
    {
      break;
    }
  }
  return bResult;
}

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration)
{
  bool bResult = false;
  switch (pDeclaration->Type)
  {
  case TDeclaration_ID:
  {
    TDeclaration* p = (TDeclaration*)pDeclaration;
    bResult = TDeclarationSpecifiers_IsTypedef(&p->Specifiers);
  }
  break;
  default:
    ASSERT(false);
    break;
  }
  return bResult;
}

int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration)
{
  int result = -1;
  switch (pDeclaration->Type)
  {
  case TDeclaration_ID:
    result = ((TDeclaration*)pDeclaration)->FileIndex;
    break;
  case TStaticAssertDeclaration_ID:
    break;
  default:
    ASSERT(false);
    break;
  }
  return result;
}

void TAnyDeclaration_Delete(TAnyDeclaration* pDeclaration) _default
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

void TDesignation_Destroy(TDesignation* pDesignation) _default
{
  TDesignatorList_Destroy(&pDesignation->DesignatorList);
  TScannerItemList_Destroy(&pDesignation->ClueList0);
}

TDesignator* TDesignator_Create(void) _default
{
  TDesignator *p = (TDesignator*)malloc(sizeof * p);
  if (p != NULL)
  {
    String_Init(&p->Name);
    p->pExpression = NULL;
    p->pNext = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
  }
  return p;
}
void TDesignator_Destroy(TDesignator* p) _default
{
  String_Destroy(&p->Name);
  TExpression_Delete(p->pExpression);
  TDesignator_Delete(p->pNext);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}
void TDesignator_Delete(TDesignator* p) _default
{
  if (p != NULL)
  {
    TDesignator_Destroy(p);
    free((void*)p);
  }
}


TInitializerListType* TInitializerListType_Create(void) _default
{
  TInitializerListType *p = (TInitializerListType*)malloc(sizeof * p);
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
void TInitializerListType_Destroy(TInitializerListType* p) _default
{
  TInitializerList_Destroy(&p->InitializerList);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
}
void TInitializerListType_Delete(TInitializerListType* p) _default
{
  if (p != NULL)
  {
    TInitializerListType_Destroy(p);
    free((void*)p);
  }
}

void TInitializerList_Init(TInitializerList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TInitializerList_Destroy(TInitializerList* p) _default
{
  TInitializerListItem_Delete(p->pHead);
}

void TInitializer_Delete(TInitializer* p) _default
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
    default:
      break;
    }
  }
}


void TDesignatorList_Init(TDesignatorList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TDesignatorList_Destroy(TDesignatorList* p) _default
{
  TDesignator_Delete(p->pHead);
}

void TDesignatorList_PushBack(TDesignatorList* pList, TDesignator* pItem)
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

void TInitializerListItem_Destroy(TInitializerListItem* p) _default
{
  TDesignatorList_Destroy(&p->DesignatorList);
  TInitializer_Delete(p->pInitializer);
  TInitializerListItem_Delete(p->pNext);
  TScannerItemList_Destroy(&p->ClueList);
}

TInitializerListItem* TInitializerListItem_Create() _default
{
  TInitializerListItem *p = (TInitializerListItem*)malloc(sizeof * p);
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
void TInitializerListItem_Delete(TInitializerListItem* p) _default
{
  if (p != NULL)
  {
    TInitializerListItem_Destroy(p);
    free((void*)p);
  }
}




TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name)
{
  TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
  if (pt != NULL &&
    pt->Type == TDeclaration_ID)
  {
    return (TDeclaration*)pt;
  }
  return NULL;
  //return DeclarationsMap_FindDeclaration(&p->Symbols, name);
}

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name)
{
  TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
  if (pt != NULL &&
    pt->Type == TDeclaration_ID)
  {
    return (TDeclaration*)pt;
  }
  return NULL;
}



//Retorna a declaracao final do tipo entrando em cada typedef. 
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName)
{
  return SymbolMap_FindTypedefDeclarationTarget(&p->GlobalScope, typeName);
}


void TProgram_Init(TProgram* p) _default
{
  TDeclarations_Init(&p->Declarations);
  TFileArray_Init(&p->Files2);
  SymbolMap_Init(&p->GlobalScope);
  MacroMap_Init(&p->Defines);
  StrBuilder_Init(&p->sbPreDeclaration);
}


void TProgram_Destroy(TProgram * p) _default
{
  TDeclarations_Destroy(&p->Declarations);
  TFileArray_Destroy(&p->Files2);
  SymbolMap_Destroy(&p->GlobalScope);
  MacroMap_Destroy(&p->Defines);
  StrBuilder_Destroy(&p->sbPreDeclaration);
}



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
  int *pResult)
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
    ASSERT(false);
    break;
  case TK_ARROW:
    //fprintf(fp, "->%s", p->Identifier);
    //b = true;
    ASSERT(false);
    break;

  case TK_LEFT_SQUARE_BRACKET:
  {
    int index;
    //fprintf(fp, "[");
    EvaluateConstantExpression(p->pExpressionRight, &index);
    //fprintf(fp, "]");
    ASSERT(false);
  }
  break;

  case TK_LEFT_PARENTHESIS:
  {
    EvaluateConstantExpression(p->pExpressionRight, &result);
  }
  break;

  case TK_PLUSPLUS:
    ASSERT(false);
    break;
  case TK_MINUSMINUS:
    ASSERT(false);
    break;
  default:
    ASSERT(false);
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
bool EvaluateConstantExpression(TExpression *  p, int *pResult)
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
      TBinaryExpression* pBinaryExpression =
        (TBinaryExpression*)p;

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
        ASSERT(false);
        b = false;
      }

      //if (pBinaryExpression->)
    }
    break;

    CASE(TTernaryExpression) :
    {
      int e1, e2, e3;
      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionLeft, &e1);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionMiddle, &e2);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionRight, &e3);
      ASSERT(false);
    }
    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

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
          ASSERT(0);
          break;
        }

      }
    }
    break;

    CASE(TPostfixExpressionCore) :
    {
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
      ASSERT(false);
    }
    break;

    CASE(TUnaryExpressionOperator) :
    {

      TUnaryExpressionOperator* pTUnaryExpressionOperator =
        (TUnaryExpressionOperator*)p;

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
          ASSERT(false);
        }
      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;


      //b = TTypeQualifier_CodePrint2(&pCastExpressionType->TypeName.qualifiers, fp);
      //b = TTypeSpecifier_CodePrint2(pCastExpressionType->TypeName.pTypeSpecifier, b, fp);
      //b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.declarator, b, fp);

      b = EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
      ASSERT(false);

    }
    break;

  default:
    ASSERT(false);
  }

  ASSERT(result != -987654321);
  *pResult = result;
  return b;
}



TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(TDeclaration* p, int index)
{
  TDeclarationSpecifiers* pResult = NULL;
  TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
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

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration* p)
{
  TParameterTypeList* pParameterTypeList = NULL;

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

const char* TDeclaration_GetFunctionName(TDeclaration* p)
{
  const char* functionName = NULL;

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

TCompoundStatement* TDeclaration_Is_FunctionDefinition(TDeclaration* p)
{
  TCompoundStatement* pCompoundStatement = NULL;

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

TStructUnionSpecifier* TDeclarationSpecifiers_Find_StructUnionSpecifier(TDeclarationSpecifiers* p)
{
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;

  for (int i = 0; i < p->Size; i++)
  {
    TDeclarationSpecifier* pDeclarationSpecifier = p->pData[i];

    pStructUnionSpecifier =
      TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclarationSpecifier);
    if (pStructUnionSpecifier)
    {
      break;
    }
  }
  return pStructUnionSpecifier;
}

TStructUnionSpecifier* TParameter_Is_DirectPointerToStruct(TProgram* program, TParameter* pParameter)
{
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;
  if (TParameter_IsDirectPointer(pParameter))
  {
    const char* typedefName = TParameter_GetTypedefName(pParameter);
    if (typedefName != NULL)
    {
      TDeclaration* pArgType = TProgram_FindDeclaration(program, TParameter_GetTypedefName(pParameter));
      if (pArgType)
      {
        pStructUnionSpecifier =
          TDeclarationSpecifiers_Find_StructUnionSpecifier(&pArgType->Specifiers);
      }
    }
  }
  return pStructUnionSpecifier;
}

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}

void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList* p) _default
{
  TPrimaryExpressionLiteralItem_Delete(p->pHead);
}

void TPrimaryExpressionLiteralItemList_Add(TPrimaryExpressionLiteralItemList* pList, TPrimaryExpressionLiteralItem *pItem)
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

const char* TDeclaration_GetArgName(TDeclaration* p, int index)
{
  const char* argName = NULL;
  TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
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


int TDeclaration_GetNumberFuncArgs(TDeclaration* p)
{
  TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
  int n = 0;
  ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
  {
    n++;
  }
  return n;
}






TDirectDeclarator* TDirectDeclarator_Create() _default
{
  TDirectDeclarator *p = (TDirectDeclarator*)malloc(sizeof * p);
  if (p != NULL)
  {
    String_Init(&p->Identifier);
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


TTypeName* TTypeName_Create() _default
{
  TTypeName *p = (TTypeName*)malloc(sizeof * p);
  if (p != NULL)
  {
    TTypeName_Init(p);
  }
  return p;
}


void TTypeName_Destroy(TTypeName* p) _default
{
  TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
  TDeclarator_Destroy(&p->Declarator);
}

void TTypeName_Delete(TTypeName* p) _default
{
  if (p != NULL)
  {
    TTypeName_Destroy(p);
    free((void*)p);
  }
}


TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create() _default
{
  TAtomicTypeSpecifier *p = (TAtomicTypeSpecifier*)malloc(sizeof * p);
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




TPostfixExpressionCore* TPostfixExpressionCore_Create() _default
{
  TPostfixExpressionCore *p = (TPostfixExpressionCore*)malloc(sizeof * p);
  if (p != NULL)
  {
    p->Type = TPostfixExpressionCore_ID;
    p->token = TK_NONE;
    String_Init(&p->lexeme);
    p->pExpressionLeft = NULL;
    p->pExpressionRight = NULL;
    p->pNext = NULL;
    TInitializerList_Init(&p->InitializerList);
    String_Init(&p->Identifier);
    p->pTypeName = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
    TScannerItemList_Init(&p->ClueList3);
    TScannerItemList_Init(&p->ClueList4);
  }
  return p;
}

TCastExpressionType* TCastExpressionType_Create() _default
{
  TCastExpressionType *p = (TCastExpressionType*)malloc(sizeof * p);
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


TUnaryExpressionOperator* TUnaryExpressionOperator_Create() _default
{
  TUnaryExpressionOperator *p = (TUnaryExpressionOperator*)malloc(sizeof * p);
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





#define CPRIME_MAX_DRIVE 255
#define CPRIME_MAX_DIR 255
#define CPRIME_MAX_FNAME 255
#define CPRIME_MAX_EXT 255
#define CPRIME_MAX_PATH 260

void GetFullPath(const char* fileName, String* out);
void GetFullDir(const char* fileName, String* out);
bool IsFullPath(const char * path);
bool IsInPath(const char * filePath, const char* path);
bool FileExists(const char* fullPath);
void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext);
void MakePath(char* path, char* drv, char* dir, char* name, char* ext);



void TProgram_PrintAstToFile(TProgram* pProgram,
  const char* fileName,
  const char* inputFileName);



void PrintLiteralString(FILE* fp, const char* psz);

bool TFunctionSpecifier_Print(TFunctionSpecifier* p, bool b, FILE* fp);
bool StorageSpecifier_Print(TStorageSpecifier* p, bool b, FILE* fp);
bool TTypeQualifierList_Print(TTypeQualifierList* p, bool b, FILE* fp);
bool TDeclarator_Print(TDeclarator* p, bool b, FILE* fp);
bool TAnyDeclaration_Print(TAnyDeclaration *pDeclaration, bool b, FILE* fp);
bool TTypeSpecifier_Print(TTypeSpecifier* p, bool b, FILE* fp);
bool TStructDeclaration_Print(TAnyStructDeclaration* p, bool b, FILE* fp);
bool TTypeQualifier_Print(TTypeQualifier* p, bool b, FILE* fp);
bool TDeclaration_Print(TDeclaration* p, bool b, FILE* fp);
bool TExpression_Print(TExpression * p, const char* name, bool b, FILE* fp);
bool TStatement_Print(TStatement * p, bool b, FILE* fp);
bool TBlockItem_Print(TBlockItem * p, bool b, FILE* fp);
bool TInitializer_Print(TInitializer* p, bool b, FILE* fp);
bool TPointer_Print(TPointer* pPointer, bool b, FILE* fp);
bool TParameter_Print(TParameter* p, bool b, FILE* fp);
bool TInitializerListItem_Print(TInitializerListItem* p, bool b, FILE* fp);

bool TCompoundStatement_Print(TCompoundStatement * p, bool b, FILE* fp)
{
  if (b)
  {
    fprintf(fp, ",");
  }

  b = true;
  fprintf(fp, "\"compound-statement\": [");

  for (int j = 0; j < p->BlockItemList.Size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_Print(pBlockItem, j > 0, fp);
  }

  fprintf(fp, "]");
  return b;
}


bool TLabeledStatement_Print(TLabeledStatement * p, bool b, FILE* fp)
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

bool TForStatement_Print(TForStatement * p, bool b, FILE* fp)
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


bool TWhileStatement_Print(TWhileStatement * p, bool b, FILE* fp)
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


bool TDoStatement_Print(TDoStatement * p, bool b, FILE* fp)
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

void PrintLiteralString(FILE* fp, const char* psz)
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

bool TExpressionStatement_Print(TExpressionStatement * p, bool b, FILE* fp)
{
  TExpression_Print(p->pExpression, "expression-statement", b, fp);
  //fprintf(fp, ",");
  //TExpression_Print(&p->Expression, false, fp);
  //fprintf(fp, "}");
  return true;
}


bool TJumpStatement_Print(TJumpStatement * p, bool b, FILE* fp)
{
  fprintf(fp, "\"type\":\"jump-statement\"");
  //fprintf(fp, ",");
  //fprintf(fp, "\"statement\": {");
  b = TExpression_Print(p->pExpression, "statement", false, fp);
  //fprintf(fp, "}");
  return true;
}

bool TAsmStatement_Print(TAsmStatement * p, bool b, FILE* fp)
{
  fprintf(fp, "\"type\":\"asm-statement\"");
  return true;
}

bool TSwitchStatement_Print(TSwitchStatement * p, bool b, FILE* fp)
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


bool TIfStatement_Print(TIfStatement * p, bool b, FILE* fp)
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

bool TStatement_Print(TStatement *  p, bool b, FILE* fp)
{
  if (p == NULL)
  {
    return false;
  }

  switch (p->Type)
  {
  case TExpressionStatement_ID:
    b = TExpressionStatement_Print((TExpressionStatement*)p, b, fp);
    break;

  case TSwitchStatement_ID:
    b = TSwitchStatement_Print((TSwitchStatement*)p, b, fp);
    break;

  case TLabeledStatement_ID:
    b = TLabeledStatement_Print((TLabeledStatement*)p, b, fp);
    break;

  case TForStatement_ID:
    b = TForStatement_Print((TForStatement*)p, b, fp);
    break;

  case TJumpStatement_ID:
    b = TJumpStatement_Print((TJumpStatement*)p, b, fp);
    break;

  case TAsmStatement_ID:
    b = TAsmStatement_Print((TAsmStatement*)p, b, fp);
    break;

  case TCompoundStatement_ID:
    b = TCompoundStatement_Print((TCompoundStatement*)p, b, fp);
    break;

  case TIfStatement_ID:
    b = TIfStatement_Print((TIfStatement*)p, b, fp);
    break;

  case TDoStatement_ID:
    TDoStatement_Print((TDoStatement*)p, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

bool TBlockItem_Print(TBlockItem *  p, bool b, FILE* fp)
{
  if (p == NULL)
  {
    ASSERT(false);
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
    b = TSwitchStatement_Print((TSwitchStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TJumpStatement_ID:
    fprintf(fp, "{");
    b = TJumpStatement_Print((TJumpStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TForStatement_ID:
    fprintf(fp, "{");
    b = TForStatement_Print((TForStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TIfStatement_ID:
    fprintf(fp, "{");
    b = TIfStatement_Print((TIfStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TWhileStatement_ID:
    fprintf(fp, "{");
    b = TWhileStatement_Print((TWhileStatement*)p, b, fp);
    fprintf(fp, "}");
    break;

  case TDoStatement_ID:
    fprintf(fp, "{");
    b = TDoStatement_Print((TDoStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TDeclaration_ID:
    b = TDeclaration_Print((TDeclaration*)p, false, fp);
    break;

  case TLabeledStatement_ID:
    fprintf(fp, "{");
    b = TLabeledStatement_Print((TLabeledStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TCompoundStatement_ID:
    fprintf(fp, "{");
    b = TCompoundStatement_Print((TCompoundStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TExpressionStatement_ID:
    fprintf(fp, "{");
    b = TExpressionStatement_Print((TExpressionStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  case TAsmStatement_ID:
    fprintf(fp, "{");
    b = TAsmStatement_Print((TAsmStatement*)p, false, fp);
    fprintf(fp, "}");
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

bool TPostfixExpressionCore_Print(TPostfixExpressionCore * p, bool b, FILE* fp)
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
    ASSERT(false);
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

bool TTypeName_Print(TTypeName *  p, const char* name, bool b, FILE* fp)
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

bool TExpression_Print(TExpression *  p, const char* name, bool b, FILE* fp)
{
  if (p == NULL)
  {
    //ASSERT(false);
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
      b = TExpression_Print(((TBinaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    b = TExpression_Print(((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
    fprintf(fp, ",\"binary\":\"%s\"", TokenToString(((TBinaryExpression*)p)->token));

    //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
    break;

    CASE(TTernaryExpression) :
      b = TExpression_Print(((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
    b = TExpression_Print(((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
    b = TExpression_Print(((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
    fprintf(fp, ",\"ternary\":\"%s\"", TokenToString(((TTernaryExpression*)p)->token));

    //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

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
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      b = TPostfixExpressionCore_Print(pPostfixExpressionCore, b, fp);
    }
    break;

    CASE(TUnaryExpressionOperator) :
    {
      TUnaryExpressionOperator* pTUnaryExpressionOperator =
        (TUnaryExpressionOperator*)p;

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

      fprintf(fp, ",\"unary\":\"%s\"", TokenToString(((TBinaryExpression*)p)->token));
    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;

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

    ASSERT(false);
  }

  fprintf(fp, "}");
  return b;
}


bool TEnumerator_Print(TEnumerator* pTEnumerator, bool b, FILE* fp)
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

bool TEnumSpecifier_Print(TEnumSpecifier* p, bool b, FILE* fp)
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


bool TStructUnionSpecifier_Print(TStructUnionSpecifier* p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "{");
  if (p->Token == TK_STRUCT)
    fprintf(fp, "\"type:\":\"struct-specifier\",");
  else if (p->Token == TK_UNION)
    fprintf(fp, "\"type:\":\"union-specifier\",");

  fprintf(fp, "\"name\":\"%s\",", p->Name);

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

bool TSingleTypeSpecifier_Print(TSingleTypeSpecifier* p, bool b, FILE* fp)
{
  fprintf(fp, "{");
  b = true;
  fprintf(fp, "\"type\":\"type-specifier\",");
  fprintf(fp, "\"lexeme\":");

  fprintf(fp, "\"");

  if (p->Token == TK_IDENTIFIER)
  {
    fprintf(fp, "%s", p->TypedefName);
  }
  else
  {
    fprintf(fp, "%s", TokenToString(p->Token));
  }

  fprintf(fp, "\"");

  fprintf(fp, "}");

  return b;
}

bool TTypeSpecifier_Print(TTypeSpecifier*  p, bool b, FILE* fp)
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
    b = TStructUnionSpecifier_Print((TStructUnionSpecifier*)p, b, fp);
    break;

  case TEnumSpecifier_ID:
    b = TEnumSpecifier_Print((TEnumSpecifier*)p, b, fp);
    break;

  case TSingleTypeSpecifier_ID:
    b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier*)p, b, fp);
    break;

  default:
    break;
  }

  return b;
}

bool TDesignator_Print(TDesignator* p, bool b, FILE* fp)
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

bool TInitializerList_Print(TInitializerList*p, bool b, FILE* fp)
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


bool TInitializer_Print(TInitializer* p, bool b, FILE* fp)
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
    b = TExpression_Print((TExpression*)p, "initializer-expression", false, fp);
    //fprintf(fp, "}");
    break;

  case TInitializerListType_ID:
    fprintf(fp, "\"initializer\":");
    b = TInitializerList_Print(&((TInitializerListType*)p)->InitializerList, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}


bool TPointerList_Print(TPointerList *p, bool b, FILE* fp)
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

bool TParameterList_Print(TParameterList *p, bool b, FILE* fp)
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
bool TParameterTypeList_Print(TParameterTypeList *p, bool b, FILE* fp)
{
  return TParameterList_Print(&p->ParameterList, b, fp);
}

bool TStructDeclarator_Print(TStructDeclarator* p, bool b, FILE* fp)
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

bool TInitDeclarator_Print(TInitDeclarator* p, bool b, FILE* fp)
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

bool TDirectDeclarator_Print(TDirectDeclarator* pDirectDeclarator,
  bool b,
  FILE* fp)
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

bool TDeclarator_Print(TDeclarator* p, bool b, FILE* fp)
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

bool TStructDeclaratorList_Print(TStructDeclaratorList *p, bool b, FILE* fp)
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

bool TInitDeclaratorList_Print(TInitDeclaratorList *p, bool b, FILE* fp)
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

bool SpecifierQualifier_Print(TSpecifierQualifier* pItem, bool b, FILE* fp)
{
  switch (pItem->Type)
  {
    CASE(TStorageSpecifier) :
      b = StorageSpecifier_Print((TStorageSpecifier*)pItem, b, fp);
    break;
    CASE(TTypeQualifier) :
      b = TTypeQualifier_Print((TTypeQualifier*)pItem, b, fp);
    break;
    CASE(TFunctionSpecifier) :
      b = TFunctionSpecifier_Print((TFunctionSpecifier*)pItem, b, fp);
    break;

    CASE(TSingleTypeSpecifier) :
      b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier*)pItem, b, fp);
    break;

    CASE(TStructUnionSpecifier) :
      b = TStructUnionSpecifier_Print((TStructUnionSpecifier*)pItem, b, fp);
    break;

    CASE(TEnumSpecifier) :
      b = TEnumSpecifier_Print((TEnumSpecifier*)pItem, b, fp);
    break;

    //CASE(TAlignmentSpecifier) :
    //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
    //break;
  default:
    ASSERT(false);
    break;
  }
  return b;
}
bool SpecifierQualifierList_Print(TSpecifierQualifierList* p, bool b, FILE* fp)
{
  fprintf(fp, "\"specifier-qualifier-list\" : [");
  for (int i = 0; i < p->Size; i++)
  {
    TSpecifierQualifier* pItem = p->pData[i];
    if (b)
      fprintf(fp, ",");

    b = SpecifierQualifier_Print(pItem, b, fp);
  }
  fprintf(fp, "]");
  return b;
}

bool TStructDeclarationBase_Print(TStructDeclaration* p, bool b, FILE* fp)
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

bool TStructDeclaration_Print(TAnyStructDeclaration* p, bool b, FILE* fp)
{
  switch (p->Type)
  {
  case TStructDeclaration_ID:
    b = TStructDeclarationBase_Print((TStructDeclaration*)p, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

bool StorageSpecifier_Print(TStorageSpecifier* p, bool b, FILE* fp)
{
  b = true;
  fprintf(fp, "{");
  fprintf(fp, "\"type\":\"storage-specifer\",");
  fprintf(fp, "\"lexeme\":\"");

  fprintf(fp, TokenToString(p->Token));

  fprintf(fp, "\"}");

  return b;
}

bool TFunctionSpecifier_Print(TFunctionSpecifier* p, bool b, FILE* fp)
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



bool TTypeQualifier_Print(TTypeQualifier* p, bool b, FILE* fp)
{
  fprintf(fp, "{");
  fprintf(fp, "\"type\": \"type-qualifier\",");
  fprintf(fp, "\"lexeme\": \"");


  fprintf(fp, "%s", TokenToString(p->Token));


  fprintf(fp, "\"}");

  return true;
}

bool TTypeQualifierList_Print(TTypeQualifierList* p, bool b, FILE* fp)
{
  fprintf(fp, "\"type-qualifier-list\":[");
  b = false;
  for (int i = 0; i < p->Size; i++)
  {
    TTypeQualifier* pItem = p->Data[i];

    if (b)
    {
      fprintf(fp, ",");
    }
    b = TTypeQualifier_Print(pItem, b, fp);
  }
  fprintf(fp, "]");
  return b;
}



bool TPointer_Print(TPointer* pPointer, bool b, FILE* fp)
{
  fprintf(fp, "{");
  TTypeQualifierList_Print(&pPointer->Qualifier, false, fp);
  fprintf(fp, "}");
  return true;
}

bool TDeclarationSpecifier_Print(TDeclarationSpecifier* pItem, bool b, FILE* fp)
{
  switch (pItem->Type)
  {
    CASE(TStorageSpecifier) :
      b = StorageSpecifier_Print((TStorageSpecifier*)pItem, b, fp);
    break;
    CASE(TTypeQualifier) :
      b = TTypeQualifier_Print((TTypeQualifier*)pItem, b, fp);
    break;

    CASE(TFunctionSpecifier) :
      b = TFunctionSpecifier_Print((TFunctionSpecifier*)pItem, b, fp);
    break;

    CASE(TSingleTypeSpecifier) :
      b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier*)pItem, b, fp);
    break;

    CASE(TStructUnionSpecifier) :
      b = TStructUnionSpecifier_Print((TStructUnionSpecifier*)pItem, b, fp);
    break;

    CASE(TEnumSpecifier) :
      b = TEnumSpecifier_Print((TEnumSpecifier*)pItem, b, fp);
    break;

  default:
    ASSERT(false);
    break;
    //CASE(TAlignmentSpecifier) :
    //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
    //break;

  }
  return b;
}
bool TDeclarationSpecifiers_Print(TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, FILE* fp)
{
  fprintf(fp, "\"declarations-specifiers\": [");
  b = false;

  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];


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

bool TDeclaration_Print(TDeclaration* p, bool b, FILE* fp)
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


bool TParameter_Print(TParameter* p, bool b, FILE* fp)
{
  fprintf(fp, "{");
  b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);
  fprintf(fp, ",");
  fprintf(fp, "\"declarator\":");
  b = TDeclarator_Print(&p->Declarator, b, fp);
  fprintf(fp, "}");
  return b;
}

bool TAnyDeclaration_Print(TAnyDeclaration *pDeclaration, bool b, FILE* fp)
{
  switch (pDeclaration->Type)
  {
  case TEofDeclaration_ID:
    break;

  case TStaticAssertDeclaration_ID:
    break;

  case TDeclaration_ID:
    b = TDeclaration_Print((TDeclaration*)pDeclaration, b, fp);
    break;

  default:
    ASSERT(false);
    break;
  }

  return b;
}

bool TDesignatorList_Print(TDesignatorList *p, bool b, FILE* fp)
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


bool TInitializerListItem_Print(TInitializerListItem* p, bool b, FILE* fp)
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


bool TDeclarations_Print(TDeclarations *p, bool b, FILE* fp)
{
  b = false;
  fprintf(fp, "[");

  for (int i = 0; i < p->Size; i++)
  {
    if (i > 0)
      fprintf(fp, ",");

    TAnyDeclaration* pItem = p->pItems[i];
    b = TAnyDeclaration_Print(pItem, b, fp);
  }

  fprintf(fp, "]");
  return true;
}


void TProgram_PrintAstToFile(TProgram* pProgram,
  const char* fileName,
  const char* inputFileName)
{
  FILE * fp = fopen(fileName, "w");
  //TDeclarations_Print(&pProgram->Declarations, false, fp);


  bool b = false;
  fprintf(fp, "[");

  for (int i = 0; i < pProgram->Declarations.Size; i++)
  {
    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
    if (b)
      fprintf(fp, ",");
    b = TAnyDeclaration_Print(pItem, b, fp);

  }

  fprintf(fp, "]");

  fclose(fp);
}










#define SYMBOL_BUCKETS_SIZE 1000

typedef struct {
  // indica presenca de erro no parser
  bool bError;

  // mensagem de erro
  StrBuilder ErrorMessage;

  // scanner ja pr�-processado
  Scanner Scanner;

  TScannerItemList ClueList;

  SymbolMap GlobalScope;
  SymbolMap* pCurrentScope;

  int IncludeLevel;
  bool bPreprocessorEvalFlag;
} Parser;

Result Parser_InitFile(Parser *parser, const char *fileName);

Result Parser_InitString(Parser *parser, const char *name, const char *text);

void Parser_Destroy(Parser *parser);

bool Parser_HasError(Parser *pParser);

const char *GetCompletationMessage(Parser *parser);

bool GetAST(const char *filename, const char *configFileName,

  TProgram *pProgram);

void ConstantExpression(Parser *ctx, TExpression **ppExpression);
Tokens Parser_MatchToken(Parser *parser, Tokens tk, TScannerItemList *listOpt);

Tokens Parser_LookAheadToken(Parser *parser);

bool GetASTFromString(const char*  sourceCode,
  TProgram* pProgram);

wchar_t BasicScanner_MatchChar(BasicScanner* scanner);

const char* TokenToString(Tokens tk)
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
  case TK__AUTO:
    return "_auto";
  case TK__SIZE:
    return "_size";
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
  case TK__DEFAULT:
    return "_default";
  case TK__DEFVAL:
    return "_defval";
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
  case TK__UNION:
    return "_union";
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
    ASSERT(false);
    break;
  }
  return "???";
}

ScannerItem* ScannerItem_Create(void) _default
{
  ScannerItem *p = (ScannerItem*)malloc(sizeof * p);
  if (p != NULL)
  {
    ScannerItem_Init(p);
  }
  return p;
}

void ScannerItem_Delete(ScannerItem* pScannerItem) _default
{
  if (pScannerItem != NULL)
  {
    ScannerItem_Destroy(pScannerItem);
    free((void*)pScannerItem);
  }
}

void ScannerItem_Init(ScannerItem* scannerItem) _default
{
  LocalStrBuilder_Init(&scannerItem->lexeme);
  scannerItem->token = TK_NONE;
  scannerItem->Line = -1;
  scannerItem->FileIndex = -1;
  scannerItem->bActive = 1;
  scannerItem->pNext = NULL;
}

void ScannerItem_Reset(ScannerItem* scannerItem)
{
  LocalStrBuilder_Clear(&scannerItem->lexeme);
  scannerItem->token = TK_EOF;
}

void ScannerItem_Copy(ScannerItem* scannerItem,
  ScannerItem* other)
{
  scannerItem->token = other->token;
  LocalStrBuilder_Set(&scannerItem->lexeme, other->lexeme.c_str);
}

void ScannerItem_Swap(ScannerItem* scannerItem,
  ScannerItem* other)
{
  Tokens tk = other->token;
  other->token = scannerItem->token;
  scannerItem->token = tk;
  LocalStrBuilder_Swap(&scannerItem->lexeme, &other->lexeme);
}

void ScannerItem_Destroy(ScannerItem* scannerItem) _default
{
  LocalStrBuilder_Destroy(&scannerItem->lexeme);
}

void BasicScanner_InitCore(BasicScanner* pBasicScanner,
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

Result BasicScanner_Init(BasicScanner* pBasicScanner,
  const char* name,
  const char* text,
  BasicScannerType type)
{
  BasicScanner_InitCore(pBasicScanner, type);
  return SStream_Init(&pBasicScanner->stream, name, text);
}

Result BasicScanner_InitFile(BasicScanner* pBasicScanner,
  const char* fileName)
{
  BasicScanner_InitCore(pBasicScanner, BasicScannerType_File);
  return SStream_InitFile(&pBasicScanner->stream, fileName);
}

Result BasicScanner_Create(BasicScanner** pp,
  const char* name,
  const char* text,
  BasicScannerType Type)
{
  Result result = RESULT_OUT_OF_MEM;
  BasicScanner* p = (BasicScanner*)malloc(sizeof(BasicScanner));
  if (p)
  {
    result = BasicScanner_Init(p, name, text, Type);
    if (result == RESULT_OK)
    {
      *pp = p;
    }
    else
    {
      free(p);
    }
  }
  return result;
}

Result BasicScanner_CreateFile(const char* fileName, BasicScanner** pp)
{
  Result result = RESULT_OUT_OF_MEM;
  BasicScanner* p = (BasicScanner*)malloc(sizeof(BasicScanner));
  if (p)
  {
    result = BasicScanner_InitFile(p, fileName);
    if (result == RESULT_OK)
    {
      *pp = p;
    }
    else
    {
      free(p);
    }
  }
  return result;
}


void BasicScanner_Destroy(BasicScanner* pBasicScanner) _default
{
  SStream_Destroy(&pBasicScanner->stream);
  ScannerItem_Destroy(&pBasicScanner->currentItem);
}

void BasicScanner_Delete(BasicScanner* pBasicScanner) _default
{
  if (pBasicScanner != NULL)
  {
    BasicScanner_Destroy(pBasicScanner);
    free((void*)pBasicScanner);
  }
}

struct TkPair
{
  const char* lexeme;
  Tokens token;
};

static struct TkPair singleoperators[] =
{
  //punctuator: one of

  { "[", TK_LEFT_SQUARE_BRACKET }, //0
  { "]",  TK_RIGHT_SQUARE_BRACKET },
  { "(", TK_LEFT_PARENTHESIS },
  { ")", TK_RIGHT_PARENTHESIS },
  { "{", TK_LEFT_CURLY_BRACKET },
  { "}", TK_RIGHT_CURLY_BRACKET },
  { ".", TK_FULL_STOP },
  { "&", TK_AMPERSAND },
  { "*", TK_ASTERISK },
  { "+", TK_PLUS_SIGN },
  { "-",  TK_HYPHEN_MINUS },
  { "~", TK_TILDE },
  { "!", TK_EXCLAMATION_MARK },
  { "%", TK_PERCENT_SIGN },
  { "<", TK_LESS_THAN_SIGN },
  { ">", TK_GREATER_THAN_SIGN },
  { "^", TK_CIRCUMFLEX_ACCENT },
  { "|", TK_VERTICAL_LINE },
  { "?", TK_QUESTION_MARK },
  { ":", TK_COLON },
  { ";", TK_SEMICOLON },
  { "=", TK_EQUALS_SIGN },
  { ",", TK_COMMA },
  { "$", TK_DOLLAR_SIGN },
  { "@", TK_COMMERCIAL_AT }
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
  { "_auto", TK__AUTO },
  { "_size", TK__SIZE },
  { "break", TK_BREAK },
  { "case", TK_CASE },
  { "char", TK_CHAR },
  { "const", TK_CONST },
  { "continue", TK_CONTINUE },
  { "default", TK_DEFAULT },
  { "_default", TK__DEFAULT },
  { "_defval", TK__DEFVAL },
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
  { "__forceinline", TK__FORCEINLINE },
  { "int", TK_INT },
  { "long", TK_LONG },
  //
  { "__int8", TK__INT8 },
  { "__int16", TK__INT16 },
  { "__int32", TK__INT32 },
  { "__int64", TK__INT64 },
  { "__wchar_t", TK__WCHAR_T },
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
  { "_union", TK__UNION },
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
  { "__asm", TK__ASM }, //visual studio
  { "class", TK_CLASS }

};
void BasicScanner_Next(BasicScanner* scanner);
void BasicScanner_Match(BasicScanner* scanner)
{
  BasicScanner_Next(scanner);
}

bool BasicScanner_MatchToken(BasicScanner* scanner, Tokens token)
{
  bool b = false;
  if (scanner->currentItem.token == token)
  {
    b = true;
    BasicScanner_Match(scanner);
  }
  return b;
}


void BasicScanner_Next(BasicScanner* scanner)
{
  if (scanner->Type == BasicScannerType_Token)
  {
    if (scanner->bLineStart)
    {
      ScannerItem_Reset(&scanner->currentItem);
      scanner->currentItem.token = scanner->m_Token;
      LocalStrBuilder_Set(&scanner->currentItem.lexeme,
        scanner->stream.text);
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


  scanner->currentItem.Line = scanner->stream.currentLine;
  scanner->currentItem.FileIndex = scanner->FileIndex;

  //bool bLineStart = scanner->bLineStart;
  //scanner->bLineStart = false;
  wchar_t ch = '\0';
  ScannerItem_Reset(&scanner->currentItem);
  ch = scanner->stream.currentChar;
  wchar_t ch1 = SStream_LookAhead(&scanner->stream);
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
        //SStream_Next(&scanner->stream);
        break;
      }
    }
    scanner->bLineStart = false;
    return;
  }
  if (ch == '0' && (ch1 == 'x' || ch1 == 'X'))
  {
    ch = BasicScanner_MatchChar(scanner);
    ch = BasicScanner_MatchChar(scanner);
    scanner->currentItem.token = TK_HEX_INTEGER;
    while ((ch >= '0' && ch <= '9') ||
      (ch >= 'A' && ch <= 'F') ||
      (ch >= 'a' && ch <= 'f'))
    {
      ch = BasicScanner_MatchChar(scanner);
    }

    bool bHasIntegerSuffix = false;
    while (ch == 'l' || ch == 'L' || ch == 'u' || ch == 'U')
    {
      ch = BasicScanner_MatchChar(scanner);
      bHasIntegerSuffix = true;
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

    //integer-suffix:
    //ULL L LL U
    bool bHasIntegerSuffix = false;
    while (ch == 'l' || ch == 'L' || ch == 'u' || ch == 'U')
    {
      ch = BasicScanner_MatchChar(scanner);
      bHasIntegerSuffix = true;
    }

    if (bHasIntegerSuffix)
    {
      //ver se faz sentido?
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
      if (scanner->stream.currentChar == 'e' ||
        scanner->stream.currentChar == 'E')
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
      SStream_Match(&scanner->stream);
      ch = scanner->stream.currentChar;
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
  if (scanner->stream.currentChar == '#')
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
          SStream_Match(&scanner->stream);
          ch = scanner->stream.currentChar;
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
      //scanner->bLineStart = true;
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
  ASSERT(false);
}


Tokens BasicScanner_Token(BasicScanner* scanner)
{
  return scanner->currentItem.token;
}

const char* BasicScanner_Lexeme(BasicScanner* scanner)
{
  return scanner->currentItem.lexeme.c_str;
}

bool BasicScanner_IsLexeme(BasicScanner* scanner, const char* psz)
{
  return strcmp(BasicScanner_Lexeme(scanner), psz) == 0;
}

wchar_t BasicScanner_MatchChar(BasicScanner* scanner)
{
  LocalStrBuilder_AppendChar(&scanner->currentItem.lexeme,
    (char)scanner->stream.currentChar);
  SStream_Match(&scanner->stream);
  return scanner->stream.currentChar;
}

//////////////////////////////////////////////



void BasicScannerStack_Init(BasicScannerStack* stack)
{
  *stack = NULL;
}

void BasicScannerStack_Push(BasicScannerStack* stack, BasicScanner* pItem)
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

BasicScanner* BasicScannerStack_PopGet(BasicScannerStack* stack)
{
  BasicScanner* pItem = NULL;
  if (*stack != NULL)
  {
    pItem = *stack;
    *stack = pItem->pPrevious;
  }
  return pItem;
}

void BasicScannerStack_PopIfNotLast(BasicScannerStack* stack)
{
  ASSERT(*stack != NULL);
  if ((*stack)->pPrevious != NULL)
  {
    BasicScanner_Delete(BasicScannerStack_PopGet(stack));
  }
}

void BasicScannerStack_Pop(BasicScannerStack* stack)
{
  BasicScanner_Delete(BasicScannerStack_PopGet(stack));
}

void BasicScannerStack_Destroy(BasicScannerStack* stack)
{
  BasicScanner* pItem = *stack;
  while (pItem)
  {
    BasicScanner* p = pItem;
    pItem = pItem->pPrevious;
    BasicScanner_Delete(p);
  }
}





typedef enum
{
  SearchNone,
  SearchAll,
  SearchDestroy,
  SearchInit,
  SearchDelete,
} Search;

typedef struct Options
{
  ///////////
  //controle interno
  bool bInclude;// = true;
  int IncludeLevel;// = 0;
                   ////////////
  bool bExpandMacros;
  bool bIncludeComments _defval(1);

  //Usado para converter para string 
  //exemplo unsigned   /*algo*/ int   
  //tem que imprimir so 'unsigned int'
  bool bPrintRepresentation;

  int IdentationLevel;
  bool bHideDefaultImplementation;
} Options;

#define OPTIONS_INIT {true, 0,  false, true, false, 0, false}

void Options_Destroy(Options* options);

void TProgram_PrintCodeToFile(TProgram * pProgram,
  Options* options,
  const char * fileName,
  const char* userpath);

void TProgram_PrintCodeToString(TProgram* pProgram,
  Options* options,
  StrBuilder* output);


void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp);


bool IsSuffix(const char* s, const char* suffix);
void TSpecifierQualifierList_CodePrint(TProgram* program,
  Options * options,
  TSpecifierQualifierList* pDeclarationSpecifiers,

  StrBuilder* fp);


void TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, StrBuilder* fp);

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

void InstanciateDestroy2(TProgram* program,
  Options* options,
  TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
  TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
  TInitializer* pInitializer,
  TParameterTypeList* pArgsOpt,
  const char* pInitExpressionText, //(x->p->i = 0)    
  const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                              //se passar null eh pq nao interessa
  const Action action,
  Search search,
  bool *pbHasInitializers,
  StrBuilder* fp);



void Options_Destroy(Options* options) _default
{
}


void TSpecifierQualifierList_CodePrint(TProgram* program, Options * options, TSpecifierQualifierList* pDeclarationSpecifiers, StrBuilder* fp);

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp);

static void TInitializer_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitializer* pTInitializer,

  StrBuilder* fp);

static void TInitializerList_CodePrint(TProgram* program,
  Options * options,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TDeclarator* pDeclarator,
  TInitializerList*p,

  StrBuilder* fp);


static void TInitializerListItem_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitializerListItem* p,

  StrBuilder* fp);


static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp);

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp);

static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp);
static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp);
static void TDeclaration_CodePrint(TProgram* program, Options * options, TDeclaration* p, StrBuilder* fp);
static void TExpression_CodePrint(TProgram* program, Options * options, TExpression * p, const char* name, StrBuilder* fp);
static void TStatement_CodePrint(TProgram* program, Options * options, TStatement * p, StrBuilder* fp);
static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem * p, StrBuilder* fp);

static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp);
static void TParameter_CodePrint(TProgram* program, Options * options, TParameter* p, StrBuilder* fp);

void Output_Append(StrBuilder* p,
  Options* options,
  const char* source)
{
  if (options->bInclude  && options->IncludeLevel == 0)
    StrBuilder_Append(p, source);
}

static void TNodeClueList_CodePrint(Options* options, TScannerItemList* list,
  StrBuilder* fp)
{
  if (options->bPrintRepresentation)
  {
    //quando se imprime a representacao o espacamento
    //eh feito por fora e nao tem macros.
    return;
  }

  ForEachListItem(ScannerItem, pNodeClue, list)
  {
    switch (pNodeClue->token)
    {
    case TK_PRE_INCLUDE:

      Output_Append(fp, options, pNodeClue->lexeme.c_str);
      Output_Append(fp, options, "\n");
      //if (pNodeClue->bActive)

      options->IncludeLevel++;
      //}
      break;

    case TK_FILE_EOF:
      options->IncludeLevel--;
      //ASSERT(IncludeLevel > 0);
      //bInclude = true;
      break;
    case TK_PRE_DEFINE:
      //TODO gerar macros como init
      Output_Append(fp, options, pNodeClue->lexeme.c_str);
      Output_Append(fp, options, "\n");
      break;

    case TK_PRE_UNDEF:
    case TK_PRE_PRAGMA:
    case TK_PRE_IF:
    case TK_PRE_ENDIF:
    case TK_PRE_ELSE:
    case TK_PRE_IFDEF:
    case TK_PRE_IFNDEF:
    case TK_PRE_ELIF:
      Output_Append(fp, options, pNodeClue->lexeme.c_str);
      Output_Append(fp, options, "\n");
      break;

    case TK_COMMENT:
      if (options->bIncludeComments)
      {
        Output_Append(fp, options, pNodeClue->lexeme.c_str);
      }
      else
      {
        Output_Append(fp, options, " ");
      }

      break;

    case TK_LINE_COMMENT:
      if (options->bIncludeComments)
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
      if (options->bExpandMacros)
      {

      }
      else
      {
        Output_Append(fp, options, pNodeClue->lexeme.c_str);
        options->bInclude = false;
      }
      break;


    case TK_MACRO_EOF:
      if (options->bExpandMacros)
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

static void TCompoundStatement_CodePrint(TProgram* program,
  Options * options,
  TCompoundStatement * p,

  StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, "{");

  for (int j = 0; j < p->BlockItemList.Size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_CodePrint(program, options, pBlockItem, fp);
  }

  TNodeClueList_CodePrint(options, &p->ClueList1, fp);
  Output_Append(fp, options, "}");

}


static void TLabeledStatement_CodePrint(TProgram* program, Options * options, TLabeledStatement * p, StrBuilder* fp)
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
      ASSERT(false);
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

static void TForStatement_CodePrint(TProgram* program, Options * options, TForStatement * p, StrBuilder* fp)
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


static void TWhileStatement_CodePrint(TProgram* program, Options * options, TWhileStatement * p, StrBuilder* fp)
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



static void TDoStatement_CodePrint(TProgram* program, Options * options, TDoStatement * p, StrBuilder* fp)
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


static void TExpressionStatement_CodePrint(TProgram* program, Options * options, TExpressionStatement * p, StrBuilder* fp)
{
  TExpression_CodePrint(program, options, p->pExpression, "", fp);

  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, ";");


}


static void TJumpStatement_CodePrint(TProgram* program, Options * options, TJumpStatement * p, StrBuilder* fp)
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
    ASSERT(false);
  }


  TNodeClueList_CodePrint(options, &p->ClueList2, fp);
  Output_Append(fp, options, ";");


}

static void TAsmStatement_CodePrint(TProgram* program, Options * options, TAsmStatement * p, StrBuilder* fp)
{
  Output_Append(fp, options, "\"type\":\"asm-statement\"");

}

static void TSwitchStatement_CodePrint(TProgram* program, Options * options, TSwitchStatement * p, StrBuilder* fp)
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


static void TIfStatement_CodePrint(TProgram* program, Options * options, TIfStatement * p, StrBuilder* fp)
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

static void TStatement_CodePrint(TProgram* program, Options * options, TStatement *  p, StrBuilder* fp)
{
  if (p == NULL)
  {
    return;
  }

  switch (p->Type)
  {
  case TExpressionStatement_ID:
    TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);
    break;

  case TSwitchStatement_ID:
    TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);
    break;

  case TLabeledStatement_ID:
    TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);
    break;

  case TForStatement_ID:
    TForStatement_CodePrint(program, options, (TForStatement*)p, fp);
    break;

  case TJumpStatement_ID:
    TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);
    break;

  case TAsmStatement_ID:
    TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);
    break;

  case TCompoundStatement_ID:
    TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
    break;

  case TIfStatement_ID:
    TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);
    break;

  case TDoStatement_ID:
    TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);
    break;

  default:
    ASSERT(false);
    break;
  }


}

static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem *  p, StrBuilder* fp)
{
  if (p == NULL)
  {
    ASSERT(false);
    return;
  }


  switch (p->Type)
  {
  case TEofDeclaration_ID:
    break;

  case TStaticAssertDeclaration_ID:
    break;

  case TSwitchStatement_ID:

    TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);

    break;

  case TJumpStatement_ID:

    TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);

    break;

  case TForStatement_ID:

    TForStatement_CodePrint(program, options, (TForStatement*)p, fp);

    break;

  case TIfStatement_ID:

    TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);

    break;

  case TWhileStatement_ID:

    TWhileStatement_CodePrint(program, options, (TWhileStatement*)p, fp);

    break;

  case TDoStatement_ID:

    TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);

    break;

  case TDeclaration_ID:
    TDeclaration_CodePrint(program, options, (TDeclaration*)p, fp);
    //Output_Append(fp, options,  "\n");
    break;

  case TLabeledStatement_ID:

    TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);

    break;

  case TCompoundStatement_ID:
    TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
    break;

  case TExpressionStatement_ID:

    TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);

    break;


  case TAsmStatement_ID:

    TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);

    break;

  default:
    ASSERT(false);
    break;
  }


}



bool GetType(const char* source,
  StrBuilder* strBuilderType)
{

  while (*source  &&
    *source != '_')
  {
    StrBuilder_AppendChar(strBuilderType, *source);
    source++;
  }


  return *source == '_';
}


bool GetTypeAndFunction(const char* source,
  StrBuilder* strBuilderType,
  StrBuilder* strBuilderFunc)
{

  while (*source  &&
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

static void TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, StrBuilder* fp);


static void TPrimaryExpressionLambda_CodePrint(TProgram* program,
  Options * options,
  TPrimaryExpressionLambda * p,
  StrBuilder* fp)
{
  static int global_lambda_counter = 0;
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

static void TPostfixExpressionCore_CodePrint(TProgram* program,
  Options * options,
  TPostfixExpressionCore * p,

  StrBuilder* fp)
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
        (TDeclarationSpecifiers*)&p->pTypeName->SpecifierQualifierList,
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
    ASSERT(false);
    break;
  }



  if (p->pNext)
  {
    TPostfixExpressionCore_CodePrint(program, options, p->pNext, fp);
  }



}

static void TExpression_CodePrint(TProgram* program, Options * options, TExpression *  p,
  const char* name,

  StrBuilder* fp)
{
  if (p == NULL)
  {
    //ASSERT(false);
    return;
  }



  switch (p->Type)
  {
    CASE(TBinaryExpression) :
    {
      TBinaryExpression* pBinaryExpression = (TBinaryExpression*)p;

      TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", fp);

      TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList0, fp);
      Output_Append(fp, options, TokenToString(pBinaryExpression->token));

      TExpression_CodePrint(program, options, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", fp);
    }
    break;

    CASE(TTernaryExpression) :
    {
      TTernaryExpression* pTernaryExpression =
        (TTernaryExpression*)p;


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
      TPrimaryExpressionLiteral* pPrimaryExpressionLiteral
        = (TPrimaryExpressionLiteral*)p;

      ForEachListItem(TPrimaryExpressionLiteralItem, pItem, &pPrimaryExpressionLiteral->List)
      {
        TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
        Output_Append(fp, options, pItem->lexeme);
      }
    }
    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

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
      TPrimaryExpressionLambda* pPostfixExpressionCore =
        (TPrimaryExpressionLambda*)p;
      TPrimaryExpressionLambda_CodePrint(program, options, pPostfixExpressionCore, fp);
    }
    break;

    CASE(TPostfixExpressionCore) :
    {
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, fp);
    }
    break;

    CASE(TUnaryExpressionOperator) :
    {
      TUnaryExpressionOperator* pTUnaryExpressionOperator =
        (TUnaryExpressionOperator*)p;

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
        Output_Append(fp, options, TokenToString(((TBinaryExpression*)p)->token));
        TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
      }
    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;
      TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
      Output_Append(fp, options, "(");

      TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, fp);


      TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
      Output_Append(fp, options, ")");

      TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", fp);
    }
    break;

  default:

    ASSERT(false);
  }



}



static   void TEnumerator_CodePrint(TProgram* program, Options * options, TEnumerator* pTEnumerator, StrBuilder* fp)
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

static void TEnumSpecifier_CodePrint(TProgram* program, Options * options, TEnumSpecifier* p, StrBuilder* fp)
{
  //true;

  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, "enum");

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

static void TUnionSetItem_CodePrint(TProgram* program, Options * options, TUnionSetItem* p, StrBuilder* fp)
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

static void TUnionSet_CodePrint(TProgram* program, Options * options, TUnionSet* p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, "_union");

  TNodeClueList_CodePrint(options, &p->ClueList1, fp);
  Output_Append(fp, options, "(");
  TUnionSetItem* pCurrent = p->pHead;
  while (pCurrent)
  {
    TUnionSetItem_CodePrint(program, options, pCurrent, fp);
    pCurrent = pCurrent->pNext;
  }

  TNodeClueList_CodePrint(options, &p->ClueList2, fp);
  Output_Append(fp, options, ")");


}

static void TStructUnionSpecifier_CodePrint(TProgram* program, Options * options, TStructUnionSpecifier* p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);

  //true;

  if (p->Token == TK_STRUCT)
  {
    Output_Append(fp, options, "struct");
  }
  else if (p->Token == TK_UNION)
  {
    Output_Append(fp, options, "union");
  }

  if (p->Token2 == TK__UNION)
  {
    TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
  }
  TNodeClueList_CodePrint(options, &p->ClueList1, fp);

  if (options->bPrintRepresentation)
  {
    Output_Append(fp, options, " ");
  }

  Output_Append(fp, options, p->Name);


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

static void TSingleTypeSpecifier_CodePrint(TProgram* program, Options * options, TSingleTypeSpecifier* p, StrBuilder* fp)
{

  TNodeClueList_CodePrint(options, &p->ClueList0, fp);

  //true;
  if (p->Token != TK_IDENTIFIER)
  {
    Output_Append(fp, options,
      TokenToString(p->Token));
  }
  else
  {
    Output_Append(fp, options, p->TypedefName);
  }


}

static void TDesignator_CodePrint(TProgram* program, Options * options, TDesignator* p, StrBuilder* fp)
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

static void TInitializerList_CodePrint(TProgram* program,
  Options * options,
  TDeclarationSpecifiers* pDeclarationSpecifiers, //<- usadao para construir {}
  TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
  TInitializerList*p,

  StrBuilder* fp)
{
  if (List_HasOneItem(p) &&
    List_Back(p)->pInitializer == NULL/* &&
                                      pSpecifierQualifierList != NULL*/)
  {
    if (!options->bHideDefaultImplementation)
    {
      Output_Append(fp, options, "_default ");
    }
    //a partir de {} e um tipo consegue gerar o final  
    StrBuilder sb = STRBUILDER_INIT;
    bool bHasInitializers = false;
    InstanciateDestroy2(program,
      options,
      (TSpecifierQualifierList*)(pDeclarationSpecifiers),
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

static void TInitializerListType_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitializerListType*p,

  StrBuilder* fp)
{

  if (p->bDefault)
  {
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    TInitializer* pInitializer = NULL;
    //p->InitializerList.pHead ?
    //p->InitializerList.pHead->pInitializer : NULL;

    Output_Append(fp, options, "_default");
    Output_Append(fp, options, " {");
    if (options->bHideDefaultImplementation)
    {
    }
    else
    {
      StrBuilder sb = STRBUILDER_INIT;
      bool bHasInitializers = false;
      InstanciateDestroy2(program,
        options,
        (TSpecifierQualifierList*)(pDeclarationSpecifiers),
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
        Output_Append(fp, options, "0");
      }

      StrBuilder_Destroy(&sb);
    }
    Output_Append(fp, options, "}");
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


static void TInitializer_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitializer* pTInitializer,

  StrBuilder* fp)
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
      (TInitializerListType*)pTInitializer, fp);
  }
  else
  {
    TExpression_CodePrint(program, options, (TExpression*)pTInitializer, "", fp);
  }


}



static void TPointerList_CodePrint(TProgram* program, Options * options, TPointerList *p, StrBuilder* fp)
{
  ForEachListItem(TPointer, pItem, p)
  {
    TPointer_CodePrint(program, options, pItem, fp);
  }
}

static void TParameterList_CodePrint(TProgram* program, Options * options, TParameterList *p, StrBuilder* fp)
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

static void TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, StrBuilder* fp)
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
static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp);

static void TDirectDeclarator_CodePrint(TProgram* program, Options * options, TDirectDeclarator* pDirectDeclarator,

  bool bPrintName,
  StrBuilder* fp)
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

static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp)
{
  TPointerList_CodePrint(program, options, &p->PointerList, fp);
  TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}

//void TInitDeclarator_CodePrint(TProgram* program, 
//Options * options, 
//TI/nitDeclarator* p,    
//StrBuilder* fp);



void TStructDeclarator_CodePrint(TProgram* program,
  Options * options,
  TSpecifierQualifierList* pSpecifierQualifierList,
  TStructDeclarator* p,
  StrBuilder* fp)
{

  TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);
  if (p->pInitializer)
  {
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "_defval");

    Output_Append(fp, options, "(");

    Options options2 = *options;
    options2.bExpandMacros = true;
    options2.bIncludeComments = false;


    TInitializer_CodePrint(program,
      &options2,
      p->pDeclarator,
      (TDeclarationSpecifiers*)pSpecifierQualifierList,
      p->pInitializer,

      fp);
    Output_Append(fp, options, ")");
  }

}

static void TStructDeclaratorList_CodePrint(TProgram* program,
  Options * options,
  TSpecifierQualifierList* pSpecifierQualifierList,
  TStructDeclaratorList *p,
  StrBuilder* fp)
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

static void TStructDeclaration_CodePrint(TProgram* program,
  Options * options,
  TStructDeclaration* p,
  StrBuilder* fp)
{
  TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);
  TStructDeclaratorList_CodePrint(program,
    options,
    &p->SpecifierQualifierList,
    &p->DeclaratorList, fp);


  TNodeClueList_CodePrint(options, &p->ClueList1, fp);
  Output_Append(fp, options, ";");


}

static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp)
{
  switch (p->Type)
  {
  case TStructDeclaration_ID:
    TStructDeclaration_CodePrint(program, options, (TStructDeclaration*)p, fp);
    break;

  default:
    ASSERT(false);
    break;
  }


}

static void StorageSpecifier_CodePrint(TProgram* program, Options * options, TStorageSpecifier* p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, TokenToString(p->Token));
}

static void TFunctionSpecifier_CodePrint(TProgram* program, Options * options, TFunctionSpecifier* p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, TokenToString(p->Token));
}


static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);

  Output_Append(fp, options, TokenToString(p->Token));
#ifdef LANGUAGE_EXTENSIONS
  if (p->Token == TK__SIZE)
  {
    Output_Append(fp, options, "(");
    Output_Append(fp, options, p->SizeIdentifier);
    Output_Append(fp, options, ")");
  }
#endif
}

static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp)
{
  for (int i = 0; i < p->Size; i++)
  {
    TTypeQualifier* pItem = p->Data[i];
    TTypeQualifier_CodePrint(program, options, pItem, fp);
  }

}
static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp)
{

  TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
  Output_Append(fp, options, "*");

  TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, fp);



}

void TSpecifierQualifierList_CodePrint(TProgram* program,
  Options * options,
  TSpecifierQualifierList* pDeclarationSpecifiers,
  StrBuilder* fp)
{
  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TSpecifierQualifier* pItem = pDeclarationSpecifiers->pData[i];
    switch (pItem->Type)
    {

      CASE(TSingleTypeSpecifier) :
        TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
      break;

      CASE(TStorageSpecifier) :
        StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
      break;
      CASE(TTypeQualifier) :
        TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
      break;
      CASE(TFunctionSpecifier) :
        TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
      break;
      //CASE(TAlignmentSpecifier) : 
      ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
      //break;

      CASE(TStructUnionSpecifier) :
        TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
      break;

      CASE(TEnumSpecifier) :
        TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
      break;

    default:
      ASSERT(false);
      break;
    }
  }


}

void TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, StrBuilder* fp)
{

  for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
  {
    TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

    switch (pItem->Type)
    {

      CASE(TSingleTypeSpecifier) :
        TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
      break;

      CASE(TStructUnionSpecifier) :
        TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
      break;

      CASE(TEnumSpecifier) :
        TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
      break;

      CASE(TStorageSpecifier) :
        StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
      break;
      CASE(TTypeQualifier) :
        TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
      break;
      CASE(TFunctionSpecifier) :
        TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
      break;

      //CASE(TAlignmentSpecifier) : 
      ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
      //break;

    default:
      ASSERT(false);
      break;
    }
  }





}

void TInitDeclarator_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitDeclarator* p,
  StrBuilder* fp)
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



void TInitDeclaratorList_CodePrint(TProgram* program,
  Options * options,

  TDeclarationSpecifiers *pDeclarationSpecifiers,
  TInitDeclaratorList *p,

  StrBuilder* fp)
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



TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);


static bool FindListStructPattern(TProgram* program,
  TParameter* pParameter,
  bool* pbItemIsPointer,
  bool* pbItemIsAutoPointer,
  StrBuilder* itemTypeName,
  StrBuilder* arrayName)
{
  //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
  //ter size, capacity e um vector de items

  bool bHasHead = false;
  bool bHasTail = false;

  //O primeiro parametro tem que ser struct or typedef para struct
  TStructUnionSpecifier* pStructUnionSpecifier =
    GetStructSpecifier(program, &pParameter->Specifiers);
  if (pStructUnionSpecifier)
  {
    //Vou analisar a "digital" da struct
    //ok tem a definicao completa da struct
    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
    {
      TAnyStructDeclaration* pAnyStructDeclaration =
        pStructUnionSpecifier->StructDeclarationList.pItems[i];

      TStructDeclaration* pStructDeclaration =
        TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
      if (pStructDeclaration)
      {
        TStructDeclarator* pStructDeclarator =
          pStructDeclaration->DeclaratorList.pHead;

        while (pStructDeclarator)
        {
          const char* structDeclaratorName =
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

static bool FindVectorStructPattern(TProgram* program,
  TParameter* pParameter,
  bool* pbItemIsPointer,
  bool* pbItemIsAutoPointer,
  StrBuilder* itemTypeName,
  StrBuilder* arrayName)
{
  //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
  //ter size, capacity e um vector de items
  bool bHasVector = false;
  bool bHasSize = false;
  bool bHasCapacity = false;

  //O primeiro parametro tem que ser struct or typedef para struct
  TStructUnionSpecifier* pStructUnionSpecifier =
    GetStructSpecifier(program, &pParameter->Specifiers);
  if (pStructUnionSpecifier)
  {
    //Vou analisar a "digital" da struct
    //ok tem a definicao completa da struct
    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
    {
      TAnyStructDeclaration* pAnyStructDeclaration =
        pStructUnionSpecifier->StructDeclarationList.pItems[i];

      TStructDeclaration* pStructDeclaration =
        TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
      if (pStructDeclaration)
      {
        TStructDeclarator* pStructDeclarator =
          pStructDeclaration->DeclaratorList.pHead;

        while (pStructDeclarator)
        {
          const char* structDeclaratorName =
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
            TTypeName* pTypeName = NULL;
            Options  options = OPTIONS_INIT;
            options.bPrintRepresentation = true;
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
  const char* Name;
  const char* Value;
};

const char* FindValue(const char* name, int namesize, struct TemplateVar* args, int argssize)
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
  const char* tmpt,
  struct TemplateVar* vars,
  int size,
  int identationLevel)
{


  const char* pch = tmpt;

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
      const char* name = pch;
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

      const char* val =
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

void GetPrefixSuffix(const char* psz, StrBuilder* prefix, StrBuilder* suffix)
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

static int FindRuntimeID(TProgram* program,
  const char* structOrTypeName,
  StrBuilder* idname)
{
  ////////////
  TDeclaration * pFinalDecl =
    TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
  int typeInt = 0;
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;
  if (pFinalDecl)
  {
    typeInt = 1; //typefef
    if (pFinalDecl->Specifiers.Size > 1)
    {
      pStructUnionSpecifier =
        TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
      if (pStructUnionSpecifier->Name)
      {
        //procura a mais completa
        pStructUnionSpecifier =
          SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
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
    pStructUnionSpecifier->Token2 == TK__UNION)
  {
    if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
    {
      TStructDeclaration* pStructDeclaration =
        TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
      if (pStructDeclaration)
      {
        TStructDeclarator* pStructDeclarator =
          pStructDeclaration->DeclaratorList.pHead;

        //o primeiro item tem que ser o ID
        if (pStructDeclarator)
        {
          const char* structDeclaratorName =
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


static int FindIDValue(TProgram* program,
  const char* structOrTypeName,
  StrBuilder* idname)
{
  ////////////
  TDeclaration * pFinalDecl =
    TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
  int typeInt = 0;
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;
  if (pFinalDecl)
  {
    typeInt = 1; //typefef
    if (pFinalDecl->Specifiers.Size > 1)
    {
      pStructUnionSpecifier =
        TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
      if (pStructUnionSpecifier->Name)
      {
        //procura a mais completa
        pStructUnionSpecifier =
          SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
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
      TStructDeclaration* pStructDeclaration =
        TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
      if (pStructDeclaration)
      {
        TStructDeclarator* pStructDeclarator =
          pStructDeclaration->DeclaratorList.pHead;

        //o primeiro item tem que ser o ID
        if (pStructDeclarator)
        {
          const char* structDeclaratorName =
            TDeclarator_GetName(pStructDeclarator->pDeclarator);
          //if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
          {
            Options options2 = OPTIONS_INIT;
            TInitializer_CodePrint(program, &options2, pStructDeclarator->pDeclarator,
              (TDeclarationSpecifiers*)&pStructDeclaration->SpecifierQualifierList,
              pStructDeclarator->pInitializer, idname);

            //StrBuilder_Set(idname, structDeclaratorName);
          }
        }
      }
    }
  }
  return typeInt;
}


void FindUnionSetOf(TProgram* program,
  const char* structOrTypeName,
  Map2* map)
{
  TDeclaration * pFinalDecl =
    TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
  int typeInt = 0;
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;
  if (pFinalDecl)
  {
    typeInt = 1; //typefef
    if (pFinalDecl->Specifiers.Size > 1)
    {
      pStructUnionSpecifier =
        TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
      if (pStructUnionSpecifier->Name)
      {
        //procura a mais completa
        pStructUnionSpecifier =
          SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
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
    pStructUnionSpecifier->Token2 == TK__UNION)
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
    void *pp;
    Map2_SetAt(map, structOrTypeName, (void*)typeInt, &pp);
  }
}

void UnionTypeDefault(TProgram* program,
  Options* options,
  const char* structName,
  TParameterTypeList * pArgsOpt, //parametros
  const char* parameterName,
  const char* functionSuffix,
  StrBuilder* fp);
static const char* GetNullStr(TProgram* program);

static void DefaultFunctionDefinition_CodePrint(TProgram* program,
  Options * options,
  TDeclaration* p,
  StrBuilder* fp)
{

  //Retorno da funcao
  TDeclarationSpecifiers* pSpecifiers =
    &p->Specifiers;

  const char* funcName =
    TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

  StrBuilder functionPrefix = STRBUILDER_INIT;
  StrBuilder functionSuffix = STRBUILDER_INIT;

  GetPrefixSuffix(funcName, &functionPrefix, &functionSuffix);

  //parametros


  TParameterTypeList * pArgs =
    TDeclaration_GetFunctionArguments(p);

  TParameter* pFirstParameter =
    TParameterTypeList_GetParameterByIndex(pArgs, 0);

  TParameter* pSecondParameter =
    TParameterTypeList_GetParameterByIndex(pArgs, 1);


  if (IsSuffix(funcName, "_Create"))
  {
    options->IdentationLevel++;

    InstanciateDestroy2(program,
      options,
      (TSpecifierQualifierList*)(pSpecifiers),
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
  else if (IsSuffix(funcName, "_Init") && pFirstParameter != NULL)
  {
    options->IdentationLevel++;
    InstanciateDestroy2(program,
      options,
      (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
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
  else if (IsSuffix(funcName, "_Destroy") && pFirstParameter != NULL)
  {

    options->IdentationLevel++;
    InstanciateDestroy2(program,
      options,
      (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
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
  else if (IsSuffix(funcName, "_Delete") && pFirstParameter != NULL)
  {

    options->IdentationLevel++;
    InstanciateDestroy2(program,
      options,
      (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
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
    if (pFirstParameter != NULL &&
      pSecondParameter != NULL &&
      IsSuffix(funcName, "_Reserve"))
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
        const char* pszTemplatePointer =
          "if ($nelements > $p->Capacity)\n"
          "{\n"
          " $type** pnew = $p->$data;\n"
          " pnew = ($type**)realloc(pnew, $nelements * sizeof($type*));\n"
          " if (pnew)\n"
          " {\n"
          "  $p->$data = pnew;\n"
          "  $p->Capacity = $nelements;\n"
          " }\n"
          "}\n";

        const char* pszTemplateNotPointer =
          "if ($nelements > $p->Capacity)\n"
          "{\n"
          " $type* pnew = $p->$data;\n"
          " pnew = ($type*)realloc(pnew, $nelements * sizeof($type));\n"
          " if (pnew)\n"
          " {\n"
          "  $p->$data = pnew;\n"
          "  $p->Capacity = $nelements;\n"
          " }\n"
          "}\n";

        const char* pszTemplate =
          bItemIsPointer ? pszTemplatePointer : pszTemplateNotPointer;

        struct TemplateVar vars[] = {
          { "p", TParameter_GetName(pFirstParameter) },
          { "nelements", TParameter_GetName(pSecondParameter) },
          { "type", itemType.c_str },
          { "data", arrayName.c_str }
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
    else if (pFirstParameter != NULL &&
      pSecondParameter != NULL &&
      IsSuffix(funcName, "_PushBack"))
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
        bool bHasReserve =
          SymbolMap_FindObjFunction(&program->GlobalScope, functionPrefix.c_str, "Reserve") != 0;
        const char* pszTemplate = "";

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
          pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
            "{\n"
            " int n = $p->Capacity * 2;\n"
            " if (n == 0)\n"
            " {\n"
            "  n = 1;\n"
            " }\n"
            " $type** pnew = $p->data;\n"
            " pnew = ($type**)realloc(pnew, n * sizeof($type*));\n"
            " if (pnew)\n"
            " {\n"
            "  $p->data = pnew;\n"
            "  $p->Capacity = n;\n"
            " }\n"
            "}\n"
            "$p->$data[$p->Size] = $nelements;\n"
            "$p->Size++;\n";
        }

        struct TemplateVar vars[] = {
          { "p", TParameter_GetName(pFirstParameter) },
          { "nelements", TParameter_GetName(pSecondParameter) },
          { "type", itemType.c_str },
          { "data", arrayName.c_str },
          { "prefix", functionPrefix.c_str }
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
          { "null", GetNullStr(program) }
        };
        //o item apontado tem que ter pNext verificar isso
        //e colocar erro se nao tiver
        const char* pszTemplate =
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
        TStructUnionSpecifier* pStructUnionSpecifier =
          GetStructSpecifier(program, &pFirstParameter->Specifiers);
        if (pStructUnionSpecifier &&
          pStructUnionSpecifier->Token2 == TK__UNION)
        {
          options->IdentationLevel++;
          UnionTypeDefault(program,
            options,
            pStructUnionSpecifier->Name,
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

static void TDeclaration_CodePrint(TProgram* program,
  Options * options,
  TDeclaration* p,

  StrBuilder* fp)
{
  TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);

  TInitDeclaratorList_CodePrint(program,
    options,
    &p->Specifiers,
    &p->InitDeclaratorList, fp);

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
      StrBuilder_Append(fp, "_default");

      if (options->bHideDefaultImplementation)
      {
        Output_Append(fp, options, ";");
      }
      else
      {
        TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
        Output_Append(fp, options, "{\n");

        DefaultFunctionDefinition_CodePrint(program,
          options,
          p,

          fp);

        Output_Append(fp, options, "}");

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

      if (!options->bHideDefaultImplementation)
      {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        StrBuilder_Append(fp, "_default");

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "\n{\n");

        DefaultFunctionDefinition_CodePrint(program,
          options,
          p,

          fp);

        Output_Append(fp, options, "}");
      }
      else
      {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        StrBuilder_Append(fp, " _default");
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

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp)
{

  TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);

  TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);


}

static void TParameter_CodePrint(TProgram* program,
  Options * options,
  TParameter* p,

  StrBuilder* fp)
{
  TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
  TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);

  if (p->bHasComma)
  {
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, ",");
  }


}

static void TEofDeclaration_CodePrint(TProgram* program,
  Options * options,
  TEofDeclaration *p,

  StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);

}

static void TStaticAssertDeclaration_CodePrint(TProgram* program,
  Options * options,
  TStaticAssertDeclaration *p,

  StrBuilder* fp)
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

static void TGroupDeclaration_CodePrint(TProgram* program, Options * options, TGroupDeclaration *p, StrBuilder* fp)
{
  TNodeClueList_CodePrint(options, &p->ClueList0, fp);
  Output_Append(fp, options, "#pragma region cprime");
  TNodeClueList_CodePrint(options, &p->ClueList1, fp);
  Output_Append(fp, options, p->Identifier);
  TNodeClueList_CodePrint(options, &p->ClueList2, fp);
  Output_Append(fp, options, "\n");

  TDeclaration* pFunction =
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
        const char* derivedName = (const char*)map.pHashTable[i]->Key;
        const char* baseName = p->Identifier;

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
    Map2_Destroy(&map);
    StrBuilder_Destroy(&idname);

  }

  //for (int i = 0; i < p->Declarations.Size; i++)
  //{
  //TAnyDeclaration_CodePrint(program, options, p->Declarations.pItems[i], fp);
  //}
  //TNodeClueList_CodePrint(options, &p->ClueList1, fp);
  Output_Append(fp, options, "#pragma endregion cprime\n");
}

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp)
{
  switch (pDeclaration->Type)
  {
  case TGroupDeclaration_ID:
    TGroupDeclaration_CodePrint(program, options, (TGroupDeclaration*)pDeclaration, fp);
    break;

  case TEofDeclaration_ID:
    TEofDeclaration_CodePrint(program, options, (TEofDeclaration*)pDeclaration, fp);
    break;

  case TStaticAssertDeclaration_ID:
    TStaticAssertDeclaration_CodePrint(program, options, (TStaticAssertDeclaration*)pDeclaration, fp);
    break;

  case TDeclaration_ID:
    TDeclaration_CodePrint(program, options, (TDeclaration*)pDeclaration, fp);
    break;

  default:
    ASSERT(false);
    break;
  }


}

static void TDesignatorList_CodePrint(TProgram* program, Options * options, TDesignatorList *p, StrBuilder* fp)
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


static void TInitializerListItem_CodePrint(TProgram* program,
  Options * options,
  TDeclarator* pDeclarator,
  TDeclarationSpecifiers* pDeclarationSpecifiers,
  TInitializerListItem* p,

  StrBuilder* fp)
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
}



void TProgram_PrintCodeToFile(TProgram* pProgram,
  Options* options,
  const char* outFileName,
  const char* inputFileName)
{
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
    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

    StrBuilder_Clear(&pProgram->sbPreDeclaration);

    StrBuilder sbDeclaration = STRBUILDER_INIT;
    TAnyDeclaration_CodePrint(pProgram, options, pItem, &sbDeclaration);

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

void TProgram_PrintCodeToString(TProgram* pProgram,
  Options* options,
  StrBuilder* output)
{

  int k = 0;


  StrBuilder sb = STRBUILDER_INIT;
  StrBuilder_Reserve(&sb, 80 * 5000);

  for (int i = 0; i < pProgram->Declarations.Size; i++)
  {
    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

    StrBuilder_Clear(&pProgram->sbPreDeclaration);

    StrBuilder sbDeclaration = STRBUILDER_INIT;
    TAnyDeclaration_CodePrint(pProgram, options, pItem, &sbDeclaration);

    StrBuilder_Append(&sb, pProgram->sbPreDeclaration.c_str);
    StrBuilder_Append(&sb, sbDeclaration.c_str);

    StrBuilder_Destroy(&sbDeclaration);

    StrBuilder_Append(output, sb.c_str);


    StrBuilder_Clear(&sb);
    k++;
  }
  StrBuilder_Destroy(&sb);

}


static const char* GetFreeStr(TProgram* program)
{
  TDeclaration* pDeclarationDestroy =
    SymbolMap_FindFunction(&program->GlobalScope,
      "Free");

  return pDeclarationDestroy ? "Free" : "free";
}

static const char* GetMallocStr(TProgram* program)
{
  TDeclaration* pDeclarationDestroy =
    SymbolMap_FindFunction(&program->GlobalScope,
      "Malloc");

  return pDeclarationDestroy ? "Malloc" : "malloc";
}


static const char* GetFalseStr(TProgram* program)
{
  bool bHasFalse =
    MacroMap_Find(&program->Defines, "false") != NULL;

  return bHasFalse ? "false" : "0";
}

static const char* GetNullStr(TProgram* program)
{
  bool bHasFalse =
    MacroMap_Find(&program->Defines, "NULL") != NULL;

  return bHasFalse ? "NULL" : "0";
}



static void PrintIfNotNullLn(TProgram* program,
  Options* options,
  const char* pInitExpressionText, //(x->p->i = 0)    
  StrBuilder* fp)
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


static bool FindHighLevelFunction(TProgram* program,
  Options* options,
  TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
  TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
  TParameterTypeList * pArgsOpt, //parametros do create /init
  TInitializer* pInitializerOpt,
  const char* pInitExpressionText, //(x->p->i = 0)    
  const char* pszAutoPointerLenExpressionOpt,
  const Action action,
  Search search,
  const char* nameToFind,
  StrBuilder* fp)
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
          TDeclaration* pDeclarationDestroy =
            SymbolMap_FindObjFunction(&program->GlobalScope,
              nameToFind,
              "Delete");
          if (pDeclarationDestroy)
          {
            if (bIsAutoPointerToObject)
            {
              StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                "%s_Delete(%s);",
                nameToFind,
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
                  "%s_Delete(%s[i]);",
                  nameToFind,
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
                  "%s_Delete(%s[0]);",
                  nameToFind,
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
              TDeclaration* pDeclarationDestroy2 =
                SymbolMap_FindObjFunction(&program->GlobalScope,
                  nameToFind,
                  "Destroy");
              if (pDeclarationDestroy2)
              {
                if (bIsAutoPointerToObject)
                {
                  StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "%s_Destroy(%s);",
                    nameToFind,
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
                      "%s_Destroy(%s[i]);",
                      nameToFind,
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
                      "%s_Destroy(%s[0]);",
                      nameToFind,
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
                      "%s_Destroy(%s[i]);",
                      nameToFind,
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
                      "%s_Destroy(%s[0]);",
                      nameToFind,
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
          //vamos procurar pela funcao conceito _Destroy
          TDeclaration* pDeclarationDestroy =
            SymbolMap_FindObjFunction(&program->GlobalScope,
              nameToFind,
              "Destroy");
          if (pDeclarationDestroy)
          {
            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
              "%s_Destroy(&%s);",
              nameToFind,
              pInitExpressionText);
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
      TDeclaration* pDeclarationDestroy =
        SymbolMap_FindObjFunction(&program->GlobalScope,
          nameToFind,
          "Delete");
      if (pDeclarationDestroy)
      {
        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
          "%s_Delete(%s);",
          nameToFind,
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
          TDeclaration* pDeclarationDestroy2 =
            SymbolMap_FindObjFunction(&program->GlobalScope,
              nameToFind,
              "Destroy");
          if (pDeclarationDestroy2)
          {
            StrBuilder_AppendFmtLn(fp, 4 * 1,
              "%s_Destroy(%s);",
              nameToFind,
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
        TDeclaration* pDeclarationDestroy =
          SymbolMap_FindObjFunction(&program->GlobalScope,
            nameToFind,
            "Destroy");
        if (pDeclarationDestroy)
        {
          PrintIfNotNullLn(program, options, pInitExpressionText, fp);



          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "{");

          options->IdentationLevel++;
          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "%s_Destroy(%s);",
            nameToFind,
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
        TDeclaration* pDeclarationInit =
          SymbolMap_FindObjFunction(&program->GlobalScope,
            nameToFind,
            "Init");
        if (pDeclarationInit)
        {
          StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
            "%s_Init(&%s",
            nameToFind,
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
      TDeclaration* pDeclarationInit =
        SymbolMap_FindObjFunction(&program->GlobalScope,
          nameToFind,
          "Init");
      if (pDeclarationInit)
      {

        if (bIsPointer)
        {
          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "%s_Init(%s);",
            nameToFind,
            pInitExpressionText);
        }
        else
        {
          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "%s_Init(&%s);",
            nameToFind,
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
      TDeclaration* pDeclarationInit =
        SymbolMap_FindObjFunction(&program->GlobalScope,
          nameToFind,
          "Init");
      if (pDeclarationInit)
      {
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
          "%s_Init(p",
          nameToFind);

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
      Options options2 = *options;
      TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);

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
static bool IsVector(TStructUnionSpecifier* pStructUnionSpecifier)
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
      TAnyStructDeclaration* pAnyStructDeclaration =
        pStructUnionSpecifier->StructDeclarationList.pItems[i];

      TStructDeclaration* pStructDeclaration =
        TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
      if (pStructDeclaration)
      {
        TStructDeclarator* pStructDeclarator =
          pStructDeclaration->DeclaratorList.pHead;

        while (pStructDeclarator)
        {
          const char* structDeclaratorName =
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

void UnionTypeDefault(TProgram* program,
  Options* options,
  const char* structName,
  TParameterTypeList * pArgsOpt, //parametros
  const char* parameterName0,
  const char* functionSuffix,
  StrBuilder* fp)
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
        (const char*)map.pHashTable[i]->Key,
        &idvalue);

      struct TemplateVar vars[] = {
        { "type", (const char*)map.pHashTable[i]->Key },
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

  Map2_Destroy(&map);
}

void InstanciateDestroy2(TProgram* program,
  Options* options,
  TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
  TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
  TInitializer* pInitializerOpt, //usado para inicializacao estatica
  TParameterTypeList * pArgsOpt, //parametros do create /init
  const char* pInitExpressionText, //(x->p->i = 0)    
  const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                              //se passar null eh pq nao interessa
  const Action action,
  Search search,
  bool* pbHasInitializers,
  StrBuilder* fp)
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

  TDeclarationSpecifier* pMainSpecifier =
    TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

  if (pMainSpecifier == NULL)
  {
    //error
    return;
  }

  if (pMainSpecifier->Type == TSingleTypeSpecifier_ID)
  {
    TSingleTypeSpecifier* pSingleTypeSpecifier =
      (TSingleTypeSpecifier*)pMainSpecifier;

    if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
    {
      bool bComplete = false;
      TDeclarator declarator;
      TDeclarator_Init(&declarator);
      //Pode ter uma cadeia de typdefs
      //ele vai entrandando em cada uma ...
      //ate que chega no fim recursivamente
      //enquanto ele vai andando ele vai tentando
      //algo com o nome do typedef
      TDeclarationSpecifiers* pDeclarationSpecifiers =
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

          TDeclaration* pDeclarationInit =
            SymbolMap_FindObjFunction(&program->GlobalScope,
              pSingleTypeSpecifier->TypedefName,
              "Init");

          if (pDeclarationInit)
          {
            StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
              "%s_Init(p",
              pSingleTypeSpecifier->TypedefName);

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
              (TSpecifierQualifierList*)pDeclarationSpecifiers,
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
              (TSpecifierQualifierList*)pDeclarationSpecifiers,
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
        ASSERT(false);
      }

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
          Options options2 = *options;
          TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
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
          Options options2 = *options;
          TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
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
    TStructUnionSpecifier* pStructUnionSpecifier =
      (TStructUnionSpecifier*)pMainSpecifier;

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
      pStructUnionSpecifier->Name,
      fp);

    //Exemplos
    //struct Y *pY e � para destruir o conteudo
    //struct Y *pY e NAO � para destruir o conteudo
    //struct Y * auto pY; e � para destruir o conteudo ou nao
    //struct Y y; //eh para destruir o conteudo
    if (!bComplete) //se for para entrar na struct
    {
      if (pStructUnionSpecifier &&
        pStructUnionSpecifier->Name != NULL)
      {
        //se nao eh completa tenta achar
        //vou procurar a definicao completa da struct
        pStructUnionSpecifier =
          SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
      }

      bool bIsUnionTypes = pStructUnionSpecifier &&
        pStructUnionSpecifier->Token2 == TK__UNION;


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
              //ASSERT(false);
            }

          }

        }
        else if (action == ActionCreate)
        {
          //struct sem nome tem que ser criada
          //com typedef que chama outro codigo
          ASSERT(pStructUnionSpecifier->Name != NULL);

          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "struct %s* p = (struct %s*) %s(sizeof * p);",
            pStructUnionSpecifier->Name,
            pStructUnionSpecifier->Name,
            GetMallocStr(program));

          PrintIfNotNullLn(program, options, pInitExpressionText, fp);
          StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
            "{");
          options->IdentationLevel++;
        }
        else if (action == ActionStaticInit)
        {
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
              pStructUnionSpecifier->Name,
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
              pStructUnionSpecifier->Name,
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
          //ok tem a definicao completa da struct
          for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
          {



            if (action == ActionStaticInit && i > 0)
            {
              StrBuilder_Append(fp, ", ");
            }

            TAnyStructDeclaration* pAnyStructDeclaration =
              pStructUnionSpecifier->StructDeclarationList.pItems[i];

            TStructDeclaration* pStructDeclaration =
              TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

            if (pStructDeclaration != NULL)
            {
              TStructDeclarator* pStructDeclarator =
                pStructDeclaration->DeclaratorList.pHead;

              StrBuilder strVariableName = STRBUILDER_INIT;
              StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


              while (pStructDeclarator)
              {
                //O padrao eh ser o inicializador do tipo
                TInitializer* pStructMemberInitializer =
                  pStructDeclarator->pInitializer;

                TPrimaryExpressionValue initializerExpression;
                TPrimaryExpressionValue_Init(&initializerExpression);


                StrBuilder_Clear(&strVariableName);
                StrBuilder_Clear(&strPonterSizeExpr);

                const char* structDeclaratorName =
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

                  TParameter* pParameter = NULL;
                  if (pArgsOpt)
                  {
                    pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                    if (pParameter != NULL)
                    {
                      pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                      initializerExpression.token = TK_IDENTIFIER;
                      String_Set(&initializerExpression.lexeme, structDeclaratorName);
                    }
                  }

                  action2 = ActionInit;
                }
                else if (action == ActionCreate)
                {
                  TParameter* pParameter = NULL;
                  if (pArgsOpt)
                  {
                    pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                    if (pParameter != NULL)
                    {
                      pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                      initializerExpression.token = TK_IDENTIFIER;
                      String_Set(&initializerExpression.lexeme, structDeclaratorName);
                    }
                  }

                  action2 = ActionInit;
                }

                if (action2 == ActionDestroy)
                {

                  //Tem que detectar isso aqui!
                  // String * _auto pItems;
                  // X * _auto * _auto pItems;
                  //sef or ele vai precisar da informacao do _size
                  // X * _auto * _auto _size(Size) pItems;
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
    TEnumSpecifier *pEnumSpecifier =
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
        ASSERT(false);
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
        Options options2 = *options;
        TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
        StrBuilder_Append(fp, ";\n");
      }
      else
      {
        //TODO achar a definicao completa do enum
        const char* firstValue =
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
        Options options2 = *options;
        TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
        StrBuilder_Append(fp, ";");
      }
      else
      {
        //TODO achar a definicao completa do enum
        const char* firstValue =
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
        Options options2 = *options;
        TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
      }
      else
      {
        //TODO achar a definicao completa do enum
        const char* firstValue =
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
    ASSERT(false);
  }

}



bool IsSuffix(const char* s, const char* suffix)
{
  bool bResult = false;
  int len = strlen(s);
  int len2 = strlen(suffix);
  if (len > len2)
  {
    const char* pEndPart = &s[len - len2];
    if (strcmp(pEndPart, suffix) == 0)
    {
      bResult = true;
    }
  }
  return bResult;

}

TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers)
{
  if (specifiers == NULL)
    return NULL;

  TStructUnionSpecifier* pTStructUnionSpecifier =
    TDeclarationSpecifier_As_TStructUnionSpecifier(specifiers->pData[0]);

  if (pTStructUnionSpecifier == NULL)
  {
    TSingleTypeSpecifier *pSingleTypeSpecifier =
      TDeclarationSpecifier_As_TSingleTypeSpecifier(specifiers->pData[0]);

    if (pSingleTypeSpecifier != NULL &&
      pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
    pTStructUnionSpecifier->Name != NULL)
  {
    pTStructUnionSpecifier =
      SymbolMap_FindStructUnion(&program->GlobalScope, pTStructUnionSpecifier->Name);
  }


  return pTStructUnionSpecifier;
}




#include <time.h>  

void AllTests();


void AstPlayground(TProgram* program);

void Compile(const char* configFileName,
  const char* inputFileName,
  const char* outputFileName,
  Options* options,
  bool bPrintASTFile)
{
  TProgram program;
  TProgram_Init(&program);

  clock_t tstart = clock();

  printf("Parsing...\n");
  if (GetAST(inputFileName, configFileName, &program))
  {

    AstPlayground(&program);

    char drive[CPRIME_MAX_DRIVE];
    char dir[CPRIME_MAX_DIR];
    char fname[CPRIME_MAX_FNAME];
    char ext[CPRIME_MAX_EXT];
    SplitPath(inputFileName, drive, dir, fname, ext); // C4996


    printf("Generating code for %s...\n", inputFileName);
    if (outputFileName)
    {
      if (bPrintASTFile)
      {
        TProgram_PrintAstToFile(&program, outputFileName, inputFileName);
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
        MakePath(outc, drive, dir, fname, ".json");
        TProgram_PrintAstToFile(&program, outc, inputFileName);
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
}

void PrintHelp()
{
  printf("Syntax: cprime [options] [file ...]\n");
  printf("\n");
  printf("Examples: cprime hello.c\n");
  printf("          cprime -config config.h hello.c\n");
  printf("          cprime -config config.h hello.c -o hello.c\n");
  printf("          cprime -config config.h -P hello.c\n");
  printf("          cprime -E hello.c\n");
  printf("          cprime -P hello.c\n");
  printf("          cprime -A hello.c\n");
  printf("\n");
  printf("Options:\n");
  printf("-config FILE                          Configuration file.\n");
  printf("-help                                 Print this message.\n");
  printf("-o FILE                               Sets ouput file name.\n");
  printf("-E                                    Preprocess to console.\n");
  printf("-P                                    Preprocess to file.\n");
  printf("-A                                    Output AST to file.\n");
  printf("-r                                    Reverts generation.\n");

}

EMSCRIPTEN_KEEPALIVE

char* EMSCRIPTEN_KEEPALIVE myFunction(int argc, char * input) 
{
/*  printf("MyFunction Called %s\n", argv);
  char* p = malloc(500);

  strcpy(p, argv);
  strcat(p, "\ntext added by C function\n");

  return p;*/

  printf("compile");
  TProgram program;
  TProgram_Init(&program);
  if (GetASTFromString(input,
    &program))
  {
    Options options2 = OPTIONS_INIT;
    options2.bHideDefaultImplementation = false;


    StrBuilder output = STRBUILDER_INIT;
    TProgram_PrintCodeToString(&program,
      &options2, &output);
    return output.c_str;
    //StrBuilder_Destroy(&output);
  }
  return 0;

}

char * CompileText(char* input)
{
  printf("compile");
  TProgram program;
  TProgram_Init(&program);
  if (GetASTFromString(input,
    &program))
  {
    Options options2 = OPTIONS_INIT;
    options2.bHideDefaultImplementation = false;


    StrBuilder output = STRBUILDER_INIT;
    TProgram_PrintCodeToString(&program,
      &options2, &output);
    return output.c_str;
    //StrBuilder_Destroy(&output);
  }
  return 0;
}

int main(int argc, char* argv[])
{
  printf("\n");
  printf("C' Version " __DATE__ "\n");
  printf("https://github.com/thradams/CPrime\n\n");

#ifdef _DEBUG
  AllTests();
#endif
  if (argc < 2)
  {
    PrintHelp();
    return 1;
  }

  const char* configFileName = NULL;

  String outputFullPath = NULL;
  String inputFullPath = NULL;

  Options options = OPTIONS_INIT;
  options.bHideDefaultImplementation = false;

  bool bPrintPreprocessedToFile = false;
  bool bPrintPreprocessedToConsole = false;
  bool bPrintASTFile = false;

  clock_t tstart = clock();

  int numberOfFiles = 0;
  //a primeira fase � para recolher opcoes
  //a segunda eh para processar arquivos
  for (int fase = 0; fase < 2; fase++)
  {
    for (int i = 1; i < argc; i++)
    {
      const char * option = argv[i];
      if (strcmp(option, "-P") == 0)
      {
        bPrintPreprocessedToFile = true;
      }
      else if (strcmp(option, "-E") == 0)
      {
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
      else if (strcmp(option, "-help") == 0)
      {
        if (fase == 1)
        {
          PrintHelp();
        }
      }
      else if (strcmp(option, "-s") == 0)
      {
        options.bHideDefaultImplementation = true;
      }
      else if (strcmp(option, "-config") == 0)
      {
        if (fase == 0)
        {
          if (i + 1 < argc)
          {
            configFileName = argv[i + 1];
          }
          else
          {
            printf("missing file\n");
            break;
          }
        }
        i++;
      }
      else if (strcmp(option, "-o") == 0)
      {
        if (i + 1 < argc)
        {
          GetFullPath(argv[i + 1], &outputFullPath);
          i++;
        }
        else
        {
          printf("missing file\n");
        }
      }
      else
      {
        if (fase == 1)
        {
          //const char* inputFileName = option;
          //String inputFullPath = NULL;
          GetFullPath(option, &inputFullPath);

          if (bPrintPreprocessedToFile)
          {
            PrintPreprocessedToFile(inputFullPath, configFileName);
          }
          else if (bPrintPreprocessedToConsole)
          {
            PrintPreprocessedToConsole(inputFullPath, configFileName);
          }
          else
          {
            Compile(configFileName, inputFullPath, outputFullPath, &options, bPrintASTFile);
          }
        }
        else
        {
          numberOfFiles++;
        }
      }

    }
  }

  clock_t tend = clock();
  printf("Total %d files in = %d seconds\n", numberOfFiles, (int)((tend - tstart) / CLOCKS_PER_SEC));

  String_Destroy(&outputFullPath);
  String_Destroy(&inputFullPath);

  return 0;
}



bool EachStructDeclarator(TStructUnionSpecifier* pStruct,
  int *i,
  TSpecifierQualifierList **ppSpecifierQualifierList,
  TStructDeclarator** ppStructDeclarator)
{
  /*
  Exemplo:
  TSpecifierQualifierList *pSpecifierQualifierList = NULL;
  TStructDeclarator* pStructDeclarator = NULL;
  int i = 0;
  while (EachStructDeclarator(pStruct, &i, &pSpecifierQualifierList, &pStructDeclarator))
  {
  printf("%s\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
  }
  */
  if (*ppStructDeclarator != NULL)
  {
    goto Continue;
  }

  for (; *i < pStruct->StructDeclarationList.Size; (*i)++)
  {
    TAnyStructDeclaration* pAnyStructDeclaration =
      pStruct->StructDeclarationList.pItems[*i];

    TStructDeclaration* pStructDeclaration =
      TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

    if (pStructDeclaration != NULL)
    {
      *ppSpecifierQualifierList =
        &pStructDeclaration->SpecifierQualifierList;
      *ppStructDeclarator =
        pStructDeclaration->DeclaratorList.pHead;

      while (*ppStructDeclarator != NULL)
      {
        return true;
      Continue:
        *ppStructDeclarator = (*ppStructDeclarator)->pNext;
      }
    }
  }
  return false;
}



void AstPlayground(TProgram* program)
{

  // SymbolMap_Print(&program->GlobalScope);

  // TStructUnionSpecifier* p =
  //     SymbolMap_FindStructUnion(&program->GlobalScope, "X");


  // TTypeSpecifier* p2 = 
  //    SymbolMap_FindTypedefSpecifierTarget(&program->GlobalScope, "Y");
  //find struct X
  //find X
}



void LocalStrBuilder_Init(LocalStrBuilder* p)
{
  p->capacity = LOCALSTRBUILDER_NCHARS;
  p->size = 0;
  p->c_str = p->chars;
}

void LocalStrBuilder_Swap(LocalStrBuilder* pA, LocalStrBuilder* pB)
{
  int bA = (pA->c_str == pA->chars);
  int bB = (pB->c_str == pB->chars);

  LocalStrBuilder temp = *pA;
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

void LocalStrBuilder_Destroy(LocalStrBuilder* p)
{
  if (p->c_str != p->chars)
  {
    free(p->c_str);
  }
}

void LocalStrBuilder_Reserve(LocalStrBuilder* p, int nelements)
{
  if (nelements > p->capacity)
  {
    char* pnew = NULL;
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
        pnew = (char*)malloc((nelements + 1) * sizeof(char));
        memcpy(pnew, p->chars, LOCALSTRBUILDER_NCHARS);
      }
      else
      {
        pnew = (char*)realloc(p->c_str, (nelements + 1) * sizeof(char));
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

void LocalStrBuilder_Print(LocalStrBuilder* p)
{
  printf("size = %d, capacity = %d, c_str = '%s', internal buffer = %s \n",
    (int)p->size,
    (int)p->capacity,
    p->c_str,
    (p->c_str == p->chars ? "yes" : "no"));
}

void LocalStrBuilder_Clear(LocalStrBuilder* p)
{
  if (p->c_str)
  {
    p->c_str[0] = 0;
  }
  p->size = 0;
}

void LocalStrBuilder_Grow(LocalStrBuilder* p, int nelements)
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

void LocalStrBuilder_Append(LocalStrBuilder* p, const char* source)
{
  while (*source)
  {
    LocalStrBuilder_AppendChar(p, *source);
    source++;
  }
}


void LocalStrBuilder_Set(LocalStrBuilder* p, const char* source)
{
  LocalStrBuilder_Clear(p);
  while (*source)
  {
    LocalStrBuilder_AppendChar(p, *source);
    source++;
  }
}



void LocalStrBuilder_AppendChar(LocalStrBuilder* p, char ch)
{
  LocalStrBuilder_Grow(p, p->size + 1);

  p->c_str[p->size] = ch;
  p->c_str[p->size + 1] = 0;
  p->size++;
}

/*
based on
https://github.com/dspinellis/cscout/blob/084d64dc7a0c5466dc2d505c1ca16fb303eb2bf1/src/macro.cpp
*/





Macro* Macro_Create(void) _default
{
  Macro *p = (Macro*)malloc(sizeof * p);
  if (p != NULL)
  {
    String_Init(&p->Name);
    p->bIsFunction = false;
    TokenArray_Init(&p->TokenSequence);
    TokenArray_Init(&p->FormalArguments);
    p->FileIndex = 0;
  }
  return p;
}

void Macro_Destroy(Macro * p) _default
{
  String_Destroy(&p->Name);
  TokenArray_Destroy(&p->TokenSequence);
  TokenArray_Destroy(&p->FormalArguments);
}

void Macro_Delete(Macro * p) _default
{
  if (p != NULL)
  {
    Macro_Destroy(p);
    free((void*)p);
  }
}


bool FillIn(TokenArray* ts,
  bool get_more,
  TokenArray* removed);

void Glue(const TokenArray* lsI,
  const TokenArray* rsI,
  TokenArray* out);

// Return a new token sequence with hs added to the hide set of every element of ts
void HidenSetAdd(const TokenSet* hs,
  const TokenArray* ts,
  TokenArray* pOut)
{
  TokenArray_Clear(pOut);


  for (int i = 0; i < ts->Size; i++)
  {
    PPToken* t = ts->pItems[i];

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

void ExpandMacro(const TokenArray* pTokenSequence,
  const MacroMap* macros,
  bool get_more,
  bool skip_defined,
  bool evalmode,
  Macro* caller,
  TokenArray* pOutputSequence);

/*
Retorna o indice do primeiro token que não for espaço
a partir e incluindo o indice start.
Return -1 se não achar.
*/
int FindNoSpaceIndex(const TokenArray* pArray, int start)
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
void AppendEscaped(StrBuilder* strBuilder,
  const char* source)
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
void AppendStringize(StrBuilder* strBuilder, const TokenArray* ts)
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
    PPToken* pToken = ts->pItems[i];

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
void SubstituteArgs(Macro *pMacro,
  const MacroMap* macros,
  const TokenArray* isOriginal,   //macro
  const TokenArrayMap *args,
  TokenSet* hs,
  bool skip_defined,
  bool evalmode,
  Macro *pCaller,
  TokenArray* pOutputSequence)
{
  TokenArray_Clear(pOutputSequence);

  //Trabalha com uma copia
  TokenArray is = TOKENARRAY_INIT;
  TokenArray_AppendCopy(&is, isOriginal);

  TokenArray os = TOKENARRAY_INIT;

  while (is.Size > 0)
  {

    //printf("subst: is=");
    TokenArray_Print(&is);
    //printf(" os=");
    TokenArray_Print(&os);
    //printf("\n");

    PPToken* head = TokenArray_PopFront(&is);

    if (PPToken_IsStringizingOp(head))
    {
      /*
      Each # preprocessing token in the replacement list for
      a function-like macro shall be followed by a parameter
      as the next preprocessing token in the replacement list.
      */

      // Stringizing operator
      int idx = FindNoSpaceIndex(&is, 0);
      TokenArray* aseq;

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
        TokenArray* aseq;

        if (TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
        {
          TokenArray_Erase(&is, 0, idx + 1);

          // Only if actuals can be empty
          if (aseq->Size > 0)
          {
            TokenArray os2 = TOKENARRAY_INIT;
            Glue(&os, aseq, &os2);
            TokenArray_Swap(&os2, &os);
            TokenArray_Destroy(&os2);
          }
        }

        else
        {
          TokenArray t = TOKENARRAY_INIT;
          TokenArray_PushBack(&t, PPToken_Clone(is.pItems[idx]));
          TokenArray_Erase(&is, 0, idx + 1);

          TokenArray os2 = TOKENARRAY_INIT;
          Glue(&os, &t, &os2);
          TokenArray_Swap(&os2, &os);
          TokenArray_Destroy(&os2);
          TokenArray_Destroy(&t);
        }

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
        TokenArray* aseq;

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
              TokenArray* aseq2;

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

        continue;
      }

      TokenArray* argseq = NULL;

      if (args != NULL &&
        TokenArrayMap_Lookup(args, head->Lexeme, &argseq))
      {
        //expand head
        TokenArray expanded = TOKENARRAY_INIT;
        ExpandMacro(argseq, macros, false, skip_defined, evalmode, pCaller, &expanded);
        TokenArray_AppendMove(&os, &expanded);
        TokenArray_Destroy(&expanded);
        continue;
      }
    }

    TokenArray_PushBack(&os, head);
  }

  TokenArray os2 = TOKENARRAY_INIT;
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
void ArgToken(TokenArray* tokens,
  bool get_more,
  bool want_space,
  PPToken* token)
{
  PPToken *pToken = TokenArray_PopFront(tokens);
  PPToken_Swap(pToken, token);
  PPToken_Delete(pToken);

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
bool GatherArgs(const char* name,
  TokenArray* tokens,
  const TokenArray* formal_args,
  TokenArrayMap* args,
  bool get_more,
  bool is_vararg,
  PPToken* close)
{
  PPToken t = TOKEN_INIT;

  for (int i = 0; i < formal_args->Size; i++)
  {
    TokenArray* pV = TokenArray_Create();

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
      TokenArray* pV2 = TokenArray_Create();

      TokenArrayMap_SetAt(args,
        formal_args->pItems[i]->Lexeme,
        pV2);

      // Instantiate argument with an empty value list
      //args[(*i).get_val()];
      break;
    }

    String_Set(&close->Lexeme, t.Lexeme);
    //close = t;
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

  //#endif
  return (true);
}

/*
* Remove from tokens and return the elements comprising the arguments to the defined
* operator, * such as "defined X" or "defined(X)"
* This is the rule when processing #if #elif expressions
*/
void GatherDefinedOperator(TokenArray* tokens,
  const MacroMap* macros,
  TokenArray* result)
{
  //TokenArray tokens = TOKENARRAY_INIT;
  //TokenArray_AppendCopy(&tokens, tokensIn);

  // Skip leading space
  while (PPToken_IsSpace(tokens->pItems[0]))
  {
    PPToken* pp = TokenArray_PopFront(tokens);
    TokenArray_PushBack(result, pp);
  }

  if ((PPToken_IsIdentifier(tokens->pItems[0])))
  {
    // defined X form
    if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
    {
      PPToken* pp0 = TokenArray_PopFront(tokens);
      String_Set(&pp0->Lexeme, "1");
      TokenArray_PushBack(result, pp0);
    }

    else
    {
      PPToken* pp0 = TokenArray_PopFront(tokens);
      String_Set(&pp0->Lexeme, "0");
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
      PPToken* pp = TokenArray_PopFront(tokens);
      TokenArray_PushBack(result, pp);
    }

    if (!PPToken_IsIdentifier(tokens->pItems[0]))
    {
      //goto error;
    }

    if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
    {
      PPToken* pp0 = TokenArray_PopFront(tokens);
      String_Set(&pp0->Lexeme, "1");
      TokenArray_PushBack(result, pp0);
    }

    else
    {
      PPToken* pp0 = TokenArray_PopFront(tokens);
      String_Set(&pp0->Lexeme, "0");
      TokenArray_PushBack(result, pp0);
    }

    //PPToken* pp = TokenArray_PopFront(&tokens);
    //TokenArray_PushBack(result, pp);

    // Skip spaces
    while (PPToken_IsSpace(tokens->pItems[0]))
    {
      PPToken* pp = TokenArray_PopFront(tokens);
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


void ExpandMacro(const TokenArray* tsOriginal,
  const MacroMap* macros,
  bool get_more,
  bool skip_defined,
  bool evalmode,
  Macro* caller,
  TokenArray* pOutputSequence2)
{
  TokenArray_Clear(pOutputSequence2);

  TokenArray r = TOKENARRAY_INIT;

  TokenArray ts = TOKENARRAY_INIT;
  TokenArray_AppendCopy(&ts, tsOriginal);

  //printf("Expanding: ");
  TokenArray_Print(&ts);
  //printf("\n");

  while (ts.Size > 0)
  {
    //printf("r = ");
    TokenArray_Print(&r);
    //printf("\n");

    PPToken* pHead =
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
      TokenArray result = TOKENARRAY_INIT;
      GatherDefinedOperator(&ts, macros, &result);
      TokenArray_AppendMove(&r, &result);

      TokenArray_Destroy(&result);
      continue;
    }

    Macro * pMacro = MacroMap_Find(macros, pHead->Lexeme);

    if (pMacro == NULL)
    {
      //if eval mode se nao achar a macro
      //ela vira zero
      if (evalmode)
      {
        String_Set(&pHead->Lexeme, "0");
        pHead->Token = PPTokenType_Number;
      }
      // Nothing to do if the identifier is not a macro
      TokenArray_PushBack(&r, pHead);
      pHead = NULL; //moved
      continue;
    }

    PPToken* pFound =
      TokenSet_Find(&pHead->HiddenSet, pMacro->Name);

    if (pFound)
    {
      // Skip the head token if it is in the hideset
      //printf("Skipping (head is in HS)\n");
      TokenArray_PushBack(&r, pHead);
      pHead = NULL;
      continue;
    }

    TokenArray removed_spaces = TOKENARRAY_INIT;

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

      TokenArray s = TOKENARRAY_INIT;

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

      TokenArray_PopFront(&ts);
      PPToken close = TOKEN_INIT;

      if (!GatherArgs(pHead->Lexeme,
        &ts,
        &pMacro->FormalArguments,
        &args,
        get_more,
        false, /*m.is_vararg,*/
        &close))
      {
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

      TokenArray s = TOKENARRAY_INIT;

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

  TokenArray_Swap(&r, pOutputSequence2);

  TokenArray_Destroy(&r);
  TokenArray_Destroy(&ts);
}


/*
* Try to ensure that ts has at least one non-space token
* Return true if this is the case
* Return any discarded space tokens in removed
*/
bool FillIn(TokenArray* ts, bool get_more, TokenArray* removed)
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

void Glue(const TokenArray* lsI,
  const TokenArray* rsI,
  TokenArray* out)
{
  TokenArray ls = TOKENARRAY_INIT;
  TokenArray_AppendCopy(&ls, lsI);

  TokenArray rs = TOKENARRAY_INIT;
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
      PPToken* tk = TokenArray_PopFront(&rs);
      PPToken_Delete(tk);
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

void ExpandMacroToText(const TokenArray* pTokenSequence,
  const MacroMap* macros,
  bool get_more,
  bool skip_defined,
  bool evalmode,
  Macro* caller,
  StrBuilder* strBuilder)
{
  StrBuilder_Clear(strBuilder);
  TokenArray tks = TOKENARRAY_INIT;
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




int MacroMap_SetAt(MacroMap* pMap,
  const char* Key,
  Macro* newValue)
{
  void *pPrevious;
  int r = Map2_SetAt((Map2*)pMap, Key, newValue, &pPrevious);
  Macro_Delete((Macro*)pPrevious);
  return r;
}

bool MacroMap_Lookup(const MacroMap* pMap,
  const char*  Key,
  Macro** rValue)
{
  return Map2_Lookup((Map2*)pMap,
    Key,
    (void**)rValue);
}

Macro* MacroMap_Find(const MacroMap* pMap, const char*  Key)
{
  void* p = NULL;
  Map2_Lookup((Map2*)pMap,
    Key,
    &p);
  return (Macro*)p;
}


bool MacroMap_RemoveKey(MacroMap* pMap, const char*  Key)
{
  Macro *pItem;
  bool r = Map2_RemoveKey((Map2*)pMap, Key, (void**)&pItem);

  if (r)
  {
    Macro_Delete(pItem);
  }

  return r;
}

void MacroMap_Init(MacroMap* p)
{
  MacroMap t = MACROMAP_INIT;
  *p = t;
}

void MacroMap_Destroy(MacroMap* p)
{
  Map2_Destroy((Map2*)p);
}


void MacroMap_Swap(MacroMap * pA, MacroMap * pB)
{
  MacroMap t = *pA;
  *pA = *pB;
  *pB = t;
}



/**
* Simple Bob Jenkins's hash algorithm taken from the
* wikipedia description.
*/
static uint32_t HashFunc(const char* a)
{
  ASSERT(a != NULL);
  int len = strlen(a);
  const char* key = a;
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

Result Bucket_Reserve(Bucket* p, int nelements);

Result BucketItem_InitMoveKey(BucketItem* node,
  int hash,
  String* key /*in out*/,
  void* data)
{
  node->data = data;
  node->hash = hash;

  String_InitWith(&node->key, NULL);
  String_Swap(&node->key, key);

  return RESULT_OK;
}


Result BucketItem_Init(BucketItem* node,
  int hash,
  const char* key,
  void* data)
{
  Result result = String_InitWith(&node->key, key);
  node->data = data;
  node->hash = hash;
  return result;
}

Result BucketItem_CreateMoveKey(BucketItem** pp,
  int hash,
  String* key,
  void* data)
{
  Result result = RESULT_OUT_OF_MEM;
  BucketItem* node = (BucketItem*)malloc(sizeof(BucketItem) * 1);
  if (node)
  {
    BucketItem_InitMoveKey(node,
      hash,
      key,
      data);
    *pp = node;
    result = RESULT_OK;
  }
  return result;
}

Result BucketItem_Change(BucketItem* p,
  void* data)
{
  p->data = data;
  return RESULT_OK;
}

void BucketItem_Destroy(BucketItem* node, void(*pfDestroyData)(void*))
{
  String_Destroy(&node->key);
  if (pfDestroyData)
  {
    pfDestroyData(node->data);
  }
}

void BucketItem_Delete(BucketItem* p, void(*pfDestroyData)(void*))
{
  if (p)
  {
    BucketItem_Destroy(p, pfDestroyData);
    free(p);
  }
}

Result Bucket_Init(Bucket* p, int capacity)
{
  Result result = RESULT_OK;
  p->data = NULL;
  p->size = 0;
  p->capacity = 0;

  if (capacity > 0)
  {
    result = Bucket_Reserve(p, capacity);
  }

  return result;
}

Result Bucket_Create(Bucket** pp)
{
  Result result = RESULT_OUT_OF_MEM;
  Bucket*  p = (Bucket*)malloc(sizeof(Bucket) * 1);
  if (p)
  {
    result = Bucket_Init(p, 0);
    if (result == RESULT_OK)
    {
      *pp = p;
      p = NULL;
    }
    free(p);
  }
  return result;
}


void Bucket_Destroy(Bucket* p, void(*pfDestroyData)(void*))
{
  for (int i = 0; i < p->size; i++)
  {
    BucketItem_Delete(p->data[i], pfDestroyData);
  }
  free(p->data);
}


void Bucket_Delete(Bucket* p, void(*pfDestroyData)(void*))
{
  if (p)
  {
    Bucket_Destroy(p, pfDestroyData);
    free(p);
  }
}


Result Bucket_Reserve(Bucket* p, int nelements)
{
  Result r = RESULT_OK;

  if (nelements > p->capacity)
  {
    BucketItem** pnew = (BucketItem**)realloc(p->data,
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
      ASSERT(false);
      r = RESULT_OUT_OF_MEM;
    }
  }

  return r;
}
static Result Grow(Bucket* p, int nelements)
{
  Result r = RESULT_OK;

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

Result Bucket_Append(Bucket* p, BucketItem* pItem)
{
  Result result = Grow(p, p->size + 1);

  if (result == RESULT_OK)
  {
    p->data[p->size] = pItem;
    p->size++;
  }

  return result;
}

static int FindNodeIndex(Bucket* bucket, uint32_t hash, const char* key)
{
  ASSERT(key != NULL);
  for (int i = 0; i < bucket->size; i++)
  {
    BucketItem* node = bucket->data[i];
    if (node->hash == hash &&
      strcmp(node->key, key) == 0)
    {
      return (int)i;
    }
  }

  return -1;
}

Result RemoveBucketItem(Bucket* bucket,
  uint32_t hash,
  const char* key,
  void** ppData)
{
  ASSERT(key != NULL);
  *ppData = NULL; //out

  int index = FindNodeIndex(bucket, hash, key);
  Result result = index != -1 ? RESULT_OK : RESULT_FAIL;

  if (result == RESULT_OK)
  {
    //ponteiro de item que vai ser removido (out)
    *ppData = bucket->data[index]->data;

    if (index != (int)(bucket->size) - 1)
    {
      //swap  dos ponteiros de [index] e [size - 1]
      BucketItem* pTemp = bucket->data[bucket->size - 1];
      bucket->data[bucket->size - 1] = bucket->data[index];
      bucket->data[index] = pTemp;
    }

    BucketItem_Delete(bucket->data[bucket->size - 1], NULL);
    bucket->size--;
  }


  return result;
}


Result Buckets_Init(Buckets* p,
  int size)
{
  Result result = RESULT_OUT_OF_MEM;
  p->data = NULL;
  p->size = size;

  p->data = (Bucket**)malloc(sizeof(Bucket*) * size);
  if (p->data)
  {
    for (int i = 0; i < size; i++)
    {
      p->data[i] = NULL;
    }
    result = RESULT_OK;
  }

  return result;
}

void Buckets_Destroy(Buckets* p, void(*pfDestroyData)(void*))
{
  for (int i = 0; i < p->size; i++)
  {
    Bucket_Delete(p->data[i],
      pfDestroyData);
  }
  free(p->data);
}


Result Map_Init(Map* map, int nBuckets)
{
  map->Size = 0;
  Result result = Buckets_Init(&map->buckets, nBuckets);
  if (result == RESULT_OK)
  {
  }
  return result;
}

Result Map_Create(Map** pp, int nBuckets)
{
  Result result = RESULT_OUT_OF_MEM;
  Map* p = (Map*)malloc(sizeof(Map));
  if (p)
  {
    result = Map_Init(p, nBuckets);
    if (result == RESULT_OK)
    {
      *pp = p;
    }
    else
    {
      free(p);
    }
  }
  return result;
}

void Map_Destroy(Map* map, void(*pfDestroyData)(void*))
{
  Buckets_Destroy(&map->buckets, pfDestroyData);
}

void Map_Delete(Map* p, void(*pfDestroyData)(void*))
{
  Map_Destroy(p, pfDestroyData);
  free((void*)p);
}

BucketItem* Map_FindNode(Map* map, const char* key)
{
  if (map->buckets.data == NULL)
  {
    return NULL;
  }

  ASSERT(key != NULL);
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;

  Bucket* pBucket = map->buckets.data[bucket_n];

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


Result Map_SetMoveKey(Map* map, String* key, void* data)
{
  ASSERT(key != NULL);
  Result result;

  BucketItem* pNode = Map_FindNode(map, *key);
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
  Bucket* bucket = map->buckets.data[bucket_n];

  if (bucket == NULL)
  {
    result = Bucket_Create(&bucket);
    if (result == RESULT_OK)
    {
      map->buckets.data[bucket_n] = bucket;
    }
  }
  else
  {
    result = RESULT_OK;
  }

  if (result == RESULT_OK)
  {
    BucketItem* node;
    result = BucketItem_CreateMoveKey(&node,
      hash,
      key,
      data);
    if (result == RESULT_OK)
    {
      result = Bucket_Append(bucket, node /*moved*/);
    }
  }

  if (result == RESULT_OK)
  {
    map->Size++;
  }

  return result;
}

Result Map_Set(Map* map, const char* key, void* data)
{
  ASSERT(key != NULL);
  void* pv;
  Result result = Map_Find(map, key, &pv);
  if (result == RESULT_OK)
  {
    return RESULT_FAIL;
    //ASSERT(false);
  }


  ASSERT(key != NULL);
  String localkey;
  String_InitWith(&localkey, key);

  result = Map_SetMoveKey(map, &localkey, data);

  String_Destroy(&localkey);
  return result;
}


Result Map_Find(Map* map, const char* key, void** pp)
{
  ASSERT(key != NULL);
  BucketItem* pNode = Map_FindNode(map, key);
  Result result = pNode ? RESULT_OK : RESULT_FAIL;

  if (result == RESULT_OK)
  {
    *pp = pNode->data;
  }

  return result;
}

void* Map_Find2(Map* map, const char* key)
{
  void* pv;
  Result result = Map_Find(map, key, &pv);

  return result == RESULT_OK ? pv : NULL;
}

Result Map_DeleteEx(Map* map, const char* key, void** pp)
{
  ASSERT(key != NULL);
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;

  Bucket* bucket = map->buckets.data[bucket_n];

  if (bucket == NULL)
  {
    return RESULT_FAIL;
  }

  Result result = RemoveBucketItem(bucket, hash, key, pp);

  if (result == RESULT_OK)
  {
    map->Size--;
  }
  return result;
}

Result Map_DeleteItemOpt(Map* map, const char* key, void(*pfDestroyData)(void*))
{
  ASSERT(key != NULL);
  void* p;
  Result result = Map_DeleteEx(map, key, &p);
  if (result == RESULT_OK)
  {
    if (pfDestroyData != NULL)
    {
      pfDestroyData(p);
    }
  }
  return result;
}

Result Map_DeleteItem(Map* map, const char* key, void(*pfDestroyData)(void*))
{
  Result result = Map_DeleteItemOpt(map, key, pfDestroyData);
  void* p;
  //ASSERT(Map_Find(map, key, &p) != RESULT_OK);
  if (Map_Find(map, key, &p) == RESULT_OK)
  {
    ASSERT(false);
    Map_DeleteItemOpt(map, key, pfDestroyData);
  }
  return result;
}


void Map_Print(Map* map)
{
  for (int i = 0; i < map->buckets.size; i++)
  {
    Bucket* data = map->buckets.data[i];
    if (data != NULL)
    {
      for (int k = 0; k < data->size; k++)
      {
        BucketItem* node = data->data[k];
        printf("%s", node->key);
      }
    }
  }
}


void Buckets_Swap(Buckets* b1, Buckets* b2)
{
  Bucket** data2 = b2->data;
  int size2 = b2->size;

  b2->data = b1->data;
  b2->size = b1->size;

  b1->data = data2;
  b1->size = size2;

}

void Map_Swap(Map* map, Map* map2)
{
  Map temp = *map2;
  *map2 = *map;
  *map = temp;
  //Buckets_Swap(&map->buckets, &map2->buckets);
}


////

Result MultiMap_Init(MultiMap* map, int nBuckets)
{
  map->Size = 0;
  Result result = Buckets_Init(&map->buckets, nBuckets);
  if (result == RESULT_OK)
  {
  }
  return result;
}

void MultiMap_Destroy(MultiMap* map, void(*pfDestroyData)(void*))
{
  Buckets_Destroy(&map->buckets, pfDestroyData);
}

Result MultiMap_Add(MultiMap* map, const char* key, void* data)
{
  ASSERT(key != NULL);
  Result result;

  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;
  Bucket* bucket = map->buckets.data[bucket_n];

  if (bucket == NULL)
  {
    //N�o existia..criar
    result = Bucket_Create(&bucket);
    if (result == RESULT_OK)
    {
      map->buckets.data[bucket_n] = bucket;
    }
  }
  else
  {
    result = RESULT_OK;
  }

  if (result == RESULT_OK)
  {
    //Adiciona no fim - n�o verifica se ja existe
    String stemp = STRING_INIT;
    String_Set(&stemp, key);
    BucketItem* node;
    result = BucketItem_CreateMoveKey(&node,
      hash,
      &stemp,
      data);

    String_Destroy(&stemp);

    if (result == RESULT_OK)
    {
      result = Bucket_Append(bucket, node /*moved*/);
    }
  }

  if (result == RESULT_OK)
  {
    map->Size++;
  }

  return result;
}


Bucket*  MultiMap_FindBucket(MultiMap* map, const char* key)
{
  if (map->buckets.data == NULL)
  {
    return NULL;
  }

  ASSERT(key != NULL);
  uint32_t hash = HashFunc(key);
  int bucket_n = hash % map->buckets.size;

  Bucket*  pBucket = map->buckets.data[bucket_n];

  if (pBucket == NULL)
  {
    return NULL;
  }

  return pBucket;
}

void MultiMap_Swap(MultiMap* map, MultiMap* map2)
{
  MultiMap temp = *map2;
  *map2 = *map;
  *map = temp;
}//#include "Map.h"


 //#include "stdafx.h"



void KeyValue_Delete(MapItem2* p) _default
{
  if (p != NULL)
  {
    String_Destroy(&p->Key);
    free((void*)p);
  }
}

static MapItem2* Map2_GetAssocAt(
  Map2* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue);


unsigned int String2_HashKey(const char*  Key)
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


void Map2_RemoveAll(Map2* pMap)
{
  if (pMap->pHashTable != NULL)
  {
    for (unsigned int nHash = 0;
      nHash < pMap->nHashTableSize;
      nHash++)
    {
      MapItem2* pKeyValue =
        pMap->pHashTable[nHash];

      while (pKeyValue != NULL)
      {
        MapItem2* pKeyValueCurrent = pKeyValue;
        pKeyValue = pKeyValue->pNext;
        KeyValue_Delete(pKeyValueCurrent);
      }
    }

    free(pMap->pHashTable);
    pMap->pHashTable = NULL;
    pMap->nCount = 0;
  }
}

void Map2_Destroy(Map2* pMap)
{
  Map2_RemoveAll(pMap);
}

static MapItem2* Map2_GetAssocAt(
  Map2* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue)
{
  if (pMap->pHashTable == NULL)
  {
    *HashValue = 0;
    *nHashBucket = 0;
    return NULL;
  }

  *HashValue = String2_HashKey(Key);
  *nHashBucket = *HashValue % pMap->nHashTableSize;

  MapItem2* pResult = NULL;

  MapItem2* pKeyValue =
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

bool Map2_Lookup(Map2* pMap,
  const char*  Key,
  void** rValue)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
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

bool Map2_LookupKey(Map2* pMap,
  const char*  Key,
  const char** rKey)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
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

bool Map2_RemoveKey(Map2* pMap,
  const char*  Key,
  void** ppValue)
{
  *ppValue = 0;
  bool bResult = false;

  if (pMap->pHashTable != NULL)
  {
    unsigned int HashValue =
      String2_HashKey(Key);

    MapItem2** ppKeyValuePrev =
      &pMap->pHashTable[HashValue % pMap->nHashTableSize];

    MapItem2* pKeyValue = *ppKeyValuePrev;

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

int Map2_SetAt(Map2* pMap,
  const char* Key,
  void* newValue,
  void** ppPreviousValue)
{
  int result = 0;
  *ppPreviousValue = NULL;

  if (pMap->pHashTable == NULL)
  {
    if (pMap->nHashTableSize < 1)
    {
      pMap->nHashTableSize = 1000;
    }

    MapItem2** pHashTable =
      (MapItem2**)malloc(sizeof(MapItem2*) * pMap->nHashTableSize);

    if (pHashTable != NULL)
    {
      memset(pHashTable, 0, sizeof(MapItem2*) * pMap->nHashTableSize);
      pMap->pHashTable = pHashTable;
    }
  }

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    MapItem2* pKeyValue =
      Map2_GetAssocAt(pMap,
        Key,
        &nHashBucket,
        &HashValue);

    if (pKeyValue == NULL)
    {
      pKeyValue = (MapItem2*)malloc(sizeof(MapItem2) * 1);
      pKeyValue->HashValue = HashValue;
      pKeyValue->pValue = newValue;
      String_InitWith(&pKeyValue->Key, Key);
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
      String_Set(&pKeyValue->Key, Key);
    }
  }

  return result;
}

void Map2_Init(Map2 * p) _default
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

Map2* Map2_Create(void) _default
{
  Map2 *p = (Map2*)malloc(sizeof * p);
  if (p != NULL)
  {
    Map2_Init(p);
  }
  return p;
}

void Map2_Delete(Map2 * p) _default
{
  if (p != NULL)
  {
    Map2_Destroy(p);
    free((void*)p);
  }
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

void Declarator(Parser* ctx, bool bAbstract, TDeclarator** ppTDeclarator2);


Tokens Parser_Match(Parser* parser, TScannerItemList* listOpt);
Tokens Parser_MatchToken(Parser* parser,
  Tokens tk,
  TScannerItemList* listOpt);
bool TTypeSpecifier_IsFirst(Parser* ctx, Tokens token, const char* lexeme);
//static bool Is_Type_QualifierFirst(Tokens token);
void Specifier_Qualifier_List(Parser* ctx, TSpecifierQualifierList* pSpecifierQualifierList);
static bool TTypeQualifier_IsFirst(Tokens token);


static bool IsPreprocessorTokenPhase(Tokens token)
{
  return
    token == TK_SPACES ||
    token == TK_COMMENT ||
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




bool Declaration(Parser* ctx, TAnyDeclaration** ppDeclaration);

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme);



Result Parser_InitString(Parser* parser,
  const char* name,
  const char* text)
{
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
  Scanner_InitString(&parser->Scanner, name, text);

  //sair do BOF
  TScannerItemList clueList0 = { 0 };
  Parser_Match(parser, &clueList0);
  TScannerItemList_Destroy(&clueList0);

  return RESULT_OK;
}

Result Parser_InitFile(Parser* parser, const char* fileName)
{


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

  return RESULT_OK;
}

void Parser_PushFile(Parser* parser, const char* fileName)
{
  Scanner_IncludeFile(&parser->Scanner, fileName, FileIncludeTypeFullPath, false);


  TScannerItemList clueList0 = { 0 };
  Parser_Match(parser, &clueList0);
  ASSERT(clueList0.pHead == NULL);
  TScannerItemList_Destroy(&clueList0);

}





void Parser_Destroy(Parser* parser)
{
  TScannerItemList_Destroy(&parser->ClueList);

  SymbolMap_Destroy(&parser->GlobalScope);

  //Map_Destroy(&parser->TypeDefNames, NULL);
  StrBuilder_Destroy(&parser->ErrorMessage);
  Scanner_Destroy(&parser->Scanner);

}

static const char* GetName()
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

bool Parser_HasError(Parser* pParser)
{
  return pParser->bError || pParser->Scanner.bError;
}

void SetWarning(Parser* parser, const char* fmt, ...)
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

void SetError(Parser* parser, const char* fmt, ...)
{
  //    ASSERT(false);
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


int GetCurrentLine(Parser* parser)
{
  if (Parser_HasError(parser))
  {
    return -1;
  }

  return Scanner_LineAt(&parser->Scanner, 0);
}

int GetFileIndex(Parser* parser)
{
  if (Parser_HasError(parser))
  {
    return -1;
  }

  return Scanner_FileIndexAt(&parser->Scanner, 0);
}

static void GetPosition(Parser* ctx, TPosition* pPosition)
{
  pPosition->Line = GetCurrentLine(ctx);
  pPosition->FileIndex = GetFileIndex(ctx);
  //ASSERT(pPosition->FileIndex >= 0);
}

Tokens Parser_LookAheadToken(Parser* parser)
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


const char* Parser_LookAheadLexeme(Parser* parser)
{
  if (Parser_HasError(parser))
  {
    return "";
  }

  const char* lexeme = NULL;

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


Tokens Parser_CurrentToken(Parser* parser)
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

Tokens Parser_Match(Parser* parser, TScannerItemList* listOpt)
{
  //ASSERT(listOpt != NULL);
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
      if (token == TK_PRE_INCLUDE)
      {
        //otimizacao para nao ficar
        //acumulando tokens nos niveis
        //internos do include
        //pois eles nao serao usados
        //gerar o fonte de qualquer forma.
        parser->IncludeLevel++;
        if (parser->IncludeLevel == 1)
        {
          ScannerItem* pNew = ScannerItem_Create();
          LocalStrBuilder_Set(&pNew->lexeme, Scanner_LexemeAt(&parser->Scanner, 0));
          pNew->token = Scanner_TokenAt(&parser->Scanner, 0);
          TScannerItemList_PushBack(&parser->ClueList, pNew);
        }
      }
      else if (token == TK_FILE_EOF)
      {
        parser->IncludeLevel--;
        if (parser->IncludeLevel == 0)
        {
          ScannerItem* pNew = ScannerItem_Create();
          LocalStrBuilder_Set(&pNew->lexeme, Scanner_LexemeAt(&parser->Scanner, 0));
          pNew->token = Scanner_TokenAt(&parser->Scanner, 0);
          TScannerItemList_PushBack(&parser->ClueList, pNew);
        }
      }
      else if (parser->IncludeLevel == 0)
      {
        ScannerItem* pNew = ScannerItem_Create();
        LocalStrBuilder_Set(&pNew->lexeme, Scanner_LexemeAt(&parser->Scanner, 0));
        pNew->token = Scanner_TokenAt(&parser->Scanner, 0);
        TScannerItemList_PushBack(&parser->ClueList, pNew);
      }

      Scanner_Match(&parser->Scanner);
      token = Scanner_TokenAt(&parser->Scanner, 0);
    }
  }

  return token;
}
Tokens Parser_MatchToken(Parser* parser,
  Tokens tk,
  TScannerItemList* listOpt)
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

const char* GetCompletationMessage(Parser* parser)
{
  const char* pMessage = "ok";

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

const char* Lexeme(Parser* parser)
{
  if (Parser_HasError(parser))
  {
    ASSERT(false);
    return "";
  }

  return Scanner_LexemeAt(&parser->Scanner, 0);
}

bool ErrorOrEof(Parser* parser)
{
  return Parser_HasError(parser) ||
    Parser_CurrentToken(parser) == TK_EOF;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


void Expression0(Parser* ctx, TExpression**);
void CastExpression(Parser* ctx, TExpression**);
void GenericSelection(Parser* ctx);
void ArgumentExpressionList(Parser* ctx, TExpression**);
void AssignmentExpression(Parser* ctx, TExpression**);
void Initializer_List(Parser* ctx, TInitializerList* pInitializerList);



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

void PrimaryExpressionLiteral(Parser* ctx, TExpression** ppPrimaryExpression)
{
  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);

  TPrimaryExpressionLiteral *  pPrimaryExpressionLiteral
    = TPrimaryExpressionLiteral_Create();

  *ppPrimaryExpression = (TExpression*)pPrimaryExpressionLiteral;

  while (token == TK_STRING_LITERAL)
  {
    TPrimaryExpressionLiteralItem *  pPrimaryExpressionLiteralItem
      = TPrimaryExpressionLiteralItem_Create();
    const char* lexeme2 = Lexeme(ctx);
    String_Set(&pPrimaryExpressionLiteralItem->lexeme, lexeme2);

    token = Parser_Match(ctx,
      &pPrimaryExpressionLiteralItem->ClueList0);

    TPrimaryExpressionLiteralItemList_Add(&pPrimaryExpressionLiteral->List, pPrimaryExpressionLiteralItem);
  }
}

void Compound_Statement(Parser* ctx, TStatement** ppStatement);

void Parameter_Type_List(Parser* ctx, TParameterTypeList* pParameterList);

void LambdaExpression(Parser* ctx, TExpression** ppPrimaryExpression)
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
  TPrimaryExpressionLambda* pPrimaryExpressionLambda = TPrimaryExpressionLambda_Create();

  *ppPrimaryExpression = pPrimaryExpressionLambda; //out

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

  Compound_Statement(ctx, &pPrimaryExpressionLambda->pCompoundStatement);
}

void PrimaryExpression(Parser* ctx, TExpression** ppPrimaryExpression)
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
  *ppPrimaryExpression = NULL; //out

  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);
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

    TPrimaryExpressionValue *   pPrimaryExpressionValue
      = TPrimaryExpressionValue_Create();

    pPrimaryExpressionValue->token = token;
    String_Set(&pPrimaryExpressionValue->lexeme, lexeme);


    Parser_Match(ctx,
      &pPrimaryExpressionValue->ClueList0);
    *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;
  }
  break;

  case TK_CHAR_LITERAL:
  case TK_DECIMAL_INTEGER:
  case TK_HEX_INTEGER:
  case TK_FLOAT_NUMBER:
  {
    TPrimaryExpressionValue *   pPrimaryExpressionValue
      = TPrimaryExpressionValue_Create();

    pPrimaryExpressionValue->token = token;
    String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));


    Parser_Match(ctx,
      &pPrimaryExpressionValue->ClueList0);
    *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;
  }
  break;

  case TK_LEFT_PARENTHESIS:
  {
    TPrimaryExpressionValue *   pPrimaryExpressionValue
      = TPrimaryExpressionValue_Create();

    Parser_Match(ctx,
      &pPrimaryExpressionValue->ClueList0);

    TExpression* pExpression;
    Expression0(ctx, &pExpression);

    //    //TNodeClueList_MoveToEnd(&pPrimaryExpressionValue->ClueList, &ctx->Scanner.ClueList);
    Parser_MatchToken(ctx,
      TK_RIGHT_PARENTHESIS,
      &pPrimaryExpressionValue->ClueList1);


    pPrimaryExpressionValue->token = token;
    String_Set(&pPrimaryExpressionValue->lexeme, Lexeme(ctx));
    pPrimaryExpressionValue->pExpressionOpt = pExpression;


    *ppPrimaryExpression = (TExpression*)pPrimaryExpressionValue;
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

void GenericSelection(Parser* ctx)
{
  //_Generic

  /*
  (6.5.1.1) generic-selection:
  _Generic ( assignment-expression , generic-assoc-list )
  */
}

void GenericAssocList(Parser* ctx)
{

  //type-name default

  /*
  (6.5.1.1) generic-assoc-list:
  generic-association
  generic-assoc-list , generic-association
  */
}

void GenericAssociation(Parser* ctx)
{
  //type-name default

  /*
  (6.5.1.1) generic-association:
  type-name : assignment-expression
  default : assignment-expression
  */
}

void TTypeName_Swap(TTypeName* a, TTypeName* b)
{
  TTypeName temp = *a;
  *a = *b;
  *b = temp;
}

void TTypeName_Init(TTypeName* p) _default
{
  p->Type = TypeName_ID;
  p->SpecifierQualifierList.pData = NULL;
  p->SpecifierQualifierList.Size = 0;
  p->SpecifierQualifierList.Capacity = 0;
  TDeclarator_Init(&p->Declarator);
}



void TypeName(Parser* ctx, TTypeName* pTypeName)
{
  /*
  type-name:
  specifier-qualifier-list abstract-declaratoropt
  */

  Specifier_Qualifier_List(ctx, &pTypeName->SpecifierQualifierList);

  TDeclarator* pDeclarator = NULL;
  Declarator(ctx, true, &pDeclarator);
  if (pDeclarator)
  {
    pTypeName->Declarator = *pDeclarator;
  }
}


static void PostfixExpressionCore(Parser* ctx, TPostfixExpressionCore* pPostfixExpressionCore)
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

    String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));

    Parser_MatchToken(ctx, TK_IDENTIFIER,
      &pPostfixExpressionCore->ClueList1);
  }
  break;

  case TK_ARROW:
  {
    // postfix-expression -> identifier
    pPostfixExpressionCore->token = token;

    Parser_Match(ctx, &pPostfixExpressionCore->ClueList0);

    String_Set(&pPostfixExpressionCore->Identifier, Lexeme(ctx));

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
    // ASSERT(false);
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
    TPostfixExpressionCore *  pPostfixExpressionCoreNext =
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
    ASSERT(false);
    break;
  }


}

void PostfixExpression(Parser* ctx, TExpression** ppExpression)
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
    const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
    Tokens lookAheadToken = Parser_LookAheadToken(ctx);

    if (IsTypeName(ctx, lookAheadToken, lookAheadlexeme))
    {
      // ( type-name ) { initializer-list }

      TPostfixExpressionCore *  pTPostfixExpressionCore =
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

      *ppExpression = (TExpression*)pTPostfixExpressionCore;
    }

    else
    {
      //primary-expression
      TExpression* pPrimaryExpression;
      PrimaryExpression(ctx, &pPrimaryExpression);
      *ppExpression = pPrimaryExpression;
    }
  }
  else
  {
    //tem que ser?
    ASSERT(IsFirstOfPrimaryExpression(token));

    //primary-expression
    TExpression* pPrimaryExpression;
    PrimaryExpression(ctx, &pPrimaryExpression);
    *ppExpression = pPrimaryExpression;
  }

  token = Parser_CurrentToken(ctx);
  if (IsFirstOfPrimaryExpression(token))
  {

    // ASSERT(false); //pergunta deve continuar? ta certo?

    TPostfixExpressionCore *  pPostfixExpressionCore =
      TPostfixExpressionCore_Create();
    pPostfixExpressionCore->pExpressionLeft = *ppExpression;
    PostfixExpressionCore(ctx, pPostfixExpressionCore);
    *ppExpression = (TExpression*)pPostfixExpressionCore;
  }
  else
  {
    switch (token)
    {
    case TK_LEFT_PARENTHESIS:
    {
      TPostfixExpressionCore *  pPostfixExpressionCore =
        TPostfixExpressionCore_Create();
      pPostfixExpressionCore->pExpressionLeft = *ppExpression;

      String lexemeCopy = STRING_INIT;

      TPrimaryExpressionValue* ppri =
        TExpression_As_TPrimaryExpressionValue(*ppExpression);
      if (ppri)
      {
        String_Set(&lexemeCopy, ppri->lexeme);
      }
      PostfixExpressionCore(ctx, pPostfixExpressionCore);
      *ppExpression = (TExpression*)pPostfixExpressionCore;



      String_Destroy(&lexemeCopy);
    }
    break;
    case TK_LEFT_SQUARE_BRACKET:
    case TK_FULL_STOP:
    case TK_ARROW:
    case TK_PLUSPLUS:
    case TK_MINUSMINUS:
    {
      TPostfixExpressionCore *  pPostfixExpressionCore =
        TPostfixExpressionCore_Create();
      pPostfixExpressionCore->pExpressionLeft = *ppExpression;
      PostfixExpressionCore(ctx, pPostfixExpressionCore);
      *ppExpression = (TExpression*)pPostfixExpressionCore;
    }
    break;
    default:
      ASSERT(false);
      break;
    }

  }

}

void ArgumentExpressionList(Parser* ctx, TExpression** ppExpression)
{
  /*(6.5.2) argument-expression-list:
  assignment-expression
  argument-expression-list , assignment-expression
  */
  TExpression* pAssignmentExpression;
  AssignmentExpression(ctx, &pAssignmentExpression);
  *ppExpression = pAssignmentExpression;

  Tokens token = Parser_CurrentToken(ctx);

  if (token == TK_COMMA)
  {
    TBinaryExpression *  pExpr =
      TBinaryExpression_Create();

    Parser_Match(ctx, &pExpr->ClueList0);// &pAssignmentExpression->ClueList);

    TExpression* pAssignmentExpressionRight;
    AssignmentExpression(ctx, &pAssignmentExpressionRight);


    GetPosition(ctx, &pExpr->Position);
    pExpr->token = TK_COMMA;
    pExpr->pExpressionLeft = pAssignmentExpression;
    pExpr->pExpressionRight = pAssignmentExpressionRight;



    *ppExpression = (TExpression*)pExpr;
  }

  token = Parser_CurrentToken(ctx);

  if (token == TK_COMMA)
  {
    TBinaryExpression *  pExpr =
      TBinaryExpression_Create();

    Parser_Match(ctx, &pExpr->ClueList0);

    GetPosition(ctx, &pExpr->Position);
    pExpr->token = TK_COMMA;
    pExpr->pExpressionLeft = *ppExpression;

    TExpression *pExpressionRight;
    ArgumentExpressionList(ctx, &pExpressionRight);
    pExpr->pExpressionRight = pExpressionRight;

    *ppExpression = (TExpression*)pExpr;
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

  case TK__AUTO:
  case TK__SIZE:

  case TK_OPT_QUALIFIER:
  case TK_OWN_QUALIFIER:
  case TK_DTOR_QUALIFIER:
  case TK_MDTOR_QUALIFIER:
    bResult = true;
    break;
#endif
  default:
    ASSERT(false);
    break;
  }
  return bResult;
}

bool IsTypeName(Parser* ctx, Tokens token, const char * lexeme)
{

  bool bResult = false;

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
  case TK__AUTO:
  case TK__SIZE:
    //type-qualifier-extensions 
  case TK_OPT_QUALIFIER:
  case TK_OWN_QUALIFIER:
  case TK_DTOR_QUALIFIER:
  case TK_MDTOR_QUALIFIER:
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
    ASSERT(false);
    break;
  }

  return bResult;
}

void UnaryExpression(Parser* ctx, TExpression** ppExpression)
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
  const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);

  if (IsTypeName(ctx, tokenAhead, lookAheadlexeme))
  {
    //first para postfix-expression
    TExpression * pPostfixExpression;
    PostfixExpression(ctx, &pPostfixExpression);
    *ppExpression = (TExpression*)(pPostfixExpression);
    return;
  }

  else if (IsFirstOfPrimaryExpression(token0))
  {
    //primary-expression é first para postfix-expression

    TExpression * pPostfixExpression;
    PostfixExpression(ctx, &pPostfixExpression);
    *ppExpression = (TExpression*)(pPostfixExpression);
    return;
  }

  switch (token0)
  {
  case TK_PLUSPLUS:
  case TK_MINUSMINUS:
  {
    TUnaryExpressionOperator* pUnaryExpressionOperator =
      TUnaryExpressionOperator_Create();

    Parser_Match(ctx, &pUnaryExpressionOperator->ClueList0);

    TExpression *pUnaryExpression;
    UnaryExpression(ctx, &pUnaryExpression);


    pUnaryExpressionOperator->token = token0;
    pUnaryExpressionOperator->pExpressionRight = pUnaryExpression;
    *ppExpression = (TExpression*)pUnaryExpressionOperator;
  }
  break;

  //unary-operator cast-expression
  case TK_AMPERSAND:
  case TK_ASTERISK:
  case TK_PLUS_SIGN:
  case TK_HYPHEN_MINUS:
  case TK_TILDE:
  case TK_EXCLAMATION_MARK:

#ifdef LANGUAGE_EXTENSIONS
    //unary-operator-extension
  case TK_MOVE:
#endif
    //
  {
    TUnaryExpressionOperator* pUnaryExpressionOperator =
      TUnaryExpressionOperator_Create();

    Parser_Match(ctx, &pUnaryExpressionOperator->ClueList0);
    TExpression* pCastExpression;
    CastExpression(ctx, &pCastExpression);



    pUnaryExpressionOperator->token = token0;
    pUnaryExpressionOperator->pExpressionRight = pCastExpression;
    *ppExpression = (TExpression*)pUnaryExpressionOperator;

  }
  break;

  //////////////

  case TK_SIZEOF:
  {
    TUnaryExpressionOperator* pUnaryExpressionOperator =
      TUnaryExpressionOperator_Create();
    *ppExpression = (TExpression*)pUnaryExpressionOperator;

    pUnaryExpressionOperator->token = token0;

    Parser_MatchToken(ctx, TK_SIZEOF, &pUnaryExpressionOperator->ClueList0);

    if (Parser_CurrentToken(ctx) == TK_LEFT_PARENTHESIS)
    {
      const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
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
        TExpression *pTUnaryExpression;
        UnaryExpression(ctx, &pTUnaryExpression);
        pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
      }
    }
    else
    {
      //sizeof do tipo desta expressao
      TExpression *pTUnaryExpression;
      UnaryExpression(ctx, &pTUnaryExpression);
      pUnaryExpressionOperator->pExpressionRight = pTUnaryExpression;
    }
  }
  break;

  case TK__ALINGOF:
    //Match
    ASSERT(false);
    break;
  case TK_EOF:
    break;
    //TODO ver tudo que pode ser follow
  default:
    //ASSERT(false);
    //        SetUnexpectedError(ctx, "Assert", "");
    //aqui nao eh erro necessariamente
    break;
  }

}

void CastExpression(Parser* ctx, TExpression** ppExpression)
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
    const char* lookAheadlexeme = Parser_LookAheadLexeme(ctx);
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

        TPostfixExpressionCore*  pTPostfixExpressionCore =
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
        *ppExpression = (TExpression*)pTPostfixExpressionCore;
        //PostfixExpressionCore(ctx, pTPostfixExpressionCore);
      }
      else
      {
        TCastExpressionType *pCastExpressionType =
          TCastExpressionType_Create();

        TScannerItemList_Swap(&tempList0, &pCastExpressionType->ClueList0);
        TScannerItemList_Swap(&tempList1, &pCastExpressionType->ClueList1);

        TExpression* pCastExpression;
        CastExpression(ctx, &pCastExpression);

        TTypeName_Swap(&pCastExpressionType->TypeName, &typeName);
        pCastExpressionType->pExpression = pCastExpression;
        *ppExpression = (TExpression*)pCastExpressionType;

      }

      TTypeName_Destroy(&typeName);
      TScannerItemList_Destroy(&tempList0);
      TScannerItemList_Destroy(&tempList1);
    }
    else
    {
      TExpression* pUnaryExpression;
      UnaryExpression(ctx, &pUnaryExpression);
      *ppExpression = pUnaryExpression;
    }
  }
  else
  {
    TExpression* pUnaryExpression;
    UnaryExpression(ctx, &pUnaryExpression);

    *ppExpression = pUnaryExpression;
  }
}


void MultiplicativeExpression(Parser* ctx, TExpression** ppExpression)
{


  /*
  (6.5.5) multiplicative-expression:
  cast-expression                                // identifier  constant  string-literal  (  _Generic ++	  -- 	 & * + - ~ ! 		 sizeof 		 sizeof		 alignof
  multiplicative-expression * cast-expression
  multiplicative-expression / cast-expression
  multiplicative-expression % cast-expression
  */

  TExpression* pExpressionLeft;
  CastExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_PERCENT_SIGN:
  case TK_SOLIDUS:
  case TK_ASTERISK:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();

    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;

    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    CastExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_PERCENT_SIGN:
  case TK_SOLIDUS:
  case TK_ASTERISK:
  {
    TBinaryExpression *pBinaryExpression =
      TBinaryExpression_Create();

    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    MultiplicativeExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void AdditiveExpression(Parser* ctx, TExpression** ppExpression)
{

  /*
  (6.5.6) additive-expression:
  multiplicative-expression
  additive-expression + multiplicative-expression
  additive-expression - multiplicative-expression
  */

  TExpression* pExpressionLeft;
  MultiplicativeExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_PLUS_SIGN:
  case TK_HYPHEN_MINUS:
  {
    TBinaryExpression *pBinaryExpression =
      TBinaryExpression_Create();
    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    MultiplicativeExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_PLUS_SIGN:
  case TK_HYPHEN_MINUS:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    AdditiveExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

}

void ShiftExpression(Parser* ctx, TExpression** ppExpression)
{

  /*(6.5.7) shift-expression:
  additive-expression
  shift-expression << additive-expression
  shift-expression >> additive-expression
  */


  TExpression* pExpressionLeft;
  AdditiveExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_GREATERGREATER:
  case TK_LESSLESS:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    AdditiveExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_GREATERGREATER:
  case TK_LESSLESS:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    ShiftExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void RelationalExpression(Parser* ctx, TExpression** ppExpression)
{
  /*
  (6.5.8) relational-expression:
  shift-expression
  relational-expression < shift-expression
  relational-expression > shift-expression
  relational-expression <= shift-expression
  relational-expression >= shift-expression
  */

  TExpression* pExpressionLeft;
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
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    ShiftExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
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
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    RelationalExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

}

void EqualityExpression(Parser* ctx, TExpression** ppExpression)
{
  /*(6.5.9) equality-expression:
  relational-expression
  equality-expression == relational-expression
  equality-expression != relational-expression
  */

  TExpression* pExpressionLeft;
  RelationalExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_EQUALEQUAL:
  case TK_NOTEQUAL:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    RelationalExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_EQUALEQUAL:
  case TK_NOTEQUAL:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    EqualityExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void AndExpression(Parser* ctx, TExpression **ppExpression)
{
  /*(6.5.10) AND-expression:
  equality-expression
  AND-expression & equality-expression
  */

  TExpression* pExpressionLeft;
  EqualityExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_AMPERSAND:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    EqualityExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_AMPERSAND:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    AndExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void ExclusiveOrExpression(Parser* ctx, TExpression** ppExpression)
{
  /*
  (6.5.11) exclusive-OR-expression:
  AND-expression
  exclusive-OR-expression ^ AND-expression
  */

  TExpression* pExpressionLeft;
  AndExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_CIRCUMFLEX_ACCENT:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    AndExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_CIRCUMFLEX_ACCENT:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);


    TExpression* pExpressionRight;
    ExclusiveOrExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

}

void InclusiveOrExpression(Parser* ctx, TExpression**ppExpression)
{

  /*
  (6.5.12) inclusive-OR-expression:
  exclusive-OR-expression
  inclusive-OR-expression | exclusive-OR-expression
  */

  TExpression* pExpressionLeft;
  ExclusiveOrExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_VERTICAL_LINE:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    ExclusiveOrExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_VERTICAL_LINE:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    InclusiveOrExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void LogicalAndExpression(Parser* ctx, TExpression** ppExpression)
{

  /*
  (6.5.13) logical-AND-expression:
  inclusive-OR-expression
  logical-AND-expression && inclusive-OR-expression
  */

  TExpression* pExpressionLeft;
  InclusiveOrExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_ANDAND:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;
    GetPosition(ctx, &pBinaryExpression->Position);


    Parser_Match(ctx, &pBinaryExpression->ClueList0);


    TExpression* pExpressionRight;
    InclusiveOrExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_ANDAND:
  {
    TBinaryExpression *pBinaryExpression =
      TBinaryExpression_Create();

    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    LogicalAndExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}

void LogicalOrExpression(Parser* ctx, TExpression** ppExpression)
{
  /*(6.5.14) logical-OR-expression:
  logical-AND-expression
  logical-OR-expression || logical-AND-expression
  */


  TExpression* pExpressionLeft;
  LogicalAndExpression(ctx, &pExpressionLeft);
  *ppExpression = pExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);


  switch (token)
  {
  case TK_OROR:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    LogicalAndExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }

  token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_OROR:
  {
    TBinaryExpression *pBinaryExpression = TBinaryExpression_Create();
    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->token = token;
    pBinaryExpression->pExpressionLeft = *ppExpression;


    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    TExpression* pExpressionRight;
    LogicalOrExpression(ctx, &pExpressionRight);
    pBinaryExpression->pExpressionRight = pExpressionRight;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;
  default:
    ASSERT(false);
    break;
  }
}


void ConditionalExpression(Parser* ctx, TExpression**ppExpression)
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
    TTernaryExpression* pTernaryExpression =
      TTernaryExpression_Create();

    Parser_Match(ctx, &pTernaryExpression->ClueList0);

    TExpression* pTExpression;
    Expression0(ctx, &pTExpression);

    Parser_MatchToken(ctx, TK_COLON, &pTernaryExpression->ClueList1);

    TExpression* pConditionalExpressionRight;
    ConditionalExpression(ctx, &pConditionalExpressionRight);


    pTernaryExpression->token = TK_QUESTION_MARK;
    pTernaryExpression->pExpressionLeft = pLogicalOrExpressionLeft;
    pTernaryExpression->pExpressionMiddle = pTExpression;
    pTernaryExpression->pExpressionRight = pConditionalExpressionRight;
    *ppExpression = (TExpression*)pTernaryExpression;
  }


}

void AssignmentExpression(Parser* ctx, TExpression** ppExpression)
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
  TExpression* pConditionalExpressionLeft;
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
    TBinaryExpression *pBinaryExpression =
      TBinaryExpression_Create();

    Parser_Match(ctx, &pBinaryExpression->ClueList0);

    //Significa que o anterior deve ser do tipo  unary-expression
    //embora tenhamos feito o parser de conditional-expression
    //se nao for é erro.
    TExpression* pAssignmentExpressionRight;
    AssignmentExpression(ctx, &pAssignmentExpressionRight);

    GetPosition(ctx, &pBinaryExpression->Position);

    pBinaryExpression->pExpressionLeft = *ppExpression;
    pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
    pBinaryExpression->token = token;
    *ppExpression = (TExpression*)pBinaryExpression;
  }
  break;

  default:
    //É apenas conditional-expression
    break;
  }
}

void Expression0(Parser* ctx, TExpression** ppExpression)
{
  *ppExpression = NULL; //out
                        /*
                        (6.5.17) expression:
                        assignment-expression
                        expression , assignment-expression
                        */
  TExpression* pAssignmentExpressionLeft;
  AssignmentExpression(ctx, &pAssignmentExpressionLeft);
  *ppExpression = pAssignmentExpressionLeft;

  Tokens token = Parser_CurrentToken(ctx);

  if (token == TK_COMMA)
  {
    TExpression* pAssignmentExpressionRight;
    Parser_Match(ctx, NULL);
    Expression0(ctx, &pAssignmentExpressionRight);

    TBinaryExpression* pBinaryExpression =
      TBinaryExpression_Create();
    GetPosition(ctx, &pBinaryExpression->Position);
    pBinaryExpression->pExpressionLeft = *ppExpression;
    pBinaryExpression->pExpressionRight = pAssignmentExpressionRight;
    pBinaryExpression->token = TK_COMMA;

    *ppExpression = (TExpression*)pBinaryExpression;
  }
}

void ConstantExpression(Parser* ctx, TExpression** ppExpression)
{
  *ppExpression = NULL; //out

                        /*
                        (6.6) constant-expression:
                        conditional-expression
                        */
  ConditionalExpression(ctx, ppExpression);
}


///////////////////////////////////////////////////////////////////////////////


void Designator(Parser* ctx, TDesignator* pDesignator);
void Designator_List(Parser* ctx, TDesignatorList* pDesignatorList);
void Designation(Parser* ctx, TDesignatorList* pDesignatorList);
void Initializer_List(Parser* ctx, TInitializerList* pInitializerList);
//void Assignment_Expression(Parser* ctx, TExpressionStatement* pExpressionStatement, Tokens endToken1, Tokens endToken2);
bool Statement(Parser* ctx, TStatement** ppStatement);
//void Constant_Expression(Parser* ctx, Tokens endToken1, Tokens endToken2, ScannerItemStack* outStack);
void Compound_Statement(Parser* ctx, TStatement** ppStatement);
//void Expression(Parser* ctx, TExpression** pExpression, Tokens endToken1, Tokens endToken2);
void Parameter_Declaration(Parser* ctx, TParameter* pParameterDeclaration);
bool Declaration(Parser* ctx, TAnyDeclaration** ppDeclaration);
void Type_Qualifier_List(Parser* ctx, TTypeQualifierList* pQualifiers);
void Declaration_Specifiers(Parser* ctx, TDeclarationSpecifiers* pDeclarationSpecifiers);

//void Declarator(Parser* ctx, bool bAbstract, TDeclarator** pTDeclarator2);
void Type_Specifier(Parser* ctx, TTypeSpecifier** ppTypeSpecifier);
bool Type_Qualifier(Parser* ctx, TTypeQualifier* pQualifier);
void Initializer(Parser* ctx,
  TInitializer** ppInitializer,
  Tokens endToken1,
  Tokens endToken2);


void Expression_Statement(Parser* ctx, TStatement** ppStatement)
{
  /*
  expression-statement:
  expressionopt;
  */
  TExpressionStatement* pExpression = TExpressionStatement_Create();
  *ppStatement = (TStatement*)pExpression;
  Tokens token = Parser_CurrentToken(ctx);

  if (token != TK_SEMICOLON)
  {
    Expression0(ctx, &pExpression->pExpression);
  }

  Parser_MatchToken(ctx, TK_SEMICOLON, &pExpression->ClueList0);
}

void Selection_Statement(Parser* ctx, TStatement** ppStatement)
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
    TIfStatement* pIfStatement = TIfStatement_Create();
    *ppStatement = (TStatement*)pIfStatement;

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
    TSwitchStatement* pSelectionStatement = TSwitchStatement_Create();
    *ppStatement = (TStatement*)pSelectionStatement;


    Parser_Match(ctx, &pSelectionStatement->ClueList0);


    Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pSelectionStatement->ClueList1);

    Expression0(ctx, &pSelectionStatement->pConditionExpression);


    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pSelectionStatement->ClueList2);

    Statement(ctx, &pSelectionStatement->pExpression);
  }
  break;

  default:
    ASSERT(false);
    break;
  }
}

void Jump_Statement(Parser* ctx, TStatement** ppStatement)
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
    TJumpStatement* pJumpStatement = TJumpStatement_Create();
    pJumpStatement->token = token;
    *ppStatement = (TStatement*)pJumpStatement;

    Parser_Match(ctx, &pJumpStatement->ClueList0);
    String_Set(&pJumpStatement->Identifier, Lexeme(ctx));
    Parser_MatchToken(ctx, TK_IDENTIFIER, &pJumpStatement->ClueList1);
    Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
  }
  break;

  case TK_CONTINUE:
  {
    TJumpStatement* pJumpStatement = TJumpStatement_Create();
    pJumpStatement->token = token;
    *ppStatement = (TStatement*)pJumpStatement;
    Parser_Match(ctx, &pJumpStatement->ClueList0);

    Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
  }
  break;

  case TK_BREAK:
  {
    TJumpStatement* pJumpStatement = TJumpStatement_Create();
    pJumpStatement->token = token;
    *ppStatement = (TStatement*)pJumpStatement;

    Parser_Match(ctx, &pJumpStatement->ClueList0);
    Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
  }
  break;

  case TK_RETURN:
  {
    TJumpStatement* pJumpStatement = TJumpStatement_Create();
    pJumpStatement->token = token;
    *ppStatement = (TStatement*)pJumpStatement;

    token = Parser_Match(ctx, &pJumpStatement->ClueList0);

    if (token != TK_SEMICOLON)
    {
      Expression0(ctx, &pJumpStatement->pExpression);
    }

    Parser_MatchToken(ctx, TK_SEMICOLON, &pJumpStatement->ClueList2);
  }
  break;

  default:
    ASSERT(false);
    break;
  }
}

void Iteration_Statement(Parser* ctx, TStatement** ppStatement)
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
    TWhileStatement* pWhileStatement = TWhileStatement_Create();
    *ppStatement = (TStatement*)pWhileStatement;

    Parser_Match(ctx, &pWhileStatement->ClueList0);

    Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pWhileStatement->ClueList1);

    Expression0(ctx, &pWhileStatement->pExpression);

    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pWhileStatement->ClueList2);

    Statement(ctx, &pWhileStatement->pStatement);
  }
  break;

  case TK_DO:
  {
    TDoStatement* pDoStatement = TDoStatement_Create();
    *ppStatement = (TStatement*)pDoStatement;

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
    TForStatement* pIterationStatement = TForStatement_Create();
    *ppStatement = (TStatement*)pIterationStatement;

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
    ASSERT(false);
    break;
  }
}


void Labeled_Statement(Parser* ctx, TStatement** ppStatement)
{
  /*
  labeled-statement:
  identifier : statement (ver Labeled_StatementLabel)
  case constant-expression : statement
  default : statement
  */
  TLabeledStatement* pLabeledStatement = TLabeledStatement_Create();
  *ppStatement = (TStatement*)pLabeledStatement;
  Tokens token = Parser_CurrentToken(ctx);
  pLabeledStatement->token = token;

  if (token == TK_IDENTIFIER)
  {
    //aqui nao eh um tipo
    String_Set(&pLabeledStatement->Identifier, Lexeme(ctx));

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

void Asm_Statement(Parser* ctx, TStatement** ppStatement)
{
  /*
  __asm assembly-instruction ;opt
  __asm { assembly-instruction-list };opt
  */
  TAsmStatement * pAsmStatement = TAsmStatement_Create();
  *ppStatement = (TStatement*)pAsmStatement;
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

bool Statement(Parser* ctx, TStatement** ppStatement)
{
  ASSERT(*ppStatement == NULL);

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
    //assert(false);
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

#ifdef LANGUAGE_EXTENSIONS
    //type-qualifier-extensions 
    //case TK_AUTO:

  case TK_OPT_QUALIFIER:
  case TK_OWN_QUALIFIER:
  case TK_DTOR_QUALIFIER:
  case TK_MDTOR_QUALIFIER:
    //
#endif

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

void Block_Item(Parser* ctx, TBlockItem** ppBlockItem)
{
  /*
  block-item:
  declaration
  statement
  */
  *ppBlockItem = NULL;
  TStatement* pStatement = NULL;

  if (Statement(ctx, &pStatement))
  {
    *ppBlockItem = (TAnyDeclaration*)pStatement;
    ASSERT(*ppBlockItem != NULL);
  }

  else
  {


    TAnyDeclaration* pDeclaration;
    Declaration(ctx, &pDeclaration);
    *ppBlockItem = (TAnyDeclaration*)pDeclaration;
    ASSERT(*ppBlockItem != NULL);
  }
}

void Block_Item_List(Parser* ctx, TBlockItemList* pBlockItemList)
{
  for (; ;)
  {
    if (ErrorOrEof(ctx))
      break;

    TBlockItem* pBlockItem = NULL;
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

void Compound_Statement(Parser* ctx, TStatement** ppStatement)
{
  /*
  compound-statement:
  { block-item-listopt }
  */
  TCompoundStatement* pCompoundStatement = TCompoundStatement_Create();
  *ppStatement = (TStatement*)pCompoundStatement;

  SymbolMap BlockScope = SYMBOLMAP_INIT;

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

void Struct_Or_Union(Parser* ctx,
  TStructUnionSpecifier* pStructUnionSpecifier)
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
    ASSERT(false);
    break;
  }
}

void Static_Assert_Declaration(Parser* ctx, TStaticAssertDeclaration* pStaticAssertDeclaration)
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

    String_Set(&pStaticAssertDeclaration->Text, Lexeme(ctx));
    Parser_MatchToken(ctx, TK_STRING_LITERAL, &pStaticAssertDeclaration->ClueList3);

    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pStaticAssertDeclaration->ClueList4);

    Parser_MatchToken(ctx, TK_SEMICOLON, &pStaticAssertDeclaration->ClueList5);
  }
}

void Specifier_Qualifier_List(Parser* ctx, TSpecifierQualifierList* pSpecifierQualifierList)
{
  /*specifier-qualifier-list:
  type-specifier specifier-qualifier-listopt
  type-qualifier specifier-qualifier-listopt
  */
  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);
  if (TTypeSpecifier_IsFirst(ctx, token, lexeme))
  {
    if (TSpecifierQualifierList_CanAdd(pSpecifierQualifierList, token, lexeme))
    {
      TTypeSpecifier* pTypeSpecifier = NULL;
      Type_Specifier(ctx, &pTypeSpecifier);
      if (pTypeSpecifier != NULL)
      {
        TSpecifierQualifierList_PushBack(pSpecifierQualifierList, pTypeSpecifier);
      }
    }
    else
    {
      SetError(ctx, "invalid specifier-qualifier-list");
    }

  }
  else if (TTypeQualifier_IsFirst(token))
  {
    TTypeQualifier* pTypeQualifier = TTypeQualifier_Create();
    Type_Qualifier(ctx, pTypeQualifier);
    TSpecifierQualifierList_PushBack(pSpecifierQualifierList, TTypeQualifier_As_TSpecifierQualifier(pTypeQualifier));
  }
  else
  {
    SetError(ctx, "internal error 1");
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

void Struct_Declarator(Parser* ctx,

  TStructDeclarator** ppTDeclarator2)
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
    TExpression* p = NULL;
    ConstantExpression(ctx, &p);
    TExpression_Delete(p);
  }

  else
  {
    TInitDeclarator* pInitDeclarator =
      TInitDeclarator_Create();

    *ppTDeclarator2 = pInitDeclarator;

    ASSERT(pInitDeclarator->pDeclarator == NULL);
    Declarator(ctx, false, &pInitDeclarator->pDeclarator);

    token = Parser_CurrentToken(ctx);

    if (token == TK_COLON)
    {
      Parser_Match(ctx, &pInitDeclarator->ClueList0);

      TExpression* p = NULL;
      ConstantExpression(ctx, &p);
      TExpression_Delete(p);
    }
#ifdef LANGUAGE_EXTENSIONS
    else if (token == TK_EQUALS_SIGN)
    {
      Parser_Match(ctx, &pInitDeclarator->ClueList1); //_defval ou =
      Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
    }
    else if (token == TK__DEFVAL)
    {
      Parser_Match(ctx, &pInitDeclarator->ClueList1); //_defval
      Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL); //(

      Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);

      Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL); //)
    }
#endif
  }
}

void Struct_Declarator_List(Parser* ctx,

  TStructDeclaratorList* pStructDeclarationList)
{
  /*
  struct-declarator-list:
  struct-declarator
  struct-declarator-list , struct-declarator
  */
  TStructDeclarator* pTDeclarator2 = NULL;// TDeclarator_Create();

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

void Struct_Declaration(Parser* ctx,
  TAnyStructDeclaration** ppStructDeclaration)
{
  /**
  struct-declaration:
  specifier-qualifier-list struct-declarator-listopt ;
  static_assert-declaration
  */
  Tokens token = Parser_CurrentToken(ctx);

  if (token != TK__STATIC_ASSERT)
  {
    TStructDeclaration* pStructDeclarationBase = TStructDeclaration_Create();
    *ppStructDeclaration = (TAnyStructDeclaration*)pStructDeclarationBase;
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
    TStaticAssertDeclaration* pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
    *ppStructDeclaration = (TAnyStructDeclaration*)pStaticAssertDeclaration;
    Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
  }
}

void Struct_Declaration_List(Parser* ctx,
  TStructDeclarationList* pStructDeclarationList)
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

  TAnyStructDeclaration* pStructDeclaration = NULL;
  Struct_Declaration(ctx, &pStructDeclaration);
  TStructDeclarationList_PushBack(pStructDeclarationList, pStructDeclaration);


  Tokens token = Parser_CurrentToken(ctx);
  if (token != TK_RIGHT_CURLY_BRACKET)
  {
    //Tem mais?
    Struct_Declaration_List(ctx, pStructDeclarationList);
  }
}

void UnionSetItem(Parser* ctx, TUnionSet* p)
{
  /*
  _union-set-item:
  struct Identifier
  union Identifier
  Identifier
  */
  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);

  TUnionSetItem *pItem = TUnionSetItem_Create();

  if (token == TK_IDENTIFIER)
  {
    String_Set(&pItem->Name, lexeme);
    Parser_Match(ctx, &pItem->ClueList1);
    TUnionSet_PushBack(p, pItem);
  }
  else if (token == TK_STRUCT ||
    token == TK_UNION)
  {
    Parser_Match(ctx, &pItem->ClueList0);

    String_Set(&pItem->Name, lexeme);
    Parser_MatchToken(ctx, TK_IDENTIFIER, &pItem->ClueList1);
    TUnionSet_PushBack(p, pItem);
  }
  else
  {
    SetError(ctx, "invalid token for union set");
  }
}

void UnionSetList(Parser* ctx, TUnionSet* p)
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

void UnionSet(Parser* ctx, TUnionSet* pUnionSet)
{
  /*
  _union-set:
  _union ( _union-set-list )
  */

  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);

  if (token == TK__UNION)
  {
    Parser_Match(ctx, &pUnionSet->ClueList0);


    Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS,
      &pUnionSet->ClueList1);

    UnionSetList(ctx, pUnionSet);

    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS,
      &pUnionSet->ClueList2);
  }
}

void Struct_Or_Union_Specifier(Parser* ctx,
  TStructUnionSpecifier* pStructUnionSpecifier)
{
  /*
  struct-or-union-specifier:
  struct-or-union identifieropt { struct-declaration-list }
  struct-or-union identifier
  */

  /*
  struct-or-union-specifier:
  struct-or-union _union("")opt identifieropt { struct-declaration-list }
  struct-or-union _union("")opt identifier
  */


  Struct_Or_Union(ctx, pStructUnionSpecifier);//TODO


  Tokens token = Parser_CurrentToken(ctx);
  const char* lexeme = Lexeme(ctx);

  pStructUnionSpecifier->Token2 = token;

  if (token == TK__UNION)
  {
    UnionSet(ctx, &pStructUnionSpecifier->UnionSet);
  }

  token = Parser_CurrentToken(ctx);
  lexeme = Lexeme(ctx);

  if (token == TK_IDENTIFIER)
  {
    String_Set(&pStructUnionSpecifier->Name, lexeme);
    Parser_Match(ctx, &pStructUnionSpecifier->ClueList1);
  }

  if (pStructUnionSpecifier->Name != NULL)
  {
    SymbolMap_SetAt(ctx->pCurrentScope, pStructUnionSpecifier->Name, (TTypePointer*)pStructUnionSpecifier);
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
    //struct X *
    // SetError2(ctx, "expected name or {", "");
  }
}

void Enumeration_Constant(Parser* ctx,
  TEnumerator* pEnumerator2)
{
  const char* lexeme = Lexeme(ctx);
  String_Set(&pEnumerator2->Name, lexeme);
  Parser_MatchToken(ctx, TK_IDENTIFIER, &pEnumerator2->ClueList0);
}

bool EnumeratorC(Parser* ctx, TEnumerator* pEnumerator2)
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

void Enumerator_List(Parser* ctx,
  TEnumeratorList* pEnumeratorList2)
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

  TEnumerator* pEnumerator2 = TEnumerator_Create();
  List_Add(pEnumeratorList2, pEnumerator2);

  EnumeratorC(ctx, pEnumerator2);
  SymbolMap_SetAt(ctx->pCurrentScope, pEnumerator2->Name, (TTypePointer*)pEnumerator2);

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

void Enum_Specifier(Parser* ctx, TEnumSpecifier* pEnumSpecifier2)
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
    const char* lexeme = Lexeme(ctx);
    String_Set(&pEnumSpecifier2->Name, lexeme);
    Parser_Match(ctx, &pEnumSpecifier2->ClueList1);
  }

  else
  {
    const char* name = GetName();
    String_Set(&pEnumSpecifier2->Name, name);
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

void Function_Specifier(Parser* ctx,
  TFunctionSpecifier* pFunctionSpecifier)
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

void Storage_Class_Specifier(Parser* ctx,

  TStorageSpecifier* pStorageSpecifier)
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

void Parameter_List(Parser* ctx,
  TParameterList* pParameterList)
{
  /*
  parameter-list:
  parameter-declaration
  parameter-list, parameter-declaration
  */
  Tokens token = Parser_CurrentToken(ctx);

  TParameter*  pParameter = TParameter_Create();
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

void Parameter_Declaration(Parser* ctx,
  TParameter* pParameterDeclaration)
{

  //ctx->pCurrentParameterScope

  /*
  parameter-declaration:
  declaration-specifiers declarator
  declaration-specifiers abstract-declaratoropt
  */
  Declaration_Specifiers(ctx,
    &pParameterDeclaration->Specifiers);

  TDeclarator *pDeclarator = NULL;
  Declarator(ctx, true, &pDeclarator);
  if (pDeclarator)
  {
    pParameterDeclaration->Declarator = *pDeclarator;
  }
}

void Parameter_Type_List(Parser* ctx,
  TParameterTypeList* pParameterList)
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


void Direct_Declarator(Parser* ctx, bool bAbstract, TDirectDeclarator** ppDeclarator2)
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
  TDirectDeclarator *pDirectDeclarator = NULL;

  if (ErrorOrEof(ctx))
    return;


  Tokens token = Parser_CurrentToken(ctx);

  switch (token)
  {
  case TK_LEFT_PARENTHESIS:
  {
    ASSERT(pDirectDeclarator == NULL);
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

    const char* lexeme = Lexeme(ctx);
    String_Set(&pDirectDeclarator->Identifier, lexeme);
    pDirectDeclarator->Position.Line = GetCurrentLine(ctx);
    pDirectDeclarator->Position.FileIndex = GetFileIndex(ctx);
    Parser_Match(ctx, &pDirectDeclarator->ClueList0);
  }
  break;

  default:
    //assert(false);
    break;
  }



  if (pDirectDeclarator == NULL)
  {
    //Por enquanto esta funcao esta sendo usada para
    //abstract declarator que nao tem nome.
    //vou criar aqui por enquanto um cara vazio
    pDirectDeclarator = TDirectDeclarator_Create();
    String_Set(&pDirectDeclarator->Identifier, "");
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
    ASSERT(pDirectDeclarator != NULL);

    token = Parser_CurrentToken(ctx);
    switch (token)
    {
    case TK_LEFT_PARENTHESIS:

      /*
      direct-declarator ( parameter-type-list )
      direct-declarator ( identifier-listopt )
      */
      //      pDirectDeclarator->token = token;
      //      ASSERT(pDirectDeclarator->pParametersOpt == NULL);
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

      //ASSERT(pDirectDeclarator->pParametersOpt == NULL);
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
          ASSERT(pDirectDeclarator->pExpression == NULL);
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
      ASSERT(false);
      break;
    }

    token = Parser_CurrentToken(ctx);
    if (token != TK_LEFT_PARENTHESIS &&   token != TK_LEFT_SQUARE_BRACKET)
    {
      break;
    }
    else
    {
      TDirectDeclarator *pDirectDeclaratorNext = TDirectDeclarator_Create();
      pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
      pDirectDeclarator = pDirectDeclaratorNext;
    }
  }

  token = Parser_CurrentToken(ctx);
  if (token == TK_LEFT_PARENTHESIS)
  {
    //tem mais
    TDirectDeclarator *pDirectDeclaratorNext = NULL;
    Direct_Declarator(ctx, bAbstract, &pDirectDeclaratorNext);
    pDirectDeclarator->pDirectDeclarator = pDirectDeclaratorNext;
  }
  else if (!bAbstract && token == TK_IDENTIFIER)
  {
    //tem mais
    TDirectDeclarator *pDirectDeclaratorNext = NULL;
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
  case TK__AUTO:
  case TK__SIZE:
  case TK_OPT_QUALIFIER:
  case TK_OWN_QUALIFIER:
  case TK_DTOR_QUALIFIER:
  case TK_MDTOR_QUALIFIER:
    bResult = true;
    break;
#endif
  default:
    break;
  }

  return bResult;
}

#ifdef LANGUAGE_EXTENSIONS
void Size_Qualifier(Parser* ctx, TTypeQualifier* pQualifier)
{
  Tokens token = Parser_CurrentToken(ctx);
  pQualifier->Token = token;
  token = Parser_Match(ctx, &pQualifier->ClueList0);

  token = Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, NULL);

  switch (token)
  {
  case TK_IDENTIFIER:
    String_Set(&pQualifier->SizeIdentifier, Lexeme(ctx));
    token = Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
    break;
  }


  token = Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);
}
#endif


bool Type_Qualifier(Parser* ctx, TTypeQualifier* pQualifier)
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
  _auto
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

  case TK__SIZE:
    Size_Qualifier(ctx, pQualifier);
    bResult = true;
    break;
  case TK__AUTO:

    //type-qualifier-extensions 
  case TK_OPT_QUALIFIER:
  case TK_OWN_QUALIFIER:
  case TK_DTOR_QUALIFIER:
  case TK_MDTOR_QUALIFIER:
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

void Type_Qualifier_List(Parser* ctx,
  TTypeQualifierList* pQualifiers)
{
  /*
  type-qualifier-list:
  type-qualifier
  type-qualifier-list type-qualifier
  */

  TTypeQualifier* pTypeQualifier = TTypeQualifier_Create();
  Type_Qualifier(ctx, pTypeQualifier);
  TTypeQualifierList_PushBack(pQualifiers, pTypeQualifier);

  if (IsTypeQualifierToken(Parser_CurrentToken(ctx)))
  {
    Type_Qualifier_List(ctx, pQualifiers);
  }

}


void Pointer(Parser* ctx, TPointerList* pPointerList)
{
  /*
  pointer:
  * type-qualifier-listopt
  * type-qualifier-listopt pointer
  */

  TPointer* pPointer = TPointer_Create();

  Tokens token = Parser_CurrentToken(ctx);

  if (token == TK_ASTERISK)
  {
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
void Declarator(Parser* ctx, bool bAbstract, TDeclarator** ppTDeclarator2)
{
  *ppTDeclarator2 = NULL; //out
  TDeclarator* pDeclarator = TDeclarator_Create();
  /*
  declarator:
  pointeropt direct-declarator
  */
  Tokens token = Parser_CurrentToken(ctx);

  if (token == TK_ASTERISK)
  {
    Pointer(ctx, &pDeclarator->PointerList);
  }

  ASSERT(pDeclarator->pDirectDeclarator == NULL);
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

bool Alignment_Specifier(Parser* ctx,
  TAlignmentSpecifier* pAlignmentSpecifier)
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
    ASSERT(false);//TODO
    Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, NULL);
    bResult = true;
  }

  return bResult;
}


bool TTypeSpecifier_IsFirst(Parser* ctx, Tokens token, const char* lexeme)
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


void AtomicTypeSpecifier(Parser* ctx,
  TTypeSpecifier** ppTypeSpecifier)
{
  assert(false); //tODO criar TAtomicTypeSpecifier
                 /*
                 atomic-type-specifier:
                 _Atomic ( type-name )
                 */
  TAtomicTypeSpecifier* pAtomicTypeSpecifier =
    TAtomicTypeSpecifier_Create();

  *ppTypeSpecifier = TAtomicTypeSpecifier_As_TTypeSpecifier(pAtomicTypeSpecifier);

  Parser_MatchToken(ctx, TK__ATOMIC, &pAtomicTypeSpecifier->ClueList0);

  Parser_MatchToken(ctx, TK_LEFT_PARENTHESIS, &pAtomicTypeSpecifier->ClueList1);

  TypeName(ctx, &pAtomicTypeSpecifier->TypeName);

  Parser_MatchToken(ctx, TK_RIGHT_PARENTHESIS, &pAtomicTypeSpecifier->ClueList2);
}

void Type_Specifier(Parser* ctx, TTypeSpecifier** ppTypeSpecifier)
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

  const char* lexeme = Lexeme(ctx);
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
    TSingleTypeSpecifier*  pSingleTypeSpecifier =
      TSingleTypeSpecifier_Create();

    pSingleTypeSpecifier->Token = token;
    bResult = true;

    Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);

    *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;
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
    ASSERT(*ppTypeSpecifier == NULL);
    bResult = true;
    TStructUnionSpecifier* pStructUnionSpecifier = TStructUnionSpecifier_Create();

    *ppTypeSpecifier = (TTypeSpecifier*)pStructUnionSpecifier;
    Struct_Or_Union_Specifier(ctx, pStructUnionSpecifier);
  }
  break;

  case TK_ENUM:
  {
    ASSERT(*ppTypeSpecifier == NULL);
    bResult = true;
    TEnumSpecifier* pEnumSpecifier2 = TEnumSpecifier_Create();
    *ppTypeSpecifier = (TTypeSpecifier*)pEnumSpecifier2;
    Enum_Specifier(ctx, pEnumSpecifier2);
  }
  break;

  case TK_IDENTIFIER:
  {
    int bIsTypedef = IsTypeName(ctx, TK_IDENTIFIER, lexeme);
    if (bIsTypedef)
    {
      TSingleTypeSpecifier* pSingleTypeSpecifier = TSingleTypeSpecifier_Create();
      pSingleTypeSpecifier->Token = token;
      String_Set(&pSingleTypeSpecifier->TypedefName, lexeme);
      bResult = true;

      Parser_Match(ctx, &pSingleTypeSpecifier->ClueList0);
      *ppTypeSpecifier = (TTypeSpecifier*)pSingleTypeSpecifier;

    }
    else
    {
      ASSERT(false); //temque chegar aqui limpo ja
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

bool Declaration_Specifiers_IsFirst(Parser* ctx, Tokens token, const char* lexeme)
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

void Declaration_Specifiers(Parser* ctx,
  TDeclarationSpecifiers* pDeclarationSpecifiers)
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
  const char* lexeme = Lexeme(ctx);

  if (TStorageSpecifier_IsFirst(token))
  {
    TStorageSpecifier* pStorageSpecifier = TStorageSpecifier_Create();

    Storage_Class_Specifier(ctx, pStorageSpecifier);

    TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, TStorageSpecifier_As_TDeclarationSpecifier(pStorageSpecifier));
  }
  else if (TTypeSpecifier_IsFirst(ctx, token, lexeme))
  {
    if (TDeclarationSpecifiers_CanAddSpeficier(pDeclarationSpecifiers,
      token,
      lexeme))
    {
      TTypeSpecifier* pTypeSpecifier = NULL;
      Type_Specifier(ctx, &pTypeSpecifier);
      TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, pTypeSpecifier);
    }
    else
    {
      SetError(ctx, "double typedef");
    }

  }
  else if (TTypeQualifier_IsFirst(token))
  {
    TTypeQualifier* pTypeQualifier = TTypeQualifier_Create();
    Type_Qualifier(ctx, pTypeQualifier);
    TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, TTypeQualifier_As_TSpecifierQualifier(pTypeQualifier));
  }
  else if (TFunctionSpecifier_IsFirst(token))
  {
    TFunctionSpecifier* pFunctionSpecifier = TFunctionSpecifier_Create();
    Function_Specifier(ctx, pFunctionSpecifier);
    TDeclarationSpecifiers_PushBack(pDeclarationSpecifiers, TFunctionSpecifier_As_TDeclarationSpecifier(pFunctionSpecifier));
  }
  else if (TAlignmentSpecifier_IsFirst(token))
  {
    ASSERT(false);
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



void Initializer(Parser* ctx,
  TInitializer** ppInitializer,
  Tokens endToken1,
  Tokens endToken2)
{
  ASSERT(*ppInitializer == NULL);
  /*
  initializer:
  assignment-expression
  { initializer-list }
  { initializer-list , }
  */

  /*
  initializer:
  _default
  assignment-expression
  _defaultopt { initializer-list }
  _defaultopt { initializer-list , }
  */

  Tokens token = Parser_CurrentToken(ctx);
  if (token == TK__DEFAULT ||
    token == TK_DEFAULT)
  {
    TInitializerListType* pTInitializerList =
      TInitializerListType_Create();

    pTInitializerList->bDefault = true;

    *ppInitializer = (TInitializer*)pTInitializerList;

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
      TInitializerListType* pTInitializerList =
        TInitializerListType_Create();


      *ppInitializer = (TInitializer*)pTInitializerList;

      Parser_Match(ctx, &pTInitializerList->ClueList1);

      Initializer_List(ctx, &pTInitializerList->InitializerList);

      Parser_MatchToken(ctx, TK_RIGHT_CURLY_BRACKET,
        &pTInitializerList->ClueList2);
    }

    else
    {
      TExpression* pExpression = NULL;
      AssignmentExpression(ctx, &pExpression);
      *ppInitializer = (TInitializer*)pExpression;
    }
  }
}

void Initializer_List(Parser* ctx, TInitializerList* pInitializerList)
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

    TInitializerListItem* pTInitializerListItem = TInitializerListItem_Create();
    List_Add(pInitializerList, pTInitializerListItem);
    Tokens token = Parser_CurrentToken(ctx);
#ifdef LANGUAGE_EXTENSIONS
    if (token == TK_RIGHT_CURLY_BRACKET)
    {
      //Empty initializer
      break;
    }
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

void Designation(Parser* ctx, TDesignatorList* pDesignatorList)
{
  /*
  designation:
  designator-list =
  */
  Designator_List(ctx, pDesignatorList);
  Parser_MatchToken(ctx, TK_EQUALS_SIGN, NULL);//tODO
}

void Designator_List(Parser* ctx, TDesignatorList* pDesignatorList)
{
  // http://www.drdobbs.com/the-new-c-declarations-initializations/184401377
  /*
  designator-list:
  designator
  designator-list designator
  */
  TDesignator* pDesignator = TDesignator_Create();
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
      TDesignator* pDesignatorNew = TDesignator_Create();
      Designator(ctx, pDesignatorNew);
      List_Add(pDesignatorList, pDesignatorNew);
    }

    else
    {
      break;
    }
  }
}

void Designator(Parser* ctx, TDesignator* p)
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

    String_Set(&p->Name, Lexeme(ctx));
    Parser_MatchToken(ctx, TK_IDENTIFIER, NULL);
  }
}

void Init_Declarator(Parser* ctx,
  TInitDeclarator** ppDeclarator2)
{
  /*
  init-declarator:
  declarator
  declarator = initializer
  */
  TInitDeclarator* pInitDeclarator =
    TInitDeclarator_Create();

  ASSERT(pInitDeclarator->pDeclarator == NULL);
  Declarator(ctx, false, &pInitDeclarator->pDeclarator);
  Tokens token = Parser_CurrentToken(ctx);

  const char* declaratorName = TInitDeclarator_FindName(pInitDeclarator);
  if (declaratorName)
  {
    //Fica em um contexto que vive so durante a declaracao
    //depois eh substituido

    SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer*)pInitDeclarator);
  }

  //Antes do =
  *ppDeclarator2 = pInitDeclarator;

  if (token == TK_EQUALS_SIGN)
  {
    ASSERT(*ppDeclarator2 != NULL);

    Parser_Match(ctx, &pInitDeclarator->ClueList0);

    Initializer(ctx, &pInitDeclarator->pInitializer, TK_SEMICOLON, TK_SEMICOLON);
    ////TNodeClueList_MoveToEnd(&pInitDeclarator->ClueList, &ctx->Scanner.ClueList);
  }
}

void Init_Declarator_List(Parser* ctx,
  TInitDeclaratorList* pInitDeclaratorList)
{
  /*
  init-declarator-list:
  init-declarator
  init-declarator-list , init-declarator
  */

  TInitDeclarator* pInitDeclarator = NULL;
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

void Parse_Declarations(Parser* ctx, TDeclarations* declarations);

void GroupDeclaration(Parser* ctx,
  TGroupDeclaration** ppGroupDeclaration)
{
  /*
  CPRIME
  group-declaration:
  default identifier { declarations opt }
  */

  TGroupDeclaration* p = TGroupDeclaration_Create();
  *ppGroupDeclaration = p;

  Parser_Match(ctx, &p->ClueList0);//default


  String_Set(&p->Identifier, Lexeme(ctx));
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


bool  Declaration(Parser* ctx,
  TAnyDeclaration** ppDeclaration)
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
    TStaticAssertDeclaration* pStaticAssertDeclaration = TStaticAssertDeclaration_Create();
    *ppDeclaration = (TAnyDeclaration*)pStaticAssertDeclaration;
    Static_Assert_Declaration(ctx, pStaticAssertDeclaration);
    bHasDeclaration = true;

  }
  else if (token == TK_DEFAULT)
  {
    TGroupDeclaration* p = NULL;
    GroupDeclaration(ctx, &p);
    *ppDeclaration = p;//moved
    bHasDeclaration = true;
  }
  else
  {
    TDeclaration* pFuncVarDeclaration = TDeclaration_Create();

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
      *ppDeclaration = (TAnyDeclaration*)pFuncVarDeclaration;
      pFuncVarDeclaration->FileIndex = GetFileIndex(ctx);
      pFuncVarDeclaration->Line = GetCurrentLine(ctx);
      //ASSERT(pFuncVarDeclaration->FileIndex >= 0);

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

        SymbolMap BlockScope = SYMBOLMAP_INIT;

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
          const char* declaratorName = TInitDeclarator_FindName(pInitDeclarator);



          if (declaratorName != NULL)
          {
            SymbolMap_SetAt(ctx->pCurrentScope, declaratorName, (TTypePointer*)pFuncVarDeclaration);
          }

          //ctx->
        }
        //
        if (token == TK__DEFAULT ||
          token == TK_DEFAULT)
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
          //Ativa o escopo dos parametros
          //Adiconar os parametros em um escopo um pouco a cima.
          SymbolMap BlockScope2 = SYMBOLMAP_INIT;

          TInitDeclarator* pDeclarator3 =
            pFuncVarDeclaration->InitDeclaratorList.pHead;

          ForEachListItem(TParameter, pParameter, &pDeclarator3->pDeclarator->pDirectDeclarator->Parameters.ParameterList)
          {
            const char* parameterName = TDeclarator_GetName(&pParameter->Declarator);
            if (parameterName != NULL)
            {
              SymbolMap_SetAt(&BlockScope2, parameterName, (TTypePointer*)pParameter);
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
          TStatement* pStatement;
          Compound_Statement(ctx, &pStatement);
          //TODO cast

          ctx->pCurrentScope = BlockScope2.pPrevious;
          SymbolMap_Destroy(&BlockScope2);


          pFuncVarDeclaration->pCompoundStatementOpt = (TCompoundStatement*)pStatement;
        }

        else
        {
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


void Parse_Declarations(Parser* ctx, TDeclarations* declarations)
{
  int declarationIndex = 0;

  while (!ErrorOrEof(ctx))
  {

    TAnyDeclaration* pDeclarationOut = NULL;
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
      TEofDeclaration* pEofDeclaration =
        TEofDeclaration_Create();
      //ok
      Parser_Match(ctx, &pEofDeclaration->ClueList0);
      TDeclarations_PushBack(declarations, pEofDeclaration);
    }

    if (Parser_HasError(ctx))
      break;

  }



}

void Parser_Main(Parser* ctx, TDeclarations* declarations)
{
  Parse_Declarations(ctx, declarations);
}

static void TFileMapToStrArray(TFileMap* map, TFileArray* arr)
{
  TFileArray_Reserve(arr, map->Size);
  arr->Size = map->Size;

  for (int i = 0; i < map->buckets.size; i++)
  {
    Bucket*  data = map->buckets.data[i];

    if (data != NULL)
    {
      for (int k = 0; k < data->size; k++)
      {
        BucketItem* node = data->data[k];
        TFile* pFile = (TFile*)node->data;

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

bool GetAST(const char*  filename,
  const char* configFileName /*optional*/,

  TProgram* pProgram)
{
  bool bResult = false;


  Parser parser;

  if (configFileName != NULL)
  {
    //opcional   
    String fullConfigFilePath = STRING_INIT;
    GetFullPath(configFileName, &fullConfigFilePath);

    Parser_InitFile(&parser, fullConfigFilePath);
    Parser_Main(&parser, &pProgram->Declarations);

    //Some com o arquivo de config
    TScannerItemList_Clear(&parser.ClueList);
    BasicScannerStack_Pop(&parser.Scanner.stack);
    //Some com o arquivo de config
    String_Destroy(&fullConfigFilePath);
  }

  String fullFileNamePath = STRING_INIT;
  GetFullPath(filename, &fullFileNamePath);


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
  String_Destroy(&fullFileNamePath);

  return bResult;
}



bool GetASTFromString(const char*  sourceCode,
  TProgram* pProgram)
{
  bool bResult = false;

  Parser parser;

  Parser_InitString(&parser, "source", sourceCode);
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




#if 0


void PrintString(const char* psz)
{
  printf("\"");

  while (*psz)
  {
    switch (*psz)
    {
    case '"':
      printf("\\\"");
      break;

    case '/':
      printf("\\/");
      break;

    case '\b':
      printf("\\b");
      break;

    case '\f':
      printf("\\f");
      break;

    case '\n':
      printf("\\n");
      break;

    case L'\r':
      printf("\\r");
      break;

    case L'\t':
      printf("\\t");
      break;

    case L'\\':
      printf("\\\\");
      break;

    default:
      printf("%c", *psz);
      break;
    }

    psz++;
  }

  printf("\"");
}

void PrintTokens(Scanner* scanner)
{
  while (Scanner_TokenAt(scanner) != TK_EOF)
  {
    printf("%s : ", Scanner_TokenString(scanner));
    PrintString(Scanner_Lexeme(scanner));
    printf("\n");
    Scanner_Next(scanner);
  }
}

void PrintTokensOfFile(const char* fileName)
{
  Scanner scanner;
  Scanner_Init(&scanner);
  Scanner_IncludeFile(&scanner, fileName, FileIncludeTypeFullPath);
  PrintTokens(&scanner);
  Scanner_Destroy(&scanner);
}


void PrintPreprocessedToConsole(const char* fileIn)
{
  Scanner scanner;
  Scanner_Init(&scanner);
  Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);
  scanner.bIncludeSpaces = true;

  while (Scanner_TokenAt(&scanner) != TK_EOF)
  {
    Tokens token = Scanner_Top(&scanner)->currentItem.token;
    const char* lexeme = Scanner_Top(&scanner)->currentItem.lexeme.c_str;

    if (token == TK_BREAKLINE)
    {
      printf("%s", lexeme);
    }

    if (token == TK_LINE_COMMENT ||
      token == TK_COMMENT)
    {
      //fprintf(fp, "%s", lexeme);
    }
    else
    {
      printf("%s", lexeme);
    }

    Scanner_Next(&scanner);
  }

  Scanner_Destroy(&scanner);
}


void GetUnprocessedTokens(const char* fileIn/*, JObj* pOutArray*/)
{
  BasicScanner scanner;
  BasicScanner_InitFile(&scanner, fileIn);

  while (scanner.currentItem.token != TK_EOF)
  {
    Tokens token = scanner.currentItem.token;
    const char* lexeme = scanner.currentItem.lexeme.c_str;
    //JObj *pNew = JObj_PushNewArray(pOutArray);
    //JObj_PushString(pNew, TokenToString(token));
    //JObj_PushString(pNew, lexeme);
    BasicScanner_Next(&scanner);
  }

  BasicScanner_Destroy(&scanner);
}

void GetProcessedTokens2(const char* fileIn/*, JObj* pOutArray*/)
{
  Scanner scanner;
  Scanner_Init(&scanner);
  Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);

  while (Scanner_TokenAt(&scanner) != TK_EOF)
  {
    Tokens token = Scanner_TokenAt(&scanner);
    const char* lexeme = Scanner_Lexeme(&scanner);
    //JObj *pNew = JObj_PushNewArray(pOutArray);
    //JObj_PushString(pNew, TokenToString(token));
    //JObj_PushString(pNew, lexeme);
    Scanner_Next(&scanner);
  }

  Scanner_Destroy(&scanner);
}

void GetProcessedTokens(const char* fileIn/*, JObj* pOutArray*/)
{
  Scanner scanner;
  Scanner_Init(&scanner);
  scanner.bIncludeSpaces = true;
  Scanner_IncludeFile(&scanner, fileIn, FileIncludeTypeFullPath);

  while (Scanner_TokenAt(&scanner) != TK_EOF)
  {
    Tokens token = Scanner_Top(&scanner)->currentItem.token;
    const char* lexeme = Scanner_Top(&scanner)->currentItem.lexeme.c_str;
    //JObj *pNew = JObj_PushNewObject(pOutArray);
    //JObj_SetString(pNew, "token", TokenToString(token));
    //JObj_SetString(pNew, "lexeme", lexeme);
    Scanner_Next(&scanner);
  }

  Scanner_Destroy(&scanner);
}



#endif




#include <limits.h>
#include <ctype.h>


void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext)
{
  const char* end; /* end of processed string */
  const char* p;      /* search pointer */
  const char* s;      /* copy pointer */

                      /* extract drive name */
  if (path[0] && path[1] == ':') {
    if (drv) {
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
  for (p = end; p>path && *--p != '\\' && *p != '/'; )
    if (*p == '.') {
      end = p;
      break;
    }

  if (ext)
    for (s = end; (*ext = *s++); )
      ext++;

  /* search for end of directory name */
  for (p = end; p>path; )
    if (*--p == '\\' || *p == '/') {
      p++;
      break;
    }

  if (name) {
    for (s = p; s<end; )
      *name++ = *s++;

    *name = '\0';
  }

  if (dir) {
    for (s = path; s<p; )
      *dir++ = *s++;

    *dir = '\0';
  }
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


void GetFullDir(const char* fileName, String* out)
{
  char buffer[CPRIME_MAX_PATH];

#ifdef WIN32

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
  String_Attach(out, StrBuilder_Release(&s));
  StrBuilder_Destroy(&s);
}


void GetFullPath(const char* fileName, String* out)
{
  char buffer[CPRIME_MAX_PATH];

#ifdef WIN32


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
  String_Attach(out, StrBuilder_Release(&s));
  StrBuilder_Destroy(&s);
}





void PPToken_Destroy(PPToken * p) _default
{
  String_Destroy(&p->Lexeme);
  TokenSet_Destroy(&p->HiddenSet);
}

void PPToken_Swap(PPToken * pA, PPToken * pB)
{
  PPToken temp = *pA;
  *pA = *pB;
  *pB = temp;
}

PPToken*  PPToken_Clone(PPToken* p)
{
  PPToken* pNew = PPToken_Create(p->Lexeme, p->Token);
  TokenSetAppendCopy(&pNew->HiddenSet, &p->HiddenSet);
  return pNew;
}

PPToken* PPToken_Create(const char* s, PPTokenType token)
{
  PPToken* p = (PPToken*)malloc(sizeof(PPToken));

  if (p != 0)
  {
    PPToken t = TOKEN_INIT;
    *p = t;
    String_Set(&p->Lexeme, s);
    p->Token = token;
  }
  else
  {
    ASSERT(false);
  }

  return p;
}

void PPToken_Delete(PPToken * p) _default
{
  if (p != NULL)
  {
    PPToken_Destroy(p);
    free((void*)p);
  }
}

void PPToken_DeleteVoid(void* pv)
{
  PPToken_Delete((PPToken *)pv);
}

bool PPToken_IsIdentifier(PPToken* pHead)
{
  return pHead->Token == PPTokenType_Identifier;
}

bool PPToken_IsSpace(PPToken* pHead)
{
  if (pHead->Token == PPTokenType_Spaces)
  {
    return true;
  }
  return false;
}

bool PPToken_IsStringizingOp(PPToken* pHead)
{
  return pHead->Lexeme[0] == '#' &&
    pHead->Lexeme[1] == '\0';
}

bool PPToken_IsConcatOp(PPToken* pHead)
{
  return pHead->Lexeme[0] == '#' &&
    pHead->Lexeme[1] == '#' &&
    pHead->Lexeme[2] == '\0';
}

bool PPToken_IsStringLit(PPToken* pHead)
{
  return pHead->Token == PPTokenType_StringLiteral;
}

bool PPToken_IsCharLit(PPToken* pHead)
{
  return pHead->Token == PPTokenType_CharConstant;
}

bool PPToken_IsOpenPar(PPToken* pHead)
{
  return pHead->Lexeme[0] == '('&&
    pHead->Lexeme[1] == '\0';
}

bool PPToken_IsChar(PPToken* pHead, char ch)
{
  return pHead->Lexeme[0] == ch &&
    pHead->Lexeme[1] == '\0';
}

bool PPToken_IsLexeme(PPToken* pHead, const char* lexeme)
{
  return strcmp(pHead->Lexeme, lexeme) == 0;
}
BasicScanner* Scanner_Top(Scanner* pScanner);

void Scanner_MatchDontExpand(Scanner* pScanner);

PPTokenType TokenToPPToken(Tokens token)
{
  PPTokenType result = PPTokenType_Other;

  switch (token)
  {
  case TK_AUTO:
  case TK__AUTO:
  case TK__SIZE:
  case TK_BREAK:
  case TK_CASE:
  case TK_CHAR:
  case TK_CONST:
  case TK_CONTINUE:
  case TK_DEFAULT:
  case TK__DEFAULT:
  case TK__DEFVAL:
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
    ASSERT(false);
    result = PPTokenType_Punctuator;
    break;
  }

  return result;
}

TFile* TFile_Create() _default
{
  TFile *p = (TFile*)malloc(sizeof * p);
  if (p != NULL)
  {
    String_Init(&p->FullPath);
    String_Init(&p->IncludePath);
    p->FileIndex = 0;
    p->PragmaOnce = false;
    p->bDirectInclude = false;
    p->bSystemLikeInclude = false;
  }
  return p;
}

void TFile_Destroy(TFile* p) _default
{
  String_Destroy(&p->FullPath);
  String_Destroy(&p->IncludePath);
}

void TFile_Delete(TFile* p) _default
{
  if (p != NULL)
  {
    TFile_Destroy(p);
    free((void*)p);
  }
}

void TFile_DeleteVoid(void* p)
{
  TFile_Delete((TFile*)p);
}

void TFileMap_Destroy(TFileMap* p)
{
  Map_Destroy(p, TFile_DeleteVoid);
}

void TFileArray_Init(TFileArray* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}
void TFileArray_Destroy(TFileArray* p) _default
{
  for (int i = 0; i < p->Size; i++)
  {
    TFile_Delete(p->pItems[i]);
  }
  free((void*)p->pItems);
}

void TFileArray_Reserve(TFileArray* p, int n) _default
{
  if (n > p->Capacity)
  {
    TFile** pnew = p->pItems;
    pnew = (TFile**)realloc(pnew, n * sizeof(TFile*));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = n;
    }
  }
}

void TFileArray_PushBack(TFileArray* p, TFile* pItem) _default
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

Result TFileMap_Set(TFileMap* map, const char* key, TFile* pFile)
{
  // tem que ser case insensitive!
  ASSERT(IsFullPath(key));
  // converter
  // Ajusta o file index de acordo com a entrada dele no mapa
  pFile->FileIndex = map->Size;
  Result result = Map_Set(map, key, pFile);
  String_Set(&pFile->FullPath, key);
  return result;
}

TFile* TFileMap_Find(TFileMap* map, const char* key)
{
  // tem que ser case insensitive!
  return (TFile*)Map_Find2(map, key);
}

Result TFileMap_DeleteItem(TFileMap* map, const char* key)
{
  return Map_DeleteItem(map, key, TFile_DeleteVoid);
}



bool IsIncludeState(State e)
{
  return e == NONE || e == I1 || e == E1;
}

void StackInts_Init(StackInts* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}
void StackInts_Destroy(StackInts* p) /*_default*/
{
  free(p->pItems);
}

void StackInts_Pop(StackInts* p) /*_default*/
{
  if (p->Size > 0)
  {
    p->Size--;
  }
}

void StackInts_Reserve(StackInts* p, int n) _default
{
  if (n > p->Capacity)
  {
    State* pnew = p->pItems;
    pnew = (State*)realloc(pnew, n * sizeof(State));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = n;
    }
  }
}

void StackInts_PushBack(StackInts* p, State e) _default
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

State StateTop(Scanner* pScanner)
{
  if (pScanner->StackIfDef.Size == 0)
    return NONE;

  return pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1];
}

void StatePush(Scanner* pScanner, State s)
{
  StackInts_PushBack(&pScanner->StackIfDef, s);
}

void StatePop(Scanner* pScanner)
{
  StackInts_Pop(&pScanner->StackIfDef);
}

void Scanner_GetError(Scanner* pScanner, StrBuilder* str)
{
  StrBuilder_Append(str, pScanner->DebugString.c_str);
  StrBuilder_Append(str, "\n");

  ForEachBasicScanner(p, pScanner->stack)
  {
    StrBuilder_AppendFmt(str, "%s(%d)\n",
      p->stream.NameOrFullPath,
      p->stream.currentLine);
  }
}


void Scanner_GetFilePositionString(Scanner* pScanner, StrBuilder* sb)
{
  BasicScanner* pScannerTop = Scanner_Top(pScanner);

  if (pScannerTop != NULL)
  {
    StrBuilder_Set(sb,
      pScannerTop->stream.NameOrFullPath);
  }

  if (pScannerTop)
  {
    StrBuilder_AppendFmt(sb, "(%d): ", pScannerTop->stream.currentLine);
  }
  else
  {
    StrBuilder_Append(sb, "(1): ");
  }
}

void Scanner_SetError(Scanner* pScanner, const char* fmt, ...)
{
  if (!pScanner->bError)
  {
    pScanner->bError = true;

    if (Scanner_Top(pScanner))
    {
      StrBuilder_AppendFmt(&pScanner->ErrorString, "%s(%d) :",
        Scanner_Top(pScanner)->stream.NameOrFullPath,
        Scanner_Top(pScanner)->stream.currentLine);
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

void Scanner_PrintDebug(Scanner* pScanner)
{
  printf("\ndebug---\n");

  ForEachBasicScanner(p, pScanner->stack)
  {
    printf("stream %s\n", p->stream.NameOrFullPath);
    printf("line, col = %d %d\n", p->stream.currentLine, p->stream.currentCol);
  }

  printf("---\n");
}

static Result AddStandardMacro(Scanner* pScanner, const char* name,
  const char* value)
{
  Macro* pDefine1 = Macro_Create();
  String_Set(&pDefine1->Name, name);
  // TODO tipo do token
  TokenArray_PushBack(&pDefine1->TokenSequence,
    PPToken_Create(value, PPTokenType_Other));
  pDefine1->FileIndex = 0;
  MacroMap_SetAt(&pScanner->Defines2, name, pDefine1);
  return RESULT_OK;
}
static void Scanner_PushToken(Scanner* pScanner, Tokens token,
  const char* lexeme, bool bActive);

static Result Scanner_InitCore(Scanner* pScanner)
{
  TScannerItemList_Init(&pScanner->AcumulatedTokens);

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

  return RESULT_OK;
}

Result Scanner_InitString(Scanner* pScanner, const char* name,
  const char* text)
{
  Scanner_InitCore(pScanner);

  BasicScanner* pNewScanner;
  Result result =
    BasicScanner_Create(&pNewScanner, name, text, BasicScannerType_Macro);
  BasicScannerStack_Push(&pScanner->stack, pNewScanner);
  return result;
}

Result PushExpandedMacro(Scanner* pScanner,

  const char* callString,
  const char* defineContent)
{
  if (pScanner->bError)
  {
    return RESULT_FAIL;
  }

  BasicScanner* pNewScanner;
  Result result = BasicScanner_Create(&pNewScanner, callString, /*defineName*/
    defineContent, BasicScannerType_Macro);

  if (result == RESULT_OK)
  {
    pNewScanner->bMacroExpanded = true;
    BasicScanner_Match(pNewScanner); // inicia
    BasicScannerStack_Push(&pScanner->stack, pNewScanner);
  }

  return result;
}

bool Scanner_GetFullPath(Scanner* pScanner, const char* fileName,
  bool bQuotedForm, String* fullPathOut)
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
    // String s = STRING_INIT;
    // GetFullPath(fileName, &s);
    // String_Destroy(&s);
    if (IsFullPath(fileName))
    {
      // Se ja vier com fullpath?? este caso esta cobrindo
      // mas deve ter uma maneira melhor de verificar se eh um fullpath ja
      bFullPathFound = true;
      String_Set(fullPathOut, fileName);
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
        String fullPath;
        String_InitWith(&fullPath, NULL);
        GetFullPath(fileName, &fullPath);
        bool bFileExists = FileExists(fullPath);

        if (bFileExists)
        {
          String_Swap(&fullPath, fullPathOut);
          bFullPathFound = true;
        }

        String_Destroy(&fullPath);
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
      const char* pItem = pScanner->IncludeDir.pItems[i];
      StrBuilder_Set(&path, pItem);

      //barra para o outro lado funciona
      //windows e linux
      StrBuilder_Append(&path, "/");

      StrBuilder_Append(&path, fileName);
      bool bFileExists = FileExists(path.c_str);

      if (bFileExists)
      {
        String_Set(fullPathOut, StrBuilder_Release(&path));
        bFullPathFound = true;
        break;
      }
    }

    StrBuilder_Destroy(&path);
  }

  return bFullPathFound;
}

void Scanner_IncludeFile(Scanner* pScanner, const char* includeFileName,
  FileIncludeType fileIncludeType, bool bSkipBof)
{
  if (pScanner->bError)
  {
    return;
  }

  bool bDirectInclude = false;

  String fullPath = STRING_INIT;
  String_InitWith(&fullPath, "");
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
    String_Set(&fullPath, includeFileName);
    bHasFullPath = true;
    break;
  };

  if (bHasFullPath)
  {
    TFile* pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

    if (pFile != NULL && pFile->PragmaOnce)
    {
      // foi marcado como pragma once.. nao faz nada
      // tenho q enviar um comando
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
        String_Set(&pFile->IncludePath, includeFileName);
        TFileMap_Set(&pScanner->FilesIncluded, fullPath, pFile); // pfile Moved
      }

      BasicScanner* pNewScanner = NULL;
      Result result = BasicScanner_CreateFile(fullPath, &pNewScanner);

      if (result == RESULT_OK)
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

  String_Destroy(&fullPath);
}

const char* Scanner_GetStreamName(Scanner* pScanner)
{
  const char* streamName = NULL;

  BasicScanner* p = Scanner_Top(pScanner);
  streamName = p ? p->stream.NameOrFullPath : NULL;

  return streamName;
}

Result Scanner_Init(Scanner* pScanner)
{
  return Scanner_InitCore(pScanner);
}

void Scanner_Destroy(Scanner* pScanner) _default
{
  BasicScannerStack_Destroy(&pScanner->stack);
  MacroMap_Destroy(&pScanner->Defines2);
  StackInts_Destroy(&pScanner->StackIfDef);
  TFileMap_Destroy(&pScanner->FilesIncluded);
  StrArray_Destroy(&pScanner->IncludeDir);
  StrBuilder_Destroy(&pScanner->DebugString);
  StrBuilder_Destroy(&pScanner->ErrorString);
  TScannerItemList_Destroy(&pScanner->AcumulatedTokens);
}

/*int Scanner_GetCurrentLine(Scanner* pScanner)
{
ASSERT(!pScanner->bHasLookAhead);

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

int Scanner_GetFileIndex(Scanner* pScanner)
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

  // ASSERT(fileIndex >= 0);
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

BasicScanner* Scanner_Top(Scanner* pScanner)
{
  return pScanner->stack;
}

// int Scanner_Line(Scanner* pScanner)
//{
//  ASSERT(!pScanner->bHasLookAhead);
// return Scanner_Top(pScanner)->stream.currentLine;
//}

// int Scanner_Col(Scanner* pScanner)
//{
//  ASSERT(!pScanner->bHasLookAhead);
//    return Scanner_Top(pScanner)->stream.currentCol;
//}

void IgnorePreProcessorv2(BasicScanner* pBasicScanner, StrBuilder* strBuilder)
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

void GetDefineString(Scanner* pScanner, StrBuilder* strBuilder)
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

    if (token == TK_COMMENT || token == TK_LINE_COMMENT)
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

Macro* Scanner_FindPreprocessorItem2(Scanner* pScanner, const char* key)
{
  Macro* pMacro = MacroMap_Find(&pScanner->Defines2, key);
  return pMacro;
}

bool Scanner_IsLexeme(Scanner* pScanner, const char* psz)
{
  return BasicScanner_IsLexeme(Scanner_Top(pScanner), psz);
}

int PreprocessorExpression(Parser* parser)
{
  // Faz o parser da expressão
  TExpression* pExpression = NULL;
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

int EvalExpression(const char* s, Scanner* pScanner)
{
  MacroMap* pDefines = &pScanner->Defines2;
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

static void GetMacroArguments(Scanner* pScanner, BasicScanner* pBasicScanner,
  Macro* pMacro, TokenArray* ppTokenArray,
  StrBuilder* strBuilder)
{
  // StrBuilder_Append(strBuilderResult, Scanner_LexemeAt(pScanner));
  // TODO aqui nao pode ser o current
  const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;
  Tokens token = pBasicScanner->currentItem.token;

  // verificar se tem parametros
  int nArgsExpected = pMacro->FormalArguments.Size; // pMacro->bIsFunction;
  int nArgsFound = 0;

  // fazer uma lista com os parametros

  if (token == TK_LEFT_PARENTHESIS)
  {
    // Adiciona o nome da macro
    PPToken* ppTokenName = PPToken_Create(pMacro->Name, PPTokenType_Identifier);
    TokenArray_PushBack(ppTokenArray, ppTokenName);

    // Match do (
    PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
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

        PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));

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
          PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
          TokenArray_PushBack(ppTokenArray, ppToken);

          StrBuilder_Append(strBuilder, lexeme);
          BasicScanner_Match(pBasicScanner);

          token = pBasicScanner->currentItem.token;
          lexeme = pBasicScanner->currentItem.lexeme.c_str;

          break;
        }

        iInsideParentesis--;

        PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
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
        PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
        TokenArray_PushBack(ppTokenArray, ppToken);

        StrBuilder_Append(strBuilder, lexeme);
        BasicScanner_Match(pBasicScanner);
        token = pBasicScanner->currentItem.token;
        lexeme = pBasicScanner->currentItem.lexeme.c_str;
      }
      else
      {
        // StrBuilder_Append(strBuilderResult, Scanner_LexemeAt(pScanner));
        PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
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
      ASSERT(false);
      // JObj_PrintDebug(pMacro);
      // Scanner_PrintDebug(pScanner);
    }
  }

  // tODO se nao for macro tem que pegar todo
  // o match feito e devolver.
  // nome da macro e espacos..

  // return false;
}

Tokens FindPreToken(const char* lexeme)
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

void GetPPTokens(BasicScanner* pBasicScanner, TokenArray* pptokens,
  StrBuilder* strBuilder)
{
  Tokens token = pBasicScanner->currentItem.token;
  const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;

  // Corpo da macro
  while (token != TK_BREAKLINE && token != TK_EOF && token != TK_FILE_EOF)
  {
    StrBuilder_Append(strBuilder, lexeme);

    if (token != TK_BACKSLASHBREAKLINE)
    {
      // TODO comentarios entram como espaco
      PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
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

static void Scanner_MatchAllPreprocessorSpaces(BasicScanner* pBasicScanner,
  StrBuilder* strBuilder)
{
  Tokens token = pBasicScanner->currentItem.token;
  while (token == TK_SPACES || token == TK_BACKSLASHBREAKLINE ||
    token == TK_COMMENT)
  {
    StrBuilder_Append(strBuilder, pBasicScanner->currentItem.lexeme.c_str);

    BasicScanner_Match(pBasicScanner);
    token = pBasicScanner->currentItem.token;
  }
}

void ParsePreDefinev2(Scanner* pScanner, StrBuilder* strBuilder)
{
  BasicScanner* pBasicScanner = Scanner_Top(pScanner);

  // objetivo eh montar a macro e colocar no mapa
  Macro* pNewMacro = Macro_Create();

  Tokens token = pBasicScanner->currentItem.token;
  const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;

  String_Set(&pNewMacro->Name, lexeme);
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

      PPToken* ppToken = PPToken_Create(lexeme, TokenToPPToken(token));
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

int EvalPre(Scanner* pScanner, StrBuilder* sb)
{
  if (pScanner->bError)
  {
    return 0;
  }

  // pega todos os tokens ate o final da linha expande e
  // avalia
  // usado no #if #elif etc.
  BasicScanner* pBasicScanner = Scanner_Top(pScanner);

  TokenArray pptokens = TOKENARRAY_INIT;
  GetPPTokens(pBasicScanner, &pptokens, sb);
  StrBuilder strBuilder = STRBUILDER_INIT;
  ExpandMacroToText(&pptokens, &pScanner->Defines2, false, true, true, NULL,
    &strBuilder);

  int iRes = EvalExpression(strBuilder.c_str, pScanner);

  StrBuilder_Destroy(&strBuilder);
  TokenArray_Destroy(&pptokens);
  return iRes;
}

static void Scanner_PushToken(Scanner* pScanner, Tokens token,
  const char* lexeme, bool bActive)
{
  if (pScanner->bError)
  {
    return;
  }

  ScannerItem* pNew = ScannerItem_Create();
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
void Scanner_BuyIdentifierThatCanExpandAndCollapse(Scanner* pScanner)
{
  State state = StateTop(pScanner);
  BasicScanner* pBasicScanner = Scanner_Top(pScanner);
  ASSERT(pBasicScanner != NULL);

  Tokens token = pBasicScanner->currentItem.token;
  const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;
  ASSERT(token == TK_IDENTIFIER);

  if (!IsIncludeState(state))
  {
    ScannerItem* pNew = ScannerItem_Create();
    LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
    pNew->token = pBasicScanner->currentItem.token;
    pNew->bActive = false;
    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

    // Match do identificador
    BasicScanner_Match(pBasicScanner);
    return;
  }

  Macro* pMacro2 = Scanner_FindPreprocessorItem2(pScanner, lexeme);
  if (pMacro2 == NULL)
  {
    // nao eh macro
    ScannerItem* pNew = ScannerItem_Create();
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
    ScannerItem* pNew = ScannerItem_Create();
    LocalStrBuilder_Swap(&pNew->lexeme, &pBasicScanner->currentItem.lexeme);
    pNew->token = pBasicScanner->currentItem.token;
    pNew->bActive = true;
    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

    // Match do identificador
    BasicScanner_Match(pBasicScanner);
    return;
  }

  Macro* pFirstMacro = pMacro2;

  // Match do identificador do nome da macro funcao
  BasicScanner_Match(pBasicScanner);

  bool bExitLoop = false;

  do
  {
    if (!pMacro2->bIsFunction)
    {
      TokenArray ppTokenArray = TOKENARRAY_INIT;
      // o nome eh a propria expansao
      PPToken* ppTokenName =
        PPToken_Create(pMacro2->Name, TokenToPPToken(TK_IDENTIFIER));
      TokenArray_PushBack(&ppTokenArray, ppTokenName);

      StrBuilder strExpanded = STRBUILDER_INIT;

      ExpandMacroToText(&ppTokenArray, &pScanner->Defines2, false, false, false, NULL,
        &strExpanded);

      // se expandir para identificador e ele for uma macro do tipo funcao
      // pode ser tetris
      Macro* pMacro3 = NULL;

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
      while (token == TK_SPACES || token == TK_COMMENT)
      {
        // StrBuilder_Append(strBuilder, lexeme);

        /////////////
        ScannerItem* pNew = ScannerItem_Create();
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
        TokenArray ppTokenArray = TOKENARRAY_INIT;

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
        Macro* pMacro3 = NULL;
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
          ScannerItem* pNew = ScannerItem_Create();
          LocalStrBuilder_Append(&pNew->lexeme, pFirstMacro->Name);
          pNew->token = TK_MACRO_CALL;
          pNew->bActive = true;
          TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);
        }

        ScannerItem* pNew0 = ScannerItem_Create();
        LocalStrBuilder_Append(&pNew0->lexeme, pMacro2->Name);
        pNew0->token = TK_IDENTIFIER;
        pNew0->bActive = true;
        TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew0);

        if (pFirstMacro != pMacro2)
        {
          ScannerItem* pNew2 = ScannerItem_Create();
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
  } while (!bExitLoop);
}

void Scanner_BuyTokens(Scanner* pScanner)
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

  BasicScanner* pBasicScanner = Scanner_Top(pScanner);
  if (pBasicScanner == NULL)
  {
    // acabaram todos os montes de tokens (cartas do baralho)
    return;
  }

  Tokens token = pBasicScanner->currentItem.token;
  const char* lexeme = pBasicScanner->currentItem.lexeme.c_str;

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
    ScannerItem* pNew = ScannerItem_Create();
    pNew->token = TK_EOF;
    pNew->bActive = true;
    TScannerItemList_PushBack(&pScanner->AcumulatedTokens, pNew);

    return;
  }

  StrBuilder strBuilder = STRBUILDER_INIT;

  State state = StateTop(pScanner);
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
          String fileName;
          String_InitWith(&fileName, lexeme + 1);

          StrBuilder_Append(&strBuilder, lexeme);
          BasicScanner_Match(pBasicScanner);

          fileName[strlen(fileName) - 1] = 0;

          // tem que ser antes de colocar o outro na pilha
          IgnorePreProcessorv2(pBasicScanner, &strBuilder);

          Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
          Scanner_IncludeFile(pScanner, fileName, FileIncludeTypeQuoted, true);
          String_Destroy(&fileName);
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

          Scanner_PushToken(pScanner, TK_PRE_INCLUDE, strBuilder.c_str, true);
          Scanner_IncludeFile(pScanner, path.c_str, FileIncludeTypeIncludes,
            true);
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
          const char* fullPath = Scanner_Top(pScanner)->stream.NameOrFullPath;
          TFile* pFile = TFileMap_Find(&pScanner->FilesIncluded, fullPath);

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
        else if (BasicScanner_IsLexeme(Scanner_Top(pScanner), "dir"))
        {
          StrBuilder_Append(&strBuilder, lexeme);

          BasicScanner_Match(pBasicScanner);
          Scanner_MatchAllPreprocessorSpaces(pBasicScanner, &strBuilder);
          lexeme = pBasicScanner->currentItem.lexeme.c_str;
          String fileName;
          String_InitWith(&fileName, lexeme + 1);
          Scanner_Match(pScanner);
          fileName[strlen(fileName) - 1] = 0;
          StrArray_Push(&pScanner->IncludeDir, fileName);
          String_Destroy(&fileName);
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
      case NONE:
      case I1:
      case E1:
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
          StatePush(pScanner, I1);
        }
        else
        {
          StatePush(pScanner, I0);
        }
      }
      break;

      case I0:
        StatePush(pScanner, I0);
        break;

      case E0:
        StatePush(pScanner, E0);
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
      case NONE:
      case I1:
        pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = E0;
        break;

      case I0:
      {
        int iRes = EvalPre(pScanner, &strBuilder);

        if (pScanner->StackIfDef.Size >= 2)
        {
          if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
            I1 ||
            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
            E1))
          {
            if (iRes)
            {
              pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = I1;
            }
          }
        }
        else
        {
          if (iRes)
          {
            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = I1;
          }
        }
      }
      break;

      case E0:
        break;

      case E1:
        ASSERT(0);
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
      case NONE:
        ASSERT(0);
        break;

      case I1:
        pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = E0;
        break;

      case I0:
        if (pScanner->StackIfDef.Size >= 2)
        {
          if ((pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
            I1 ||
            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 2] ==
            E1))
          {
            pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = E1;
          }
        }
        else
        {
          pScanner->StackIfDef.pItems[pScanner->StackIfDef.Size - 1] = E1;
        }

        break;

      case E0:
        break;

      case E1:
        ASSERT(false);
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
    ScannerItem* pNew = ScannerItem_Create();
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

void PrintPreprocessedToFileCore(FILE* fp, Scanner* scanner)
{
  while (Scanner_TokenAt(scanner, 0) != TK_EOF)
  {
    Tokens token = Scanner_TokenAt(scanner, 0);
    const char* lexeme = Scanner_LexemeAt(scanner, 0);
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

void PrintPreprocessedToFile(const char* fileIn, const char* configFileName)
{
  String fullFileNamePath = STRING_INIT;
  GetFullPath(fileIn, &fullFileNamePath);

  Scanner scanner;
  Scanner_Init(&scanner);

  Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath,
    false);

  if (configFileName != NULL)
  {
    String configFullPath = STRING_INIT;
    GetFullPath(configFileName, &configFullPath);

    Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath,
      true);
    Scanner_Match(&scanner);

    String_Destroy(&configFullPath);
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

  FILE* fp = fopen(fileNameOut, "w");
  PrintPreprocessedToFileCore(fp, &scanner);

  fclose(fp);
  Scanner_Destroy(&scanner);
  String_Destroy(&fullFileNamePath);
}

void PrintPreprocessedToConsole(const char* fileIn,
  const char* configFileName)
{
  String fullFileNamePath = STRING_INIT;
  GetFullPath(fileIn, &fullFileNamePath);

  Scanner scanner;
  Scanner_Init(&scanner);

  Scanner_IncludeFile(&scanner, fullFileNamePath, FileIncludeTypeFullPath,
    false);

  if (configFileName != NULL)
  {
    String configFullPath = STRING_INIT;
    GetFullPath(configFileName, &configFullPath);

    Scanner_IncludeFile(&scanner, configFullPath, FileIncludeTypeFullPath,
      true);
    Scanner_Match(&scanner);

    String_Destroy(&configFullPath);
  }

  PrintPreprocessedToFileCore(stdout, &scanner);

  Scanner_Destroy(&scanner);
  String_Destroy(&fullFileNamePath);
}

int Scanner_GetNumberOfScannerItems(Scanner* pScanner)
{
  int nCount = 1; // contando com o "normal"
  ForEachListItem(ScannerItem, pItem, &pScanner->AcumulatedTokens)
  {
    nCount++;
  }
  return nCount;
}

ScannerItem* Scanner_ScannerItemAt(Scanner* pScanner, int index)
{

  // item0 item1 ..itemN
  //^
  // posicao atual

  ScannerItem* pScannerItem = NULL;

  if (!pScanner->bError)
  {
    // conta o numero de itens empilhados
    int nCount = 0;
    ForEachListItem(ScannerItem, pItem, &pScanner->AcumulatedTokens)
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
      ForEachListItem(ScannerItem, pItem, &pScanner->AcumulatedTokens)
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

void Scanner_PrintItems(Scanner* pScanner)
{
  printf("-----\n");
  int n = Scanner_GetNumberOfScannerItems(pScanner);
  for (int i = 0; i < n; i++)
  {
    ScannerItem* pItem = Scanner_ScannerItemAt(pScanner, i);
    printf("%d : %s %s\n", i, pItem->lexeme.c_str, TokenToString(pItem->token));
  }
  printf("-----\n");
}

int Scanner_FileIndexAt(Scanner* pScanner, int index)
{
  ScannerItem* pScannerItem = Scanner_ScannerItemAt(pScanner, index);
  if (pScannerItem)
  {
    return pScannerItem->FileIndex;
  }
  return 0;
}

int Scanner_LineAt(Scanner* pScanner, int index)
{
  ScannerItem* pScannerItem = Scanner_ScannerItemAt(pScanner, index);
  if (pScannerItem)
  {
    return pScannerItem->Line;
  }
  return 0;
}

bool Scanner_IsActiveAt(Scanner* pScanner, int index)
{
  ScannerItem* pScannerItem = Scanner_ScannerItemAt(pScanner, index);
  if (pScannerItem)
  {
    return pScannerItem->bActive;
  }
  return false;
}

Tokens Scanner_TokenAt(Scanner* pScanner, int index)
{
  ScannerItem* pScannerItem = Scanner_ScannerItemAt(pScanner, index);
  if (pScannerItem)
  {
    return pScannerItem->token;
  }

  return TK_EOF;
}

const char* Scanner_LexemeAt(Scanner* pScanner, int index)
{
  ScannerItem* pScannerItem = Scanner_ScannerItemAt(pScanner, index);
  if (pScannerItem)
  {
    return pScannerItem->lexeme.c_str;
  }
  return "";
}



void Scanner_MatchDontExpand(Scanner* pScanner)
{
  if (!pScanner->bError)
  {
    if (pScanner->AcumulatedTokens.pHead != NULL)
    {
      TScannerItemList_PopFront(&pScanner->AcumulatedTokens);
    }
    else
    {
      BasicScanner* pTopScanner = Scanner_Top(pScanner);
      if (pTopScanner == NULL)
      {
        return;
      }

      BasicScanner_Match(pTopScanner);

      Tokens token = pTopScanner->currentItem.token;

      while (token == TK_EOF && pScanner->stack->pPrevious != NULL)
      {
        ASSERT(pScanner->AcumulatedTokens.pHead == NULL);
        BasicScannerStack_PopIfNotLast(&pScanner->stack);
        pTopScanner = Scanner_Top(pScanner);
        token = pTopScanner->currentItem.token;
      }
    }
  }
}
void Scanner_Match(Scanner* pScanner)
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

bool Scanner_MatchToken(Scanner* pScanner, Tokens token, bool bActive)
{
  if (pScanner->bError)
  {
    return false;
  }

  bool b = Scanner_TokenAt(pScanner, 0) == token;
  Scanner_Match(pScanner);
  return b;
}


void TScannerItemList_Destroy(TScannerItemList* p) _default
{
  ScannerItem_Delete(p->pHead);
}

void TScannerItemList_Clear(TScannerItemList* p)
{
  TScannerItemList_Destroy(p);
  TScannerItemList_Init(p);
}

void TScannerItemList_Init(TScannerItemList* p) _default
{
  p->pHead = NULL;
  p->pTail = NULL;
}


void TScannerItemList_Swap(TScannerItemList* a, TScannerItemList* b)
{
  TScannerItemList t = *a;
  *a = *b;
  *b = t;
}

void TScannerItemList_PopFront(TScannerItemList* pList)
{
  ScannerItem *p = pList->pHead;
  pList->pHead = pList->pHead->pNext;
  ScannerItem_Delete(p);
}

void TScannerItemList_PushBack(TScannerItemList* pList, ScannerItem* pItem)
{
  if ((pList)->pHead == NULL) {
    (pList)->pHead = (pItem);
    (pList)->pTail = (pItem);
  }
  else {
    (pList)->pTail->pNext = (pItem);
    (pList)->pTail = (pItem);
  }

}




#include <stddef.h>

#ifdef USE_UTF8
#include  "Utf8.h"
#endif



void StrBuilder_Init(StrBuilder* p) _default
{
  p->c_str = NULL;
  p->size = 0;
  p->capacity = 0;
}

void StrBuilder_Swap(StrBuilder* str1,
  StrBuilder* str2)
{
  StrBuilder temp_Moved = *str1;
  *str1 = *str2;
  *str2 = temp_Moved;
}

void StrBuilder_Destroy(StrBuilder* p)
{
  if (p)
  {
    free(p->c_str);
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
  }
}

Result StrBuilder_Reserve(StrBuilder* p, int nelements)
{
  Result r = RESULT_OK;

  if (nelements > p->capacity)
  {
    char* pnew = (char*)realloc(p->c_str,
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
      r = RESULT_OUT_OF_MEM;
    }
  }

  return r;
}

static Result StrBuilder_Grow(StrBuilder* p, int nelements)
{
  Result r = RESULT_OK;

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

Result StrBuilder_SetN(StrBuilder* p,
  const char* source,
  int nelements)
{
  Result r = StrBuilder_Grow(p, nelements);

  if (r == 0)
  {
    strncpy(p->c_str, /*p->capacity + 1,*/ source, nelements);
    p->c_str[nelements] = '\0';
    p->size = nelements;
  }

  return r;
}

Result StrBuilder_Set(StrBuilder* p,
  const char* source)
{
  Result r = RESULT_OK;
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

Result StrBuilder_AppendN(StrBuilder* p,
  const char* source,
  int nelements)
{
  if (IsEmptyStr(source))
  {
    return RESULT_OK;
  }

  Result r = StrBuilder_Grow(p, p->size + nelements);

  if (r == RESULT_OK)
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

Result StrBuilder_AppendIdent(StrBuilder* p,
  int nspaces,
  const char* source)
{
  for (int i = 0; i < nspaces; i++)
  {
    StrBuilder_Append(p, " ");
  }
  return StrBuilder_Append(p, source);
}

Result StrBuilder_Append(StrBuilder* p,
  const char* source)
{
  if (IsEmptyStr(source))
  {
    return RESULT_OK;
  }

  return StrBuilder_AppendN(p, source, strlen(source));
}

void StrBuilder_Clear(StrBuilder* p)
{
  if (p->c_str != NULL)
  {
    p->c_str[0] = '\0';
    p->size = 0;
  }
}

char* StrBuilder_Release(StrBuilder* p)
{
  char* pResult = p->c_str;

  if (pResult != NULL)
  {
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
  }

  return pResult;
}


void StrBuilder_Attach(StrBuilder* pStrBuilder,
  char*  psz,
  int nBytes)
{
  if (psz != NULL)
  {
    ASSERT(nBytes > 0);
    StrBuilder_Destroy(pStrBuilder);
    pStrBuilder->c_str = psz;
    pStrBuilder->capacity = nBytes - 1;
    pStrBuilder->size = 0;
    pStrBuilder->c_str[0] = '\0';
  }
}

Result StrBuilder_AppendWChar(StrBuilder* p, wchar_t wch)
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


Result StrBuilder_AppendChar(StrBuilder* p, char ch)
{
  return StrBuilder_AppendN(p, &ch, 1);
}

Result StrBuilder_AppendW(StrBuilder* p, const wchar_t* psz)
{
  Result result = RESULT_FAIL;

  while (*psz)
  {
    result = StrBuilder_AppendWChar(p, *psz);

    if (result != RESULT_OK)
    {
      break;
    }

    psz++;
  }

  return result;
}


void StrBuilder_Trim(StrBuilder* p)
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



Result StrBuilder_AppendUpper(StrBuilder *p, const char*  s)
{
  if (s != NULL)
  {
    while (*s)
    {
      StrBuilder_AppendChar(p, toupper(*s));
      s++;
    }
  }

  return RESULT_OK;
}


void StrBuilder_AppendFmtV(StrBuilder * p, const char* fmt, va_list va)
{
  char buffer[500];
  vsnprintf(buffer, 500, fmt, va);
  StrBuilder_Append(p, buffer);
}

void StrBuilder_AppendFmt(StrBuilder * p, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char buffer[500];
  vsnprintf(buffer, 500, fmt, args);
  StrBuilder_Append(p, buffer);
  va_end(args);

}

void StrBuilder_AppendFmtIdent(StrBuilder * p, int nspaces, const char* fmt, ...)
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
  const char* fmt,
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





Result LoadFile(const char* filename, const char** out, int* szOut)
{
  Result result = RESULT_FAIL;
  int lSize = 0;
  FILE*  fp = (FILE*)fopen(filename, "rb");

  if (fp)
  {
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);
    char*  buffer = (char*)malloc(lSize + 1);

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
        result = RESULT_OK;
        *szOut = lSize;
      }

      free(buffer);
    }

    fclose(fp);
  }

  return result;
}


Result SStream_InitFile(SStream* pStream,
  const char* fullPath)
{
  ASSERT(IsFullPath(fullPath));
  String_InitWith(&pStream->NameOrFullPath, fullPath);
  String_InitWith(&pStream->FullDir2, NULL);
  pStream->currentLine = 1;
  pStream->currentCol = 1;
  pStream->position = 0;
  Result result = LoadFile(fullPath, (const char**)&pStream->text,
    &pStream->text_length);

  if (result == RESULT_OK)
  {
    //O objetivo aqui eh pegar o diretorio
    GetFullDir(fullPath, &pStream->FullDir2);

    if (pStream->text != NULL &&
      pStream->text[0] != '\0')
    {
      //unicode?
      pStream->currentChar = pStream->text[0];
    }

    else
    {
      pStream->currentChar = '\0';
    }
  }

  return result;
}

Result SStream_Init(SStream* pStream, const char* name, const char*  text)
{
  pStream->currentLine = 1;
  pStream->currentCol = 1;
  pStream->position = 0;
  String_InitWith(&pStream->text, text);
  String_InitWith(&pStream->NameOrFullPath, name);
  String_InitWith(&pStream->FullDir2, "");

  if (text != NULL)
  {
    pStream->text_length = strlen(text);
  }

  else
  {
    pStream->text_length = 0;
  }

  if (pStream->text != NULL &&
    pStream->text[0] != '\0')
  {
    //unicode?
    pStream->currentChar = pStream->text[0];
  }

  else
  {
    pStream->currentChar = '\0';
  }

  return RESULT_OK;
}


void SStream_Destroy(SStream* pStream) _default
{
  String_Destroy(&pStream->NameOrFullPath);
  String_Destroy(&pStream->FullDir2);
  String_Destroy(&pStream->text);
}


wchar_t SStream_LookAhead(SStream* pStream)
{
  if (pStream->position + 1 >= pStream->text_length)
  {
    return '\0';
  }

  return pStream->text[pStream->position + 1];
}

bool SStream_MatchChar(SStream* pStream, wchar_t ch)
{
  bool b = pStream->currentChar == ch;
  SStream_Match(pStream);
  return b;
}

void SStream_Match(SStream* pStream)
{
  if (pStream->position >= pStream->text_length)
  {
    pStream->currentChar = L'\0';
    return;
  }

  pStream->currentCol++;
  pStream->position++;

  if (pStream->position == pStream->text_length)
  {
    pStream->currentChar = '\0';
  }

  else
  {
    pStream->currentChar = pStream->text[pStream->position];
  }

  if (pStream->currentChar == '\n')
  {
    pStream->currentLine++;
    pStream->currentCol = 0;
  }
}



void String_Init(String* s)
{
  *s = 0;
}

void String_Reset(String* pString)
{
  String_Destroy(pString);
  String_InitWith(pString, NULL);
}

void String_Destroy(String*  pString)
{
  if (pString != NULL)
  {
    free(*pString);
    *pString = NULL;
  }
}

void String_Attach(String* pString, char* psz)
{
  free(*pString);
  *pString = psz;
}

void String_Swap(String* pA, String* pB)
{
  String temp_Moved = *pA;
  *pA = *pB;
  *pB = temp_Moved;
}

Result String_Set(String *pS1, const char* psz1)
{
  Result result;
  String s1_Moved;
  result = String_InitWith(&s1_Moved, psz1);

  if (result == RESULT_OK)
  {
    String_Swap(&s1_Moved, pS1);
    String_Destroy(&s1_Moved);
  }

  return result;
}

Result String_InitWith(String* pString, const char*  sourceOpt)
{
  if (sourceOpt != NULL)
  {
    int len = strlen(sourceOpt) + 1;
    void *   snew = malloc(sizeof(char) * len);

    if (snew == NULL)
    {
      return RESULT_OUT_OF_MEM;
    }

    memcpy(snew, sourceOpt, len);
    *pString = (char*)snew;
  }

  else
  {
    *pString = NULL;
  }

  return RESULT_OK;
}


int IsEmptyStr(const char*  psz)
{
  return psz == NULL || psz[0] == '\0';
}
//#include "Map.h"


//#include "stdafx.h"

static void SymbolMap_KeyValue_Delete(SymbolMapItem* p)
{
  if (p)
  {
    String_Destroy(&p->Key);
    free(p);
  }
}

static SymbolMapItem* SymbolMap_GetAssocAt(
  SymbolMap* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue);


static unsigned int SymbolMap_String2_HashKey(const char*  Key)
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


void SymbolMap_RemoveAll(SymbolMap* pMap)
{
  if (pMap->pHashTable != NULL)
  {
    for (int nHash = 0;
      nHash < pMap->nHashTableSize;
      nHash++)
    {
      SymbolMapItem* pKeyValue =
        pMap->pHashTable[nHash];

      while (pKeyValue != NULL)
      {
        SymbolMapItem* pKeyValueCurrent = pKeyValue;
        pKeyValue = pKeyValue->pNext;
        SymbolMap_KeyValue_Delete(pKeyValueCurrent);
      }
    }

    free(pMap->pHashTable);
    pMap->pHashTable = NULL;
    pMap->nCount = 0;
  }
}

void SymbolMap_Destroy(SymbolMap* pMap)
{
  SymbolMap_RemoveAll(pMap);
}

SymbolMapItem* SymbolMap_FindBucket(SymbolMap* pMap, const char*  Key)
{
  if (pMap->pHashTable == NULL)
  {
    return NULL;
  }

  unsigned int HashValue = SymbolMap_String2_HashKey(Key);
  unsigned int nHashBucket = HashValue % pMap->nHashTableSize;


  SymbolMapItem* pKeyValue =
    pMap->pHashTable[nHashBucket];

  return pKeyValue;
}

static SymbolMapItem* SymbolMap_GetAssocAt(
  SymbolMap* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue)
{
  if (pMap->pHashTable == NULL)
  {
    *HashValue = 0;
    *nHashBucket = 0;
    return NULL;
  }

  *HashValue = SymbolMap_String2_HashKey(Key);
  *nHashBucket = *HashValue % pMap->nHashTableSize;

  SymbolMapItem* pResult = NULL;

  SymbolMapItem* pKeyValue =
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

TTypePointer* SymbolMap_Find(SymbolMap* pMap,
  const char*  Key)
{
  TTypePointer* pTypePointer = NULL;
  unsigned int nHashBucket, HashValue;
  SymbolMapItem* pKeyValue = SymbolMap_GetAssocAt(pMap,
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

bool SymbolMap_LookupKey(SymbolMap* pMap,
  const char*  Key,
  const char** rKey)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  SymbolMapItem* pKeyValue = SymbolMap_GetAssocAt(pMap,
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

bool SymbolMap_RemoveKey(SymbolMap* pMap,
  const char*  Key,
  TTypePointer** ppValue)
{
  *ppValue = 0;
  bool bResult = false;

  if (pMap->pHashTable != NULL)
  {
    unsigned int HashValue =
      SymbolMap_String2_HashKey(Key);

    SymbolMapItem** ppKeyValuePrev =
      &pMap->pHashTable[HashValue % pMap->nHashTableSize];

    SymbolMapItem* pKeyValue = *ppKeyValuePrev;

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

int SymbolMap_SetAt(SymbolMap* pMap,
  const char* Key,
  TTypePointer* newValue)
{
  int result = 0;


  if (pMap->pHashTable == NULL)
  {
    if (pMap->nHashTableSize < 1)
    {
      pMap->nHashTableSize = 1000;
    }

    SymbolMapItem** pHashTable =
      (SymbolMapItem**)malloc(sizeof(SymbolMapItem*) * pMap->nHashTableSize);

    if (pHashTable != NULL)
    {
      memset(pHashTable, 0, sizeof(SymbolMapItem*) * pMap->nHashTableSize);
      pMap->pHashTable = pHashTable;
    }
  }

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
      SymbolMap_GetAssocAt(pMap,
        Key,
        &nHashBucket,
        &HashValue);

    //if (pKeyValue == NULL)
    {
      pKeyValue = (SymbolMapItem*)malloc(sizeof(SymbolMapItem) * 1);
      pKeyValue->HashValue = HashValue;
      pKeyValue->pValue = newValue;
      String_InitWith(&pKeyValue->Key, Key);
      pKeyValue->pNext = pMap->pHashTable[nHashBucket];
      pMap->pHashTable[nHashBucket] = pKeyValue;
      pMap->nCount++;
      result = 0;
    }

    //else
    //{
    //    result = 1;
    //    pKeyValue->pValue = newValue;
    //    String_Set(&pKeyValue->Key, Key);
    //}
  }

  return result;
}

void SymbolMap_Init(SymbolMap * p)
{
  SymbolMap temp = SYMBOLMAP_INIT;
  *p = temp;
}

void SymbolMap_Swap(SymbolMap * pA, SymbolMap * pB)
{
  SymbolMap temp = *pA;
  *pA = *pB;
  *pB = temp;
}

SymbolMap* SymbolMap_Create()
{
  SymbolMap* p = (SymbolMap*)malloc(sizeof(SymbolMap));

  if (p != 0)
  {
    SymbolMap t = SYMBOLMAP_INIT;
    *p = t;
  }

  return p;
}

void SymbolMap_Delete(SymbolMap * p)
{
  if (p != 0)
  {
    SymbolMap_Destroy(p);
    free(p);
  }
}

const char* PrintType(EType type)
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

static void SymbolMap_PrintCore(SymbolMap* pMap, int* n)
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
      SymbolMapItem* pSymbolMapItem = pMap->pHashTable[i];
      while (pSymbolMapItem != NULL)
      {
        printf("%s = %s\n", pSymbolMapItem->Key, PrintType(pSymbolMapItem->pValue->Type));
        pSymbolMapItem = pSymbolMapItem->pNext;
      }
    }
  }
}


void SymbolMap_Print(SymbolMap* pMap)
{
  int n = 0;
  SymbolMap_PrintCore(pMap, &n);
}



bool SymbolMap_IsTypeName(SymbolMap* pMap, const char* identifierName)
{
  bool bIsTypeName = false;

  while (pMap)
  {
    SymbolMapItem* pBucket =
      SymbolMap_FindBucket(pMap, identifierName);

    while (pBucket)
    {
      if (pBucket->pValue->Type == TDeclaration_ID &&
        strcmp(pBucket->Key, identifierName) == 0)
      {
        TDeclaration* pDeclaration =
          (TDeclaration*)pBucket->pValue;

        for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
        {
          TDeclarationSpecifier* pItem = pDeclaration->Specifiers.pData[i];

          if (pItem->Type == TStorageSpecifier_ID)
          {
            TStorageSpecifier* pStorageSpecifier =
              (TStorageSpecifier*)pItem;
            if (pStorageSpecifier->Token == TK_TYPEDEF)
            {
              bIsTypeName = 1;
              break;
            }
          }
        }
      }
      if (bIsTypeName)
        break;
      pBucket = pBucket->pNext;
    }

    if (bIsTypeName)
      break;

    pMap = pMap->pPrevious;
  }

  return bIsTypeName;
}


TDeclaration* SymbolMap_FindFunction(SymbolMap* pMap, const char* funcName)
{
  TDeclaration* pDeclaration = NULL;

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
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
            (TDeclaration*)pKeyValue->pValue;

          break;
        }
      }
      pKeyValue = pKeyValue->pNext;
    }
  }

  return pDeclaration;
}

TDeclaration* SymbolMap_FindObjFunction(SymbolMap* pMap,
  const char* objName,
  const char* funcName)
{
  if (objName == NULL || funcName == NULL)
  {
    return NULL;
  }

  char buffer[500] = { 0 };
  strcat(buffer, objName);
  strcat(buffer, "_");
  strcat(buffer, funcName);
  TDeclaration* p = SymbolMap_FindFunction(pMap, buffer);
  return p;
}

TStructUnionSpecifier* SymbolMap_FindStructUnion(SymbolMap* pMap, const char* structTagName)
{
  TStructUnionSpecifier* pStructUnionSpecifier = NULL;

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
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
            (TStructUnionSpecifier*)pKeyValue->pValue;
          if (pStructUnionSpecifier->StructDeclarationList.Size > 0 ||
            pStructUnionSpecifier->Token2 == TK__UNION)
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


TEnumSpecifier* SymbolMap_FindEnum(SymbolMap* pMap, const char* enumTagName)
{
  TEnumSpecifier* pEnumSpecifier = NULL;

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
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
            (TEnumSpecifier*)pKeyValue->pValue;
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


TDeclaration* SymbolMap_FindTypedefDeclarationTarget(SymbolMap* pMap,
  const char* typedefName)
{
  TDeclaration* pDeclarationResult = NULL;


  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
      SymbolMap_GetAssocAt(pMap,
        typedefName,
        &nHashBucket,
        &HashValue);

    while (pKeyValue != NULL)
    {
      if (pKeyValue->pValue->Type == TDeclaration_ID &&
        strcmp(pKeyValue->Key, typedefName) == 0)
      {
        TDeclaration *pDeclaration =
          (TDeclaration *)pKeyValue->pValue;

        //typedef X Y;
        bool bIsTypedef = false;
        const char* indirectTypedef = NULL;
        for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
        {
          TDeclarationSpecifier* pItem = pDeclaration->Specifiers.pData[i];


          switch (pItem->Type)
          {
          case TStorageSpecifier_ID:
          {
            TStorageSpecifier* pStorageSpecifier =
              (TStorageSpecifier*)pItem;
            if (pStorageSpecifier->Token == TK_TYPEDEF)
            {
              bIsTypedef = true;
            }
          }
          break;
          case TSingleTypeSpecifier_ID:
          {
            TSingleTypeSpecifier* pSingleTypeSpecifier =
              (TSingleTypeSpecifier*)pItem;

            if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
            {
              indirectTypedef = pSingleTypeSpecifier->TypedefName;
            }
          }
          break;
          default:
            ASSERT(false);
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
TDeclarationSpecifiers* SymbolMap_FindTypedefTarget(SymbolMap* pMap,
  const char* typedefName,
  TDeclarator* declarator)
{
  //TDeclaration* pDeclarationResult = NULL;
  TDeclarationSpecifiers* pSpecifiersResult = NULL;



  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
      SymbolMap_GetAssocAt(pMap,
        typedefName,
        &nHashBucket,
        &HashValue);

    while (pKeyValue != NULL)
    {
      if (pKeyValue->pValue->Type == TDeclaration_ID &&
        strcmp(pKeyValue->Key, typedefName) == 0)
      {
        TDeclaration *pDeclaration =
          (TDeclaration *)pKeyValue->pValue;

        //typedef X Y;
        bool bIsTypedef = false;
        const char* indirectTypedef = NULL;
        for (int i = 0; i <pDeclaration->Specifiers.Size; i++)
        {
          TDeclarationSpecifier* pItem = pDeclaration->Specifiers.pData[i];

          switch (pItem->Type)
          {
          case TStorageSpecifier_ID:
          {
            TStorageSpecifier* pStorageSpecifier =
              (TStorageSpecifier*)pItem;
            if (pStorageSpecifier->Token == TK_TYPEDEF)
            {
              bIsTypedef = true;
            }
          }
          break;
          case TSingleTypeSpecifier_ID:
          {
            TSingleTypeSpecifier* pSingleTypeSpecifier =
              (TSingleTypeSpecifier*)pItem;

            if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
            {
              indirectTypedef = pSingleTypeSpecifier->TypedefName;
            }
          }
          break;
          default:
            ASSERT(false);
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
            TDeclarator* pDeclarator =
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
              ASSERT(false);
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
TDeclarationSpecifiers* SymbolMap_FindTypedefFirstTarget(SymbolMap* pMap,
  const char* typedefName,
  TDeclarator* declarator)
{
  //TDeclaration* pDeclarationResult = NULL;
  TDeclarationSpecifiers* pSpecifiersResult = NULL;



  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue =
      SymbolMap_GetAssocAt(pMap,
        typedefName,
        &nHashBucket,
        &HashValue);

    while (pKeyValue != NULL)
    {
      if (pKeyValue->pValue->Type == TDeclaration_ID &&
        strcmp(pKeyValue->Key, typedefName) == 0)
      {
        TDeclaration *pDeclaration =
          (TDeclaration *)pKeyValue->pValue;

        //typedef X Y;
        bool bIsTypedef = false;
        const char* indirectTypedef = NULL;

        for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
        {
          TDeclarationSpecifier* pItem = pDeclaration->Specifiers.pData[i];


          switch (pItem->Type)
          {
          case TStorageSpecifier_ID:
          {
            TStorageSpecifier* pStorageSpecifier =
              (TStorageSpecifier*)pItem;
            if (pStorageSpecifier->Token == TK_TYPEDEF)
            {
              bIsTypedef = true;
            }
          }
          break;
          case TSingleTypeSpecifier_ID:
          {
            TSingleTypeSpecifier* pSingleTypeSpecifier =
              (TSingleTypeSpecifier*)pItem;

            if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
            {
              indirectTypedef = pSingleTypeSpecifier->TypedefName;
            }
          }
          break;
          default:
            ASSERT(false);
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
            TDeclarator* pDeclarator =
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
              ASSERT(false);
            }
          }
          else
          {
            //'e um typedef direto - retorna a declaracao que ele aparece
            TDeclarator* pDeclarator =
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
TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(SymbolMap* pMap,
  const char* typedefName)
{
  /*Sample:
  struct X;
  typedef struct X X;
  struct X { int i;  };
  typedef X Y;
  */

  TTypeSpecifier* pSpecifierTarget = NULL;

  TDeclaration* pDeclaration =
    SymbolMap_FindTypedefDeclarationTarget(pMap, typedefName);
  if (pDeclaration)
  {
    for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
    {
      TDeclarationSpecifier* pItem = pDeclaration->Specifiers.pData[i];


      switch (pItem->Type)
      {
      case TSingleTypeSpecifier_ID:
        pSpecifierTarget = pItem;
        break;

      case TStructUnionSpecifier_ID:
      {
        TStructUnionSpecifier* pStructUnionSpecifier =
          (TStructUnionSpecifier*)pItem;
        if (pStructUnionSpecifier->StructDeclarationList.Size == 0)
        {
          if (pStructUnionSpecifier->Name != NULL)
          {
            pSpecifierTarget = (TTypeSpecifier*)SymbolMap_FindStructUnion(pMap, pStructUnionSpecifier->Name);
          }
          else
          {
            ASSERT(false);
          }
        }
        else
        {
          pSpecifierTarget = (TTypeSpecifier*)pStructUnionSpecifier;
        }
      }
      break;
      case TEnumSpecifier_ID:
      {
        TEnumSpecifier* pEnumSpecifier =
          (TEnumSpecifier*)pItem;
        if (pEnumSpecifier->EnumeratorList.pHead == NULL)
        {
          if (pEnumSpecifier->Name != NULL)
          {
            pEnumSpecifier = SymbolMap_FindEnum(pMap, pEnumSpecifier->Name);
          }
          else
          {
            ASSERT(false);
          }
        }
        else
        {
          pSpecifierTarget = (TTypeSpecifier*)pEnumSpecifier;
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
void TokenArray_Reserve(TokenArray* p, int nelements) _default
{
  if (nelements > p->Capacity)
  {
    PPToken** pnew = p->pItems;
    pnew = (PPToken**)realloc(pnew, nelements * sizeof(PPToken*));
    if (pnew)
    {
      p->pItems = pnew;
      p->Capacity = nelements;
    }
  }
}

int TokenArray_Grow(TokenArray* p, int nelements)
{
  return Array_Grow((Array*)p, nelements);
}

PPToken* TokenArray_PopFront(TokenArray* p)
{
  void *pItem = Array_PopFront((Array*)p);
  return (PPToken*)pItem;
}

void TokenArray_Pop(TokenArray* p)
{
  Array_Pop((Array*)p, PPToken_DeleteVoid);
}

PPToken* TokenArray_Top(TokenArray* p)
{
  return (PPToken*)Array_Top((Array*)p);
}

void TokenArray_PushBack(TokenArray* p, PPToken* pItem) _default
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

void TokenArray_Clear(TokenArray* p)
{
  Array_Clear((Array*)p, PPToken_DeleteVoid);
}


void TokenArray_Init(TokenArray* p) _default
{
  p->pItems = NULL;
  p->Size = 0;
  p->Capacity = 0;
}

TokenArray* TokenArray_Create() _default
{
  TokenArray *p = (TokenArray*)malloc(sizeof * p);
  if (p != NULL)
  {
    TokenArray_Init(p);
  }
  return p;
}

void TokenArray_Destroy(TokenArray* st) _default
{
  for (int i = 0; i < st->Size; i++)
  {
    PPToken_Delete(st->pItems[i]);
  }
  free((void*)st->pItems);
}

void TokenArray_Swap(TokenArray* p1, TokenArray* p2)
{
  TokenArray temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void TokenArray_Delete(TokenArray* st) _default
{
  if (st != NULL)
  {
    TokenArray_Destroy(st);
    free((void*)st);
  }
}




void TokenArray_AppendTokensCopy(TokenArray *pArray, PPToken** pToken, int len)
{
  for (int i = 0; i < len; i++)
  {
    TokenArray_PushBack(pArray, PPToken_Clone(pToken[i]));
  }
}
void TokenArray_AppendTokensMove(TokenArray *pArray, PPToken** pToken, int len)
{
  for (int i = 0; i < len; i++)
  {
    TokenArray_PushBack(pArray, pToken[i]);
    pToken[i] = NULL;
  }
}

void TokenArray_AppendCopy(TokenArray *pArrayTo, const TokenArray *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenArray_PushBack(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
  }
}

void TokenArray_AppendMove(TokenArray *pArrayTo, TokenArray *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenArray_PushBack(pArrayTo, pArrayFrom->pItems[i]);
    pArrayFrom->pItems[i] = NULL;
  }
}

PPToken* TokenArray_Find(const TokenArray *pArray, const char * lexeme)
{
  PPToken* pFound = NULL;

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

void TokenArray_ToStrBuilder(const TokenArray* tokens,
  StrBuilder* strBuidler)
{
  StrBuilder_Clear(strBuidler);
  for (int i = 0; i < tokens->Size; i++)
  {
    StrBuilder_Append(strBuidler, tokens->pItems[i]->Lexeme);
  }
}

void TokenArray_Print(const TokenArray* tokens)
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


void TokenArray_Erase(TokenArray *pArray, int begin, int end)
{
  for (int i = begin; i < end; i++)
  {
    PPToken_Delete(pArray->pItems[i]);
  }


  if (pArray->Size > 1)
  {
    memmove(pArray->pItems + begin,
      pArray->pItems + end,
      sizeof(void*) * (pArray->Size - end));
  }

  pArray->Size = pArray->Size - end;
}


int TokenArrayMap_SetAt(TokenArrayMap* pMap,
  const char* Key,
  TokenArray* newValue)
{
  void *pPrevious;
  int r = Map2_SetAt((Map2*)pMap, Key, newValue, &pPrevious);
  TokenArray_Delete((TokenArray*)pPrevious);
  return r;
}

bool TokenArrayMap_Lookup(const TokenArrayMap* pMap,
  const char*  Key,
  TokenArray** rValue)
{
  if (pMap == NULL)
  {
    return false;
  }

  return Map2_Lookup((Map2*)pMap,
    Key,
    (void**)rValue);
}

bool TokenArrayMap_RemoveKey(TokenArrayMap* pMap, const char*  Key)
{
  TokenArray *pItem;
  bool r = Map2_RemoveKey((Map2*)pMap, Key, (void**)&pItem);

  if (r)
  {
    TokenArray_Delete(pItem);
  }

  return r;
}

void TokenArrayMap_Init(TokenArrayMap* p)
{
  TokenArrayMap t = TOKENARRAY_INIT;
  *p = t;
}

void TokenArrayMap_Destroy(TokenArrayMap* p)
{
  Map2_Destroy((Map2*)p);
}



void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB)
{
  TokenArrayMap t = TOKENARRAYMAP_INIT;
  *pA = *pB;
  *pB = t;
}

void TokenSet_PushBack(TokenSet* p, PPToken* pItem) /*custom*/
{
  int r = 0;
  PPToken* pTk = TokenSet_Find(p, pItem->Lexeme);

  if (pTk == NULL)
  {
    r = Array_Push((Array*)p, pItem);

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


void TokenSetAppendCopy(TokenSet *pArrayTo, const TokenSet *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenSet_PushBack(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
  }
}


PPToken* TokenSet_Find(const TokenSet *pArray, const char * lexeme)
{
  PPToken* pFound = NULL;

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

void TokenSet_Clear(TokenSet* p)
{
  Array_Clear((Array*)p, PPToken_DeleteVoid);
}


void TokenSet_Destroy(TokenSet *pArray) _default
{
  for (int i = 0; i < pArray->Size; i++)
  {
    PPToken_Delete(pArray->pItems[i]);
  }
  free((void*)pArray->pItems);
}

void SetIntersection(const TokenSet *p1,
  const TokenSet *p2,
  TokenSet *pResult)
{
  if (p1->Size != 0 && p2->Size != 0)
  {
    PPToken* first1 = p1->pItems[0];
    PPToken* last1 = p1->pItems[p1->Size];

    PPToken* first2 = p2->pItems[0];
    PPToken* last2 = p2->pItems[p2->Size];

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


static int error_count = 0;
static int sucess_count = 0;

#define TEST(condition) \
if (condition)\
{\
  sucess_count++;\
}\
else\
{\
  printf("%s LINE %d FAILED!\n", __FUNCTION__, __LINE__); \
  error_count++;\
}

void Match(Scanner* pScanner,
  Tokens token,
  bool bExpectedActive,
  const char* expectedLexeme,
  const char* func,
  int line)
{
  Tokens tk = Scanner_TokenAt((pScanner), 0);
  const char* lexeme = Scanner_LexemeAt((pScanner), 0);
  bool bIsActive = Scanner_IsActiveAt((pScanner), 0);

  if (tk == token &&
    bIsActive == bExpectedActive &&
    (expectedLexeme == NULL || strcmp(expectedLexeme, lexeme) == 0))
  {
    Scanner_Match(pScanner);
    sucess_count++;
  }
  else
  {
    printf("%s LINE %d FAILED!\n", func, line);
    error_count++;
  }
}

#define MATCH(scanner, TK) \
  Match(scanner, TK, true, NULL, __FUNCTION__, __LINE__)

#define MATCH_INACTIVE(scanner, TK) \
  Match(scanner, TK, false, NULL, __FUNCTION__, __LINE__)

#define  MATCH_INACTIVE2(scanner, TK, lexeme)\
  Match(scanner, TK, false, lexeme, __FUNCTION__, __LINE__)

#define  MATCH2(scanner, TK, lexeme)\
  Match(scanner, TK, true, lexeme, __FUNCTION__, __LINE__)

void Scanner_Test1(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test1.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);

  TEST(Scanner_TokenAt(&scanner2, 0) == TK_MACRO_CALL);
  TEST(Scanner_TokenAt(&scanner2, 1) == TK_DECIMAL_INTEGER);
  TEST(Scanner_TokenAt(&scanner2, 2) == TK_MACRO_EOF);
  TEST(Scanner_TokenAt(&scanner2, 3) == TK_BREAKLINE);
  //TEST(Scanner_TokenAt(&scanner2, 4) == TK_FILE_EOF);
  TEST(Scanner_TokenAt(&scanner2, 5) == TK_EOF);
  TEST(Scanner_TokenAt(&scanner2, 6) == TK_EOF);

  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);

  Scanner_Destroy(&scanner2);
}

void Scanner_Test2(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test2.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);

  Scanner_Destroy(&scanner2);
}
void Scanner_Test3(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test3.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);

  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_STRING_LITERAL);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);



  Scanner_Destroy(&scanner2);


}

void Scanner_Test4(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test4.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);

  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_PLUS_SIGN);
  MATCH(&scanner2, TK_SPACES);

  MATCH2(&scanner2, TK_IDENTIFIER, "foo");
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);

  Scanner_Destroy(&scanner2);
}

void Scanner_Test5(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test5.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH2(&scanner2, TK_STRING_LITERAL, "\"x ## y\"");
  MATCH(&scanner2, TK_MACRO_EOF);

  Scanner_Destroy(&scanner2);
}

void Scanner_Test10(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test9.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);


  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_EOF);


  Scanner_Destroy(&scanner2);
}

void Scanner_Test11(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test12.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_PLUS_SIGN);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_EOF);

  Scanner_Destroy(&scanner2);
}




void Scanner_Test12(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test10.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);

  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_EOF);


  Scanner_Destroy(&scanner2);
}

void Scanner_Test13(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test11.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);

  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_EOF);


  Scanner_Destroy(&scanner2);
}

void Scanner_Test14(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test13.h", FileIncludeTypeQuoted, false);

  MATCH(&scanner2, TK_BOF);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_PRE_DEFINE);

  MATCH(&scanner2, TK_MACRO_CALL);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_MACRO_EOF);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_DECIMAL_INTEGER);
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_EOF);


  Scanner_Destroy(&scanner2);
}


void Scanner_Test6(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);
  MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN");
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_IF);
  MATCH2(&scanner2, TK_IDENTIFIER, "A");
  MATCH(&scanner2, TK_SPACES);
  MATCH2(&scanner2, TK_IDENTIFIER, "B");
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH_INACTIVE(&scanner2, TK_PRE_ELSE);

  //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
  MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B");
  MATCH_INACTIVE(&scanner2, TK_SPACES);
  MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D");
  MATCH_INACTIVE(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_ENDIF);
  //MATCH(&scanner2, TK_BREAKLINE) //#endif

  MATCH2(&scanner2, TK_IDENTIFIER, "END");
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  Scanner_Destroy(&scanner2);
  ///////////////////////////
}

void Scanner_Test7(void)
{
  //
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test7.h", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);
  //Test7.h
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_PRAGMA);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_VOID);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_SEMICOLON);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  //Test7.h
  Scanner_Destroy(&scanner2);
  ///////////////////////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test7.c", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);

  MATCH(&scanner2, TK_PRE_INCLUDE);

  //Test7.h
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_PRAGMA);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_VOID);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_SEMICOLON);
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_FILE_EOF);
  //Test7.h;

  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_VOID);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_LEFT_PARENTHESIS);
  MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
  MATCH(&scanner2, TK_SEMICOLON);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  Scanner_Destroy(&scanner2);

}


void Scanner_Test9(void)
{
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);
  MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN");
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_IF);
  MATCH2(&scanner2, TK_IDENTIFIER, "A");
  MATCH(&scanner2, TK_SPACES);
  MATCH2(&scanner2, TK_IDENTIFIER, "B");
  MATCH(&scanner2, TK_BREAKLINE);

  TEST(Scanner_IsActiveAt(&scanner2, 1) == 0);

  MATCH_INACTIVE(&scanner2, TK_PRE_ELSE);

  //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
  MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B");
  MATCH_INACTIVE(&scanner2, TK_SPACES);
  MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D");
  MATCH_INACTIVE(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_ENDIF);
  //MATCH(&scanner2, TK_BREAKLINE) //#endif

  MATCH2(&scanner2, TK_IDENTIFIER, "END");
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  Scanner_Destroy(&scanner2);
  ///////////////////////////
}


void Scanner_Test8(void)
{

  //
  Scanner scanner2;
  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test8.h", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);
  //Test8.h
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  //Test7.h
  Scanner_Destroy(&scanner2);
  ///////////////////////////

  Scanner_Init(&scanner2);
  Scanner_IncludeFile(&scanner2, ".\\Test\\Test8.c", FileIncludeTypeQuoted, false);
  MATCH(&scanner2, TK_BOF);

  MATCH(&scanner2, TK_PRE_INCLUDE);

  //Test8.h
  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_PRE_DEFINE);
  MATCH(&scanner2, TK_FILE_EOF);
  //Test8.h

  MATCH(&scanner2, TK_BREAKLINE);
  MATCH(&scanner2, TK_INT);
  MATCH(&scanner2, TK_SPACES);
  MATCH(&scanner2, TK_IDENTIFIER);
  MATCH(&scanner2, TK_SEMICOLON);
  MATCH(&scanner2, TK_BREAKLINE);
  //MATCH(&scanner2, TK_FILE_EOF)
  MATCH(&scanner2, TK_EOF);
  Scanner_Destroy(&scanner2);



}

void Stream_Test1(void)
{
  SStream stream;
  SStream_Init(&stream, "name", "123");
  TEST(SStream_MatchChar(&stream, L'1'));
  TEST(SStream_LookAhead(&stream) == '3');
  TEST(SStream_MatchChar(&stream, L'2'));
  TEST(SStream_MatchChar(&stream, L'3'));
  TEST(SStream_MatchChar(&stream, L'\0'));
  TEST(SStream_MatchChar(&stream, L'\0'));
  SStream_Destroy(&stream);
}

void BasicScanner_Test1(void)
{
  BasicScanner scanner;

  BasicScanner_Init(&scanner, "name", "#if 1", BasicScannerType_Token);
  scanner.m_Token = TK_PRE_IF;

  TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_PRE_IF));

  TEST(BasicScanner_MatchToken(&scanner, TK_EOF));

  BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test2(void)
{
  BasicScanner scanner;
  BasicScanner_Init(&scanner, "name", "123\r\n", BasicScannerType_File);

  TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_DECIMAL_INTEGER));
  TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
  TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
  BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test3(void)
{
  BasicScanner scanner;
  BasicScanner_Init(&scanner, "name", "#pragma once\r\n", BasicScannerType_File);

  TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_PREPROCESSOR));
  TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
  TEST(BasicScanner_MatchToken(&scanner, TK_SPACES));
  TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
  TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
  TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
  BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test4(void)
{
  BasicScanner scanner;

  BasicScanner_Init(&scanner, "name", "//comment", BasicScannerType_File);
  TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_LINE_COMMENT));
  TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
  BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test5(void)
{
  BasicScanner scanner;

  BasicScanner_Init(&scanner, "name", "/*comment*/", BasicScannerType_File);

  TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_COMMENT));
  TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
  TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
  BasicScanner_Destroy(&scanner);
}

#define ParserMatch(parser, token) \
 Parser_MatchToken((parser), (token), NULL); \
 TEST(!Parser_HasError((parser)));

void Parser_Test1(void)
{
  Parser parser;
  Parser_InitString(&parser, "a", "int a /*comment*/ = 1 + 2;");
  ParserMatch(&parser, TK_INT);

  TEST(Parser_LookAheadToken(&parser) == TK_EQUALS_SIGN);

  ParserMatch(&parser, TK_IDENTIFIER);
  ParserMatch(&parser, TK_EQUALS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_PLUS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_SEMICOLON);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}

void Parser_Test2(void)
{
  Parser parser;
  Parser_InitString(&parser, "a", "int a = 1 + 2;");
  ParserMatch(&parser, TK_INT);
  ParserMatch(&parser, TK_IDENTIFIER);

  ParserMatch(&parser, TK_EQUALS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_PLUS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_SEMICOLON);
  ParserMatch(&parser, TK_EOF);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}


void Parser_Test3(void)
{
  Parser parser;
  Parser_InitString(&parser, "a", "int a  =  1 + 2;");
  ParserMatch(&parser, TK_INT);
  ParserMatch(&parser, TK_IDENTIFIER);
  TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);
  TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);

  ParserMatch(&parser, TK_EQUALS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_PLUS_SIGN);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_SEMICOLON);
  ParserMatch(&parser, TK_EOF);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}


void Parser_Test4(void)
{
  const char* code =
    "a = \n"
    "#if 0\n"
    "1\n"
    "#else\n"
    "int\n"
    "#endif\n"
    "\n";

  Parser parser;
  Parser_InitString(&parser, "a", code);
  ParserMatch(&parser, TK_IDENTIFIER);
  TEST(Parser_LookAheadToken(&parser) == TK_INT);
  ParserMatch(&parser, TK_EQUALS_SIGN);
  ParserMatch(&parser, TK_INT);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}


void Parser_Test5(void)
{
  const char* code =
    "#define false 0\n"
    "int main()\n"
    "{\n"
    "return (false);\n"
    "}\n";

  Parser parser;
  Parser_InitString(&parser, "a", code);
  ParserMatch(&parser, TK_INT);

  ParserMatch(&parser, TK_IDENTIFIER);
  ParserMatch(&parser, TK_LEFT_PARENTHESIS);
  ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
  ParserMatch(&parser, TK_LEFT_CURLY_BRACKET);
  ParserMatch(&parser, TK_RETURN);


  TEST(Scanner_TokenAt(&parser.Scanner, 0) == TK_LEFT_PARENTHESIS);

  TEST(Scanner_TokenAt(&parser.Scanner, 1) == TK_MACRO_CALL);


  TEST(Scanner_TokenAt(&parser.Scanner, 2) == TK_DECIMAL_INTEGER);



  TEST(Scanner_TokenAt(&parser.Scanner, 3) == TK_MACRO_EOF);

  TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_LEFT_PARENTHESIS);


  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
  ParserMatch(&parser, TK_SEMICOLON);
  ParserMatch(&parser, TK_RIGHT_CURLY_BRACKET);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}

void Parser_Test6(void)
{
  const char* code =
    "#define false 0\n"
    "int main()\n"
    "{\n"
    "return (false);\n"
    "}\n";

  Parser parser;
  Parser_InitString(&parser, "a", code);
  ParserMatch(&parser, TK_INT);

  ParserMatch(&parser, TK_IDENTIFIER);
  ParserMatch(&parser, TK_LEFT_PARENTHESIS);
  ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
  ParserMatch(&parser, TK_LEFT_CURLY_BRACKET);
  ParserMatch(&parser, TK_RETURN);
  ParserMatch(&parser, TK_LEFT_PARENTHESIS);
  ParserMatch(&parser, TK_DECIMAL_INTEGER);
  ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
  ParserMatch(&parser, TK_SEMICOLON);
  ParserMatch(&parser, TK_RIGHT_CURLY_BRACKET);
  ParserMatch(&parser, TK_EOF);
  Parser_Destroy(&parser);
}


void AllTests(void)
{
  printf("RUNNING TESTS ...\n");
  Scanner_Test10();
  Scanner_Test14();
  Scanner_Test11();




  Scanner_Test12();
  Scanner_Test13();


  Stream_Test1();

  BasicScanner_Test1();
  BasicScanner_Test2();
  BasicScanner_Test3();
  BasicScanner_Test4();
  BasicScanner_Test5();





  Scanner_Test1();
  Scanner_Test2();
  Scanner_Test3();

  Scanner_Test4();
  Scanner_Test5();
  Scanner_Test6();
  Scanner_Test7();
  Scanner_Test8();
  Scanner_Test9();
  Scanner_Test10();
  Scanner_Test11();

  Parser_Test1();
  Parser_Test2();
  Parser_Test3();
  Parser_Test4();
  Parser_Test5();
  Parser_Test6();

  if (error_count == 0)
  {
    printf("ALL TESTS OK\n");
  }
  printf("\n");
}

