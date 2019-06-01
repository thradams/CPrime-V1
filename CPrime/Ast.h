#pragma once
#pragma source

#include <stdlib.h>
#include <stdio.h>

#include "Array.h"

#include "StringEx.h"
#include "Scanner.h"
#include "Macro.h"
#include "SymbolMap.h"


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

enum TDirectDeclaratorType
{
    TDirectDeclaratorTypeNone,
    TDirectDeclaratorTypeIdentifier,
    TDirectDeclaratorTypeDeclarator,
    TDirectDeclaratorTypeFunction,
    TDirectDeclaratorTypeArray,

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

