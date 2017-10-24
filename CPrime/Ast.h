#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "Array.h"
#include "List.h"
#include "StringEx.h"
#include "Scanner.h"
#include "Macro.h"
#include "SymbolMap.h"


#define CAST(FROM, TO) \
static inline TO *  FROM##_As_##TO( FROM*  p)\
{\
if (p != NULL && IS_TYPE( (p), TO##_ID))\
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

    TParameter_ID
} EType;

struct TypeStruct
{
    EType type;
};

inline EType TypeOf(void* p) { return p ? ((struct TypeStruct*)(p))->type : TypeNull;  }
#define TYPEOF(p) TypeOf((void*) (p))
#define IS_TYPE(x, ID) (TYPEOF(x) == (ID))


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
	EType Type _defval(TEofDeclaration_ID);
	TScannerItemList ClueList0;
} TEofDeclaration;

TEofDeclaration* TEofDeclaration_Create();
void TEofDeclaration_Delete(TEofDeclaration* p);

struct TStatement;
typedef struct TStatement TStatement;


struct _union(TStaticAssertDeclaration |
              TDeclaration |
              TEofDeclaration) TAnyDeclaration;

typedef struct TAnyDeclaration TAnyDeclaration;
void TAnyDeclaration_Delete(TAnyDeclaration* p);


struct TBlockItem;
typedef struct TBlockItem TBlockItem;

typedef struct {
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
    EType Type _defval(TTypeQualifier_ID);

//#ifdef LANGUAGE_EXTENSIONS
    String SizeIdentifier;
//#endif

    Tokens Token;
    TScannerItemList ClueList0;


} TTypeQualifier;

typedef struct {
    TTypeQualifier * _auto * _auto _size(Size) pData;
    int Size;
    int Capacity;
} TTypeQualifierList;


#define TTYPEQUALIFIERLIST_INIT {0,0,0}
void TTypeQualifierList_Destroy(TTypeQualifierList* p);
void TTypeQualifierList_PushBack(TTypeQualifierList* p, TTypeQualifier* pItem);

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
              TSwitchStatement) TStatement;

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

struct _union(TStatement) TBlockItem;
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
    TTypeQualifierList Qualifier;
    Tokens Token;
    struct TPointer* _auto pNext;
    TScannerItemList ClueList0;
} TPointer;

TPointer* TPointer_Create(void);
void TPointer_Delete(TPointer* p);



typedef struct TPointerList
{
    TPointer* _auto pHead, *pTail;
} TPointerList;

void TPointerList_Destroy(TPointerList* p);
bool TPointerList_IsPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerN(TPointerList* pPointerlist, int n);
bool TPointerList_IsAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointer(TPointerList* pPointerlist);

const char * TPointerList_GetSize(TPointerList* pPointerlist);

typedef struct
{
    EType Type  _defval(TFunctionSpecifier_ID);
    //TTypeSpecifier*  _auto pNext;
    bool bIsInline;
    bool bIsNoReturn;
    TScannerItemList ClueList0;
} TFunctionSpecifier;


TFunctionSpecifier* TFunctionSpecifier_Create(void);
void TFunctionSpecifier_Delete(TFunctionSpecifier* p);

typedef struct
{
    EType Type  _defval(TStorageSpecifier_ID);    
    bool bIsTypedef;
    bool bIsExtern;
    bool bIsStatic;
    bool bIsThread_local;
    bool bIsAuto;
    bool bIsRegister;
    TScannerItemList ClueList0;
} TStorageSpecifier;

TStorageSpecifier* TStorageSpecifier_Create(void);
void TStorageSpecifier_Delete(TStorageSpecifier* p);



typedef struct
{
    EType Type  _defval(TAlignmentSpecifier_ID);    
    String TypeName;
    //_Alignas(type - name)
    //  _Alignas(constant - expression)
} TAlignmentSpecifier;

TAlignmentSpecifier* TAlignmentSpecifier_Create(void);
void TAlignmentSpecifier_Delete(TAlignmentSpecifier* p);


typedef struct TEnumerator
{
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
    TEnumerator * _auto pHead, *pTail;
} TEnumeratorList;
void TEnumeratorList_Destroy(TEnumeratorList* p);
void TEnumeratorList_Init(TEnumeratorList* p);

typedef struct TEnumSpecifier
{
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



struct _union(TStorageSpecifier |
    TFunctionSpecifier | 
    TAlignmentSpecifier | 
    TSingleTypeSpecifier | 
    TEnumSpecifier) TSpecifier;

typedef struct TSpecifier TSpecifier;

CAST(TSpecifier, TStorageSpecifier)
CAST(TSpecifier, TFunctionSpecifier)
CAST(TSpecifier, TAlignmentSpecifier)
CAST(TSpecifier, TSingleTypeSpecifier)
CAST(TSpecifier, TEnumSpecifier)


struct _union(TSpecifier |
              TTypeQualifier) TSpecifierQualifier;

typedef struct TSpecifierQualifier TSpecifierQualifier;
void TSpecifierQualifier_Delete(TSpecifierQualifier* p);

CAST(TSpecifierQualifier, TStorageSpecifier)
CAST(TSpecifierQualifier, TAlignmentSpecifier)
CAST(TSpecifierQualifier, TSingleTypeSpecifier)

CAST(TSpecifierQualifier, TTypeQualifier)
CAST(TSpecifierQualifier, TEnumSpecifier)


typedef struct {
    TSpecifierQualifier *_auto *_auto _size(Size) pData;
    int Size;
    int Capacity;
} TSpecifierQualifierList;

#define TSPECIFIERQUALIFIERLIST_INIT {0,0,0}

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers);
void TSpecifierQualifierList_PushBack(TSpecifierQualifierList* p, TSpecifierQualifier* pItem);
bool TSpecifierQualifierList_IsTypedef(TSpecifierQualifierList* p);
const char* TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList* p);
TSpecifier* TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAutoPointer(TSpecifierQualifierList *pSpecifierQualifierList);

bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList* p, Tokens token, const char* lexeme);
bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList* p);
bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList* p);


typedef struct TDeclarationSpecifiers {
    TSpecifier *_auto *_auto _size(Size) pData;
    int Size;
    int Capacity;
} TDeclarationSpecifiers;

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers);
void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers* p, TSpecifier* pItem);

const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers);
bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers* pDeclarationSpecifiers, Tokens token, const char* lexeme);


struct TParameter;
typedef struct TParameter TParameter;

typedef struct
{
    TParameter* _auto pHead, *pTail;
} TParameterList;

void TParameterList_Destroy(TParameterList* p);
void TParameterList_Init(TParameterList* p);
const char* TParameter_GetName(TParameter* p);
bool TParameter_IsDirectPointer(TParameter* p);

typedef struct TParameterTypeList
{
    TParameterList ParameterList;
    TScannerItemList ClueList0; //,
    TScannerItemList ClueList1; //...
    bool bVariadicArgs;
} TParameterTypeList;

void TParameterTypeList_Init(TParameterTypeList* p);
void TParameterTypeList_Destroy(TParameterTypeList* p);

typedef struct TDesignator
{
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
    TDesignator* _auto pHead, *pTail;
} TDesignatorList;
void TDesignatorList_Destroy(TDesignatorList* p);
void TDesignatorList_Init(TDesignatorList* p) ;


typedef struct TDesignation
{
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
    TDesignatorList  DesignatorList;
    TInitializer*_auto  pInitializer;
    struct TInitializerListItem* _auto pNext;
    TScannerItemList ClueList;
	bool bDefault;
} TInitializerListItem;

TInitializerListItem* TInitializerListItem_Create() ;
void TInitializerListItem_Delete(TInitializerListItem* p);



typedef struct TInitializerList
{
    TInitializerListItem * _auto pHead, *pTail;
} TInitializerList; 

void TInitializerList_Init(TInitializerList* p);
void TInitializerList_Destroy(TInitializerList* p);
void TInitializerList_Delete(TInitializerList* p);

typedef struct
{
    EType Type  _defval(TInitializerListType_ID);
    TInitializerList InitializerList;
	TScannerItemList ClueList00;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
	bool bDefault;
} TInitializerListType;

TInitializerListType* TInitializerListType_Create(void);
void TInitializerListType_Delete(TInitializerListType* p);



struct _union(TInitializerListType | TExpression) TInitializer;
typedef struct TInitializer TInitializer;

CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;
typedef struct TDirectDeclarator TDirectDeclarator;

typedef struct TDeclarator
{
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
    String Identifier; //identifier
    TDeclarator* _auto pDeclarator; //(declarator)
    struct TDirectDeclarator* _auto  pDirectDeclarator; //
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
    TDeclarator*_auto  pDeclarator;
    TInitializer*_auto   pInitializer;
    struct TInitDeclarator * _auto pNext;
    TScannerItemList ClueList00;	
	TScannerItemList ClueList1; //defval
} TInitDeclarator;


TInitDeclarator* TInitDeclarator_Create();
void TInitDeclarator_Delete(TInitDeclarator* p);

typedef TInitDeclarator TStructDeclarator;


typedef struct TInitDeclaratorList
{
    TInitDeclarator* _auto pHead, *pTail;
} TInitDeclaratorList;

void TInitDeclaratorList_Destroy(TInitDeclaratorList* p);
void TInitDeclaratorList_Init(TInitDeclaratorList* p);
const char* TDeclarator_GetName(TDeclarator* p);
const char* TInitDeclarator_FindName(TInitDeclarator* p);


typedef TInitDeclaratorList TStructDeclaratorList;


typedef struct TStructDeclaration
{
    EType Type  _defval(TStructDeclaration_ID);

    TSpecifierQualifierList SpecifierQualifierList;
    TStructDeclaratorList DeclaratorList;
    TScannerItemList ClueList1;
} TStructDeclaration;


TStructDeclaration* TStructDeclaration_Create();
void TStructDeclaration_Delete(TStructDeclaration* p);


struct _union(TStructDeclaration |
              TStaticAssertDeclaration) TAnyStructDeclaration;

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



struct _union(TSingleTypeSpecifier |
              TEnumSpecifier |
              TStructUnionSpecifier) TTypeSpecifier;

typedef struct TTypeSpecifier TTypeSpecifier;

CAST(TTypeSpecifier, TSingleTypeSpecifier)
CAST(TTypeSpecifier, TEnumSpecifier)
CAST(TTypeSpecifier, TStructUnionSpecifier)

CAST(TSpecifier, TStructUnionSpecifier)
CAST(TSpecifierQualifier, TStructUnionSpecifier)


typedef struct TDeclaration
{
    EType Type  _defval(TDeclaration_ID);
    TDeclarationSpecifiers Specifiers;
    TInitDeclaratorList InitDeclaratorList;

    //se for funcao
    TCompoundStatement* _auto  pCompoundStatementOpt;

    int FileIndex;
    int Line;

	TScannerItemList ClueList00; //default

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
    struct TParameter* _auto pNext;
    TDeclarationSpecifiers Specifiers;
    TDeclarator Declarator;
    
    //Anotacoes in out opt geradas automaticamente?
    //para os parametros?
    //para o retorno opt?
    TScannerItemList ClueList00; //, do parametro
    bool bHasComma;
} TParameter;

TParameter* TParameter_Create();
void TParameter_Delete(TParameter* p);

void TParameter_Swap(TParameter* a, TParameter* b);
const char* TParameter_GetTypedefName(TParameter* p);


typedef struct
{
    TAnyDeclaration * _auto * _auto _size(Size) pItems;
    int Size;
    int Capacity;
} TDeclarations;

void TDeclarations_Destroy(TDeclarations* p);
void TDeclarations_Init(TDeclarations* p);
void TDeclarations_PushBack(TDeclarations* p, TDeclarations* pItem);



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

   

} TProgram;


void TProgram_Init(TProgram* p);
void TProgram_Destroy(TProgram* p);
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName);
TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name);





typedef struct TTypeName
{
    EType Type  _defval(TypeName_ID);
    TSpecifierQualifierList SpecifierQualifierList;
    TDeclarator Declarator;
} TTypeName;

TTypeName* TTypeName_Create();
void TTypeName_Destroy(TTypeName* p);
void TTypeName_Delete(TTypeName* p) ;
void TTypeName_Init(TTypeName* p);

typedef struct TAtomicTypeSpecifier
{
    EType Type  _defval(TAtomicTypeSpecifier_ID);
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TAtomicTypeSpecifier;


TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create();
void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier* p);


CAST(TTypeSpecifier, TAtomicTypeSpecifier)



bool EvaluateConstantExpression(TExpression * p, int *pResult);

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration * p);


TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name);

bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers);



typedef struct
{
    EType Type _defval(TPrimaryExpressionValue_ID);
    Tokens token;
    String lexeme;
    TExpression*_auto   pExpressionOpt;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TPrimaryExpressionValue;

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

#define TPRIMARYEXPRESSIONLITERALITEMLIST_INIT LIST_INIT
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

    TScannerItemList ClueList00;

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

    //cast


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
    TScannerItemList ClueList00;
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
    TCastExpressionType) TExpression;

typedef struct TExpression TExpression;
void TExpression_Delete(TExpression* p);


CAST(TExpression, TPrimaryExpressionLiteral)
CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)

