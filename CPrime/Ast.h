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
static inline TO *  FROM##_As_##TO(FROM*  p)\
{\
if (p != NULL && p->Type == TO##_ID)\
    return ( TO * )p;\
  return NULL;\
}\
static inline FROM *  TO##_As_##FROM(TO*  p)\
{\
    return ( FROM * )p;\
}

#define CASTSAME(FROM, TO) \
static inline TO * FROM##_As_##TO(FROM* p) { return p; }\
static inline FROM * TO##_As_##FROM(TO* p) { return p; }


/*
   AST data structures
*/

typedef enum
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
} Type;
#define CASE(T) case T##_ID


#define CREATETYPEOR(TYPE)\
  typedef TTypePointer TYPE ;\
  void TYPE##_Destroy(TYPE* p);\
static inline void TYPE##_Delete(TYPE*  p)\
{\
  if (p)\
  {\
    TYPE##_Destroy(p);\
    free(p);\
  }\
}\
static inline void TYPE##_DeleteVoid(void*  p)\
{\
  TYPE##_Delete((TYPE*)p);\
}


#define CREATETYPE(TYPE, INIT) \
static inline TYPE*  TYPE##_Create(void)\
{\
  TYPE* p = (TYPE*)malloc(sizeof * p);\
  if (p)\
  {\
    TYPE temp_Moved = INIT;\
    *p =  temp_Moved;\
  }\
  else \
  {\
    exit(EXIT_FAILURE); \
  }\
  return p;\
}\
void TYPE##_Destroy(TYPE* p);\
static inline void TYPE##_Delete(TYPE*  p)\
{\
  if (p)\
  {\
    TYPE##_Destroy(p);\
    free(p);\
  }\
}\
static inline void TYPE##_DeleteVoid(void*  p)\
{\
  TYPE##_Delete((TYPE*)p);\
}


typedef struct
{
    int FileIndex;
    int Line;
} TPosition;
#define TPOSITION_INIT {0,0}

typedef struct TTypePointer
{
    Type Type;
    struct TTypePointer *pNext;
} TTypePointer;

typedef TTypePointer TExpression;

typedef struct
{
    TTypePointer Type;

    TExpression*_auto  pConstantExpression;
    String Text;
	TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    TScannerItemList ClueList4;
    TScannerItemList ClueList5;

} TStaticAssertDeclaration;
#define TSTATIC_ASSERT_DECLARATION_INIT { {TStaticAssertDeclaration_ID, NULL} , NULL, STRING_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TStaticAssertDeclaration, TSTATIC_ASSERT_DECLARATION_INIT)


typedef struct
{
	TTypePointer Type;
	TScannerItemList ClueList0;
} TEofDeclaration;

#define TEOFDECLARATION_INIT { {TEofDeclaration_ID, NULL} , TSCANNERITEMLIST_INIT}
CREATETYPE(TEofDeclaration, TEOFDECLARATION_INIT)


typedef TTypePointer TStatement;
typedef TTypePointer TBlockItem;

CREATETYPEOR(TBlockItem)
CASTSAME(TBlockItem, TStatement)

typedef TTypePointer TAnyDeclaration;
CASTSAME(TBlockItem, TAnyDeclaration)
CREATETYPEOR(TAnyDeclaration)

typedef ArrayT(TBlockItem) TBlockItemList;
void TBlockItemList_Destroy(TBlockItemList* p);

typedef struct
{
    TTypePointer Type;
    TBlockItemList BlockItemList;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    //bool bTemplate;
} TCompoundStatement;

#define TCOMPOUNDSTATEMENT_INIT { {TCompoundStatement_ID, NULL}, ARRAYT_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TCompoundStatement, TCOMPOUNDSTATEMENT_INIT)

//////////////////



typedef struct
{
    TTypePointer Type;
    Tokens token;
    String lexeme;
    TExpression*_auto   pExpressionOpt;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TPrimaryExpressionValue;

#define TPRIMARY_EXPRESSION_VALUE { {TPrimaryExpressionValue_ID, NULL}, TK_NONE, STRING_INIT, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TPrimaryExpressionValue, TPRIMARY_EXPRESSION_VALUE)

typedef struct TPrimaryExpressionLiteralItem
{
    struct TPrimaryExpressionLiteralItem* pNext;
    String lexeme;
    TScannerItemList ClueList0;
} TPrimaryExpressionLiteralItem;

#define TPRIMARYEXPRESSIONLITERALITEM_INIT {NULL, STRING_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TPrimaryExpressionLiteralItem, TPRIMARYEXPRESSIONLITERALITEM_INIT)

typedef List(TPrimaryExpressionLiteralItem) TPrimaryExpressionLiteralItemList;

void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList* p);

#define TPRIMARYEXPRESSIONLITERALITEMLIST_INIT LIST_INIT
typedef struct
{
    TTypePointer Type;
    TPrimaryExpressionLiteralItemList List;
} TPrimaryExpressionLiteral;

#define TPRIMARYEXPRESSIONLITERAL_INIT { {TPrimaryExpressionLiteral_ID, NULL}, LIST_INIT}
CREATETYPE(TPrimaryExpressionLiteral, TPRIMARYEXPRESSIONLITERAL_INIT)


typedef  struct TInitializerListItem TInitializerListItem;
typedef List(TInitializerListItem) TInitializerList;
void TInitializerList_Destroy(TInitializerList* p);


typedef struct
{
    TTypePointer Type;
    Tokens token;
    TExpression*_auto   pExpressionLeft;
    TExpression*_auto    pExpressionRight;
    TPosition Position;

    TScannerItemList ClueList00;

} TBinaryExpression;
#define TBINARYEXPRESSION_INIT { {TBinaryExpression_ID, NULL}, TK_NONE, NULL, NULL, TPOSITION_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TBinaryExpression, TBINARYEXPRESSION_INIT)

typedef struct
{
    TTypePointer Type;
    Tokens token;
    TExpression*_auto   pExpressionLeft;
    TExpression*_auto    pExpressionMiddle;
    TExpression*_auto    pExpressionRight;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TTernaryExpression;
#define TTERNARYEXPRESSION_INIT { {TTernaryExpression_ID, NULL}, TK_NONE, NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TTernaryExpression, TTERNARYEXPRESSION_INIT)



CREATETYPEOR(TExpression)

typedef struct TTypeQualifier
{
    Type Type;
    struct TTypeQualifier* pNext;

//#ifdef LANGUAGE_EXTENSIONS
    String SizeIdentifier;
//#endif

    Tokens Token;
    TScannerItemList ClueList0;


} TTypeQualifier;

typedef List(TTypeQualifier) TTypeQualifierList;
#define TTYPEQUALIFIERLIST_INIT LIST_INIT
#define TTypeQualifierList_Destroy(p) List_Destroy(TTypeQualifier, p)

#define TTYPE_QUALIFIER_INIT {TTypeQualifier_ID, NULL, STRING_INIT, TK_NONE, TSCANNERITEMLIST_INIT}
CREATETYPE(TTypeQualifier, TTYPE_QUALIFIER_INIT)

////////////////////////////

typedef struct
{
    TTypePointer Type;
    TExpression *_auto    pExpression;
    TScannerItemList ClueList0;
} TExpressionStatement;
#define TEXPRESSION_STATEMENT_INIT { {TExpressionStatement_ID, NULL}, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TExpressionStatement, TEXPRESSION_STATEMENT_INIT)

typedef struct
{
    TTypePointer Type;
    Tokens token;
    String Identifier;
    TExpression *_auto   pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TJumpStatement;

#define TJUMP_STATEMENT_INIT {{TJumpStatement_ID, NULL}, TK_NONE, STRING_INIT, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT }
CREATETYPE(TJumpStatement, TJUMP_STATEMENT_INIT)


typedef struct
{
    TTypePointer Type;
    TScannerItemList ClueList;
} TAsmStatement;

#define TASM_STATEMENT_INIT {{TAsmStatement_ID, NULL} , TSCANNERITEMLIST_INIT}
CREATETYPE(TAsmStatement, TASM_STATEMENT_INIT)


typedef struct
{
    TTypePointer Type;
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

#define TFORSTATEMENT_INIT {{TForStatement_ID, NULL}, NULL, NULL, NULL, NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TForStatement, TFORSTATEMENT_INIT)

typedef struct
{
    TTypePointer Type;
    TExpression*_auto   pExpression;
    TStatement*_auto   pStatement;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TWhileStatement;

#define TWHILESTATEMENT_INIT { {TWhileStatement_ID, NULL}, NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TWhileStatement, TWHILESTATEMENT_INIT)


typedef struct
{
    TTypePointer Type;
    TExpression *_auto    pExpression;
    TStatement*_auto    pStatement;
    TScannerItemList ClueList0; //do
    TScannerItemList ClueList1; //while
    TScannerItemList ClueList2; //(
    TScannerItemList ClueList3; //)
    TScannerItemList ClueList4; // ;
    
} TDoStatement;
#define TDOSTATEMENT_INIT {{TDoStatement_ID, NULL}, NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TDoStatement, TDOSTATEMENT_INIT)

typedef struct
{
    TTypePointer Type;

    TStatement *_auto   pStatementOpt;
    TExpression *_auto   pExpression;
    String Identifier;
    Tokens token;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TLabeledStatement;

#define TLABEDSTATEMENT_INIT {{TLabeledStatement_ID, NULL},  NULL, NULL, STRING_INIT, TK_NONE, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TLabeledStatement, TLABEDSTATEMENT_INIT)


typedef struct
{
    TTypePointer Type;
    TExpression *_auto   pConditionExpression;
    TStatement*_auto    pExpression;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TSwitchStatement;

#define TSWITCH_STATEMENT { {TSwitchStatement_ID, NULL}, NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TSwitchStatement, TSWITCH_STATEMENT)


typedef struct
{
    TTypePointer Type;
    TExpression*_auto    pConditionExpression;
    TStatement*_auto   pStatement;
    TStatement*_auto   pElseStatement;
    TScannerItemList ClueList0; //if 
    TScannerItemList ClueList1; //(
    TScannerItemList ClueList2; //)
    TScannerItemList ClueList3; //else
} TIfStatement;
#define TIFSTATEMENT_INIT { {TIfStatement_ID, NULL}, NULL, NULL, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TIfStatement, TIFSTATEMENT_INIT)



CREATETYPEOR(TStatement)
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



typedef struct TPointer
{
    TTypeQualifierList Qualifier;
    Tokens Token;
    struct TPointer* pNext;
    TScannerItemList ClueList0;
} TPointer;

#define TPOINTER_INIT {TTYPEQUALIFIERLIST_INIT, false, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TPointer, TPOINTER_INIT)


typedef List(TPointer) TPointerList;
void TPointerList_Destroy(TPointerList* p);
bool TPointerList_IsPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerN(TPointerList* pPointerlist, int n);
bool TPointerList_IsAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToAutoPointer(TPointerList* pPointerlist);
bool TPointerList_IsPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToObject(TPointerList* pPointerlist);
bool TPointerList_IsAutoPointerToPointer(TPointerList* pPointerlist);
const char * TPointerList_GetSize(TPointerList* pPointerlist);

typedef struct
{
    Type Type;
    void* pNext;
    bool bIsInline;
    bool bIsNoReturn;
    TScannerItemList ClueList0;
} TFunctionSpecifier;


void TFunctionSpecifier_Destroy(TFunctionSpecifier* p);

#define TFUNCTION_SPECIFIER_INIT {TFunctionSpecifier_ID, NULL, false, false, TSCANNERITEMLIST_INIT}
CREATETYPE(TFunctionSpecifier, TFUNCTION_SPECIFIER_INIT)

typedef struct
{
    Type Type;
    void* pNext;
    bool bIsTypedef;
    bool bIsExtern;
    bool bIsStatic;
    bool bIsThread_local;
    bool bIsAuto;
    bool bIsRegister;
    TScannerItemList ClueList0;
} TStorageSpecifier;
#define TSTORAGE_SPECIFIER_INIT {TStorageSpecifier_ID, NULL, false, false, false, false, false, false, TSCANNERITEMLIST_INIT}
CREATETYPE(TStorageSpecifier, TSTORAGE_SPECIFIER_INIT)



typedef struct
{
    Type Type;
    void *pNext;
    String TypeName;
    //_Alignas(type - name)
    //  _Alignas(constant - expression)
} TAlignmentSpecifier;
#define TALIGNMENT_SPECIFIER { TAlignmentSpecifier_ID, NULL, STRING_INIT }

CREATETYPE(TAlignmentSpecifier, TALIGNMENT_SPECIFIER)
void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p);



typedef struct TEnumerator
{
    
    TTypePointer Type;
    String Name;
    TExpression*_auto   pExpression;
    struct TEnumerator *pNext;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1; // =
    TScannerItemList ClueList2; // ,
    bool bHasComma;
} TEnumerator;

#define TENUMERATOR_INIT { {TEnumerator_ID, 0} ,STRING_INIT , NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, false}
CREATETYPE(TEnumerator, TENUMERATOR_INIT)

typedef List(TEnumerator) TEnumeratorList;
void TEnumeratorList_Destroy(TEnumeratorList* p);

typedef struct TEnumSpecifier
{
    TTypePointer Type;
    String Name;
    TEnumeratorList EnumeratorList;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
} TEnumSpecifier;

#define ENUM_SPECIFIER_INIT { {TEnumSpecifier_ID, NULL}, STRING_INIT, LIST_INIT, LIST_INIT, LIST_INIT, LIST_INIT, LIST_INIT }
CREATETYPE(TEnumSpecifier, ENUM_SPECIFIER_INIT)

typedef struct
{
    TTypePointer Type;
    void *pNext;
    Tokens Token;
    String TypedefName;  
    TScannerItemList ClueList0;
} TSingleTypeSpecifier;

#define TBUILDINTYPE_SPECIFIER_INIT { {TSingleTypeSpecifier_ID, NULL}, NULL, TK_NONE, STRING_INIT, LIST_INIT}
CREATETYPE(TSingleTypeSpecifier, TBUILDINTYPE_SPECIFIER_INIT)

const char* TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier* p);


typedef TTypePointer TTypeSpecifier;


CREATETYPEOR(TSpecifier)
CAST(TSpecifier, TStorageSpecifier)
//CAST(TSpecifier, TTypeQualifier)
CAST(TSpecifier, TFunctionSpecifier)
CAST(TSpecifier, TAlignmentSpecifier)
CAST(TSpecifier, TSingleTypeSpecifier)
CAST(TSpecifier, TEnumSpecifier)


CREATETYPEOR(TSpecifierQualifier)
CAST(TSpecifierQualifier, TStorageSpecifier)
CAST(TSpecifierQualifier, TAlignmentSpecifier)
CAST(TSpecifierQualifier, TSingleTypeSpecifier)

CAST(TSpecifierQualifier, TTypeQualifier)
CAST(TSpecifierQualifier, TEnumSpecifier)


//CAST(TSpecifierQualifier, TTypeQualifier)

typedef List(TSpecifierQualifier) TSpecifierQualifierList;
#define TSPECIFIERQUALIFIERLIST_INIT LIST_INIT
void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers);
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


//typedef List(TSpecifier) TDeclarationSpecifiers; //tODO pode ser 4 TSpecifier no max
typedef struct TDeclarationSpecifiers {    
        TSpecifier* pHead; 
        TSpecifier* pTail; 
} TDeclarationSpecifiers;

#define TDECLARATION_SPECIFIERS_INIT LIST_INIT
void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers);

const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers);
bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers* pDeclarationSpecifiers, Tokens token, const char* lexeme);



struct TParameter;
typedef struct TParameter TParameter;
typedef List(TParameter) TParameterList;

#define TParameterList_Destroy(x) List_Destroy(TParameter, (x))
const char* TParameter_GetName(TParameter* p);
bool TParameter_IsDirectPointer(TParameter* p);

typedef struct TParameterTypeList
{
    TParameterList ParameterList;
    TScannerItemList ClueList0; //,
    TScannerItemList ClueList1; //...
    bool bVariadicArgs;
} TParameterTypeList;

#define TPARAMETERTYPELIST_INIT {LIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, false}
//int TParameterTypeList_GetNumberOfParameters(TParameterTypeList* p);

typedef struct TDesignator
{
    String Name;
    TExpression *_auto  pExpression;
    struct TDesignator *pNext;
    TScannerItemList ClueList0; //. ou [
    TScannerItemList ClueList1; //]
} TDesignator;

#define TDESIGNATOR_INIT { STRING_INIT , NULL, NULL,TSCANNERITEMLIST_INIT}
CREATETYPE(TDesignator, TDESIGNATOR_INIT)
typedef List(TDesignator) TDesignatorList;


typedef struct TDesignation
{
    TDesignatorList DesignatorList;
    TScannerItemList ClueList0;
} TDesignation;

#define TDESIGNATION_INIT { LIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TDesignation, TDESIGNATION_INIT)

typedef TTypePointer TInitializer;

typedef struct TInitializerListItem
{
    TDesignatorList  DesignatorList;
    TInitializer*_auto  pInitializer;
    struct TInitializerListItem* pNext;
    TScannerItemList ClueList;
	bool bDefault;
} TInitializerListItem;

#define TINITIALIZER_LIST_ITEM_INIT { LIST_INIT , NULL, NULL, TSCANNERITEMLIST_INIT, false}
CREATETYPE(TInitializerListItem, TINITIALIZER_LIST_ITEM_INIT)



typedef struct
{
    TTypePointer Type;
    TInitializerList InitializerList;
	TScannerItemList ClueList00;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
	bool bDefault;
} TInitializerListType;

#define TINITIALIZER_LIST_TYPE_INIT {{TInitializerListType_ID, NULL}, LIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, false}
CREATETYPE(TInitializerListType, TINITIALIZER_LIST_TYPE_INIT)


CREATETYPEOR(TInitializer)
CAST(TInitializer, TInitializerListType)
CASTSAME(TInitializer, TExpression)

struct TDirectDeclarator;
typedef struct TDirectDeclarator TDirectDeclarator;

typedef struct TDeclarator
{
    TPointerList PointerList;
    TDirectDeclarator*_auto  pDirectDeclarator;
    TScannerItemList ClueList;
} TDeclarator;

#define TDECLARATOR_INIT {LIST_INIT, NULL, TSCANNERITEMLIST_INIT}
CREATETYPE(TDeclarator, TDECLARATOR_INIT)
//bool TDeclarator_IsPointer(TDeclarator* p);
//bool TDeclarator_IsAutoPointer(TDeclarator* p);
//bool TDeclarator_IsDirectPointer(TDeclarator* p);
const char* TDeclarator_GetName(TDeclarator* p);

//typedef struct TAbstractDeclarator
//{
  //TPointerList PointerList;
  //struct TAbstractDeclarator* pDirectDeclarator;
//} TAbstractDeclarator;

//#define TDECLARATOR_INIT {TPOINTERLIST_INIT, NULL}
//CREATETYPE(TDeclarator, TDECLARATOR_INIT)


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
    TDirectDeclaratorType Type; //para diferenciar pois null nao basta []
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
} TDirectDeclarator;

#define TDIRECTDECLARATOR_INIT { STRING_INIT, NULL  ,NULL, TPOSITION_INIT, TPARAMETERTYPELIST_INIT, NULL, TDirectDeclaratorTypeNone, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TDirectDeclarator, TDIRECTDECLARATOR_INIT)


typedef struct TInitDeclarator
{
    TTypePointer Type;
    TDeclarator*_auto  pDeclarator;
    TInitializer*_auto   pInitializer;
    struct TInitDeclarator * pNext;
    TScannerItemList ClueList00;	
	TScannerItemList ClueList1; //defval
} TInitDeclarator;

#define TINITDECLARATOR_INIT {{TInitDeclarator_ID, NULL}, NULL, NULL, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TInitDeclarator, TINITDECLARATOR_INIT)

typedef TInitDeclarator TStructDeclarator;
typedef List(TInitDeclarator) TInitDeclaratorList;

const char* TDeclarator_GetName(TDeclarator* p);
const char* TInitDeclarator_FindName(TInitDeclarator* p);


typedef TInitDeclaratorList TStructDeclaratorList;


typedef struct
{
    TTypePointer Type;//= {TStructDeclaration_ID, NULL}

    TSpecifierQualifierList SpecifierQualifierList;
    TStructDeclaratorList DeclaratorList;
    TScannerItemList ClueList1;
} TStructDeclaration;
#define TSTRUCT_DECLARATION_BASE_INIT {{TStructDeclaration_ID, NULL}, TSPECIFIERQUALIFIERLIST_INIT,  LIST_INIT, TSCANNERITEMLIST_INIT}


CREATETYPE(TStructDeclaration, TSTRUCT_DECLARATION_BASE_INIT)

//Mudar o nome p TAnyStructDeclaration
CREATETYPEOR(TAnyStructDeclaration)

CAST(TAnyStructDeclaration, TStructDeclaration)
CAST(TAnyStructDeclaration, TStaticAssertDeclaration)
CAST(TAnyStructDeclaration, TEofDeclaration)

typedef ArrayT(TAnyStructDeclaration) TStructDeclarationList;
void TStructDeclarationList_Destroy(TStructDeclarationList* p);

typedef struct TStructUnionSpecifier
{
    TTypePointer Type;
    TStructDeclarationList StructDeclarationList;
    String Name;
    String TemplateName;
    bool bIsStruct;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    List(struct TTemplateTypeSpecifierArgument) Args;
} TStructUnionSpecifier;
#define TSTRUCT_UNION_SPECIFIER_INIT { {TStructUnionSpecifier_ID, NULL}, ARRAYT_INIT, STRING_INIT , STRING_INIT , true , LIST_INIT, LIST_INIT, LIST_INIT}

bool TStructUnionSpecifier_IsTemplate(TStructUnionSpecifier* p, const char* templateName);
CREATETYPE(TStructUnionSpecifier, TSTRUCT_UNION_SPECIFIER_INIT)


CREATETYPEOR(TTypeSpecifier)
CAST(TTypeSpecifier, TSingleTypeSpecifier)
CAST(TTypeSpecifier, TEnumSpecifier)
CAST(TTypeSpecifier, TStructUnionSpecifier)

CAST(TSpecifier, TStructUnionSpecifier)
CAST(TSpecifierQualifier, TStructUnionSpecifier)


typedef struct TDeclaration
{
    TTypePointer Type;
    TDeclarationSpecifiers Specifiers;
    TInitDeclaratorList InitDeclaratorList;

    //se for funcao
    TCompoundStatement* _auto  pCompoundStatementOpt;

    int FileIndex;
    int Line;

	TScannerItemList ClueList00; //default
    //TScannerItemList ClueList0;

    bool bDefault;
    TScannerItemList ClueList1;


} TDeclaration;
#define TFUNCVARDECLARATION_INIT { {TDeclaration_ID, NULL}, TDECLARATION_SPECIFIERS_INIT, LIST_INIT, NULL,  -1, -1, TSCANNERITEMLIST_INIT,  false, TSCANNERITEMLIST_INIT}
CREATETYPE(TDeclaration, TFUNCVARDECLARATION_INIT)

TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(TDeclaration* p, int index);
void TDeclaration_Destroy(TDeclaration* p);

const char* TDeclaration_GetArgName(TDeclaration* p, int index);
int TDeclaration_GetNumberFuncArgs(TDeclaration* p);

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p);
//bool TDeclaration_Is_FunctionDeclaration(TDeclaration* p);
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
    TTypePointer Type;
    TDeclarationSpecifiers Specifiers;
    TDeclarator Declarator;

    struct TParameter* pNext;
    //Anotacoes in out opt geradas automaticamente?
    //para os parametros?
    //para o retorno opt?
    TScannerItemList ClueList00; //, do parametro
    bool bHasComma;
} TParameter;
#define TPARAMETER_DECLARATION_INIT { { TParameter_ID, NULL}, TDECLARATION_SPECIFIERS_INIT, TDECLARATOR_INIT, NULL, TSCANNERITEMLIST_INIT, false}
void TParameter_Destroy(TParameter* p);
void TParameter_Swap(TParameter* a, TParameter* b);
const char* TParameter_GetTypedefName(TParameter* p);

CREATETYPE(TParameter, TPARAMETER_DECLARATION_INIT)

typedef ArrayT(TAnyDeclaration) TDeclarations;


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



typedef struct TTypeName
{
    Type Type;
    TSpecifierQualifierList SpecifierQualifierList;
    TDeclarator Declarator;
} TTypeName;

//Na verdade Typename nao precisa umas partes do
//TParameterDeclaration
//mas para simplificar vou usar o mesmo
//typedef TParameterDeclaration TTypeName;
#define TTYPENAME_INIT {TypeName_ID, TSPECIFIERQUALIFIERLIST_INIT, TDECLARATOR_INIT}
CREATETYPE(TTypeName, TTYPENAME_INIT)


typedef struct TAtomicTypeSpecifier
{
    Type Type;
    void* pNext;
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
} TAtomicTypeSpecifier;

#define TATOMICTYPESPECIFIER_INIT {TStorageSpecifier_ID, NULL, TTYPENAME_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TAtomicTypeSpecifier, TATOMICTYPESPECIFIER_INIT)
CAST(TTypeSpecifier, TAtomicTypeSpecifier)

typedef struct  TTemplateTypeSpecifierArgument
{
    TTypeName TypeName;
    struct TTemplateTypeSpecifierArgument* pNext;
} TTemplateTypeSpecifierArgument;

#define TTEMPLATETYPESPECIFIERARGUMENT_INIT {TTYPENAME_INIT, NULL}
CREATETYPE(TTemplateTypeSpecifierArgument, TTEMPLATETYPESPECIFIERARGUMENT_INIT)



typedef List(TTemplateTypeSpecifierArgument) TTemplateTypeSpecifierArgumentList;

#define TTemplateTypeSpecifierArgumentList_Destroy(p) List_Destroy(TTemplateTypeSpecifierArgument, p)


typedef struct TTemplateTypeSpecifier
{
    Type Type;
    void* pNext;
    TTemplateTypeSpecifierArgumentList Args;
    String Identifier;
    TScannerItemList ClueList0;
} TTemplateTypeSpecifier;

#define TTEMPLATETYPESPECIFIER_INIT {TTemplateTypeSpecifier_ID, NULL, LIST_INIT, STRING_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TTemplateTypeSpecifier, TTEMPLATETYPESPECIFIER_INIT)
CAST(TTypeSpecifier, TTemplateTypeSpecifier)
CAST(TSpecifier, TTemplateTypeSpecifier)

typedef struct TPostfixExpressionCoreTag
{
    TTypePointer Type;
    Tokens token;
    String lexeme;
    TExpression*_auto   pExpressionLeft;
    TExpression*_auto   pExpressionRight;

    //cast


    struct TPostfixExpressionCoreTag*  pNext;
    TInitializerList InitializerList;
    String Identifier;
    TTypeName*_auto  pTypeName; /*typename*/
    
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
    TScannerItemList ClueList2;
    TScannerItemList ClueList3;
    TScannerItemList ClueList4;

} TPostfixExpressionCore;
#define TPOSTFIX_EXPRESSION_CORE { {TPostfixExpressionCore_ID, NULL}, TK_NONE, STRING_INIT, NULL, NULL, NULL, LIST_INIT, STRING_INIT, NULL, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TPostfixExpressionCore, TPOSTFIX_EXPRESSION_CORE)


typedef struct
{
    TTypePointer Type;
    TExpression*_auto    pExpression;
    TTypeName TypeName;
    TScannerItemList ClueList0;
    TScannerItemList ClueList1;
} TCastExpressionType;
#define TCAST_EXPRESSION_INIT { {TCastExpressionType_ID, NULL}, NULL , TTYPENAME_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TCastExpressionType, TCAST_EXPRESSION_INIT)




typedef struct
{
    TTypePointer Type;
    Tokens token;
    TExpression*_auto   pExpressionRight;
    TTypeName TypeName;
    TScannerItemList ClueList00;
	TScannerItemList ClueList1; //sizeof (
	TScannerItemList ClueList2; //sizeof ( )
} TUnaryExpressionOperator;

#define TUNARY_EXPRESSION_OPERATOR_INIT { {TUnaryExpressionOperator_ID, NULL}, TK_NONE,  NULL, TTYPENAME_INIT, TSCANNERITEMLIST_INIT}
CREATETYPE(TUnaryExpressionOperator, TUNARY_EXPRESSION_OPERATOR_INIT)


bool EvaluateConstantExpression(TExpression * p, int *pResult);

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration * p);

CAST(TExpression, TPrimaryExpressionLiteral)
CAST(TExpression, TPrimaryExpressionValue)
CAST(TExpression, TBinaryExpression)
CAST(TExpression, TUnaryExpressionOperator)
CAST(TExpression, TPostfixExpressionCore)
CAST(TExpression, TCastExpressionType)

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name);

bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers);