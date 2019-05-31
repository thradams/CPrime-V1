#pragma once
#pragma source

#include <stdbool.h>
#include "StrBuilder.h"
#include "Stream.h"
#include "LocalStrBuilder.h"
#define LANGUAGE_EXTENSIONS
//


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



typedef struct BasicScanner* BasicScannerStack;

#define ITEM_STACK_INIT NULL
void BasicScannerStack_Init(BasicScannerStack* stack);
void BasicScannerStack_Push(BasicScannerStack* stack, struct BasicScanner* pItem);
struct BasicScanner* BasicScannerStack_PopGet(BasicScannerStack* stack);
void BasicScannerStack_Pop(BasicScannerStack* stack);
void BasicScannerStack_PopIfNotLast(BasicScannerStack* stack);
void BasicScannerStack_Destroy(BasicScannerStack* stack);

#define ForEachBasicScanner(pItem, stack)\
    for (struct BasicScanner* pItem = stack;\
      pItem;\
      pItem = pItem->pPrevious)

