








#include <stdbool.h>


#include <stdlib.h>

struct StrArray
{
    const char* /*@auto*/ * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;

};

#define STRARRAY_INIT { NULL , 0 , 0 }






struct Stream
{
    //name to identify this stream
    char* /*@auto*/ NameOrFullPath;
    char* /*@auto*/ FullDir2;

    //stream content and length
    char* /*@auto*/ Text;
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








#include <string.h>


#include <stdarg.h>


#include <wchar.h>

struct StrBuilder
{
    char* c_str;
    int size;
    int capacity;
};

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

void StrBuilder_Init(struct StrBuilder* p);

bool StrBuilder_Reserve(struct StrBuilder* p, int nelements);

void StrBuilder_Attach(struct StrBuilder* wstr,
                       char* psz,
                       int nBytes);

void StrBuilder_Destroy(struct StrBuilder* wstr);
void StrBuilder_Swap(struct StrBuilder* str1, struct StrBuilder* str2);


void StrBuilder_Clear(struct StrBuilder* wstr);

bool StrBuilder_SetN(struct StrBuilder* p,
                     const char* source,
                     int nelements);

bool StrBuilder_Set(struct StrBuilder* p,
                    const char* source);

bool StrBuilder_AppendN(struct StrBuilder* p,
                        const char* source,
                        int nelements);

bool StrBuilder_Append(struct StrBuilder* p,
                       const char* source);

char* StrBuilder_Release(struct StrBuilder* p);


void StrBuilder_AppendFmt(struct StrBuilder* p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(struct StrBuilder* p, int nspaces, const char* fmt, ...);

bool StrBuilder_AppendWChar(struct StrBuilder* p, wchar_t wch);
bool StrBuilder_AppendW(struct StrBuilder* p, const wchar_t* psz);
bool StrBuilder_AppendChar(struct StrBuilder* p, char wch);
void StrBuilder_Trim(struct StrBuilder* p);
bool StrBuilder_AppendUpper(struct StrBuilder* p, const char* s);

bool StrBuilder_AppendIdent(struct StrBuilder* p,
                            int nspaces,
                            const char* source);


void StrBuilder_AppendFmtLn(struct StrBuilder* p,
                            int nspaces,
                            const char* fmt,
                            ...);
void StrBuilder_AppendFmtV(struct StrBuilder* p, const char* fmt, va_list va);






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

// #END_EXPORT







struct MapItem2
{
    struct MapItem2* pNext;
    unsigned int HashValue;
    char* /*@auto*/ Key;
    void* pValue;
};

struct Map2
{
    struct MapItem2** pHashTable;
    unsigned int nHashTableSize;
    int  nCount;
};


#define MAPSTRINGTOPTR_INIT { NULL, 100, 0 }

int Map2_SetAt(struct Map2* pMap,
               const char* Key,
               void* newValue,
               void** ppPreviousValue);


bool Map2_Lookup(struct Map2* pMap,
                 const char* Key,
                 void** rValue);

bool Map2_RemoveKey(struct Map2* pMap,
                    const char* Key,
                    void** ppValue);

void Map2_Init(struct Map2* p);
void Map2_Destroy(struct Map2* p, void (*DeleteFunc)(void*));

struct Map2* Map2_Create(void);


void Map2_Swap(struct Map2* pA, struct Map2* pB);
void Map2_Delete(struct Map2* p, void(*DeleteFunc)(void*));






struct TDeclarator;
struct TDeclarationSpecifiers;
struct TDeclaration;
struct TTypeSpecifier;
struct TStructUnionSpecifier;
struct TTypePointer;

struct SymbolMapItem
{
    struct SymbolMapItem* pNext;
    unsigned int HashValue;
    char* /*@auto*/ Key;
    struct TTypePointer* pValue;
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
                    struct TTypePointer* newValue);


struct TTypePointer* SymbolMap_Find(struct SymbolMap* pMap,
    const char* Key);

bool SymbolMap_RemoveKey(struct SymbolMap* pMap,
                         const char* Key,
                         struct TTypePointer** ppValue);

void SymbolMap_Init(struct SymbolMap* p);
void SymbolMap_Destroy(struct SymbolMap* p);

struct SymbolMap* SymbolMap_Create();
void SymbolMap_Delete(struct SymbolMap* p);

struct SymbolMapItem* SymbolMap_FindBucket(struct SymbolMap* pMap, const char* Key);

void SymbolMap_Swap(struct SymbolMap* pA, struct SymbolMap* pB);

void SymbolMap_Print(struct SymbolMap* pMap);
bool SymbolMap_IsTypeName(struct SymbolMap* pMap, const char* identifierName);

struct SymbolMapItem* SymbolMap_GetAssocAt(struct SymbolMap* pMap,
    const char* Key,
                                           unsigned int* nHashBucket,
                                           unsigned int* HashValue);

struct TStructUnionSpecifier* SymbolMap_FindCompleteStructUnionSpecifier(struct SymbolMap* pMap, const char* structTagName);



struct TTypeSpecifier* SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindTypedefDeclarationTarget(struct SymbolMap* pMap,
    const char* typedefName);

struct TDeclaration* SymbolMap_FindFunction(struct SymbolMap* pMap, const char* funcName);

struct TEnumSpecifier* SymbolMap_FindCompleteEnumSpecifier(struct SymbolMap* pMap, const char* enumName);

struct TDeclaration* SymbolMap_FindObjFunction2(struct SymbolMap* pMap,
    const char* objName,
                                                const char* funcName);


struct TDeclarationSpecifiers* SymbolMap_FindTypedefTarget(struct SymbolMap* pMap,
    const char* typedefName,
                                                           struct TDeclarator* declarator);

struct TDeclarationSpecifiers* SymbolMap_FindTypedefFirstTarget(struct SymbolMap* pMap,
    const char* typedefName,
                                                                struct TDeclarator* declarator);








struct TokenArray
{
    struct PPToken* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

#define TOKENARRAY_INIT {0, 0, 0}

void      TokenArray_Reserve(struct TokenArray* p, int nelements);

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
void TokenArray_ToStrBuilder(const struct TokenArray* tokens, struct StrBuilder* strBuidler);

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

void TokenSet_PushUnique(struct TokenSet* p, struct PPToken* pItem);
void TokenSetAppendCopy(struct TokenSet* pArrayTo, const struct TokenSet* pArrayFrom);
struct PPToken* TokenSet_Find(const struct TokenSet* pArray, const char* lexeme);
void TokenSet_Destroy(struct TokenSet* pArray);

void SetIntersection(const struct TokenSet* p1,
                     const struct TokenSet* p2,
                     struct TokenSet* pResult);






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







enum Tokens
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
    TK_HYPHEN_MINUS_NEG,// = '-'; //nao retorna no basic char mas eh usado para saber se eh - unario
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

    //enum Tokens para linhas do pre processador
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



};


struct ScannerItem
{
    struct LocalStrBuilder lexeme;
    enum Tokens token;
    int Line /*@= -1*/;
    int FileIndex /*@= -1*/;
    bool bActive /*@= 1*/;
    struct ScannerItem* pNext;
};


const char* TokenToString(enum Tokens tk);

void ScannerItem_Init(struct ScannerItem* scannerItem);
void ScannerItem_Reset(struct ScannerItem* scannerItem);
void ScannerItem_Swap(struct ScannerItem* scannerItem, struct ScannerItem* other);
void ScannerItem_Destroy(struct ScannerItem* scannerItem);
void ScannerItem_Copy(struct ScannerItem* scannerItem, struct ScannerItem* other);
struct ScannerItem* ScannerItem_Create(void);
void ScannerItem_Delete(struct ScannerItem* scannerItem);

enum BasicScannerType
{
    BasicScannerType_Macro,
    BasicScannerType_Token,
    BasicScannerType_File,
};

struct BasicScanner
{
    enum BasicScannerType Type;
    struct Stream stream;
    struct ScannerItem currentItem;

    //true antes do 1 token de cada linha
    bool bLineStart;
    bool bMacroExpanded;
    int FileIndex;
    enum Tokens m_Token;
    struct BasicScanner* pPrevious;

};


const char* BasicScanner_Lexeme(struct BasicScanner* scanner);
bool        BasicScanner_IsLexeme(struct BasicScanner* scanner, const char* psz);

void        BasicScanner_Match(struct BasicScanner* scanner);
bool         BasicScanner_MatchToken(struct BasicScanner* scanner, enum Tokens token);
bool      BasicScanner_InitFile(struct BasicScanner* pScanner, const char* fileName);
bool      BasicScanner_CreateFile(const char* fileName, struct BasicScanner** pp);
void        BasicScanner_Delete(struct BasicScanner* pScanner);

bool BasicScanner_Init(struct BasicScanner* pScanner,
                       const char* name,
                       const char* Text,
                       enum BasicScannerType Type);

bool BasicScanner_Create(struct BasicScanner** pp,
                         const char* name,
                         const char* Text,
                         enum BasicScannerType Type);

void BasicScanner_Destroy(struct BasicScanner* pScanner);





struct BasicScannerStack
{
    struct BasicScanner * pTop;
};

#define ITEM_STACK_INIT NULL
void BasicScannerStack_Init(struct BasicScannerStack* stack);
void BasicScannerStack_Push(struct BasicScannerStack* stack, struct BasicScanner* pItem);
struct BasicScanner* BasicScannerStack_PopGet(struct BasicScannerStack* stack);
void BasicScannerStack_Pop(struct BasicScannerStack* stack);
void BasicScannerStack_PopIfNotLast(struct BasicScannerStack* stack);
void BasicScannerStack_Destroy(struct BasicScannerStack* stack);

#define ForEachBasicScanner(pItem, stack)\
    for (struct BasicScanner* pItem = stack;\
      pItem;\
      pItem = pItem->pPrevious)






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

typedef struct Map2 TFileMap;

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






#define CAST(FROM, TO) \
static inline struct TO *  FROM##_As_##TO( struct FROM*  p)\
{\
if (p != NULL &&  p->Type == TO##_ID)\
    return ( struct TO * )p;\
  return NULL;\
}\
static inline  struct FROM *  TO##_As_##FROM(struct TO*  p)\
{\
    return (  struct FROM * )p;\
}

#define CASTSAME(FROM, TO) \
static inline struct TO * FROM##_As_##TO(struct FROM* p) { return (struct TO * ) p; }\
static inline struct FROM * TO##_As_##FROM(struct TO* p) { return (struct FROM *) p; }


/*
AST data structures
*/

enum Type
{
    TNull_ID,
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
    TTypeName_ID,
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
};

struct TTypePointer
{
    enum Type Type;
};


struct TFilePos
{
    int FileIndex;
    int Line;
};

#define TPOSITION_INIT {0,0}


struct TStaticAssertDeclaration
{
    /*
    static_assert-declaration:
    _Static_assert ( constant-expression , char-literal ) ;
    */
    enum Type Type /*@=TStaticAssertDeclaration_ID*/;

    struct TExpression* /*@auto*/ pConstantExpression;
    char* /*@auto*/ Text;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    struct TScannerItemList ClueList3;
    struct TScannerItemList ClueList4;
    struct TScannerItemList ClueList5;

};

struct TStaticAssertDeclaration* TStaticAssertDeclaration_Create();
void TStaticAssertDeclaration_Delete(struct TStaticAssertDeclaration* p);


struct TEofDeclaration
{
    /*
    Marca fim de um arquivo
    */
    enum Type Type /*@=TEofDeclaration_ID*/;
    struct TScannerItemList ClueList0;
};

struct TEofDeclaration* TEofDeclaration_Create();
void TEofDeclaration_Delete(struct TEofDeclaration* p);


struct /*@<TStaticAssertDeclaration |
  TDeclaration |
  TGroupDeclaration |
  TEofDeclaration>*/ TAnyDeclaration
{
    enum Type Type;
};

void TAnyDeclaration_Delete(struct TAnyDeclaration* p);


struct TBlockItemList
{
    /*
    block-item-list:
    block-item
    block-item-list block-item
    */
    struct TBlockItem* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

void TBlockItemList_Destroy(struct TBlockItemList* p);
void TBlockItemList_Init(struct TBlockItemList* p);
void TBlockItemList_PushBack(struct TBlockItemList* p, struct TBlockItem* pItem);


struct TCompoundStatement
{
    enum Type Type  /*@=TCompoundStatement_ID*/;
    struct TBlockItemList BlockItemList;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;

};

struct TCompoundStatement* TCompoundStatement_Create();
void TCompoundStatement_Delete(struct TCompoundStatement* p);


struct TTypeQualifier
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

    enum Type Type /*@=TTypeQualifier_ID*/;
    char* /*@auto*/ SizeIdentifier;
    enum Tokens Token;
    struct TScannerItemList ClueList0;

};

void TTypeQualifier_Copy(struct TTypeQualifier* dest, struct TTypeQualifier* src);
bool TTypeQualifier_Compare(struct TTypeQualifier* p1, struct TTypeQualifier* p2);

struct TTypeQualifierList
{
    /*
    type-qualifier-list:
    type-qualifier
    type-qualifier-list type-qualifier
    */

    struct TTypeQualifier* /*@auto*/ Data[4];
    int Size;
};

void TTypeQualifierList_Init(struct TTypeQualifierList* p);
void TTypeQualifierList_Destroy(struct TTypeQualifierList* p);
void TTypeQualifierList_PushBack(struct TTypeQualifierList* p, struct TTypeQualifier* pItem);
void TTypeQualifierList_Copy(struct TTypeQualifierList* dest, struct TTypeQualifierList* src);

struct TTypeQualifier* TTypeQualifier_Create(void);
void TTypeQualifier_Delete(struct TTypeQualifier* p);


struct TExpressionStatement
{
    enum Type Type /*@=TExpressionStatement_ID*/;
    struct TExpression* /*@auto*/ pExpression;
    struct TScannerItemList ClueList0;
};

struct TExpressionStatement* TExpressionStatement_Create(void);
void TExpressionStatement_Delete(struct TExpressionStatement* p);

struct TJumpStatement
{
    enum Type Type /*@=TJumpStatement_ID*/;
    enum Tokens token;
    char* /*@auto*/ Identifier;
    struct TExpression* /*@auto*/ pExpression;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};

struct TJumpStatement* TJumpStatement_Create(void);
void TJumpStatement_Delete(struct TJumpStatement* p);


struct TAsmStatement
{
    enum Type Type  /*@=TAsmStatement_ID*/;
    struct TScannerItemList ClueList;
};

struct TAsmStatement* TAsmStatement_Create(void);
void TAsmStatement_Delete(struct TAsmStatement* p);

struct TForStatement
{
    /*
    iteration-statement:
     for ( expressionopt ; expressionopt ; expressionopt ) statement
     for ( declaration expressionopt ; expressionopt ) statement
    */

    enum Type Type  /*@=TForStatement_ID*/;
    struct TAnyDeclaration* /*@auto*/ pInitDeclarationOpt;
    struct TExpression* /*@auto*/ pExpression1;
    struct TExpression* /*@auto*/ pExpression2;
    struct TExpression* /*@auto*/ pExpression3;
    struct TStatement* /*@auto*/ pStatement;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    struct TScannerItemList ClueList3;
    struct TScannerItemList ClueList4;
};

struct TForStatement* TForStatement_Create(void);
void TForStatement_Delete(struct TForStatement* p);

struct TWhileStatement
{
    enum Type Type  /*@=TWhileStatement_ID*/;
    struct TExpression* /*@auto*/ pExpression;
    struct TStatement* /*@auto*/ pStatement;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};

struct TWhileStatement* TWhileStatement_Create(void);
void TWhileStatement_Delete(struct TWhileStatement* p);

struct TDoStatement
{
    enum Type Type  /*@=TDoStatement_ID*/;
    struct TExpression* /*@auto*/ pExpression;
    struct TStatement* /*@auto*/ pStatement;
    struct TScannerItemList ClueList0; //do
    struct TScannerItemList ClueList1; //while
    struct TScannerItemList ClueList2; //(
    struct TScannerItemList ClueList3; //)
    struct TScannerItemList ClueList4; // ;

};

struct TDoStatement* TDoStatement_Create(void);
void TDoStatement_Delete(struct TDoStatement* p);

struct TLabeledStatement
{
    enum Type Type  /*@=TLabeledStatement_ID*/;

    struct TStatement* /*@auto*/ pStatementOpt;
    struct TExpression* /*@auto*/ pExpression;
    char* /*@auto*/ Identifier;
    enum Tokens token;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
};

struct TLabeledStatement* TLabeledStatement_Create(void);
void TLabeledStatement_Delete(struct TLabeledStatement* p);


struct TSwitchStatement
{
    enum Type Type  /*@=TSwitchStatement_ID*/;
    struct TExpression* /*@auto*/ pConditionExpression;
    struct TStatement* /*@auto*/ pExpression;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};

struct TSwitchStatement* TSwitchStatement_Create(void);
void TSwitchStatement_Delete(struct TSwitchStatement* p);


struct TIfStatement
{
    enum Type Type  /*@=TIfStatement_ID*/;
    struct TExpression* /*@auto*/ pConditionExpression;
    struct TStatement* /*@auto*/ pStatement;
    struct TStatement* /*@auto*/ pElseStatement;
    struct TScannerItemList ClueList0; //if 
    struct TScannerItemList ClueList1; //(
    struct TScannerItemList ClueList2; //)
    struct TScannerItemList ClueList3; //else
};

struct TIfStatement* TIfStatement_Create(void);
void TIfStatement_Delete(struct TIfStatement* p);


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
    enum Type Type;
};

void TStatement_Delete(struct TStatement* p);

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



struct /*@<TDeclaration | TStatement>*/ TBlockItem
{
    /*block-item:
       declaration
       statement
    */
    enum Type Type;
};


void TBlockItem_Delete(struct TBlockItem* p);

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

struct TPointer
{
    /*
    pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
    */
    struct TTypeQualifierList Qualifier;
    struct TPointer* pNext;
    struct TScannerItemList ClueList0;
};

struct TPointer* TPointer_Create(void);
void TPointer_Delete(struct TPointer* p);
void TPointer_Copy(struct TPointer* dest, struct TPointer* src);


struct TPointerList
{
    /*
    pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
    */
    struct TPointer* pHead, * pTail;
};

void TPointerList_PushBack(struct TPointerList* pList, struct TPointer* pItem);


void TPointerList_Destroy(struct TPointerList* p);
bool TPointerList_IsPointer(struct TPointerList* pPointerlist);

bool TPointerList_IsAutoPointer(struct TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToAutoPointer(struct TPointerList* pPointerlist);
bool TPointerList_IsPointerToObject(struct TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToObject(struct TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToPointer(struct TPointerList* pPointerlist);
bool TPointerList_IsPointer(struct TPointerList* pPointerlist);
void TPointerList_Swap(struct TPointerList* a, struct TPointerList* b);
bool TPointerList_IsAutoPointerSizeToObject(struct TPointerList* pPointerlist);
bool TPointerList_IsPointerN(struct TPointerList* pPointerlist, int n);
const char* TPointerList_GetSize(struct TPointerList* pPointerlist);

struct TFunctionSpecifier
{
    /*
    function-specifier:
      inline
      _Noreturn
    */
    enum Type Type  /*@=TFunctionSpecifier_ID*/;
    enum Tokens Token;
    struct TScannerItemList ClueList0;
};


struct TFunctionSpecifier* TFunctionSpecifier_Create(void);
void TFunctionSpecifier_Delete(struct TFunctionSpecifier* p);
bool TFunctionSpecifier_Compare(struct TFunctionSpecifier* p1, struct TFunctionSpecifier* p2);

struct TStorageSpecifier
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
    enum Type Type  /*@=TStorageSpecifier_ID*/;
    enum Tokens Token;
    struct TScannerItemList ClueList0;
};

struct TStorageSpecifier* TStorageSpecifier_Create(void);
void TStorageSpecifier_Delete(struct TStorageSpecifier* p);
bool TStorageSpecifier_Compare(struct TStorageSpecifier* p1, struct TStorageSpecifier* p2);

struct TAlignmentSpecifier
{
    /*
    alignment-specifier:
    _Alignas ( type-name )
    _Alignas ( constant-expression )
    */
    enum Type Type  /*@=TAlignmentSpecifier_ID*/;
    char* /*@auto*/ TypeName;
};

struct TAlignmentSpecifier* TAlignmentSpecifier_Create(void);
void TAlignmentSpecifier_Delete(struct TAlignmentSpecifier* p);


struct TEnumerator
{
    /*
    enumerator:
    enumeration-constant
    enumeration-constant = constant-expression
    */
    struct TEnumerator* pNext;
    char* /*@auto*/ Name;
    struct TExpression* /*@auto*/ pConstantExpression;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1; // =
    struct TScannerItemList ClueList2; // ,
    bool bHasComma;
};

struct TEnumerator* TEnumerator_Create(void);
void TEnumerator_Delete(struct TEnumerator* p);


struct TEnumeratorList
{
    /*
    enumerator-list:
    enumerator
    enumerator-list, enumerator
    */
    struct TEnumerator* pHead, * pTail;
};
void TEnumeratorList_Destroy(struct TEnumeratorList* p);
void TEnumeratorList_Init(struct TEnumeratorList* p);

struct TEnumSpecifier
{
    /*
    enum-specifier:
    enum identifieropt { enumerator-list }
    enum identifieropt { enumerator-list , }
    enum identifier
    */

    enum Type Type  /*@=TEnumSpecifier_ID*/;
    char* /*@auto*/ Tag;
    struct TEnumeratorList EnumeratorList;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    struct TScannerItemList ClueList3;
};

struct TEnumSpecifier* TEnumSpecifier_Create(void);
void TEnumSpecifier_Delete(struct TEnumSpecifier* p);
bool TEnumSpecifier_IsSameTag(struct TEnumSpecifier* p1, struct TEnumSpecifier* p2);

struct TSingleTypeSpecifier
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
    enum Type Type  /*@=TSingleTypeSpecifier_ID*/;
    enum Tokens Token2;
    char* /*@auto*/ TypedefName;
    struct TScannerItemList ClueList0;
};

struct TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void);
void TSingleTypeSpecifier_Delete(struct TSingleTypeSpecifier* p);

const char* TSingleTypeSpecifier_GetTypedefName(struct TSingleTypeSpecifier* p);
bool TSingleTypeSpecifier_Compare(struct TSingleTypeSpecifier* p1, struct TSingleTypeSpecifier* p2);


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
    enum Type Type;
};


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
    enum Type Type;
};


/*
specifier-qualifier-list:
type-specifier specifier-qualifier-listopt
type-qualifier specifier-qualifier-listopt
*/

void TSpecifierQualifier_Delete(struct TSpecifierQualifier* p);

CAST(TSpecifierQualifier, TStorageSpecifier)
CAST(TSpecifierQualifier, TAlignmentSpecifier)
CAST(TSpecifierQualifier, TSingleTypeSpecifier)

CAST(TSpecifierQualifier, TTypeQualifier)
CAST(TSpecifierQualifier, TEnumSpecifier)


struct TSpecifierQualifierList
{
    /*
    specifier-qualifier-list:
    type-specifier specifier-qualifier-listopt
    type-qualifier specifier-qualifier-listopt
    */
    struct TSpecifierQualifier* /*@auto*/* /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};

void TSpecifierQualifierList_Destroy(struct TSpecifierQualifierList* pDeclarationSpecifiers);
void TSpecifierQualifierList_PushBack(struct TSpecifierQualifierList* p, struct TSpecifierQualifier* pItem);

const char* TSpecifierQualifierList_GetTypedefName(struct TSpecifierQualifierList* p);
struct TDeclarationSpecifier* TSpecifierQualifierList_GetMainSpecifier(struct TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsTypedefQualifier(struct TSpecifierQualifierList* p);
bool TSpecifierQualifierList_Compare(struct TSpecifierQualifierList* p1, struct TSpecifierQualifierList* p2);

bool TSpecifierQualifierList_CanAdd(struct TSpecifierQualifierList* p, enum Tokens token, const char* lexeme);
bool TSpecifierQualifierList_IsBool(struct TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsChar(struct TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyInteger(struct TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyFloat(struct TSpecifierQualifierList* p);


struct TDeclarationSpecifiers
{
    /*
    declaration-specifiers:
    storage-class-specifier declaration-specifiersopt
    type-specifier declaration-specifiersopt
    type-qualifier declaration-specifiersopt
    function-specifier declaration-specifiersopt
    alignment-specifier declaration-specifiersopt
    */
    struct TDeclarationSpecifier* /*@auto*/* /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};

void TDeclarationSpecifiers_Init(struct TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_Destroy(struct TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_PushBack(struct TDeclarationSpecifiers* p, struct TDeclarationSpecifier* pItem);
struct TDeclarationSpecifier* TDeclarationSpecifiers_GetMainSpecifier(struct TDeclarationSpecifiers* p, enum Type type);


const char* TDeclarationSpecifiers_GetTypedefName(struct TDeclarationSpecifiers* pDeclarationSpecifiers);
bool TDeclarationSpecifiers_CanAddSpeficier(struct TDeclarationSpecifiers* pDeclarationSpecifiers, enum Tokens token, const char* lexeme);


struct TStructUnionSpecifier* TDeclarationSpecifiers_GetCompleteStructUnionSpecifier(struct SymbolMap* pSymbolMap,
    struct TDeclarationSpecifiers* pDeclarationSpecifiers);


struct TParameterList
{
    /*
    parameter-list:
    parameter-declaration
    parameter-list , parameter-declaration
    */

    struct TParameter* pHead, * pTail;
};

void TParameterList_Destroy(struct TParameterList* p);
void TParameterList_Init(struct TParameterList* p);
const char* TParameter_GetName(struct TParameter* p);
bool TParameter_IsDirectPointer(struct TParameter* p);

struct TParameterTypeList
{
    /*
    parameter-type-list:
    parameter-list
    parameter-list , ...
    */
    struct TParameterList ParameterList;
    struct TScannerItemList ClueList0; //,
    struct TScannerItemList ClueList1; //...
    bool bVariadicArgs;
};

void TParameterTypeList_Init(struct TParameterTypeList* p);
void TParameterTypeList_Destroy(struct TParameterTypeList* p);
struct TParameterTypeList* TParameterTypeList_Create();
void TParameterTypeList_Delete(struct TParameterTypeList* p);

const char* TParameterTypeList_GetFirstParameterName(struct TParameterTypeList* p);
const char* TParameterTypeList_GetSecondParameterName(struct TParameterTypeList* p);
struct TParameter* TParameterTypeList_FindParameterByName(struct TParameterTypeList* p, const char* name);
struct TParameter* TParameterTypeList_GetParameterByIndex(struct TParameterTypeList* p, int index);
void TParameterTypeList_GetArgsString(struct TParameterTypeList* p, struct StrBuilder* sb);
bool TParameterTypeList_HasNamedArgs(struct TParameterTypeList* p);

struct TDesignator
{
    /*
    designator:
    [ constant-expression ]
    . identifier
    */
    char* /*@auto*/ Name;
    struct TExpression* /*@auto*/ pExpression;
    struct TDesignator* pNext;
    struct TScannerItemList ClueList0; //. ou [
    struct TScannerItemList ClueList1; //]
};


struct TDesignator* TDesignator_Create(void);
void TDesignator_Delete(struct TDesignator* p);


struct TDesignatorList
{
    /*
    designator-list:
    designator
    designator-list designator
    */
    struct TDesignator* /*@auto*/ pHead, * pTail;
};

void TDesignatorList_Destroy(struct TDesignatorList* p);
void TDesignatorList_Init(struct TDesignatorList* p);
void TDesignatorList_PushBack(struct TDesignatorList* p, struct TDesignator* pItem);

struct TDesignation
{
    /*
    designation:
    designator-list =
    */
    struct TDesignatorList DesignatorList;
    struct TScannerItemList ClueList0;
};

struct TDesignation* TDesignation_Create(void);
void TDesignation_Delete(struct TDesignation* p);

struct TInitializer;

void TInitializer_Delete(struct TInitializer* p);

struct TInitializerListItem
{
    /*
    initializer-list:
    designationopt initializer
    initializer-list , designationopt initializer
    */
    struct TDesignatorList  DesignatorList;
    struct TInitializer* /*@auto*/ pInitializer;
    struct TInitializerListItem* pNext;
    struct TScannerItemList ClueList;
    bool bDefault;
};

struct TInitializerListItem* TInitializerListItem_Create();
void TInitializerListItem_Delete(struct TInitializerListItem* p);


struct TInitializerList
{
    /*
    initializer-list:
    designationopt initializer
    initializer-list , designationopt initializer
    */

    struct TInitializerListItem* /*@auto*/ pHead, * pTail;
};

void TInitializerList_Init(struct TInitializerList* p);
void TInitializerList_Destroy(struct TInitializerList* p);


struct TInitializerListType
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

    enum Type Type  /*@=TInitializerListType_ID*/;
    struct TInitializerList InitializerList;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    bool bDefault;
};

struct TInitializerListType* TInitializerListType_Create(void);
void TInitializerListType_Delete(struct TInitializerListType* p);



struct /*@<TInitializerListType | TExpression>*/ TInitializer
{
    /*
    initializer:
    assignment-expression

    { initializer-list }
    { initializer-list ,}
    */
    enum Type Type;
};

CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)


struct TDeclarator
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

    struct TPointerList PointerList;
    struct TDirectDeclarator* /*@auto*/ pDirectDeclarator;
    struct TScannerItemList ClueList;
};

struct TDeclarator* TDeclarator_Create();
void TDeclarator_Delete(struct TDeclarator* p);
void TDeclarator_Init(struct TDeclarator* p);
void TDeclarator_Destroy(struct TDeclarator* p);
const char* TDeclarator_GetName(struct TDeclarator* p);
void TDeclarator_Swap(struct TDeclarator* a, struct TDeclarator* b);
bool TDeclarator_IsAutoArray(struct TDeclarator* pDeclarator);

enum TDirectDeclaratorType
{
    TDirectDeclaratorTypeNone,
    TDirectDeclaratorTypeIdentifier,
    TDirectDeclaratorTypeDeclarator,
    TDirectDeclaratorTypeFunction,
    TDirectDeclaratorTypeArray,
    TDirectDeclaratorTypeAutoArray,
};

struct TDirectDeclarator
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

    char* /*@auto*/ Identifier;
    struct TDeclarator* /*@auto*/ pDeclarator;
    struct TDirectDeclarator* /*@auto*/ pDirectDeclarator;
    struct TFilePos Position;
    struct TParameterTypeList  Parameters;
    struct TExpression* /*@auto*/ pExpression;
    enum TDirectDeclaratorType DeclaratorType; //para diferenciar pois null nao basta []
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    struct TScannerItemList ClueList3;
};


struct TDirectDeclarator* TDirectDeclarator_Create();
void TDirectDeclarator_Delete(struct TDirectDeclarator* p);

struct TInitDeclarator
{
    /*
    init-declarator:
    declarator
    declarator = initializer
    */
    struct TDeclarator* /*@auto*/ pDeclarator;
    struct TInitializer* /*@auto*/ pInitializer;
    struct TInitDeclarator* pNext;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1; //defval
};
typedef struct TInitDeclarator TStructDeclarator;

struct TInitDeclarator* TInitDeclarator_Create();
void TInitDeclarator_Delete(struct TInitDeclarator* p);


struct TInitDeclaratorList
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */
    struct TInitDeclarator* pHead, * pTail;
};

void TInitDeclaratorList_Destroy(struct TInitDeclaratorList* p);
void TInitDeclaratorList_Init(struct TInitDeclaratorList* p);
const char* TDeclarator_GetName(struct TDeclarator* p);
const char* TInitDeclarator_FindName(struct TInitDeclarator* p);


struct TStructDeclaratorList
{
    /*
    init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
    */
    struct TInitDeclarator* /*@auto*/ pHead, * pTail;
};

void TStructDeclaratorList_Destroy(struct TStructDeclaratorList* p);
void TStructDeclaratorList_Init(struct TStructDeclaratorList* p);
void TStructDeclaratorList_Add(struct TStructDeclaratorList* p, struct TInitDeclarator* pItem);


struct TStructDeclaration
{
    /*
    struct-declaration:
    specifier-qualifier-list struct-declarator-listopt ;
    static_assert-declaration
    */

    enum Type Type  /*@=TStructDeclaration_ID*/;

    struct TSpecifierQualifierList SpecifierQualifierList;
    struct TStructDeclaratorList DeclaratorList;
    struct TScannerItemList ClueList1;
};

struct TStructDeclaration* TStructDeclaration_Create();
void TStructDeclaration_Delete(struct TStructDeclaration* p);


/*
struct-declaration:
specifier-qualifier-list struct-declarator-listopt ;
static_assert-declaration
*/
struct /*@<TStructDeclaration | TStaticAssertDeclaration>*/ TAnyStructDeclaration
{
    enum Type Type;
};


void TAnyStructDeclaration_Delete(struct TAnyStructDeclaration* p);

CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)
CAST(TAnyStructDeclaration, TEofDeclaration)

struct TStructDeclarationList
{
    struct TAnyStructDeclaration* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

void TStructDeclarationList_Destroy(struct TStructDeclarationList* p);
void TStructDeclarationList_Init(struct TStructDeclarationList* p);
void TStructDeclarationList_PushBack(struct TStructDeclarationList* p, struct TAnyStructDeclaration* pItem);


struct TUnionSetItem
{
    struct TUnionSetItem* pNext;
    enum Tokens Token;
    enum Tokens TokenFollow;
    char* /*@auto*/ Name;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};

struct TUnionSetItem* TUnionSetItem_Create();
void TUnionSetItem_Delete(struct TUnionSetItem*);

struct TUnionSet
{
    struct TUnionSetItem* pHead, * pTail;

    struct TScannerItemList ClueList0; // <
    struct TScannerItemList ClueList1; // > 
};

void TUnionSet_Init(struct TUnionSet* p);
void TUnionSet_Destroy(struct TUnionSet* p);
void TUnionSet_PushBack(struct TUnionSet* p, struct TUnionSetItem* pItem);

struct TStructUnionSpecifier
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

    enum Type Type  /*@=TStructUnionSpecifier_ID*/;
    struct TStructDeclarationList StructDeclarationList;
    char* /*@auto*/ Tag;

    enum Tokens Token;


    struct TUnionSet UnionSet;
    struct TScannerItemList ClueList0; //struct-or-union
    struct TScannerItemList ClueList1; //identifieropt
    struct TScannerItemList ClueList2; //{
    struct TScannerItemList ClueList3; //}


};

struct TStructUnionSpecifier* TStructUnionSpecifier_Create();
void TStructUnionSpecifier_Delete(struct TStructUnionSpecifier* p);


struct /*@<TSingleTypeSpecifier |
  TAtomicTypeSpecifier |
  TEnumSpecifier |
  TStructUnionSpecifier>*/ TTypeSpecifier
{
    enum Type Type;
};

bool TTypeSpecifier_Compare(struct TTypeSpecifier* p1, struct TTypeSpecifier* p2);


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


struct TDeclaration
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

    enum Type Type  /*@=TDeclaration_ID*/;
    struct TDeclarationSpecifiers Specifiers;
    struct TInitDeclaratorList InitDeclaratorList;

    //se for funcao
    struct TCompoundStatement* /*@auto*/ pCompoundStatementOpt;

    int FileIndex;
    int Line;

    struct TScannerItemList ClueList0; //default FunctionTag
    struct TScannerItemList ClueList00; //:
    struct TScannerItemList ClueList001; //identifier

    bool bDefault;
    char* /*@auto*/ FunctionTag;
    bool bAutoTag;
    struct TScannerItemList ClueList1;


};


struct TDeclaration* TDeclaration_Create();
void TDeclaration_Delete(struct TDeclaration* p);

struct TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(struct TDeclaration* p, int index);

const char* TDeclaration_GetArgName(struct TDeclaration* p, int index);
int TDeclaration_GetNumberFuncArgs(struct TDeclaration* p);

bool TDeclaration_Is_StructOrUnionDeclaration(struct TDeclaration* p);

struct TCompoundStatement* TDeclaration_Is_FunctionDefinition(struct TDeclaration* p);

struct TDeclarator* TDeclaration_FindDeclarator(struct TDeclaration* p, const char* name);
const char* TDeclaration_GetFunctionName(struct TDeclaration* p);
const char* TDeclaration_FindFunctionTagName(struct TDeclaration* p, struct SymbolMap* pMap);


CAST(TAnyDeclaration, TStaticAssertDeclaration)
CAST(TAnyDeclaration, TDeclaration)
CAST(TAnyDeclaration, TEofDeclaration)

bool TAnyDeclaration_IsTypedef(struct TAnyDeclaration* pDeclaration);
bool TAnyDeclaration_Is_StructOrUnionDeclaration(struct TAnyDeclaration* pDeclaration);
int TAnyDeclaration_GetFileIndex(struct TAnyDeclaration* pDeclaration);


struct TParameter
{
    enum Type Type  /*@=TParameter_ID*/;
    /*
    parameter-declaration:
    declaration-specifiers declarator
    declaration-specifiers abstract-declaratoropt
    */

    struct TParameter* pNext;
    struct TDeclarationSpecifiers Specifiers;
    struct TDeclarator Declarator;
    struct TScannerItemList ClueList0; //, do parametro
    bool bHasComma;
};

struct TParameter* TParameter_Create();
void TParameter_Delete(struct TParameter* p);

void TParameter_Swap(struct TParameter* a, struct TParameter* b);
const char* TParameter_GetName(struct TParameter* p);
const char* TParameter_GetTypedefName(struct TParameter* p);
bool TParameter_IsAutoArray(struct TParameter* pParameter);

struct TDeclarations
{
    struct TAnyDeclaration* /*@auto*/* /*@auto*/ /*@[Size]*/ pItems;
    int Size;
    int Capacity;
};

void TDeclarations_Destroy(struct TDeclarations* p);
void TDeclarations_Init(struct TDeclarations* p);
void TDeclarations_PushBack(struct TDeclarations* p, struct TAnyDeclaration* pItem);

struct TGroupDeclaration
{
    /*
    default identifier
    {
    }
    */
    enum Type Type  /*@=TGroupDeclaration_ID*/;
    struct TDeclarations Declarations;
    char* /*@auto*/ Identifier;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};

struct TGroupDeclaration* TGroupDeclaration_Create();
void TGroupDeclaration_Delete(struct TGroupDeclaration* p);


struct TTypeName
{
    /*
    type-name:
    specifier-qualifier-list abstract-declaratoropt
    */
    enum Type Type  /*@=TTypeName_ID*/;
    struct TSpecifierQualifierList SpecifierQualifierList;
    struct TDeclarator Declarator;
};

struct TTypeName* TTypeName_Create();
void TTypeName_Destroy(struct TTypeName* p);
void TTypeName_Delete(struct TTypeName* p);
void TTypeName_Init(struct TTypeName* p);

struct TAtomicTypeSpecifier
{
    /*
    atomic-type-specifier:
    _Atomic ( type-name )
    */
    enum Type Type  /*@=TAtomicTypeSpecifier_ID*/;
    struct TTypeName TypeName;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
};


struct TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create();
void TAtomicTypeSpecifier_Delete(struct TAtomicTypeSpecifier* p);
bool TAtomicTypeSpecifier_Compare(struct TAtomicTypeSpecifier* p1, struct TAtomicTypeSpecifier* p2);


bool EvaluateConstantExpression(struct TExpression* p, int* pResult);

struct TParameterTypeList* TDeclaration_GetFunctionArguments(struct TDeclaration* p);

struct TDeclaration* SyntaxTree_FindFunctionDeclaration(struct SyntaxTree* p, const char* name);

bool TDeclarationSpecifiers_IsTypedef(struct TDeclarationSpecifiers* pDeclarationSpecifiers);



struct TPrimaryExpressionValue
{
    /*
    (6.5.1) primary-expression:
    identifier
    constant
    char-literal
    ( expression )
    generic-selection
    */

    enum Type Type /*@=TPrimaryExpressionValue_ID*/;
    enum Tokens token;
    char* /*@auto*/ lexeme;
    struct TExpression* /*@auto*/ pExpressionOpt; //( expression )
    struct TDeclaration* pDeclaration; //se for identificador aponta para a declaracao dele
    struct TParameter* pParameter; //se for identificador pode apontar para parametro funcao

    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
};

void TPrimaryExpressionValue_Init(struct TPrimaryExpressionValue* p);
void TPrimaryExpressionValue_Destroy(struct TPrimaryExpressionValue* p);
struct TPrimaryExpressionValue* TPrimaryExpressionValue_Create();
void TPrimaryExpressionValue_Delete(struct TPrimaryExpressionValue* p);

struct TPrimaryExpressionLiteralItem
{
    struct TPrimaryExpressionLiteralItem* pNext;
    char* /*@auto*/ lexeme;
    struct TScannerItemList ClueList0;
};

struct TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create();
void TPrimaryExpressionLiteralItem_Delete(struct TPrimaryExpressionLiteralItem* p);

struct TPrimaryExpressionLiteralItemList
{
    struct TPrimaryExpressionLiteralItem* pHead, * pTail;
};

void TPrimaryExpressionLiteralItemList_Init(struct TPrimaryExpressionLiteralItemList* p);
void TPrimaryExpressionLiteralItemList_Destroy(struct TPrimaryExpressionLiteralItemList* p);
void TPrimaryExpressionLiteralItemList_Add(struct TPrimaryExpressionLiteralItemList* p, struct TPrimaryExpressionLiteralItem* pItem);


struct TPrimaryExpressionLiteral
{
    enum Type Type /*@=TPrimaryExpressionLiteral_ID*/;
    struct TPrimaryExpressionLiteralItemList List;
};


struct TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create();
void TPrimaryExpressionLiteral_Delete(struct TPrimaryExpressionLiteral* p);


struct TBinaryExpression
{
    enum Type Type /*@=TBinaryExpression_ID*/;
    enum Tokens token;
    struct TExpression* /*@auto*/ pExpressionLeft;
    struct TExpression* /*@auto*/ pExpressionRight;
    struct TFilePos Position;
    struct TScannerItemList ClueList0;
};

struct TBinaryExpression* TBinaryExpression_Create(void);
void TBinaryExpression_Delete(struct TBinaryExpression* p);

struct TTernaryExpression
{
    enum Type Type /*@=TTernaryExpression_ID*/;
    enum Tokens token;
    struct TExpression* /*@auto*/ pExpressionLeft;
    struct TExpression* /*@auto*/ pExpressionMiddle;
    struct TExpression* /*@auto*/ pExpressionRight;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
};

struct TTernaryExpression* TTernaryExpression_Create(void);
void TTernaryExpression_Delete(struct TTernaryExpression* p);


struct TPostfixExpressionCore
{
    enum Type Type  /*@=TPostfixExpressionCore_ID*/;
    enum Tokens token;
    char* /*@auto*/ lexeme;
    struct TExpression* /*@auto*/ pExpressionLeft;
    struct TExpression* /*@auto*/ pExpressionRight;

    struct TPostfixExpressionCore* /*@auto*/ pNext;
    struct TInitializerList InitializerList;
    char* /*@auto*/ Identifier;
    struct TTypeName* /*@auto*/ pTypeName;

    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
    struct TScannerItemList ClueList2;
    struct TScannerItemList ClueList3;
    struct TScannerItemList ClueList4;

};

struct TPostfixExpressionCore* TPostfixExpressionCore_Create();
void TPostfixExpressionCore_Delete(struct TPostfixExpressionCore* p);


struct TCastExpressionType
{
    enum Type Type  /*@=TCastExpressionType_ID*/;
    struct TExpression* /*@auto*/ pExpression;
    struct TTypeName TypeName;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1;
};

struct TCastExpressionType* TCastExpressionType_Create();
void TCastExpressionType_Delete(struct TCastExpressionType* p);


struct TUnaryExpressionOperator
{
    enum Type Type  /*@=TUnaryExpressionOperator_ID*/;
    enum Tokens token;
    struct TExpression* /*@auto*/ pExpressionRight;
    struct TTypeName TypeName;
    struct TScannerItemList ClueList0;
    struct TScannerItemList ClueList1; //sizeof (
    struct TScannerItemList ClueList2; //sizeof ( )
};


struct TUnaryExpressionOperator* TUnaryExpressionOperator_Create();
void TUnaryExpressionOperator_Delete(struct TUnaryExpressionOperator* p);

struct  /*@<TPrimaryExpressionLiteral |
  TPrimaryExpressionValue |
  TBinaryExpression |
  TUnaryExpressionOperator |
  TPostfixExpressionCore |
  TPostfixExpressionCore |
  TCastExpressionType |
  TTernaryExpression |
  TPrimaryExpressionLambda>*/TExpression
{
    enum Type Type;
};


void TExpression_Delete(struct TExpression* p);


CAST(TExpression, TPrimaryExpressionLiteral)
CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)


struct TPrimaryExpressionLambda
{
    enum Type Type /*@=TPrimaryExpressionLambda_ID*/;

    struct TCompoundStatement* pCompoundStatement;
    struct TParameterTypeList* /*@auto*/ pParameterTypeListOpt;
    struct TScannerItemList ClueList0; //[
    struct TScannerItemList ClueList1; //]
    struct TScannerItemList ClueList2; //(
    struct TScannerItemList ClueList3; //)
};

struct TPrimaryExpressionLambda* TPrimaryExpressionLambda_Create();
void TPrimaryExpressionLambda_Delete(struct TPrimaryExpressionLambda* p);


struct SyntaxTree
{
    //declaracoes
    struct TDeclarations Declarations;

    //arquivos na qual declaracao tem indice
    struct TFileArray Files2;

    //multimap dos simbolos
    //DeclarationsMap Symbols;
    struct SymbolMap GlobalScope;

    //Defines
    struct MacroMap Defines;
};


void SyntaxTree_Init(struct SyntaxTree* p);
void SyntaxTree_Destroy(struct SyntaxTree* p);
struct TDeclaration* SyntaxTree_GetFinalTypeDeclaration(struct SyntaxTree* p, const char* typeName);
struct TDeclaration* SyntaxTree_FindDeclaration(struct SyntaxTree* p, const char* name);







struct ParserOptions
{
    bool bNoImplicitTag;
};

struct Parser
{
    // indica presenca de erro no parser
    bool bError;

    // mensagem de erro
    struct StrBuilder ErrorMessage;

    // scanner ja pré-processado
    struct Scanner Scanner;

    struct TScannerItemList ClueList;

    struct SymbolMap GlobalScope;
    struct SymbolMap* pCurrentScope;

    int IncludeLevel;
    bool bPreprocessorEvalFlag;

    struct ParserOptions ParserOptions;
};

bool Parser_InitFile(struct Parser* parser, const char* fileName);

bool Parser_InitString(struct Parser* parser, const char* name, const char* Text);

void Parser_Destroy(struct Parser* parser);

bool Parser_HasError(struct Parser* pParser);

const char* GetCompletationMessage(struct Parser* parser);

bool GetAST(const char* filename,
            const char* configFileName,
            struct Options* options,
            struct SyntaxTree* pSyntaxTree);

void ConstantExpression(struct Parser* ctx, struct TExpression** ppExpression);
enum Tokens Parser_MatchToken(struct Parser* parser, enum Tokens tk, struct TScannerItemList* listOpt);

enum Tokens Parser_LookAheadToken(struct Parser* parser);

bool GetASTFromString(const char* sourceCode,
                      struct Options* options,
                      struct SyntaxTree* pSyntaxTree);






struct IntegerStack
{
    int* /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};


#define INTEGER_STACK_INIT {0,0,0}
enum Search
{
    SearchNone,
    SearchAll,
    SearchDestroy,
    SearchInit,
    SearchDelete,
};


struct PrintCodeOptions
{
    struct Options Options;

    ///////////
    //controle interno
    struct IntegerStack Stack;// = 0;
    bool bInclude;// = true;
    int IdentationLevel;
    //

    struct StrBuilder sbPreDeclaration;

};

#define CODE_PRINT_OPTIONS_INIT {OPTIONS_INIT, INTEGER_STACK_INIT, true, 0, STRBUILDER_INIT}

void PrintCodeOptions_Destroy(struct PrintCodeOptions* options);

void SyntaxTree_PrintCodeToFile(struct SyntaxTree* pSyntaxTree,
                                struct Options* options,
                                const char* fileName,
                                const char* userpath);

void SyntaxTree_PrintCodeToString(struct SyntaxTree* pSyntaxTree,
                                  struct Options* options,
                                  struct StrBuilder* output);


void TTypeName_CodePrint(struct SyntaxTree* pSyntaxTree, struct PrintCodeOptions* options, struct TTypeName* p, struct StrBuilder* fp);



void TSpecifierQualifierList_CodePrint(struct SyntaxTree* pSyntaxTree,
                                       struct PrintCodeOptions* options,
                                       struct TSpecifierQualifierList* pDeclarationSpecifiers,

                                       struct StrBuilder* fp);


void TDeclarationSpecifiers_CodePrint(struct SyntaxTree* pSyntaxTree, struct PrintCodeOptions* options, struct TDeclarationSpecifiers* pDeclarationSpecifiers, struct StrBuilder* fp);

enum Action
{
    ActionDestroy,
    ActionDestroyContent,
    ActionDelete,
    ActionCreate,
    ActionInit,
    ActionInitContent,
    ActionStaticInit,
};

void InstanciateEspecialFunction(struct SyntaxTree* pSyntaxTree,
                         struct PrintCodeOptions* options,
                         struct TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
                         struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                         struct TInitializer* pInitializer,
                         struct TParameterTypeList* pArgsOpt,
                         const char* pInitExpressionText, //(x->p->i = 0)    
                         const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                                                     //se passar null eh pq nao interessa
                         const enum Action action,
                         enum Search search,
                         bool* pbHasInitializers,
                         struct StrBuilder* fp);



